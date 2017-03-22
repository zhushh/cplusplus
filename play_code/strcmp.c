#include <stdio.h>

int main() {
    char str1[100], str2[100];
    int i, len1, len2;
    printf("Input string a:\n");
    fgets(str1, sizeof(str1), stdin);
    printf("Input string b:\n");
    fgets(str2, sizeof(str2), stdin);
    for (len1 = 0; str1[len1] != '\n'; ++len1);
    for (len2 = 0; str2[len2] != '\n'; ++len2);
    for (i = 0; i < len1 && i < len2; ++i) {
        if (str1[i] != str2[i]) {
            printf("The different position is %d\n", i + 1);
            break;
        }
    }
    if (i == len1 || i == len2) {
        if (len1 > len2) printf("string a is bigger than string b\n");
        if (len1 == len2) printf("string a is equal to string b\n");
        if (len1 < len2) printf("string a is less than string b\n");
    } else {
        if (str1[i] > str2[i])
            printf("string a is bigger than string b\n");
        if (str1[i] < str2[i])
            printf("string a is less than string b\n");
    }
    return 0;
}


