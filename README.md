# Employee Management System in C

A simple *Employee Management System* built using *pure C programming. It supports **Admin* and *Employee* logins, complete with features like employee management, payroll viewing, and attendance tracking.

---

## 📁 Project Structure


├── main.c
├── admin.c
├── admin.h
├── employee.c
├── employee.h
├── utils.c
├── utils.h
├── employees.txt          # Employee records (ID, Name, Password)
├── attendance.txt         # Attendance logs (ID, Date)


---

## 🔑 Features

### ✅ Admin Login
- Fixed credentials
- Admin-only features:
  - Add New Employee
  - Delete Employee
  - Update Employee Details
  - View All Employees

### ✅ Employee Login
- Login using Employee ID and Password
- Employee-only features:
  - View Personal Details
  - Mark Attendance (one-time per day)

### ✅ Data Storage
- Employee records are saved in employees.txt
- Attendance is recorded in attendance.txt
- Uses *file handling only*, no external DB

---

## 🚀 How to Run

### 🧰 Prerequisites
- GCC compiler (e.g., MinGW for Windows)
- A terminal or CMD with access to gcc

### 🛠 Compile the project
bash
gcc main.c admin.c employee.c utils.c -o ems.exe


### ▶ Run the project
bash
./ems.exe


> 💡 Use cls for Windows or clear for Linux/macOS if screen clearing doesn't work.

---

## 👨‍💻 Admin Credentials
| Username | Password |
|----------|----------|
| admin  | admin  |

---

## 📒 Sample Format: employees.txt

101 John john123
102 Alice alice321


## 📒 Sample Format: attendance.txt

101 2025-04-11
102 2025-04-11


---

## 📌 Notes
- All data is stored in *plain text files*.
- Uses system("cls") for screen clearing (Windows-specific).
- clearScreen() and other utilities are placed in utils.c.

---

## ✅ Future Enhancements
- Add payroll system
- Password encryption
- Search/sort employee features
- MySQL backend integration (planned)

---

## 🧑‍💼 Developed By
*Your Name Here*  
C Programming Enthusiast | Developer
