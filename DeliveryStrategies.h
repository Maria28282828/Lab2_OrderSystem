#pragma once
#include "Delivery.h"
#include "Order.h"
#include <stdexcept>

class CourierDelivery : public Delivery {
public:
    double getCost(const Order& order) const override {
        return 500.0; 
    }
    std::string getEstimatedTime() const override {
        return "1-2 дня";
    }
    bool isAvailable(const Order& order) const override {
        return order.getTotalWeight() <= 20.0;
    }
};


class PickupDelivery : public Delivery {
public:
    double getCost(const Order& order) const override {
        return 0.0; 
    }
    std::string getEstimatedTime() const override {
        return "2-10 дней ";
    }
    bool isAvailable(const Order& order) const override {
        return true; 
    }
};

class PostDelivery : public Delivery {
public:
    double getCost(const Order& order) const override {
        return 200.0; 
    }
    std::string getEstimatedTime() const override {
        return "10-бесконечость дней";
    }
    bool isAvailable(const Order& order) const override {
        return order.getTotalWeight() <= 10.0;
    }
};