#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define QTD_COMODOS 3
#define SENHA_CORRETA "1234"

const char *comodos[QTD_COMODOS] = {"Sala", "Quarto", "Cozinha"};
bool sensores[QTD_COMODOS] = {false, false, false};
bool alarmeAtivado = false;
bool alarmeDisparado = false;
int localDisparo = -1;

void ativarAlarme() {
    char senha[10];
    printf("Digite a senha: ");
    scanf("%9s", senha);
    if (strcmp(senha, SENHA_CORRETA) == 0) {
        alarmeAtivado = true;
        alarmeDisparado = false;
        localDisparo = -1;
        printf("Alarme ativado com sucesso.\n");
    } else {
        printf("Senha incorreta!\n");
    }
}

void desativarAlarme() {
    char senha[10];
    printf("Digite a senha: ");
    scanf("%9s", senha);
    if (strcmp(senha, SENHA_CORRETA) == 0) {
        alarmeAtivado = false;
        alarmeDisparado = false;
        localDisparo = -1;
        for (int i = 0; i < QTD_COMODOS; i++) sensores[i] = false;
        printf("Alarme desativado com sucesso.\n");
    } else {
        printf("Senha incorreta!\n");
    }
}

void simularMovimento() {
    int escolha;
    printf("Escolha o cômodo (0: Sala, 1: Quarto, 2: Cozinha): ");
    scanf("%d", &escolha);
    if (escolha < 0 || escolha >= QTD_COMODOS) {
        printf("Cômodo inválido!\n");
        return;
    }
    sensores[escolha] = true;
    if (alarmeAtivado) {
        alarmeDisparado = true;
        localDisparo = escolha;
        printf("[ALERTA] Movimento detectado em: %s! Alarme disparado!\n", comodos[escolha]);
    } else {
        printf("Movimento detectado em: %s, mas o alarme está desativado.\n", comodos[escolha]);
    }
}

void verStatus() {
    printf("Status: Alarme %s\n", alarmeAtivado ? "ATIVADO" : "DESATIVADO");
    for (int i = 0; i < QTD_COMODOS; i++) {
        printf("%s: %s\n", comodos[i], sensores[i] ? "Movimento detectado" : "Sem movimento");
    }
    if (alarmeDisparado && localDisparo >= 0) {
        printf("Alarme disparado em: %s!\n", comodos[localDisparo]);
    }
}

int main() {
    int opcao;
    do {
        printf("\n--- Sistema de Alarme Residencial ---\n");
        printf("1. Ativar alarme\n2. Desativar alarme\n3. Simular movimento\n4. Ver status\n5. Sair\nEscolha: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                ativarAlarme();
                break;
            case 2:
                desativarAlarme();
                break;
            case 3:
                simularMovimento();
                break;
            case 4:
                verStatus();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);
    return 0;
}