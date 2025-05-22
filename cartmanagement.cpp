#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Product Class
class Product {
public:
    int id;
    string name;
    double price;
    int quantity;

    Product() : id(0), name(""), price(0.0), quantity(0) {}

    Product(int id, string name, double price, int quantity)
        : id(id), name(name), price(price), quantity(quantity) {}
};

// Coupon Class
class Coupon {
private:
    int id;
    double dis_percentage;
    bool active;

public:
    Coupon() : id(0), dis_percentage(0.0), active(true) {}

    Coupon(int id, double dis_percentage)
        : id(id), dis_percentage(dis_percentage), active(true) {}

    double getDiscountPercentage() const {
        return active ? dis_percentage : 0.0;
    }

    void deactivate() {
        active = false;
    }

    int getId() const { return id; }
    bool isActive() const { return active; }
};

// Inventory Class
class Inventory {
private:
    unordered_map<int, Product> products;
    unordered_map<int, Coupon> coupons;

public:
    void addProduct(Product product) {
        products[product.id] = product;
    }

    void createCoupon(int id, double discountPercentage) {
        coupons[id] = Coupon(id, discountPercentage);
    }

    Coupon* getCoupon(int id) {
        if (coupons.count(id) && coupons[id].isActive())
            return &coupons[id];
        return nullptr;
    }

    bool isAvailable(int productId, int quantity) {
        return products.count(productId) && products[productId].quantity >= quantity;
    }

    Product* getProduct(int productId) {
        if (products.count(productId)) return &products[productId];
        return nullptr;
    }

    void reduceStock(int productId, int quantity) {
        if (isAvailable(productId, quantity)) {
            products[productId].quantity -= quantity;
        }
    }

    void displayProducts() {
        cout << "\nAvailable Products:\n";
        for (auto& it : products) {
            Product& p = it.second;
            cout << "ID: " << p.id << ", Name: " << p.name
                 << ", Price: " << p.price << ", Stock: " << p.quantity << "\n";
        }
    }
};

// CartItem Class
class CartItem {
public:
    Product product;
    int quantity;

    CartItem(Product p, int q) : product(p), quantity(q) {}
};

// ShoppingCart Class
class ShoppingCart {
private:
    vector<CartItem> items;
    double discountPercentage;

public:
    ShoppingCart() : discountPercentage(0.0) {}

    void addItem(Product product, int quantity) {
        items.push_back(CartItem(product, quantity));
    }

    void applyCoupon(Coupon* coupon) {
        if (coupon && coupon->isActive()) {
            discountPercentage = coupon->getDiscountPercentage();
            coupon->deactivate();
            cout << "Coupon applied! Discount: " << discountPercentage << "%\n";
        } else {
            cout << "Invalid or inactive coupon.\n";
        }
    }

    double getTotalPrice() {
        double total = 0;
        for (auto& item : items) {
            total += item.product.price * item.quantity;
        }
        if (discountPercentage > 0) {
            total *= (1.0 - discountPercentage / 100.0);
        }
        return total;
    }

    void displayCart() {
        cout << "\nCart Contents:\n";
        for (auto& item : items) {
            cout << item.product.name << " x " << item.quantity
                 << " = " << item.product.price * item.quantity << "\n";
        }
        cout << "Total after discount: " << getTotalPrice() << "\n";
    }
};

// Main Function - Simulation
int main() {
    Inventory inventory;
    ShoppingCart cart;

    // Add Products
    inventory.addProduct(Product(1, "Laptop", 1000.0, 10));
    inventory.addProduct(Product(2, "Phone", 500.0, 15));
    inventory.addProduct(Product(3, "Headphones", 100.0, 20));

    // Create Coupons
    inventory.createCoupon(101, 10.0);  // 10% off
    inventory.createCoupon(102, 25.0);  // 25% off

    inventory.displayProducts();

    // Add to Cart
    int productId = 1, quantity = 2;
    if (inventory.isAvailable(productId, quantity)) {
        Product* p = inventory.getProduct(productId);
        cart.addItem(*p, quantity);
        inventory.reduceStock(productId, quantity);
    }

    // Apply Coupon
    Coupon* myCoupon = inventory.getCoupon(101);
    cart.applyCoupon(myCoupon);

    // Display Cart and Inventory again
    cart.displayCart();
    inventory.displayProducts();

    return 0;
}
