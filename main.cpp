#include <iostream>
#include <memory>
#include <windows.h>
#include "OrderManager.h"
#include "ProductType.h"
#include "Product.h"
#include "DiscountStrategies.h"
#include "DeliveryStrategies.h"
#include "DeliveryProxy.h"
#include <windows.h>

int main() {
   
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
    std::cout << "Лабораторная 2: Система управления заказа\n\n";

    OrderManager manager(5);

    std::cout << "Сценарий 1: Создание заказа и добавление товаров\n";
    auto order1 = manager.createOrder("Макс");

    auto cupType = ProductType::getType("Кружка");
    auto teapotType = ProductType::getType("Чайник");

    auto cup = std::make_shared<Product>(1, 2, 300.0, cupType);
    auto teapot = std::make_shared<Product>(2, 1, 1500.0, teapotType);

    order1->addItem(cup);
    order1->addItem(teapot);

    std::cout << "Заказ создан. Общий вес: " << order1->getTotalWeight() << " кг.\n";
    std::cout << "Общая стоимость: " << order1->getTotalPrice() << " руб.\n\n";

    std::cout << "Сценарий 2: Применение скидки\n";
    auto discount = std::make_shared<PercentDiscount>();
    

    *order1 + discount; 
    
    std::cout << "\n";

    std::cout << "Сценарий 3: Выбор доставки\n";
    auto realCourier = std::make_shared<CourierDelivery>();
    auto proxy = std::make_shared<DeliveryProxy>(realCourier);

   
    proxy << *order1; 

    if (proxy->isAvailable(*order1)) {
        double cost = proxy->getCost(*order1);
        std::cout << "Стоимость доставки: " << cost << " руб.\n";
        std::cout << "Итоговая сумма с доставкой: " << order1->getTotalPrice() + cost << " руб.\n"; 
        std::cout << "Срок доставки: " << proxy->getEstimatedTime() << "\n";
    }
    std::cout << "\n";

    std::cout << "Сценарий 4: Оплата заказа\n";
    std::cout << "Выручка ДО оплаты: " << manager.getTurnover() << " руб.\n";
    
    order1->setStatus(OrderStatus::Paid);
    
    std::cout << "Выручка ПОСЛЕ оплаты: " << manager.getTurnover() << " руб.\n";
    std::cout << "Количество клиентов: " << manager.getCustomerCount() << "\n\n";

    std::cout << *order1 << "\n\n";

    std::cout << "Сценарий 5: Применение нескольких скидок\n";
    auto freeDelivery = std::make_shared<FreeDeliveryDiscount>();
    *order1 + freeDelivery;
    std::cout << "Применена вторая скидка (Бесплатная доставка).\n";
    std::cout << *order1 << "\n\n";

    std::cout << "Сценарий 6: Отмена заказа и проверка лимита\n";
    auto order2 = manager.createOrder("Мария");
    std::cout << "Создан заказ 2 (Мария). Всего активных: 2\n";
    
    order2->setStatus(OrderStatus::Cancelled);
    std::cout << "Заказ 2 отменен.\n";

    try {
        auto order3 = manager.createOrder("Алла");
        std::cout << "Создан заказ 3 (Алла). Лимит не превышен, так как заказ 2 отменен\n";
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
   
    return 0;
}