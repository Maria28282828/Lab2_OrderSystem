#pragma once
#include "Discount.h"
#include "Order.h"
#include <iostream>

class PercentDiscount : public Discount {
public:
    void apply(Order& order) override {
        std::cout << "Применена скидка 10% на заказ " << order.getId() << "\n";
    }
};

class CashbackDiscount : public Discount {
public:
    void apply(Order& order) override {
        std::cout << "Начислен кэшбэк 5% за заказ " << order.getId() << "\n";
    }
};

class FreeDeliveryDiscount : public Discount {
public:
    void apply(Order& order) override {
        std::cout << "Доставка для заказа " << order.getId() << " стала бесплатной!\n";
    }
};

class GiftDiscount : public Discount {
public:
    void apply(Order& order) override {
        std::cout << "К заказу " << order.getId() << " добавлен подарок: Кружка!\n";
    }
};