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
int main(int argc, char *argv[]){

    char *strA = argv[1];
    char *strB = argv[2];
    int len = strlen(strA);
    int len2 = strlen(strB);
    printf("String A: %s\n", strA);
    printf("String B: %s\n", strB);;
    printf("Soma: %s\n", somaStr(strA, strB));
    /** TO-DO: paramêtros 10110 e 1101101 quebraram o algoritmo da soma, preciso encontrar o problema e corrigir */
    return 0;

}
