#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void Clean()
{
    system("cls");
}

void Pause()
{
    printf("\nPressione Enter para continuar...\n");
    getchar();
    Clean();
}

void ClearBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void ShowMessage(char *Message)
{
    printf("%s", Message);
    Pause();
}

int getint()
{
    int integer;
    scanf_s("%d", &integer);
    ClearBuffer();

    return integer;
}

int MainMenu()
{
    int answer = -1;

    while (answer == -1)
    {
        Clean();
        printf("ALUNO: Fernando Velloso Borges de Melo Gomes\nDISCIPLINA: Estrutura de Dados I\nPROFESSOR: Walace Bonfim\n\n\tEditor De Arvore\n\n1 - Inserir\n2 - Remover apenas um no\n3 - Pesquisar\n4 - Esvaziar a arvore\n5 - Exibir a arvore\n0 - Sair\n\nDigite sua opcao: ");

        answer = getint();

        if (answer != 1 && answer != 2 && answer != 3 && answer != 4 && answer != 5 && answer != 0)
            answer = -1;
    }

    Clean();
    return answer;
}

int SubMenu(char *Message)
{
    int value = 0;

    while (value == 0)
    {
        Clean();
        printf("ALUNO: Fernando Velloso Borges de Melo Gomes\nDISCIPLINA: Estrutura de Dados I\nPROFESSOR: Walace Bonfim\n\n\tEditor De Arvore\n\n%s", Message);
        value = getint();
    }

    Clean();
    return value;
}