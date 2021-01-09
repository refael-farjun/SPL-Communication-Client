CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude 
LDFLAGS:=-lboost_system -pthread -lboost_thread


all: BGRSclient

@echo 'Building target: 'BGRSclient'
@echo 'Invoking: 'C++ Linker'
BGRSclient: bin/connectionHandler.o bin/BGRSClient.o bin/Server2Client.o bin/User2Client.o bin/echoClient.o
	 g++ -Wall -Weffc++ -o bin/BGRSclient bin/connectionHandler.o bin/BGRSClient.o bin/Server2Client.o bin/User2Client.o bin/echoClient.o $(LDFLAGS)
@echo 'Finished building target: BGRSclient'

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp $(LDFLAGS)

bin/BGRSClient.o: src/BGRSClient.cpp
	g++ $(CFLAGS) -o bin/BGRSClient.o src/BGRSClient.cpp

bin/Server2Client.o: src/Server2Client.cpp
	g++ $(CFLAGS) -o bin/Server2Client.o src/Server2Client.cpp

bin/User2Client.o:src/User2Client.cpp
		g++ $(CFLAGS) -o bin/User2Client.o src/User2Client.cpp $(LDFLAGS)

bin/echoClient.o:src/echoClient.cpp
		g++ $(CFLAGS) -o bin/echoClient.o src/echoClient.cpp $(LDFLAGS)

.PHONY: clean
clean:
	@echo 'Cleaning'
	rm -f bin/*


