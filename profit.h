#ifndef PROFIT_H_
#define PROFIT_H_

#include "sys/node-id.h"
#include "sim_config.h"

#define PROFIT_MAX_DATA_LEN         100
#define PROFIT_MAX_QUEUE_LEN        8
#define PROFIT_MAX_SOURCES          4
#define PROFIT_LAST_SOURCE          0xFFFF
#define PROFIT_MAX_PKTS_TO_SEND		1000

#define PROFIT_PRIORITY_HI          1
#define PROFIT_PRIORITY_LO          2

typedef uint8_t PRIORITY;

#define PKT_TX_INTERVAL                  (16*CLOCK_SECOND)


/* PRoFIT Structure for Packet */
typedef struct profit_packet
{
    uint8_t priority;
    uint32_t seq;
    uint8_t data[PROFIT_MAX_DATA_LEN];
}PROFIT_PACKET;

/* PRoFIT Queue */
typedef struct profit_queue_struct {
  struct profit_queue_struct *next;
  //struct simple_udp_connection *udp_conn;
  uint16_t len;
  uip_ipaddr_t *dest_ipaddr;
  PROFIT_PACKET pkt;
}PROFIT_Q_ELEMENT;

#endif /* PROFIT_H_ */
