CC=g++
CFLAGS=-c -Wall
SOURCES=Parser/CommandsParser.cpp Parser/CommandsParser.h Storage/Storage.cpp Storage/Storage.h View/Print.cpp View/Print.h View/PrintFull.cpp View/PrintFull.h View/Menu.cpp View/Menu.h Commands/Subscribes.cpp Commands/Subscribes.h View/SubscribesView.cpp View/SubscribesView.h Commands/ModifyOrder.cpp Commands/ModifyOrder.h Commands/MdReplay.cpp Commands/MdReplay.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=orderBook

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $< -o $@