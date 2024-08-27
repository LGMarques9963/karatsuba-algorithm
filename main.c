#include <stdio.h>
#include <string.h>

char mult(char a, char b) {
    return (a == '1' && b == '1') ? '1' : '0'; // forçando o retorno manter em string
}

char *shiftLeft(char *str, int len, int shift){
    char temp[len];
    char shifted[shift];
    int i;
    for (i = 0; i < shift; i++){
        shifted[i] = '0';
    }
    shifted[shift] = '\0';
    return strcat(str, shifted);
    
}

int main(int argc, char *argv[]){

    char *str = argv[1];
    int len = strlen(str);
    int i;
    printf("String: %s\n", str);
    char *temp = shiftLeft(str, len, 1);
    printf("Shifted string: %s\n", temp);
    return 0;

}
