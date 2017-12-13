# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build target executable:
TARGET = mosquitto_send

$(TARGET): $(TARGET).o
	$(CC)	$(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	-rm	-f	$(TARGET).o
	-rm	-f	$(TARGET)



#mosquitto_send: mosquitto_send.o
#	gcc -o mosquitto_send mosquitto_send.o
#
#mosquitto_send.o: mosquitto_send.c
#	gcc -c mosquitto_send.c
#
#clean:
#	-rm -f mosquitto_send.o
#	-rm -f mosquitto_send
