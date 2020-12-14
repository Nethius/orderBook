cmake_minimum_required(VERSION 3.16)
project(orderBook)

set(CMAKE_CXX_STANDARD 17)
include_directories(Source)
add_executable(orderBook main.cpp Source/Parser/CommandsParser.cpp Source/Parser/CommandsParser.h Source/Storage/Storage.cpp Source/Storage/Storage.h Source/View/Print.cpp Source/View/Print.h Source/View/PrintFull.cpp Source/View/PrintFull.h Source/View/Menu.cpp Source/View/Menu.h Source/Commands/Subscribes.cpp Source/Commands/Subscribes.h Source/View/SubscribesView.cpp Source/View/SubscribesView.h Source/Commands/ModifyOrder.cpp Source/Commands/ModifyOrder.h Source/Commands/MdReplay.cpp Source/Commands/MdReplay.h)