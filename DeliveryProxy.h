#pragma once
#include "Delivery.h"
#include "Order.h"
#include <iostream>
#include <memory>

class DeliveryProxy : public Delivery {
private:
    
    std::shared_ptr<Delivery> realDelivery_; 
    
    mutable double cachedCost_;
    mutable bool isCacheValid_;

public:
    DeliveryProxy(std::shared_ptr<Delivery> realDelivery)
        : realDelivery_(realDelivery), cachedCost_(0.0), isCacheValid_(false) {}

    bool isAvailable(const Order& order) const override {
        std::cout << "[Proxy LOG] Проверка доступности для заказа ID: " << order.getId() << "\n";
        return realDelivery_->isAvailable(order);
    }

    double getCost(const Order& order) const override {
        std::cout << "[Proxy LOG] Запрос стоимости для заказа ID: " << order.getId() << "\n";
        
    
        if (!realDelivery_->isAvailable(order)) {
            std::cout << "[Proxy LOG] ОШИБКА: Доставка недоступна (превышен вес или зона)!\n";
            return -1.0;
        }

        
        if (isCacheValid_) {
            std::cout << "[Proxy LOG] Возврат из кэша: " << cachedCost_ << "\n";
            return cachedCost_;
        }

        
        std::cout << "[Proxy LOG] Делегирование расчета реальному объекту...\n";
        cachedCost_ = realDelivery_->getCost(order);
        isCacheValid_ = true;
        return cachedCost_;
    }

    
    std::string getEstimatedTime() const override {
        return realDelivery_->getEstimatedTime();
    }
};