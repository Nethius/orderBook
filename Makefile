CC=g++
CFLAGS=-g -std=c++17 -Wall -pedantic
SOURCES=Storage/Storage.h Storage/Storage.cpp Parser/CommandsParser.h Parser/CommandsParser.cpp Commands/ModifyOrder.h Commands/ModifyOrder.cpp Commands/MdReplay.h Commands/MdReplay.cpp Commands/Subscribes.h Commands/Subscribes.cpp View/Print.h View/Print.cpp View/PrintFull.h View/PrintFull.cpp View/SubscribesView.h View/SubscribesView.cpp View/Menu.h View/Menu.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=orderBook

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $< -o $@