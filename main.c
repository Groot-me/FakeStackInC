#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <math.h>

struct termios info; // for press the key automatic


//@@@@@@@@@@@@@@ Node @@@@@@@@@@@@@@@@

typedef struct node {

    int data;
    struct node* m_next_Node;

}Node;

void New_Node(Node* nouveau_Node, int Value, Node* next_node)
{
    nouveau_Node->data = Value;
    nouveau_Node->m_next_Node = next_node;

}//constructor

// @@@@@@@@@@@@@ CLIST @@@@@@@@@@@@@@@@
typedef struct{

    Node* Head;

} CList;

// @@@@@@@@@@@@@ STACK @@@@@@@@@@@@@@@@
typedef struct {
    unsigned size_of_stack;
    unsigned actual_size;
    CList* top;

} STACK;


// @@@@@@@@@@@@@ global variables @@@@@@@@@@@@@@@@
STACK My_stack; // une stack
CList My_CList; // une Liste Chainee


// @@@@@@@@@@@@@ Input User @@@@@@@@@@@@@@@@
int GetInputuser() //recupere la saisit filtrée de l'utilisateur
{
    // Get input of user
    char *endptr_i;
    char str_i[20];
    double result = 0 ;

    fgets(str_i, 20, stdin);
    result = strtol(str_i, &endptr_i, 0);

    if (*endptr_i != '\n' || str_i[0] == '\n' || endptr_i == str_i)
    {
        printf("\033[31m    OOOOPS ceci n'est pas autorisé, merci de me faire survenir l'erreur si vous pensez que ça n'en est pas une :D \033[37m\n\n ");
        return 2147483647;
    }
    if(result > 2147483646 || result < -2147483646)
    {
        printf("\033[31m    OOOOPS ceci n'est pas autorisé, merci de me faire survenir l'erreur si vous pensez que ça n'en est pas une :D \033[37m\n\n ");
        return 2147483647;
    }
    return (int)result;

}

// @@@@@@@@@@@@@ Stack function @@@@@@@@@@@@@@@@

int IfFull() //Vérifie si la stack est pleine
{
    if(My_stack.actual_size == My_stack.size_of_stack)
    {
        printf("    La Stack est pleine !! \n ");
        return 1;
    }
    return 0;

}

int isEmpty() //Vérifie si la stack n'est pas vide
{
    if(My_CList.Head == NULL )
    {
        printf("    La Stack est vide !! \n");
        return 1;
    }else
    {
        printf("    La Stack n'est pas vide !! \n");
        return 0;
    }
}

void Push() //ajoute une valeur à la stack (remplace la Head par une autre)
{
    printf("    Renseigner la Valeur du Noeud à Ajouter : ");
    int Value = GetInputuser();
    if(Value != 2147483647) //Error Value
    {
        if(!IfFull())
        {
            if(My_CList.Head == NULL)
            {
             My_CList.Head = malloc(sizeof(Node));
             New_Node(My_CList.Head,Value,NULL);
             My_stack.actual_size +=1;
             printf("\n    Valeur Ajoutée ! \n");
            }else
            {
                Node* NewNode = malloc(sizeof(Node));

                //copy the node where head point in tmp               
                Node* TmpNode = My_CList.Head->m_next_Node;

                //head point now to the newnode
                My_CList.Head->m_next_Node = NewNode;

                //NewNode point now on  his next struct with Head value
                New_Node(NewNode, My_CList.Head->data, TmpNode);

                //Head get the value of the new Node
                My_CList.Head->data = Value;

                printf("\n    Valeur Ajoutée ! \n");
                My_stack.actual_size +=1;
            }


        }else{}


    }else{}

}

void Pop() //Supprime la tete de la stack
{
    if(My_CList.Head != NULL )
    {

        Node* TmpNode = My_CList.Head;
        //head is now the next Node so the next node is the head there is no Head
        My_CList.Head = My_CList.Head->m_next_Node;

        //free the
        free(TmpNode);
        printf("\n    Tête supprimé ! \n");

    }else
    {
        printf("    La Stack est vide !! \n");
    }

}

void Peek()
{
    printf("    Renseigner le Noeud à afficher : ");
    int Element = GetInputuser();
    if(Element != 2147483647) //Error Value
    {
        int cpt = 1;
        Node* Node_Tmp = My_CList.Head;

        while (Node_Tmp!= NULL)
        {
            if(cpt >= Element)
            {
                printf("    Noeud numero %d : Valeur -> %d \n",cpt,Node_Tmp->data);
                break;
            }

            Node_Tmp = Node_Tmp->m_next_Node;
            cpt +=1;

        }
    }
}

void StackTop()
{
    if(My_CList.Head != NULL)
    {
        printf("    La valeur en haut de la pile est : %d \n",My_stack.top->Head->data);
    }else{
        printf("    La Stack est vide !! \n");
    }
}



void EmptyStack()
{
    Node* TmpNode;

    while (My_CList.Head != NULL)
     {
        TmpNode = My_CList.Head;
        My_CList.Head = My_CList.Head->m_next_Node;
        free(TmpNode);
     }
    printf("    Stack vidée ! \n");
    My_stack.actual_size = 0;
}



void ASCII_Stack();
void Special_print(int cpt, int Data)
{
    int espace_vide = 38;
    int taille_Data ;

    if(Data == 0) // log10 ne gere pas les 0
    {
        taille_Data = 1;
    }
    else if(Data < 0) //log10 ne gere pas les nombres négatifs
    {
        int tmp = Data*-1;
        taille_Data = log10((double)tmp) + 2; //+2 car il faut prendre en compte le char '-'
    }else
    {
        taille_Data = log10((double)Data) + 1; //calcule la taille du nombre (nbr de char dans celui-ci)
    }

    int espace_chaque_cote = (espace_vide-taille_Data)/2;
    printf(" %d |",  cpt);
    for(int i =0 ; i < espace_chaque_cote; i++)
    {
        printf(" ");
    }
    printf("%d", Data);
    for(int i =0 ; i < (espace_vide - espace_chaque_cote- taille_Data); i++)
    {
        printf(" ");
    }
    printf("|\n");

}
void printStack()
{
    if(My_CList.Head != NULL)
    {

         system("clear");
         ASCII_Stack();

         int cpt = 0;
         Node* Node_Tmp = My_CList.Head;



         while (Node_Tmp!= NULL)
         {
             printf("   +--------------------------------------+\n");
             printf("   |                                      |\n");
             Special_print(cpt,Node_Tmp->data);
             printf("   |                                      |\n");

             Node_Tmp = Node_Tmp->m_next_Node;
             cpt +=1;

         }
            printf("   +--------------------------------------+\n");


    }else
    {
        printf("    La Stack est vide !! \n");
    }

}


// @@@@@@@@@@@@@@ MENU FUNC @@@@@@@@@@@@@
void Choice_Of_User(int choice) // Choix de l'utilsateur d'après le menu des choix
{
    switch (choice) {
        case 1 :  Push(); break;
        case 2 :  Pop(); break;
        case 3 :  Peek(); break;
        case 4 :  printStack(); break;
        case 5 :  StackTop(); break;
        case 6 :  EmptyStack(); break;
        case 7 :  isEmpty(); break;
        case 8 :  IfFull(); break;
        default : printf("\n\033[31m    Choix pas dans liste !! \033[37m\n"); break;
    }

}
void ASCII_Stack()
{
    printf(" \033[1;32m ");
    printf("       ____ _____  _    ____ _  __ \n ");
    printf("       / ___|_   _|/ \\  / ___| |/ / \n");
    printf("        \\___ \\ | | / _ \\| |   | ' /  \n");
    printf("         ___) || |/ ___ \\ |___| . \\  \n");
    printf("        |____/ |_/_/   \\_\\____|_|\\_\\ \033[0;00m\n\n");
}

int Menu() //Affiche le Menu des Choix et permet à l'utilsateur de choisir une action et les listes
{
    tcgetattr(0, &info);          /* get current terminal attirbutes; 0 is the file descriptor for stdin */
    info.c_lflag &= ~ICANON;      /* disable canonical mode */
    info.c_cc[VMIN] = 1;          /* wait until at least one keystroke available */
    info.c_cc[VTIME] = 0;         /* no timeout */
    tcsetattr(0, TCSANOW, &info); /* set immediately */


    while(1)
    {
        ASCII_Stack();
        printf("\033[1;36m    Menu (Renseignez le nombre correspondant à l'action) :    \033[0;36m");
        printf("\n\n     (1) -> Ajouter une valeur a la stack\n");
        printf("     (2) -> Enlever la valeur en haut de la stack \n");
        printf("     (3) -> Rechercher une valeur a l'index n \n");
        printf("     (4) -> Afficher les valeurs de la stack\n");
        printf("     (5) -> Afficher le haut de la stack \n");
        printf("     (6) -> Vider la stack  \n");
        printf("     (7) -> La stack est-elle vide ? \n");
        printf("     (8) -> La stack est-elle pleine ? \n");
        printf("     (99) -> Quitter :,(                          \n ");
        printf("\n\033[0;0m");
        printf("    Alors ? : ");

        // Get input of user
        int resultMenu = GetInputuser();

        if(resultMenu == 99) {
            printf("\n    A bientot ! :D \n");
            return 0;
        } // Quitter

        if(resultMenu != 2147483647)
        {
            Choice_Of_User(resultMenu);
        }

        printf("    Appuyer sur une touche pour continuer... ");
        getchar();
        system("clear");

    }

    return 0;
}

int main()
{
    My_stack.size_of_stack = 10;
    My_stack.actual_size = 0;
    My_stack.top = &My_CList;
    My_CList.Head = NULL;
    Menu();

    return 0;
}
