#pragma once
#include <vector>
#include <memory>
#include <string>
#include <set>
#include "Order.h"
#include "IObserver.h"

class OrderManager : public IObserver {
private:
    std::vector<std::shared_ptr<Order>> orders_; 
    std::set<std::string> customers_;            
    double turnover_;                            
    int maxActiveOrders_;                        
    int nextOrderId_;                            

public:
    OrderManager(int maxActiveOrders) 
        : turnover_(0.0), maxActiveOrders_(maxActiveOrders), nextOrderId_(1) {}

    std::shared_ptr<Order> createOrder(const std::string& customer) {
        
        int activeCount = 0;
        for (const auto& order : orders_) {
            if (order->getStatus() != OrderStatus::Delivered && 
                order->getStatus() != OrderStatus::Cancelled) {
                activeCount++;
            }
        }

        if (activeCount >= maxActiveOrders_) {
            throw std::runtime_error("Достигнут лимит активных заказов!");
        }

       
        auto newOrder = std::make_shared<Order>(nextOrderId_++, customer);
        
        
        orders_.push_back(newOrder);
        customers_.insert(customer); 

        newOrder->subscribe(this);

        return newOrder;
    }


    double getTurnover() const { return turnover_; }
    int getCustomerCount() const { return customers_.size(); }



    void onOrderEvent(const OrderEvent& event) override {
        if (event.newStatus == OrderStatus::Paid && event.oldStatus != OrderStatus::Paid) {
            for (const auto& order : orders_) {
                if (order->getId() == event.orderId) {
                    turnover_ += order->getTotalPrice();
                    break;
                }
            }
        }
    
        else if (event.newStatus == OrderStatus::Cancelled && event.oldStatus == OrderStatus::Paid) {
            for (const auto& order : orders_) {
                if (order->getId() == event.orderId) {
                    turnover_ -= order->getTotalPrice();
                    break;
                }
            }
        }
    }
};