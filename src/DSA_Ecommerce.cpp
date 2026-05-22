#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// ==================== DATA STRUCTURES USED ====================
// 1. Linked List - Shopping Cart Management
// 2. Stack - Order History (LIFO)
// 3. Queue - Wishlist / Notifications (FIFO)
// 4. Hash Table - Product Catalog (O(1) Search)
// 5. Binary Search Tree - Price Sorted Products

// ==================== PRODUCT STRUCT ====================
struct Product {
    int id;
    char name[50];
    char category[30];
    double price;
    int stock;
    
    Product() : id(0), price(0), stock(0) {
        name[0] = '\0';
        category[0] = '\0';
    }
    
    Product(int i, const char* n, const char* cat, double p, int s) {
        id = i;
        strcpy(name, n);
        strcpy(category, cat);
        price = p;
        stock = s;
    }
    
    void display() const {
        cout << "ID: " << id << " | " << name << " | " << category 
             << " | $" << price << " | Stock: " << stock << endl;
    }
};

// ==================== 1. HASH TABLE (Product Catalog) ====================
const int TABLE_SIZE = 100;

struct HashNode {
    Product product;
    HashNode* next;
    bool isEmpty;
    
    HashNode() : next(nullptr), isEmpty(true) {}
};

class ProductCatalog {
private:
    HashNode* table[TABLE_SIZE];
    
    int hashFunction(int id) {
        return id % TABLE_SIZE;
    }
    
    void saveToFile() {
        ofstream file("products_dsa.txt");
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!table[i]->isEmpty) {
                file << table[i]->product.id << ","
                     << table[i]->product.name << ","
                     << table[i]->product.category << ","
                     << table[i]->product.price << ","
                     << table[i]->product.stock << endl;
                
                HashNode* temp = table[i]->next;
                while (temp != nullptr) {
                    file << temp->product.id << ","
                         << temp->product.name << ","
                         << temp->product.category << ","
                         << temp->product.price << ","
                         << temp->product.stock << endl;
                    temp = temp->next;
                }
            }
        }
        file.close();
    }
    
    void createDefaultProducts() {
        // Electronics
        insert(Product(1, "Gaming Laptop", "Electronics", 1200.00, 10));
        insert(Product(2, "Wireless Mouse", "Electronics", 25.00, 50));
        insert(Product(3, "Mechanical Keyboard", "Electronics", 75.00, 30));
        insert(Product(4, "4K Monitor", "Electronics", 350.00, 20));
        insert(Product(5, "VR Headset", "Electronics", 430.00, 5));
        
        // Books
        insert(Product(6, "Fiction Novel", "Books", 15.99, 100));
        insert(Product(7, "History Book", "Books", 22.50, 60));
        insert(Product(8, "Cooking Guide", "Books", 18.00, 80));
        insert(Product(9, "Science Textbook", "Books", 45.00, 40));
        
        // Furniture
        insert(Product(10, "Office Chair", "Furniture", 150.00, 15));
        insert(Product(11, "Wooden Table", "Furniture", 300.00, 7));
        insert(Product(12, "Bookshelf", "Furniture", 85.00, 20));
        
        // Beauty
        insert(Product(13, "Lipstick Set", "Beauty", 29.99, 40));
        insert(Product(14, "Face Cream", "Beauty", 35.00, 25));
        insert(Product(15, "Perfume", "Beauty", 60.00, 15));
        
        // Grocery
        insert(Product(16, "Organic Apples", "Grocery", 4.50, 100));
        insert(Product(17, "Milk 1L", "Grocery", 2.00, 100));
        insert(Product(18, "Brown Bread", "Grocery", 3.00, 80));
        insert(Product(19, "Rice 1kg", "Grocery", 1.50, 90));
        insert(Product(20, "Eggs 12pcs", "Grocery", 2.50, 75));
        
        saveToFile();
    }
    
public:
    ProductCatalog() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = new HashNode();
        }
        loadFromFile();
    }
    
    ~ProductCatalog() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    
    void loadFromFile() {
        ifstream file("products_dsa.txt");
        if (!file) {
            createDefaultProducts();
            return;
        }
        
        int id, stock;
        char name[50], category[30];
        double price;
        char comma;
        
        while (file >> id >> comma) {
            file.getline(name, 50, ',');
            file.getline(category, 30, ',');
            file >> price >> comma >> stock;
            file.ignore();
            insert(Product(id, name, category, price, stock));
        }
        file.close();
    }
    
    void insert(Product p) {
        int index = hashFunction(p.id);
        
        if (table[index]->isEmpty) {
            table[index]->product = p;
            table[index]->isEmpty = false;
        } else {
            HashNode* newNode = new HashNode();
            newNode->product = p;
            newNode->isEmpty = false;
            newNode->next = table[index]->next;
            table[index]->next = newNode;
        }
    }
    
    Product* search(int id) {
        int index = hashFunction(id);
        HashNode* temp = table[index];
        
        while (temp != nullptr && !temp->isEmpty) {
            if (temp->product.id == id) {
                return &(temp->product);
            }
            temp = temp->next;
        }
        return nullptr;
    }
    
    void updateStock(int id, int newStock) {
        Product* p = search(id);
        if (p != nullptr) {
            p->stock = newStock;
            saveToFile();
        }
    }
    
    void displayAll() {
        cout << "\n========== PRODUCT CATALOG ==========\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!table[i]->isEmpty) {
                table[i]->product.display();
                
                HashNode* temp = table[i]->next;
                while (temp != nullptr) {
                    temp->product.display();
                    temp = temp->next;
                }
            }
        }
    }
    
    void displayByCategory(const char* category) {
        cout << "\n========== " << category << " ==========\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!table[i]->isEmpty && strcmp(table[i]->product.category, category) == 0) {
                table[i]->product.display();
            }
            HashNode* temp = table[i]->next;
            while (temp != nullptr) {
                if (strcmp(temp->product.category, category) == 0) {
                    temp->product.display();
                }
                temp = temp->next;
            }
        }
    }
};

// ==================== 2. LINKED LIST (Shopping Cart) ====================
struct CartItem {
    Product product;
    int quantity;
    CartItem* next;
    
    CartItem(Product p, int qty) : product(p), quantity(qty), next(nullptr) {}
};

class ShoppingCart {
private:
    CartItem* head;
    double total;
    
    void calculateTotal() {
        total = 0;
        CartItem* temp = head;
        while (temp != nullptr) {
            total += temp->product.price * temp->quantity;
            temp = temp->next;
        }
    }
    
public:
    ShoppingCart() : head(nullptr), total(0) {}
    
    ~ShoppingCart() {
        while (head != nullptr) {
            CartItem* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    void addItem(Product p, int quantity, ProductCatalog& catalog) {
        if (quantity > p.stock) {
            cout << "Only " << p.stock << " left in stock!\n";
            return;
        }
        
        CartItem* current = head;
        while (current != nullptr) {
            if (current->product.id == p.id) {
                current->quantity += quantity;
                calculateTotal();
                cout << "Updated quantity in cart!\n";
                return;
            }
            current = current->next;
        }
        
        CartItem* newItem = new CartItem(p, quantity);
        newItem->next = head;
        head = newItem;
        
        p.stock -= quantity;
        catalog.updateStock(p.id, p.stock);
        
        calculateTotal();
        cout << "Added to cart: " << p.name << " x" << quantity << endl;
    }
    
    void removeItem(int productId) {
        CartItem* temp = head;
        CartItem* prev = nullptr;
        
        while (temp != nullptr && temp->product.id != productId) {
            prev = temp;
            temp = temp->next;
        }
        
        if (temp == nullptr) {
            cout << "Product not found in cart!\n";
            return;
        }
        
        if (prev == nullptr) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        
        delete temp;
        calculateTotal();
        cout << "Removed from cart!\n";
    }
    
    void viewCart() {
        if (head == nullptr) {
            cout << "Cart is empty!\n";
            return;
        }
        
        cout << "\n========== SHOPPING CART ==========\n";
        CartItem* temp = head;
        while (temp != nullptr) {
            cout << temp->product.name << " x" << temp->quantity
                 << " = $" << temp->product.price * temp->quantity << endl;
            temp = temp->next;
        }
        cout << "Total: $" << total << endl;
    }
    
    double getTotal() { return total; }
    bool isEmpty() { return head == nullptr; }
    
    void clear() {
        while (head != nullptr) {
            CartItem* temp = head;
            head = head->next;
            delete temp;
        }
        total = 0;
    }
};

// ==================== 3. STACK (Order History) ====================
struct Order {
    int orderId;
    double amount;
    char date[20];
    int itemCount;
    
    Order() : orderId(0), amount(0), itemCount(0) {
        date[0] = '\0';
    }
    
    Order(int id, double amt, const char* d, int count) 
        : orderId(id), amount(amt), itemCount(count) {
        strcpy(date, d);
    }
};

class OrderHistory {
private:
    Order orders[50];
    int top;
    static int nextOrderId;
    
public:
    OrderHistory() : top(-1) {}
    
    void addOrder(double amount, int itemCount) {
        if (top >= 49) {
            cout << "Order history full!\n";
            return;
        }
        
        nextOrderId++;
        Order newOrder(nextOrderId, amount, "2025-05-22", itemCount);
        orders[++top] = newOrder;
        cout << "Order #" << nextOrderId << " saved to history!\n";
    }
    
    void viewHistory() {
        if (top == -1) {
            cout << "No order history!\n";
            return;
        }
        
        cout << "\n========== ORDER HISTORY (Recent First) ==========\n";
        for (int i = top; i >= 0; i--) {
            cout << "Order #" << orders[i].orderId 
                 << " | $" << orders[i].amount 
                 << " | " << orders[i].date
                 << " | Items: " << orders[i].itemCount << endl;
        }
    }
    
    Order* getLastOrder() {
        if (top == -1) return nullptr;
        return &orders[top];
    }
};

int OrderHistory::nextOrderId = 1000;

// ==================== 4. QUEUE (Wishlist) ====================
struct WishItem {
    int productId;
    char productName[50];
    WishItem* next;
    
    WishItem(int id, const char* name) : productId(id), next(nullptr) {
        strcpy(productName, name);
    }
};

class WishlistQueue {
private:
    WishItem* front;
    WishItem* rear;
    
public:
    WishlistQueue() : front(nullptr), rear(nullptr) {}
    
    ~WishlistQueue() {
        while (front != nullptr) {
            WishItem* temp = front;
            front = front->next;
            delete temp;
        }
    }
    
    void addToWishlist(int id, const char* name) {
        WishItem* newItem = new WishItem(id, name);
        
        if (rear == nullptr) {
            front = rear = newItem;
        } else {
            rear->next = newItem;
            rear = newItem;
        }
        cout << "Added to wishlist: " << name << endl;
    }
    
    void processNotifications() {
        if (front == nullptr) {
            cout << "No wishlist items!\n";
            return;
        }
        
        cout << "\n========== PRICE DROP NOTIFICATIONS ==========\n";
        while (front != nullptr) {
            cout << "?? " << front->productName << " is on sale!\n";
            WishItem* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
    
    void viewWishlist() {
        if (front == nullptr) {
            cout << "Wishlist is empty!\n";
            return;
        }
        
        cout << "\n========== YOUR WISHLIST ==========\n";
        WishItem* temp = front;
        while (temp != nullptr) {
            cout << "?? " << temp->productName << endl;
            temp = temp->next;
        }
    }
    
    bool isEmpty() { return front == nullptr; }
};

// ==================== 5. BINARY SEARCH TREE (Price Search) ====================
struct BSTNode {
    Product product;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(Product p) : product(p), left(nullptr), right(nullptr) {}
};

class PriceBST {
private:
    BSTNode* root;
    
    BSTNode* insert(BSTNode* node, Product p) {
        if (node == nullptr) {
            return new BSTNode(p);
        }
        
        if (p.price < node->product.price) {
            node->left = insert(node->left, p);
        } else if (p.price > node->product.price) {
            node->right = insert(node->right, p);
        }
        return node;
    }
    
    void inorder(BSTNode* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << "$" << node->product.price << " - " 
                 << node->product.name << " (" << node->product.category << ")\n";
            inorder(node->right);
        }
    }
    
    void rangeQuery(BSTNode* node, double min, double max) {
        if (node != nullptr) {
            if (node->product.price >= min) {
                rangeQuery(node->left, min, max);
            }
            if (node->product.price >= min && node->product.price <= max) {
                cout << "$" << node->product.price << " - " 
                     << node->product.name << endl;
            }
            if (node->product.price <= max) {
                rangeQuery(node->right, min, max);
            }
        }
    }
    
    void destroy(BSTNode* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
    
public:
    PriceBST() : root(nullptr) {}
    
    ~PriceBST() {
        destroy(root);
    }
    
    void addProduct(Product p) {
        root = insert(root, p);
    }
    
    void displayByPrice() {
        cout << "\n========== PRODUCTS SORTED BY PRICE ==========\n";
        inorder(root);
    }
    
    void searchByPriceRange(double min, double max) {
        cout << "\n========== PRODUCTS BETWEEN $" << min << " - $" << max << " ==========\n";
        rangeQuery(root, min, max);
    }
};

// ==================== MAIN APPLICATION ====================
int main() {
    ProductCatalog catalog;
    ShoppingCart cart;
    OrderHistory orders;
    WishlistQueue wishlist;
    PriceBST priceTree;
    
    // Load products into BST
    for (int i = 1; i <= 20; i++) {
        Product* p = catalog.search(i);
        if (p != nullptr) {
            priceTree.addProduct(*p);
        }
    }
    
    int choice, role;
    
    cout << "========================================\n";
    cout << "   E-COMMERCE DSA PROJECT - Spring 2025\n";
    cout << "========================================\n";
    cout << "Submitted by: Muhammad Anas Tahir\n";
    cout << "Roll No: F2024266985\n";
    cout << "Course: Data Structures & Algorithm Lab\n";
    cout << "========================================\n\n";
    
    cout << "Select Role:\n";
    cout << "1. Customer\n";
    cout << "2. Admin\n";
    cout << "Enter choice: ";
    cin >> role;
    
    if (role == 2) {
        string password;
        cout << "Enter Admin Password: ";
        cin >> password;
        if (password != "admin123") {
            cout << "Incorrect password!\n";
            return 0;
        }
        
        // Admin Menu
        do {
            cout << "\n========== ADMIN MENU ==========\n";
            cout << "1. View All Products\n";
            cout << "2. View Products by Price (BST)\n";
            cout << "3. Search Price Range\n";
            cout << "4. View Order History\n";
            cout << "0. Exit\n";
            cout << "Choice: ";
            cin >> choice;
            
            switch(choice) {
                case 1: catalog.displayAll(); break;
                case 2: priceTree.displayByPrice(); break;
                case 3: 
                    double min, max;
                    cout << "Min price: "; cin >> min;
                    cout << "Max price: "; cin >> max;
                    priceTree.searchByPriceRange(min, max);
                    break;
                case 4: orders.viewHistory(); break;
            }
        } while (choice != 0);
        
        return 0;
    }
    
    // Customer Menu
    do {
        cout << "\n========== CUSTOMER MENU ==========\n";
        cout << "1. View All Products\n";
        cout << "2. Search Product by ID (Hash Table O(1))\n";
        cout << "3. Browse by Category\n";
        cout << "4. Add to Cart (Linked List)\n";
        cout << "5. View Cart\n";
        cout << "6. Remove from Cart\n";
        cout << "7. Checkout ? Push to Order History (Stack)\n";
        cout << "8. View Order History\n";
        cout << "9. Add to Wishlist (Queue)\n";
        cout << "10. View Wishlist\n";
        cout << "11. Process Wishlist Notifications\n";
        cout << "12. View Products by Price (BST)\n";
        cout << "13. Search Price Range\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                catalog.displayAll();
                break;
                
            case 2: {
                int id;
                cout << "Enter Product ID: ";
                cin >> id;
                Product* p = catalog.search(id);
                if (p) {
                    p->display();
                } else {
                    cout << "Product not found!\n";
                }
                break;
            }
            
            case 3: {
                cout << "\nCategories:\n";
                cout << "1. Electronics\n2. Books\n3. Furniture\n4. Beauty\n5. Grocery\n";
                int catChoice;
                cout << "Choice: ";
                cin >> catChoice;
                const char* category;
                switch(catChoice) {
                    case 1: category = "Electronics"; break;
                    case 2: category = "Books"; break;
                    case 3: category = "Furniture"; break;
                    case 4: category = "Beauty"; break;
                    case 5: category = "Grocery"; break;
                    default: category = ""; break;
                }
                if (strcmp(category, "") != 0) {
                    catalog.displayByCategory(category);
                }
                break;
            }
            
            case 4: {
                int id, qty;
                catalog.displayAll();
                cout << "Enter Product ID: ";
                cin >> id;
                cout << "Enter Quantity: ";
                cin >> qty;
                Product* p = catalog.search(id);
                if (p) {
                    cart.addItem(*p, qty, catalog);
                } else {
                    cout << "Product not found!\n";
                }
                break;
            }
            
            case 5:
                cart.viewCart();
                break;
                
            case 6: {
                int id;
                cart.viewCart();
                cout << "Enter Product ID to remove: ";
                cin >> id;
                cart.removeItem(id);
                break;
            }
            
            case 7:
                if (!cart.isEmpty()) {
                    cart.viewCart();
                    char confirm;
                    cout << "Confirm checkout? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') {
                        int itemCount = 0;
                        // Count items (simplified)
                        orders.addOrder(cart.getTotal(), 1);
                        cart.clear();
                        cout << "Checkout successful! Thank you for shopping!\n";
                    }
                } else {
                    cout << "Cart is empty!\n";
                }
                break;
                
            case 8:
                orders.viewHistory();
                break;
                
            case 9: {
                int id;
                catalog.displayAll();
                cout << "Enter Product ID to add to wishlist: ";
                cin >> id;
                Product* p = catalog.search(id);
                if (p) {
                    wishlist.addToWishlist(id, p->name);
                } else {
                    cout << "Product not found!\n";
                }
                break;
            }
            
            case 10:
                wishlist.viewWishlist();
                break;
                
            case 11:
                wishlist.processNotifications();
                break;
                
            case 12:
                priceTree.displayByPrice();
                break;
                
            case 13: {
                double min, max;
                cout << "Min price: "; cin >> min;
                cout << "Max price: "; cin >> max;
                priceTree.searchByPriceRange(min, max);
                break;
            }
        }
    } while (choice != 0);
    
    cout << "\nThank you for using E-Commerce DSA System!\n";
    return 0;
}
