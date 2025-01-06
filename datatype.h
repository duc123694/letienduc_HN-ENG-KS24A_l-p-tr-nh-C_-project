#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Date {
    int day, month, year;
};

struct Category {
    char categoryId[10];
    char categoryName[50];
};

struct Product {
    char productId[10];
    char categoryId[10];
    char productName[50];
    int quantity;
    int price;
};

struct Order {
    char orderId[10];
    char customerId[20];
    struct Date date;
    struct Product product;
};

