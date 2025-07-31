# 🛢️ Oil Refining Internal Management System

A Windows-based C++ project designed to manage the internal operations of a large-scale oil refinery company, including employee management, attendance tracking, salary calculation, and plant operations. The company structure spans seven hierarchical levels and includes support for multiple plants across different locations.

---

## 📌 Project Summary

This system solves the problem of managing internal operations in a multi-plant oil refining company by providing:

- Hierarchical login-based access:
  - CEO
  - Director
  - Administrator
  - Manager (Management, Accountant, HR)
  - Employee
- Location-based plant management
- Employee attendance system
- Salary calculation based on working hours
- File-based data storage and manipulation

---

## ✅ Key Achievements

- **Efficient Use of File Handling:**  
  Implemented robust file reading, parsing, editing, and saving mechanisms to handle large data such as attendance logs and plant records.

---

## 🔧 Areas of Improvement

- **Code Refactoring:**  
  Reusable code can be modularized into functions to improve clarity and reduce redundancy.

- **Switch to Database:**  
  Replacing text files with a database (e.g., MySQL) would enhance security, reliability, and efficiency.

- **Clean-Up:**  
  Remove unnecessary or unused code to streamline the system.

---

## 🧠 Most Challenging Feature

- **Attendance & Salary Module:**  
  Calculating salaries based on attendance using file handling was difficult. The solution involved implementing a credit-hour system:
  - Present → 9 credit hours
  - Absent → 0 credit hours
  - Total salary = Total hours × Rate/hour

---

## 📚 Transferable Skills

- **File Handling in C++:**  
  A fundamental concept learned through this project, applicable to a wide range of applications where persistent data storage is required.

---

## 🛠️ Code Readability & Maintenance

- **Modular Structure:**  
  Code separated into `.cpp` and `.h` files for better maintainability.
- **Commenting:**  
  Comments added to function prototypes and major sections to improve understanding and future adaptability.

---

> Developed with 💻 using C++ for a robust management experience in the oil refining industry.
