#include <stdio.h>
#include <stdlib.h>
#include "category.h"
#include "product.h"
#include "order.h"
int main() {
	system("cls");
    int choice;
    while (1) {
        printf("\n** Store Management System Using C **\n");
        printf("======================================\n");
        printf("1. Manage Categories\n");
        printf("2. Manage Products\n");
        printf("3. Manage Orders\n");
        printf("0. Exit\n");
        printf("======================================\n");
        printf("Moi nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                manageCategory();
                break;
            case 2:
                manageProduct();
                break;
            case 3:
                manageOrder();
                break;
            case 0:
                printf("Exiting... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
