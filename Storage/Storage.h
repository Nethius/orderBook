//
// Created by developer_stag on 07.12.2020.
//

#ifndef ORDERBOOK_STORAGE_H
#define ORDERBOOK_STORAGE_H
#include "string"
#include "vector"
#include "map"
#include "list"
#include <iostream>
#include <CommandsParser.h>

struct OrderData
{
    uint64_t quantity;
    std::string symbol;
};

enum OrderAction
{
    BUY = 0,
    SELL = 1
};

struct Order
{
    uint64_t id;
    double price;
    OrderData data;
    OrderAction side;
};

class Storage
{
    std::list<Order> orders;

    std::map<uint64_t, OrderData*> buysSortedById;
    std::map<double, std::vector<OrderData*>> buysSortedByPrice;

    std::map<uint64_t, OrderData*> sellsSortedById;
    std::map<double, std::vector<OrderData*>> sellsSortedByPrice;

    void updateMaps(std::map<uint64_t, OrderData*> &sortedById, std::map<double, std::vector<OrderData*>> &sortedByPrice, Command &cmd);
public:

    auto getBuysByPriceIterator();
    bool insertOrder(Command &cmd);
    size_t getOrdersCount();
    size_t getOrderCount(const std::string& symbol);


};
size_t print(const std::string& symbol, uint64_t& price, Order& order);
#endif //ORDERBOOK_STORAGE_H
