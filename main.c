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
        if (carry == '0' && res == '2') {
            result[i] = '0';
            carry = '1';
        } else if (carry == '0' && res == '1') {
            result[i] = '1';
            carry = '0';
        } else if (carry == '0' && res == '0') {
            result[i] = '0';
            carry = '0';
        } else if(carry == '1' && res == '1'){
            result[i] = '1';
            carry = '1';
        }else if(carry == '1' && res == '2') {
            result[i] = '0';
            carry = '1';
        } else if (carry == '1' && res == '0') {
            result[i] = '1';
            carry = '0';
        }
    }
    return result;
}
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
    printf("Soma: %s\n", somaStr(strA, strB));
    return 0;

}
