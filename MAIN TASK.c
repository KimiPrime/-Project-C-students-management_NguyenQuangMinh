#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>   // để dùng isdigit check số nhập vào có phải là số đt
#define MAX 100

// Sinh viên
struct Student {
    int StudentId;
    char name[30];
    bool gender;
    char email[30];
    char phone[20];
};

// ================= Nhập ID hợp lệ (chỉ số) =================
int getValidId() {
    int id;
    char c;
    while (1) {
        printf("Student ID: ");
        if (scanf("%d", &id) == 1) {  // nhập đúng số
            while ((c = getchar()) != '\n' && c != EOF); // xóa bộ đệm
            return id;
        } else {
            printf(">> Invalid input! ID must be a number.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

// ================= Nhập lựa chọn menu hợp lệ =================
int getValidChoice() {
    int choice;
    char c;
    while (1) {
        printf("Choose your option (1-5): ");
        if (scanf("%d", &choice) == 1) {
            while ((c = getchar()) != '\n' && c != EOF); // clear buffer
            return choice;
        } else {
            printf(">> Invalid input! Choice must be a number.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

// ================= Nhập giới tính hợp lệ =================
bool getValidGender() {
    int gen;
    char c;
    while (1) {
        printf("Gender (1=Male, 0=Female): ");
        if (scanf("%d", &gen) == 1 && (gen == 0 || gen == 1)) {
            while ((c = getchar()) != '\n' && c != EOF); // clear buffer
            return gen == 1;
        } else {
            printf(">> Invalid input! Please enter 1 for Male or 0 for Female.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

// ================= Nhập số điện thoại hợp lệ =================
void getValidPhone(char *phone, int size) {
    while (1) {
        printf("Phone number: ");
        fgets(phone, size, stdin);
        phone[strcspn(phone, "\n")] = 0;  // xóa \n

        int valid = 1;
        for (int i = 0; phone[i] != '\0'; i++) {
            if (!isdigit((unsigned char)phone[i])) {  // nếu không phải số
                valid = 0;
                break;
            }
        }

        if (valid && strlen(phone) > 0) return;  // hợp lệ thì thoát
        printf(">> Invalid phone number! Only digits allowed.\n");
    }
}

// ================= Menu =================
void studentMenu() {
    printf("\n**** STUDENT MENU ****\n");
    printf("============================\n");
    printf("[1] SHOW STUDENT LIST\n");
    printf("[2] ADD A NEW STUDENT\n");
    printf("[3] EDIT STUDENT INFORMATION\n");
    printf("[4] REMOVE A STUDENT\n");
    printf("[5] EXIT\n");
    printf("============================\n");
}

// ================= Hiển thị danh sách =================
void showStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("-- NO STUDENT ON THE LIST --\n");
        return;
    }
    printf("\n======= STUDENT LIST =======\n");
    printf("====================================================================================\n");
    printf("|%-5s| %-20s| %-8s| %-25s| %-15s|\n",
           "ID", "Name", "Gender", "Email", "Phone");
    printf("------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("|%-5d| %-20s| %-8s| %-25s| %-15s|\n",
               students[i].StudentId,
               students[i].name,
               students[i].gender ? "MALE" : "FEMALE",
               students[i].email,
               students[i].phone);
    }
    printf("====================================================================================\n");
}

// ================= Thêm sinh viên =================
void addStudents(struct Student students[], int *count) {
    if (*count >= MAX) {
        printf("!! Student list is full. Cannot add more.\n");
        return;
    }
    struct Student stu;

    printf("\n--- Enter student information ---\n");
    // 1. ID
    stu.StudentId = getValidId();   // dùng hàm nhập ID hợp lệ

    for (int i = 0; i < *count; i++) {
        if (students[i].StudentId == stu.StudentId) {
            printf("!! Student ID already exists.\n");
            return;
        }
    }

    // 2. Tên
    printf("Full name: ");
    fgets(stu.name, sizeof(stu.name), stdin);
    stu.name[strcspn(stu.name, "\n")] = 0;

    // 3. Giới tính
    stu.gender = getValidGender();

    // 4. Email
    printf("Email: ");
    fgets(stu.email, sizeof(stu.email), stdin);
    stu.email[strcspn(stu.email, "\n")] = 0;

    // 5. Điện thoại (chỉ số)
    getValidPhone(stu.phone, sizeof(stu.phone));

    // Thêm vào danh sách
    students[*count] = stu;
    (*count)++;
    printf(">> Student added successfully!\n");
}

// ================= Sửa sinh viên =================
void editStudent(struct Student students[], int count) {
    if (count == 0) {
        printf("-- NO STUDENT TO EDIT --\n");
        return;
    }

    int id = getValidId();  // dùng lại hàm nhập ID hợp lệ

    for (int i = 0; i < count; i++) {
        if (students[i].StudentId == id) {
            printf("Editing info for student: %s\n", students[i].name);

            printf("New name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            students[i].gender = getValidGender();

            printf("New Email: ");
            fgets(students[i].email, sizeof(students[i].email), stdin);
            students[i].email[strcspn(students[i].email, "\n")] = 0;

            getValidPhone(students[i].phone, sizeof(students[i].phone));

            printf(">> Student updated successfully!\n");
            return;
        }
    }
    printf("!! Student ID not found !!\n");
}

// ================= Xóa sinh viên =================
void removeStudent(struct Student students[], int *count) {
    if (*count == 0) {
        printf("-- NO STUDENT TO REMOVE --\n");
        return;
    }

    int id = getValidId();   // cũng dùng hàm nhập ID hợp lệ

    for (int i = 0; i < *count; i++) {
        if (students[i].StudentId == id) {
            // Dịch phần tử phía sau lên
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

int main() {
    int choice;
    struct Student students[MAX];
    int count = 0;

    do {
        studentMenu();
        choice = getValidChoice();  // sử dụng hàm mới

        switch (choice) {
            case 1:
                showStudents(students, count);
                break;
            case 2:
                addStudents(students, &count);
                break;
            case 3:
                editStudent(students, count);
                break;
            case 4:
                removeStudent(students, &count);
                break;
            case 5:
                printf("Exiting program... BYE BYE!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
