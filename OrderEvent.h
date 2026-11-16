#pragma once
#include "OrderStatus.h" 

class OrderEvent {
public:
    int orderId;           
    OrderStatus oldStatus; 
    OrderStatus newStatus; 
    long long timestamp;   

    OrderEvent(int id, OrderStatus oldS, OrderStatus newS, long long time)
        : orderId(id), oldStatus(oldS), newStatus(newS), timestamp(time) {}
};