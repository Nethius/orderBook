//
// Created by developer_stag on 01.12.2020.
//

#ifndef ORDERBOOK_COMMANDSPARSER_H
#define ORDERBOOK_COMMANDSPARSER_H
#include <cstdint>
#include <string>
#include "Storage.h"

struct Order;
struct Command
{
    std::string commandName;
    Order order;
};

Command parser(std::string str);



#endif //ORDERBOOK_COMMANDSPARSER_H
