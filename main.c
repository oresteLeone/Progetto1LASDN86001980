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
    visitaInOrdineLibro(radLibro);
    printf("\n***Fine Elenco***");

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
        printf("\n*****\t Menu \t*****");
        printf("\n1. Aggiungere una richiesta ");
        printf("\n2. Gestire le richieste (%d)",lenghtCoda=lenghtQueue(coda,coda->head));
        printf("\n3. Stampa catalogo libri ");
        printf("\n4. Stampa libri attualmente in prestito (%d) ",prestiti=nPrestiti(radLibro));
        printf("\n0. Terminare ");
        printf("\n input: ");
            do{             //permette solo l'iserimento di valori compresi tra 0 e 4
                scanf("%d",&choice);
                if(choice<0 || choice>5)
                    printf(" Non valido!\n input: ");
            }while(choice<0 || choice>5);


        switch(choice){
            case 1:
                printf("\n\tAggiungere una richiesta: \n");
                catchRequest(&radStudente,&radLibro,coda);  // Creazione della richiesta di prestito/restituzione
                printf("\n***Fine Operazione***\n");        // ed immissione nella coda in attesa della gestione
                               
                break;
            case 2:
                printf("\n\tGestire le richieste: \n");     // stampa la situazione della coda prima della gestione
                if(!emptyQueue(coda)){                      // del primo elemento e poi stampa la situzione successiva
                    printf("\nCoda prima della gestione : \n"); 
                    printQueue(coda,coda->head);        // stampa precedente
                    tryRequest(coda,&radStudente);      // gestione richiesta in testa
                    printf("\nCoda dopo la gestione : \n");
                    if(!emptyQueue(coda)) 
                        printQueue(coda,coda->head);    // stampa successiva
                    else 
                        printf("\nNon ci sono ulteriori richieste!\n");
                }else 
                    printf("\nNon ci sono richieste!\n");
                printf("\n***Fine Operazione***\n");
                
                break;
            case 3:
                printf("\nLibri in catalogo:\n");
                visitaInOrdineLibro(radLibro);   // stampa in ordine ABR libri
                printf("\n***Fine Elenco***\n");

                break;
            case 4:
                printf("\nLibri attualmente in prestito: %d \n",prestiti=nPrestiti(radLibro));
                visitaInOrdineLibroInPrestito(radLibro); // stampa in ordine SOLO gli elementi con il prestito attivo
                printf("\n***Fine Elenco***\n");

                break;
            case 0:
                sospese=emptyQueue(coda);       // gestione condizioni d'uscita del programma
                prestiti=nPrestiti(radLibro);   // è consentita la chiusura solo se 
                if(sospese && (prestiti==0)) {  // non ci sono richieste in sospeso e siano stati restituiti tutti i libri
                        printf("\nChiusura programma in corso...\n");
                        canIclose=1;        // a condizioni soddisfatte aggiorno la flag d'uscita
                }else if(!sospese)
                    printf("\nSono presenti richieste in sospeso da gestire! \n");
                else if(prestiti!=0)
                    printf("\nNon tutti i libri sono stati restituiti, prego sollecitare la restituzione!\n");
                break;
        }

    }while( choice!=0 || canIclose!=1 );

        
    return 0; 
}
