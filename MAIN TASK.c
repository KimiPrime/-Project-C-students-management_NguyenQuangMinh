#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 100

// ================== STRUCT ==================
struct Date {
    int day, month, year;
};

struct Student {
    int StudentId;
    char name[30];
    struct Date birth;
    bool gender;
    char email[30];
    char phone[20];
};
struct Classroom{
char classroomId[10];
char teacherId[10];
char classroomName[10];

};
struct Teacher {
    int TeacherId;
    char name[30];
    struct Date birth;
    bool gender;
    char email[30];
    char phone[20];
};

// ================== HÀM HỖ TRỢ ==================
int getValidChoice(int min, int max) {
    int choice;
    char c;
    while (1) {
        if (scanf("%d%c", &choice, &c) != 2 || c != '\n') {
            while (getchar() != '\n');
            printf("Invalid choice. Enter again: ");
        } else if (choice < min || choice > max) {
            printf("Choice must be between %d and %d: ", min, max);
        } else {
            return choice;
        }
    }
}

struct Date getValidDate() {
    struct Date d;
    while (1) {
        printf("Enter DOB (dd mm yyyy): ");
        if (scanf("%d %d %d", &d.day, &d.month, &d.year) == 3 &&
            d.day >= 1 && d.day <= 31 &&
            d.month >= 1 && d.month <= 12 &&
            d.year >= 1900 && d.year <= 2100) {
            getchar();
            return d;
        } else {
            printf("Invalid date!\n");
            while (getchar() != '\n');
        }
    }
}

bool getValidGender() {
    int g;
    printf("Gender (1=Male, 0=Female): ");
    g = getValidChoice(0, 1);
    return g == 1;
}

void getValidEmail(char *email) {
    while (1) {
        printf("Enter Email: ");
        fgets(email, 30, stdin);
        email[strcspn(email, "\n")] = 0;
        if (strchr(email, '@') && strchr(email, '.')) break;
        printf("Invalid email!\n");
    }
}

void getValidPhone(char *phone) {
    while (1) {
        printf("Enter Phone: ");
        fgets(phone, 20, stdin);
        phone[strcspn(phone, "\n")] = 0;
        int valid = 1;
        for (int i = 0; i < strlen(phone); i++) {
            if (!isdigit(phone[i])) valid = 0;
        }
        if (valid && strlen(phone) >= 9 && strlen(phone) <= 11) break;
        printf("Invalid phone!\n");
    }
}

int getNextIdStu(struct Student students[], int count) {
    int max = 0;
    for (int i = 0; i < count; i++)
        if (students[i].StudentId > max) max = students[i].StudentId;
    return max + 1;
}
// id tự sin của iaso viên
int getNextIdTea(struct Teacher teachers[], int count) {
    int max = 0;
    for (int i = 0; i < count; i++)
        if (teachers[i].TeacherId > max) max = teachers[i].TeacherId;
    return max + 1;
}
//chu hoa chu thuong
int compareNames(const char *a, const char *b) {
    char nameA[30], nameB[30];
    strcpy(nameA, a);
    strcpy(nameB, b);
    for (int i = 0; nameA[i]; i++) nameA[i] = tolower(nameA[i]);
    for (int i = 0; nameB[i]; i++) nameB[i] = tolower(nameB[i]);
    return strcmp(nameA, nameB);
}
//  trùng email và sdt
bool isEmailDuplicateStu(struct Student students[], int count, const char *email) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].email, email) == 0) {
            return true; // trùng nhót
        }
    }
    return false;
}

bool isPhoneDuplicateStu(struct Student students[], int count, const char *phone) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].phone, phone) == 0) {
            return true;
        }
    }
    return false;
}

bool isEmailDuplicateTea(struct Teacher teachers[], int count, const char *email) {
    for (int i = 0; i < count; i++) {
        if (strcmp(teachers[i].email, email) == 0) {
            return true;
        }
    }
    return false;
}

bool isPhoneDuplicateTea(struct Teacher teachers[], int count, const char *phone) {
    for (int i = 0; i < count; i++) {
        if (strcmp(teachers[i].phone, phone) == 0) {
            return true;
        }
    }
    return false;
}
// check trống
bool isEmptyOrSpaces(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isspace((unsigned char)str[i])) return false;
    }
    return true;
}

// ================== STUDENT FUNCTIONS ==================
void showStudents(struct Student students[], int count) {
    if (count ==0) {
        printf("No Student found!\n");
        return;
    }
    printf("======================================================================================================\n");
    printf("\n| %-5s| %-20s| %-10s| %-8s| %-25s| %-12s|\n ",
           "ID", "Name", "DOB", "Gender", "Email", "Phone");
    printf("------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("| %-5d| %-20s| %02d/%02d/%04d| %-8s| %-25s| %-12s|\n",
               students[i].StudentId,
               students[i].name,
               students[i].birth.day,
               students[i].birth.month,
               students[i].birth.year,
               students[i].gender ? "Male" : "Female",
               students[i].email, students[i].phone);
    }
}
void addStudents(struct Student students[], int *count) {
    struct Student s;
    s.StudentId = getNextIdStu(students, *count);
    printf("\n>>> Add New Student\n");
    printf("ID: %d\n", s.StudentId);
    printf("Enter Name: ");
    fgets(s.name, 30, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    s.birth = getValidDate();
    s.gender = getValidGender();
    do {
        getValidEmail(s.email);
        if (isEmailDuplicateStu(students, *count, s.email)) {
            printf("This email already exists! Please enter again.\n");
        } else break;
    } while (1);
    do {
        getValidPhone(s.phone);
        if (isPhoneDuplicateStu(students, *count, s.phone)) {
            printf("This phone number already exists! Please enter again.\n");
        } else break;
    } while (1);

    students[*count] = s;
    (*count)++;
    printf("Student added successfully!\n");
}

void editStudent(struct Student students[], int count) {
    int id;
    printf("Enter Student ID to edit: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < count; i++) {
        if (students[i].StudentId == id) {
            printf("Editing Student %d\n", id);
            printf("Enter new name: ");
            fgets(students[i].name, 30, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;
            students[i].birth = getValidDate();
            students[i].gender = getValidGender();
            getValidEmail(students[i].email);
            getValidPhone(students[i].phone);
            printf("Edited successfully!\n");
            return;
        }
    }
    printf("Not found!\n");
}

void removeStudent(struct Student students[], int *count) {
    int id;
    printf("Enter Student ID to remove: ");
    scanf("%d", &id); getchar();
    for (int i = 0; i < *count; i++) {
        if (students[i].StudentId == id) {
            for (int j = i; j < *count - 1; j++)
                students[j] = students[j + 1];
            (*count)--;
            printf("Removed successfully!\n");
            return;
        }
    }
    printf("Not found!\n");
}
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
            if (students[i].birth.year == year) {
                if (!found) {
                    printf("======================================================================================================\n");
                    printf("|%-5s| %-20s| %-12s| %-8s| %-25s| %-15s|\n",
                           "ID", "Name", "DOB", "Gender", "Email", "Phone");
                    printf("------------------------------------------------------------------------------------------------------\n");
                }
                printf("|%-5d| %-20s| %02d/%02d/%04d  | %-8s| %-25s| %-15s|\n",
                       students[i].StudentId,
                       students[i].name,
                       students[i].birth.day,
                       students[i].birth.month,
                       students[i].birth.year,
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
                   students[i].birth.day,
                   students[i].birth.month,
                   students[i].birth.year,
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
        choice = getValidChoice(0, 4);
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
//======================================================================================================
// ================== TEACHER FUNCTIONS ==================
void showTeachers(struct Teacher teachers[], int count) {
    if (count==0) {
        printf("No Teacher found!\n");
        return;
    }
    printf("\n======= TEACHER LIST =======\n");
    printf("======================================================================================================\n");
    printf("\n| %-5s| %-20s| %-10s| %-8s| %-25s| %-12s|\n",
           "ID", "Name", "DOB", "Gender", "Email", "Phone");
    printf("------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("|%-5d| %-20s| %02d/%02d/%04d| %-8s| %-25s| %-12s|\n",
               teachers[i].TeacherId,
               teachers[i].name,
               teachers[i].birth.day,
               teachers[i].birth.month,
               teachers[i].birth.year,
               teachers[i].gender ? "Male" : "Female",
               teachers[i].email,
               teachers[i].phone);
    }
    printf("======================================================================================================\n");
}
void addTeacher(struct Teacher teachers[], int *count) {
    struct Teacher t;
    t.TeacherId = getNextIdTea(teachers, *count);
    printf("\n>>> Add New Teacher\n");
    printf("ID: %d\n", t.TeacherId);
    printf("Enter Name: ");
    fgets(t.name, 30, stdin);
    t.name[strcspn(t.name, "\n")] = 0;
    t.birth = getValidDate();
    t.gender = getValidGender();
    do {
        getValidEmail(t.email);
        if (isEmailDuplicateTea(teachers, *count, t.email)) {
            printf("This email already exists! Please enter again.\n");
        } else break;
    } while (1);
    do {
        getValidPhone(t.phone);
        if (isPhoneDuplicateTea(teachers, *count, t.phone)) {
            printf("This phone number already exists! Please enter again.\n");
        } else break;
    } while (1);

    teachers[*count] = t;
    (*count)++;
    printf("Teacher added successfully!\n");
}
// ================== MENU ==================
void studentMenu(struct Student students[], int *stuCount) {
    int choice;
    do {
        printf("\n===== STUDENT MENU =====\n");
        printf("1. Show Students\n");
        printf("2. Add Student\n");
        printf("3. Edit Student\n");
        printf("4. Remove Student\n");
        printf("5. Search Student\n");
        printf("6. Sort Students\n");
        printf("0. Back\n");
        choice = getValidChoice(0, 6);
        switch (choice) {
            case 1:
                showStudents(students, *stuCount);
                break;
            case 2: {
                int again;
                do {
                    addStudents(students, stuCount);
                    printf("\n[1] Add another student\n[0] Back\n");
                    again = getValidChoice(0, 1);
                } while (again == 1);
                break;
            }
            case 3: {
                int again;
                do {
                    editStudent(students, *stuCount);
                    printf("\n[1] Edit another student\n[0] Back\n");
                    again = getValidChoice(0, 1);
                } while (again == 1);
                break;
            }
            case 4: {
                int again;
                do {
                    removeStudent(students, stuCount);
                    printf("\n[1] Remove another student\n[0] Back\n");
                    again = getValidChoice(0, 1);
                } while (again == 1);
                break;
            }
            case 5: {
                int sc;
                printf("1. Search by Name\n2. Search by Year\n");
                sc = getValidChoice(1, 2);
                if (sc == 1) searchStudentByName(students, *stuCount);
                else searchStudentByYear(students, *stuCount);
                break;
            }
            case 6:
                sortStudents(students, *stuCount);
                break;
        }
    } while (choice != 0);
}

void teacherMenu(struct Teacher teachers[], int *teaCount) {
    int choice;
    do {
        printf("\n===== TEACHER MENU =====\n");
        printf("1. Show Teachers\n2. Add Teacher\n3. Edit Teacher\n4. Remove Teacher\n5. Search Teacher\n6. Sort Teachers\n0. Back\n");
        choice = getValidChoice(0, 6);
        switch (choice) {
            case 1: showTeachers(teachers, *teaCount);
                break;
            case 2:
                int again;
                do {
                    addTeacher(teachers, teaCount);
                    printf("\n[1] Add another Teacher\n[0] Back\n");
                    again = getValidChoice(0, 1);
                }while (again ==1);
                break;

        }
    } while (choice != 0);
}

void adminMenu(struct Student students[], int *stuCount, struct Teacher teachers[], int *teaCount) {
    int choice;
    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Manage Students\n2. Manage Teachers\n0. Back\n");
        choice = getValidChoice(0, 2);
        if
        (choice == 1) studentMenu(students, stuCount);
        else if
        (choice == 2) teacherMenu(teachers, teaCount);
    } while (choice != 0);
}

int main() {
    struct Student students[MAX];
    struct Teacher teachers[MAX];
    int stuCount = 0, teaCount = 0;
    int choice;
    do {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Admin\n2. Student Role\n3. Teacher Role\n0. Exit\n");
        choice = getValidChoice(0, 3);
        if
        (choice == 1) adminMenu(students, &stuCount, teachers, &teaCount);
        else if
        (choice == 2) printf(">> Student role menu here.\n");
        else if
        (choice == 3) printf(">> Teacher role menu here.\n");
    } while (choice != 0);
    return 0;
}
