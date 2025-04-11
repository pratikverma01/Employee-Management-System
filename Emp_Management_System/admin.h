#ifndef ADMIN_H
#define ADMIN_H

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "1234"
#define EMPLOYEE_FILE "employees.txt"

void adminLogin();
void adminMenu();
void addEmployee();
void deleteEmployee();
void updateEmployee();
void processPayroll();
void viewPayroll();
void viewEmployees();

#endif
