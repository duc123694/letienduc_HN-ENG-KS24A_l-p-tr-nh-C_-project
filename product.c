#include <stdio.h>
#include <string.h>
#include "product.h"
#include "datatype.h"
struct Product products[100];
int proCount = 0;
void manageProduct() {
	system("cls");
    int choice;
    while (1) {
        printf("\n=====** Manage Products **=====\n");
        printf("1. Display Products\n");
        printf("2. Add Product\n");
        printf("3. Edit Product\n");
        printf("4. Delete Product\n");
        printf("5. Search Product\n");
        printf("6. Sort Product\n");
        printf("0. Back to Main Menu\n");
        printf("Moi nhap lua chon cua minh: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                displayProducts();
                break;
            case 2:
            	addProduct();
                break;
            case 3:
            	editProduct();
                break;
            case 4:
            	deleteProduct();
                break;
            case 5:{
            	searchProduct();
				break;
			}
            case 6:{
            	sortProduct();
				break;
			}
            case 0:
            	system("cls");
                return;
            default:
                printf("Moi nhap lai lua chon cua ban.\n");
        }
    }
}

void savePro(){
	FILE *file;
	file=fopen("product.bin","wb");
	if(file){
		fwrite(&proCount,sizeof(int),1,file);
		fwrite(products, sizeof(struct Product), proCount, file);
		fclose(file);
	}
}
void loadProduct() {
    FILE *file = fopen("product.bin", "rb");
    if (file) {
        fread(&proCount, sizeof(int), 1, file);
        fread(products, sizeof(struct Product), proCount, file);
        fclose(file);
    } 
}
void displayProducts() {
	system("cls");
	loadProduct();
    if (proCount == 0) {
        printf("Ko co san pham nao ca.\n");
        return;
    }
    printf("\n-----**List of Products**-----\n");
    printf("+------------+-------------------+----------+-------+\n");
    printf("| ProductID  | Product Name      | Quantity | Price |\n");
    printf("+------------+-------------------+----------+-------+\n");
    for (int i = 0; i < proCount; i++) {
        printf("| %-10s | %-17s | %-8d | %-5d |\n", products[i].productId, products[i].productName, products[i].quantity, products[i].price);
    }
    printf("+------------+-------------------+----------+-------+\n");
    savePro();
}

void addProduct() {
	system("cls");
    if (proCount >= 100) {
        printf("Danh sach da day.\n");
        return;
    }
    struct Product newProduct;
    printf("Moi nhap ID san pham: ");
    scanf("%s", newProduct.productId);
    getchar();
    for (int i = 0; i < proCount; i++) {
        if (strcmp(products[i].productId, newProduct.productId) == 0) {
            printf("ID san pham da ton tai moi nhap ID khac\n");
            savePro();
            return;
        }
    }

    printf("Moi nhap ten san pham: ");
    fgets(newProduct.productName, 50, stdin);
    newProduct.productName[strcspn(newProduct.productName, "\n")] = '\0';

    printf("Moi nhap so luong: ");
    scanf("%d", &newProduct.quantity);

    printf("Moi nhap gia tien: ");
    scanf("%d", &newProduct.price);

    products[proCount++] = newProduct;
    printf("San pham da duoc them vao thanh cong!!!!.\n");
    savePro();
}
void deleteProduct() {
    system("cls");
    char id[10];
    printf("Moi nhap ID ban muon xoa: ");
    scanf("%s", id);
    getchar();
    for (int i = 0; i < proCount; i++) {
        if (strcmp(products[i].productId, id) == 0) {
            printf("Ban co chac chan muon xoa danh muc nay? (Y/N): ");
            char choice;
            scanf(" %c", &choice);
            getchar();
            if (choice == 'Y' || choice == 'y') {
                for (int j = i; j < proCount - 1; j++) {
                    products[j] = products[j + 1];
                }
                proCount--;
                printf("Danh muc da duoc xoa thanh cong!\n");
                savePro();
                return;
            } else if (choice == 'N' || choice == 'n') {
                printf("Huy xoa danh muc.\n");
                return;
            } else {
                printf("Lua chon khong hop le. Huy xoa danh muc.\n");
                return;
            }
        }
    }

    printf("Khong tim thay ID ban can xoa.\n");
}
void editProduct(){
	system("cls");
	char id[10];
	printf("Moi ban nhap ID ban muon chinh sua: ");
	scanf("%d");
	for(int i=0;i<proCount;i++){
		if(strcmp(products[i].productId,id)==0){
			printf("Moi nhap ten mat hang moi: ");
			fgets(products[i].productName,100,stdin);
			products[i].productName[strcspn(products[i].productName,"\n")]='\0';
			printf("San pham da duoc cap nhat thanh cong");
			savePro();
			return;
		}
	}
}
void searchProduct(){
	system("cls");
	char searchName[50];
	printf("Moi nhap ten can tim kiem ");
	fgets(searchName,50,stdin);
	searchName[strcspn(searchName,"\n")]='\0';
	int found=0;
	printf("****Ket qua tim kiem****\n");
	printf("+--------------+--------------------------+\n");
	printf("|    ID        |          Name            |\n");
	printf("+--------------+--------------------------+\n");
	for(int i=0;i<proCount;i++){
		if(strstr(products[i].productName,searchName) != NULL){
			printf("| %-12s | %-19s |\n",products[i].productId,products[i].productName);
			found = 1;
		}
	}
	printf("+--------------+--------------------------+\n");
	if(!found){
		printf("Ko tim thay san pham co ky tu %s\n",searchName);
	}	
}
void sortProduct() {
    int choose = 0;
    if (proCount == 0) {
        printf("Ko co danh muc nao dc sap xep\n");
        return;
    }
    system("cls");
    printf("1. Sap xep san pham theo chieu tang dan cua gia tien\n");
    printf("2. Sap xep san pham theo chieu giam dan cua gia tien\n");
    scanf("%d", &choose);

    if (choose == 1) {
        for (int i = 0; i < proCount - 1; i++) {
            for (int j = 0; j < proCount - i - 1; j++) {
                if ( products[j].price > products[j+1].price) {
                    struct Product temp = products[j];
                    products[j] = products[j + 1];
                    products[j + 1] = temp;
                }
            }
        }
    } else if (choose == 2) {
        for (int i = 0; i < proCount - 1; i++) {
            for (int j = 0; j < proCount - i - 1; j++) {
                if ( products[j].price < products[j+1].price) {
                    struct Product temp = products[j];
                    products[j] = products[j + 1];
                    products[j + 1] = temp;
                }
            }
        }
    } else {
        printf("Lua chon chua hop le\n");
        return;
    }
    savePro();
    printf("San pham da duoc sap xep\n");
}

