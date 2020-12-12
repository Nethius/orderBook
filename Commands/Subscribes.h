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
}
#endif //ORDERBOOK_SUBSCRIBES_H
