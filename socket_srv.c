#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")  // Link para a biblioteca Winsock

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "Erro ao inicializar o Winsock\n");
        return 1;
    }

    // Criar um socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        fprintf(stderr, "Erro ao criar o socket\n");
        WSACleanup();
        return 1;
    }

    // Configurar informações do endereço do servidor
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);  // Porta do servidor
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Endereço IP do servidor

    // Estabelecer uma conexão
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
        fprintf(stderr, "Erro ao conectar ao servidor\n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // O socket está agora conectado e pronto para ser usado.

    // Fechar o socket e limpar o Winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}