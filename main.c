#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char mult(char a, char b) {
    return (a == '1' && b == '1') ? '1' : '0'; // forçando o retorno manter em string
}

char *shift(char *str, int len, int shift, int left) {
    // char *shifted = malloc(len + shift + 1);
    // if (left) {
    //     strcat(shifted, str);
    //     memset(shifted + len, '0', shift);
    // } else {
    //     memset(shifted, '0', shift);
    //     strcat(shifted, str);
    // }
    // return shifted;

    char *shifted = malloc(len + shift + 1);
    memset(shifted, '0', len + shift);
    shifted[len + shift] = '\0';
    if (left) {
        strncpy(shifted, str, len);
    } else {
        strncpy(shifted + shift, str, len);
    }
    return shifted;
}

char *shiftLeft(char *str, int len, int n){
    return shift(str, len, n, 1);
}

char *shiftRight(char *str, int len, int n) {
    return shift(str, len, n, 0);
}

void normalize(char **strA, char **strB) {
    int lenA = strlen(*strA);
    int lenB = strlen(*strB);
    if (lenA > lenB) {
        *strB = shiftRight(*strB, lenB, lenA - lenB);
    } else if (lenB > lenA) {
        *strA = shiftRight(*strA, lenA, lenB - lenA);
    }
}

char soma(char a, char b){
    if (a == '1' && b == '1') {
        return '2';
    }else if ((a == '1' && b == '0') || (a == '0' && b == '1')){
        return '1';
    
    }else {
        return '0';
    }
}

char *somaStr(char *strA, char *strB) {
    char carry = '0';
    normalize(&strA, &strB);
    int len = strlen(strA);
    char *result = malloc(len + 1);
    result = memset(result, '0', len);
    for (int i = len - 1; i >= 0; i--) {
        char res = soma(strA[i], strB[i]);
        switch (res) {
            case '0':
                if (carry == '0') {
                    result[i] = '0';
                    carry = '0';
                } else {
                    result[i] = '1';
                    carry = '0';
                }
                break;
            case '1':
                if (carry == '0') {
                    result[i] = '1';
                    carry = '0';
                } else {
                    result[i] = '0';
                    carry = '1';
                }
                break;
            case '2':
                if (carry == '0') {
                    result[i] = '0';
                    carry = '1';
                } else {
                    result[i] = '1';
                    carry = '1';
                }
                break;
        }
    }
    if (carry == '1') {
        result = shiftRight(result, len, 1);
        result[0] = '1';
    }
    result[strlen(result) + 1] = '\0';
    return result;
}

char sub(char a, char b) {
    if (a == '1' && b == '1') {
        return '0';
    } else if (a == '0' && b == '1') {
        return '2';
    } else if (a == '1' && b == '0') {
        return '1';
    } else {
        return '0';
    }
}

char *subStr(char *strA, char *strB) {
    char borrow = '0';
    normalize(&strA, &strB); // normaliza os tamanhos das strings (completando com zeros à esquerda)
    int len = strlen(strA);
    char *result = malloc(len);
    result = memset(result, '0', len);
    for (int i = len - 1; i >= 0; i--) {
        char res = sub(strA[i], strB[i]);
        switch (res) {
            case '0':
                if (borrow == '0') {
                    result[i] = '0';
                    borrow = '0';
                } else {
                    result[i] = '1';
                    borrow = '1';
                }
                break;
            case '1':
                if (borrow == '0') {
                    result[i] = '1';
                    borrow = '0';
                } else {
                    result[i] = '0';
                    borrow = '0';
                }
                break;
            case '2':
                if (borrow == '0') {
                    result[i] = '1';
                    borrow = '1';
                } else {
                    result[i] = '0';
                    borrow = '1';
                }
                break;
        }
    }
    result[strlen(result) + 1] = '\0';
    return result;
}


char *karatsuba(char *strA, char *strB, int len) {
    int lenA = strlen(strA);
    int lenB = strlen(strB);
    if (lenA == 1 && lenB == 1) {
        char *result = malloc(1);
        result[0] = mult(strA[0], strB[0]);
        return result;
    }
    char *resp = karatsuba(strA, strB, len / 2);
}

int main(int argc, char *argv[]){

    char *strA = argv[1];
    char *strB = argv[2];
    // int len = strlen(strA);
    // int len2 = strlen(strB);
    // int dif = len - len2;
    // if (dif > 0) {
    //     strB = shiftRight(strB, len2, dif);
    // } else if (dif < 0) {
    //     strA = shiftRight(strA, len, -dif);
    // }
    normalize(&strA, &strB);
    printf("String A: %s\n", strA);
    printf("String B: %s\n", strB);
    printf("Soma: %s\n", subStr(strA, strB));
    /** TO-DO: paramêtros 10110 e 1101101 quebraram o algoritmo da soma, preciso encontrar o problema e corrigir */
    return 0;

}
