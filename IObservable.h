#pragma once
#include <vector>
#include "IObserver.h"

class IObservable {
protected:
    std::vector<IObserver*> observers_; 

public:
    virtual ~IObservable() = default;

    void subscribe(IObserver* observer) {
        observers_.push_back(observer);
    }

    void unsubscribe(IObserver* observer) {
        for (auto it = observers_.begin(); it != observers_.end(); ++it) {
            if (*it == observer) {
                observers_.erase(it); 
                break;
            }
        }
    }

    void notify(const OrderEvent& event) {
        for (IObserver* observer : observers_) {
            observer->onOrderEvent(event);
        }
    }
};