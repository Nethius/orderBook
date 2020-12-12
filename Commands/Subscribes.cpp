//
// Created by Astan on 12.12.2020.
//

#include "Subscribes.h"
#include <vector>

std::vector<std::string> bboArray;
std::vector<std::pair<std::string, uint64_t>> vwapArray;

namespace commands {
    bool bboSubscribe(const std::string& symbol)
    {
        if (!bboArray.empty())
            for(const auto& bbo : bboArray)
                if (bbo == symbol)
                    return false;
        bboArray.push_back(symbol);
        return true;
    }

    bool bboUnsubscribe(const std::string& symbol)
    {
        if (bboArray.empty())
            return false;

        for(auto it = bboArray.cbegin(); it != bboArray.cend(); it++)
            if (*it == symbol) {
                bboArray.erase(it);
                return true;
            }
        return false;
    }

    std::vector<std::string>::const_iterator getBboIterBegin()
    {
        return bboArray.cbegin();
    }
    std::vector<std::string>::const_iterator getBboIterEnd()
    {
        return bboArray.cend();
    }

    void vwapSubscribe(std::string symbol, std::string quantity)
    {

    }

    void vwapUnsubscribe(std::string symbol, std::string quantity)
    {

    }
}