/* Fifo manager v0.2bUnixVer- Gestion cyclique MàJ ecr*/

#include <stdio.h>

#define NB_ELT_MAX 20 //Définition du nombre de valeur maximum du tableau

struct Tpile //Déclaration de la structure stockant la pile FIFO ainsi que les pointeur associés
{   int value[NB_ELT_MAX]; //Déclaration d'un tableau de NB_ELT_MAX valeurs
    int point_wr;//Déclaration du pointeur d'écriture
    int point_rd;//Déclaration du pointeur de lecture
};

int sp_ini(struct Tpile *ini_pile)//Sous programme Initialisation Tpile
{    int ini_vli = 0;//Initialisation du tableau de valeurs
   
     for (ini_vli = 0;ini_vli<(NB_ELT_MAX);ini_vli++) //Initialisation des NB_ELT_MAX valeurs
     {   (*ini_pile).value[ini_vli]=0;
     }; 
     (*ini_pile).point_wr=0;//Initialisation du pointeur d'écriture
     (*ini_pile).point_rd=0;//Initialisation du pointeur de lecture
     return 0;
};

int sp_mpr(char *mpr_chm) //Affichage du menu principal (E/S : choix utilisateur)
{	fprintf (stdout,"\n ->'N'ouvelle Pile\n");
	fprintf (stdout," ->'A'fficher la Pile\n");
	fprintf (stdout," ->'I'nitialiser une Pile\n");
	fprintf (stdout," ->'E'ntrer une nouvelle valeur\n");
	fprintf (stdout," ->'L'ire la prochaine valeur\n");
	fprintf (stdout," ->'Q'uitter\n");
	fprintf (stdout,"\n   >");
	fscanf(stdin,"%c",&(*mpr_chm)); getchar(); //Saisie du choix de l'utilisateur
	return 0;
};

int sp_ecr(struct Tpile *ecr_pile) //Sous programme d'écriture séquentielle
{	int ecr_mde=0; //Initialisation 
	
	while (1) // Boucle de saisie
	{	fprintf(stdout,"\nOrigine du pointeur de lecture (par defaut 0): ");
		(*ecr_pile).point_rd=0; //Réinitialisation du pointeur de lecture dans la boucle en cas d'erreur de saisie
		fscanf(stdin,"%d",&(*ecr_pile).point_rd); getchar(); //Saisie du pointeur de lecture
		if ((((*ecr_pile).point_rd)>=0)&&(((*ecr_pile).point_rd)<=NB_ELT_MAX)) //Si la saisie est conforme
		{	break; //Alors, sortie de la boucle sortie de la boucle de saisie
		};
		fprintf(stdout,"\nErreur de saisie, le pointeur de lecture doit etre compris entre 0 et NB_ELT_MAX\n"); // Sinon, on recommence une itération
	};
	while (1) // Boucle de saisie
	{	ecr_mde=0;//Initialisation de la variable de saisie
		fprintf(stdout,"Nombre de donnees dans le tableau (maximum %d): ",(NB_ELT_MAX-(*ecr_pile).point_rd));
		fscanf(stdin,"%d",&ecr_mde); getchar(); //Saisie du nombre de données du tableau
		ecr_mde--; //Le nombre de valeur du tableau est égal au nombre de cases du tableau + 1
		if ((ecr_mde>0)&&(ecr_mde<=(NB_ELT_MAX-(*ecr_pile).point_rd))) //Si le nombre de données du tableau est inférieur au nombre d'élément max
		{	break; //Alors, sortie de la boucle de saisie
		};
		fprintf(stdout,"\nErreur de saisie, le pointeur d'ecriture doit etre compris entre 1 et NB_ELT_MAX\n");
	};
	for (((*ecr_pile).point_wr)=(*ecr_pile).point_rd;((*ecr_pile).point_wr)<=((ecr_mde+(*ecr_pile).point_rd));(*ecr_pile).point_wr++) //Boucle de saisie des n valeurs choisie en partant du pointeur de lecture
	{	fprintf(stdout,"\tValeur %d : >",((*ecr_pile).point_wr));
		fscanf(stdin,"%d",&(*ecr_pile).value[(*ecr_pile).point_wr]);getchar(); //Saisie d'utilisateur
	};
	return 0;
};

int sp_aff(struct Tpile *aff_pile) //Sous programme d'affichage du tableau (E/S : structure Tpile)
{	int aff_vli=0;

	fprintf(stdout,"\tPointeur d'ecriture : %d, Pointeur de lecture : %d\n\n",(*aff_pile).point_wr,(*aff_pile).point_rd);
	for (aff_vli=(*aff_pile).point_rd;aff_vli!=(*aff_pile).point_wr;aff_vli++) //Lecture des données du point de lecture jusqu'au pointeur d'écriture
	{	
		if (aff_vli==(NB_ELT_MAX)) //Si le bas du tableau est atteint
		{	aff_vli=0;//réinitialisation du pointeur de lecture
		};
		fprintf(stdout,"Position : %d\tValeur : %d\n",aff_vli,(*aff_pile).value[aff_vli]); //Affichage de la valeur associée au pointeur de lecture
		
	};
	fprintf(stdout,"\nLecture de la pile terminee\n\n");
	return 0;
};

int sp_enr(struct Tpile *enr_pile) //Sous programme d'écriture de Srt_fifo.txt
{	int enr_vli;//Création d'un pointeur local pour charger le tableau
	
	FILE * enr_fd_out;

	enr_fd_out=	fopen("Srt_fifo.txt","w");//Ouverture de Srt_fifo.txt en écriture
	fprintf(enr_fd_out,"NB_ELT_MAX = %d\npoint_wr = %d\npoint_rd = %d\n",NB_ELT_MAX,((*enr_pile).point_wr),((*enr_pile).point_rd));
	for (enr_vli=0;enr_vli<NB_ELT_MAX;enr_vli++)//Lecture des données du tableau
	{	fprintf (enr_fd_out,"%d;",(*enr_pile).value[enr_vli]);//Enregistrement du tableau de la structure dans le fichier
	};
	fclose(enr_fd_out); //Fermeture de Srt_fifo.txt
	fprintf(stdout,"\nEnregistrement effectue...\n");
	return 0;
};

int sp_ouv(struct Tpile *ouv_pile) //Sous programme d'ouverture de Srt_fifo.txt
{	int ouv_vli=0; //Création d'un pointeur local pour charger le tableau
	
	FILE * ouv_fd_in;

	ouv_fd_in=	fopen("Srt_fifo.txt","r");
	fscanf(ouv_fd_in,"NB_ELT_MAX = 20\npoint_wr = %d\npoint_rd = %d\n",&((*ouv_pile).point_wr),&((*ouv_pile).point_rd));
	for (ouv_vli=0;ouv_vli<NB_ELT_MAX;ouv_vli++) //Lecture des données du tableau
	{	fscanf(ouv_fd_in,"%d;",&(*ouv_pile).value[ouv_vli]); //Enregistrement de ces données dans le tableau de la structure
	};
	fclose(ouv_fd_in); //Fermeture de Srt_fifo.txt
	
	return 0;
};

int sp_ins(struct Tpile *ins_pile)
{	if ((*ins_pile).point_wr>=NB_ELT_MAX)//Si le pointeur d'écriture atteint le bas du tableau
	{	if (((*ins_pile).point_rd)==0) //Si le pointeur de lecture est déjà à la position 0
		{	fprintf(stdout,"\nEchec : l'ecriture va ecraser une valeur non lue.");//
			return 0; //Blocage de la saisie et retour au menu principal
		}
		else //il ne faut pas initialiser le pointeur d'écriture, sous peine d'écraser un valeur non-lue 
		{	(*ins_pile).point_wr=0;//Initialisation du pointeur d'écriture
		};
	};
	if ((((*ins_pile).point_wr)==((*ins_pile).point_rd-1)))//Si le pointeur d'écriture va atteindre le pointeur de lecture
	{	fprintf(stdout,"\nEchec : l'ecriture va ecraser une valeur non lue.");//
		 //Blocage de la saisie et retour au menu principal
	}
	else
	{	fprintf(stdout,"Valeur de l'element a inserer >"); 
		fscanf(stdin,"%d",&(*ins_pile).value[(*ins_pile).point_wr]);	getchar();//Saisie d'une valeur dans le tableau
		(*ins_pile).point_wr++;//Incrémentation du pointeur d'écriture
	};
	return 0;
};

int sp_svl (struct Tpile *svl_pile)
{	
	if ((*svl_pile).point_rd==(*svl_pile).point_wr) //Si le pointeur de lecture a atteint le pointeur d'écriture (pile vide)
	{	fprintf(stdout,"\nLe pointeur de lecture ne peut pas etre superieur au pointeur d'ecriture.\n ");
	}
	else //Si le pointeur de lecture n'a pas atteint le pointeur d'écriture
	{	fprintf(stdout,"Pointeur de lecture: %d\tValeur : %d\n",((*svl_pile).point_rd),(*svl_pile).value[(*svl_pile).point_rd]);
		(*svl_pile).value[(*svl_pile).point_rd]=0;//Mise à zéro de la valeur lue
		(*svl_pile).point_rd++; //Incrémentation du pointeur de lecture
		fprintf(stdout,"\nLe pointeur de lecture vaut maintenant %d\n\n",(*svl_pile).point_rd);
	};
	if (((*svl_pile).point_rd>=NB_ELT_MAX)&&((*svl_pile).point_rd!=(*svl_pile).point_wr)) //Si le pointeur de lecture atteint le bas du tableau et que le poiteur d'écriture n'a pas atteint le pointeur d'écriture
	{	(*svl_pile).point_rd=0; //Initialisation du pointeur de lecture
	};
	return 0;
};

int sp_apl()
{	struct Tpile apl_pile; //Appel de la structure Tpile
    char apl_chm=0; //Initialisation de la variable de choix du menu principal

	sp_ini(&(apl_pile)); //Appel du sous programme d'initialistion de la strucure
	fprintf (stdout,"\t\t\t\tFifo Manager v0.2b\n"); //0.1 Finale /0.2 Ajout du fopen_s

	while (1) //Boucle de saisie du Menu Principal
	{	sp_mpr(&apl_chm); //Appel du sous programme Menu Principal
		switch (apl_chm)  
		{	case 'N' : case 'n' ://Nouveau
			sp_ecr(&(apl_pile)); //Création
			sp_enr(&(apl_pile)); //Enregistement 
			break;

			case 'A' : case 'a' ://Afficher
			sp_ouv(&(apl_pile)); //Appel du sous programme d'ouverture
			sp_aff(&(apl_pile)); //Affichage des valeurs
			break;	

			case 'I' : case 'i' ://Initialiser
			sp_ini(&(apl_pile)); //Appel du sous programme d'initialisation
			sp_enr(&(apl_pile)); //Appel du sous programme d'enregistrement
			break;

			case 'E' : case 'e' ://Ecrire la valeur suivante
			sp_ouv(&(apl_pile)); //Appel du sous programme d'ouverture
			sp_ins(&(apl_pile)); //Ecriture d'une seule valeur au pointeur d'écriture
			sp_enr(&(apl_pile)); //Appel du sous programme d'enregistrement
			break;

			case 'L' : case 'l' ://Lire la valeur suivante
			sp_ouv(&(apl_pile)); //Appel du sous programme d'ouverture
			sp_svl(&(apl_pile)); //lecture de la seule valeur au pointeur de lecture
			sp_enr(&(apl_pile)); //Appel du sous programme d'enregistrement
			break;

			case 'Q' : case 'q' ://Quitter
			return 0;
			break;

			default: //Si la saisie est incorrecte
			fprintf (stdout,"Erreur de saisie, veuillez recommencer...\n");
			break; 
		};
	};
	return 0;
};

int main(void)
{	sp_apl(); //Appel de la sous fonction principale
	return 0;
};
