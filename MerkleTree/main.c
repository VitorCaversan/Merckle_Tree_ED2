#include "Node.h"

int maximumCapacity = 10; // Maximum capacity of hash tree
int size = 0; // how many nodes there are in the hash tree

void saveData(Node** arrayTree);// Saves all data in a txt file
void saveDataAux(Node* tree, FILE* arq);// Used for recursively runing the tree and saving it's components
void recoverData(Node** arrayTree);// Recovers data from the file and puts it in the tree

int main()
{
    int option, key, value, loop = 1;
    int recovered = 0; // If the user has already recovered the data, this flag won't let it do it anymore
    
    Node** arrayTree = (Node**)malloc(maximumCapacity*sizeof(Node*));

    init(arrayTree, maximumCapacity);

    printf("Implementation of Hash Tree\n");

    while(loop == 1)
    {
        printf("\nMENU-: \n1. Insert an item in the Hash Tree \n2. Remove an item from the Hash Tree \n3. Check the size of Hash Tree \n4. Display Hash Tree \n5. Save data \n6. Recover and merge with last save \n7. Exit \n\nPlease enter your choice-:");

        scanf("%d", &option);

        switch(option)
        {
        case 1:
            printf("Enter key and value: ");
            scanf("%d %d", &key, &value);
            add(key, value, maximumCapacity, arrayTree, &size);
            break;

        case 2:
            printf("Enter the key to delete: ");
            scanf("%d", &key);
            del(key, arrayTree, maximumCapacity, &size);
            break;

        case 3:
            printf("Size of the Hash Tree: %d\n", size);
            break;

        case 4:
            display(arrayTree, maximumCapacity);
            break;

        case 5:
            saveData(arrayTree);
            break;

        case 6:
            if (recovered == 0)
                recoverData(arrayTree);
            recovered = 1;
            break;

        case 7:
            loop = 0;
            break;

        default:
            printf("The option maches no number\n");
        }
    }

    freeArrayTree(arrayTree, maximumCapacity);
    return 0;
}

void saveData(Node** arrayTree)
{
    FILE* arq = fopen("save.txt", "w");

    int i = 0;
    Node* aux = NULL;
    for (i=0 ; i<maximumCapacity ; i++)
    {
        aux = arrayTree[i];
        if (aux != NULL)
        {
            saveDataAux(aux, arq);
        }
    }

    fclose(arq);
}
void saveDataAux(Node* tree, FILE* arq)
{
    if (tree == NULL)
        return;

    fprintf(arq, "%d \n", tree->key);
    fprintf(arq, "%d \n", tree->value);
    saveDataAux(tree->left, arq);
    saveDataAux(tree->right, arq);
}

void recoverData(Node** arrayTree)
{
    FILE* arq = fopen("save.txt", "r");

    if (arq != NULL)
    {
        int aux1;
        int aux2;
        int i = 0;
        while (!feof(arq)) 
        {
            fscanf(arq, "%d", &aux1);    
            fscanf(arq, "%d", &aux2);
            if (aux1 < 1000000 && aux1 > 0 && aux2 < 1000000)
                add(aux1, aux2, maximumCapacity, arrayTree, &size);
        }
    }
    else
        printf("erro em abrir o arquivo\n");

    fclose(arq);
}