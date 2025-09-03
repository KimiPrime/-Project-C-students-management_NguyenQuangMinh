#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

// Sinh viên
struct Student {
    int StudentId;
    char name[30];
    bool gender;
    char email[30];
    char phone[20];
};

// Check ID có phải là 1 số nếu không thì nhót
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
    printf("CHOOSE YOUR OPTION (1-5): ");
}

// ================= Hiển thị danh sách =================
void showStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("-- NO STUDENT ON THE LIST --\n");
        return;
    }
    printf("\n======= STUDENT LIST =======\n");
    printf("%-5s %-20s %-8s %-25s %-15s\n",
           "ID", "Name", "Gender", "Email", "Phone");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-8s %-25s %-15s\n",
               students[i].StudentId,
               students[i].name,
               students[i].gender ? "MALE" : "FEMALE",
               students[i].email,
               students[i].phone);
    }
    printf("===============================\n");
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
    int gen;
    printf("Gender (1=Male, 0=Female): ");
    scanf("%d", &gen);
    stu.gender = (gen == 1);
    getchar();

    // 4. Email
    printf("Email: ");
    fgets(stu.email, sizeof(stu.email), stdin);
    stu.email[strcspn(stu.email, "\n")] = 0;

    // 5. Điện thoại
    printf("Phone number: ");
    fgets(stu.phone, sizeof(stu.phone), stdin);
    stu.phone[strcspn(stu.phone, "\n")] = 0;

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

    int id;
    printf("Enter Student ID to edit: ");
    id = getValidId();  // dùng lại hàm nhập ID hợp lệ

    for (int i = 0; i < count; i++) {
        if (students[i].StudentId == id) {
            printf("Editing info for student: %s\n", students[i].name);

            printf("New name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            int gen;
            printf("New Gender (1=Male, 0=Female): ");
            scanf("%d", &gen);
            students[i].gender = (gen == 1);
            getchar();

            printf("New Email: ");
            fgets(students[i].email, sizeof(students[i].email), stdin);
            students[i].email[strcspn(students[i].email, "\n")] = 0;

            printf("New Phone: ");
            fgets(students[i].phone, sizeof(students[i].phone), stdin);
            students[i].phone[strcspn(students[i].phone, "\n")] = 0;

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

    int id;
    printf("Enter Student ID to remove: ");
    id = getValidId();   // cũng dùng hàm nhập ID hợp lệ

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
        choice = getValidId();  // cũng tận dụng cho menu

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
