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
    char password[20];
};
struct Classroom {
    int classroomId;
    char teacherId;
    char classroomName[30];
    struct Student students[];
};
struct Teacher {
    int TeacherId;
    char name[30];
    struct Date dayOfBirth;
    bool gender;
    char email[30];
    char phone[20];
    char password[20];
    struct Classroom classrooms;
};
// ================== HÀM NHẬP ==================
// kiểm tra các phần nhập có đúng với yêu cầu
// id
int getValidId() {
    int id;
    char c;
    while (1) {
        printf("Student ID: ");
        if (scanf("%d", &id) == 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            return id;
        } else {
            printf(">> Invalid input! ID must be a number.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}
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
    printf("[5] SEARCHING A STUDENT\n");
    printf("[6] SORT OF STUDENT NAME LIST (A-Z)\n");
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
        printf("|%-5d| %-20s| %02d/%02d/%04d | %-8s| %-25s| %-15s|\n",
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

// ================== SẮP XẾP ==================
void sortStudents(struct Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (students[i].StudentId > students[j].StudentId) {
                struct Student tmp = students[i];
                students[i] = students[j];
                students[j] = tmp;
            }
        }
    }
}

// ================== THÊM ==================
void addStudents(struct Student students[], int *count) {
    if (*count >= MAX) {
        printf("!! Student list is full. Cannot add more.\n");
        return;
    }
    struct Student stu;
    printf("\n--- Enter student information ---\n");

    stu.StudentId = getValidId();
    for (int i = 0; i < *count; i++) {
        if (students[i].StudentId == stu.StudentId) {
            printf("!! Student ID already exists.\n");
            return;
        }
    }
    printf("Full name: ");
    fgets(stu.name, sizeof(stu.name), stdin);
    stu.name[strcspn(stu.name, "\n")] = 0;

    stu.dayOfBirth = getValidDate();
    stu.gender = getValidGender();

    printf("Email: ");
    fgets(stu.email, sizeof(stu.email), stdin);
    stu.email[strcspn(stu.email, "\n")] = 0;

    getValidPhone(stu.phone, sizeof(stu.phone));

    students[*count] = stu;
    (*count)++;
    sortStudents(students, *count);
    printf(">> Student added successfully!\n");
}

// ================== SỬA ==================
void editStudent(struct Student students[], int count) {
    if (count == 0) {
        printf("-- NO STUDENT TO EDIT --\n");
        return;
    }
    int id = getValidId();
    for (int i = 0; i < count; i++) {
        if (students[i].StudentId == id) {
            printf("Editing info for student: %s\n", students[i].name);

            int newId = getValidId();
            for (int j = 0; j < count; j++) {
                if (j != i && students[j].StudentId == newId) {
                    printf("!! New ID already exists. Update cancelled.\n");
                    return;
                }
            }
            students[i].StudentId = newId;

            printf("New name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            students[i].dayOfBirth = getValidDate();
            students[i].gender = getValidGender();

            printf("New Email: ");
            fgets(students[i].email, sizeof(students[i].email), stdin);
            students[i].email[strcspn(students[i].email, "\n")] = 0;

            getValidPhone(students[i].phone, sizeof(students[i].phone));
            sortStudents(students, count);
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
    int id = getValidId();
    for (int i = 0; i < *count; i++) {
        if (students[i].StudentId == id) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf(">> Student removed successfully!\n");
            return;
        }
    }
    printf("!! Student ID not found !!\n");
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
            printf(">> Admin menu .\n");
        } else if (choice == 2) {
            // STUDENT MENU
            int studentChoice;
            do {
                studentMenu();
                studentChoice = getValidChoice();
                switch (studentChoice) {
                    case 1: showStudents(students, count);
                        break;
                    case 2: addStudents(students, &count);
                        break;
                    case 3: editStudent(students, count);
                        break;
                    case 4: removeStudent(students, &count);
                        break;
                    case 5: printf("Exiting student menu...\n");
                        break;
                    default: printf("Invalid choice! Try again.\n");
                }
            } while (studentChoice != 5);
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
