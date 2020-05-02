#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projectlib.h"

void addNodoStudente(studente **rad,int matr, char *nome ){
    //se la radice è vuota creo il nodo e lo imposto come radice
    if(!(*rad)){
            studente *aux=(studente *)malloc(sizeof(studente));
            strcpy(aux->nomeStudente,nome);    //copio "nome" nel nomestudente
            aux->matricola=matr;
            aux->sx=NULL;
            aux->dx=NULL;
            *rad=aux;
            return;

    }else if ((*rad)->matricola < matr)  {     // se la matricola in radice è più piccola di matr
            addNodoStudente(&(*rad)->dx , matr,nome);}          // vado nel sottoalbero destro
     else if ((*rad)->matricola > matr){       // se la matricola in radice è più grande di matr
            addNodoStudente(&(*rad)->sx , matr,nome);}          // vado nel sottoalbero sinistro
}
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
    char stringabase[maxstring];
    for(i=0;i<maxlibri;i++){
        int c=i+1;
        sprintf(stringabase,"%s%d","libro",c);
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

// funzione ricerca libro con restituzione int
int ricercaLibro(libro *rad,char *nome){
    int trovato=0;
    if(rad){
        if(strcmp(rad->nomeLibro,nome)==0)
            return 1;
        else if (strcmp(rad->nomeLibro, nome)<0)  {     // se il nome in radice è più piccolo di "nome"
            trovato=ricercaLibro(rad->dx , nome);}          // vado nel sottoalbero destro
        else if (strcmp(rad->nomeLibro, nome)>0){       // se il nome in radice è più grande di "nome"
            trovato=ricercaLibro(rad->sx , nome);}
    }
    return trovato;
}

// funzione ricerca studente con restituzione int
int ricercaStudente(studente *rad, int matr){
    int trovato=0;
    if(rad){
        if(rad->matricola==matr)
            return 1;
        else if (rad->matricola < matr)  {                  // se la matricola in radice è più piccola di matr
            trovato=ricercaStudente(rad->dx , matr);}       // vado nel sottoalbero destro
        else if (rad->matricola > matr){                    // se la matricola in radice è più grande di matr
            trovato=ricercaStudente(rad->sx , matr);}
    }
    return trovato;
}


// funzione ricerca libro con restituzione puntatore
libro *referenceLibro(libro *rad,char *nome){
    libro *ref=NULL;
    if(rad){
        if(strcmp(rad->nomeLibro,nome)==0){
            ref=rad;
            return ref;}
        else if (strcmp(rad->nomeLibro, nome)<0)  {     // se il nome in radice è più piccolo di "nome"
            ref=referenceLibro(rad->dx , nome);}          // vado nel sottoalbero destro
        else if (strcmp(rad->nomeLibro, nome)>0){       // se il nome in radice è più grande di "nome"
            ref=referenceLibro(rad->sx , nome);}
    }
    return ref;

}

// funzione ricerca studente con restituzione puntatore
studente *referenceStudente(studente *rad, int matr){
    studente *ref=NULL;
    if(rad){
        if(rad->matricola==matr){
            ref=rad;
            return ref;}
        else if (rad->matricola < matr)  {                  // se la matricola in radice è più piccola di matr
            ref=referenceStudente(rad->dx , matr);}       // vado nel sottoalbero destro
        else if (rad->matricola > matr){                    // se la matricola in radice è più grande di matr
            ref=referenceStudente(rad->sx , matr);}
    }
    return ref;

}


// inizializzazione coda
void initializeQueue(queue *coda){
        coda->head=NULL;
        coda->tail=NULL;
}


// creazione richiesta
richiesta *addNodoRichiesta(char *tipo, studente *matricola, libro *oggetto ){
    richiesta *temp = (richiesta *)malloc(sizeof(richiesta));
    if(temp){
        strcpy(temp->tipo ,tipo);
        temp->richiedente=matricola;
        temp->oggetto=oggetto;
        temp->next=NULL;
    }else printf("\n Errore in allocazione Richiesta!");
    return temp;
}

// funzione per l'impacchettamento e accodamento della richiesta
void catchRequest(studente **radStudente,libro **radLibro, queue *coda){
    int caso =-1;
    char tipo[maxstring];
    int matr;
    char nomeStudente[maxstring];
    char nomeObj[maxstring];
    int foundLib=0;
    int foundStud=0;
    printf("\nInserisci tipo richiesta (1.Prestito//0.Restituzione) ");
    do{
        scanf("%d",&caso);
            if(caso!=1 && caso !=0)     printf("\nPerfavore, inserisci 1 o 0; ");
    }while(caso!=1 && caso !=0);
    if(caso){
        strcpy(tipo,"prestito");
        printf("\nInserisci generalità studente ");
        
        printf("\nNome: ");
        scanf("%s",nomeStudente);
        printf("\nMatricola: ");
        scanf("%d",&matr);
        foundStud=ricercaStudente(*radStudente,matr);
        if(foundStud){
            printf("\nLo studente ha già fatto una richiesta di prestito,non è consentito effettuarne un altra...\toperazione annullata");
            exit(-1);
        }

        printf("\nInserisci nome libro richiesto in prestito: ");
        scanf("%s",nomeObj);
        foundLib=ricercaLibro(*radLibro,nomeObj);
        if(foundLib){
            printf("\nElaborazione dati e inserimento richiesta");
            addNodoStudente(radStudente,matr,nomeStudente);
            
        }else{
            printf("\nIl libro richiesto non è presente in catalogo...\toperazione annullata");
            exit(-1);
        }
    }else{
        strcpy(tipo,"restituzione");
        printf("\nInserisci nome libro da restituire: ");
        scanf("%s",nomeObj);
        foundLib=ricercaLibro(*radLibro,nomeObj);
        if(!foundLib){
            printf("\nIl libro presentato non è presente in catalogo...\toperazione annullata");
            exit(-1);
        }else 
            printf("\nElaborazione dati e inserimento richiesta");
            
             

    }
    libro *refLib=referenceLibro(*radLibro,nomeObj);
    studente *refStud=referenceStudente(*radStudente,matr);
    if(strcmp(tipo,"restituzione")==0){
        if(refLib->prestito==NULL){
        printf("\nAbbiamo già un libro con quel nome, quello presentato apparterrà ad altri...\toperazione annullata");
        exit(-1);}
        }

    richiesta *request=addNodoRichiesta(tipo,refStud, refLib);
    enqueue(coda, request);

}

// funzione per l'accodamento della coda di richieste
void enqueue(queue *coda,richiesta *nodo){
    if(coda->head==NULL)
        coda->head=nodo;
    else 
        coda->tail->next=nodo;
    
    coda->tail=nodo;
    coda->tail->next=coda->head;
    
}


// funzione iterativa per la stampa della coda
void printQueue(queue *coda){
    richiesta *temp = coda->head;
    printf("\n Coda richieste:\n");
    while(temp->next!=coda->head){
        printf("%s\t%d\t%s\n",temp->tipo,temp->richiedente->matricola,temp->oggetto->nomeLibro);
        temp=temp->next;
    }
    printf("%s\t%d\t%s\n",temp->tipo,temp->richiedente->matricola,temp->oggetto->nomeLibro);
}

int emptyQueue(queue *coda){
    return coda->head==NULL;
}