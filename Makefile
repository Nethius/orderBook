CC=g++
CFLAGS=-c -Wall
SOURCES=Storage/Storage.cpp Storage/Storage.h Parser/CommandsParser.cpp Parser/CommandsParser.h Commands/ModifyOrder.cpp Commands/ModifyOrder.h Commands/MdReplay.cpp Commands/MdReplay.h Commands/Subscribes.cpp Commands/Subscribes.h View/Print.cpp View/Print.h View/PrintFull.cpp View/PrintFull.h View/SubscribesView.cpp View/SubscribesView.h View/Menu.cpp View/Menu.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=orderBook

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $< -o $@