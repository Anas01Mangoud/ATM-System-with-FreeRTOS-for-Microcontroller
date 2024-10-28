# ATM-System-with-FreeRTOS-for-Microcontroller
This project implements an ATM system on a microcontroller using FreeRTOS for task management, inter-task communication, and resource management. The ATM allows users to log in, check their balance, and withdraw money, with the FreeRTOS framework enabling multitasking and synchronization among various tasks such as keypad input, LCD display, balance checking, and more.

Features
User Login: Allows users to log in with an ID and password.
Balance Check: Validates user balance before allowing withdrawal.
Cash Withdrawal: Withdraws the requested amount based on the available denominations.
LCD Display: Displays prompts and feedback to the user.
Task Management with FreeRTOS: Separate tasks handle input, validation, balance checking, display, and money output, improving modularity and reliability.
Semaphores and Queues: Utilizes FreeRTOS semaphores and queues for synchronization and data passing between tasks.

Project Structure
User Database: Stores user information (ID, password, balance).
Bank Structure: Holds bank's cash inventory in various denominations.
FreeRTOS Components: Semaphores and queues for managing inter-task communication and ensuring safe access to shared resources.
Tasks: Tasks perform specific functions and communicate via FreeRTOS queues

Getting Started
Prerequisites: Install the AVR-GCC compiler and FreeRTOS library.
Setup: Clone the repository and configure the microcontroller pins for LCD, keypad, and motor control.
Compile: Use the AVR-GCC compiler to build the project.
Upload: Flash the compiled binary to the microcontroller.
Usage
Power on the system: The ATM system will initialize.
Log in: Enter the user ID and password via the keypad.
Select an Option: Choose to check balance or withdraw cash.
Withdraw Cash: Enter the amount, and if available, the system will dispense the amount.
