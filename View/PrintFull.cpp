//
// Created by Astan on 12.12.2020.
//

#include "PrintFull.h"
#include <iomanip>
#include <algorithm>
#include <Storage.h>

namespace {
    const size_t MAX_PRINT_ON_SCREEN = 5;
    const size_t PADDING = 15;

    void formatPrint(std::vector<Order> &buys, std::vector<Order> &sells) {
        for (size_t i = 0; i < std::max(buys.size(), sells.size()); i++) {
            std::cout << std::setw(PADDING) << std::left << ((i < buys.size()) ? std::to_string(buys[i].id) : "");
            std::cout << std::setw(PADDING) << std::left << ((i < buys.size()) ? buys[i].data.symbol : "");
            std::cout << std::setw(PADDING) << std::left
                      << ((i < buys.size()) ? std::to_string(buys[i].data.quantity) : "");
            std::cout << std::setw(PADDING) << std::left << ((i < buys.size()) ? std::to_string(buys[i].price) : "");

            std::cout << std::setw(PADDING) << std::left << ((i < sells.size()) ? std::to_string(sells[i].price) : "");
            std::cout << std::setw(PADDING) << std::left
                      << ((i < sells.size()) ? std::to_string(sells[i].data.quantity) : "");
            std::cout << std::setw(PADDING) << std::left << ((i < sells.size()) ? sells[i].data.symbol : "");
            std::cout << std::setw(PADDING) << std::left << ((i < sells.size()) ? std::to_string(sells[i].id) : "") << std::endl;
        }
    }

    void printHeader() {
        std::cout << std::setw(PADDING) << std::left << "id";
        std::cout << std::setw(PADDING) << std::left << "symbol";
        std::cout << std::setw(PADDING) << std::left << "quantity";
        std::cout << std::setw(PADDING) << std::left << "bid";

        std::cout << std::setw(PADDING) << std::left << "ask";
        std::cout << std::setw(PADDING) << std::left << "quantity";
        std::cout << std::setw(PADDING) << std::left << "symbol";
        std::cout << std::setw(PADDING) << std::left << "id" << std::endl;
    }
}

namespace view {
    void printFull() {
        Storage &storage = Storage::instance();

        std::vector<Order> buys;
        std::vector<Order> sells;
        auto buysIter = storage.getBuysByPriceBegin();
        auto sellsIter = storage.getSellsByPriceBegin();

        printHeader();

        bool shouldPrint = false;

        size_t buysIdInVector = 0;
        size_t sellsIdInVector = 0;
        while (true) {

            Order buyData = {};
        //TODO вынести в отдельную функцию
            if (buysIter != storage.getBuysByPriceEnd()) {
                if (buys.size() < MAX_PRINT_ON_SCREEN) {
                    if (storage.getDataForPrintFull(order_with_key_t{buysIter->first, buysIter->second}, buyData,
                                                    buysIdInVector)) {
                        buysIdInVector++;
                        buys.push_back(buyData);
                    } else {
                        buysIdInVector = 0;
                        buysIter = std::next(buysIter);
                    }
                }
            }

            Order sellData = {};

            if (sellsIter != storage.getSellsByPriceEnd()) {
                if (sells.size() < MAX_PRINT_ON_SCREEN) {
                    if (storage.getDataForPrintFull(order_with_key_t{sellsIter->first, sellsIter->second}, sellData,
                                                    sellsIdInVector)) {
                        sellsIdInVector++;
                        sells.push_back(sellData);
                    } else {
                        sellsIdInVector = 0;
                        sellsIter = std::next(sellsIter);
                    }
                }
            }

            shouldPrint = (buys.size() == MAX_PRINT_ON_SCREEN && sells.size() == MAX_PRINT_ON_SCREEN) || (buysIter == storage.getBuysByPriceEnd() &&
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
                    switch (std::stoi(s)) {
                        case 0:
                            return;
                        case 1: {
                            shouldPrint = false;
                            //TODO clear screen
                            printHeader();
                            break;
                        }
                        default:
                            std::cout << "Erroneous input" << std::endl;
                    }
                }
            }
        }
    }
}