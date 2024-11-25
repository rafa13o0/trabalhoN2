#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TENTATIVAS 10
#define NUM_PALAVRAS 3

// Estruturas para armazenar informações sobre a palavra, jogo e jogador
struct Palavra {
    char *palavraOriginal;
    char *palavraComMascara;
    int tamanho;
};

struct Jogo {
    int tentativas;
    char *letrasJaArriscadas;
    struct Palavra palavra;
};

struct Jogador {
    char nome[50];
    int pontuacao;
};

// Função para limpar a tela (Windows)
void limpaTela() {
    system("CLS");
}

// Função para retornar uma palavra aleatória
char *retornaPalavraAleatoria() {
    // Vetor com palavras disponíveis
    char *palavras[NUM_PALAVRAS] = {"abacaxi", "manga", "morango"};

    // Índice gerado no intervalo {0, 1, 2}
    int indiceAleatorio = rand() % NUM_PALAVRAS;

    return palavras[indiceAleatorio];
}


struct Palavra inicializarPalavra(char *palavraOriginal) {
    struct Palavra p;
    p.palavraOriginal = palavraOriginal;
    p.tamanho = strlen(palavraOriginal);
    p.palavraComMascara = (char *)malloc((p.tamanho + 1) * sizeof(char));  
    for (int i = 0; i < p.tamanho; i++) {
        p.palavraComMascara[i] = '_';  
    }
    p.palavraComMascara[p.tamanho] = '\0';  
    return p;
}


void exibeStatus(struct Jogo *jogo) {
    printf("%s", jogo->letrasJaArriscadas);
    printf("\nPalavra: %s (Tamanho: %d)", jogo->palavra.palavraComMascara, jogo->palavra.tamanho);
    printf("\nTentativas Restantes: %d", MAX_TENTATIVAS - jogo->tentativas);

    printf("\nLetras arriscadas: ");
    for (int i = 0; i < strlen(jogo->letrasJaArriscadas); i++) {
        printf("%c, ", jogo->letrasJaArriscadas[i]);
    }
}


int jogar(struct Jogo *jogo, int numeroDeJogadores) {
    char letra;
    int opcao;

    
    if (numeroDeJogadores == 1) {
        jogo->palavra.palavraOriginal = retornaPalavraAleatoria();
    } else {
        printf("\nDigite uma palavra: ");
        char palavra[50];
        scanf("%s", palavra);
        jogo->palavra.palavraOriginal = strdup(palavra); 
    }

    
    jogo->palavra = inicializarPalavra(jogo->palavra.palavraOriginal);
    jogo->tentativas = 0;
    jogo->letrasJaArriscadas = (char *)malloc(1 * sizeof(char)); 
    jogo->letrasJaArriscadas[0] = '\0';  

    while (strcmp(jogo->palavra.palavraOriginal, jogo->palavra.palavraComMascara) != 0 && jogo->tentativas < MAX_TENTATIVAS) {
        limpaTela();
        exibeStatus(jogo);

        printf("\nDigite uma letra (Ou digite 1 para arriscar a palavra): ");
        scanf(" %c", &letra);

        
        if (letra == '1') {
            char palavraArriscada[50];
            scanf("%s", palavraArriscada);
            if (strcmp(palavraArriscada, jogo->palavra.palavraOriginal) == 0) {
                strcpy(jogo->palavra.palavraComMascara, palavraArriscada);
            } else {
                jogo->tentativas = MAX_TENTATIVAS;
            }
        }

        
        if (strchr(jogo->letrasJaArriscadas, letra) != NULL) {
            printf("\nEssa letra já foi digitada!\n");
        } else {
            jogo->letrasJaArriscadas = realloc(jogo->letrasJaArriscadas, (strlen(jogo->letrasJaArriscadas) + 2) * sizeof(char));
            strncat(jogo->letrasJaArriscadas, &letra, 1);  

            int acertouLetra = 0;
            for (int i = 0; i < jogo->palavra.tamanho; i++) {
                if (jogo->palavra.palavraOriginal[i] == letra) {
                    jogo->palavra.palavraComMascara[i] = letra;
                    acertouLetra = 1;
                }
            }

            if (acertouLetra == 0) {
                printf("\nVocê errou uma letra!\n");
            } else {
                printf("\nVocê acertou uma letra!\n");
            }
            jogo->tentativas++;
        }
    }

    
    if (strcmp(jogo->palavra.palavraOriginal, jogo->palavra.palavraComMascara) == 0) {
        limpaTela();
        printf("Parabéns, você venceu!\n");
        printf("Deseja reiniciar?\n1 - Sim\n2 - Não: ");
        scanf("%d", &opcao);
        return opcao;
    } else {
        limpaTela();
        printf("Você perdeu!\n");
        printf("Deseja reiniciar?\n1 - Sim\n2 - Não: ");
        scanf("%d", &opcao);
        return opcao;
    }
}


void menuInicial() {
    int opcao = 0;
    struct Jogo jogo;
    jogo.letrasJaArriscadas = NULL;  

    while (opcao != 4) {
        limpaTela();
        printf("Bem-vindo ao Jogo da Forca\n");
        printf("1 - Jogar Sozinho\n");
        printf("2 - Jogar em Dupla\n");
        printf("3 - Sobre\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (jogar(&jogo, 1) == 1) {
                    menuInicial();
                }
                break;
            case 2:
                if (jogar(&jogo, 2) == 1) {
                    menuInicial();
                }
                break;
            case 3:
                printf("Informações do jogo\nDesenvolvido por Thiago,Ridrigo,Yan,Rafael M, Raphael R em 2024\n");
                printf("\n1 - Voltar\n2 - Sair\n");
                scanf("%d", &opcao);
                if (opcao == 1) {
                    menuInicial();
                }
                break;
            case 4:
                printf("Até mais!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
}


int main() {
    srand((unsigned)time(NULL));  
    menuInicial();  

    return 0;
}
