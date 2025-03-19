#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <bits/stdc++.h>
using namespace std;

char *concatenate_strings(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
    if (result == NULL) {
        perror("malloc failed");
        return NULL;
    }
    strcpy(result, str1);
    strcpy(result + len1, str2);
    return result;
}

char* char_to_char_ptr(char c) {
    char* str = (char*)malloc(2 * sizeof(char));
    if (str == NULL) {
        perror("malloc failed");
    }
    str[0] = c;
    str[1] = '\0';
    return str;
}
#endif
