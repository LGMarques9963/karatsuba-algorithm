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

char *shiftLeft(char *str, int len, int n){
    return shift(str, len, n, 1);
}

char *shiftRight(char *str, int len, int n) {
    return shift(str, len, n, 0);
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
    int lenA = strlen(strA);
    int lenB = strlen(strB);
    if (lenA - lenB > 0) {
        strB = shiftRight(strB, lenB, lenA - lenB);
    } else if (lenB - lenA > 0) {
        strA = shiftRight(strA, lenA, lenB - lenA);
    }
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
    int lenA = strlen(strA);
    int lenB = strlen(strB);
    if (lenA - lenB > 0) {
        strB = shiftRight(strB, lenB, lenA - lenB);
    } else if (lenB - lenA > 0) {
        strA = shiftRight(strA, lenA, lenB - lenA);
    }
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
    return result;
}

char *karatsuba(char *strA, char *strB, int len) {
    if (len == 1) {
        char *result = malloc(1);
        return memset(result, mult(strA[0], strB[0]), 1);
    }
    int newLen = len / 2;
    char *a1 = malloc(newLen);
    char *a2 = malloc(newLen);
    char *b1 = malloc(newLen);
    char *b2 = malloc(newLen);
    for (int i = 0; i < newLen; i++) {
        a1[i] = strA[i];
        a2[i] = strA[i + newLen];
        b1[i] = strB[i];
        b2[i] = strB[i + newLen];
    }
    char *a1b1 = karatsuba(a1, b1, newLen);
    char *a2b2 = karatsuba(a2, b2, newLen);
    char *a1a2 = somaStr(a1, a2);
    char *b1b2 = somaStr(b1, b2);
    char *s1 = karatsuba(a1a2, b1b2, newLen);
    char *s2 = subStr(s1, a1b1);
    char *p3 = subStr(s2, a2b2);

    char *p1 = shiftLeft(a1b1, newLen, 2);
    char *p2 = a2b2;
    printf("P1: %s\n", p1);
    printf("P2: %s\n", a2b2);
    printf("P3: %s\n", p3);
    char *result = somaStr(p1, p2);
    result = somaStr(result, p3);
    return result;


}

int main(int argc, char *argv[]){

    char *strA = argv[1];
    char *strB = argv[2];
    int len = strlen(strA);
    int len2 = strlen(strB);
    int dif = len - len2;
    if (dif > 0) {
        strB = shiftRight(strB, len2, dif);
    } else if (dif < 0) {
        strA = shiftRight(strA, len, -dif);
    }
    printf("String A: %s\n", strA);
    printf("String B: %s\n", strB);;
    printf("Soma: %s\n", karatsuba(strA, strB, len));
    /** TO-DO: paramêtros 10110 e 1101101 quebraram o algoritmo da soma, preciso encontrar o problema e corrigir */
    return 0;

}
