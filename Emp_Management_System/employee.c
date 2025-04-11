#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "employee.h"
#include "admin.h"
#include "utils.h"

int employeeLogin(int *loggedInID) {
    clearScreen();
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL) {
        printf("\nNo employees found! Please contact admin.\n");
        return 0;
    }

    int id, enteredID, found = 0;
    char name[50], password[20], enteredPassword[20];

    while (1) {
        printf("\nEnter Employee ID: ");
        scanf("%d", &enteredID);
        printf("Enter Password: ");
        scanf("%s", enteredPassword);

        rewind(file);  // Reset file pointer to beginning

        while (fscanf(file, "%d %s %s", &id, name, password) != EOF) {
            if (id == enteredID && strcmp(password, enteredPassword) == 0) {
                printf("\nLogin Successful! Welcome, %s.\n", name);
                *loggedInID = id;  // Store the logged-in Employee ID
                fclose(file);
                return 1;
            }
        }

        printf("\nInvalid Employee ID or Password. Try again? (1-Yes, 2-No): ");
        int choice;
        scanf("%d", &choice);
        if (choice != 1) {
            fclose(file);
            return 0;
        }
    }
}
void viewEmployeeDetails(int empID) {
    clearScreen();
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL) {
        printf("\nError opening employee records.\n");
        return;
    }

    int id, found = 0;
    char name[50], password[20];

    while (fscanf(file, "%d %s %s", &id, name, password) != EOF) {
        if (id == empID) {
            printf("\n=====================================\n");
            printf("       Employee Details        \n");
            printf("=====================================\n");
            printf("ID: %d\n", id);
            printf("Name: %s\n", name);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("\nEmployee details not found!\n");
    }
}
void markAttendance(int empID) {
    clearScreen();
    FILE *file = fopen("attendance.txt", "r+");
    if (file == NULL) {
        file = fopen("attendance.txt", "w");  // Create file if it doesn't exist
        if (file == NULL) {
            printf("\nError opening attendance file!\n");
            return;
        }
    }

    time_t t;
    time(&t);
    struct tm *tm_info = localtime(&t);

    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d", tm_info);

    int id;
    char existingDate[20];
    
    while (fscanf(file, "%d %s", &id, existingDate) != EOF) {
        if (id == empID && strcmp(existingDate, date) == 0) {
            printf("\nAttendance already marked for Employee ID %d on %s\n", empID, date);
            fclose(file);
            return;
        }
    }
    fseek(file, 0, SEEK_END);
    fprintf(file, "%d %s\n", empID, date);
    fclose(file);

    printf("\nAttendance marked successfully for Employee ID %d on %s\n", empID, date);
}

void employeeMenu(int empID) {
    clearScreen();
    int choice;
    
    while (1) {
        printf("\n=====================================\n");
        printf("           Employee Menu            \n");
        printf("=====================================\n");
        printf("1. View My Details\n");
        printf("2. Mark Attendance\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewEmployeeDetails(empID);
                break;
            case 2:
                markAttendance(empID);
                break;
            case 3:
                clearScreen();
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
}