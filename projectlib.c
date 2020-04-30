#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projectlib.h"

// funzione di inserimento nodo nell'ABR libri
void addNodoLibro(libro **rad, char *nome ){
    //se la radice è vuota creo il nodo e lo imposto come radice
    if(!(*rad)){
            libro *aux=(libro *)malloc(sizeof(libro));
            strcpy(aux->nomeLibro,nome);    //copio "nome" nel nomelibro
            aux->prestito=NULL;
            aux->sx=NULL;
            aux->dx=NULL;
            *rad=aux;
            return;

    }else if (strcmp((*rad)->nomeLibro, nome)<0)  {     // se il nome in radice è più piccolo di "nome"
            addNodoLibro(&(*rad)->dx , nome);}          // vado nel sottoalbero destro
     else if (strcmp((*rad)->nomeLibro, nome)>0){       // se il nome in radice è più grande di "nome"
            addNodoLibro(&(*rad)->sx , nome);}          // vado nel sottoalbero sinistro
}

// funzione inizializzazione ABR libri
void initializeABRLibro(libro **rad){
    int i=0;
    char stringabase[8];
    for(i=0;i<maxlibri;i++){
        int c=i+1;
        sprintf(stringabase,"%s%2d","libro",c);
        addNodoLibro(rad,stringabase);
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