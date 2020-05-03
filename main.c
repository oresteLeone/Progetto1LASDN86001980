#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projectlib.h"


int main(){

    // inizializzazione ABR libri
    printf("\nInizializzazione programma...");
    libro *radLibro = (libro *)malloc(sizeof(libro));
    radLibro=NULL;
    initializeABRLibro(&radLibro);

    // prima stampa per visualizzare all'utilizzatore
    // l'elenco dei libri
    printf("\nCatalogo libri:\n");
    visitaInPreordineLibro(radLibro);
    printf("\n***Fine Elenco***\n");

    //inizializzazione Coda richieste
    queue *coda=(queue *)malloc(sizeof(queue));
    initializeQueue(coda);

    // inizializzazione ABR Studenti
    studente *radStudente = (studente *)malloc(sizeof(studente));
    radStudente=NULL;

    // inizializzazione variabili d'ambiente
    int prestiti=0;
    int sospese=1;
    int canIclose=0; // flag d'uscita
    int choice=-1;
    int lenghtCoda=0;

    // menu interattivo
    do{
        printf("\n1. Aggiungere una richiesta ");
        printf("\n2. Gestire le richieste (%d)",lenghtCoda=lenghtQueue(coda,coda->head));
        printf("\n3. Stampa catalogo libri ");
        printf("\n4. Stampa libri attualmente in prestito (%d) ",prestiti=nPrestiti(radLibro));
        printf("\n0. Terminare ");
        printf("\n input: ");
            do{
                scanf("%d",&choice);
                if(choice<0 || choice>5)
                    printf(" Non valido!\n input: ");
            }while(choice<0 || choice>5);


        switch(choice){
            case 1:
                printf("\n\tAggiungere una richiesta: \n");
                catchRequest(&radStudente,&radLibro,coda);
                printf("\n***Fine Operazione***\n");
                               
                break;
            case 2:
                printf("\n\tGestire le richieste: \n");
                if(!emptyQueue(coda)){
                    printf("\nCoda prima della gestione : \n");
                    printQueue(coda,coda->head);
                    tryRequest(coda,&radStudente);
                    printf("\nCoda dopo la gestione : \n");
                    if(!emptyQueue(coda)) 
                        printQueue(coda,coda->head);
                    else 
                        printf("\nNon ci sono ulteriori richieste!\n");
                }else 
                    printf("\nNon ci sono richieste!\n");
                printf("\n***Fine Operazione***\n");
                
                break;
            case 3:
                printf("\nLibri in catalogo:\n");
                visitaInPreordineLibro(radLibro);
                printf("\n***Fine Elenco***\n");

                break;
            case 4:
                printf("\nLibri attualmente in prestito: %d \n",prestiti=nPrestiti(radLibro));
                visitaInPreordineLibroInPrestito(radLibro);
                printf("\n***Fine Elenco***\n");

                break;
            case 0:
                sospese=emptyQueue(coda);
                prestiti=nPrestiti(radLibro);
                if(sospese && (prestiti==0)) {
                        printf("\nChiusura programma in corso...\n");
                        canIclose=1;
                }else if(!sospese)
                    printf("\nSono presenti richieste in sospeso da gestire! \n");
                else if(prestiti!=0)
                    printf("\nNon tutti i libri sono stati restituiti, prego sollecitare la restituzione!\n");
                break;
        }

    }while( choice!=0 || canIclose!=1 );

        
    return 0; 
}
