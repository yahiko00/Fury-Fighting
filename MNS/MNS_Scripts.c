#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int MNS_base_tableau(char *nom,char *tab,char *mot,char *adresse)
{
    FILE *fichier;
    int lettre,i = 0,l=0,rz = 0,type = 0,lecture = 0,t = 0;
    char chaine[1000];
    chaine[0] = 0x00;
    unsigned char crypage = 0;;

    fichier = fopen(nom, "rb");

    if (fichier != NULL)
    {
        while(1)
        {
            lettre =  fgetc(fichier);
            if(lettre == -1) break;
            lettre -= crypage;

            if(rz == 3)
            {
                if
                (
                    (lettre != ' ') && (lettre != 0x09 )
                )
                {
                    lecture = 1;
                }


                if
                (
                    (lecture == 1) &&
                    (lettre != 0x0D) && (lettre != -1) && (t == 0)
                )
                {

                    type = 1;
                    chaine[i] = lettre;
                    i++;
                }


                if
                (
                    (lecture == 1) &&
                    (lettre != '"') && (lettre != -1) && (t == 1)
                )
                {

                    type = 1;
                    chaine[i] = lettre;
                    i++;
                }

                if( (lettre == 0x0D) && (t == 0) )
                {
                    chaine[i] = 0x00;
                    rz = 4;
                }

                if( (lettre == '"') && (t == 1) )
                {
                    chaine[i] = 0x00;
                    rz = 4;
                }

                if(lettre == -1)
                {
                    chaine[i] = 0x00;
                    rz = 4;
                }

            }

            if(rz == 2)
            {
                i = 0;
                l = 0;

                if(lettre == '=')
                    rz = 3;

                if(lettre == '"')
                {
                    rz = 3;
                    t = 1;
                }
            }

            if(rz == 0)
            {
                if(lettre == tab[i])
                    i++;
                else
                    i = 0;

                if(tab[i] == 0x00)
                    rz = 1;
            }

            if(rz == 1)
            {

                if(lettre == mot[l])
                    l++;
                else
                    l = 0;

                if(mot[l] == 0x00)
                {
                    lettre =  fgetc(fichier);
                    lettre -= crypage;

                    if( (lettre == ' ') || (lettre == '=') || (lettre == 0x09 ) )
                        rz = 2;
                    else
                        l = 0;

                    fseek(fichier, -1, SEEK_CUR);
                }
            }

            if( (rz < 2) && ( ( lettre == ';') || (lettre == '=' )  || (lettre == '"' )) )
            {

                while(lettre != 0x0D)
                {
                    lettre =  fgetc(fichier);

                    if(lettre == -1)
                        break;

                    lettre -= crypage;
                }
            }

            if( (rz == 1) && ( lettre == '[') )
                break;

            if(lettre == -1)
                break;
        }

        fclose(fichier);
    }

    if ( ( (chaine[0] >= '0') && (chaine[0] <= '9') )|| (chaine[0] == '-') || (chaine[0] == '+')  )
        type = 2;


    if(type == 1)
        strcpy(adresse,chaine);

    if(type == 2)
        type = atoi(chaine);

    return type;

}

//permet de recuperer un tableau de int
int MNS_tableau(char *nom_du_fichier,char *tab,char *texte,int *valeur)
{

    int i = 0,ok;
    int lecture = 0;
    FILE *fichier;
    char chaine[1000];
    chaine[0] = 0;

    fichier = fopen(nom_du_fichier, "r");

    if(fichier != NULL)
    {
        char octet = 0;

        while(octet != -1)
        {
            ok = 0;
            octet = fgetc(fichier);


            if(lecture < 2)
            {
                if(octet > 32)
                {
                    chaine[i] = octet;
                    i++;
                }else
                {
                    chaine[i] = 0;
                    i = 0;
                    ok = 1;
                }
            }


            if(ok == 1 && lecture == 0)
            {
                if(strcmp(chaine,tab) == 0)
                    lecture = 1;
            }

            if(ok == 1 && lecture == 1)
            {
                if(strcmp(chaine,texte) == 0)
                    lecture = 2;
            }

            if(lecture > 2)
            {
                if(lecture == 3 && octet == ')') octet = -1;

                if(octet != -1)
                {
                    chaine[i] = octet;
                    i++;
                }

            }

            if(lecture == 2)
            {
                i = 0;
                if(octet == '(') lecture = 3;
            }

            if(lecture > 0 && octet == '[') octet = -1;

        }

        fclose(fichier);
    }



    chaine[i] = 0;

    char tmp[1000];
    int l,n;
    n = 0;
    l = 0;
    i  = 0;

    while(1)
    {

        if(chaine[i] > 32)
        {
            if(chaine[i] != ',')
            {
                tmp[l] = chaine[i];
                l++;
            }else
            {

                tmp[l] = 0;
                valeur[n] = atoi(tmp);

                l = 0;
                n++;
            }



        }

        if(chaine[i] == 0)
        {
            tmp[l] = 0;
            valeur[n] = atoi(tmp);
            break;
        }

        i++;

    }
    return n;

}


int MNS_fbuffer(char *nom_du_fichier,char *out)
{
    FILE *fichier;
    int octet = 0,i = 0;

    fichier = fopen(nom_du_fichier, "rb");

    if(fichier == NULL) return 0;

    while(octet != -1)
    {
        octet = fgetc(fichier);
        out[i] = octet;
        i++;
    }

    fclose(fichier);

    return i;
}
