#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projectlib.h"


int main(){

    printf("\n dovrei inizializzare i libri \n");
    
    libro *rad = (libro *)malloc(sizeof(libro));
    // inizializzo l'albero con la funzione initialize passando come argomento &rad poiché
    // l'inserimento ricorsivo utilizza il doppio puntatore
    initializeABRLibro(&rad);
    
    // qui uso il puntatore singolo e quindi passo rad
    visitaInPreordineLibro(rad);

    int canIclose=0;
    int choice=-1;
    do{
        printf("\n1. Aggiungere una richiesta ");
        printf("\n2. Gestire le richieste ");
        printf("\n0. Terminare ");
        printf("\n input: ");
            do{
                scanf("%d",&choice);
                if(choice<0 || choice>2)
                    printf(" Non valido!\n input: ");
            }while(choice<0 || choice>2);

        printf("\n ho selezionato %d \n",choice);

        switch(choice){
            case 1:
                printf("\n Aggiungere una richiesta (aggiunta una)\n");
                canIclose++;                
                break;
            case 2:
                printf("\n Gestire le richieste (gestita una)\n");
                canIclose--;
                break;
            case 0:
                if(canIclose==0)
                    printf("\n Arrivederci \n");
                else
                    printf("\n ci sono %d richieste in sospeso da gestire! \n",canIclose);
                
            break;
        }

    }while( choice!=0 || canIclose!=0 );

        
    return 0; 
}
