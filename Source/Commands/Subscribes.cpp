//
// Created by Astan on 12.12.2020.
//

#include "Subscribes.h"
#include <vector>

std::vector<std::string> bboArray;
std::vector<std::pair<std::string, uint64_t>> vwapArray;

namespace commands {
    bool bboSubscribe(Command&& cmd)
    {
        if (cmd.commandName != "SUBSCRIBE BBO") {
            std::cout << "Wrong command signature: " << cmd.commandName << std::endl;
            return false;
        }
        if (!bboArray.empty())
            for(const auto& bbo : bboArray)
                if (bbo == cmd.order.data.symbol) {
                    std::cout << "Already subscribed" << std::endl;
                    return false;
                }
        bboArray.push_back(cmd.order.data.symbol);
        return true;
    }

    bool bboUnsubscribe(Command&& cmd)
    {
        if (cmd.commandName != "UNSUBSCRIBE BBO") {
            std::cout << "Wrong command signature: " << cmd.commandName << std::endl;
            return false;
        }
        if (bboArray.empty()) {
            std::cout << "Not subscribed" << std::endl;
            return false;
        }

        for(auto it = bboArray.cbegin(); it != bboArray.cend(); it++)
            if (*it == cmd.order.data.symbol) {
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

    bool vwapSubscribe(Command&& cmd)
    {
        if (cmd.commandName != "SUBSCRIBE VWAP") {
            std::cout << "Wrong command signature: " << cmd.commandName << std::endl;
            return false;
        }
        if (!vwapArray.empty())
            for(const auto& vwap : vwapArray)
                if (vwap.first == cmd.order.data.symbol && vwap.second == cmd.order.data.quantity) {
                    std::cout << "Already subscribed" << std::endl;
                    return false;
                }
        vwapArray.emplace_back(std::make_pair(cmd.order.data.symbol, cmd.order.data.quantity));
        return true;
    }

    bool vwapUnsubscribe(Command&& cmd)
    {
        if (cmd.commandName != "UNSUBSCRIBE VWAP") {
            std::cout << "Wrong command signature: " << cmd.commandName << std::endl;
            return false;
        }
        if (vwapArray.empty()) {
            std::cout << "Not subscribed" << std::endl;
            return false;
        }

        for(auto it = vwapArray.cbegin(); it != vwapArray.cend(); it++)
            if (it->first == cmd.order.data.symbol && it->second == cmd.order.data.quantity) {
                vwapArray.erase(it);
                return true;
            }
        std::cout << "Not subscribed" << std::endl;
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