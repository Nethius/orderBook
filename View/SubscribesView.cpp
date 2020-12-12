//
// Created by Astan on 12.12.2020.
//

#include "SubscribesView.h"
#include <Storage.h>
#include <Subscribes.h>
#include <iomanip>

namespace view {
    void printSubscribes()
    {
        Storage &storage = Storage::instance();

        auto bboIter = commands::getBboIterBegin();
        double bid = 0;
        double ask = 0;
// чето вывожу в обратном порядке
        while (bboIter != commands::getBboIterEnd()) {
            storage.getBboForPrint(*bboIter, bid, ask);
            std::cout << *bboIter;
            std::cout << " bid = " << ((bid == 0) ? "-" : std::to_string(bid));
            std::cout << " ask = " << ((bid == 0) ? "-" : std::to_string(ask)) << std::endl;
            bboIter = std::next(bboIter);
        }
    }
}