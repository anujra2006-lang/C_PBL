#include <stdio.h>
#include <string.h>

struct Customer {
    char name[100];
    char address[200];
    char phone[20];
};

struct Item {
    int   id;
    char  name[100];
    float quantity;
    char  unit[20];
    float price;
};

int main() {
    struct Customer customer;
    int   totalItems;
    float total = 0, tax = 0, grandTotal = 0;

    printf("\n----------------------------------\n");
    printf("|    CUSTOMER BILLING SYSTEM       |\n");
    printf("----------------------------------\n\n");

    printf("Enter Name    : ");
    scanf(" %100[^\n]", customer.name);
    printf("Enter Address : ");
    scanf(" %200[^\n]", customer.address);
    printf("Enter Phone   : ");
    scanf(" %10[^\n]", customer.phone);

    printf("\nHow many items : ");
    scanf("%d", &totalItems);

    struct Item items[totalItems];

    printf("\n--- Enter Item Details ---\n");
    for (int i = 0; i < totalItems; i++) {
        char hasUnit;
        items[i].id = i + 1;

        printf("\nItem %d:\n", i + 1);
        printf("  Name              : ");
        scanf(" %100[^\n]", items[i].name);
        printf("  Quantity          : ");
        scanf("%f", &items[i].quantity);
        printf("  Has unit? (y/n)   : ");
        scanf(" %c", &hasUnit);

        if (hasUnit == 'y' || hasUnit == 'Y') {
            printf("  Unit (kg/g/L/etc) : ");
            scanf(" %19s", items[i].unit);
        } else {
            strcpy(items[i].unit, "");
        }

        printf("  Price per item    : ");
        scanf("%f", &items[i].price);
    }

    for (int i = 0; i < totalItems; i++) {
        total += items[i].quantity * items[i].price;
    }
    tax        = total * 0.05f;
    grandTotal = total + tax;

    
    FILE *fp = fopen("bill.txt", "w");
    if (fp == NULL) {
        printf("Could not create bill.txt\n");
        return 1;
    }

    #define PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__); fprintf(fp, fmt, ##__VA_ARGS__)

    PRINT("\n+===============================================+\n");
    PRINT("|                    BILL                      |\n");
    PRINT("+===============================================+\n");
    PRINT("  Name    : %s\n", customer.name);
    PRINT("  Address : %s\n", customer.address);
    PRINT("  Phone   : %s\n", customer.phone);
    PRINT("+-----------------------------------------------+\n");
    PRINT("| %-4s | %-15s | %-8s | %-6s | %-8s |\n",
          "ID", "Item Name", "Qty", "Price", "Subtotal");
    PRINT("+-----------------------------------------------+\n");

    for (int i = 0; i < totalItems; i++) {
        float subtotal = items[i].quantity * items[i].price;
        if (strlen(items[i].unit) > 0) {
            PRINT("| %-4d | %-15s | %-4.1f %-3s | %-6.2f | %-8.2f |\n",
                  items[i].id, items[i].name,
                  items[i].quantity, items[i].unit,
                  items[i].price, subtotal);
        } else {
            PRINT("| %-4d | %-15s | %-8.0f | %-6.2f | %-8.2f |\n",
                  items[i].id, items[i].name,
                  items[i].quantity, items[i].price, subtotal);
        }
    }

    Printf("+-----------------------------------------------+\n");
    Printf("  Subtotal    : %.2f\n", total);
    Printf("  Tax (5%%)    : %.2f\n", tax);
    Printf("  Grand Total : %.2f\n", grandTotal);
    Printf("+===============================================+\n");
    Printf("|         Thanks for visiting us!              |\n");
    Printf("+===============================================+\n\n");

    fclose(fp);
    printf("[INFO] Bill saved to bill.txt\n\n");

    return 0;
}
