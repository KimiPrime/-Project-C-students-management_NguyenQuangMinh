#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

// Ngày sinh
struct Date {
    int day, month, year;
};

// Sinh viên
struct Student {
    int StudentId;
    char name[30];
    struct Date dateOfBirth;
    bool gender;
    char email[30];
    char phone[20];
};

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
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | DOB: %02d/%02d/%04d | Gender: %s | Email: %s | Phone: %s\n",
               students[i].StudentId,
               students[i].name,
               students[i].dateOfBirth.day,
               students[i].dateOfBirth.month,
               students[i].dateOfBirth.year,
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
    printf("Student ID: ");
    scanf("%d", &stu.StudentId);
    getchar();
    for (int i = 0; i < *count; i++) {
        if (students[i].StudentId == stu.StudentId) {
            printf(" Student ID already exists.\n");
            return;
        }
    }
    // 2. Tên
    printf("Full name: ");
    fgets(stu.name, sizeof(stu.name), stdin);
    stu.name[strcspn(stu.name, "\n")] = 0;

    // 3. Ngày sinh
    printf("Date of Birth (dd mm yyyy): ");
    scanf("%d %d %d", &stu.dateOfBirth.day, &stu.dateOfBirth.month, &stu.dateOfBirth.year);

    // 4. Giới tính
    int gen;
    printf("Gender (1=Male, 0=Female): ");
    scanf("%d", &gen);
    stu.gender = (gen == 1);
    getchar();

    // 5. Email
    printf("Email: ");
    fgets(stu.email, sizeof(stu.email), stdin);
    stu.email[strcspn(stu.email, "\n")] = 0;

    // 6. Điện thoại
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
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (students[i].StudentId == id) {
            printf("Editing info for student: %s\n", students[i].name);

            printf("New name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            printf("New DOB (dd mm yyyy): ");
            scanf("%d %d %d", &students[i].dateOfBirth.day,
                              &students[i].dateOfBirth.month,
                              &students[i].dateOfBirth.year);

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
    scanf("%d", &id);

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

// ================= Main =================
int main() {
    int choice;
    struct Student students[MAX];
    int count = 0;

    do {
        studentMenu();
        scanf("%d", &choice);
        getchar(); // xóa \n

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
