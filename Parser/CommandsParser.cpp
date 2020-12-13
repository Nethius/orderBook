//
// Created by developer_stag on 01.12.2020.
//

#include "CommandsParser.h"
#include "vector"
#include "sstream"

namespace commandParser {
    Command parser(const std::string& str)
    {
        Command cmd;
        std::vector<std::string> elems;
        std::stringstream sstr(str);
        std::string item;
        char d = 0x2C;
        try {
            while (std::getline(sstr, item, d)) {
                elems.push_back(item);
            }
            cmd.commandName = elems[0];
            if (elems.size() > 1 && elems[1] != "")
                cmd.order.id = std::stoull(elems[1]);
            if (elems.size() > 2 && elems[2] != "")
                cmd.order.data.symbol = elems[2];
            if (elems.size() > 3 && elems[3] != "") {
                if (elems[3] == "Buy")
                    cmd.order.side = OrderAction::BUY;
                else
                    cmd.order.side = OrderAction::SELL;
            }
            if (elems.size() > 4 && elems[4] != "")
                cmd.order.data.quantity = std::stoull(elems[4]);
            if (elems.size() > 5 && elems[5] != "")
                cmd.order.price = std::stod(elems[5]);
        }
        catch (...) {
            std::cout << "error while parsing command" << std::endl;
            return Command();
        }
        return cmd;
    }
}