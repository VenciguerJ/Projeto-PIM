#include <stdio.h>
#include <conio.h>

void getSenha(char *tenta_senha) {
    int c = 0;
    char password[11];
    
    while ((tenta_senha[c] = getch()) != 13) { // 13 é o código ASCII para a tecla "Enter"
        printf("%c", '*'); // Exibe '*' no lugar do caractere digitado
        c++;
    }
    
    tenta_senha[c] = '\0'; // Adiciona o terminador de string à senha inserida
}

int main() {
    char senha[12]; // A senha terá no máximo 11 caracteres + terminador de string '\0'

    printf("Digite a senha: ");
    getSenha(senha);
    
    printf("\nSenha digitada: %s\n", senha);

    return 0;
}
