    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <ctype.h>
#include  <stdlib.h>
    #define MAX 100

    // ================== STRUCT ==================
    struct Date {
        int day, month, year;
    };

    struct Student {
        int StudentId;
        int classroomId;
        char name[30];
        struct Date birth;
        bool gender;
        char email[30];
        char phone[20];
    };
    struct Classroom{
    int classroomId;
    int teacherId;
    char classroomName[50];
        struct Student student[MAX];
        int stuCount;

    };
    struct Teacher {
        int TeacherId;
        char name[30];
        struct Date birth;
        bool gender;
        char email[30];
        char phone[20];
        struct  Classroom classroom;
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
    int isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    int getDaysInMonth(int month, int year) {
        switch (month) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                return 31;
            case 4: case 6: case 9: case 11:
                return 30;
            case 2:
                return isLeapYear(year) ? 29 : 28;
            default:
                return 0;
        }
    }
    struct Date getValidDate() {
        struct Date d;
        while (1) {
            printf("Enter DOB (dd mm yyyy): ");
            if (scanf("%d %d %d", &d.day, &d.month, &d.year) == 3 &&
                d.month >= 1 && d.month <= 12 &&
                d.year >= 1900 && d.year <= 2100 &&
                d.day >= 1 && d.day <= getDaysInMonth(d.month, d.year)) {
                while (getchar() != '\n');
                return d;
                } else {
                    printf("Invalid date! Please try again.\n");
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
            int len = strlen(phone);
            int valid = 1;
            if (len != 10) {
                valid = 0;
            }
            else if (phone[0] != '0') {
                valid = 0;
            }
            else {
                for (int i = 0; i < len; i++) {
                    if (!isdigit((unsigned char)phone[i])) {
                        valid = 0;
                        break;
                    }
                }
            }
            if (valid)
                break;
            printf("Invalid phone! Must be 10 digits and start with 0 and no space between the numbers.\n");
        }
    }

    int getNextIdStu(struct Student students[], int count) {
        int max = 0;
        for (int i = 0; i < count; i++)
            if (students[i].StudentId > max) max = students[i].StudentId;
        return max + 1;
    }
    // id tự sin của giáo viên
    int getNextIdTea(struct Teacher teachers[], int count) {
        int max = 0;
        for (int i = 0; i < count; i++)
            if (teachers[i].TeacherId > max) max = teachers[i].TeacherId;
        return max + 1;
    }
int getNextIdClass(struct Classroom classrooms[], int count) {
        int max = 0;
        for (int i = 0; i < count; i++)
            if (classrooms[i].classroomId > max) max = classrooms[i].classroomId;
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
int teacherExists(struct Teacher teachers[], int teaCount, int id) {
        for (int i = 0; i < teaCount; i++) {
            if (teachers[i].TeacherId == id) return 1;
        }
        return 0;
    }

int teacherAlreadyAssigned(struct Classroom classrooms[], int classCount, int id) {
        for (int i = 0; i < classCount; i++) {
            if (classrooms[i].teacherId == id) return 1;
        }
        return 0;
    }
int inputInteger(const char *msg) {
        char buffer[100];
        int value;
        int valid;

        while (1) {
            printf("%s", msg);
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                valid = 1;
                for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
                    if (!isdigit(buffer[i])) {   // nếu gặp ký tự không phải số
                        valid = 0;
                        break;
                    }
                }

                if (valid) {
                    value = atoi(buffer); // đổi chuỗi sang số nguyên
                    return value;
                }
            }
            printf(" Invalid input! Please enter a number.\n");
        }
    }
int getValidTeacherId(struct Teacher teachers[], int teacherCount,
                      struct Classroom classrooms[], int classCount) {
        int id;

        while (1) {
            printf("Enter Teacher ID: ");
            if (scanf("%d", &id) != 1) {
                printf(" Invalid input! Please enter a number.\n");
                while (getchar() != '\n');
                break;
            }

            if (!teacherExists(teachers, teacherCount, id)) {
                printf(" Teacher ID does not exist. Try again!\n");
                break;
            }

            if (teacherAlreadyAssigned(classrooms, classCount, id)) {
                printf(" Teacher is already assigned to another classroom!\n");
                break;
            }

            return id; // hợp lệ thì thoát vòng lặp
        }
    }


    // ================== STUDENT FUNCTIONS ==================
    void showStudents(struct Student students[], int count) {
        if (count ==0) {
            printf("No Student found!\n");
            return;
        }
        printf("========== STUDENT LIST ==========\n");
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
            int choice;
            do {
                printf("\n===== EDIT STUDENT %d =====\n", id);
                printf("[1] Edit Name\n");
                printf("[2] Edit Date of Birth\n");
                printf("[3] Edit Gender\n");
                printf("[4] Edit Email\n");
                printf("[5] Edit Phone\n");
                printf("[0] Back\n");
                choice = getValidChoice(0, 5);

                switch (choice) {
                    case 1:
                        printf("Old Name: ");
                        printf("%s\n",students[i].name);
                        printf("Enter new name: ");
                        fgets(students[i].name, 30, stdin);
                        students[i].name[strcspn(students[i].name, "\n")] = 0;
                        printf(">> Name updated!\n");
                        break;
                    case 2:
                        printf("Old Date of Birth: ");
                        printf("%d %d %d\n",students[i].birth.day, students[i].birth.month,students[i].birth.year);
                        students[i].birth = getValidDate();
                        printf(">> DOB updated!\n");
                        break;
                    case 3:
                        printf("Old Gender: ");
                        printf("%d\n",students[i].gender);
                        printf("\n");
                        students[i].gender = getValidGender();
                        printf(">> Gender updated!\n");
                        break;
                    case 4:
                        printf("Old Email: ");
                        printf("%s\n",students[i].email);
                        char newEmail[30];
                        do {
                            getValidEmail(newEmail);
                            int dup = 0;
                            for (int j = 0; j < count; j++) {
                                if (j == i) continue; // bỏ qua chính nó
                                if (strcmp(students[j].email, newEmail) == 0) {
                                    dup = 1;
                                    break;
                                }
                            }
                            if (dup) {
                                printf("This email already exists! Please enter again.\n");
                            } else break;
                        } while (1);
                        strcpy(students[i].email, newEmail);
                        printf(">> Email updated!\n");
                    case 5:
                        printf("Old Phone: ");
                        printf("%s\n",students[i].phone);
                        char newPhone[15];
                        do {
                            getValidPhone(newPhone);
                            int dup = 0;
                            for (int j = 0; j < count; j++) {
                                if (j == i) continue; // bỏ qua chính student đang sửa
                                if (strcmp(students[j].phone, newPhone) == 0) {
                                    dup = 1;
                                    break;
                                }
                            }
                            if (dup) {
                                printf("This phone number already exists! Please enter again.\n");
                            } else break;
                        } while (1);
                        strcpy(students[i].phone, newPhone);
                        printf(">> Phone updated!\n");
                        break;
                }
            } while (choice != 0);
            return;
        }
    }
    printf("Not found!\n");
}
    void removeStudent(struct Student students[], int *count) {
        int id;
        int choice;
        printf("Enter Student ID to remove: ");
        scanf("%d", &id); getchar();
        for (int i = 0; i < *count; i++) {
            if (students[i].StudentId == id) {
                printf("Do you want to removed?\n");
                printf("[1].yes\n[2].no\n");
                scanf("%d", &choice);
                getchar();
                if (choice == 1) {
                    for (int j = i; j < *count - 1; j++)
                        students[j] = students[j + 1];
                    (*count)--;
                    printf("Student removed successfully!\n");
                }else if (choice == 2) {
                    printf("Cancel Delete");
                    return;
                }
                return;
            }
        }
        printf("Not found!\n");
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
                            struct Student tmp=students[i];
                            students[i]=students[j];
                            students[j]=tmp;
                        }
                printf(">> Sorted by Name ASC!\n");
            } else if (choice == 2) {
                for (int i=0;i<count-1;i++)
                    for (int j=i+1;j<count;j++)
                        if (compareNames(students[i].name,students[j].name)<0) {
                            struct Student tmp=students[i];
                            students[i]=students[j];
                            students[j]=tmp;
                        }
                printf(">> Sorted by Name DESC!\n");
            } else if (choice == 3) {
                for (int i=0;i<count-1;i++)
                    for (int j=i+1;j<count;j++)
                        if (students[i].StudentId > students[j].StudentId) {
                            struct Student tmp=students[i];
                            students[i]=students[j];
                            students[j]=tmp;
                        }
                printf(">> Sorted by ID ASC!\n");
            } else if (choice == 4) {
                for (int i=0;i<count-1;i++)
                    for (int j=i+1;j<count;j++)
                        if (students[i].StudentId < students[j].StudentId) {
                            struct Student tmp=students[i];
                            students[i]=students[j];
                            students[j]=tmp;
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
        printf("\n| %-5s| %-20s| %-10s | %-8s| %-25s| %-12s|\n",
               "ID", "Name", "DOB", "Gender", "Email", "Phone");
        printf("------------------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < count; i++) {
            printf("| %-5d| %-20s| %02d/%02d/%04d | %-8s| %-25s| %-12s|\n",
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
    void addTeacher(struct Teacher teachers[], int *count, struct Classroom classrooms[],int classCount) {
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
        if (classCount >0) {
            printf("Do you want to assign this teacher to a classroom? (1.Yes/2.No)");
            int opt;
            scanf("%d",&opt);
            getchar();
            if (opt == 1) {
                printf(">>> Enter Classroom ID: ");
                int cid, found =0;
                do {
                    scanf("%d",&cid);
                    getchar();
                    for (int i=0;i<classCount;i++) {
                        if (classrooms[i].classroomId == cid) {
                            t.classroom = classrooms[i];
                            classrooms[i].teacherId=t.TeacherId;
                            printf("Teacher assigned to classroom %s \n",classrooms[i].classroomName);
                            found=1;
                            break;
                        }
                    }if (!found) {
                        printf("Classroom ID not found!!!!. Please try again.\n");
                    }
                }while (!found);
            }
        }

        teachers[*count] = t;
        (*count)++;
        printf("Teacher added successfully!\n");
    }
void editTeacher(struct Teacher teachers[], int *count) {
    int id;
    printf("Enter Teacher ID to edit: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < *count; i++) {

        if (teachers[i].TeacherId == id) {
            int choice;
            do {
                printf("\n===== EDIT TEACHER %d =====\n", id);
                printf("[1] Edit Name\n");
                printf("[2] Edit Date of Birth\n");
                printf("[3] Edit Gender\n");
                printf("[4] Edit Email\n");
                printf("[5] Edit Phone\n");
                printf("[0] Back\n");
                choice = getValidChoice(0, 5);

                switch (choice) {
                    case 1:
                        printf("Old Name");
                        printf("%s\n",teachers[*count].name);
                        printf("Enter new name: ");
                        fgets(teachers[i].name, 30, stdin);
                        teachers[i].name[strcspn(teachers[i].name, "\n")] = 0;
                        printf(">> Name updated!\n");
                        break;
                    case 2:
                        printf("Old Date of Birth");
                        printf("%d %d %d\n",teachers[*count].birth.day, teachers[*count].birth.month, teachers[*count].birth.year);
                        teachers[i].birth = getValidDate();
                        printf(">> DOB updated!\n");
                        break;
                    case 3:
                        printf("Old Gender");
                        printf("%d\n",teachers[*count].gender);
                        teachers[i].gender = getValidGender();
                        printf(">> Gender updated!\n");
                        break;
                    case 4:
                        char newEmail[30];
                        do {
                            getValidEmail(newEmail);
                            int dup = 0;
                            for (int j = 0; j < count; j++) {
                                if (j == i) continue; // bỏ qua chính nó
                                if (strcmp(teachers[j].email, newEmail) == 0) {
                                    dup = 1;
                                    break;
                                }
                            }
                            if (dup) {
                                printf("This email already exists! Please enter again.\n");
                            } else break;
                        } while (1);
                        strcpy(teachers[i].email, newEmail);
                        printf(">> Email updated!\n");
                        break;
                    case 5:
                        char newPhone[15];
                        do {
                            getValidPhone(newPhone);
                            int dup = 0;
                            for (int j = 0; j < count; j++) {
                                if (j == i) continue;
                                if (strcmp(teachers[j].phone, newPhone) == 0) {
                                    dup = 1;
                                    break;
                                }
                            }
                            if (dup) {
                                printf("This phone number already exists! Please enter again.\n");
                            } else break;
                        } while (1);
                        strcpy(teachers[i].phone, newPhone);
                        printf(">> Phone updated!\n");

                        break;
                }
            } while (choice != 0);
            return;
        }
    }
    printf("Not found!\n");
}
    void removeTeacher(struct Teacher teacher[], int *count) {
        int id;
        int choice;
        printf("Enter Teacher ID to remove: ");
        scanf("%d", &id);
        getchar();
        for (int i = 0; i < *count; i++) {
            if (teacher[i].TeacherId == id){
                printf("Do you want to removed?\n");
                printf("[1].yes\n[2].no\n");
                scanf("%d", &choice);
            getchar();
            if (choice == 1) {
                for (int j = i; j < *count - 1; j++)
                    teacher[j] = teacher[j + 1];
                (*count)--;
                printf("Teacher removed successfully!\n");
            }else if (choice == 2) {
                printf("Cancel Delete");
                return;
            }
            return;
        }
    }
printf("Not found!\n");
    }
 void searchTeacherByName(struct Teacher teacher[], int count) {
        if (count == 0) {
            printf("-- NO TEACHER TO SEARCH --\n");
            return;
        }
        char keyword[30];
        printf("Enter teacher name to search: ");
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
            strncpy(lowerName, teacher[i].name, sizeof(lowerName));
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
                       teacher[i].TeacherId,
                       teacher[i].name,
                       teacher[i].birth.day,
                       teacher[i].birth.month,
                       teacher[i].birth.year,
                       teacher[i].gender ? "MALE" : "FEMALE",
                       teacher[i].email,
                       teacher[i].phone);
                found = 1;
            }
        }

        if (found) {
            printf("======================================================================================================\n");
        } else {
            printf(">> No teacher found with name: '%s'\n", keyword);
        }
    }

// ================== CLASSROOM FUNCTIONS ==================
void showClassrooms(struct Classroom classrooms[], int count) {
        if (count == 0) {
            printf("No Classroom found!\n");
            return;
        }
        printf("\n======= CLASSROOM LIST =======\n");
        printf("=============================================================\n");
        printf("| %-5s| %-5s| %-15s|\n", "ClassID", "TeacherID", "ClassName");
        printf("-------------------------------------------------------------\n");
        for (int i = 0; i < count; i++) {
            printf("| %-5d  | %-5d    | %-15s |\n",
                   classrooms[i].classroomId,
                   classrooms[i].teacherId,
                   classrooms[i].classroomName);
        }
        printf("=============================================================\n");
    }

void addClassroom(struct Classroom classrooms[], int *count,struct Teacher teachers[], int teaCount)
                   {
        if (*count >= MAX) {
            printf("Classroom list is full!\n");
            return;
        }
        struct Classroom c;
        c.classroomId = getNextIdClass(classrooms, *count);
        printf(" ID: %d\n", c.classroomId);

        printf("Enter Classroom Name: ");
        fgets(c.classroomName, sizeof(c.classroomName), stdin);
        c.classroomName[strcspn(c.classroomName, "\n")] = 0;

        classrooms[*count] = c;
        (*count)++;
        printf(" Classroom added successfully!\n");
    }
void editClassroom(struct Classroom classrooms[], int *count,
                   struct Teacher teachers[], int teacherCount) {
        int id;
        printf("Enter ClassroomID to edit: ");
        scanf("%d", &id);
        getchar();

        for (int i = 0; i < *count; i++) {
            if (classrooms[i].classroomId == id) {
                int choice;
                do {
                    printf("\n===== EDIT CLASSROOM %d =====\n", id);
                    printf("1. Edit Class Name\n");
                    printf("2. Edit Teacher\n");
                    printf("3. Edit Student\n");
                    printf("0. Back\n");

                    choice = getValidChoice(0, 3);
                    switch (choice) {
                        case 1: {
                            printf("Enter New Name for the class: ");
                            fgets(classrooms[i].classroomName, sizeof(classrooms[i].classroomName), stdin);
                            classrooms[i].classroomName[strcspn(classrooms[i].classroomName, "\n")] = '\0';
                            printf(" Classroom Name Updated!\n");
                            break;
                        }
                        case 2: {
                            int newId = getValidTeacherId(teachers, teacherCount, classrooms, *count);
                            classrooms[i].teacherId = newId;
                            printf(" Teacher Updated!\n");
                            break;
                        }
                        case 3: {
                            printf("\n");
                            break;
                        }
                    }
                } while (choice != 0);
                return;
            }
        }

        printf(" Classroom not found!\n");

    }

    // ================== MENU ==================
    void studentMenu(struct Student students[], int *stuCount) {
        int choice;
        do {
            printf("\n===== STUDENT MENU =====\n");
            printf("[1]. Show Students\n");
            printf("[2]. Add Student\n");
            printf("[3]. Edit Student\n");
            printf("[4]. Remove Student\n");
            printf("[5]. Search Student\n");
            printf("[6]. Sort Students\n");
            printf("[0]. Back\n");
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
                    int again;
                    do {
                        searchStudentByName(students, *stuCount);
                        printf("\n[1] Search StudentByName\n[0] Back\n");
                        again = getValidChoice(0, 1);
                    } while (again == 1);
                }
                case 6:
                    sortStudents(students, *stuCount);
                    break;
            }
        } while (choice != 0);
    }
    void teacherMenu(struct Teacher teachers[], int *teaCount, struct  Classroom classrooms[], int classCount) {
        int choice;
        do {
            printf("\n===== TEACHER MENU =====\n");
            printf("[1]. Show Teachers\n[2]. Add Teacher\n[3]. Edit Teacher\n[4]. Remove Teacher\n[5]. Search Teacher\n[6]. Sort Teachers\n[0]. Back\n");
            choice = getValidChoice(0, 6);
            switch (choice) {
                case 1: showTeachers(teachers, *teaCount);
                    break;
                case 2: {
                    int again;
                    do {
                        addTeacher(teachers, teaCount, classrooms ,classCount);
                        printf("\n[1] Add another Teacher\n[0] Back\n");
                        again = getValidChoice(0, 1);
                    }while (again ==1);
                    break;
                }
                case 3: {
                    int again;
                    do {
                        editTeacher(teachers, teaCount);
                        printf("\n[1] Edit another Teacher\n[0] Back\n");
                        again = getValidChoice(0, 1);
                    } while (again == 1);
                    break;
                }
                case 4: {
                    int again;
                    do {
                        removeTeacher(teachers, teaCount);
                        printf("\n[1] Remove another student\n[0] Back\n");
                        again = getValidChoice(0, 1);
                    } while (again == 1);
                    break;
                }
                case 5: {
                    int again;
                    do{
                    searchTeacherByName(teachers, *teaCount);
                    printf("\n[1] Searching another teacher\n[0] Back\n");
                    again = getValidChoice(0, 1);
                } while (again == 1);
                }
            }
            } while (choice != 0);
        }
void classroomMenu(struct Classroom classrooms[], int *classCount,
                   struct Teacher teachers[], int teaCount) {
    int choice;
    do {
        printf("\n===== CLASSROOM MENU =====\n");
        printf("[1]. Show Classrooms\n");
        printf("[2]. Add Classroom\n");
        printf("[3]. Edit Classroom\n");
        printf("[0]. Back\n");
        choice = getValidChoice(0, 3);
        switch (choice) {
            case 1:
                showClassrooms(classrooms, *classCount);
                break;
            case 2:
                addClassroom(classrooms, classCount, teachers, teaCount);
                break;
            case 3:
                editClassroom(classrooms,classCount,teachers, teaCount);
                break;
        }
    } while (choice != 0);
}


    void adminMenu(struct Student students[], int *stuCount, struct Teacher teachers[], int *teaCount, struct Classroom classrooms[], int *classCount) {
        int choice;
        do {
            printf("\n===== ADMIN MENU =====\n");
            printf("[1]. Manage Students\n[2]. Manage Teachers\n[3]. Manage Classroom\n[0]. Back\n");
            choice = getValidChoice(0, 3);
            if
            (choice == 1) studentMenu(students, stuCount);
            else if
            (choice == 2) teacherMenu(teachers, teaCount,classrooms, *classCount);
            else if (
                choice ==3) classroomMenu(classrooms,classCount,teachers, *teaCount );
        } while (choice != 0);
    }

    int main() {
        struct Student students[MAX];
        struct Teacher teachers[MAX];
        struct Classroom *classrooms = malloc(MAX * sizeof(struct Classroom));
        int classCount = 0;
        int stuCount = 0, teaCount = 0;
        int choice;
        do {
            printf("\n===== MAIN MENU =====\n");
            printf("[1]. Admin\n[2]. Student Role\n[3]. Teacher Role\n0. Exit\n");
            choice = getValidChoice(0, 3);
            if
            (choice == 1) adminMenu(students, &stuCount, teachers, &teaCount, classrooms,&classCount);
            else if
            (choice == 2) printf(">> Student role menu here.\n");
            else if
            (choice == 3) printf(">> Teacher role menu here.\n");
        } while (choice != 0);
        return 0;
    }
