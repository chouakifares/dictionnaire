#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct Word
{
    char content[9];
    int definition;
    struct Word* next;
};
struct letters
{
    char lettre;
    struct Word* first_word;
};
struct Word  generate_word()
{
    struct Word mot;
    int i=0;
    int    length=(rand() %7)+2;
    mot.definition=0;
    while(i<length)
        {
            mot.content[i]=(rand() %26)+97;
            mot.definition+=mot.content[i];
            i++;
        }
    mot.content[i]='\0';
    return  mot;
}
void classify_word(struct Word *w,struct letters dico[])
{
    int c=w->content[0]-97,cpt=1;
    if(dico[c].first_word==NULL)
    {
        dico[c].first_word=w;
    }
    else
    {
        struct Word *a=dico[c].first_word;
        int val=1;
        while(strlen(a->content)<strlen(w->content)&& a!=NULL)
        {
            if(a->next==NULL)
            {
                a->next=w;
                val=0;
            }
            else
            {
                a=a->next;
            }
        }
        if(val&&strlen(a->content)>=strlen(w->content))
        {
            w->next=a->next;
            a->next=w;
            char c[9];
            int i=0;
            while(a->content[i]!='\0')
            {
                c[i]=a->content[i];
                i++;
            }
            c[i]='\0';
            i=0;
            int d=a->definition;
            while(w->content[i]!='\0')
            {
                a->content[i]=w->content[i];
                i++;
            }
            a->content[i]='\0';
            i=0;
            a->definition=w->definition;
            while(c[i]!='\0')
            {
                w->content[i]=c[i];
                i++;
            }
            w->content[i]='\0';
            w->definition=d;
        }
    }
}
void recherche(struct letters dico [])
{
    char mot[9];
    printf("quel mot voulez vous rechercher");
    do
    {
        scanf("%s",mot);
    }while(strlen(mot)>=9);
    struct Word* inter;
    int val=1;
    for(int i=0;i<26;i++)
    {
        inter=dico[i].first_word;
        while(inter!=NULL)
        {
            int verifie=1;
            int j=0;
            while(j<strlen(mot))
            {
                if(mot[j]!=inter->content[j])
                {
                    verifie=0;
                }
                j++;
            }
            if(verifie)
            {
                printf("%s:%d",mot,inter->definition);
                val=0;
                break;
            }
            else
            {
                inter=inter->next;
            }
        }
    }
    if(val)
    {
        printf("mot inexistant dans le dictionnaire");
    }
}
void solution(struct letters dico [])
{
    char mot[9];
    printf("quel mot voulez vous rechercher:");
    do
    {
        scanf("%s",mot);
    }while(strlen(mot)>=9);
    struct Word* inter;
    int val=1;
    inter=dico[mot[0]-97].first_word;
    while(inter!=NULL)
    {
        int verifie=1;
        int j=0;
        while(j<strlen(mot))
        {
            if(mot[j]!=inter->content[j])
            {
                verifie=0;
            }
            j++;
        }
        if(verifie)
        {
            printf("%s:%d\n",mot,inter->definition);
            val=0;
            break;
        }
        else
        {
            inter=inter->next;
        }
    }
    if(val)
    {
        printf("\nmot inexistant dans le dictionnaire");
    }
}
int main()
{
    struct letters dico[26];
    for(int i=0;i<26;i++)
    {
        dico[i].first_word=NULL;
    }
    int i=0,j=0;
    while(i<3000)
    {
        struct Word *a=malloc(sizeof(struct Word));
        *a=generate_word();
        a->next=NULL;
        classify_word(a,dico);
        i++;
    }
   do
    {
        printf("Que voulez vous faire?\nSi vous voulez acceder au contenu du dictionnaire appuyez sur 1\nSi vous voulez rechercher un mot dans le dictionnaire appuyez sur 2\nSi vous avez terminer d'utiliser le dictionnaire appuyer sur 0\n");
        do
        {
            printf("la reponse doit etre 1,2 ou 0\nVeuillez inserez votre reponse ici:");
            scanf("%d",&j);
        }while(j!=0&&j!=1&&j!=2);
        if(j==1)
        {
            struct Word* b;
            for(int i=0;i<26;i++)
            {
                b=dico[i].first_word;
                printf("\n%d)",i);
                while(b!=NULL)
                {
                    if(b->next==NULL)
                    {
                        printf("%s\n",b->content);
                        b=b->next;
                    }
                    else
                    {
                        printf("%s->",b->content);
                        b=b->next;
                    }

                }
            }
        }
        if(j==2)
        {
            solution(dico);
        }
    }while(j);

  return 0;
}

