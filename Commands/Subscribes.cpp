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

    bool vwapSubscribe(const std::string& symbol, uint64_t quantity)
    {
        if (!vwapArray.empty())
            for(const auto& vwap : vwapArray)
                if (vwap.first == symbol && vwap.second == quantity)
                    return false;
        vwapArray.emplace_back(std::make_pair(symbol, quantity));
        return true;
    }

    bool vwapUnsubscribe(const std::string& symbol, uint64_t quantity)
    {
        if (vwapArray.empty())
            return false;

        for(auto it = vwapArray.cbegin(); it != vwapArray.cend(); it++)
            if (it->first == symbol && it->second == quantity) {
                vwapArray.erase(it);
                return true;
            }
        return false;
    }

    std::vector<std::pair<std::string, uint64_t>>::const_iterator getVwapIterBegin()
    {
        return vwapArray.cbegin();
    }
    std::vector<std::pair<std::string, uint64_t>>::const_iterator getVwapIterEnd()
    {
        return vwapArray.cend();
    }
}