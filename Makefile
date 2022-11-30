# Usage
# > make
# > ./main.out

CC = g++ -std=c++14

CFLAGS = -g
LDFLAGS = -ljsoncpp -L/opt/homebrew/lib/ -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

OBJ	= Person.o Thing.o GPS.o TIME.o

all: 	hw5Home hw5Forest hw5GrandmaHome

hw5home.h:		ecs36b_hw5.json
	jsonrpcstub ecs36b_hw5.json --cpp-server=hw5Forest --cpp-client=hw5Home

hw5forest.h:	ecs36b_hw5.json
	jsonrpcstub ecs36b_hw5.json --cpp-server=hw5Forest --cpp-client=hw5Home

Person.o:	Person.cpp Person.h
	$(CC) -c $(CFLAGS) Person.cpp

Thing.o:	Thing.cpp Thing.h
	$(CC) -c $(CFLAGS) Thing.cpp

GPS.o:	GPS.cpp GPS.h
	$(CC) -c $(CFLAGS) GPS.cpp

TIME.o:	TIME.cpp TIME.h
	$(CC) -c $(CFLAGS) TIME.cpp

ecs36b_JSON.o:	ecs36b_JSON.cpp ecs36b_JSON.h
	$(CC) -c $(CFLAGS) ecs36b_JSON.cpp

hw5Home.o:	hw5Home.cpp hw5home.h Person.h
	$(CC) -c $(CFLAGS) hw5Home.cpp

hw5Forest.o:	hw5Forest.cpp hw5forest.h Person.h
	$(CC) -c $(CFLAGS) hw5Forest.cpp

hw5GrandmaHome.o: hw5GrandmaHome.cpp hw5forest.h Person.h
	$(CC) -c $(CFLAGS) hw5GrandmaHome.cpp

hw5Home:	hw5Home.o ecs36b_JSON.o $(OBJ)
	g++ -std=c++14 hw5Home.o ecs36b_JSON.o $(OBJ) -o hw5Home $(LDFLAGS)

hw5Forest:	hw5Forest.o ecs36b_JSON.o $(OBJ)
	g++ -std=c++14 hw5Forest.o ecs36b_JSON.o $(OBJ) -o hw5Forest $(LDFLAGS)

hw5GrandmaHome:	hw5GrandmaHome.o ecs36b_JSON.o $(OBJ)
	g++ -std=c++14 hw5GrandmaHome.o ecs36b_JSON.o $(OBJ) -o hw5GrandmaHome $(LDFLAGS)

clean:
	rm -fr *.o *.out hw5home.h hw5forest.h hw5Home hw5Forest hw5GrandmaHome