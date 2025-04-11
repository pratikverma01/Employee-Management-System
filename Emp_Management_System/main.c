#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
#include "employee.h"
#include "utils.h"

void mainMenu() {
    clearScreen();
    int choice, loggedInID;
    
    while (1) {
        printf("\n=====================================\n");
        printf("       Employee Management System    \n");
        printf("=====================================\n");
        printf("1. Admin Login\n");
        printf("2. Employee Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                if (employeeLogin(&loggedInID)) {
                    employeeMenu(loggedInID);
                }
                break;
            case 3:
                printf("\nExiting the system. Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
}



int main() {
    mainMenu();
    return 0;
}

