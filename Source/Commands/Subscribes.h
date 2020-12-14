//
// Created by Astan on 12.12.2020.
//

#ifndef ORDERBOOK_SUBSCRIBES_H
#define ORDERBOOK_SUBSCRIBES_H
#include <string>
#include <vector>
#include <Storage/Storage.h>

namespace commands {
    bool bboSubscribe(Command&& cmd);
    bool bboUnsubscribe(Command&& cmd);
    std::vector<std::string>::const_iterator getBboIterBegin();
    std::vector<std::string>::const_iterator getBboIterEnd();

    bool vwapSubscribe(Command&& cmd);
    bool vwapUnsubscribe(Command&& cmd);
    std::vector<std::pair<std::string, uint64_t>>::const_iterator getVwapIterBegin();
    std::vector<std::pair<std::string, uint64_t>>::const_iterator getVwapIterEnd();
}
#endif //ORDERBOOK_SUBSCRIBES_H
