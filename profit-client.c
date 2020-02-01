#include "contiki.h"
#include "net/routing/routing.h"
#include "random.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "profit.h"

#include "sys/log.h"
#include "sys/node-id.h"
#include "lib/list.h"
#include "lib/memb.h"

#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

#define WITH_SERVER_REPLY    1
#define UDP_CLIENT_PORT        8765
#define UDP_SERVER_PORT        5678

#define PKT_GEN_INTERVAL                 (30*CLOCK_SECOND)
#define PKT_TX_INTERVAL                  (60*CLOCK_SECOND)

static struct simple_udp_connection udp_conn;

static PROFIT_PACKET pkt;

/*---------------------------------------------------------------------------*/
PROCESS(gen_process, "UDP client");
PROCESS(profit_q_process, "PRoFIT Q");

AUTOSTART_PROCESSES(&gen_process, &profit_q_process);

/* PRoFIT Queue */
LIST(PRoFIT_Q);

/* Memory PRoFIT Queue */
MEMB(PRoFIT_Q_Mem, PROFIT_Q_ELEMENT, PROFIT_MAX_QUEUE_LEN);

/* List of PRoFIT Sources */
static uint16_t source_list[PROFIT_MAX_SOURCES] = {13, PROFIT_LAST_SOURCE};

/******************************************************************************
    Function Name:
        PRoFIT_Is_Source
    Description:
        This function checks if the calling node is among the sources or not.
******************************************************************************/
static uint8_t PRoFIT_Is_Source()
{

    uint8_t found = 0;
    uint16_t i = 0;   

    for (i = 0; i < PROFIT_MAX_SOURCES; i++)
    {
        if (node_id == source_list[i])
        {
            found = 1;
            break;
        }
        else if (PROFIT_LAST_SOURCE == source_list[i])
        {
            break;
        }
    }

    return found;
}

/******************************************************************************
    Function Name:
        PRoFIT_Send_Pkt
    Description:
        This function checks if the calling node is among the sources or not.
******************************************************************************/
static uint8_t PRoFIT_Send_Pkt(PROFIT_PACKET *pkt, uint16_t len, uip_ipaddr_t *dest_ipaddr, PRIORITY p)
{

    uint16_t qlen = list_length(PRoFIT_Q);
    static uint32_t dropped_hi = 0;
    static uint32_t dropped_lo = 0;
    static uint32_t enqueued = 1;
    
    //LOG_INFO("QueueLen:%d\n", qlen);

    if (qlen > (PROFIT_MAX_QUEUE_LEN-1))
    {
        if (p == PROFIT_PRIORITY_HI)
        {
            dropped_hi++;
        }
        else if (p == PROFIT_PRIORITY_LO)
        {
            dropped_lo++;
        }
        LOG_INFO("DROPPED :T:%d:H:%d:L:%d:\n", enqueued, dropped_hi, dropped_lo);
        return -1;
    }

    PROFIT_Q_ELEMENT *pqe;
    /* Allocate memory for queue element. */
    pqe = memb_alloc(&PRoFIT_Q_Mem);

    if (pqe)
    {
        /* Save priority in outgoing packet. */
        pkt->priority = p;

        /* Copy outgoung packet into queue element. */
        memcpy(&pqe->pkt, pkt, len);
        pqe->len = len;
        pqe->dest_ipaddr = dest_ipaddr;
        
        if (p == PROFIT_PRIORITY_HI)
        {
            /* Insert high priority packet into queue head. */
            list_push(PRoFIT_Q, pqe);
        }
        else
        {
            /* Insert low priority packet into queue tail. */
            list_add(PRoFIT_Q, pqe);
        }

        /* Increment number of enqueued packets. */
        enqueued++;
    }
    else
    {
        LOG_INFO("Unable to allocate pqe\n");
    }
    return 1;
}

/*---------------------------------------------------------------------------*/


static void udp_rx_callback(struct simple_udp_connection *c,
                            const uip_ipaddr_t *sender_addr,
                            uint16_t sender_port,
                            const uip_ipaddr_t *receiver_addr,
                            uint16_t receiver_port,
                            const uint8_t *data,
                            uint16_t datalen)
{

    PROFIT_PACKET *recv_pkt;

    recv_pkt = (PROFIT_PACKET *)data;
    LOG_INFO("Client received packet [%d] priority is %d with 1st data:%d and last data:%d from ", datalen, recv_pkt->priority, recv_pkt->data[0], recv_pkt->data[PROFIT_MAX_DATA_LEN-1]);
    LOG_INFO_6ADDR(sender_addr);
    LOG_INFO_("\n");
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(gen_process, ev, data)
{
    static struct etimer periodic_timer;
    static uint32_t count;
    static uint16_t i;
    static uint8_t priority;

    uip_ipaddr_t dest_ipaddr;

    PROCESS_BEGIN();

    for (i = 0; i < PROFIT_MAX_DATA_LEN; i++)
    {
        pkt.data[i] = i;
    }

    /* Initialize UDP connection */
    simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL, UDP_SERVER_PORT, udp_rx_callback);
    
    if (PRoFIT_Is_Source())
    {
        LOG_INFO("Source Node ID: %d\n", node_id);

        etimer_set(&periodic_timer, random_rand() % PKT_GEN_INTERVAL);
        
        while(1) 
        {
            PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));

            if(NETSTACK_ROUTING.node_is_reachable() && NETSTACK_ROUTING.get_root_ipaddr(&dest_ipaddr)) 
            {
                /* Send to DAG root */
                //LOG_INFO("Sending request %u to ", count);
                //LOG_INFO_6ADDR(&dest_ipaddr);
                //LOG_INFO_("\n");
                pkt.seq = count;
                priority = 1 + count % 2;
                PRoFIT_Send_Pkt(&pkt, sizeof(pkt), &dest_ipaddr, priority);
                LOG_INFO("SENDER Seq:%d:P:%d:SINK:%d:\n", 
                         pkt.seq,
                         priority,
                         dest_ipaddr.u8[15]);
                
                count++;
                if (count == PROFIT_MAX_PKTS_TO_SEND)
                {
                    LOG_INFO("Last packet sent.\n");
                    break;       
                }
            } 
            else 
            {
                LOG_INFO("Not reachable yet\n");
            }

            /* Add some jitter */
            etimer_set(&periodic_timer, PKT_GEN_INTERVAL - CLOCK_SECOND + (random_rand() % (2 * CLOCK_SECOND)));
        }
        /* End simulation after 10 minutes */
        etimer_set(&periodic_timer, 10*60*CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));  
        LOG_INFO("SIMULATION HAS ENDED.\n");
    }

    PROCESS_END();
}
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
PROCESS_THREAD(profit_q_process, ev, data)
{
    static struct etimer periodic_timer;

    static PROFIT_PACKET pkt;
    static uip_ipaddr_t dest_ipaddr;
    static PROFIT_Q_ELEMENT *pqe;
    static uint16_t qlen, plen;

    
    PROCESS_BEGIN();
    
    LOG_INFO("Started PRoFIT queing process on Node: %d\n", node_id);

    etimer_set(&periodic_timer, random_rand() % PKT_TX_INTERVAL);

    while(1) 
    {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));

        qlen = list_length(PRoFIT_Q);

        if (qlen > 0)
        {

            if(NETSTACK_ROUTING.node_is_reachable() && NETSTACK_ROUTING.get_root_ipaddr(&dest_ipaddr)) 
            {
                pqe = (PROFIT_Q_ELEMENT *)list_pop(PRoFIT_Q);
                if (pqe)
                {
                    memcpy(&pkt, &pqe->pkt, sizeof(PROFIT_PACKET));
                    plen = pqe->len;

                    memb_free(&PRoFIT_Q_Mem, pqe);

                    /* Send to DAG root */
                    //LOG_INFO("QUEUE request for [%d]", pqe->len);
                    //LOG_INFO_6ADDR(&dest_ipaddr);
                    //LOG_INFO_("\n");
                    simple_udp_sendto(&udp_conn, &pkt, plen, &dest_ipaddr);

                }
                else
                {
                    LOG_INFO("PRoFIT Q empty\n");
                }
            } 
            else 
            {
                LOG_INFO("Not reachable yet\n");
            }
        }
        /* Add some jitter */
        etimer_set(&periodic_timer, PKT_TX_INTERVAL - CLOCK_SECOND + (random_rand() % (2 * CLOCK_SECOND)));
    }

    PROCESS_END();
}
/*---------------------------------------------------------------------------*/
