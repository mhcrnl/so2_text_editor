#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <signal.h>

FILE *arq1, *arq2;
int escolha;
char arquivo[15], caract;
void criarArquivo(); //create
void mostrarArquivo(); //show
void adicionar(); //append
void deletarArquivo(); // delete

#define TRUE 1
#define FALSE 0

int main(int argc, char** argv) {

    do {
        printf("\n\t\tEditor de Texto");
        printf("\n\n\tMENU:\n\t-----\n ");
        printf("\n\t1.CRIAR NOVO ARQUIVO\n\t2.MOSTRAR ARQUIVO EXISTENTE\n\t3.ADICIONAR TEXTO AO ARQUIVO\n\t4.DELETAR ARQUIVO\n\t5.SAIR\n");
        printf("\n\tO que você deseja fazer: ");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                criarArquivo();
                break;
            case 2:
                mostrarArquivo();
                break;
            case 3:
                adicionar();
                break;
            case 4:
                deletarArquivo();
                break;
            case 5:
                remove("temp.txt");
                return (FALSE);
        }
    } while (TRUE);
}

// Create file
void criarArquivo() {
    signal(2, SIG_IGN);
    // Flag to skip the first enter
    // Without it, all files have a \r\n on 1st line
    int flagCarriage = FALSE;
    // Temporary file that will be copied
    arq1 = fopen("temp.txt", "w");
    printf("\n\tDigite o texto e precione 'Ctrl+B' para finalizar\n\n");
    while (TRUE) {
        caract = getche();
        if (caract == 2) { // Signal of ctrl + b            
            fclose(arq1);
            printf("\n\tDigite o nome do arquivo a ser salvo: ");
            scanf("%s", arquivo);
            arq1 = fopen("temp.txt", "r");
            arq2 = fopen(arquivo, "w");
            while (!feof(arq1)) {
                caract = getc(arq1);
                putc(caract, arq2);
            }
            fclose(arq2);
            break;
        } else {
            if (caract == 10) { //enter
                printf("\t");
                if(flagCarriage == TRUE) {
                    fputc('\r', arq1);
                    caract = '\n';                    
                } else {
                    flagCarriage = TRUE;
                }                                
            }
            fputc(caract, arq1);
        }
    }
}

void mostrarArquivo() {
    printf("\n\tDigite o nome do arquivo: ");
    scanf("%s", arquivo);
    arq1 = fopen(arquivo, "r");
    if (arq1 == NULL) { // File not found
        printf("\n\tArquivo não existe!");
    } else {
        while (!feof(arq1)) {
            caract = getc(arq1);
            printf("%c", caract);
        }
    }
    fclose(arq1);
}

void adicionar() {
    signal(2, SIG_IGN);
    int flagMessage = TRUE;
    int flagCarriage = FALSE;
    printf("\n\tDigite o nome do arquivo que você quer adicionar texto: ");
    scanf("%s", arquivo);
    arq1 = fopen(arquivo, "r");
    if (arq1 == NULL) {
        //File not found
        printf("\n\tArquivo não encontrado! <o>");
        flagMessage = FALSE;
    } else {
        printf("\n\tDigite o texto e precione 'Ctrl+B' para adicionar ao arquivo:\n");
        while (!feof(arq1)) {
            caract = getc(arq1);
            printf("%c", caract);
        }
        fclose(arq1);
        arq1 = fopen(arquivo, "a");
        while (TRUE) {
            caract = getche();
            if (caract == 2) { // Signal de ctrl + b
                break;
            }
            if (caract == 10) { //enter
                if(flagCarriage == TRUE) {
                    fputc('\r', arq1);
                    caract = '\n';                    
                } else {
                    flagCarriage = TRUE;
                }
            }
            fputc(caract, arq1);            
        }        
    }
    
    fclose(arq1);
    if(flagMessage) {
        printf("\n\n\tArquivo salvo! Precione qualquer tecla para continuar...");
        getch();
    }        
}

void deletarArquivo() {
    printf("\n\tDigite o nome do arquivo: ");
    scanf("%s", arquivo);
    arq1 = fopen(arquivo, "r"); //testing if the file exist
    if (arq1 == NULL) { //File not found
        printf("\n\tArquivo não encontrado!");
    } else {
        fclose(arq1);
        if (remove(arquivo) == FALSE) {
            printf("\n\n\tArquivo deletado com sucesso!");
        } else {
            printf("\n\tNão foi possível deletar o arquivo! Deu ruim.\n");
        }            
    }    
    printf("\n\n\tPrecione qualquer tecla para continuar...");
    getch();
}
