#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct data
{
    int Value;
}Data;

typedef struct branch
{
    struct branch * Left;
    Data Content;
    struct branch * Right;
}Branch;

typedef Branch* Tree;

int IsEmpty(Branch * branch)
{
    return (branch == NULL);
}

int CompareData(Data data1, Data data2)
{
    int response = 0;

    if (data1.Value > data2.Value)
        response++;
    else if (data1.Value < data2.Value)
        response--;

    return response;
}

Branch* NewBranch()
{
    Branch * branch = (Branch*)malloc(sizeof(Branch));

    if (branch)
        branch->Left = branch->Right = NULL;

    return branch;
}

Branch* Search(Tree tree, Data data)
{
    Branch * branch = NULL;

    if (!IsEmpty(tree))
    {
        int Comparison = CompareData(tree->Content, data);

        if (Comparison == 0)
            branch = tree;
        else if (Comparison > 0)
            branch = Search(tree->Left, data);
        else
            branch = Search(tree->Right, data);
    }

    return branch;
}

Branch* SearchSetFather(Tree tree, Data data, Branch ** father)
{
    Branch * branch = NULL;

        if (!IsEmpty(tree))
        {
            int Comparison = CompareData(tree->Content, data);

            if (Comparison == 0)
                branch = tree;
            else if (Comparison > 0)
            {
                *father = tree;
                branch = SearchSetFather(tree->Left, data, father);
            }
            else
            {
                *father = tree;
                branch = SearchSetFather(tree->Right, data, father);
            }
        }

    return branch;
}

int InsertBranch(Tree *tree, Data data)
{
    int response = 0;

    if (IsEmpty(*tree))
    {
        *tree = NewBranch();

        if (IsEmpty(*tree))
            response = 0;

        (*tree)->Content = data;
        response = 1;
    }

    else
    {
        int Comparison = CompareData((*tree)->Content, data);

        if (Comparison < 0)
            response = InsertBranch(&((*tree)->Right), data);
        else if (Comparison > 0)
            response = InsertBranch(&((*tree)->Left), data);
    }

    return response;
}

int RemoveBranch(Tree *tree, Data data)
{
    int response = 0;

    Branch *branch;
    Branch *father;
    Branch *newBranch;
    Branch *fatherHeir;
    Branch *branchHeir;

    branch = *tree;
    father = NULL;

    branch = SearchSetFather(*tree, data, &father);

    if (!IsEmpty(branch))
    {
        if (branch->Left == NULL)
            newBranch = branch->Right;

        else
        {
            if (branch->Right == NULL)
                newBranch = branch->Left;

            else
            {
                fatherHeir = branch;
                newBranch = branch->Right;
                branchHeir = newBranch->Left;

                while (branchHeir != NULL)
                {
                    fatherHeir = newBranch;
                    newBranch = branchHeir;
                    branchHeir = newBranch->Left;
                }

                if (fatherHeir != branch)
                {
                    fatherHeir->Left = newBranch->Right;
                    newBranch->Right = branch->Right;
                }
                
                newBranch->Left = branch->Left;
            }
        }
        
        if (father == NULL)
            *tree = newBranch;
        else if (branch == father->Left)
            father->Left = newBranch;
        else
            father->Right = newBranch;

        free(branch);
        response = 1;
    }

    return response;
}

void GoToxy(int collumn, int row)
{
    COORD point;
    point.X = collumn;
    point.Y = row;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void Read(Tree tree)
{
    if (!IsEmpty(tree))
    {
        Read(tree->Left);
        printf("%d", tree->Content.Value);
        Read(tree->Right);
    }
}

void EmptyTree(Tree *tree)
{
    if (*tree != NULL)
    {
        EmptyTree(&(*tree)->Left);
        EmptyTree(&(*tree)->Right);

        free(*tree);
        *tree = NULL;
    }
}

void ShowTree(Tree tree, int collumn, int row, int offset)
{
    if (!IsEmpty(tree))
    {
        GoToxy(collumn, row);
        printf("%d", tree->Content.Value);

        if (tree->Left != NULL)
            ShowTree(tree->Left, collumn - offset, row + 2, offset / 2 + 1);
        if (tree->Right != NULL)
            ShowTree(tree->Right, collumn + offset, row + 2, offset / 2 + 1);
    }
}