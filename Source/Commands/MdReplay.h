//
// Created by Astan on 13.12.2020.
//

#ifndef ORDERBOOK_MDREPLAY_H
#define ORDERBOOK_MDREPLAY_H
#include <string>
namespace commands {
    void execCommandsFromFile(std::string path, std::string symbol = "");
}
#endif //ORDERBOOK_MDREPLAY_H
