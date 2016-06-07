#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int MNS_Recherche_syntaxique(int *i,char lettre,char *mots,char *chaine)
{
    if
    (
    ( (lettre >= 'a') && (lettre <= 'z') ) ||
    ( (lettre >= 'A') && (lettre <= 'Z') ) ||
    ( (lettre >= '0') && (lettre <= '9') ) ||
    (lettre == '_') || (lettre == '[') || (lettre == ']') || (lettre == '(') || (lettre == ')')
    )
    {
        chaine[*i] = lettre;
        *i = *i+1;
    }
    else
    {
        chaine[*i] = 0x00;
        if(*i > 0)
        {
            *i = 0;
            if(strcmp(mots,chaine) == 0)
                return 1;
        }
        *i = 0;
    }

    return 0;

}

int MNS_Recherche_syntaxique_extented(int *i,char lettre,char *mots)
{
    char chaine[100];

    if(lettre > 32)
    {
        chaine[*i] = lettre;
        *i = *i+1;
    }
    else
    {
        chaine[*i] = 0x00;
        if(*i > 0)
        {
            *i = 0;
            if(strcmp(mots,chaine) == 0)
                return 1;
        }
        *i = 0;
    }

    return 0;

}

int MNS_Analyseur_syntaxique(int *i,char lettre,char *mots)
{
    if(lettre > 32)
    {
        mots[*i] = lettre;
        *i = *i+1;
    }
    else
    {
        mots[*i] = 0x00;
        if(*i > 0)
        {
            *i = 0;
            return 1;
        }
        *i = 0;
    }

    return 0;

}

int MNS_chaine_syntaxe(char debut,char fin,char lettre,int *i,int *ignorer,char *mots)
{
    if( (lettre == fin) && (*ignorer == 1) )
    {
        *ignorer = 0;
        mots[*i] = 0x00;
        *i =0;
        return 1;
    }

    if(*ignorer == 1)
    {
        mots[*i] = lettre;
        *i = *i+1;
    }

    if(lettre == debut)
        *ignorer = 1;

    return 0;
}

int MNS_Ignorer_syntaxe(char debut,char fin,char lettre,int *ignorer)
{
    if( (lettre == fin) && (*ignorer == 1) )
    {
        *ignorer = 0;
        return 2;
    }

    if( (lettre == debut) && (*ignorer == 0) )
    {
        *ignorer = 1;
        return 1;
    }

    return 0;
}

void MNS_lecture_chaine(char *chaine,char *ch,int nbr)
{
    int i,l = 0,n = 0;

    for(i = 0;i < strlen(chaine)+1;i++)
    {
        if(chaine[i] > 32)
        {
            ch[l] = chaine[i];
            l++;

        }else
        {
            if(l > 0)
            {

                ch[l] =  0;
                l = 0;
                if(n == nbr) return;

                n++;
            }
        }
    }

}

int MNS_lecture_chaine_ext(char *chaine,char *ch,int nbr,char no)
{
    int i,l = 0,n = 0;

    for(i = 0;i < strlen(chaine)+1;i++)
    {
        if( (chaine[i] > 32) && (chaine[i] != no) )
        {
            ch[l] = chaine[i];
            l++;

        }else
        {
            if(l > 0)
            {

                ch[l] =  0;
                l = 0;
                if(n == nbr) return 1;

                n++;
            }
        }
    }

    return 0;

}

void MNS_fgets(FILE *fichier,char *chaine)
{
    int octet = 1,i = 0;

    while(octet != 0)
    {
        octet = fgetc(fichier);
        chaine[i] = octet;
        i++;
    }

    chaine[i] = 0;
}

void MNS_dossier_out(char *nom_du_fichier,char *dossier)
{
    int i = 0;
    char chaine[100],ch[100];
    dossier[0] = 0;
    while(MNS_lecture_chaine_ext(nom_du_fichier,chaine,i,'/') != 0)
    {
        if(MNS_lecture_chaine_ext(nom_du_fichier,ch,i+1,'/') != 0)
        {
            strcat(dossier,chaine);
            strcat(dossier,"/");
        }
        i++;
    }
}
