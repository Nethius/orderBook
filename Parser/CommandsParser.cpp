//
// Created by developer_stag on 01.12.2020.
//

#include "CommandsParser.h"
#include "vector"
#include "sstream"

Command parser(std::string str) //TODO добавить проверку на ошибки и переполнение строки
{
    Command cmd;
    std::vector<std::string> elems;
    std::stringstream sstr(str);
    std::string item;
    char d = 0x2C;
    while (std::getline(sstr, item, d)) {
        elems.push_back(item);
    }
    cmd.commandName = elems[0];
    cmd.order.id = std::stoull(elems[1]);
    cmd.order.data.symbol = elems[2];
    if (elems[3] == "Buy")
        cmd.order.side = OrderAction::BUY;
    else
        cmd.order.side = OrderAction::SELL;

    cmd.order.data.quantity = std::stoull(elems[4]);
    cmd.order.price = std::stod(elems[5]);
    return cmd;
}