#pragma once
#include <memory>
#include "ProductType.h"

class Product {
private:
    int id_;
    int quantity_;
    double currentPrice_;
    std::shared_ptr<ProductType> type_;

public:
    Product(int id, int quantity, double price, std::shared_ptr<ProductType> type)
        : id_(id), quantity_(quantity), currentPrice_(price), type_(type) {}

    int getId() const { return id_; }
    int getQuantity() const { return quantity_; }
    double getCurrentPrice() const { return currentPrice_; }
    std::shared_ptr<ProductType> getType() const { return type_; }

    double getWeight() const { return type_->getBaseWeight() * quantity_; }
    double getTotalPrice() const { return currentPrice_ * quantity_; }

    void changeQuantity(int newQuantity) {
        if (newQuantity >= 0) quantity_ = newQuantity;
    }
};