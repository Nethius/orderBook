CC=g++
CFLAGS=-c -std=c++17 -Wall -pedantic
SOURCES=Storage/Storage.cpp Parser/CommandsParser.cpp Commands/ModifyOrder.cpp Commands/MdReplay.cpp Commands/Subscribes.cpp View/Print.cpp View/PrintFull.cpp View/SubscribesView.cpp View/Menu.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=orderBook
HEADERS=Storage/Storage.h Parser/CommandsParser.h Commands/ModifyOrder.h Commands/MdReplay.h Commands/Subscribes.h View/Print.h View/PrintFull.h View/SubscribesView.h View/Menu.h
all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $< -o $@

clean:
	rm -rf *.o orderBook