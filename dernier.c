#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>

//// definitions des objets ////

    typedef int* codeword;
    typedef int* fcodeword;

    /*
    int* message : message normal
    int* codeword : message transforme avec la matrice

    int m : numero du plus grand xi
    int lg : nombre de lignes de G
    int cg : nombre de colones de G
    */

    int longueur_test;

    /// fonctions pour gerer les messages ///

        void controler_bit(int bit){
            /** verif bit = 0 ou 1 */
            if(bit!=1 && bit!=0){
                fprintf(stderr, "### : inserer 1 ou 0\n");
                exit(0);    //a changer pour dire qu il y a eu un probleme
                //exit(0) termine le programme mais comme si il ne s etait rien passe
            }
        }

        int* cree_msg(int l){
            /** cree un msg de long l (pointeur sur int) */
            int* msg = malloc((l)*sizeof(int));
            return msg;
        }

        void modif_msg(int* msg, int p, int bit){
            /** modifie le bit de puissance p en bit dans msg */ 
            controler_bit(bit);
            msg[p] = bit;
        }

        void inserer_msg( int* msg, int l){ // pas uttilise dans les tests finaux
            /* insere le msg scanne a l adresse donnee et ecrase ce qu il y avait avant */
            /* message de long l*/
            int bit;
            printf("inserer msg de %d bits :\n",l);
            for(int i=0 ; i<l; i=i+1){
                printf("%d : ",i);
                scanf("%d",&bit);
                controler_bit(bit);
                msg[i] = bit;
            }
        }
    
        void lire_msg( int* msg, int l){
            printf(" :: ");
            for(int i=0; i< l ; i=i+1){
                printf("%d", msg[i]);
            }
            printf("\n");
        }
    
        int trouver_bit(int* msg, int puiss, int l){ //utile ?
            return msg[l - puiss];
        }
    ///

    /// aleatoire ///

        int* random_msg(int l){
            int* msg = malloc(l*sizeof(int));
            int a;
            for(int i=0; i< l; i=i+1){ // pour toutes les cases du message
                a=(rand()+i)%2; // bit aleatoire : 0 ou 1 -> enlever le i
                modif_msg(msg, i, a); 
            }
            return msg;
        }

        void noize(int* msg, int max_noize, int l){
            /** intoduit au maximum max_noize erreurs (aleatoirement)
                msg : message a modifier
                max_noize : nombre maximum d erreurs
                l : longeur du message                */
            int number = rand()%(max_noize + 1); // nombre d erreurs qu il y aura : entre 0 et max_noize
            for(int i=0; i<=number; i=i+1){   
                int k = rand()%(l+1); // on prend un indice au hazard : attention il peut etre choisi plusieures fois
                modif_msg(msg, k, (msg[k]+1)%2); // on change le bit correspondant
            }
        }

        void randp_noize(int* msg, int max_noize, int p, int l){
            /** intrudit des erreurs selon une proba p et max_noize erreurs au max*/
            //proba de changer :
            //int number = rand()%(max_noize + 1);
            int proba; // si elle est inferieure a p alors l erreur se produit (on genere un nb entre 0 et 100)
            int compteur = 0;

            for(int i=0 ; i<max_noize; i=i+1){ // au max max_noize erreurs
                proba = rand()%(100+1) ; // nb entre 0 et 100
                int k = rand()%(l);  // indice entre 0 et l-1
                //pourrait changer plusieurs fois le meme bit
                if(proba<=p ){
                    modif_msg(msg, k, (msg[i]+1)%2);
                    compteur = compteur+1; // nb d erreurs
                }
            }
        }
    ///

//// CODE REPETITION 3 ////

    int** codage_repetition(int* message, int l){
        // pour chaque bit mon l envoie 3 fois : tableau qui contient des tableau de long 3 avec le bit repete
        int** code = malloc(l*sizeof(int*)); 
        for(int i=0; i<l; i=i+1){
            code[i]=malloc(3*sizeof(l));
        }
        for(int i=0; i<l; i=i+1){
            for(int j=0; j<3; j=j+1){
                code[i][j]=message[i];
            }
        }
        return code;
    }
    
    int majorite(int a, int b, int c){
        // donne le bit majoritaire
        int count=0;
        if(a==0){    count = count+1;}
        if(b==0){    count = count+1;}
        if(c==0){    count = count+1;}
        if(count>=2){
            return 0;
        }else{
            return 1;
        }
    }
    
    int* decodage_repetition(int** code_r, int l){
    
        int* message = malloc(l*sizeof(int));
    
        for(int i=0; i<l; i=i+1){
            message[i]= majorite(code_r[i][0], code_r[i][1], code_r[i][2]);
        }
        return message;
    }
////

//// REED MULLER ////

    /// outils :

        int puiss2(int n){
            // retourne 2 puiss n (on peut aussi le faire en malipulant les bits c plus efficace
            if(n==0){ 
                return 1;
            }else{
                int p=1;
                for(int i=1; i<=n; i=i+1){
                    p=p*2;
                }
                return p;
            }
        }

        int factorielle(int a){
            //retourne a!
            int fact=1;
            for(int i=1; i<=a; i=i+1){
                fact = fact*i;
            }
            return fact;
        }

        int calcul_nb_ligne(int r, int m){ // nb de lignes
            /**  nb de lignes de la matrice : somme des (k parmi m) vecteurs possibles de degre k (r=0->k)*/
            int s=0;
            for(int k=0; k<=r; k=k+1){
                s = s + (factorielle(m)/(factorielle(m-k)*factorielle(k))) ;
                // peut etre ameliorable avec le triangle de pascal ou la formule sans nom ? a voir mais peu probablef    
            }
            return s;
        }

        /*
        int* add(int* msg1, int* msg2){
            /** calcule addition de 2 vecteurs 
            int* final = malloc((MAX_PUISS+1)*sizeof(int));
            if (final == NULL) { ; }

            for(int i = 0; i<=MAX_PUISS; i=i+1){
                controler_bit(msg1[i]);
                controler_bit(msg2[i]);
                final[i] = (msg1[i]+msg2[i])%2;
            }
            return final;
        }

        int* barre(int* msg){
            //** calcule le complementaire d un vecteur 
            int* final = malloc((MAX_PUISS+1)*sizeof(int));
            if (final == NULL) { printf("erreur"); }
            for(int i = 0; i<=MAX_PUISS; i=i+1){
                controler_bit(msg[i]);
                final[i]= (msg[i]+1)%2;
            }
            return final;
        }

        int prod_scal(int* u, int* v){
            int s=0;
            for(int i=0; i<=MAX_PUISS; i=i+1){
                s=s+u[i]*v[i];
            }
            return s%2 ;
        }
        */

        int* mult(int* msg1, int* msg2, int* final,int c){
            // calcule la mult de 2 vecteurs  et pas de matrices !
            // !!! soit on retourne un final que l on a cree soi on modif celui qui est en parametres et on renvoie void
            for(int i=0; i<c; i=i+1){
                final[i]= msg1[i]*msg2[i];
            }
            return final;
        }

        void phi_xi(int i, int m, int* result){
            /** donne les xi (i=1 -> m) mais indexes 0 -> m-1*/
            int bit=0;
            int puiss = puiss2(m-(i+1));
            int j=0;
            while(j<puiss2(m)){ //on recommence en alternant 0 et 1
                for(int k=0; k<puiss; k=k+1){// partie que 0 ou que 1 long 2^(m-(i+1))
                    result[j]=bit;
                    j=j+1;
                }
                bit=(bit+1)%2;
            }  
        }

        void affiche_matrice(int** matrice,int r, int m, int i){
            int l = i;
            int c = puiss2(m);

            for(int i=0; i<l; i=i+1){
                for(int j=0; j<c; j=j+1){
                    printf("%d ", matrice[i][j]);
                }
                printf("\n");
            }
        }

    ///

    /// FONCTIONS PRINCIPALES ///

        int** mat(int r, int m){
            /* on commence par les degres les plus petits degres */
            int l=calcul_nb_ligne(r,m); // hauteur / nb vecteurs de la mat
            int c = puiss2(m); // largeur / longueur des vecteurs

            int** matrice = malloc(l*sizeof(int*));
            if (matrice == NULL) 
            { printf("erreur matrice"); }

            // premiere ligne : init en 1
            matrice[0]=malloc(c*sizeof(int));
            if (matrice[0] == NULL) 
            { printf("erreur ligne0 matrice"); }
            for(int j=0; j<c; j=j+1)
            { matrice[0][j]=1; }

            // lignes degre 1
            if(r>=1)
            {
                int* reference = malloc (l*sizeof(int)); 
                // tableau contenant le dernier facteur du vecteur i a la case i
                if (reference == NULL) 
                { printf("erreur reference"); }
                for(int i=1;i<=m;i=i+1)
                {
                    matrice[i]=malloc(c*sizeof(int));
                    if (matrice[i] == NULL) { printf("erreur ligne matrice"); }

                    phi_xi(i-1,m,matrice[i]); // x0 sur la case 1
                    reference[i-1]=i;
                }

            // lignes degre sup a 2
                if(r>=2)
                {
                    int ind_dern_vect = 1; // donne l indice du dernier vecteur
                    int j = 2; // num du vect a multiplier +1 
                    //(premier vect de degre 2 : x0x1 et x1 est sur la 2e ligne)

                    for (int i=m+1 ;i<l; i=i+1)
                    {
                        matrice[i]= malloc(c*sizeof(int)); //lignes de la matrice
                        if (matrice[i] == NULL) 
                        { 
                            printf("erreur ligne mat mult"); 
                        }
                    
                        mult(matrice[ind_dern_vect],matrice[j], matrice[i],c); 
                            // matrice[ind_dern_vect] -> vecteur de degre k-1
                            // matrice[j] -> vecteur de degre 1
                            // matrice[i] -> emplacement ou mettre le resultat
                        reference[i-1]=j;

                        if(j == m)
                        { 
                            // quand on arrive sur une fin et que l on doit changer de vect de reference
                            j=reference[ind_dern_vect]+1;
                            ind_dern_vect = ind_dern_vect+1; 
                        }
                        else
                        {
                            j=j+1; // cas normal
                        }
                    }
                }
                free(reference);
            }
            return matrice;
        }

        int** multmat(int l1, int c1_l2, int c2, int** mat1, int** mat2){
            // multiplier des matrices;
            int** mat = malloc(l1*sizeof(int*));
            // AB[i][j] = somme de 0 a c1_l2 des A[i][k]*B[k][j]
            for(int i=0; i<l1; i=i+1)
            {   //les i
                mat[i]=malloc(c1_l2*sizeof(int));
                for(int j=0; i<c2; j=j+1)
                {   // les j
                    for(int l=0; l<c1_l2;l=l+1)
                    {   // les k
                        mat[i][j] = mat[i][j] + mat1[i][l]*mat[l][j];
                    }
                }
            }
            return mat;
        }
    ///

    /// codage ///

        int* generer_mot_de_code(int* message, int** mat, int c, int m){ 
            // c est 2 puiss m : le nb de valuations possibles de x1...xm
            // on remarque que les colones de la matrice de degre 1 sont toutes les evaluations possibles
            //il suffit de multiplier les ai avec le bon coeff et de faire la somme.
            int* mot_de_code = malloc(c*sizeof(int));
            for(int i=0; i<c; i=i+1)
            {
                mot_de_code[i]=0;
            }

            for(int col = 0; col<c; col=col+1)
            { // pour chaque colone (valuation de x1...xm)
                for(int ligne=0; ligne<=m; ligne=ligne+1)
                { 
                    //on multiplie la ligne i-1(car on a commence a 0 et pas a 1) avec ai et on somme
                    mot_de_code[col]=(mot_de_code[col]+ message[ligne]*mat[ligne][col]);
                }    
                mot_de_code[col]=mot_de_code[col] %2;
            }
            return mot_de_code;
        }
    ///

    /// decodage ///

        int maximum_vraisemblance(int* valeurs, int l){
            int count =0;
            for(int i=0; i<l; i=i+1)
            {
                if(valeurs[i]==0)
                {
                    count=count+1;
                }
            }
            if(count >= l/2)
            {
                return 0;
            }else{
                return 1;
            }
        }

        int* decoder(int* code, int** matrice, int m, int c){

            // les a1 ... am sans a0

            int* valeurs_coefs = malloc((m+1)*sizeof(int)); 

            for(int i=0; i<=m; i=i+1){ // init coeffs a 0
                valeurs_coefs[i]=0;
            }
            int nb_sommes = puiss2(m-1);
            int* sommes = malloc( nb_sommes*sizeof(int));  /// il y a trop de pointeurs
            int a; int b;
            int compteur;
            int puiss ;
            for(int i = 1; i <= m; i = i + 1){ 
                compteur = 0; 
                puiss = puiss2(m-i);
                for(int k = 0; k < c; k = k + 1){
                    if ((k & puiss) == 0) { // choisir les paires ou le bit est a 0
                        a = k;
                        b = k | puiss; // l autre est celui avec le bit a 1 (indice)
                        sommes[compteur] = (code[a] + code[b]) % 2;
                        compteur = compteur + 1;
                        }
                    }
                    valeurs_coefs[i] = maximum_vraisemblance(sommes, nb_sommes); 
                }
            free(sommes);

            // pour a0
            int* mot_sans_a0 = malloc(c*sizeof(int));
            for(int i=0; i<c; i=i+1)
            {
                mot_sans_a0[i]=0;       // init a 0
            }
            for(int ligne=1; ligne<=m; ligne=ligne+1)
            {
                for(int col=0; col<c; col=col+1)
                {
                    mot_sans_a0[col]=mot_sans_a0[col]+valeurs_coefs[ligne]*matrice[ligne][col];
                }
            }
            for(int i=0; i<c; i=i+1){
                code[i]= (code[i] + mot_sans_a0[i])%2; //// on a change le code recu maintenant il contient des valeurs probable de a0
            }

            valeurs_coefs[0] = maximum_vraisemblance(code,c);
            free(mot_sans_a0);
            return valeurs_coefs;
        }
    ///
////

//// MAIN ////

int main(void){

    printf("\n");
    srand(time(NULL));  // pour l aleatoire
    int y = 10000;

    double* temps_encodage_repetition = malloc(y*sizeof(double));
    double* temps_decodage_repetition = malloc(y*sizeof(double));

    double* temps_encodage_muller = malloc(y*sizeof(double));
    double* temps_decodage_muller = malloc(y*sizeof(double));

    // CONSTANTES
        int r = 1;
        int m = 7 ;
        int c = puiss2(m);
        printf("r::%d, m::%d, c::%d\n",r,m,c);
        printf("\n");
        clock_t start, end;
        double cpu_time_used;
    //

    

    int** mots_possibles = mat(r,m);

    double moy_encodage_repetition =0;
    double moy_encodage_muller=0;
    double moy_decodage_repetition=0;
    double moy_decodage_muller=0;

    int* message = malloc((m+1)*sizeof(int));  // a enlever si on fait random

    for(int f=0; f<c; f=f+1){

        //MESSAGE

        for(int w=0; w<m+1; w=w+1){

            message[w]=mots_possibles[w][f];

        }
            
        //message = random_msg(m+1);
        //printf("message\n\n");
        //printf("    ");
        //lire_msg(message, m+1);
        //printf("\n"); 

        //
            
        for(int z=0; z<y; z=z+1){

            

            //MATRICE
                start = time(NULL);  // debut encodage muller
                int** matrice = mat(r,m);
                //printf("MATRICE \n\n");
                //affiche_matrice(matrice,r,m,calcul_nb_ligne(r,m));
                //printf("\n");
            //

            //  ENCODAGE
                int* code;
                //printf("ENCODAGE\n\n");
            
                /*int* message = malloc(4*sizeof(int));
                message[0]=1;
                message[1]=0;
                message[2]=1;
                message[3]=1;*/
                
                //printf("    ");
                code = generer_mot_de_code(message, matrice, c,m);
                end = time(NULL);  // fin encodage muller
                temps_encodage_muller[z]=(double)(end - start);
                //lire_msg(code, c);
                //printf("\n");
            //


            // DECODAGE
            //printf("ERREURS\n\n");

            randp_noize(code,1, 100, c);
            //printf("    "); 
            //lire_msg(code, c);
            

            //printf("\nDECODAGE\n\n");
            start = time(NULL); // debut decodage muller
            int* decode = decoder(code, matrice, m,c);
            end = time(NULL); // end decodage muller
            temps_decodage_muller[z]=(double)(end - start);
            //printf("    ");
            //lire_msg(decode, m+1);


            /// CODE REPETITION
                
                //printf("\n CODE REPETITION : \n\n");

                int* message_repetition = random_msg(m+1);
                //lire_msg(message_repetition, m+1);

                ///// encodage

                start = time(NULL); // debut tps encodage repetition

                int** code_repetition = codage_repetition(message_repetition, m+1);
                end = time(NULL);// fin tps encodage repetition

                temps_encodage_repetition[z]=(double)(end - start);

                ///// erreurs

                for(int i=0; i<m+1; i=i+1){
                    randp_noize(code_repetition[i],1,100,3);
                }

                ///// decodage
                free(message_repetition);
                start = time(NULL); // debut tps decodage repetition
                message_repetition = decodage_repetition(code_repetition, m+1);
                end = time(NULL); // fin tps decodage repetition
                temps_decodage_repetition[z]=(double)(end - start);
                free(message_repetition);
                for(int h = 0; h<m+1; h=h+1){
                    free(code_repetition[h]);
                }
                free(code_repetition);
                
            //



            // free
                
                free(code);
                free(decode);
                for(int i=0; i<m+1; i=i+1){
                    free(matrice[i]);
                }
                free(matrice);
            //
            
            //printf("\n\n");

        }
        
        

        for(int z=0; z<y; z=z+1){
            moy_decodage_muller = moy_decodage_muller + temps_decodage_muller[z];
            moy_encodage_muller = moy_encodage_muller + temps_encodage_muller[z];
            moy_decodage_repetition = moy_decodage_repetition + temps_decodage_repetition[z];
            moy_encodage_repetition = moy_encodage_repetition + temps_encodage_repetition[z];
        }

        //moy_decodage_muller = moy_decodage_muller ;
        //moy_encodage_muller = moy_encodage_muller ;
        //moy_decodage_repetition = moy_decodage_repetition ;
        //moy_encodage_repetition = moy_encodage_repetition;
        
        
    }
    free(message);
    free(temps_decodage_muller);
    free(temps_decodage_repetition);
    free(temps_encodage_muller);
    free(temps_encodage_repetition);

    
    moy_decodage_muller = moy_decodage_muller/c ;
    moy_encodage_muller = moy_encodage_muller/c ;
    moy_decodage_repetition = moy_decodage_repetition/c;
    moy_encodage_repetition = moy_encodage_repetition/c;
    printf("\n\ner : %f, dr %f, em : %f, dm : %f\n\n", moy_encodage_repetition,moy_decodage_repetition,moy_encodage_muller,moy_decodage_muller);

    for(int i=0; i<m+1; i=i+1){
        free(mots_possibles[i]);
    }
    free(mots_possibles);
}
