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

void particiona(char **str, char **x1, char **x2) {
    int len = strlen(*str);
    if (len % 2 != 0) {
        *str = shiftRight(*str, len, 1);
        len += 1;
    }
    int meio = len / 2;
    *x1 = malloc(meio + 1);
    *x2 = malloc(meio +  1); 
    strncpy(*x1, *str, meio);
    strncpy(*x2, *str + meio, meio);
    (*x1)[meio] = '\0';
    (*x2)[meio] = '\0';
}

char *karatsuba(char *strA, char *strB, int *call) {
    int lenA = strlen(strA);
    int lenB = strlen(strB);
    *call += 1;
    char *tab = malloc(*call + 1);
    tab=memset(tab, '\t', *call);
    printf("%sRecebido: A = %s, B = %s\n", tab, strA, strB);
    if (lenA == 1 && lenB == 1) {
        char *result = malloc(1);
        result[0] = mult(strA[0], strB[0]);
        return result;
    }
    if (lenA != lenB) {
        normalize(&strA, &strB);
    }
    int len = strlen(strA);
    char *a1 = malloc(len / 2 + 1);
    char *a2 = malloc(len / 2 + 1);
    char *b1 = malloc(len / 2 + 1);
    char *b2 = malloc(len / 2 + 1);
    particiona(&strA, &a1, &a2);
    particiona(&strB, &b1, &b2);
    printf("%sa1: %s\n", tab, a1);
    printf("%sa2: %s\n", tab, a2);
    printf("%sb1: %s\n", tab, b1);
    printf("%sb2: %s\n", tab, b2);
    printf("%sChamando a1 * b1\n", tab);
    char *p1 = karatsuba(a1, b1, call);
    printf("%sp1: %s\n", tab, p1);
    printf("%sChamando a2 * b2\n", tab);
    char *p2 = karatsuba(a2, b2, call);
    printf("%sp2: %s\n", tab, p2);
    printf("%sChamando (a1 + a2) * (b1 + b2)\n", tab);
    char *a1a2 = somaStr(a1, a2);
    printf("%sa1a2: %s\n", tab, a1a2); // TO-DO: a1a2 está com problema (10110 e 1101101
    char *b1b2 = somaStr(b1, b2);
    printf("%sb1b2: %s\n", tab, b1b2);
    char *p3 = karatsuba(a1a2, b1b2, call);
    printf("%sp3: %s\n", tab, p3);
    printf("%sCalculando p4\n", tab);
    char *p4 = subStr(p3, somaStr(p1, p2));
    printf("%sp4: %s\n", tab, p4);
    char *result;
    int m = floor(len / 2);
    p1 = shiftLeft(p1, strlen(p1), 2*m);
    printf("%sp1 shiftado: %s\n", tab, p1);
    p4 = shiftLeft(p4, strlen(p4), m);
    printf("%sp4 shiftado: %s\n", tab, p4);
    result = somaStr(p1, p2);
    printf("%sp1 + p2: %s\n", tab, result);
    result = somaStr(result, p4);
    printf("%sp1 + p2 + p4: %s\n", tab, result);
    return result;

}

int main(int argc, char *argv[]){

    char *strA = argv[1];
    char *strB = argv[2];
    int call = 0;
    normalize(&strA, &strB);
    printf("String A: %s\n", strA);
    printf("String B: %s\n", strB);
    printf("Soma: %s\n", karatsuba(strA, strB, &call));
    // char *a1;
    // char *a2;
    // particiona(&strA, &a1, &a2);
    // printf("a1: %s\n", a1);
    // printf("a2: %s\n", a2);
    /** TO-DO: paramêtros 10110 e 1101101 quebraram o algoritmo da soma, preciso encontrar o problema e corrigir */
    return 0;

}
