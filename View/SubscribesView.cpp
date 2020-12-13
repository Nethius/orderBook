//
// Created by Astan on 12.12.2020.
//

#include "SubscribesView.h"
#include <Storage/Storage.h>
#include <Commands/Subscribes.h>
#include <iomanip>

namespace view {
    void printSubscribes(std::string symbol)
    {
        Storage &storage = Storage::instance();

        auto bboIter = commands::getBboIterBegin();
        while (bboIter != commands::getBboIterEnd()) {
            if (symbol.empty() ? true : *bboIter == symbol) {
                double bid = 0;
                double ask = 0;
                storage.getBboForSubscribe(*bboIter, bid, ask);
                std::cout << *bboIter;
                std::cout << " bid = " << ((bid == 0) ? "-" : std::to_string(bid));
                std::cout << " ask = " << ((ask == 0) ? "-" : std::to_string(ask)) << std::endl;
            }
            bboIter = std::next(bboIter);
        }

        auto vwapIter = commands::getVwapIterBegin();
        while (vwapIter != commands::getVwapIterEnd()) {
            if (symbol.empty() ? true : vwapIter->first == symbol) {
                double bid = 0;
                double ask = 0;
                storage.getVwapForSubscribe(vwapIter->first, vwapIter->second, bid, ask);
                std::cout << vwapIter->first << " VWAP for given quantity (" << vwapIter->second << ")";
                std::cout << "<" << ((bid == 0) ? "nil" : std::to_string(bid));
                std::cout << ", " << ((ask == 0) ? "nil" : std::to_string(ask)) << ">" << std::endl;
            }
            vwapIter = std::next(vwapIter);
        }
    }
}