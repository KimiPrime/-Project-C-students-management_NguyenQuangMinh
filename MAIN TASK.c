#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
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

// ================== HÀM HỖ TRỢ ==================

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
        if (!fgets(phone, size, stdin)) phone[0] = '\0';
        phone[strcspn(phone, "\n")] = 0;

        int len = strlen(phone);
        int valid = 1;
        for (int i = 0; phone[i] != '\0'; i++) {
            if (!isdigit((unsigned char)phone[i])) {
                valid = 0;
                break;
            }
        }
        if (valid && len >= 9 && len <= 11) return;
        printf(">> Invalid phone number! Only digits allowed (9 to 11 chars).\n");
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

// EMAIL
int isValidEmail(const char *email) {
    int atPos = -1, dotPos = -1;
    int len = strlen(email);

    for (int i = 0; i < len; i++) {
        if (isspace((unsigned char)email[i]))
            return 0;
        if (email[i] == '@' && atPos == -1) atPos = i;
        if (email[i] == '.') dotPos = i;
    }

    if (atPos == -1 || dotPos == -1)
        return 0;
    if (dotPos < atPos)
        return 0;
    if (atPos == 0 || atPos == len - 1)
        return 0;
    if (dotPos == len - 1)
        return 0;
    if (dotPos - atPos < 2)
        return 0;

    return 1;
}

void getValidEmail(char *email, int size) {
    while (1) {
        printf("Email: ");
        if (!fgets(email, size, stdin)) email[0] = '\0';
        email[strcspn(email, "\n")] = 0;

        if (isValidEmail(email)) return;
        else printf(">> Invalid email format! Example: username@gmail.com\n");
    }
}

// check chuỗi rỗng
int isEmptyOrSpaces(const char *str) {
    if (strlen(str) == 0) return 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i]))
            return 0;
    }
    return 1;
}

// check trùng email phone
int isDuplicateExcept(struct Student students[], int count, const char *email, const char *phone, int excludeIndex) {
    for (int i = 0; i < count; i++) {
        if (i == excludeIndex) continue;
        if (strlen(email) > 0 && strcmp(students[i].email, email) == 0)
            return 2; // trùng email
        if (strlen(phone) > 0 && strcmp(students[i].phone, phone) == 0)
            return 3; // trùng phone
    }
    return 0;
}

//  id + 1
int getNextId(struct Student students[], int count) {
    int maxId = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].StudentId > maxId) maxId = students[i].StudentId;
    }
    return maxId + 1;
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
    printf("[6] SORT STUDENT LIST\n");
    printf("[7] EXIT\n");
    printf("============================\n");
}
// ================== CHỨC NĂNG =================
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
    stu.StudentId = getNextId(students, *count);
    printf(" Student ID: %d\n", stu.StudentId);

    do {
        printf("Full name: ");
        if (!fgets(stu.name, sizeof(stu.name), stdin)) stu.name[0] = '\0';
        stu.name[strcspn(stu.name, "\n")] = 0;
        if (isEmptyOrSpaces(stu.name)) {
            printf(">> Name cannot be empty!\n");
        } else break;
    } while (1);

    stu.dayOfBirth = getValidDate();
    stu.gender = getValidGender();

    do {
        getValidEmail(stu.email, sizeof(stu.email));
        if (isDuplicateExcept(students, *count, stu.email, "", -1) == 2)
            printf(">> Email already exists!\n");
        else break;
    } while (1);

    do {
        getValidPhone(stu.phone, sizeof(stu.phone));
        if (isDuplicateExcept(students, *count, "", stu.phone, -1) == 3)
            printf(">> Phone already exists!\n");
        else break;
    } while (1);

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
    if (scanf("%d", &id) != 1) {
        char c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf(">> Invalid input!\n");
        return;
    }
    getchar();

    for (int i = 0; i < count; i++) {
        if (students[i].StudentId == id) {
            printf("Editing info for student ID %d\n", students[i].StudentId);

            do {
                printf("New name: ");
                if (!fgets(students[i].name, sizeof(students[i].name), stdin)) students[i].name[0] = '\0';
                students[i].name[strcspn(students[i].name, "\n")] = 0;
                if (isEmptyOrSpaces(students[i].name))
                    printf(">> Name cannot be empty!\n");
                else break;
            } while (1);

            students[i].dayOfBirth = getValidDate();
            students[i].gender = getValidGender();

            do {
                getValidEmail(students[i].email, sizeof(students[i].email));
                if (isDuplicateExcept(students, count, students[i].email, "", i) == 2)
                    printf(">> Email already exists!\n");
                else break;
            } while (1);

            do {
                getValidPhone(students[i].phone, sizeof(students[i].phone));
                if (isDuplicateExcept(students, count, "", students[i].phone, i) == 3)
                    printf(">> Phone already exists!\n");
                else break;
            } while (1);

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
    if (scanf("%d", &id) != 1) {
        char c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf(">> Invalid input!\n");
        return;
    }
    getchar();

    for (int i = 0; i < *count; i++) {
        if (students[i].StudentId == id) {
            char confirm;
            printf("Found student: %s\n", students[i].name);
            do {
                printf("Are you sure you want to remove this student? (y/n): ");
                if (scanf(" %c", &confirm) != 1) {
                    char c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf(">> Invalid input!\n");
                    return;
                }
                getchar();
                if (confirm == 'y' || confirm == 'Y') {
                    for (int j = i; j < *count - 1; j++)
                        students[j] = students[j + 1];
                    (*count)--;
                    printf(">> Student removed successfully!\n");
                    return;
                } else if (confirm == 'n' || confirm == 'N') {
                    printf(">> Cancelled remove student!\n");
                    return;
                }
            } while (1);
        }
    }
    printf("!! Student ID not found !!\n");
}

// ================== TÌM KIẾM ==================
void searchStudentByYear(struct Student students[], int count) {
    if (count == 0) {
        printf("-- NO STUDENT TO SEARCH --\n");
        return;
    }
    int year;
    printf("Enter Student year: ");
    if (scanf("%d", &year) != 1) {
        char c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf(">> Invalid input!\n");
        return;
    }
    getchar();
    int found = 0;
    for (int i = 0; i < count; i++) {
            if (students[i].dayOfBirth.year == year) {
                if (!found) {
                    printf("======================================================================================================\n");
                    printf("|%-5s| %-20s| %-12s| %-8s| %-25s| %-15s|\n",
                           "ID", "Name", "DOB", "Gender", "Email", "Phone");
                    printf("------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-5d| %-20s| %02d/%02d/%04d  | %-8s| %-25s| %-15s|\n",
                       students[i].StudentId,
                       students[i].name,
                       students[i].dayOfBirth.day,
                       students[i].dayOfBirth.month,
                       students[i].dayOfBirth.year,
                       students[i].gender ? "MALE" : "FEMALE",
                       students[i].email,
                       students[i].phone);
                found = 1;
            }
    }
    if (found) {
        printf("======================================================================================================\n");
    } else {
        printf(">> No student found with year of birth: %d\n", year);
    }
}
void searchStudentByName(struct Student students[], int count) {
    if (count == 0) {
        printf("-- NO STUDENT TO SEARCH --\n");
        return;
    }
    char keyword[30];
    printf("Enter student name to search: ");
    if (!fgets(keyword, sizeof(keyword), stdin)) keyword[0] = '\0';
    keyword[strcspn(keyword, "\n")] = 0;

    if (isEmptyOrSpaces(keyword)) {
        printf(">> Search keyword cannot be empty.\n");
        return;
    }
    char lowerKeyword[30];
    strncpy(lowerKeyword, keyword, sizeof(lowerKeyword));
    lowerKeyword[sizeof(lowerKeyword)-1] = '\0';
    for (int i = 0; lowerKeyword[i]; i++)
        lowerKeyword[i] = tolower((unsigned char)lowerKeyword[i]);

    int found = 0;
    for (int i = 0; i < count; i++) {
        char lowerName[30];
        strncpy(lowerName, students[i].name, sizeof(lowerName));
        lowerName[sizeof(lowerName)-1] = '\0';
        for (int j = 0; lowerName[j]; j++)
            lowerName[j] = tolower((unsigned char)lowerName[j]);

        if (strstr(lowerName, lowerKeyword) != NULL) {
            if (!found) {
                printf("======================================================================================================\n");
                printf("|%-5s| %-20s| %-12s| %-8s| %-25s| %-15s|\n",
                       "ID", "Name", "DOB", "Gender", "Email", "Phone");
                printf("------------------------------------------------------------------------------------------------------\n");
            }
            printf("|%-5d| %-20s| %02d/%02d/%04d  | %-8s| %-25s| %-15s|\n",
                   students[i].StudentId,
                   students[i].name,
                   students[i].dayOfBirth.day,
                   students[i].dayOfBirth.month,
                   students[i].dayOfBirth.year,
                   students[i].gender ? "MALE" : "FEMALE",
                   students[i].email,
                   students[i].phone);
            found = 1;
        }
    }

    if (found) {
        printf("======================================================================================================\n");
    } else {
        printf(">> No student found with name: '%s'\n", keyword);
    }
}

// ================== SẮP XẾP ==================
int compareNames(const char *a, const char *b) {
    char nameA[30], nameB[30];
    strncpy(nameA, a, sizeof(nameA)); nameA[sizeof(nameA)-1] = '\0';
    strncpy(nameB, b, sizeof(nameB)); nameB[sizeof(nameB)-1] = '\0';
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
        printf("[1] Sort by Name (A->Z)\n");
        printf("[2] Sort by Name (Z->A)\n");
        printf("[3] Sort by ID (Ascending)\n");
        printf("[4] Sort by ID (Descending)\n");
        printf("[0] Back\n");
        choice = getValidChoice();
        if (choice == 1) {
            for (int i=0;i<count-1;i++)
                for (int j=i+1;j<count;j++)
                    if (compareNames(students[i].name,students[j].name)>0) {
                        struct Student tmp=students[i]; students[i]=students[j]; students[j]=tmp;
                    }
            printf(">> Sorted by Name ASC!\n");
        } else if (choice == 2) {
            for (int i=0;i<count-1;i++)
                for (int j=i+1;j<count;j++)
                    if (compareNames(students[i].name,students[j].name)<0) {
                        struct Student tmp=students[i]; students[i]=students[j]; students[j]=tmp;
                    }
            printf(">> Sorted by Name DESC!\n");
        } else if (choice == 3) {
            for (int i=0;i<count-1;i++)
                for (int j=i+1;j<count;j++)
                    if (students[i].StudentId > students[j].StudentId) {
                        struct Student tmp=students[i]; students[i]=students[j]; students[j]=tmp;
                    }
            printf(">> Sorted by ID ASC!\n");
        } else if (choice == 4) {
            for (int i=0;i<count-1;i++)
                for (int j=i+1;j<count;j++)
                    if (students[i].StudentId < students[j].StudentId) {
                        struct Student tmp=students[i]; students[i]=students[j]; students[j]=tmp;
                    }
            printf(">> Sorted by ID DESC!\n");
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
                        int searchChoice;
                        do {
                            printf("\n===== SEARCH MENU =====\n");
                            printf("[1] Search by Name\n");
                            printf("[2] Search by Year of Birth\n");
                            printf("[0] Back\n");
                            searchChoice = getValidChoice();

                            if (searchChoice == 1) {
                                searchStudentByName(students, count);
                            } else if (searchChoice == 2) {
                                searchStudentByYear(students, count);
                            }
                        } while (searchChoice != 0);
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
