#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <wincon.h>

struct Student
{
    int userID;
    char passWord[20];
    char passWord1[20];
    char name[100];
    char dept[100];
    int semester;
    float cgpa;
    float sgpa[8];
};

struct Professor
{
    int userID;
    char passWord[20];
    char passWord1[20];
    char name[100];
    char dept[100];
    int expr;
};

void title();
int Member();
int s_login();
int p_login();
void s_sign_in();
void p_sign_in();
int s_user_exists(int userID);
void s_sign_up();
int p_user_exists(int userID);
void p_sign_up();
void takePassword(char *passWord);
int s_authenticate(int *userID, char *passWord);
int p_authenticate(int *userID, char *passWord);
void s_forget_pass();
void p_forget_pass();
void s_change_pass();
void p_change_pass();
void s_delete();
void p_delete();
void s_signIn_scrn();
void s_addDetails();
void s_viewDetails();
void s_modifyDetails();
void s_viewProfDetails();
void p_signIn_scrn();
void p_addDetails();
void p_viewDetails();
void p_modifyDetails();
void p_modifyStudentDetails();
void p_viewStudentDetails();
void p_removeStudent();
void log_out();
void thanks();

int main()
{
    title();

    int member = Member();
    if (member == 1)
    {

        int choice = s_login();
        if (choice == 1)
        {
            s_sign_in();
        }
        else if (choice == 2)
        {
            s_sign_up();
        }
        else if (choice == 3)
        {
            s_forget_pass();
        }
        else if (choice == 4)
        {
            s_change_pass();
        }
        else if (choice == 5)
        {
            s_delete();
        }
        else if (choice == 6)
        {
            thanks();
            exit(0);
        }
        else
        {
            printf("Invalid Command");
        }
    }
    else if (member == 2)
    {

        int choice = p_login();
        if (choice == 1)
        {
            p_sign_in();
        }
        else if (choice == 2)
        {
            p_sign_up();
        }
        else if (choice == 3)
        {
            p_forget_pass();
        }
        else if (choice == 4)
        {
            p_change_pass();
        }
        else if (choice == 5)
        {
            p_delete();
        }
        else if (choice == 6)
        {
            thanks();
            exit(0);
        }
        else
        {
            printf("Invalid Command");
        }
    }
    else
    {
        printf("Invalid Member");
    }
    return 0;
}

void title()
{
    system("cls");
    printf("\n\n\t");
    for (int i = 1; i <= 19; i++)
    {
        printf("=");
    }
    printf(" KIIT University Management System ");
    for (int i = 1; i <= 19; i++)
    {
        printf("=");
    }
    printf("\n\n");
}

int Member()
{
    int member;
    printf("1.. STUDENT \n\n");
    printf("2.. PROFESSOR \n\n");

    printf("Enter your role in the University: ");
    scanf("%d", &member);
    return member;
}

int s_login()
{
    title();
    printf("\n ___ Student Login ___      \n\n");

    int choice;
    printf("1.. SIGN IN: (Existing User) \n\n");
    printf("2.. SIGN UP: (New User) \n\n");
    printf("3.. FORGOT PASSWORD \n\n");
    printf("4.. CHANGE/RESET PASSWORD \n\n");
    printf("5.. DELETE/REMOVE User\n\n");
    printf("6.. EXIT\n\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int p_login()
{
    title();
    printf("\n ___ Professor Login ___      \n\n");

    int choice;
    printf("1.. SIGN IN: (Existing User) \n\n");
    printf("2.. SIGN UP: (New User) \n\n");
    printf("3.. FORGOT PASSWORD \n\n");
    printf("4.. CHANGE/RESET PASSWORD \n\n");
    printf("5.. DELETE/REMOVE User\n\n");
    printf("6.. EXIT\n\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void takePassword(char *passWord)
{
    int i = 0;
    char ch;

    while (1)
    {
        ch = getch();
        if (ch == '\r')
        {
            passWord[i] = '\0';
            break;
        }
        else if (ch == '\b')
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if (ch == '\t' || ch == ' ')
        {
            continue;
        }
        else
        {
            passWord[i] = ch;
            i++;
            printf("*");
        }
    }
    printf("\n");
}

int s_authenticate(int *userID, char *passWord)
{
    struct Student s_user;
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL)
    {
        printf("No existing users. Please SIGN UP first. \n");
        return 0;
    }
    else
    {
        while (fscanf(fp, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF)
        {
            for (int i = 0; i < s_user.semester; i++)
            {
                fscanf(fp, "%f", &s_user.sgpa[i]);
            }
            if (strcmp(passWord, s_user.passWord) == 0 && *userID == s_user.userID)
            {
                fclose(fp);
                return 1;
            }
        }
        fclose(fp);
        printf("Invalid User ID or Password. Please try again. \n");
        return 0;
    }
}

int p_authenticate(int *userID, char *passWord)
{
    struct Professor p_user;
    FILE *fp = fopen("professor.txt", "r");
    if (fp == NULL)
    {
        printf("No existing users. Please SIGN UP first. \n");
        return 0;
    }
    else
    {
        while (fscanf(fp, "%d %s %s %s %d", &p_user.userID, p_user.passWord, p_user.name, p_user.dept, &p_user.expr) != EOF)
    {
            if (strcmp(passWord, p_user.passWord) == 0 && *userID == p_user.userID)
            {
                fclose(fp);
                return 1;
            }
        }
        fclose(fp);
        printf("Invalid User ID or Password. Please try again. \n");
        return 0;
    }
}

void s_sign_in()
{
    int userID;
    char passWord[20];
    int pchoice;

    title();
    printf("\n ___ [STUDENT] Sign In ___ \n\n");

    printf("Enter User ID/Roll No. : ");
    scanf("%d", &userID);

    if (!s_user_exists(userID))
    {
        printf("This user does not exists in our system. Please Sign Up first.\n");
        printf("LOADING.......\n");
        Sleep(4000);
        s_sign_up();
        return;
    }

pass:
    printf("Enter Password: ");
    takePassword(passWord);

    if (s_authenticate(&userID, passWord))
    {
        printf("Login successful!\n");
        printf("Directing to Student Screen.......\n");
        Sleep(3000);
        s_signIn_scrn();
    }
    else
    {
        printf("Login failed. Please try again and enter coorect password.\n\n");
        printf("What do you want to do?\n\n");
        printf("1.. Re-Enter Password \n");
        printf("2.. Forgot Password\n");
        printf("3.. Change Password\n");
        printf("Enter your choice: ");
        scanf("%d", &pchoice);

        switch (pchoice)
        {
        case 1:
            goto pass;
            break;

        case 2:
            s_forget_pass();

        case 3:
            s_change_pass();

        default:
            break;
        }
    }
}

void p_sign_in()
{
    int userID;
    char passWord[20];
    int pchoice;

    title();
    printf("\n ___ [PROFESSOR] Sign In ___ \n\n");

    printf("Enter User ID/Emp ID : ");
    scanf("%d", &userID);

    if (!p_user_exists(userID))
    {
        printf("This user does not exists in our system. Please Sign Up first.\n");
        printf("LOADING.......\n");
        Sleep(4000);
        p_sign_up();
        return;
    }

pass:
    printf("Enter Password: ");
    takePassword(passWord);

    if (p_authenticate(&userID, passWord))
    {
        printf("Login successful!\n");
        printf("Directing to Professor Screen.......\n");
        Sleep(3000);
        p_signIn_scrn();
    }
    else
    {
        printf("Login failed. Please try again and enter coorect password.\n\n");
        printf("What do you want to do?\n\n");
        printf("1.. Re-Enter Password \n");
        printf("2.. Forgot Password\n");
        printf("3.. Change Password\n");
        printf("Enter your choice: ");
        scanf("%d", &pchoice);

        switch (pchoice)
        {
        case 1:
            goto pass;
            break;

        case 2:
            p_forget_pass();

        case 3:
            p_change_pass();

        default:
            break;
        }
    }
}

int s_user_exists(int userID)
{
    struct Student s_user;
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL)
    {
        return 0;
    }
    while (fscanf(fp, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF)
    {
        for (int i = 0; i < s_user.semester; i++)
        {
            fscanf(fp, "%f", &s_user.sgpa[i]);
        }
        if (s_user.userID == userID)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void s_sign_up()
{
    title();
    printf("\n ___ [STUDENT] Sign Up ___ \n\n");

    struct Student s_user;
    FILE *fp = fopen("student.txt", "a+");
    if (fp == NULL)
    {
        printf("Error creating user. \n");
        return;
    }
    while (1)
    {
        printf("Enter new User ID/Roll No. : ");
        scanf("%d", &s_user.userID);

        if (s_user_exists(s_user.userID))
        {
            printf("This User ID already exists. Please choose a new one.\n");
        }
        else
        {
            break;
        }
    }

    printf("Enter new Password: ");
    takePassword(s_user.passWord);

confpass:
    printf("Confirm Password: ");
    takePassword(s_user.passWord1);

    if (!strcmp(s_user.passWord, s_user.passWord1))
    {
        fprintf(fp, "%d %s %s %s %d %f", s_user.userID, s_user.passWord, s_user.name, s_user.dept, s_user.semester, s_user.cgpa);
        for (int i = 0; i < s_user.semester; i++)
        {
            fprintf(fp, " %f", s_user.sgpa[i]);
        }
        fprintf(fp, "\n");
        fclose(fp);

        printf("Sign-up successful! You can now sign in.\n");
        printf("LOADING.......\n");
        Sleep(4000);
        s_sign_in();
    }
    else
    {
        printf("Please re-enter the correct password to confirm.\n");
        goto confpass;
    }
}

int p_user_exists(int userID)
{
    struct Professor p_user;
    FILE *fp = fopen("professor.txt", "r");
    if (fp == NULL)
    {
        return 0;
    }
    while (fscanf(fp, "%d %s %s %s %d", &p_user.userID, p_user.passWord, p_user.name, p_user.dept, &p_user.expr) != EOF)
    {
        if (p_user.userID == userID)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void p_sign_up()
{
    title();
    printf("\n ___ [PROFESSOR] Sign Up ___ \n\n");

    struct Professor p_user;
    FILE *fp = fopen("professor.txt", "a+");
    if (fp == NULL)
    {
        printf("Error creating user. \n");
        return;
    }

    while (1)
    {
        printf("Enter new User ID/Emp ID: ");
        scanf("%d", &p_user.userID);

        if (p_user_exists(p_user.userID))
        {
            printf("This User ID already exists. Please choose a new one.\n");
        }
        else
        {
            break;
        }
    }

    printf("Enter new Password: ");
    takePassword(p_user.passWord);

confpass:
    printf("Confirm Password: ");
    takePassword(p_user.passWord1);

    if (!strcmp(p_user.passWord, p_user.passWord1))
    {
        fprintf(fp, "%d %s %s %s %d", p_user.userID, p_user.passWord, p_user.name, p_user.dept, p_user.expr);
        fprintf(fp, "\n");
        fclose(fp);

        printf("Sign-up successful! You can now sign in.\n");
        printf("LOADING.......\n");
        Sleep(4000);
        p_sign_in();
    }
    else
    {
        printf("Please re-enter the correct password to confirm.\n");
        goto confpass;
    }
}

void s_forget_pass()
{
    title();
    printf("\n ___ [STUDENT] Forgot Password ___ \n\n");

    struct Student s_user;
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL)
    {
        printf("No records found. \n");
        return;
    }

    int userID;
    while (1)
    {
        printf("Enter User ID/Roll No. : ");
        scanf("%d", &userID);

        if (!s_user_exists(userID))
        {
            printf("The user does not exists on our system.\n");
        }
        else
        {
            break;
        }
    }

    while (fscanf(fp, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF)
    {
        for (int i = 0; i < s_user.semester; i++)
        {
            fscanf(fp, "%f", &s_user.sgpa[i]);
        }
        if (userID == s_user.userID)
        {
            printf("Your Password is: %s", s_user.passWord);
            printf("\n");
            fclose(fp);
            break;
        }
    }
    fclose(fp);
    printf("Now Sign In using your credentials.\n");
    printf("LOADING.......\n");
    Sleep(3000);
    s_sign_in();
}

void p_forget_pass()
{
    title();
    printf("\n ___ [PROFESSOR] Forgot Password ___ \n\n");

    struct Professor p_user;
    FILE *fp = fopen("professor.txt", "r");
    if (fp == NULL)
    {
        printf("No records found. \n");
    }

    int userID;
    while (1)
    {
        printf("Enter User ID/Emp ID: ");
        scanf("%d", &userID);

        if (!p_user_exists(userID))
        {
            printf("The user does not exists on our system.\n");
        }
        else
        {
            break;
        }
    }

    while (fscanf(fp, "%d %s %s %s %d", &p_user.userID, p_user.passWord, p_user.name, p_user.dept, &p_user.expr) != EOF)
    {
        if (userID == p_user.userID)
        {
            printf("Your Password is: %s", p_user.passWord);
            printf("\n");
            fclose(fp);
            break;
        }
    }
    fclose(fp);
    printf("Now Sign In using your credentials.\n");
    printf("LOADING\n");
    Sleep(3000);
    p_sign_in();
}

void s_change_pass()
{
    title();
    printf("\n ___ [STUDENT] Change/Reset Password ___ \n\n");

    char newPassword[20];

    struct Student s_user;
    FILE *fp = fopen("student.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening files.\n");
        if (fp != NULL)
            fclose(fp);
        if (temp != NULL)
            fclose(temp);
        return;
    }

    int userID;
    while (1)
    {
        printf("Enter User ID/Roll No. : ");
        scanf("%d", &userID);

        if (!s_user_exists(userID))
        {
            printf("The user doesn't exist in our records.\n");
        }
        else
        {
            break;
        }
    }

    int found = 0;
    while (fscanf(fp, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF)
    {
        for (int i = 0; i < s_user.semester; i++)
        {
            fscanf(fp, "%f", &s_user.sgpa[i]);
        }
        if (s_user.userID == userID)
        {
            found = 1;
            printf("Enter new Password: ");
            takePassword(newPassword);
            strcpy(s_user.passWord, newPassword);
        }
        fprintf(temp, "%d %s %s %s %d %f", s_user.userID, s_user.passWord, s_user.name, s_user.dept, s_user.semester, s_user.cgpa);
        for (int i = 0; i < s_user.semester; i++)
        {
            fprintf(temp, " %f", s_user.sgpa[i]);
        }
        fprintf(temp, "\n");
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove("student.txt");
        rename("temp.txt", "student.txt");
        printf("Password changed successfully.\n");
        printf("Please Sign In to verify.\n");
        printf("LOADING.......\n");
        Sleep(4000);
        s_sign_in();
    }
    else
    {
        remove("temp.txt");
        printf("User ID not found.\n");
    }
}

void p_change_pass()
{
    title();
    printf("\n ___ [PROFESSOR] Change/Reset Password ___ \n\n");

    char newPassword[20];

    struct Professor p_user;
    FILE *fp = fopen("professor.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening files.\n");
        if (fp != NULL)
            fclose(fp);
        if (temp != NULL)
            fclose(temp);
        return;
    }

    int userID;
    while (1)
    {
        printf("Enter User ID/Emp ID: ");
        scanf("%d", &userID);

        if (!p_user_exists(userID))
        {
            printf("The user doesn't exist in our records.\n");
        }
        else
        {
            break;
        }
    }

    int found = 0;
    while (fscanf(fp, "%d %s %s %s %d", &p_user.userID, p_user.passWord, p_user.name, p_user.dept, &p_user.expr) != EOF)
    {
        if (p_user.userID == userID)
        {
            found = 1;
            printf("Enter new Password: ");
            takePassword(newPassword);
            strcpy(p_user.passWord, newPassword);
        }
        fprintf(temp, "%d %s %s %s %d\n", p_user.userID, p_user.passWord, p_user.name, p_user.dept, p_user.expr);
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove("professor.txt");
        rename("temp.txt", "professor.txt");
        printf("Password changed successfully.\n");
        printf("Please Sign In to verify.\n");
        printf("LOADING.......\n");
        Sleep(4000);
        p_sign_in();
    }
    else
    {
        remove("temp.txt");
        printf("User ID not found.\n");
    }
}

void s_delete()
{
    title();
    printf("\n ___ [STUDENT] Delete/Remove User ___ \n\n");

    int userID;
    while (1)
    {
        printf("Enter User ID/Roll No. : ");
        scanf("%d", &userID);

        if (!s_user_exists(userID))
        {
            printf("The user doesn't exists on our records.\n");
        }
        else
        {
            break;
        }
    }

    struct Student s_user;
    FILE *fp = fopen("student.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening files.\n");
        if (fp != NULL)
            fclose(fp);
        if (temp != NULL)
            fclose(temp);
        return;
    }
    while (fscanf(fp, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF)
    {
        for (int i = 0; i < s_user.semester; i++)
        {
            fscanf(fp, "%f", &s_user.sgpa[i]);
        }
        if (s_user.userID != userID)
        {
            fprintf(temp, "%d %s %s %s %d %f", s_user.userID, s_user.passWord, s_user.name, s_user.dept, s_user.semester, s_user.cgpa);
            for (int i = 0; i < s_user.semester; i++)
            {
                fprintf(temp, " %f", s_user.sgpa[i]);
            }
            fprintf(temp, "\n");
        }
    }
    fclose(fp);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    printf("\n User deleted successfully.\n\n");
    printf("Directing to Student Login page.......\n");
    Sleep(3000);
    s_login();

}

void p_delete()
{
    title();
    printf("\n ___ [PROFESSOR] Delete/Remove User ___ \n\n");

    int userID;
    while (1)
    {
        printf("Enter User ID/Emp ID: ");
        scanf("%d", &userID);

        if (!p_user_exists(userID))
        {
            printf("The user doesn't exists on our records.\n");
        }
        else
        {
            break;
        }
    }

    struct Professor p_user;
    FILE *fp = fopen("professor.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening files.\n");
        if (fp != NULL)
            fclose(fp);
        if (temp != NULL)
            fclose(temp);
        return;
    }
    while (fscanf(fp, "%d %s %s %s %d", &p_user.userID, p_user.passWord, p_user.name, p_user.dept, &p_user.expr) != EOF)
    {
        if (p_user.userID != userID)
        {
            fprintf(temp, "%d %s %s %s %d\n", p_user.userID, p_user.passWord, p_user.name, p_user.dept, p_user.expr);
        }
    }
    fclose(fp);
    fclose(temp);

    remove("professor.txt");
    rename("temp.txt", "professor.txt");

    printf("\n User deleted successfully.\n\n");
    printf("Directing to Professor Login page.......\n");
    Sleep(3000);
    p_login();
}

void s_signIn_scrn()
{
    title();
    printf("\n ___ Student Screen ___      \n\n");

    int choice;
    printf("1.. ADD PERSONAL DETAILS \n\n");
    printf("2.. VIEW PERSONAL DETAILS \n\n");
    printf("3.. MODIFY PERSONAL DETAILS \n\n");
    printf("4.. VIEW PROFESSOR DETAILS \n\n");
    printf("5.. LOG OUT \n\n");
    printf("6.. EXIT \n\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        s_addDetails();
        break;
    case 2:
        s_viewDetails();
        break;
    case 3:
        s_modifyDetails();
        break;
    case 4:
        s_viewProfDetails();
        break;
    case 5:
        log_out();
        break;
    case 6:
        thanks();
        exit(0);
    default:
        break;
    };
}

void s_addDetails()
{
    title();
    printf("\n\t [STUDENT] ___Add Details___ \n\n\n");

    struct Student s_user;
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL) {
        printf("No records found. \n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return;
    }

    int userID, sem, i;
    char name[100];
    char dept[100];
    int found = 0;

    printf("Enter User ID/Roll No.: ");
    scanf("%d", &userID);

    while (fscanf(fp, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF) {
        for (i = 0; i < s_user.semester; i++) {
            fscanf(fp, "%f", &s_user.sgpa[i]);
        }
        if (userID == s_user.userID) {
            found = 1;
            printf("Enter Name: ");
            scanf(" %[^\n]s", name);
            strcpy(s_user.name, name);

            printf("Enter Department: ");
            scanf(" %[^\n]s", dept);
            strcpy(s_user.dept, dept);

            printf("Enter Current Semester: ");
            scanf("%d", &sem);
            s_user.semester = sem;

            for (i = 0; i < s_user.semester; i++) {
                printf("Enter SGPA of Semester %d: ", i + 1);
                scanf("%f", &s_user.sgpa[i]);
            }

            printf("Enter CGPA: ");
            scanf("%f", &s_user.cgpa);

            // Write the updated record to the temp file
            fprintf(temp, "%d %s %s %s %d %f", s_user.userID, s_user.passWord, s_user.name, s_user.dept, s_user.semester, s_user.cgpa);
            for (i = 0; i < s_user.semester; i++) {
                fprintf(temp, " %f", s_user.sgpa[i]);
            }
            fprintf(temp, "\n");
        } else {
            // Write the existing record to the temp file
            fprintf(temp, "%d %s %s %s %d %f", s_user.userID, s_user.passWord, s_user.name, s_user.dept, s_user.semester, s_user.cgpa);
            for (i = 0; i < s_user.semester; i++) {
                fprintf(temp, " %f", s_user.sgpa[i]);
            }
            fprintf(temp, "\n");
        }
    }

    if (!found) {
        int s;
        printf("Record not found.\n");
        printf("What do you want to do?\n\n");
        printf("1.. Sign In\n\n");
        printf("2.. Sign Up\n\n");
        printf("Enter your choice: ");
        scanf("%d", &s);
        
        switch (s)
        {
        case 1:
            s_sign_in();
            break;
        case 2:
            s_sign_up();
            break;
        default:
            break;
        }
    }
    fclose(fp);
    fclose(temp);

    // Replace the old file with the updated file
    remove("student.txt");
    rename("temp.txt", "student.txt");

    printf("Record added successfully.\n\n");
    printf("Directing to Student Screen.......\n");
    Sleep(3000);
    s_signIn_scrn();
}

void s_viewDetails()
{
    title();
    printf("\n\t [STUDENT] ___View Details___ \n\n\n");

    struct Student s_user;
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL)
    {
        printf("No records found. \n");
    }

    int userID, i, choice;
    int found = 0;
    printf("Enter User ID/Roll No. : ");
    scanf("%d", &userID);

    while (fscanf(fp, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF)
    {
        for (i = 0; i < s_user.semester; i++)
        {
            fscanf(fp, "%f", &s_user.sgpa[i]);
        }

        if (userID == s_user.userID)
        {
            found = 1;
            printf("\n \t __STUDENT DETAILS__ \n\n");
            printf("User ID/Roll No. : %d \n", s_user.userID);
            printf("Student Name: %s \n", s_user.name);
            printf("Department: %s \n", s_user.dept);
            printf("Current Semester: %d \n", s_user.semester);
            printf("Semester \t SGPA \n");

            for (i = 0; i < s_user.semester; i++)
            {
                printf("%d \t\t %.2f \n", i+1, s_user.sgpa[i]);
            }

            printf("CGPA: %.2f \n", s_user.cgpa);
            break;
        }
    }
    if (!found)
    {
        printf("User not found. \n");
    }
    fclose(fp);

    printf("Press '0' to visit Student Screen.\n");
    printf("Press '1' to Exit.\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 0:
        printf("Directing to Student Screen.......\n");
        Sleep(3000);
        s_signIn_scrn();
        break;
    case 1:
        thanks();
        exit(0);
    default:
        break;
    }
}

void s_modifyDetails() 
{
    title();
    printf("\n\t [STUDENT] ___Modify Details___ \n\n\n");

    struct Student s_user;
    FILE *fp = fopen("student.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening files.\n");
        if (fp != NULL) fclose(fp);
        if (temp != NULL) fclose(temp);
        return;
    }

    int userID, i, choice, sem;
    int found = 0;
    char new_name[100];
    char new_dept[100];
    float new_sgpa, new_cgpa;
    char ch[5];

    printf("Enter User ID/Roll No.: ");
    scanf("%d", &userID);

    while (fscanf(fp, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF) {
        for (i = 0; i < s_user.semester; i++) {
            fscanf(fp, "%f", &s_user.sgpa[i]);
        }

        if (userID == s_user.userID) {
            found = 1;

            do {
                printf("\n\t__STUDENT DETAILS__\n\n");
                printf("User ID/Roll No.: %d\n", s_user.userID);
                printf("Student Name: %s\n", s_user.name);
                printf("Department: %s\n", s_user.dept);
                printf("Current Semester: %d\n", s_user.semester);
                printf("Semester\tSGPA\n");
                for (i = 0; i < s_user.semester; i++) {
                    printf("%d\t\t%.2f\n", i + 1, s_user.sgpa[i]);
                }
                printf("CGPA: %.2f\n", s_user.cgpa);

                printf("\n\nWhat do you want to MODIFY/UPDATE?\n\n");
                printf("1.. Name\n");
                printf("2.. Department\n");
                printf("3.. Current Semester\n");
                printf("4.. SGPA\n");
                printf("5.. CGPA\n");
                printf("6.. No changes\n\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                case 1:
                    printf("Enter new Name: ");
                    scanf(" %[^\n]s", new_name);
                    strcpy(s_user.name, new_name);
                    break;
                case 2:
                    printf("Enter new Department: ");
                    scanf(" %[^\n]s", new_dept);
                    strcpy(s_user.dept, new_dept);
                    break;
                case 3:
                    do {
                        printf("Enter Current Semester: ");
                        scanf("%d", &sem);
                        if (sem <= s_user.semester) {
                            printf("Enter a semester greater than the current semester (%d).\n", s_user.semester);
                        }
                    } while (sem <= s_user.semester);
                    s_user.semester = sem;
                    break;
                case 4:
                    printf("Enter semester of which you want to add/update SGPA: ");
                    scanf("%d", &sem);
                    printf("Enter SGPA: ");
                    scanf("%f", &new_sgpa);
                    s_user.sgpa[sem - 1] = new_sgpa;
                    break;
                case 5:
                    printf("Enter updated CGPA: ");
                    scanf("%f", &new_cgpa);
                    s_user.cgpa = new_cgpa;
                    break;
                case 6:
                    printf("...No Changes...\n");
                    break;
                default:
                    printf("Invalid choice.\n");
                    continue;
                }

                printf("\n\nWant to MODIFY/UPDATE any more Details? (Y/N): ");
                scanf("%s", ch);
            } while (ch[0] == 'Y' || ch[0] == 'y');
        }

        // Write the (modified) record to the temporary file
        fprintf(temp, "%d %s %s %s %d %.2f", s_user.userID, s_user.passWord, s_user.name, s_user.dept, s_user.semester, s_user.cgpa);
        for (int i = 0; i < s_user.semester; i++) {
            fprintf(temp, " %.2f", s_user.sgpa[i]);
        }
        fprintf(temp, "\n");
    }

    fclose(fp);
    fclose(temp);

    // Replace the original file with the temporary file
    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (!found) {
        printf("User not found.\n");
    }

    s_viewDetails();
}

void s_viewProfDetails()
{
    title();

    struct Professor p_user;
    FILE *fp = fopen("professor.txt", "r");
    if (fp == NULL){
        printf("No records found.\n");
        return;
    }

    int choice;
    printf("\n\n \t ___LIST OF PROFESSORS___ \n\n");
    while (fscanf(fp, "%d %s %s %s %d", &p_user.userID, p_user.passWord, p_user.name, p_user.dept, &p_user.expr) != EOF)
    {
        if (p_user.userID)
        {
            printf("User ID/Emp ID : %d \n", p_user.userID);
            printf("Professor Name: %s \n", p_user.name);
            printf("Department: %s \n", p_user.dept);
            printf("Years of Experience: %d \n", p_user.expr);
            
            printf("\n\n");
        }
    }
    fclose(fp);

    printf("Press '0' to visit Student Screen.\n");
    printf("Press '1' to Exit.\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 0:
        printf("Directing to Student Screen.......\n");
        Sleep(3000);
        s_signIn_scrn();
        break;
    case 1:
        thanks();
        exit(0);
    default:
        break;
    }
}

void p_signIn_scrn()
{
    title();
    printf("\n ___ Professor Screen ___      \n\n");

    int choice;
    printf("1.. ADD PERSONAL DETAILS \n\n");
    printf("2.. VIEW PERSONAL DETAILS \n\n");
    printf("3.. MODIFY PERSONAL DETAILS \n\n");
    printf("4.. MODIFY STUDENT DETAILS \n\n");
    printf("5.. VIEW STUDENT DETAILS \n\n");
    printf("6.. REMOVE STUDENT \n\n");
    printf("7.. LOG OUT \n\n");
    printf("8.. EXIT \n\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        p_addDetails();
        break;
    case 2:
        p_viewDetails();
        break;
    case 3:
        p_modifyDetails();
        break;
    case 4:
        p_modifyStudentDetails();
        break;
    case 5:
        p_viewStudentDetails();
        break;
    case 6:
        p_removeStudent();
        break;
    case 7:
        log_out();
        break;
    case 8:
        thanks();
        exit(0);
    default:
        break;
    };
}

void p_addDetails()
{
    title();
    printf("\n\t [PROFESSOR] ___Add Details___ \n\n\n");

    struct Professor p_user;
    FILE *fp = fopen("professor.txt", "r");
    if (fp == NULL) {
        printf("No records found. \n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return;
    }

    int userID, expr;
    char name[100];
    char dept[100];
    int found = 0;

    printf("Enter User ID/Emp ID: ");
    scanf("%d", &userID);

    while (fscanf(fp, "%d %s %s %s %d", &p_user.userID, p_user.passWord, p_user.name, p_user.dept, &p_user.expr) != EOF) {
        if (userID == p_user.userID) {
            found = 1;
            printf("Enter Name: ");
            scanf(" %[^\n]s", name);
            strcpy(p_user.name, name);

            printf("Enter Department: ");
            scanf(" %[^\n]s", dept);
            strcpy(p_user.dept, dept);

            printf("Enter Years of Experience: ");
            scanf("%d", &expr);
            p_user.expr = expr;

            // Write the updated record to the temp file
            fprintf(temp, "%d %s %s %s %d\n", p_user.userID, p_user.passWord, p_user.name, p_user.dept, p_user.expr);
        } else {
            // Write the existing record to the temp file
            fprintf(temp, "%d %s %s %s %d\n", p_user.userID, p_user.passWord, p_user.name, p_user.dept, p_user.expr);
        }
        
    }

    if (!found) {
        int s;
        printf("Record not found.\n");
        printf("What do you want to do?\n\n");
        printf("1.. Sign In\n\n");
        printf("2.. Sign Up\n\n");
        printf("Enter your choice: ");
        scanf("%d", &s);
        
        switch (s)
        {
        case 1:
            p_sign_in();
            break;
        case 2:
            p_sign_up();
            break;
        default:
            break;
        }
    }
    fclose(fp);
    fclose(temp);

    // Replace the old file with the updated file
    remove("professor.txt");
    rename("temp.txt", "professor.txt");

    printf("Record added successfully.\n");
    printf("Directing to Professor Screen.......\n");
    Sleep(3000);
    p_signIn_scrn();
}

void p_viewDetails()
{
    title();
    printf("\n\t [PROFESSOR] ___View Details___ \n\n\n");

    struct Professor p_user;
    FILE *fp = fopen("professor.txt", "r");
    if (fp == NULL)
    {
        printf("No records found. \n");
    }

    int userID, i, choice;
    int found = 0;
    printf("Enter User ID/Emp ID : ");
    scanf("%d", &userID);

    while (fscanf(fp, "%d %s %s %s %d", &p_user.userID, p_user.passWord, p_user.name, p_user.dept, &p_user.expr) != EOF)
    {
        if (userID == p_user.userID)
        {
            found = 1;
            printf("\n \t __PROFESSOR DETAILS__ \n\n");
            printf("User ID/Emp ID : %d \n", p_user.userID);
            printf("Professor Name: %s \n", p_user.name);
            printf("Department: %s \n", p_user.dept);
            printf("Years of Experience: %d \n", p_user.expr);
            
            break;
        }
    }
    if (!found)
    {
        printf("User not found. \n");
    }
    fclose(fp);

    printf("Press '0' to visit Professor Screen.\n");
    printf("Press '1' to Exit.\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 0:
        printf("Directing to Professor Screen.......\n");
        Sleep(3000);
        p_signIn_scrn();
        break;
    case 1:
        thanks();
        exit(0);
    default:
        break;
    }
}

void p_modifyDetails() 
{
    title();
    printf("\n\t [PROFESSOR] ___Modify Details___ \n\n\n");

    struct Professor p_user;
    FILE *fp = fopen("professor.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening files.\n");
        if (fp != NULL) fclose(fp);
        if (temp != NULL) fclose(temp);
        return;
    }

    int userID, i, choice, expr;
    int found = 0;
    char new_name[100];
    char new_dept[100];
    char ch[5];

    printf("Enter User ID/Emp ID : ");
    scanf("%d", &userID);

    while (fscanf(fp, "%d %s %s %s %d", &p_user.userID, p_user.passWord, p_user.name, p_user.dept, &p_user.expr) != EOF)
    {
        if (userID == p_user.userID)
        {
            found = 1;

            do {
                printf("\n\t__PROFESSOR DETAILS__\n\n");
                printf("User ID/Emp ID : %d\n", p_user.userID);
                printf("Professor Name: %s\n", p_user.name);
                printf("Department: %s\n", p_user.dept);
                printf("Years of Experience: %d\n", p_user.expr);

                printf("\n\nWhat do you want to MODIFY/UPDATE?\n\n");
                printf("1.. Name\n");
                printf("2.. Department\n");
                printf("3.. Years of Experience\n");
                printf("4.. No changes\n\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                case 1:
                    printf("Enter new Name: ");
                    scanf(" %[^\n]s", new_name);
                    strcpy(p_user.name, new_name);
                    break;
                case 2:
                    printf("Enter new Department: ");
                    scanf(" %[^\n]s", new_dept);
                    strcpy(p_user.dept, new_dept);
                    break;
                case 3:
                    do {
                        printf("Enter Years of Experience: ");
                        scanf("%d", &expr);
                        if (expr <= p_user.expr) {
                            printf("Enter experience greater than the previous years of experience (%d).\n", p_user.expr);
                        }
                    } while (expr <= p_user.expr);
                    p_user.expr = expr;
                    break;
                case 4:
                    printf("...No Changes...\n");
                    break;
                default:
                    printf("Invalid choice.\n");
                    continue;
                }

                printf("\n\nWant to MODIFY/UPDATE any more Details? (Y/N): ");
                scanf("%s", ch);
            } while (ch[0] == 'Y' || ch[0] == 'y');
        }

        // Write the (modified) record to the temporary file
        fprintf(temp, "%d %s %s %s %d", p_user.userID, p_user.passWord, p_user.name, p_user.dept, p_user.expr);
        fprintf(temp, "\n");
    }

    fclose(fp);
    fclose(temp);

    // Replace the original file with the temporary file
    remove("professor.txt");
    rename("temp.txt", "professor.txt");

    if (!found) {
        printf("User not found.\n");
    }

    p_viewDetails();
}

void p_modifyStudentDetails()
{
    //s_modifyDetails()
    title();
    printf("\n\t [STUDENT] ___Modify Details___ \n\n\n");

    struct Student s_user;
    FILE *fp = fopen("student.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening files.\n");
        if (fp != NULL) fclose(fp);
        if (temp != NULL) fclose(temp);
        return;
    }

    int userID, i, choice, sem;
    int found = 0;
    char new_name[100];
    char new_dept[100];
    float new_sgpa, new_cgpa;
    char ch[5];

    printf("Enter User ID/Roll No.: ");
    scanf("%d", &userID);

    while (fscanf(fp, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF) {
        for (i = 0; i < s_user.semester; i++) {
            fscanf(fp, "%f", &s_user.sgpa[i]);
        }

        if (userID == s_user.userID) {
            found = 1;

            do {
                printf("\n\t__STUDENT DETAILS__\n\n");
                printf("User ID/Roll No.: %d\n", s_user.userID);
                printf("Student Name: %s\n", s_user.name);
                printf("Department: %s\n", s_user.dept);
                printf("Current Semester: %d\n", s_user.semester);
                printf("Semester\tSGPA\n");
                for (i = 0; i < s_user.semester; i++) {
                    printf("%d\t\t%.2f\n", i + 1, s_user.sgpa[i]);
                }
                printf("CGPA: %.2f\n", s_user.cgpa);

                printf("\n\nWhat do you want to MODIFY/UPDATE?\n\n");
                printf("1.. Name\n");
                printf("2.. Department\n");
                printf("3.. Current Semester\n");
                printf("4.. SGPA\n");
                printf("5.. CGPA\n");
                printf("6.. No changes\n\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                case 1:
                    printf("Enter new Name: ");
                    scanf(" %[^\n]s", new_name);
                    strcpy(s_user.name, new_name);
                    break;
                case 2:
                    printf("Enter new Department: ");
                    scanf(" %[^\n]s", new_dept);
                    strcpy(s_user.dept, new_dept);
                    break;
                case 3:
                    do {
                        printf("Enter Current Semester: ");
                        scanf("%d", &sem);
                        if (sem <= s_user.semester) {
                            printf("Enter a semester greater than the current semester (%d).\n", s_user.semester);
                        }
                    } while (sem <= s_user.semester);
                    s_user.semester = sem;
                    break;
                case 4:
                    printf("Enter semester of which you want to add/update SGPA: ");
                    scanf("%d", &sem);
                    printf("Enter SGPA: ");
                    scanf("%f", &new_sgpa);
                    s_user.sgpa[sem - 1] = new_sgpa;
                    break;
                case 5:
                    printf("Enter updated CGPA: ");
                    scanf("%f", &new_cgpa);
                    s_user.cgpa = new_cgpa;
                    break;
                case 6:
                    printf("...No Changes...\n");
                    break;
                default:
                    printf("Invalid choice.\n");
                    continue;
                }

                printf("\n\nWant to MODIFY/UPDATE any more Details? (Y/N): ");
                scanf("%s", ch);
            } while (ch[0] == 'Y' || ch[0] == 'y');
        }

        // Write the (modified) record to the temporary file
        fprintf(temp, "%d %s %s %s %d %.2f", s_user.userID, s_user.passWord, s_user.name, s_user.dept, s_user.semester, s_user.cgpa);
        for (int i = 0; i < s_user.semester; i++) {
            fprintf(temp, " %.2f", s_user.sgpa[i]);
        }
        fprintf(temp, "\n");
    }

    fclose(fp);
    fclose(temp);

    // Replace the original file with the temporary file
    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (!found) {
        printf("User not found.\n");
    }

    //s_viewDetails()
    title();
    printf("\n\t [STUDENT] ___View Details___ \n\n\n");

    FILE *fn = fopen("student.txt", "r");

    printf("Enter User ID/Roll No. : ");
    scanf("%d", &userID);

    while (fscanf(fn, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF)
    {
        for (i = 0; i < s_user.semester; i++)
        {
            fscanf(fn, "%f", &s_user.sgpa[i]);
        }

        if (userID == s_user.userID)
        {
            found = 1;
            printf("\n \t __STUDENT DETAILS__ \n\n");
            printf("User ID/Roll No. : %d \n", s_user.userID);
            printf("Student Name: %s \n", s_user.name);
            printf("Department: %s \n", s_user.dept);
            printf("Current Semester: %d \n", s_user.semester);
            printf("Semester \t SGPA \n");

            for (i = 0; i < s_user.semester; i++)
            {
                printf("%d \t\t %.2f \n", i+1, s_user.sgpa[i]);
            }

            printf("CGPA: %.2f \n", s_user.cgpa);
            break;
        }
    }
    if (!found)
    {
        printf("User not found. \n");
    }
    fclose(fn);

    printf("Press '0' to visit Professor Screen.\n");
    printf("Press '1' to Exit.\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 0:
        printf("Directing to Professor Screen.......\n");
        Sleep(3000);
        p_signIn_scrn();
        break;
    case 1:
        thanks();
        exit(0);
    default:
        break;
    }
}

void p_viewStudentDetails()
{
    title();

    struct  Student s_user;
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL){
        printf("No records found.\n");
        return;
    }

    int i, choice;
    printf("\n\n \t ___LIST OF STUDENTS___ \n\n");
    while (fscanf(fp, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF)
    {
        for (i = 0; i < s_user.semester; i++)
        {
            fscanf(fp, "%f", &s_user.sgpa[i]);
        }

        if (s_user.userID)
        {
            printf("User ID/Roll No. : %d \n", s_user.userID);
            printf("Student Name: %s \n", s_user.name);
            printf("Department: %s \n", s_user.dept);
            printf("Current Semester: %d \n", s_user.semester);
            printf("Semester \t SGPA \n");

            for (i = 0; i < s_user.semester; i++)
            {
                printf("%d \t\t %.2f \n", i+1, s_user.sgpa[i]);
            }

            printf("CGPA: %.2f \n", s_user.cgpa);
            
            printf("\n\n");
        }
    }
    fclose(fp);

    printf("Press '0' to visit Professor Screen.\n");
    printf("Press '1' to Exit.\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 0:
        printf("Directing to Professor Screen.......\n");
        Sleep(3000);
        p_signIn_scrn();
        break;
    case 1:
        thanks();
        exit(0);
    default:
        break;
    }
}

void p_removeStudent()
{
    //s_delete()
    title();
    printf("\n ___ [STUDENT] Delete/Remove User ___ \n\n");

    int userID;
    while (1)
    {
        printf("Enter User ID/Roll No. : ");
        scanf("%d", &userID);

        if (!s_user_exists(userID))
        {
            printf("The user doesn't exists on our records.\n");
        }
        else
        {
            break;
        }
    }

    struct Student s_user;
    FILE *fp = fopen("student.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening files.\n");
        if (fp != NULL)
            fclose(fp);
        if (temp != NULL)
            fclose(temp);
        return;
    }
    while (fscanf(fp, "%d %s %s %s %d %f", &s_user.userID, s_user.passWord, s_user.name, s_user.dept, &s_user.semester, &s_user.cgpa) != EOF)
    {
        for (int i = 0; i < s_user.semester; i++)
        {
            fscanf(fp, "%f", &s_user.sgpa[i]);
        }
        if (s_user.userID != userID)
        {
            fprintf(temp, "%d %s %s %s %d %f", s_user.userID, s_user.passWord, s_user.name, s_user.dept, s_user.semester, s_user.cgpa);
            for (int i = 0; i < s_user.semester; i++)
            {
                fprintf(temp, " %f", s_user.sgpa[i]);
            }
            fprintf(temp, "\n");
        }
    }
    fclose(fp);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    printf("\n User deleted successfully.\n\n");
    printf("Directing to Professor Login page.......\n");
    Sleep(3000);
    p_login();
}

void log_out()
{
    main();
    return;
}

void thanks()
{
    system("cls");
    printf("\n\n\t");
    for (int i = 1; i <= 19; i++)
    {
        printf("=");
    }
    printf(" KIIT University Management System ");
    for (int i = 1; i <= 19; i++)
    {
        printf("=");
    }
    printf("\n\n\n\n\n");
    printf("\t\t _____________________________________________\n\n");
    printf("\t\t\t     Thanks for Visiting!!\n\n");
    printf("\t\t ---------------------------------------------\n\n");
}
