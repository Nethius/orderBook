//
// Created by Astan on 12.12.2020.
//

#ifndef ORDERBOOK_SUBSCRIBES_H
#define ORDERBOOK_SUBSCRIBES_H
#include <string>
#include <vector>

namespace commands {
    bool bboSubscribe(const std::string& symbol);
    bool bboUnsubscribe(const std::string& symbol);
    std::vector<std::string>::const_iterator getBboIterBegin();
    std::vector<std::string>::const_iterator getBboIterEnd();

    bool vwapSubscribe(const std::string& symbol, uint64_t quantity);
    bool vwapUnsubscribe(const std::string& symbol, uint64_t quantity);
    std::vector<std::pair<std::string, uint64_t>>::const_iterator getVwapIterBegin();
    std::vector<std::pair<std::string, uint64_t>>::const_iterator getVwapIterEnd();
}
#endif //ORDERBOOK_SUBSCRIBES_H
