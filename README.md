# E-Commerce DSA System

**Course:** Data Structures & Algorithm Lab | **Semester:** Spring 2025 | **Instructor:** Sir Muhammad Rizwan | **University:** UMT, Lahore Campus | **Student:** Muhammad Anas Tahir | **Roll Number:** F2024266985

## Data Structures Implemented

| # | Data Structure | Application | Time Complexity |
|---|----------------|-------------|-----------------|
| 1 | Hash Table | Product Catalog Search | O(1) average |
| 2 | Singly Linked List | Shopping Cart Management | O(1) insert |
| 3 | Stack (Array-based) | Order History (LIFO) | O(1) push/pop |
| 4 | Queue (Linked List) | Wishlist Notifications (FIFO) | O(1) enqueue/dequeue |
| 5 | Binary Search Tree | Price-Sorted Browsing | O(log n) average |

## Features

**Customer Panel:** View all products | Search product by ID (Hash Table - O(1)) | Browse by category (Electronics, Books, Furniture, Beauty, Grocery) | Add to cart (Linked List) | View cart | Remove from cart | Checkout (push to order history stack) | View order history (LIFO display) | Add to wishlist (queue) | View wishlist | Process wishlist notifications | View products by price (BST in-order) | Search products by price range

**Admin Panel:** View all products | View products by price (BST) | Search price range | View order history

## How to Compile and Run

**Windows:**
g++ src/DSA_Ecommerce.cpp -o ecommerce.exe
./ecommerce.exe

**Linux / Mac:**
g++ src/DSA_Ecommerce.cpp -o ecommerce
./ecommerce

**Admin Access Password:** admin123

## Project Structure

Ecommerce-DSA/
├── src/
│   └── DSA_Ecommerce.cpp
├── docs/
│   └── E-Commerce_DSA_Documentation.docx
├── README.md
└── .gitignore

## Related Projects

- OOP E-Commerce System: https://github.com/anastahir00/OOP-Ecommerce-System

## Submission Date

May 22, 2025