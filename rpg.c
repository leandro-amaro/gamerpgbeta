#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <bits/stdio2.h>

typedef struct {
    char nome[30];
    int danoMin;
    int danoMax;
} Arma;

typedef struct {
    char nome[50];
    int vidaAtual;
    int vidaMaxima;
    int ataqueBase;
    int defesa;
    Arma armaEquipada;
    Arma inventario[3];
} Personagem;

int rolarDado(int min, int max) {
    return min + rand() % (max - min + 1);
}

void abrirInventario(Personagem *p) {
    printf("\n---MOCHILA DE %s ---\n", p->nome);
    printf("Arma atual: %s (Dano: %d-%d)\n", p->armaEquipada.nome, p->armaEquipada.danoMin, p->armaEquipada.danoMax);
    printf("Itens na mochila:\n");

    for(int i = 0; i < 3; i++) {
        printf("%d. %s (Dano: %d-%d)\n", i+1, p->inventario[i].nome, p->inventario[i].danoMin, p->inventario[i].danoMax);
    }

    printf("4. Sair\n");
    printf("Escolha uma Arma para equipar: ");

    int escolha;
    scanf("%d", &escolha);

    if (escolha >=1 && escolha <= 3) {
        Arma nova = p->inventario[escolha - 1]; 
        printf("> Voce guardou a %s e equipou a %s!\n", p->armaEquipada.nome, nova.nome);
        p->armaEquipada = nova;
    } else {
        printf("> Voce fechou a mochila\n");
    }
}

int main () {
    srand(time(NULL));

    Arma katanaVelha = {"Katana Enferrujada", 2, 8};
    Arma espadaBastarda = {"Espada Bastarda", 5, 15};
    Arma bokken = {"Espada de Madeira", 1, 4};

    Personagem heroi;
    strcpy(heroi.nome, "Musachi");
    heroi.vidaMaxima = 100;
    heroi.vidaAtual = 100;
    heroi.ataqueBase = 12;
    heroi.defesa = 5;

    heroi.armaEquipada = bokken;

    heroi.inventario[0] = bokken;
    heroi.inventario[1] = katanaVelha;
    heroi.inventario[2] = espadaBastarda;

    Personagem monstro;
    strcpy(monstro.nome, "Dancarina Flamejante");
    monstro.vidaMaxima = 80;
    monstro.vidaAtual = 80;
    monstro.ataqueBase = 25; 
    monstro.defesa = 3;

    printf("Um monstro se aproxima, seu nome eh...\n");
    printf("%s!\n", monstro.nome);
    printf("Prepare-se para a batalha, %s!\n\n", heroi.nome);

    while (heroi.vidaAtual > 0 && monstro.vidaAtual > 0) {
        printf("--- SUA VEZ ---\n");
        printf("[%s] HP: %d/%d\n", heroi.nome, heroi.vidaAtual, heroi.vidaMaxima);
        printf("[%s] HP: %d/%d\n", monstro.nome, monstro.vidaAtual, monstro.vidaMaxima);
        printf("---------------\n");
        printf("O Que vais fazer?\n");
        printf("1. Atacar com %s\n", heroi.armaEquipada.nome);
        printf("2. Abrir Inventario (Trocar Arma)\n");
        printf("Escolha: ");

        int acao;
        scanf("%d", &acao);

        if (acao == 1) {
            int danoArma = rolarDado(heroi.armaEquipada.danoMin, heroi.armaEquipada.danoMax);
            int danoTotal = (heroi.ataqueBase + danoArma) - monstro.defesa;

            if (danoTotal < 0) danoTotal = 0;
            
            monstro.vidaAtual -= danoTotal;
            printf("\n> CLACK!!!! Voce acertou %s com %s e causou %d de dano! (HP inimigo: %d)\n", monstro.nome, heroi.armaEquipada.nome, danoTotal, monstro.vidaAtual);

        } else if (acao == 2) {
            abrirInventario(&heroi);
        }

        if (monstro.vidaAtual <= 0) break;

        printf("\n");
        int danoMonstro = (monstro.ataqueBase + rolarDado(1, 6)) - heroi.defesa;
        
        if (danoMonstro < 0) danoMonstro = 0;
        heroi.vidaAtual -= danoMonstro;
        printf("> %s te acertou em cheio! Voce levou %d de dano. (Seu HP: %d)\n", monstro.nome, danoMonstro, heroi.vidaAtual);
    }

    printf("\n--- FIM DE COMBATE ---\n");
    if (heroi.vidaAtual > 0) {
        printf("VITORIA! %s derrotou %s.\n", heroi.nome, monstro.nome);
    } else {
        printf("DERROTA... %s caiu em combate.\n", heroi.nome);
    }
    
    return 0;
}