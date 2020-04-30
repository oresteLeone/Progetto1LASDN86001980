#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projectlib.h"

// funzione di inserimento nodo nell'ABR libri
void addNodoLibro(libro **rad, char *nome ){
    printf("\nsto per aggiungere il nodo %s",nome);
    libro *aux=NULL;
    if(!(*rad)){
        printf("\nrad è nullo");
            aux=(libro *)malloc(sizeof(libro));
            printf("\nsto creando il nuovo nodo");
            strcpy(aux->nomeLibro,nome);
            aux->prestito=NULL;
            aux->sx=NULL;
            aux->dx=NULL;
            *rad=aux;

    }else if (!strcmp((*rad)->nomeLibro, nome))     
            addNodoLibro(&(*rad)->sx , nome);
     else if (strcmp((*rad)->nomeLibro, nome))
            addNodoLibro(&(*rad)->dx , nome);
}

// funzione inizializzazione ABR libri
void initializeABRLibro(libro **rad){
    int i=0;
    char stringabase[8];
    for(i=0;i<maxlibri;i++){
        sprintf(stringabase,"%s%d","libro",i+1);
        addNodoLibro(rad,stringabase);
        printf("\naggiunto il nodo con %s",stringabase);
    }
    
}

// funzione visita in preordine ABR Libri
void visitaInPreordineLibro(libro **rad){
    if(rad){
        printf("%s ",(*rad)->nomeLibro);
        visitaInPreordineLibro(&(*rad)->sx);
        visitaInPreordineLibro(&(*rad)->dx);
    }
}