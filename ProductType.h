#pragma once
#include <string>
#include <unordered_map>
#include <memory>

class ProductType {
private:
    std::string category_;
    double baseWeight_;
    double basePrice_;

    static std::unordered_map<std::string, std::shared_ptr<ProductType>> pool_;
    ProductType(const std::string& category, double weight, double price)
        : category_(category), baseWeight_(weight), basePrice_(price) {}

public:
    ProductType(const ProductType&) = delete;
    ProductType& operator=(const ProductType&) = delete;

    static std::shared_ptr<ProductType> getType(const std::string& category) {
        auto it = pool_.find(category);
        if (it != pool_.end()) return it->second;
        
        auto newType = std::shared_ptr<ProductType>(new ProductType(category, 1.0, 100.0));
        pool_[category] = newType;
        return newType;
    }

    std::string getCategory() const { return category_; }
    double getBaseWeight() const { return baseWeight_; }
    double getBasePrice() const { return basePrice_; }
};

inline std::unordered_map<std::string, std::shared_ptr<ProductType>> ProductType::pool_;