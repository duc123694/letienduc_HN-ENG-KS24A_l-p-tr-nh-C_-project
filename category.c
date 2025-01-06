#include <stdio.h>
#include <string.h>
#include "category.h"
#include "datatype.h"
struct Category categories[100];
int cateCount = 0;
void manageCategory() {
	system("cls");
    int choice;
    while (1) {
        printf("\n=====** Manage Categories **=====\n");
        printf("1. Display Category\n");
        printf("2. Add Category\n");
        printf("3. Edit Category\n");
        printf("4. Delete Category\n");
        printf("5. Search Category\n");
        printf("6. Sort Category\n");
        printf("0. Back to Main Menu\n");
        printf("Moi nhap lua chon: ");
        scanf("%d", &choice);
        getchar(); 
        switch (choice) {
            case 1:
                displayCategory();
                break;
            case 2:
            	addCategory();
                break;
            case 3:
            	editCategory();
                break;
            case 4:
            	deleteCategory();
                break;
            case 5:
            	searchCategory();
            	break;
            case 6:
            	sortCategories();
            	break;
            case 0:
            	system("cls");
                return;
            default:
                printf("MOi nhap lai lua chon cua ban!.\n");
        }
    }
}
void saveCate() {
    FILE *file;
	file = fopen("category.bin", "wb");
    if (file) {
        fwrite(&cateCount, sizeof(int), 1, file);
        fwrite(categories, sizeof(struct Category), cateCount, file);
        fclose(file);
    }
}
void loadCate() {
    FILE *file = fopen("category.bin", "rb");
    if (file) {
        fread(&cateCount, sizeof(int), 1, file);
        fread(categories, sizeof(struct Category), cateCount, file);
        fclose(file);
    } 
}
void displayCategory() {
	system("cls");
	loadCate();
    if (cateCount == 0) {
        printf("Khong co danh muc nao.\n");
        return;
    }
    printf("\n-----**List of Categories**------\n");
    printf("+------------+-------------------+\n");
    printf("|     ID     |          Name     |\n");
    printf("+------------+-------------------+\n");
    for (int i = 0; i < cateCount; i++) {
    printf("| %-10s | %-17s |\n", categories[i].categoryId, categories[i].categoryName);
    }
    printf("+------------+-------------------+\n");
}
void addCategory() {
    system("cls");
    if (cateCount >= 100) {
        printf("Danh sach da day.\n");
        return;
    }
    struct Category newCategory;
    while (1) {
        int isDuplicate = 0;
        printf("Moi nhap ID cua danh muc: ");
        scanf("%s", newCategory.categoryId);
        getchar();
        for (int i = 0; i < cateCount; i++) {
            if (strcmp(categories[i].categoryId, newCategory.categoryId) == 0) {
                printf("ID danh muc da ton tai, vui long nhap ID khac.\n");
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            break;
        }
    }
    while (1) {
        int isDuplicate = 0;
        printf("Moi nhap Ten danh muc: ");
        fgets(newCategory.categoryName, sizeof(newCategory.categoryName), stdin);
        newCategory.categoryName[strcspn(newCategory.categoryName, "\n")] = '\0'; 
        for (int i = 0; i < cateCount; i++) {
            if (strcmp(categories[i].categoryName, newCategory.categoryName) == 0) {
                printf("Ten danh muc da ton tai, vui long nhap ten khac.\n");
                isDuplicate = 1;
                break;
            }
        }
        if (strlen(newCategory.categoryName) == 0 || strlen(newCategory.categoryName) > 49) {
            printf("Ten danh muc khong hop le, moi nhap lai.\n");
        } else if (!isDuplicate) {
            break; 
        }
    }
    categories[cateCount++] = newCategory;
    printf("Da them danh muc thanh cong.\n");
    saveCate();
}
void editCategory(){
	system("cls");
	char id[10];
	printf("Moi nhap ID muon sua: ");
	scanf("%s",&id);
	getchar();
	for(int i=0;i<cateCount;i++){
		if(strcmp(categories[i].categoryId,id)==0){
			printf("Moi nhap ten mat hang moi: ");
			fgets(categories[i].categoryName,100,stdin);
			categories[i].categoryName[strcspn(categories[i].categoryName,"\n")]='\0';
			printf("Danh muc da duoc cap nhat thanh cong");
			saveCate(); 
			return;
		}
	}
	printf("ID ban nhap ko duoc tim thay\n");
}
void deleteCategory() {
    system("cls");
    char id[10];
    printf("Moi nhap ID ban muon xoa: ");
    scanf("%s", id);
    getchar();
    for (int i = 0; i < cateCount; i++) {
        if (strcmp(categories[i].categoryId, id) == 0) {
            printf("Ban co chac chan muon xoa danh muc nay? (Y/N): ");
            char choice;
            scanf(" %c", &choice);
            getchar();
            if (choice == 'Y' || choice == 'y') {
                for (int j = i; j < cateCount - 1; j++) {
                    categories[j] = categories[j + 1];
                }
                cateCount--;
                printf("Danh muc da duoc xoa thanh cong!\n");
                saveCate(); 
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
void searchCategory() {
    system("cls");
    char searchName[50];
    printf("Moi nhap tu khoa tim kiem: ");
    fgets(searchName, 50, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    int found = 0;
    printf("\nKet qua tim kiem danh muc:\n");
    printf("+------------+-------------------+\n");
    printf("|     ID     |          Name     |\n");
    printf("+------------+-------------------+\n");
    for (int i = 0; i < cateCount; i++) {
        if (strstr(categories[i].categoryName, searchName) != NULL) {
            printf("| %-10s | %-17s |\n", categories[i].categoryId, categories[i].categoryName);
            found = 1;
        }
    }
    printf("+------------+-------------------+\n");
    if (!found) {
        printf("Ko tim thay danh muc co tu %s\n", searchName);
    }
}
void sortCategories() {
	int choose=0;
    if (cateCount == 0) {
        printf("Khong co danh muc de sap xep.\n");
        return;
    }
    system("cls");
    printf("1.Sap xep danh muc theo ten theo chieu tang dan\n");
    printf("2.Sap xep danh muc theo ten theo chieu giam dan\n");
    printf("Moi nhap lua chon: ");
    scanf("%d",&choose);
    if(choose==1){
    	for (int i = 0; i < cateCount - 1; i++) {
          for (int j = 0; j < cateCount - i - 1; j++) {
            if (strcmp(categories[j].categoryName, categories[j + 1].categoryName) > 0) {
                struct Category temp = categories[j];
                categories[j] = categories[j + 1];
                categories[j + 1] = temp;
            }
        }
    }
} else if(choose==2){
    	for (int i = 0; i < cateCount - 1; i++) {
          for (int j = 0; j < cateCount - i - 1; j++) {
            if (strcmp(categories[j].categoryName, categories[j + 1].categoryName) < 0) {
                struct Category temp = categories[j];
                categories[j] = categories[j + 1];
                categories[j + 1] = temp;
            }
        }
    }
}else{
	printf("Lua chon ko hop le\n");
	return;
}
    saveCate(); 
    printf("Danh muc da duoc sap xep theo ten.\n");
}
