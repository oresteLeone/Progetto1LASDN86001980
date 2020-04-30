#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projectlib.h"

// funzione di inserimento nodo nell'ABR libri
void addNodoLibro(libro **rad, char *nome ){
    
    if(!(*rad)){
        // printf("\nrad è nullo");
            libro *aux=(libro *)malloc(sizeof(libro));
        //    printf("\nsto creando il nuovo nodo");
            strcpy(aux->nomeLibro,nome);
            aux->prestito=NULL;
            aux->sx=NULL;
            aux->dx=NULL;
            *rad=aux;
            printf("\naggiunto il nodo con %s",aux->nomeLibro);
            return;

    }else if (strcmp((*rad)->nomeLibro, nome)<0)  {
        //    printf("\n DESTRA->");   
            addNodoLibro(&(*rad)->dx , nome);}
     else if (strcmp((*rad)->nomeLibro, nome)>0){
        //    printf("\n SINISTRA->");
            addNodoLibro(&(*rad)->sx , nome);}
}

// funzione inizializzazione ABR libri
void initializeABRLibro(libro **rad){
    int i=0;
    char stringabase[8];
    for(i=0;i<maxlibri;i++){
        int c=i+1;
        sprintf(stringabase,"%s%2d","libro",c);
        addNodoLibro(rad,stringabase);
        printf("\n esterno/aggiunto il nodo con %s",stringabase);
    }
    
}

// funzione visita in preordine ABR Libri
void visitaInPreordineLibro(libro *rad){
    if(rad){
        printf("%s ",rad->nomeLibro);
        visitaInPreordineLibro(rad->sx);
        visitaInPreordineLibro(rad->dx);
    }
}