#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#define TAILLE_MAX 400



/* @@@@@@@@@*********************************************************************************


    GESTION DES CLIENTS ***********************************************************


    @@@@@@@@@*******************************************************************************

    */

    /* ***********************************************************************
    *************************  DEBUT  ****************************************
    */

    typedef struct clients
{
	char NOM[100],PRENOM[100],PROFESSION[15],NUMERO[9],DATE[10],NCIN[9];
}clients;
clients id;

int menu();
//FOCNTIONS DU PROGRAMME
void ajout();
void supprimer(char*NCIN);
void modifier();
void afficher();
void recherche();
void menu_client();


/*int quitter()
{
    int quitte=0, retour=0;
    char clz[500]="";
    do
    {
        printf("voulez vous vraiment quitter le programme\n\n");
        printf("**\t\t1.OUI\n**\t\t2.NON\n");
        retour=scanf("%d",&quitte);
        gets(clz);
    }while(retour!=1);
    if(quitte==1)
        exit(0);
    return 0;
}*/




void ajout()
{

	system("cls");
	printf("*********EFFECTUER LA SASIE***********\n");
    char s = 0;
    int n = 1;

    FILE* banque = fopen("banque.txt","a");
    if(banque == NULL) {

    	printf("\nImpossible d'ouvrir le fichier");
    	return;
    }
    do{
    	printf("Client %d\n",n);
    	/*printf("\nEntrer l'identifiant du client comportant 3 chiffres : ");
        scanf("%[0-9]s",id.NCIN);
        fflush(stdin);*/
        do
        {
            printf("\nEntrer l'identifiant du client comportant 3 chiffres : ");
            scanf("%[0-9]s",id.NCIN);
            getc(stdin);
        }while(strlen(id.NCIN) != 3 );
        fprintf(banque,"%s;",id.NCIN);
        printf("\nEntrer le nom du client : ");
        scanf("%[^\n]",id.NOM);
        fflush(stdin);
        fprintf(banque,"%s;",id.NOM);
        printf("\nEntrez le PRENOM du client : ");
        scanf("%[^\n]",id.PRENOM);
        fflush(stdin);
        fprintf(banque,"%s;",id.PRENOM);
        printf("\nEntrez le numero du client : ");
        gets(id.NUMERO);
        fflush(stdin);
         while(strlen(id.NUMERO) != 9 )
        {
            printf("\nRe-entrer le numero comportant 9 chiffres : ");
            scanf("%[0-9]s",id.NUMERO);
            getc(stdin);
        }
        fprintf(banque,"%s;",id.NUMERO);
        printf("\nEntrer la profession du client : ");
        scanf("%[^\n]",id.PROFESSION);
        fflush(stdin);
        fprintf(banque,"%s;",id.PROFESSION);
        printf("\nEntrez la date de creation :");
        scanf("%[^\n]",id.DATE);
        fflush(stdin);
		fprintf(banque,"%s\n",id.DATE);
		printf("Si le nombre de clients est atteint veuillez tape s : ");
		scanf("%c",&s);
		fflush(stdin);
		n++;
		system("cls");

	}while(s != 's');
	fclose(banque);
}
void supprime()
{
		 char NCIN[9];
		int premier = 1,d=0;
		char chaine[200] = "",temp[201] = "",*token = NULL,si,ncin[9];
		FILE* banque = fopen("banque.txt","a"),*file_NCIN = fopen("banque_tmp.txt","w");
		if(banque==NULL || file_NCIN==NULL)
		{
			printf("impossible d'ouvrir le fichier !!");
			return ;
		}
		printf("1-Supprimer tout \n");
		printf("2-Supprimer un a un :");
		scanf("%d",&d);
		if(d==1)
		{
			remove("banque.txt");
			printf("fichier supprimer avec succes !!");
			menu_client();
		}
		else if(d==2)
		{
			do{
				if(premier)
					printf("\nRE-Entrer l'identifiant du client a supprimer si vous le voulez vraiment : ");
		        else{
		        	printf("\nNCIN n'existe pas re-entrer : ");
		        	printf("\nReesayer ?(o/n) : ");
		        	scanf("%[o-n^;]c",&si);
		        	if(si == 'n')
		        		goto found;  // sortie d'un nested construct de boucle
		        	printf("\nEntrer l'identifiant' a supprimer : ");
		        }
		        scanf("%s",ncin);
		        fflush(stdin);
		        premier = 0;
		    }while(rechercher(ncin)==0);
		    while(fgets(chaine, 200, banque) != NULL)
			{
				strcpy(temp,chaine);
				token = strtok(chaine,";");
				if(strcmp(token,NCIN) != 0)
					fprintf(file_NCIN,"%s\n",temp);
		    }


		}
    	fclose(banque);
        fclose(file_NCIN);
        remove("banque.txt");
        rename("banque_tmp.txt","banque.txt");
        return;
        found:
            remove("banque_tmp.txt");
            fclose(banque);
            printf("\nvous-etes sortie");
            system("pause");

}
void modifier()
{
	FILE* banque = fopen("banque.txt","r"),*file_tmp = fopen("banque_tmp.txt","w");
	char chaine[200], ncin[10], choix, *token = NULL, temp[200] = "" ,s=0;
	int n=1;

	if(banque == NULL || file_tmp == NULL)
    {
		printf("Impossible d'ouvvrir ce fichier\n");
		return;
	}
	printf("\t\tEntrez le numero de la cni a modifier :\n ");
	scanf("%s",ncin);
    fflush(stdin);
	printf("\t\tVoullez vous vraiment modifier ? o/n :\n ");
	scanf("%c",&choix);
	fflush(stdin);
	if(choix == 'o'|| choix == 'O')
	{
		while(fgets(chaine,TAILLE_MAX,banque)!=NULL)
		{
			strcpy(temp,chaine);
			token = strtok(chaine,";");
			if(strcmp(token,ncin) != 0)
			{
			    printf("identifiant inexistant !!");
				fprintf(file_tmp,"%s",temp);
				menu_client();
		    }else {
                    do{
                        printf("Client %d\n",n);
                        printf("\nEntrer le numero identifiant : ");
                        gets(id.NCIN);
                         while(strlen(id.NCIN) != 3 )
                        {
                            printf("\nRe-entrer le numero comportant 9 chiffres : ");
                            scanf("%[0-9]s",id.NCIN);
                            getc(stdin);
                        }
                        fprintf(file_tmp,"%s;",id.NCIN);
                        getc(stdin);
                        printf("\nEntrer le nom du client : ");
                        scanf("%[^\n]",id.NOM);
                        fflush(stdin);
                        fprintf(file_tmp,"%s;",id.NOM);
                        printf("\nEntrez le PRENOM du client : ");
                        scanf("%[^\n]",id.PRENOM);
                        fflush(stdin);
                        fprintf(file_tmp,"%s;",id.PRENOM);
                        printf("\nEntrez le numero du client : ");
                        gets(id.NUMERO);
                        fflush(stdin);
                         while(strlen(id.NUMERO) != 9 )
                        {
                            printf("\nRe-entrer le numero comportant 9 chiffres : ");
                            scanf("%[0-9]s",id.NUMERO);
                            getc(stdin);
                        }
                        fprintf(file_tmp,"%s;",id.NUMERO);
                        printf("\nEntrer la profession du client : ");
                        scanf("%[^\n]",id.PROFESSION);
                        fflush(stdin);
                        fprintf(file_tmp,"%s;",id.PROFESSION);
                        printf("\nEntrez la date de creation :");
                        scanf("%[^\n]",id.DATE);
                        fflush(stdin);
                        fprintf(file_tmp,"%s\n",id.DATE);
                        printf("Si le nombre de clients est atteint veuillez tape s : ");
                        scanf("%c",&s);
                        fflush(stdin);
                        n++;
                        system("cls");

                }while(s != 's');


			}
	   }
   }else{
   printf("merci d'avoir utiliser notre programme !!!");
   menu_client();
   }
   fclose(banque);
   fclose(file_tmp);
   remove("banque.txt");
   rename("banque_tmp.txt","banque.txt");
}
void afficher()
{
	int i=0 , k=0;
	char chaine[TAILLE_MAX],*token = NULL;
	FILE *banque = fopen("banque.txt","r");
	clients t[TAILLE_MAX] ;
	while(fgets(chaine, TAILLE_MAX, banque) != NULL)
    {
    	token = strtok(chaine ,";");
        for(i=0;i<5;i++)
        {
            if(i == 0)
            {
                strcpy(id.NUMERO ,token);
            }
            else if(i==1)
            {
                strcpy(id.NOM,token);
            }
            else if (i==2)
            {
                strcpy(id.PRENOM,token);
            }
            else if (i==3)
            {
                strcpy(id.NCIN,token);
            }
            else if(i==4)
            {
            	strcpy(id.PROFESSION,token);
			}
			 else if(i==5)
            {
            	strcpy(id.DATE,token);
			}
            token = strtok(NULL ,";");
        }
        t[k] = id;
        k++;
    }
     printf("\n");
    for(i=0;i<k;i++)
    {
        printf("\n\n-----------------------------------------------------------------------------------------------------------------------\n\n");
        printf("Les informations sur le client %d\n",i+1);
        printf("\tNUMERO: %s",t[i].NUMERO);
        printf("\tNOM: %s",t[i].NOM);
        printf("\tPRENOM: %s",t[i].PRENOM);
        printf("\tIDENTIFIANT : %s",t[i].NCIN);
        printf("\tPROFESSION : %s",t[i].PROFESSION);
        printf("\tDATE DE CREATION: %s",t[i].DATE);
    }
    printf("\n\n-----------------------------------------------------------------------------------------------------------------------\n\n");
    fclose(banque);
}
int rechercher() {
   FILE *banque = fopen("banque.txt","r");
   char chain[200] = {},ncin[9];

   if(banque == NULL){
   	printf("Impossible d'ouvrir le fichier");
   	return -1;
   }
   char*split = NULL;
   while(fgets(chain,200,banque) != NULL)
    {
   		split = strtok(chain,";");
   		if(strcmp(split,ncin) == 0){
   			fclose(banque);
   			return 1;
   		}
   }
   fclose(banque);
   return 0;
}
void recherche(char*NCIN,char*NOM)
{
	char chaine[TAILLE_MAX],*token = NULL, temp[200]="",s=0;
	FILE *banque = fopen("banque.txt","r");
	int d=0;
	do{
		printf("1-rechercher avec le nom: ");
	printf("2-rechercher avec l'identifiant: ");
	scanf("%d",&d);
	if(d==1)
	{
		printf("1-rechercher avec le nom: ");
		scanf("%s",id.NOM);
	}else if(d==2){
		printf("1-rechercher avec l'identifiant: ");
		scanf("%s",id.NCIN);
	}else{
		printf("desolée cette option n'est valide");
	}

	}while(d!=1 && d!=2);
	if(d==1)
	{
		while(fgets(chaine, TAILLE_MAX, banque) != NULL)
			{

                    strcpy(temp,chaine);
                    token = strtok(chaine,";");
                    if(strcmp(token,NOM) == 0)
                        afficher(NOM);
                    else
                        printf("cet identifiant n'existe pas !!");
                     printf("Si le nombre de clients est atteint veuillez tape s : ");
                    scanf("%c",&s);
                    fflush(stdin);

		    }
	}
	if(d==2){
		while(fgets(chaine, 200, banque) != NULL)
		{
			strcpy(temp,chaine);
			token = strtok(chaine,";");
			if(strcmp(token,NCIN) == 0)
				afficher(NCIN);
			else{
				printf("cet identifiant n'existe pas !!");
				menu_client();/*Menu();cette fonction ecrite par guylene permet de rentrer sur le menu apres avoir effectuer un choi
				non desireux*/
			}
		}
	}
	else{
		printf("choix non disponible !!");
		menu_client();
	}
}


void menu_client()
{
	system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("\t\t *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	         printf("\t\t *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*           BIENVENUE DANS LE MENU GESTION DES CLIENTS DE KALATA - BANK SA          *-*-*\n");
	         printf("\t\t *-*-*                     =============== ***** ===============                         *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*             MENUS:                                                                *-*-*\n");
	         printf("\t\t *-*-*             =====                                                                 *-*-*\n");
	         printf("\t\t *-*-*     [ 1- AJOUT CLIENT              ]      [ 3- SUPPRESSION           ]            *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*     [ 2- MODIFICATION              ]      [ 4- RECHERCHE             ]            *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*     [ 5- AFFICHER LES CLIENTS      ]      [ 6 - MENU -- GENERAL      ]            *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	         printf("\t\t *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");

}

void selection_client();
void selection_client()
{
    unsigned int ID_CLIENT, ID_COMPTE = 1500000, NCIN = 0;
    int choix1, choix2, continu;
    unsigned char NOM[] = "";
    do{
        menu_client();
        printf("\t         Votre choix > >:\t");
        scanf("%d", &choix1);
        switch(choix1)
        {
            case 1:

                system("cls");
                charge();
                ajout();
            break;
            case 2:
                system("cls");
                charge();
                modifier();
            break;
            case 3:
                system("cls");
                charge();
                /*printf("Quel est le numero de CNI du client que vous voulez supprimer?   >:\n");
                scanf("%d", &NCIN);*/
                supprime();
                break;
            case 4:
                system("cls");
                charge();
               // printf("Quel est le numero de CNI et le nom du client que vous voulez rechercher?   >:\n");
                //scanf("%d%s", &NCIN, NOM);
                recherche(NCIN, NOM);
            break;
            case 5:
                system("cls");
                charge();
                afficher();
            break;
            case 6:
                system("cls");
                charge();
                menu_main();
        }
        //system("cls");
        printf("\nvoulez vous continuer ? (1 / 0) 1 pour oui et 0 pour non:");

	            scanf("%d", &continu);
	            switch (continu) {
	                case 1:
	                    continu = 1;
	                    break;


	                case 0:
	                    continu = 0;
	                    system("cls");
	                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t *-*-*-*  Merci de faire confiance a KALATA - BANK SA !!!   *-*-*-*\n");
	                    //exit("cls");
	                    break;
	                default:
	                    system("cls");
	                	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t *-*-*-*  Merci de faire confiance a KALATA - BANK SA !!!   *-*-*-*\n");
	                    break;
	                }
    }while(continu);
}



 /* ***********************************************************************
    *************************  FIN  ****************************************
    */





 /* @@@@@@@@@*********************************************************************************


    GESTION DES COMPTES ***********************************************************


    @@@@@@@@@*******************************************************************************

    */

    /* ***********************************************************************
    *************************  DEBUT  ****************************************
    */



/*
Veuillez creer le fichier "comptes.txt" manuellemnt avant de commencer

*/

//typedef enum {Virement, Retrait} operations;
typedef struct Compte Compte;
struct Compte
{
    unsigned int Id_Client;
    unsigned int Id_Compte;
    int Solde;
    char Last_Operation[100];
};

Compte *Creer();
void Consultation_solde(const unsigned int Id_Compte);
void Fermer_le_Compte(const unsigned int Id_Compte);
void Afficher_Les_Comptes();
int lireVarChar(char *chaine);
Compte recuperation(char *ligne);
void operations_bancaires(const unsigned int Id_Compte);
void viderBuffer();
void menu_client();
int nbr_compte();
int existance(const unsigned int id_compte);


Compte *TAB = NULL;
unsigned int nb_comptes = 1;

int nbr_compte()
{
    int nbre_lignes = 0, nbre_compte = 0;
    char c1=' ';
    FILE*fichier=fopen("comptes.txt", "r");
    if(fichier == NULL)
        exit(1);
    if(fichier != NULL)
    {
        if((c1=fgetc(fichier))==EOF)
        {
           nbre_compte=nbre_lignes;
                return nbre_compte;
        }
        while((c1=fgetc(fichier))!=EOF)
        {
            if(c1 == '\n')
            {
               nbre_lignes++;
            }
        }

            /*if(nbre_lignes == 0)
            {
                nbre_lignes++;
                nbre_candidats=nbre_lignes;
                return nbre_candidats;
            }*/
            if(nbre_lignes >= 1)
            {
                nbre_compte=nbre_lignes;
                return (nbre_compte - 0);
            }
        fclose(fichier);
    }
}

//ici on �cri une fonction qui nous permettra d'entrer les differentes informations concernant chaque compte et pour cel�, on prend en param�tre un tableau de compte ainsi que le nombre de ces derniers

Compte*Creer()
{
    /*
        On fait une allocation dynamique
        Afin d'avoir une taille de tableau �gale aux nombre de compte entr� par l'utilisateur
    */

    float SOLDE_COMPTE;
    int choix = 0, i = 0;
    nb_comptes = nbr_compte();
    unsigned char choix1;
    /*
    printf("Entrez le nombre de comptes > ");
    scanf("%d",&nb_comptes);
    */
    FILE*fichier=fopen("comptes.txt", "a+");
    TAB = malloc(sizeof(Compte)*nb_comptes+1);
    //printf("%d\n", (sizeof(TAB)/1));
        //FILE *fichier = NULL;
    /*
            r : lecture
            r+ : lecture ,creation du fichier si non existant
            w : ecriture ,pour ecrire dans le fichier
            w+ : ecriture ,creation du fichier si non existant
            a : ajout
            a+ : ajout ,creation du fichier si non existant
        */
        //ici on ouvre le fichier cr�e en utilisant tout simplement la syntaxe appropri� le fichier a �t� cr�e juste au dessus du commentaire pr�c�dent
        /*
        for(int i=0;i<nb_comptes;i++)
        {

        }
        */
        printf("\t\t\t\tTotal des comptes de la banque Kalata - B@nk: %d\n\n\n", nb_comptes);
        SOLDE_COMPTE = 0.0;
            printf("Entrer les donnees relatives au compte : \n\n\n");
            printf("Entrer le Numero de ID du client dont vous avez besoin de creer le compte> ");
            scanf("%d",&TAB[i].Id_Client);
            printf("\nVous devez posseder un ID pour votre compte pour la suite.\n 1.creer un ID manuellement. \n 2.Obtenir un ID automatiquement\n Choix>:");
            scanf("%d", &choix);
            if(choix == 1)
            {
                do{
                    printf("\nEntrer le Numero de ID de votre compte (Il doit etre compris entre 1.000.000 et 10.000.000)> ");
                    scanf("%d",&TAB[i].Id_Compte);
                    if((existance(TAB[i].Id_Compte)) == 1)
                        printf("\nEchec !! ID deja existant ! Veuillez en choisir un autre svp");
                    if(TAB[i].Id_Compte < 1000000 || TAB[i].Id_Compte > 10000000)
                        printf("\nEchec !! Veuillez respecter l'intervalle demander");
                }while((existance(TAB[i].Id_Compte)) == 1 || TAB[i].Id_Compte < 1000000 || TAB[i].Id_Compte > 10000000);
            }

            else if(choix == 2)
            {
                do{
                        printf("\nComming soon\n");
                }while((existance(TAB[i].Id_Compte)) == 1 || TAB[i].Id_Compte < 1000000 || TAB[i].Id_Compte > 10000000);
            }
            printf("\n\nBravo !! Votre numero de compte a ete cree avec succes !\n\n");
            printf("Entrer le montant a initialiser dans le solde de votre compte bancaire. NB: Il doit etre superieur a 25000fr> ");
            scanf("%d",&TAB[i].Solde);
            if(TAB[i].Solde <= 25000)
            {
                do{
                printf("\nMontant invalide ! :( \n Entrer le montant a initialiser dans le solde de votre compte bancaire superieure a 25000fr > ");
                scanf("%d",&TAB[i].Solde);
            }while(TAB[i].Solde <= 25000);
            }
            else{
                printf("\n\nFeliciltation la creation du compte Terminee avce succes ! :)\n");
                //printf("Vous pouvez debuter en effectuer les operations suivantes sur votre compte (Recharge, Retrait, Transaction).\n");
            }

            if(fichier == NULL) //ici, on v�rifie tout simplement si l'ouverture du fichier s'est bien faite avec l'expression qui va s'afficher si elle s'est mal produite
            {
                printf("Impossible d'ouvrir le fichier ! \n");
                exit(0);
            }
            //ici si le fichier s'est bien ouvert, on aura la possiblit� d'ajouter les differentes informations d'un candidat en respectant ce qu'a dit le projet chaque information doit etre s�par� de l'autre par le point virgule et pour pouvoir ajouter on a utilis� la fontion fprintf en respectant la syntaxe

            strcpy(TAB[i].Last_Operation, "Aucune operation effectuee");
            printf("%d     %d     %d    %s",TAB[i].Id_Client ,TAB[i].Id_Compte ,TAB[i].Solde, TAB[i].Last_Operation);
            fprintf(fichier ,"%u;%u;%u;%s" ,TAB[i].Id_Client ,TAB[i].Id_Compte ,TAB[i].Solde, TAB[i].Last_Operation);
            fputs("\n", fichier);
            printf("\n\n\n");
        fclose(fichier);
        return TAB;

}

int existance(const unsigned int id_compte)
{
    char chaine[256];
    Compte donnees_compte;
    int existe = 0, i = 0;
    FILE*fichier=fopen("comptes.txt", "r");
    if(fichier == NULL)
    {
        exit(1);
    }
    while(fgets(chaine ,255 ,fichier) != NULL)
    {
        donnees_compte = recuperation(chaine);
        // Si le Numero de CNI correspond on modifie selon le choix de l' utilisateur !
        if(donnees_compte.Id_Compte == id_compte)
        {

            existe = 1;
            return 1;
            //break;
        }
    }
    if(existe == 0)
        return 0;
    fclose(fichier);
}
void Consultation_solde(const unsigned int ID_COMPTE)
{
    if((existance(ID_COMPTE)) == 0)
        printf("Desole le compte est inexistant. Veuillez reesayer avec un compte valide\n");
    if((existance(ID_COMPTE)) == 1)
    {
    char chaine[256];
    Compte donnees_compte;
    int i = 1;
    int j = nbr_compte();
    FILE *fichier=fopen ("comptes.txt", "r");
    if(fichier == NULL)
        exit(1);
    if(fichier!= NULL)
    {
        while(fgets(chaine ,255 ,fichier) != NULL && i <= j )
    {
        donnees_compte = recuperation(chaine);
        // Si le Numero de CNI correspond on modifie selon le choix de l' utilisateur !
        if(donnees_compte.Id_Compte == ID_COMPTE)
        {
            printf("Le solde de votre compte ayant pour Id %d est  ---->> : %d\n", donnees_compte.Id_Compte, donnees_compte.Solde);
            printf("\n\n\n");
            break;
        }
        i++;
    }
    fclose(fichier);
    }
    }

}

Compte recuperation(char *ligne)
{
    Compte donnees_compte;
    unsigned int cpt = 0;
    char *jeton = NULL;
    jeton = strtok(ligne ,";");
    while(jeton != NULL)
    {
        if(cpt == 0)
            donnees_compte.Id_Client = atoi(jeton);
        else if(cpt == 1)
            donnees_compte.Id_Compte = atoi(jeton);
        else if(cpt == 2)
        {
            donnees_compte.Solde = atoi(jeton);
        }
        else if(cpt == 3)
            strcpy(donnees_compte.Last_Operation ,jeton);
        cpt++;
        jeton = strtok(NULL ,";");
    }
    return donnees_compte;
}

void Afficher_Les_Comptes()
{
    Compte donnees_compte;
    int i = 1;
    int j = nbr_compte();
    FILE*fichier=fopen("comptes.txt", "r");
    if(fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier \n");
        exit(0);
    }
    if((nbr_compte()) == 0)
        printf("Aucun compte existant pour le moment dans notre Banque. Veuillez reesayer ulterieurement svp\n");
    /*else{

    }*/
    char chaine[256];
        while(fgets(chaine ,255 ,fichier) != NULL && i <= j)
        {
        donnees_compte = recuperation(chaine);

        //printf("%d\n", j);
        printf("\nCompte n@ %d>>>>: ID CLIENT>>: %d \t\t ID COMPTE>>: %d \t\t SOLDE DU COMPTE>>: %d \t\t DERNIERE OPERATION>>: %s\n\n", i, donnees_compte.Id_Client, donnees_compte.Id_Compte, donnees_compte.Solde, donnees_compte.Last_Operation);
        i++;
        }
        printf("\n\n\n");
    fclose(fichier);
}


void Fermer_le_Compte(const unsigned int Id_Compte)
{
    if((existance(Id_Compte)) == 0)
        printf("Desole le compte est inexistant. Veuillez reesayer avec un compte valide\n");
    if((existance(Id_Compte)) == 1)
    {
    char chaine[256] ,choix[] = "n";
    Compte Compte_supprimer;
    FILE*fichier = fopen("comptes.txt" ,"r");
    int i = 1, j;
    j = nbr_compte();
    FILE*f_supprimer = fopen("comptes_new.txt" ,"w");
    if(f_supprimer == NULL)
    {
        printf("Impossible d'ouvrir le fichier \n");
        exit(0);
    }
    if(fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier \n");
        exit(0);
    }
    while(fgets(chaine ,255 ,fichier) != NULL && i <= j)
    {
        Compte_supprimer = recuperation(chaine);
        // Si le Numero de Compte correspond on modifie selon le choix de l' utilisateur !
        if(Compte_supprimer.Id_Compte == Id_Compte)
        {
            printf("Vous allez retirer les donnees du compte d'ID_COMPTE >>>>>>: %u'\n\n\t" ,Compte_supprimer.Id_Compte);
            printf("(Attention : Vous ne pourrez plus recuperer les donnees de ce compte une fois supprimer !!.)\n");
            printf("\t\t\t\t\n\nConfirmez - vous cette action ? (o/n) :\t");
            scanf("%s" ,choix);
        }
        if((Compte_supprimer.Id_Compte == Id_Compte && strcmp(choix ,"o") != 0) || Compte_supprimer.Id_Compte != Id_Compte)
        {
            fprintf(f_supprimer ,"%u;%u;%u;%s" ,Compte_supprimer.Id_Client ,Compte_supprimer.Id_Compte ,Compte_supprimer.Solde ,Compte_supprimer.Last_Operation);

        }
        i++;
    }
    if(!(strcmp(choix ,"o") != 0))
        printf("\n\nSuppression du compte effectuee avec succes !\n");
    fclose(fichier);
    fclose(f_supprimer);
    remove("comptes.txt");
    rename("comptes_new.txt" ,"comptes.txt");
}
}

void menu_compte(){
    system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("\t\t *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	         printf("\t\t *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*              BIENVENUE DANS LE MENU GESTION DES COMPTES - BANK SA                 *-*-*\n");
	         printf("\t\t *-*-*                     =============== ***** ===============                         *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*             MENUS:                                                                *-*-*\n");
	         printf("\t\t *-*-*             =====                                                                 *-*-*\n");
	         printf("\t\t *-*-*     [ 1- CREER UN COMPTE           ]      [ 3- FERMER LE COMPTE            ]      *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*     [ 2- CONSULTATION DU SOLDE     ]       [ 4- AFFICHER LES COMPTES       ]      *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*                        [5-      MENU   --  GENERAL    ]                           *-*-*\n");
	         printf("\t\t *-*-*                                                                                   *-*-*\n");
	         printf("\t\t *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	         printf("\t\t *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");

}


void menu_main();
void menu_main(){
    int choix1, continu;
    do{
    system("cls");
    system("color 3");
	printf("\n\n\n\n\n\n\n");
        printf("\t ~~-~~-~~-~~-~~-~~--~~-~~-~~-~~-~~-~~-~~-~ ****** ~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~\n");
        printf("\t ~~-~~-~~                                                                             ~~-~~-~~\n");
        printf("\t **-**-**                  BIENVENUE DANS OUTILS DE GESTION DES BANQUES               **-**-**\n");
        printf("\t **-**-**                  =============== ~~~~~ ===============                      **-**-**\n");
        printf("\t ~~-~~-~~-~~-~~-~~--~~-~~-~~-~~-~~-~~-~~-~ ****** ~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~\n");
        printf("\t ~~-~~-~~                                                                             ~~-~~-~~\n");
        printf("\t **-**-**           KALATA BANK- BANK SA  :                                           **-**-**\n");
        printf("\t **-**-**            ======~~~~~~======                                               **-**-**\n");
        printf("\t ~~-~~-~~                                                                             ~~-~~-~~\n");
        printf("\t ~~-~~-~~     1 - GESTION DES CLIENTS                                                 ~~-~~-~~\n");
        printf("\t **-**-**                                                                             **-**-**\n");
        printf("\t **-**-**     2 - GESTION DES COMPTES                                                 **-**-**\n");
        printf("\t ~~-~~-~~                                                                             ~~-~~-~~\n");
        printf("\t ~~-~~-~~     3 - GESTION DES OPERATIONS                                              ~~-~~-~~\n");
        printf("\t **-**-**                                                                             **-**-**\n");
        printf("\t **-**-**     4 - QUITTER                                                             **-**-**\n");
        printf("\t ~~-~~-~~                                                                             ~~-~~-~~\n");
        printf("\t ~~-~~-~~-~~-~~-~~--~~-~~-~~-~~-~~-~~-~~-~ ****** ~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~-~~\n");


        printf("\t         Votre choix > >:\t");
        scanf("%d", &choix1);
        switch(choix1)
        {
            case 1:
                system("cls");
                /*
                    Appeler la fonction proinciale de gestion des clients ici

                */
                charge();
                selection_client();
            break;
            case 2:
                system("cls");
                charge();
                selection_compte();
            break;
            case 3:
                system("cls");
                /*
                    Appeler la fonction proinciale de gestion des operations ici

                */
                charge();
                MenuOperation();

                break;
            case 4:
                charge();
                exit(0);
            break;
        }
        //system("cls");
        printf("\nvoulez vous continuer ? (1 / 0) 1 pour oui et 0 pour non:");

	            scanf("%d", &continu);
	            switch (continu) {
	                case 1:
	                    continu = 1;
	                    break;


	                case 0:
	                    continu = 0;
	                    system("cls");
	                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t *-*-*-*  Merci de faire confiance a KALATA - BANK SA !!!   *-*-*-*\n");
	                    //exit("cls");
	                    break;
	                default:
	                    system("cls");
	                	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t *-*-*-*  Merci de faire confiance a KALATA - BANK SA !!!   *-*-*-*\n");
	                    break;
	                }
    }while(continu);

}
void selection_compte();
void selection_compte()
{
    unsigned int ID_CLIENT, ID_COMPTE = 1500000;
    int choix1, choix2, continu;
    do{
        menu_compte();
        printf("\t         Votre choix > >:\t");
        scanf("%d", &choix1);
        switch(choix1)
        {
            case 1:
                charge();
                existance(ID_COMPTE);
                system("cls");
                Creer();
            break;
            case 2:
                charge();
                system("cls");
                printf("Quel est le numero ID du compte dont vous voulez consulter le solde ?   >:\n");
                scanf("%d", &ID_COMPTE);
                Consultation_solde(ID_COMPTE);
            break;
            case 3:
                //charge();
                system("cls");
                printf("Quel est le numero ID du compte que vous voulez supprimer?   >:\n");
                scanf("%d", &ID_COMPTE);
                Fermer_le_Compte(ID_COMPTE);
                break;
            case 4:
                charge();
                system("cls");
                Afficher_Les_Comptes();
            break;
            case 5:
                system("cls");
                menu_main();
        }
        //system("cls");
        printf("\nvoulez vous continuer ? (1 / 0) 1 pour oui et 0 pour non:");

	            scanf("%d", &continu);
	            switch (continu) {
	                case 1:
	                    continu = 1;
	                    break;


	                case 0:
	                    continu = 0;
	                    system("cls");
	                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t *-*-*-*  Merci de faire confiance a KALATA - BANK SA !!!   *-*-*-*\n");
	                    //exit("cls");
	                    break;
	                default:
	                    system("cls");
	                	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t *-*-*-*  Merci de faire confiance a KALATA - BANK SA !!!   *-*-*-*\n");
	                    break;
	                }
    }while(continu);
}


 /* ***********************************************************************
    *************************  FIN  ****************************************
    */
void chargement();
void chargement()
{
    long int i = 0;
    char espace[50] = "                              .";
    strcpy(espace, "");
    while(i < 200000000)
    {
        strcat(espace, ".    ");
        printf("%s", espace);
        system("cls");
    i++;
    }
}

void charge();
void charge()
{
    int i = 0;
    do{
        chargement();
        i++;
    }while(i<2);
}
int main()
{

    menu_main();
    return 0;
}

void retrait(unsigned int ID_COMPTE, int Solde)
{
    int somme=0, nouv_solde;
    char c , chaine[TAILLE_MAX],token,temp;
    FILE* compte = fopen("comptes.txt","a");
    if(compte ==NULL)
    {
        printf("\nImpossible d'ouvrir le fichier");
    	return;
    }
    printf("entrez l'identité  du compte : ");
    scanf("%u",&ID_COMPTE);

    do
    {
        printf("entrez le montant:");
        scanf("%d",&somme);
        if(Solde>=25000 && somme<250000)

        while(fgets(chaine ,255 ,compte) != NULL)
        {
            strcpy(temp,chaine);
            token = strtok(chaine,";");
            if(strcmp(token,Solde) == 0 && Solde>=25000 && somme<250000 )
                nouv_solde = Solde - somme;

        }
        printf("RETRAIT IMPOSSIBLE");
        printf("voulez vous reessayer o/n? :");
        scanf("%s",&c);
        if(c=='n')
            MenuOperation();
    }while(nouv_solde<=25000 || c=='o' );
    printf("RETRAIT EFFECTUER");
}

void MenuOperation()
{
            int choix, Solde;
            unsigned int ID_COMPTE;
    do{
        printf("\t &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& KALATA_BANK &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
        printf("\t &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& *-*-*-*-*-* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
        printf("\t &&&&&                                                                          &&&&&\n");
        printf("\t *-*-*                             GESTION DES OPERQTIONS                       *-*-*\n");
        printf("\t &&&&&                               ====== **** ======                         &&&&&\n");
        printf("\t *-*-*                                                                          *-*-*\n");
        printf("\t &&&&&                                                                          &&&&&\n");
        printf("\t *-*-*                     MENU:                                                *-*-*\n");
        printf("\t &&&&&                     ====                                                 &&&&&\n");
        printf("\t *-*-*            1- RETRAIT                                                    *-*-*\n");
        printf("\t &&&&&                                                                          &&&&&\n");
        printf("\t *-*-*            2- VIREMENT                                                   *-*-*\n");
        printf("\t &&&&&                                                                          &&&&&\n");
        printf("\t *-*-*            3- MENU GENERAL                                               *-*-*\n");
        printf("\t &&&&&                                                                          &&&&&\n");
        printf("\t *-*-*                                                                          *-*-*\n");
        printf("\t &&&&&&&&&&&&&&&&&&&&&&                                           &&&&&&&&&&&&&&&&&&&\n");

           printf("\t *-*-*   Votre choix:\t");
        scanf("%d\a",&choix);
    }while(choix <= 0||choix>3);

    switch(choix)
    {
         case 1:
            system("cls");
            retrait(ID_COMPTE, Solde);
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("\t OPERATION EFFECTUEE AVEC SUCCES ! ! !  \n");
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            break;
        case 2:
            system("cls");
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            printf("\t OPERATION EFFECTUEE AVEC SUCCES ! ! !  \n");
            printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            break;
        case 3:
            system("cls");
            menu_main();
            break;
    }
}
