//
// Created by developer_stag on 07.12.2020.
//

#include "Storage.h"
#include <utility>

void Storage::updateMaps(orders_by_id_t &sortedById, orders_by_price_t &sortedByPrice, Order &order) {
    sortedById.insert(std::make_pair(order.id, &orders.back()));

    std::vector<Order *> pOrders;
    if (!sortedByPrice.empty()) {
        auto i = sortedByPrice.find(std::make_pair(order.price, order.data.symbol));
        if (i != sortedByPrice.end()) {
            pOrders = i->second;
        }
    }
    pOrders.push_back(&orders.back());
    sortedByPrice.insert_or_assign(std::make_pair(order.price, order.data.symbol), std::move(pOrders));
}

bool Storage::insertOrder(Order &order) {
    if (!buysSortedById.empty() && buysSortedById.find(order.id) != buysSortedById.end() ||
        !sellsSortedById.empty() && sellsSortedById.find(order.id) != sellsSortedById.end()) {
        std::cout << "already has order with given order id" << std::endl;
        return false;
    }
    try {
        orders.push_back(order);
        if (order.side == OrderAction::BUY)
            updateMaps(buysSortedById, buysSortedByPrice, order);
        else
            updateMaps(sellsSortedById, sellsSortedByPrice, order);
    }
    catch (...) {
        std::cout << "error while insert new order" << std::endl;
        return false;
    }
    return true;
}

bool Storage::modifyOrder(Order &order)
{
    auto modify{
            [&order](orders_by_id_t &ordersById,
                     orders_by_price_t &ordersByPrice) {
                auto itById = ordersById.find(order.id);
                if (itById == ordersById.cend())
                    return false;
                auto mapNode = ordersByPrice.extract(std::make_pair(itById->second->price, itById->second->data.symbol));
                mapNode.key() = std::make_pair(order.price, itById->second->data.symbol);
                ordersByPrice.insert(std::move(mapNode));
                itById->second->data.quantity = order.data.quantity;
                itById->second->price = order.price;
                return true;
            }
    };
    if (!modify(buysSortedById, buysSortedByPrice) && !modify(sellsSortedById, sellsSortedByPrice))
        return false;
    return true;
}

bool Storage::cancelOrder(uint64_t orderId)
{
    auto cancel{
            [&orderId, this](orders_by_id_t &ordersById,
                     orders_by_price_t &ordersByPrice) {
                auto itById = ordersById.find(orderId);
                if (itById == ordersById.cend())
                    return false;

                auto itByPrice = ordersByPrice.find(std::make_pair(itById->second->price, itById->second->data.symbol));
                ordersByPrice.erase(itByPrice);
                ordersById.erase(itById);
                auto it = std::find_if( orders.begin(),
                                        orders.end(),
                                        [orderId]( const Order& order ){ return order.id == orderId; } );
                orders.erase(it);
                return true;
            }
    };

    if (!cancel(buysSortedById, buysSortedByPrice) && !cancel(sellsSortedById, sellsSortedByPrice))
        return false;
    return true;
}

orders_by_price_t::const_reverse_iterator Storage::getBuysByPriceBegin() {
    return buysSortedByPrice.crbegin();
}

orders_by_price_t::const_reverse_iterator Storage::getBuysByPriceEnd() {
    return buysSortedByPrice.crend();
}

orders_by_price_t::const_iterator Storage::getSellsByPriceBegin() {
    return sellsSortedByPrice.cbegin();
}

orders_by_price_t::const_iterator Storage::getSellsByPriceEnd() {
    return sellsSortedByPrice.cend();
}

void
Storage::getDataForPrint(const order_with_key_t &order, Order &data, size_t &dataVolume, const std::string &pattern) {
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

bool Storage::getDataForPrintFull(const order_with_key_t &order, Order &data, size_t &idInVector) {
    if (idInVector < order.second.size()) {
        data.data.symbol = order.second[idInVector]->data.symbol;
        data.data.quantity = order.second[idInVector]->data.quantity;
        data.price = order.second[idInVector]->price;
        data.id = order.second[idInVector]->id;
        return true;
    }
    return false;
}

void Storage::getBboForSubscribe(const std::string &symbol, double &bid, double &ask) {
    auto buyIter = buysSortedByPrice.crbegin();
    while (buyIter != buysSortedByPrice.crend()) {
        if (buyIter->first.second == symbol) {
            bid = buyIter->second.front()->price;
            break;
        }
        buyIter = std::next(buyIter);
    }

    auto sellIter = sellsSortedByPrice.cbegin();
    while (sellIter != sellsSortedByPrice.cend()) {
        if (sellIter->first.second == symbol) {
            ask = sellIter->second.front()->price;
            break;
        }
        sellIter = std::next(sellIter);
    }
}

void Storage::getVwapForSubscribe(const std::string &symbol, const uint64_t &quantity, double &bid, double &ask) {
    auto getVwap{
            [symbol, quantity](std::vector<std::pair<double, uint64_t>> &vwap, const order_with_key_t &order,
                               uint64_t &tempQuantity) {
                if (order.first.second == symbol) {
                    if (order.second.front()->data.quantity < tempQuantity) {
                        vwap.emplace_back(order.second.front()->price, order.second.front()->data.quantity);
                        tempQuantity -= order.second.front()->data.quantity;
                        return false;
                    } else {
                        vwap.emplace_back(order.second.front()->price, tempQuantity);
                        return true;
                    }
                }
                return false;
            }
    };

    auto calcVwap{
            [quantity](std::vector<std::pair<double, uint64_t>> &vwap,
                       double &value) {
                uint64_t tempQuantity = 0;
                for (auto i : vwap) {
                    value += i.first * i.second;
                    tempQuantity += i.second;
                }
                value = (tempQuantity < quantity) ? NULL : value / tempQuantity;
            }
    };

    std::vector<std::pair<double, uint64_t>> vwap;
    uint64_t tempQuantity = quantity;
    auto buyIter = buysSortedByPrice.crbegin();

    while (buyIter != buysSortedByPrice.crend()) {
        if (getVwap(vwap, order_with_key_t{buyIter->first, buyIter->second}, tempQuantity))
            break;
        buyIter = std::next(buyIter);
    }
    calcVwap(vwap, bid);

    vwap.clear();
    tempQuantity = quantity;
    auto sellIter = sellsSortedByPrice.cbegin();

    while (sellIter != sellsSortedByPrice.cend()) {
        if (getVwap(vwap, order_with_key_t{sellIter->first, sellIter->second}, tempQuantity))
            break;
        sellIter = std::next(sellIter);
    }
    calcVwap(vwap, ask);
}