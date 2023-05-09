/* Programa para cadastro de pacientes diagnosticados com Covid-19 */
#include <stdio.h> /* printf, scanf, fgets */
#include <stdlib.h> /* malloc */
#include <string.h> /* para usar o fgets */
#include <locale.h> /* para usar acentos */
#include <unistd.h> /* para usar a funcao sleep */


// funcao INT retorna, ao contrario da VOID que nao retorna


/* Definindo a struct Paciente e ProfSaude */
typedef struct paciente {
    char nome[50];
    int  nascDia[50];
    int  nascMes[50];
    int  nascAno[50];
    char cpf[50];
    char email[50];
    char telefone[50];
    char endereco[100];
    char cep[50];
    char comorbidade[50];
    int idade[50];
    char resp [50];

} Paciente;


typedef struct profSaude {

} ProfSaude;


int idade, dia, mes, ano, diaAtual, mesAtual, anoAtual;


/* funcao para calculo de idade do paciente */
void calculaIdade(Paciente *paciente) {
    printf("\nDigite a data de nascimento do paciente:\n\n");
    printf("Dia: ");
    scanf("%d", &dia);
    printf("Mes: ");
    scanf("%d", &mes);
    printf("Ano: ");
    scanf("%d", &ano);
    printf("\nDigite a data atual:\n\n");
    printf("Dia: ");
    scanf("%d", &diaAtual);
    printf("Mes: ");
    scanf("%d", &mesAtual);
    printf("Ano: ");
    scanf("%d", &anoAtual);

    idade = anoAtual - ano;
    if (mesAtual < mes) {
        idade--;
    } else if (mesAtual == mes) {
        if (diaAtual < dia) {
            idade--;
        }
    }

    printf("\nIdade: %d anos\n\n", idade);
    if (idade >= 65) {
        printf("Paciente incluido no grupo de risco\n\n");
    } else {
        printf("Paciente nao incluido no grupo de risco\n\n");
    }
}

/* funcao para cadastrar paciente */
void cadastro(Paciente *paciente) {
    printf(" -- Cadastro de paciente -- \n\n");
    printf("\nPreencha os dados abaixo\n\n");
    printf("Nome: ");
    fflush(stdin); /* stdin > limpa o buffer do teclado */
    fgets(paciente->nome, 50, stdin); /* fgets > para ler espaços em branco usando o fgets ||| scanf > nao funciona com espacos em branco */
    printf("CPF (somente numeros): ");
    fflush(stdin);
    fgets(paciente->cpf, 11, stdin);
    printf("Telefone com DDD (somente numeros): ");
    fflush(stdin);
    fgets(paciente->telefone, 20, stdin);
    printf("Email: ");
    fflush(stdin);
    fgets(paciente->email, 50, stdin);
    printf("CEP: ");
    fflush(stdin);
    fgets(paciente->cep, 12, stdin);
    printf("ENDERECO COMPLETO: ");
    fflush(stdin);
    fgets(paciente->endereco, 100, stdin);
    calculaIdade(paciente);
    printf("Possui alguma comorbidade? (s/n): ");
    fflush(stdin);
    fgets(paciente->resp, 2, stdin);
    if (paciente->resp[0] == 's') {
        printf("Qual? ");
        fflush(stdin);
        fgets(paciente->comorbidade, 50, stdin);
    } else if (paciente->resp[0] == 'n') {
        printf("\nNao possui comorbidade\n");
    } else {
        printf("Opcao invalida\n");
    }
}

/* funcao para login do profissional de saude */
void login(ProfSaude *profSaude) {
    char login[50] = "admin";
    char login1[50];
    char senha[50] = "123456";
    char senha1[50];
    do {
        printf("Realize o login para continuar\n");
        printf("Login: ");
        scanf("%s", login1);
        printf("Senha: ");
        scanf("%s", senha1);
        if (strcmp(login, login1) == 0 && strcmp(senha, senha1) == 0)
        {
            printf("\nLogin efetuado com sucesso!\n\n");
        } else {
            printf("\nLogin ou senha incorretos!\n\n");
        }
    } while (strcmp(login, login1) != 0 || strcmp(senha, senha1) != 0);
}

/* funcao para salvar os dados do paciente em um arquivo */
void salvar(Paciente *paciente) {
    FILE *Ponteiro;
    Ponteiro = fopen("cadastro.txt", "a"); /* a > para adicionar no final do arquivo
    ||| w > para sobrescrever o arquivo */
    if (Ponteiro == NULL) {
        printf("Erro na abertura do arquivo!");
        exit(1);
    }

    int intDia = dia;
    int intMes = mes;
    int intAno = ano;

    int intDiaAtual = diaAtual;
    int intMesAtual = mesAtual;
    int intAnoAtual = anoAtual;

    fprintf(Ponteiro,
    "\n\nNome ----------------: %s\
    \rCPF -----------------: %s\n\
    \rTelefone ------------: %s\
    \rEmail ---------------: %s\
    \rCEP -----------------: %s\
    \rENDERECO COMPLETO ---: %s\
    \rData de nascimento --: %d/%d/%d\n\
    \rDia do diagnóstico --: %d/%d/%d\n\
    \rComorbidade ---------: %s\n\
    \r====================================\n",
    paciente->nome,
    paciente->cpf,
    paciente->telefone,
    paciente->email,
    paciente->cep,
    paciente->endereco,
    intDia,
    intMes,
    intAno,
    diaAtual,
    mesAtual,
    anoAtual,
    paciente->comorbidade
    ); /* fprintf > escreve no arquivo ||| printf > escreve na tela */
    fclose(Ponteiro);

    if (idade >= 65 ) {
        FILE *Ponteiro2;
        Ponteiro2 = fopen("grupoderisco.txt", "a"); /* a > para adicionar no final do arquivo */
        if (Ponteiro2 == NULL) {
            printf("Erro na abertura do arquivo!");
            exit(1);
            }
        fprintf(Ponteiro2,
        "\n\nNome ---------------: %s\
        \rIdade --------------: %d\n\
        \rCPF ----------------: %s\n\
        \rCEP ----------------: %s\
        \rComorbidade---------: %s\n\
        \rO Paciente foi identificado como pertencente ao grupo de risco.\n\
        \r====================================\n",
        paciente->nome,
        idade,
        paciente->cpf,
        paciente->cep,
        paciente->comorbidade);
        fclose(Ponteiro2);
    }
}

/* funcao menu */
void menu() {
    Paciente *paciente;
    int opcao;
    do {
        printf("Bem vindo ao sistema de cadastro de pacientes com Covid-19!\n\n");
        printf("Escolha uma opcao:\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Sair\n\n");
        printf("Opcao: ");
        scanf("\n%d", &opcao);

        switch (opcao) {
            case 1:
                cadastro(&paciente);
                salvar(&paciente);
                printf("Cadastro realizado com sucesso!\n\n");
                printf("1 - Retornar ao menu\n2 - Sair\n");
                printf("Opcao: ");
                scanf("\n%d", &opcao);

                if (opcao == 1) {
                    return (main());
                }

                else if (opcao == 2) { /* para encerrar o programa apos o cadastro*/
                    printf("Salvando dados e saindo");
                    for (int i = 0; i < 3; i++) {
                    printf(".");
                    sleep(1);
                    }
                    break;
                }

            case 2: /* para encerrar o programa sem realizar o cadastro */
                printf("Saindo");
                break;
                default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 2);
}

/* Programa principal */
int main() {
    Paciente paciente;

    ProfSaude profSaude;
    login(&profSaude);

    menu();
    return 0;
}
