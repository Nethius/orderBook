cmake_minimum_required(VERSION 3.16)
project(orderBook)

set(CMAKE_CXX_STANDARD 17)
include_directories(Commands Parser Storage View)
add_executable(orderBook main.cpp Commands/CommandsList.cpp Commands/CommandsList.h Parser/CommandsParser.cpp Parser/CommandsParser.h Storage/Storage.cpp Storage/Storage.h View/Print.cpp View/Print.h View/PrintFull.cpp View/PrintFull.h View/Menu.cpp View/Menu.h Commands/Subscribes.cpp Commands/Subscribes.h View/SubscribesView.cpp View/SubscribesView.h Commands/ModifyOrder.cpp Commands/ModifyOrder.h)