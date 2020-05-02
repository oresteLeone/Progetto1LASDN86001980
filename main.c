#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projectlib.h"


int main(){

    printf("\n dovrei inizializzare i libri \n");
    
    libro *radLibro = (libro *)malloc(sizeof(libro));
    // inizializzo l'albero con la funzione initialize passando come argomento &rad poiché
    // l'inserimento ricorsivo utilizza il doppio puntatore
    initializeABRLibro(&radLibro);
    
    // qui uso il puntatore singolo e quindi passo rad
    visitaInPreordineLibro(radLibro);

    queue *coda=(queue *)malloc(sizeof(queue));
    initializeQueue(coda);

    studente *radStudente = (studente *)malloc(sizeof(studente));
    radStudente=NULL;

    
    int canIclose=1; // flag presenza richieste
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
                printf("\n Aggiungere una richiesta (chiamo catch request\n");
                catchRequest(&radStudente,&radLibro,coda);
                               
                break;
            case 2:
                printf("\n Gestire le richieste \n");
                if(!emptyQueue(coda)){
                    printf("\nCoda prima della gestione : ");
                    printQueue(coda);
                    tryRequest(coda,&radStudente);
                    printf("\nCoda dopo della gestione : ");
                    if(!emptyQueue(coda)) 
                        printQueue(coda);
                    else printf("\n VUOTA!");
                }else 
                    printf("\n Non ci sono richieste!");
                
                break;
            case 0:
                canIclose=emptyQueue(coda);
                if(canIclose)
                    printf("\n Arrivederci \n");
                else
                    printf("\n ci sono richieste in sospeso da gestire! \n");
                
            break;
        }

    }while( choice!=0 || canIclose!=1 );

        
    return 0; 
}
