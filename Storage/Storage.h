//
// Created by developer_stag on 07.12.2020.
//

#ifndef ORDERBOOK_STORAGE_H
#define ORDERBOOK_STORAGE_H
#define EPSILON 0.00001
#include "string"
#include "vector"
#include "map"
#include "list"
#include <iostream>
#include <algorithm>

struct OrderData {
    uint64_t quantity;
    std::string symbol;
};

enum OrderAction {
    BUY = 0,
    SELL = 1
};

struct Order {
    uint64_t id;
    double price;
    OrderData data;
    OrderAction side;
};

struct Command
{
    std::string commandName;
    Order order;
};

struct comparator
{
    bool operator()(const std::pair<double, std::string> &l, const std::pair<double, std::string> &r) const
    {
        if (std::abs(l.first - r.first) <= EPSILON * std::max(1.0, std::max(std::abs(l.first), std::abs(r.first))))
                return l.second > r.second;
        return l.first < r.first;
    }
};

typedef std::map<uint64_t, Order *> orders_by_id_t;
typedef std::pair<std::pair<double, std::string>, std::vector<Order *>> order_with_key_t;
typedef std::map<std::pair<double, std::string>, std::vector<Order *>, comparator> orders_by_price_t ;

class Storage {
    std::list<Order> orders;

    orders_by_id_t buysSortedById;
    orders_by_price_t buysSortedByPrice;

    orders_by_id_t sellsSortedById;
    orders_by_price_t sellsSortedByPrice;

    void
    updateMaps(orders_by_id_t &sortedById, orders_by_price_t &sortedByPrice,
               Order &order);

    Storage() {};
    ~Storage() {};
    Storage(Storage const&) = delete;
    Storage& operator= (Storage const&) = delete;
public:

    orders_by_price_t::const_reverse_iterator getBuysByPriceBegin();
    orders_by_price_t::const_reverse_iterator getBuysByPriceEnd();

    orders_by_price_t::const_iterator getSellsByPriceBegin();
    orders_by_price_t::const_iterator getSellsByPriceEnd();

    static Storage& instance()
    {
        static Storage storage;
        return storage;
    };

    void getDataForPrint(const order_with_key_t& order, Order& data, size_t& dataVolume, const std::string& pattern);
    bool getDataForPrintFull(const order_with_key_t& order, Order& data, size_t& idInVector);
    bool insertOrder(Order &order);
    bool modifyOrder(Order &order);
//    bool cancelOrder(uint64_t orderId);

    void getBboForSubscribe(const std::string& symbol, double& bid, double& ask);
    void getVwapForSubscribe(const std::string &symbol, const uint64_t& quantity, double &bid, double &ask);
};

#endif //ORDERBOOK_STORAGE_H
