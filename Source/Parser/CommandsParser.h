//
// Created by developer_stag on 01.12.2020.
//

#ifndef ORDERBOOK_COMMANDSPARSER_H
#define ORDERBOOK_COMMANDSPARSER_H

#include <cstdint>
#include <string>
#include <Storage/Storage.h>

namespace commandParser {
    Command parser(const std::string &str);
}


#endif //ORDERBOOK_COMMANDSPARSER_H
