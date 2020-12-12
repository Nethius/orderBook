//
// Created by developer_stag on 07.12.2020.
//

#include "Storage.h"
#include <utility>

void Storage::updateMaps(orders_by_id_t &sortedById, orders_by_price_t &sortedByPrice, Command &cmd)
{
    sortedById.insert(std::make_pair(cmd.order.id, &orders.back()));

    std::vector<Order*> pOrders;
    if (!sortedByPrice.empty()) {
        auto i = sortedByPrice.find(std::make_pair(cmd.order.price, cmd.order.data.symbol));
        if (i != sortedByPrice.end()) {
            pOrders = i->second;
        }
    }
    pOrders.push_back(&orders.back());
    sortedByPrice.insert_or_assign(std::make_pair(cmd.order.price, cmd.order.data.symbol), std::move(pOrders));
}
bool Storage::insertOrder(Command &cmd)
{
    if (!buysSortedById.empty() && buysSortedById.find(cmd.order.id) != buysSortedById.end() ||
        !sellsSortedById.empty() && sellsSortedById.find(cmd.order.id) != sellsSortedById.end()){
        std::cout << "already has order with given order id" << std::endl;
        return false;
    }
    try {
        orders.push_back(cmd.order);
        if (cmd.order.side == OrderAction::BUY)
            updateMaps(buysSortedById, buysSortedByPrice, cmd);
        else
            updateMaps(sellsSortedById, sellsSortedByPrice, cmd);
    }
    catch (...)
    {
        std::cout << "error while insert new order" << std::endl;
        return false;
    }
    return true;
}

orders_by_price_t::const_reverse_iterator Storage::getBuysByPriceBegin()
{
    return buysSortedByPrice.crbegin();
}

orders_by_price_t::const_reverse_iterator Storage::getBuysByPriceEnd()
{
    return buysSortedByPrice.crend();
}

orders_by_price_t::const_iterator Storage::getSellsByPriceBegin()
{
    return sellsSortedByPrice.cbegin();
}

orders_by_price_t::const_iterator Storage::getSellsByPriceEnd()
{
    return sellsSortedByPrice.cend();
}

void Storage::getDataForPrint(const order_with_key_t& order, Order& data, size_t& dataVolume, const std::string& pattern) {
    if (order.second.front()->data.symbol == pattern) {
        data.data.symbol = order.second.front()->data.symbol;
        data.price = order.first.first;
        if (order.second.size() > 1) {
            for (auto i : order.second) {
                dataVolume++;
                data.data.quantity += i->data.quantity;
            }
        } else {
            dataVolume = 1;
            data.data.quantity = order.second.front()->data.quantity;
        }
    }
}

bool Storage::getDataForPrintFull(const order_with_key_t& order, Order& data, size_t& ordersLeft) {
        if (ordersLeft < order.second.size()) {
            data.data.symbol = order.second[ordersLeft]->data.symbol;
            data.data.quantity = order.second[ordersLeft]->data.quantity;
            data.price = order.second[ordersLeft]->price;
            data.id = order.second[ordersLeft]->id;
            return true;
        }
    return false;
}
