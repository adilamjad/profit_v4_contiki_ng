echo "Start time: "
date

rm rate*
cp ./NO_PROFIT/* .

echo "Rate 01"
cp sim_config.1.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate01.log

echo "Rate 02"
cp sim_config.2.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate02.log

echo "Rate 03"
cp sim_config.3.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate03.log

echo "Rate 04"
cp sim_config.4.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate04.log

echo "Rate 05"
cp sim_config.5.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate05.log

echo "Rate 06"
cp sim_config.6.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate06.log

echo "Rate 07"
cp sim_config.7.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate07.log

echo "Rate 08"
cp sim_config.8.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate08.log

echo "Rate 09"
cp sim_config.9.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate09.log

echo "Rate 10"
cp sim_config.10.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate10.log

echo "Rate 11"
cp sim_config.11.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate11.log

echo "Rate 12"
cp sim_config.12.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate12.log

echo "Rate 13"
cp sim_config.13.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate13.log

echo "Rate 14"
cp sim_config.14.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate14.log

echo "Rate 15"
cp sim_config.15.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate15.log

echo "Rate 16"
cp sim_config.16.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate16.log

echo "Rate 17"
cp sim_config.17.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate17.log

echo "Rate 18"
cp sim_config.18.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate18.log

echo "Rate 19"
cp sim_config.19.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate19.log

echo "Rate 20"
cp sim_config.20.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate20.log

echo "Rate 21"
cp sim_config.21.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate21.log

echo "Rate 22"
cp sim_config.22.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate22.log

echo "Rate 23"
cp sim_config.23.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate23.log

echo "Rate 24"
cp sim_config.24.h sim_config.h
java -jar /home/user/contiki-ng/tools/cooja/dist/cooja.jar -nogui=PROFIT-4-3-cooja-mote-nogui.csc -contiki=/home/user/contiki-ng 
mv COOJA.testlog rate24.log

echo "End time: "
date
echo "End of Simulations"
