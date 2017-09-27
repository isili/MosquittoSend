mosquitto_send: mosquitto_send.o
	gcc -o mosquitto_send mosquitto_send.o

mosquitto_send.o: mosquitto_send.c
	gcc -c mosquitto_send.c

clean:
	-rm -f mosquitto_send.o
	-rm -f mosquitto_send
