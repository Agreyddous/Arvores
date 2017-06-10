#include "FilesHandler.h"
#include "Display.h"

void main()
{
    int resposta = 666;
    Tree tree = NULL;

    if (CheckTreeFile())
        tree = ReadTreeFile();

    while (resposta != 0)
    {
        resposta = MainMenu();

        if (resposta == 1)
        {
            Data data;
            data.Value = SubMenu("Digite um valor para ser inserido na arvore:\t(Exceto 0)\n\n-> ");
            
            if (InsertBranch(&tree, data))
            {
                StoreData(data);
                ShowMessage("No adicionado com sucesso");
            }

            else
            {
                ShowMessage("No ja existe!");
            }
        }

        else if (resposta == 2)
        {
            Data data;
            data.Value = SubMenu("Digite um valor para ser removido da arvore:\t(Exceto 0)\n\n-> ");

            if (RemoveBranch(&tree, data))
            {
                ClearTreeFile();
                StoreTree(tree);
                ShowMessage("No removido com sucesso");
            }

            else
            {
                ShowMessage("No ja nao encontrado!");
            }
        }

        else if (resposta == 3)
        {
            Data data;
            data.Value = SubMenu("Digite um valor para ser pesquisado na arvore:\t(Exceto 0)\n\n-> ");

            if (Search(tree, data))
            {
                ShowMessage("Exite um no com esse valor!");
            }

            else
            {
                ShowMessage("Nao existe um no com esse valor!");
            }
        }

        else if (resposta == 4)
        {
            ClearTreeFile();
            EmptyTree(&tree);

            ShowMessage("Arvore deletada!");
        }

        else if (resposta == 5)
        {
            if (!IsEmpty(tree))
            {
                printf("\t\tEsta e a arvore:");
                ShowTree(tree, 20, 3, 10);
                getchar();
                Clean();
            }

            else
            {
                ShowMessage("A arvore esta vazia!");
            }
        }
    }

    printf("Ate mais!");
    Pause();
}