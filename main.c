#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char mult(char a, char b) {
    return (a == '1' && b == '1') ? '1' : '0'; // forçando o retorno manter em string
}

char *shift(char *str, int len, int shift, int left) {
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
    char *result = malloc(len + 2);
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
    // result[strlen(result) + 1] = '\0';
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
    char *result = malloc(len + 2);
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
    // result[strlen(result) + 1] = '\0';
    return result;
}

void particiona(char **str, char **x1, char **x2) {
    int len = strlen(*str);
    int part = len / 2;

    *x1 = malloc(len + 1);
    *x2 = malloc(len + 1);

    strncpy(*x1, *str, part);
    strncpy(*x2, *str + part, len - part);
    // (*x1)[part] = '\0';
    // (*x2)[len - part] = '\0';
}

char *karatsuba(char *strA, char *strB, int *call) {
    // printf("Chamada: %d\n", *call);
    // *call += 1;
    // printf("String A: %s\n", strA);
    // printf("String B: %s\n", strB);
    // casos base
    if (strstr(strA, "1") == NULL || strstr(strB, "1") == NULL) {
        return "0";
    }
    if (strcmp(strA,"1") == 0) {
        // printf("Retorno: %s\n", strA);
        return strB;
    }
    if (strcmp(strB, "1") == 0) {
        return strA;
    }
    if (strlen(strA) == 1 && strlen(strB) == 1) {
        char *result = malloc(2);
        result[0] = mult(strA[0], strB[0]);
        result[1] = '\0';
        return result;
    }
    // normaliza os tamanhos das strings
    normalize(&strA, &strB);

    // particiona as strings
    char *a1;
    char *a2;
    char *b1;
    char *b2;
    particiona(&strA, &a1, &a2);
    particiona(&strB, &b1, &b2);
    int lenA = strlen(strA);
    int meio = lenA / 2;
    // calcula os produtos
    char *p1 = karatsuba(a1, b1, call);
    char *p2 = karatsuba(a2, b2, call);
    char *p3 = karatsuba(somaStr(a1, a2), somaStr(b1, b2), call);
    char *p4 = subStr(p3, somaStr(p1, p2));
    char *p1_shifted = shiftLeft(p1, strlen(p1), (lenA - meio) * 2);
    char *p4_shifted = shiftLeft(p4, strlen(p4), lenA - meio);
    char *result = malloc(2*lenA + 1);
    result = somaStr(somaStr(p1_shifted, p2), p4_shifted);
    // result[strlen(result) + 1] = '\0';

    return result;
}

int main(int argc, char *argv[]){

    char *strA = argv[1];
    char *strB = argv[2];
    int call = 0;
    normalize(&strA, &strB);
    printf("String A: %s\n", strA);
    printf("String B: %s\n", strB);
    printf("Resultado: %s\n", karatsuba(strA, strB, &call));
    // printf("Resultado: %s\n", subStr(strA, strB));
    // char *a1;
    // char *a2;
    // particiona(&strA, &a1, &a2);
    // printf("a1: %s\n", a1);
    // printf("a2: %s\n", a2);
    /** TO-DO: paramêtros 10110 e 1101101 quebraram o algoritmo da soma, preciso encontrar o problema e corrigir */
    return 0;

}
