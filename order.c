#include <stdio.h>
#include <string.h>
#include "order.h"
#include "datatype.h"
struct Order orders[100];
int ordCount = 0;
void manageOrder() {
	system("cls");
    int choice;
    while (1) {
        printf("\n=====** Manage Orders **=====\n");
        printf("1. Display Orders\n");
        printf("2. Add Order\n");
        printf("3. Delete Order\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
            	displayOrders();
                break;
            case 2:
            	addOrder();
                break;
            case 3:
            	deleteOrder();
                break;
            case 0:
            	system("cls");
                return;
            default:
                printf("Moi nhap lai lua chon cua ban.\n");
        }
    }
}
void displayOrders() {
	system("cls");
    if (ordCount == 0) {
        printf("Ko co don dat hang nao.\n");
        return;
    }
    printf("\nList of Orders:\n");
    printf("+------------+-------------------+------------+------------+------------+------------+\n");
    printf("| OrderID    | CustomerID        | Date       | ProductID  | Quantity   | Price      |\n");
    printf("+------------+-------------------+------------+------------+------------+------------+\n");
    for (int i = 0; i < ordCount; i++) {
        printf("| %-10s | %-17s | %-10d-%-2d-%-4d | %-10s | %-8d | %-5d |\n",
               orders[i].orderId,
               orders[i].customerId,
               orders[i].date.day,
               orders[i].date.month,
               orders[i].date.year,
               orders[i].product.productId,
               orders[i].product.quantity,
               orders[i].product.price);
    }
    printf("+------------+-------------------+------------+------------+------------+------------+\n");
}

void addOrder() {
	system("cls");
    if (ordCount >= 100) {
        printf("Danh sach dat hang da day.\n");
        return;
    }
    struct Order newOrder;
    printf("Moi nhap ID dat hang: ");
    scanf("%s", newOrder.orderId);
    getchar(); 
    for (int i = 0; i < ordCount; i++) {
        if (strcmp(orders[i].orderId, newOrder.orderId) == 0) {
            printf("ID don hang da ton tai. Vui long nhap ID khac!\n");
            return;
        }
    }
    
    printf("Nhap ID khach hang: ");
    scanf("%s", newOrder.customerId);
    getchar(); 

    printf("Moi nhap ngay dat hang (DD MM YYYY): ");
    scanf("%d %d %d", &newOrder.date.day, &newOrder.date.month, &newOrder.date.year);

    printf("Nhap ID san pham: ");
    scanf("%s", newOrder.product.productId);
    getchar(); 

    printf("Moi nhap so luong: ");
    scanf("%d", &newOrder.product.quantity);

    printf("Moi nhap gia ban: ");
    scanf("%d", &newOrder.product.price);

    orders[ordCount++] = newOrder;
    printf("Da them don hang thanh cong.\n");
}
void deleteOrder() {
    system("cls");
    char id[10];
    printf("Moi nhap ID ban muon xoa: ");
    scanf("%s", id);
    getchar();
    for (int i = 0; i <ordCount; i++) {
        if (strcmp(orders[i].orderId, id) == 0) {
            printf("Ban co chac chan muon xoa don dat hang nay? (Y/N): ");
            char choice;
            scanf(" %c", &choice);
            getchar();
            if (choice == 'Y' || choice == 'y') {
                for (int j = i; j < ordCount - 1; j++) {
                    orders[j] = orders[j + 1];
                }
                ordCount--;
                printf("Don hang da duoc xoa thanh cong!\n");
                saveCate(); 
                return;
            } else if (choice == 'N' || choice == 'n') {
                printf("Huy xoa don hang.\n");
                return;
            } else {
                printf("Lua chon khong hop le. Huy xoa don hang.\n");
                return;
            }
        }
    }

    printf("Khong tim thay ID ban can xoa.\n");
}
