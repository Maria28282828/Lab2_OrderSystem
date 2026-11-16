#pragma once
#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include "Product.h"
#include "IObservable.h"
#include "OrderStatus.h"
#include "Discount.h"
#include "Delivery.h"

class Order : public IObservable {
private:
    int id_;                                      
    std::string customer_;                        
    std::vector<std::shared_ptr<Product>> items_; 
    OrderStatus status_;                          
    std::shared_ptr<Delivery> delivery_;          
    std::vector<std::shared_ptr<Discount>> discounts_; 

public:
    Order(int id, const std::string& customer)
        : id_(id), customer_(customer), status_(OrderStatus::Pending) {}

    int getId() const { return id_; }
    std::string getCustomer() const { return customer_; }
    OrderStatus getStatus() const { return status_; }
    
    
    const std::vector<std::shared_ptr<Product>>& getItems() const { 
        return items_; 
    }
    
    void addItem(std::shared_ptr<Product> product) {
        items_.push_back(product);
    }

    void removeItem(int productId) {
        for (auto it = items_.begin(); it != items_.end(); ++it) {
            if ((*it)->getId() == productId) {
                items_.erase(it);
                return;
            }
        }
    }

    double getTotalWeight() const {
        double total = 0;
        for (const auto& item : items_) {
            total += item->getWeight();
        }
        return total;
    }

    double getTotalPrice() const {
        double total = 0;
        for (const auto& item : items_) {
            total += item->getTotalPrice();
        }
        return total;
    }

    void setStatus(OrderStatus newStatus) {
        if (status_ != newStatus) { 
            OrderStatus oldStatus = status_;
            status_ = newStatus;    
            
            OrderEvent event(id_, oldStatus, newStatus, 0); 
            notify(event);
        }
    }

    void setDelivery(std::shared_ptr<Delivery> d) { delivery_ = d; }
    
    void applyDiscount(std::shared_ptr<Discount> d) { 
        discounts_.push_back(d); 
        d->apply(*this); 
    }
};


inline Order& operator+(Order& order, const std::shared_ptr<Discount>& discount) {
    order.applyDiscount(discount);
    return order;
}


inline Order& operator<<(const std::shared_ptr<Delivery>& delivery, Order& order) {
    order.setDelivery(delivery);
    return order;
}


inline std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "Заказ ID: " << order.getId() 
       << "  Клиент: " << order.getCustomer() 
       << "  Статус: ";
       
    switch(order.getStatus()) {
        case OrderStatus::Pending: os << "Ожидает оплаты"; break;
        case OrderStatus::Paid: os << "Оплачен"; break;
        case OrderStatus::Shipped: os << "Отправлен"; break;
        case OrderStatus::Delivered: os << "Доставлен"; break;
        case OrderStatus::Cancelled: os << "Отменен"; break;
    }
    os << "  Стоимость: " << order.getTotalPrice() << " руб.";
    return os;
}