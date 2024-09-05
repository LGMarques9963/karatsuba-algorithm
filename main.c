#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char mult(char a, char b) {
    /** Função que realiza a multiplicação de dois bits
        Input:
            a: bit A
            b: bit B
        Output:
            Resultado da multiplicação dos bits
     */
    return (a == '1' && b == '1') ? '1' : '0'; // retorna 1 se os dois bits forem 1, caso contrário, retorna 0
}

char *shift(char *str, int len, int shift, int left) {
    /** Função que realiza shift left ou right de uma string
        Input:
            str: string a ser deslocada
            len: tamanho da string
            shift: quantidade de deslocamento
            left: flag que indica se o deslocamento é para a esquerda (1) ou direita (0)
     */
    char *shifted = malloc(len + shift + 1); // aloca espaço para a string deslocada
    memset(shifted, '0', len + shift); // preenche a string com zeros
    shifted[len + shift] = '\0'; // adiciona o caractere de fim de string
    if (left) {
        strncpy(shifted, str, len); // copia a string original para a string deslocada até o tamanho da string original, completando com zeros à direita (shift left)
    } else {
        strncpy(shifted + shift, str, len); // copia a string original para a string deslocada a partir da posição de deslocamento, completando com zeros à esquerda (shift right)
    }
    return shifted; // retorna a string deslocada
}

char *shiftLeft(char *str, int len, int n){
    /** Função para realizar o shift left de uma string
        Input:
            str: string a ser deslocada
            len: tamanho da string
            n: quantidade de deslocamento
     */
    return shift(str, len, n, 1); // chama a função de shift passando a flag left como 1
}

char *shiftRight(char *str, int len, int n) {
    /** Função para realizar o shift right de uma string
        Input:
            str: string a ser deslocada
            len: tamanho da string
            n: quantidade de deslocamento
     */
    return shift(str, len, n, 0); // chama a função de shift passando a flag left como 0
}

void normalize(char **strA, char **strB) {
    /** Função para deixar duas strings com o mesmo tamanho
        Input:
            strA: string A passada por referência
            strB: string B passada por referência
     */
    int lenA = strlen(*strA); // obtém o tamanho da string A
    int lenB = strlen(*strB); // obtém o tamanho da string B

    /**
        Se o tamanho da string A for maior que o tamanho da string B, desloca a string B para a direita
        Se o tamanho da string B for maior que o tamanho da string A, desloca a string A para a direita
    */
    if (lenA > lenB) {
        *strB = shiftRight(*strB, lenB, lenA - lenB);
    } else if (lenB > lenA) {
        *strA = shiftRight(*strA, lenA, lenB - lenA);
    }
}

char soma(char a, char b){
    /** 
        Função que realiza a soma de dois bits
        Input:
            a: bit A
            b: bit B
        Output:
            Resultado da soma dos bits
    */
    if (a == '1' && b == '1') {
        return '2'; // retorna 2 para indicar que o resultado do bit é 0 e o carry é 1
    }else if ((a == '1' && b == '0') || (a == '0' && b == '1')){ 
        return '1'; // retorna 1 para indicar que o resultado do bit é 1 e o carry é 0
    }else {
        return '0'; // retorna 0 para indicar que o resultado do bit é 0 e o carry é 0
    }
}

char *somaStr(char *strA, char *strB) {
    /** 
        Função que realiza a soma de duas strings de bits
        Input:
            strA: string A
            strB: string B
        Output:
            Resultado da soma das strings
    */

    /**
        Inicializa o carry com 0
        Normaliza os tamanhos das strings
        Aloca espaço para a string de resultado
        Preenche a string de resultado com zeros
        Itera sobre as strings de trás para frente
        Realiza a soma dos bits
        Atualiza o carry
        Retorna a string de resultado
     */
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

    /**
        Se o carry for 1 ao final da iteração, desloca a string de resultado para a direita e adiciona 1 no início    
    */
    if (carry == '1') {
        result = shiftRight(result, len, 1);
        result[0] = '1';
    }
    return result;
}

char sub(char a, char b) {
    /**
        Função que realiza a subtração de dois bits
        Input:
            a: bit A
            b: bit B
        Output:
            Resultado da subtração dos bits
    */
    if (a == '1' && b == '1') {
        return '0'; // retorna 0 para indicar que o resultado do bit é 0 e o borrow é 0
    } else if (a == '0' && b == '1') {
        return '2'; // retorna 2 para indicar que o resultado do bit é 1 e o borrow é 1
    } else if (a == '1' && b == '0') {
        return '1'; // retorna 1 para indicar que o resultado do bit é 1 e o borrow é 0
    } else {
        return '0'; // retorna 0 para indicar que o resultado do bit é 0 e o borrow é 0
    }
}

char *subStr(char *strA, char *strB) {
    /**
        Função que realiza a subtração de duas strings de bits
        Input:
            strA: string A
            strB: string B
        Output:
            Resultado da subtração das strings
    */

    /**
        Inicializa o borrow com 0
        Normaliza os tamanhos das strings
        Aloca espaço para a string de resultado
        Preenche a string de resultado com zeros
        Itera sobre as strings de trás para frente
        Realiza a subtração dos bits
        Atualiza o borrow
        Retorna a string de resultado
    */

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
    return result;
}

void particiona(char **str, char **x1, char **x2) {
    /**
        Função que particiona uma string em duas partes
        Input:
            str: string a ser particionada passada por referência
            x1: string que armazenará a primeira parte passada por referência
            x2: string que armazenará a segunda parte passada por referência
    */

    /**
        Calcula o tamanho da string
        Calcula o ponto de partição
     */
    int len = strlen(*str);
    int part = len / 2;

    /**
        Aloca espaço para as strings x1 e x2
     */
    *x1 = malloc(len + 1);
    *x2 = malloc(len + 1);

    /**
        Copia a primeira parte da string para x1
        Copia a segunda parte da string para x2
     */
    strncpy(*x1, *str, part);
    strncpy(*x2, *str + part, len - part);
}

char *karatsuba(char *strA, char *strB) {
    /**
        Função que implementa o algoritmo de Karatsuba para multiplicação de strings de bits
        Input:
            strA: string A
            strB: string B
            call: contador de chamadas recursivas, usado para debug
        Output:
            Resultado da multiplicação das strings utilizando o algoritmo de Karatsuba
    */
    
    /** 
        Casos Base:
            Se a string A não contém 1, retorna 0 
                -> Se uma das strings for inteiramente 0, não é necessário continuar particionando e chamar a recursão, o resultado é certamente 0
                -> Acelera o processo para strings de tamanho maior que 1 que contenham apenas 0s
            Se a string B não contém 1, retorna 0 
                -> Se uma das strings for inteiramente 0, não é necessário continuar particionando e chamar a recursão, o resultado é certamente 0
                -> Acelera o processo para strings de tamanho maior que 1 que contenham apenas 0s
            Se a string A é 1, retorna a string B 
                -> Se uma das strings for 1, não é necessário continuar particionando e chamar a recursão, o resultado é certamente a outra string                
            Se a string B é 1, retorna a string A 
                -> Se uma das strings for 1, não é necessário continuar particionando e chamar a recursão, o resultado é certamente a outra string
            Se as strings possuem tamanho 1, retorna o resultado da multiplicação dos bits 
                -> Se as strings possuem tamanho 1, o resultado é a multiplicação dos bits
                -> Possivelmente nunca caia nesse caso devido aos casos bases anteriores, mas deixei para garantir
    */ 
    if (strstr(strA, "1") == NULL || strstr(strB, "1") == NULL) {
        return "0";
    }
    if (strcmp(strA,"1") == 0) {
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

    //Normaliza as strings, deixando-as com o mesmo tamanho
    normalize(&strA, &strB);

    /**
        Particiona as strings em duas partes
        Calcula o tamanho da string A
        Calcula o ponto de partição
    */
    char *a1;
    char *a2;
    char *b1;
    char *b2;
    particiona(&strA, &a1, &a2);
    particiona(&strB, &b1, &b2);
    int lenA = strlen(strA);
    int meio = lenA / 2;
    
    
    /**
        Chama a função de Karatsuba para as partições
        Calcula os produtos intermediários
        Calcula o produto final
        
            Fórmula de Karatsuba:
                P1 = a1 * b1
                P2 = a2 * b2
                P3 = (a1 + a2) * (b1 + b2)
                P4 = P3 - P1 - P2
                Resultado = P1 << <<  + P4 << + P2
     */
    char *p1 = karatsuba(a1, b1); // chama a função de Karatsuba para a primeira partição -> a1 * b1
    char *p2 = karatsuba(a2, b2); // chama a função de Karatsuba para a segunda partição -> a2 * b2
    char *p3 = karatsuba(somaStr(a1, a2), somaStr(b1, b2)); // chama a função de Karatsuba para a soma das partições -> (a1 + a2) * (b1 + b2)
    char *p4 = subStr(p3, somaStr(p1, p2)); // calcula o produto intermediário P4 -> P3 - P1 - P2
    char *p1_shifted = shiftLeft(p1, strlen(p1), (lenA - meio) * 2); // desloca o produto P1 para a esquerda
    char *p4_shifted = shiftLeft(p4, strlen(p4), lenA - meio); // desloca o produto P4 para a esquerda
    /** 
        Aloca espaço para o resultado. 
        Prof: o problema que havia comentado no email estava relacionado ao tamanho alocado para armazenar o resultado.
        Como RAM não é mais um problema atualmente, aloquei um espaço do dobro mais um da string original para armazenar o resultado, o que resolveu o problema. 
    */
    char *result = malloc(2*lenA + 1); 
    result = somaStr(somaStr(p1_shifted, p2), p4_shifted); // calcula o resultado final -> P1 << <<  + P4 << + P2

    return result; // retorna o resultado
}

void removeZeros(char **str) {
    /**
        Função que remove os zeros à esquerda de uma string
        Input:
            str: string passada por referência
    */
    int len = strlen(*str); // calcula o tamanho da string
    int i = 0;
    while ((*str)[i] == '0') {
        i++; // encontra o primeiro caractere diferente de zero
    }
    if (i == len) {
        i--; // se a string for inteiramente zero, volta uma posição
    }
    char *newStr = malloc(len - i + 1); // aloca espaço para a nova string
    strncpy(newStr, *str + i, len - i); // copia a string original para a nova string a partir do primeiro caractere diferente de zero
    newStr[len - i] = '\0'; // adiciona o caractere de fim de string
    *str = newStr; // atualiza a string original
}

int main(int argc, char *argv[]){

    /**
        Prof, fiz o código em C para praticar, mas como não tenho muito proficiência provavelmente o código não está muito otimizado, nem implementando boas práticas de C.
        Possivelmente tenha algumas "atrocidades" escritas também.
        Mas é trabalho honesto, acompanhe meu sofrimento pelo histórico de commits :D.
    */


    /**
        Recebe os argumentos da chamada e armazena nas strings strA e strB
        Normaliza as strings, deixando-as com o mesmo tamanho
    */
    char *strA = argv[1];
    char *strB = argv[2];
    normalize(&strA, &strB);


    /**
        Calcula a multiplicação pelo algoritmo de Karatsuba e print o resultado na tela.
        O código foi testado para números de até 10000 bits.
    */
    char *result = karatsuba(strA, strB);
    removeZeros(&result);
    printf("%s\n", result);

    /**
        Prints para debug
     */
    // printf("String A: %s\n", strA);
    // printf("String B: %s\n", strB);
    // printf("Resultado: %s\n", karatsuba(strA, strB));
    return 0;

}
