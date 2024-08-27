#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char mult(char a, char b) {
    return (a == '1' && b == '1') ? '1' : '0'; // forçando o retorno manter em string
}

char *shift(char *str, int len, int shift, int left) {
    char *shifted = malloc(len + shift + 1);
    if (left) {
        strcat(shifted, str);
        memset(shifted + len, '0', shift);
    } else {
        memset(shifted, '0', shift);
        strcat(shifted, str);
    }
    return shifted;
}

char *shiftLeft(char *str, int len, int shift){
    return shift(str, len, shift, 1);
}

char *shiftRight(char *str, int len, int shift) {
    return shift(str, len, shift, 0);
}

// char somaStr(char *a, char *b) {
//     int lenStrA = strlen(a);
//     int lenStrB = strlen(b);
//     if (lenStrA - lenStrB > 0) {
//     }
// }

int main(int argc, char *argv[]){

    char *strA = argv[1];
    char *strB = argv[2];
    int len = strlen(strA);
    int len2 = strlen(strB);
    printf("String A: %s\n", strA);
    char *temp = shiftLeft(strA, len, 1);
    printf("String B: %s\n", strB);
    char *temp2 = shiftRight(strB, len2, 1);
    printf("Shifted string: %s\n", temp);
    printf("Shifted string: %s\n", temp2);
    return 0;

}
