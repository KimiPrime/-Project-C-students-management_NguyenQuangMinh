#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 100

struct Date {
    int month, day, year;
};
struct Student {
    int StudentId;
    char name[30];
    struct Date dayOfBirth;
    bool gender;
    char email[30];
    char phone[20];
};
// fix cứng
//struct Student students[MAX] = {
    //{1, "Nguyen Van A", {01, 01, 2000}, true,  "vana@gmail.com", "0123456789"},
  //  {2, "Tran Thi B",   {15, 05, 2001}, false, "thib@gmail.com", "0987654321"}
//};
//int count = 2;

// ================== HÀM NHẬP ==================
// lựa chọn
int getValidChoice() {
    int choice;
    char c;
    while (1) {
        printf("Choose your option: ");
        if (scanf("%d", &choice) == 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            return choice;
        } else {
            printf(">> Invalid input! Choice must be a number.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

// giới tính
bool getValidGender() {
    int gen;
    char c;
    while (1) {
        printf("Gender (1=Male, 0=Female): ");
        if (scanf("%d", &gen) == 1 && (gen == 0 || gen == 1)) {
            while ((c = getchar()) != '\n' && c != EOF);
            return gen == 1;
        } else {
            printf(">> Invalid input! Enter 1 for Male or 0 for Female.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

// số đt
void getValidPhone(char *phone, int size) {
    while (1) {
        printf("Phone number: ");
        fgets(phone, size, stdin);
        phone[strcspn(phone, "\n")] = 0;

        int valid = 1;
        for (int i = 0; phone[i] != '\0'; i++) {
            if (!isdigit((unsigned char)phone[i])) {
                valid = 0;
                break;
            }
        }
        if (valid && strlen(phone) > 0) return;
        printf(">> Invalid phone number! Only digits allowed.\n");
    }
}

// ngày tháng
struct Date getValidDate() {
    struct Date d;
    while (1) {
        printf("Enter date of birth (dd mm yyyy): ");
        if (scanf("%d %d %d", &d.day, &d.month, &d.year) == 3) {
            char c;
            while ((c = getchar()) != '\n' && c != EOF);
            if (d.day >= 1 && d.day <= 31 &&
                d.month >= 1 && d.month <= 12 &&
                d.year >= 1900 && d.year <= 2100) {
                return d;
            } else {
                printf(">> Invalid date! Please enter again.\n");
            }
        } else {
            printf(">> Invalid input! Please enter 3 numbers.\n");
            char c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

//  EMAIL
int isValidEmail(const char *email) {
    int atPos = -1, dotPos = -1;
    int len = strlen(email);

    for (int i = 0; i < len; i++) {
        if (isspace((unsigned char)email[i]))
            return 0; // không cho phép khoảng trắng
        if (email[i] == '@' && atPos == -1) atPos = i;
        if (email[i] == '.') dotPos = i;
    }

    if (atPos == -1 || dotPos == -1)
        return 0;                 // phải có @ và .
    if (dotPos < atPos)
        return 0;                // . phải sau @
    if (atPos == 0 || atPos == len - 1)
        return 0;               // @ không ở đầu/cuối
    if (dotPos == len - 1)
        return 0;               // . không ở cuối
    if (dotPos - atPos < 2)
        return 0;               // phải có ký tự giữa @ và .

    return 1;
}

void getValidEmail(char *email, int size) {
    while (1) {
        printf("Email: ");
        fgets(email, size, stdin);
        email[strcspn(email, "\n")] = 0;

        if (isValidEmail(email)) {
            return;
        } else {
            printf(">> Invalid email format! Example: user@gmail.com\n");
        }
    }
}

// ================== CHỌN ROLE ==================
void getRoleMenu() {
    printf("\n===== CHOOSE YOUR ROLE =====\n");
    printf("[1] Admin\n");
    printf("[2] Student\n");
    printf("[3] Teacher\n");
    printf("[0] EXIT\n");
    printf("============================\n");
}

// ================== MENU ==================
void studentMenu() {
    printf("\n**** STUDENT MENU ****\n");
    printf("============================\n");
    printf("[1] SHOW STUDENT LIST\n");
    printf("[2] ADD A NEW STUDENT\n");
    printf("[3] EDIT STUDENT INFORMATION\n");
    printf("[4] REMOVE A STUDENT\n");
    printf("[5] SEARCHING A STUDENT \n");
    printf("[6] SORT OF STUDENT NAME LIST \n");
    printf("[7] EXIT\n");
    printf("============================\n");
}

// ================== HIỂN THỊ ==================
void showStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("-- NO STUDENT ON THE LIST --\n");
        return;
    }
    printf("\n======= STUDENT LIST =======\n");
    printf("======================================================================================================\n");
    printf("|%-5s| %-20s| %-12s| %-8s| %-25s| %-15s|\n",
           "ID", "Name", "DOB", "Gender", "Email", "Phone");
    printf("------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("|%-5d| %-20s| %02d/%02d/%04d  | %-8s| %-25s| %-15s|\n",
               students[i].StudentId,
               students[i].name,
               students[i].dayOfBirth.day,
               students[i].dayOfBirth.month,
               students[i].dayOfBirth.year,
               students[i].gender ? "MALE" : "FEMALE",
               students[i].email,
               students[i].phone);
    }
    printf("======================================================================================================\n");
}

// ================== THÊM ==================
void addStudents(struct Student students[], int *count) {
    if (*count >= MAX) {
        printf("!! Student list is full. Cannot add more.\n");
        return;
    }
    struct Student stu;
    printf("\n--- Enter student information ---\n");

    // ID tự sinh
    stu.StudentId = *count + 1;
    printf(" Student ID: %d\n", stu.StudentId);

    printf("Full name: ");
    fgets(stu.name, sizeof(stu.name), stdin);
    stu.name[strcspn(stu.name, "\n")] = 0;

    stu.dayOfBirth = getValidDate();
    stu.gender = getValidGender();
    getValidEmail(stu.email, sizeof(stu.email));
    getValidPhone(stu.phone, sizeof(stu.phone));

    students[*count] = stu;
    (*count)++;
    printf(">> Student added successfully!\n");
}

// ================== SỬA ==================
void editStudent(struct Student students[], int count) {
    if (count == 0) {
        printf("-- NO STUDENT TO EDIT --\n");
        return;
    }
    int id;
    printf("Enter Student ID to edit: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (students[i].StudentId == id) {
            printf("Editing info for student");
            printf("Student ID: %d\n", students[i].StudentId);
            printf("NAME: %s\n", students[i].name);
            printf("DAY OF BIRTH: %02d|%02d|%04d\n", students[i].dayOfBirth.day,students[i].dayOfBirth.month,students[i].dayOfBirth.year);
            printf("GENDER: %s\n", students[i].gender ? "MALE" : "FEMALE");
            printf("EMAIL: %s\n", students[i].email);
            printf("PHONE: %s\n", students[i].phone);

            printf("New name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            students[i].dayOfBirth = getValidDate();

            students[i].gender = getValidGender();

            getValidEmail(students[i].email, sizeof(students[i].email));

            getValidPhone(students[i].phone, sizeof(students[i].phone));

            printf(">> Student updated successfully!\n");
            return;
        }
    }
    printf("!! Student ID not found !!\n");
}

// ================== XÓA ==================
void removeStudent(struct Student students[], int *count) {
    if (*count == 0) {
        printf("-- NO STUDENT TO REMOVE --\n");
        return;
    }

    int id;
    printf("Enter Student ID to remove: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < *count; i++) {
        if (students[i].StudentId == id) {
            printf("\n>> Found student:\n");
            printf("ID: %d | Name: %s | DOB: %02d/%02d/%04d | Gender: %s | Email: %s | Phone: %s\n",
                   students[i].StudentId,
                   students[i].name,
                   students[i].dayOfBirth.day,
                   students[i].dayOfBirth.month,
                   students[i].dayOfBirth.year,
                   students[i].gender ? "MALE" : "FEMALE",
                   students[i].email,
                   students[i].phone);

            char confirm;
            do {
                printf("Are you sure you want to remove this student? (y/n): ");
                scanf(" %c", &confirm);
                getchar();

                if (confirm == 'y' || confirm == 'Y') {
                    for (int j = i; j < *count - 1; j++) {
                        students[j] = students[j + 1];
                        students[j].StudentId = j + 1;
                    }
                    (*count)--;
                    printf(">> Student removed successfully!\n");
                    return;
                } else if (confirm == 'n' || confirm == 'N') {
                    printf(">> Cancelled remove student!\n");
                    return;
                } else {
                    printf("!! Just Y/N or y/n !!\n");
                }
            } while (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N');

            return;
        }
    }
    printf("!! Student ID not found !!\n");
}

// ================== SẮP XẾP ==================
int compareNames(const char *a, const char *b) {
    char nameA[30], nameB[30];
    strcpy(nameA, a);
    strcpy(nameB, b);
    // chuyển thành chữ thường
    for (int i = 0; nameA[i]; i++) nameA[i] = tolower((unsigned char)nameA[i]);
    for (int i = 0; nameB[i]; i++) nameB[i] = tolower((unsigned char)nameB[i]);

    return strcmp(nameA, nameB);
}

void sortStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("-- NO STUDENT TO SORT --\n");
        return;
    }

    int choice;
    do {
        printf("\n===== SORT MENU =====\n");
        printf("[1] Sort by Name (Ascending A->Z)\n");
        printf("[2] Sort by Name (Descending Z->A)\n");
        printf("[0] Back to Student Menu\n");
        printf("======================\n");
        choice = getValidChoice();

        if (choice == 1) {
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (compareNames(students[i].name, students[j].name) > 0) {
                        struct Student temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            printf("\n>> Student list sorted in Ascending order!\n");
            showStudents(students, count);
        } else if (choice == 2) {
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (compareNames(students[i].name, students[j].name) < 0) {
                        struct Student temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            printf("\n>> Student list sorted in Descending order!\n");
            showStudents(students, count);
        } else if (choice == 0) {
            printf("Back to Student Menu...\n");
        } else {
            printf(">> Invalid choice! Try again.\n");
        }
    } while (choice != 0);
}
// ================== MAIN ==================
int main() {
    int choice;
    struct Student students[MAX];
    int count = 0;
    do {
        getRoleMenu();
        choice = getValidChoice();
        if (choice == 1) {
             int studentChoice;
            do {
                studentMenu();
                studentChoice = getValidChoice();
                switch (studentChoice) {
                    case 1: {
                        showStudents(students, count);
                        break;
                    }
                    case 2: {
                        int cont;
                        do {
                            addStudents(students, &count);
                            printf("\n[1] Add another student\n[0] Back to Student Menu\n");
                            cont = getValidChoice();
                        } while (cont == 1);
                        break;
                    }
                    case 3: {
                        int cont;
                        do {
                            editStudent(students, count);
                            printf("\n[1] Edit another student\n[0] Back to Student Menu\n");
                            cont = getValidChoice();
                        } while (cont == 1);
                        break;
                    }
                    case 4: {
                        int cont;
                        do {
                            removeStudent(students, &count);
                            printf("\n[1] Remove another student\n[0] Back to Student Menu\n");
                            cont = getValidChoice();
                        } while (cont == 1);
                        break;
                    }
                    case 5: {
                        printf(">> Search student.\n");
                        break;
                    }
                    case 6: {
                        sortStudents(students, count);
                        break;
                    }
                    case 7: {
                        printf("Exiting student menu...\n");
                        break;
                    }
                    default:
                        printf("Invalid choice! Try again.\n");
                }
            } while (studentChoice != 7);
        } else if (choice == 2) {
            printf(">> Student menu .\n");
        } else if (choice == 3) {
            printf(">> Teacher menu .\n");
        } else if (choice == 0) {
            printf("Exiting program... BYE BYE!\n");
        } else {
            printf(">> Invalid role! Try again.\n");
        }

    } while (choice != 0);

    return 0;
}
