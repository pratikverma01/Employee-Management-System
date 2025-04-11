#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "utils.h"

void adminLogin() {
    clearScreen();
    char username[20], password[20];
    int choice;

    while (1) {
        printf("\nEnter Admin Username: ");
        scanf("%s", username);
        printf("Enter Admin Password: ");
        scanf("%s", password);

        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("\nLogin Successful! Welcome, Admin.\n");
            adminMenu();
            return;
        } else {
            printf("\nIncorrect Username or Password!\n");
            printf("1. Try Again\n");
            printf("2. Exit to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            if (choice == 2) {
                return;
            }
        }
    }
}

void adminMenu() {
    clearScreen();
    int choice;
    
    while (1) {
        
        printf("\n=====================================\n");
        printf("            Admin Menu            \n");
        printf("=====================================\n");
        printf("1. Add Employee\n");
        printf("2. Delete Employee\n");
        printf("3. Update Employee\n");
        printf("4. View All Employees\n");
        printf("5. Process Payroll\n");
        printf("6. View Payroll\n");
        printf("7. Go Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                updateEmployee();
                break;
            case 4:
                viewEmployees();
                break;
            case 5:
                processPayroll();
                break;
            case 6:
                viewPayroll();
                break;
            case 7:
                clearScreen();
                return;
            default:
                printf("\nInvalid choice! Please enter again.\n");
        }
    }
}


void addEmployee() {
    clearScreen();
    
    FILE *file = fopen(EMPLOYEE_FILE, "r+"); 
    if (file == NULL) {
        file = fopen(EMPLOYEE_FILE, "w"); 
        if (file == NULL) {
            printf("\nError opening file!\n");
            return;
        }
    }

    int id, existingID;
    char name[50], password[20], designation[50], existingName[50], existingPassword[20], existingDesignation[50];

    printf("\nEnter Employee ID: ");
    scanf("%d", &id);

    // Check if ID already exists
    while (fscanf(file, "%d %s %s %s", &existingID, existingName, existingPassword, existingDesignation) != EOF) {
        if (existingID == id) {
            printf("\nError: Employee ID %d already exists! Please use a unique ID.\n", id);
            fclose(file);
            return;
        }
    }

    printf("Enter Employee Name: ");
    scanf(" %[^\n]", name);  // Read full name with spaces
    printf("Enter Employee Password: ");
    scanf("%s", password);
    printf("Enter Employee Designation: ");
    scanf(" %[^\n]", designation);

    // Move to end of file to append new data
    fseek(file, 0, SEEK_END);
    fprintf(file, "%d %s %s %s\n", id, name, password, designation);
    fclose(file);

    printf("\nEmployee Added Successfully!\n");
}



void viewEmployees() {
    clearScreen();
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL) {
        printf("\nNo employees found! File does not exist or is empty.\n");
        return;
    }

    int id;
    char name[50], password[20], designation[50];

    printf("\n=============================================\n");
    printf("               Employee List                 \n");
    printf("=============================================\n");
    printf("%-10s %-20s %-15s %-20s\n", "ID", "Name", "Password", "Designation");
    printf("---------------------------------------------------------------\n");

    while (fscanf(file, "%d %s %s %[^\n]", &id, name, password, designation) != EOF) {
        printf("%-10d %-20s %-15s %-20s\n", id, name, password, designation);
    }

    fclose(file);
}

void deleteEmployee() {
    clearScreen();
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL) {
        printf("\nNo employees found! File does not exist or is empty.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("\nError creating temporary file!\n");
        fclose(file);
        return;
    }

    int id, deleteID, found = 0;
    char name[50], password[20], designation[50];  // Added designation field
    char choice;

    printf("\nEnter Employee ID to delete: ");
    scanf("%d", &deleteID);

    while (fscanf(file, "%d %s %s %s", &id, name, password, designation) != EOF) {
        if (id == deleteID) {
            found = 1;
            printf("\nEmployee Found:\n");
            printf("ID: %d\nName: %s\nDesignation: %s\n", id, name, designation);

            printf("\nAre you sure you want to delete this employee? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                printf("\nEmployee with ID %d deleted successfully!\n", deleteID);
                continue;  // Skip writing this employee to `temp.txt`, effectively deleting it.
            } else {
                fprintf(tempFile, "%d %s %s %s\n", id, name, password, designation);
                printf("\nDeletion cancelled!\n");
            }
        } else {
            fprintf(tempFile, "%d %s %s %s\n", id, name, password, designation);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(EMPLOYEE_FILE);
        rename("temp.txt", EMPLOYEE_FILE);
    } else {
        remove("temp.txt");
        printf("\nEmployee with ID %d not found!\n", deleteID);
    }
}

void updateEmployee() {
    clearScreen();
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (file == NULL) {
        printf("\nNo employees found! File does not exist or is empty.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("\nError creating temporary file!\n");
        fclose(file);
        return;
    }

    int id, updateID, found = 0;
    char name[50], password[20], newName[50], newPassword[20];

    printf("\nEnter Employee ID to update: ");
    scanf("%d", &updateID);

    while (fscanf(file, "%d %s %s", &id, name, password) != EOF) {
        if (id == updateID) {
            found = 1;
            printf("\nEnter New Name: ");
            scanf(" %[^\n]", newName);
            printf("Enter New Password: ");
            scanf("%s", newPassword);
            fprintf(tempFile, "%d %s %s\n", id, newName, newPassword);
            printf("\nEmployee with ID %d updated successfully!\n", updateID);
        } else {
            fprintf(tempFile, "%d %s %s\n", id, name, password);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(EMPLOYEE_FILE);
        rename("temp.txt", EMPLOYEE_FILE);
    } else {
        remove("temp.txt");
        printf("\nEmployee with ID %d not found!\n", updateID);
    }
}
void processPayroll() {
    clearScreen();
    FILE *empFile = fopen(EMPLOYEE_FILE, "r");
    if (empFile == NULL) {
        printf("\nNo employees found! Please add employees first.\n");
        return;
    }

    int id, enteredID, empExists = 0;
    char name[50], password[20];

    printf("\nEnter Employee ID: ");
    scanf("%d", &enteredID);

    while (fscanf(empFile, "%d %s %s", &id, name, password) != EOF) {
        if (id == enteredID) {
            empExists = 1;
            break;
        }
    }
    fclose(empFile);

    if (!empExists) {
        printf("\nError: Employee with ID %d does not exist!\n", enteredID);
        return;
    }

    FILE *payFile = fopen("payroll.txt", "a");
    if (payFile == NULL) {
        printf("\nError opening payroll file!\n");
        return;
    }

    float basicSalary, allowances, deductions, netSalary;
    printf("Enter Basic Salary: ");
    scanf("%f", &basicSalary);
    printf("Enter Allowances: ");
    scanf("%f", &allowances);
    printf("Enter Deductions: ");
    scanf("%f", &deductions);

    netSalary = basicSalary + allowances - deductions;
    fprintf(payFile, "%d %.2f %.2f %.2f %.2f\n", enteredID, basicSalary, allowances, deductions, netSalary);
    fclose(payFile);

    printf("\nPayroll Processed! Net Salary for Employee ID %d: Rs %.2f\n", enteredID, netSalary);

    char choice;
    printf("\nDo you want to update the payroll? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        printf("\nRe-enter payroll details:\n");
        processPayroll();
    } else {
        printf("\nReturning to Admin Menu...\n");
    }
}

void viewPayroll() {
    clearScreen();
    FILE *file = fopen("payroll.txt", "r");
    if (file == NULL) {
        printf("\nNo payroll records found!\n");
        return;
    }

    int id;
    float basicSalary, allowances, deductions, netSalary;

    printf("\n==============================================\n");
    printf("            Payroll Details                 \n");
    printf("==============================================\n");
    printf("%-10s %-12s %-12s %-12s %-12s\n", "ID", "Basic", "Allowances", "Deductions", "Net Salary");
    printf("----------------------------------------------------------\n");

    while (fscanf(file, "%d %f %f %f %f", &id, &basicSalary, &allowances, &deductions, &netSalary) != EOF) {
        printf("%-10d ₹%-10.2f ₹%-10.2f ₹%-10.2f ₹%-10.2f\n", id, basicSalary, allowances, deductions, netSalary);
    }

    fclose(file);
}