#include <stdio.h>
#include <string.h>

int login() {
    char username[20];
    char password[20];

    // hardcoded credentials
    char correct_user[] = "admin";
    char correct_pass[] = "1234";

    printf("\n========== LOGIN ==========\n");
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, correct_user) == 0 &&
        strcmp(password, correct_pass) == 0) {
        return 1;   // login success
    } else {
        return 0;   // login failed
    }
}
