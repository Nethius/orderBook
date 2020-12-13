//
// Created by developer_stag on 08.12.2020.
//

#include <Print.h>
#include <iomanip>
#include <algorithm>
#include <Storage.h>

namespace {
    struct PrintData {
        size_t count = 0;
        Order order = {};
    };

    const size_t MAX_PRINT_ON_SCREEN = 5;
    const size_t PADDING = 15;

    void formatPrint(std::vector<PrintData> &buys, std::vector<PrintData> &sells) {
        for (size_t i = 0; i < std::max(buys.size(), sells.size()); i++) {
            std::cout << std::setw(PADDING) << std::left << ((i < buys.size()) ? std::to_string(buys[i].count) : "");
            std::cout << std::setw(PADDING) << std::left
                      << ((i < buys.size()) ? std::to_string(buys[i].order.data.quantity) : "");
            std::cout << std::setw(PADDING) << std::left
                      << ((i < buys.size()) ? std::to_string(buys[i].order.price) : "");
            std::cout << std::setw(PADDING) << std::left
                      << ((i < sells.size()) ? std::to_string(sells[i].count) : "");
            std::cout << std::setw(PADDING) << std::left
                      << ((i < sells.size()) ? std::to_string(sells[i].order.data.quantity) : "");
            std::cout << std::setw(PADDING) << std::left
                      << ((i < sells.size()) ? std::to_string(sells[i].order.price) : "") << std::endl;
        }
    }

    void printHeader() {
        std::cout << std::setw(PADDING) << std::left << "orders";
        std::cout << std::setw(PADDING) << std::left << "volume";
        std::cout << std::setw(PADDING) << std::left << "bid";

        std::cout << std::setw(PADDING) << std::left << "ask";
        std::cout << std::setw(PADDING) << std::left << "volume";
        std::cout << std::setw(PADDING) << std::left << "orders" << std::endl;
    }
}
namespace view {
    void print(const std::string &symbol) {

        Storage &storage = Storage::instance();

        std::vector<PrintData> buys;
        std::vector<PrintData> sells;
        auto buysIter = storage.getBuysByPriceBegin();
        auto sellsIter = storage.getSellsByPriceBegin();

        printHeader();

        bool shouldPrint = false;

        while (true) {
            size_t buyVolume = 0;
            Order buyData = {};

            if (buysIter != storage.getBuysByPriceEnd()) {
                if (storage.getDataForPrint(order_with_key_t{buysIter->first, buysIter->second}, buyData, buyVolume,
                                            symbol))
                    buys.push_back(PrintData{buyVolume, buyData});
                buysIter = std::next(buysIter);
            }

            size_t sellVolume = 0;
            Order sellData = {};

            if (sellsIter != storage.getSellsByPriceEnd()) {
                if (storage.getDataForPrint(order_with_key_t{sellsIter->first, sellsIter->second}, sellData, sellVolume,
                                            symbol))
                    sells.push_back(PrintData{sellVolume, sellData});
                sellsIter = std::next(sellsIter);
            }

            shouldPrint = (buys.size() == MAX_PRINT_ON_SCREEN && sells.size() == MAX_PRINT_ON_SCREEN) || (
                    buysIter == storage.getBuysByPriceEnd() &&
                    sellsIter == storage.getSellsByPriceEnd());

            if (shouldPrint) {
                formatPrint(buys, sells);
                buys.clear();
                sells.clear();
            }

            if (shouldPrint) {
                while (shouldPrint) {
                    std::cout << "Print ";
                    if (buysIter != storage.getBuysByPriceEnd() ||
                        sellsIter != storage.getSellsByPriceEnd())
                        std::cout << "'1' to see next page or ";
                    std::cout << "'0' to return to the menu" << std::endl;

                    std::string s;
                    std::getline(std::cin, s);
                    switch (std::stoi(s)) { //TODO exception
                        case 0:
                            return;
                        case 1: {
                            if (buysIter != storage.getBuysByPriceEnd() ||
                                sellsIter != storage.getSellsByPriceEnd()) {
                                shouldPrint = false;
                                //TODO clear screen
                                printHeader();
                                break;
                            }
                        }
                        default:
                            std::cout << "Erroneous input" << std::endl;
                    }
                }
            }
        }
    }
}