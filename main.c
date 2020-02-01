#include <stdio.h>
#include <stdlib.h>

struct que                  //deklaracja nowej zmiennej - lista dwukierunkowa
{
    int key;
    struct que *next;
    struct que *prev;
    char memory;
};

struct que *add(struct que *head, int nr, char sign)         //funkcja dodajaca ludzi na koniec kolejki
{
    if (head==NULL)
    {
        head=(struct que*)malloc(sizeof(struct que));
        head->key=nr;
        head->next=NULL;
        head->prev=NULL;
        head->memory=sign;
        return head;
    }

    else
    {
        struct que *wskPomoc;
        wskPomoc=head;
        while(wskPomoc->prev != NULL)
            wskPomoc=wskPomoc->prev;
        wskPomoc->prev=(struct que*)malloc(sizeof(struct que));
        wskPomoc->prev->key=nr;
        wskPomoc->prev->next=wskPomoc;
        wskPomoc->prev->prev=NULL;
        wskPomoc->prev->memory=sign;
        return head;
    }
}

struct que *before(struct que *head, int nr, char sign)      //funkcja dodajaca ludzi na poczatek kolejki
{
    if (head==NULL)
    {
        head=(struct que*)malloc(sizeof(struct que));
        head->key=nr;
        head->next=NULL;
        head->prev=NULL;
        head->memory=sign;
        return head;
    }

    else
    {
        struct que *wskPomoc=head;
        if(wskPomoc->memory==68)
        {
            wskPomoc=(struct que*)malloc(sizeof(struct que));
            wskPomoc->next=NULL;
            wskPomoc->key=nr;
            wskPomoc->prev=head;
            wskPomoc->memory=sign;
            head->next=wskPomoc;
            head=wskPomoc;
            return head;
        }
        while(wskPomoc->memory==85 && wskPomoc->prev!=NULL)
            wskPomoc=wskPomoc->prev;
        struct que *wsk1=wskPomoc->next;
        struct que *wsk2=wskPomoc;
        if(wsk2->prev==NULL)                                //W PRZYPADKU GDY W KOLEJCE SA SAME U
        {
            wsk2=wsk2->prev;
            wsk2=(struct que*)malloc(sizeof(struct que));
            wskPomoc->prev=wsk2;
            wsk2->next=wskPomoc;
            wsk2->key=nr;
            wsk2->memory=sign;
            wsk2->prev=NULL;
            return head;
        }
        wskPomoc=(struct que*)malloc(sizeof(struct que));   //reszta przypadkow
        wsk1->prev=wskPomoc;
        wsk2->next=wskPomoc;
        wskPomoc->next=wsk1;
        wskPomoc->prev=wsk2;
        wskPomoc->key=nr;
        wskPomoc->memory=sign;
        return head;
    }
}

struct que *pop(struct que *head)        //funkcja usuwajaca klientow od glowy
{
    if (head==NULL)
        return NULL;
    else
    {
        struct que *wskPomoc;
        wskPomoc=head;
        printf("%d ", head->key);
        head=head->prev;
        free(wskPomoc);
        return head;
    }
}

void pokaz(struct que *n)  //funkcja wyswietlajaca stan kolejki
{
    struct que *wskPomoc;
    wskPomoc=n;
    if (n==NULL)
        printf("Nikogo nie ma w kolejce!");

    else
    {
        do
        {
            printf("%d ", wskPomoc->key);
            wskPomoc=wskPomoc->prev;
        }
        while (wskPomoc != NULL);
    }
}

int findNumber(char *tab, int n, int i) //Funkcja wyliczajaca wprowadzona liczbe do tablicy charow oraz eliminujaca blednie wpisane liczby po spacji
{
    int x=(int) tab[i];    //zrzutuj symbol w tablicy na symbol ASCII

    if(x==10)           //przerwij gdy w tablicy znajdzie sie NULL
        return n;

    if(x==48 || x==49 || x==50 || x==51 || x==52 || x==53 || x==54 || x==55 || x==56 || x==57) //czy znak ASCII jest cyfra 0-9
    {
        x-=48;      //Oblicz liczbe z symbolu ASCII
        n*=10;
        n+=x;
        i++;
        return findNumber(tab, n, i);
    }

    else
    {
        printf("Wprowadzono niepoprawne dane!");
        getchar();
        return NULL;
    }
}

int main()
{
    int N, marker=1;
    int maxi=8;               //maksymalna mozliwa ilosc znakow na wejscie do konsoli
    char control[maxi];
    struct que *head=NULL;
    for(;;)
    {
        printf("Witaj w sklepie AISD. Wybierz odpowiednie polecenie z menu ponizej.\n");
        printf("\nKOLEJKA:\n");
        printf("----------------------------------------------------------------------\n");
        pokaz(head);
        printf("\n----------------------------------------------------------------------");
        printf("\n\nMENU:");
        printf("\nD. Przyjmij N klientow zwyklych");
        printf("\nU. Przyjmij N klientow uprzywilejowanych");
        printf("\nO. Obsluz N kolejnych klientow");
        printf("\nX. Wyjdz z programu\n");
        printf("\nWybierz polecenie D, U, O lub X oraz PO SPACJI odpowiednia liczbe klientow do kolejki lub obslugi, np.: D 4.");
        printf("\nPolecenie_Liczba klientow (Od 0 do 9999): ");
        fgets(control, maxi, stdin);                                                     //pobiera napis razem ze spacja
        if ((control[0]==68 || control[0]==85 || control[0]==79) && control[1]==32)     //warunek na istnienie liter D U O oraz spacji
        {
        N=findNumber(control, 0, 2);      //2 - zaczynamy od szufladki o indeksie 2
            switch(control[0])
            {
            case 'D':
                for (int i=0; i<N; i++, marker++)                            //MARKER CALY CZAS ZWIEKSZA SIE O JEDEN
                    head=add(head, marker, control[0]);
                break;

            case 'U':
                for (int i=0; i<N; i++, marker++)
                    head=before(head, marker, control[0]);
                break;

            case 'O':
                printf("\nKolejke opuszczaja numery: ");
                for (int i=0; i<N; i++)
                    head=pop(head);
                getchar();
                break;
            }
        }
        else
        {
            if(control[0]==88 && control[1]==10)    //sprawdz czy po X jest ENTER
            {
                printf("Zapraszamy ponownie!");
                getchar();
                exit(0);
            }
            else
            {
                printf("Wprowadzono niepoprawne dane!");
                getchar();
            }
        }
        system("cls");
    }
    return 0;
}
