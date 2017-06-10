#include "Tree.h"

int CheckTreeFile()
{
    int response = 0;

    FILE *treeFile = fopen("tree.csv", "r");

    if (treeFile != NULL)
    {
        response = 1;
        fclose(treeFile);
    }

    return response;
}

Tree * ReadTreeFile()
{
    Tree tree = NULL;
    char treeContent[1000];

    FILE *treeFile = fopen("tree.csv", "r");
    fscanf(treeFile, "%s", treeContent);
    fclose(treeFile);

    char *number;
    int indice;
    number = strtok(treeContent, ",");

    while (number != NULL)
    {
        Data data;
        data.Value = atoi(number);
        InsertBranch(&tree, data);

        number = strtok(NULL, ",");
    }

    return tree;
}

void StoreData(Data data)
{
    FILE *treeFile;
    char *filename = "tree.csv";

    treeFile = fopen(filename, "a+");
    fprintf(treeFile, "%d,", data.Value);
    fclose(treeFile);
}

void ClearTreeFile()
{
    FILE *treeFile;
    char *filename = "tree.csv";

    treeFile = fopen(filename, "w");
    fclose(treeFile);
}

void StoreTree(Tree tree)
{
    if (!IsEmpty(tree))
    {
        StoreData((*tree).Content);
        StoreTree(tree->Left);
        StoreTree(tree->Right);
    }
}