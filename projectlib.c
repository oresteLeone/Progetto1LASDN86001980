#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projectlib.h"

// funzione per aggiungere un nodo studente all'ABR dei studenti
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

// funzione di ricerca per trovare il minimo nodo di un albero
int ricercaMinABRStudente(studente *rad){
    
    int min=0;
    if(rad){
        if(rad->sx==NULL)
            min=rad->matricola;
        else 
            min=ricercaMinABRStudente(rad->sx);
        
    }
    return min;
}

// funzione per eliminare un nodo con una certa matricola dall'ABR studenti 
void eliminaNodoABRStudente(studente **rad,int matr){
    studente *aux;
    aux=*rad;
    if(*rad){
        if((*rad)->matricola > matr){
            eliminaNodoABRStudente(&(*rad)->sx,matr);} // CERCA A SINISTRA
        else if ((*rad)->matricola < matr){
            eliminaNodoABRStudente(&(*rad)->dx,matr);} // CERCA A DESTRA
        else{ // ELEMENTO TROVATO
            if(!((*rad)->sx) && !((*rad)->dx)){
                free(*rad);
                *rad=NULL;
            }
            else if( ((*rad)->sx) && (!((*rad)->dx)) ){ //se dx è vuoto
                *rad=aux->sx;}
            else if( (!((*rad)->sx)) && ((*rad)->dx) ){ // se sx è vuoto
                *rad=aux->dx;}
            else if((aux->dx==NULL) || (aux->sx==NULL) ){
                free(aux);
                return;
            }
            else if ( ((*rad)->sx) && ((*rad)->dx) ){ // se sx e dx non vuoti
                (*rad)->matricola=ricercaMinABRStudente((*rad)->dx);
                eliminaNodoABRStudente(&(*rad)->dx,(*rad)->matricola);
            }  
        }
    }
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
            return; // funzione gestioni errori?
        }

        printf("\nInserisci nome libro richiesto in prestito: ");
        scanf("%s",nomeObj);
        foundLib=ricercaLibro(*radLibro,nomeObj);
        if(foundLib){
            printf("\nElaborazione dati ");
            addNodoStudente(radStudente,matr,nomeStudente);
            
        }else{
            printf("\nIl libro richiesto non è presente in catalogo...\toperazione annullata");
            return; // funzione gestione errori?
        }
    }else{
        strcpy(tipo,"restituzione");
        printf("\nInserisci nome libro da restituire: ");
        scanf("%s",nomeObj);
        foundLib=ricercaLibro(*radLibro,nomeObj);
        if(!foundLib){
            printf("\nIl libro presentato non è presente in catalogo...\toperazione annullata");
            return; // funzione gestione errori?
        }else 
            printf("\nElaborazione dati ");
            
             

    }
    libro *refLib=referenceLibro(*radLibro,nomeObj);
    studente *refStud=NULL;
    if(strcmp(tipo,"restituzione")==0){
        if(refLib->prestito==NULL){
            printf("\nAbbiamo già un libro con quel nome, quello presentato apparterrà ad altri...\toperazione annullata");
            return;
            }else {
                refStud=referenceStudente(*radStudente,refLib->prestito->matricola);
            } 
    }else {
        refStud=referenceStudente(*radStudente,matr);
    }

    richiesta *request=addNodoRichiesta(tipo, refStud , refLib);    
    enQueue(coda, request);
    printf("\n Operazione effettuata con successo! Gestiremo la richiesta il prima possibile...\n");

}

// funzione per l'accodamento della coda di richieste
void enQueue(queue *coda,richiesta *nodo){
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

// funzione che restituisce se la coda è vuota
int emptyQueue(queue *coda){
    return coda->head==NULL;
}

// funzione gestione richieste
void tryRequest(queue *coda,studente **radStudente){
    richiesta *tmp=NULL;
    if(strcmp(coda->head->tipo,"prestito")==0){
        if(coda->head->oggetto->prestito==NULL){
            coda->head->oggetto->prestito=coda->head->richiedente;
            tmp=deQueue(coda);
        }else{
            printf("\nIl libro è stato già dato in prestito alla matricola %d... ",coda->head->oggetto->prestito->matricola);
            printf("\nLo studente desidera attendere che sia nuovamente disponibile?(1.SI 0.NO): ");
            int chc=-1;
            do{
                scanf("%d",&chc);
                if(chc!=1 && chc !=0)     printf("\nPerfavore, inserisci 1 o 0; ");
            }while(chc!=1 && chc !=0);
            tmp=deQueue(coda);
            if(chc==1){
                enQueue(coda,tmp);
            }else if(chc==0){
                eliminaNodoABRStudente(radStudente,tmp->richiedente->matricola);
                
            }
        }
        
    }else{
        tmp=deQueue(coda);
        tmp->oggetto->prestito=NULL;
        eliminaNodoABRStudente(radStudente,tmp->richiedente->matricola);

    }
}

// funzione che rimuove una richiesta dalla coda
richiesta *deQueue(queue *coda){
    richiesta *tmp=NULL;
    if(coda->head==coda->tail){
        tmp=coda->head;
        coda->head=NULL;
        coda->tail=NULL;
    }else{
        tmp=coda->head;
        coda->head=coda->head->next;
        coda->tail->next=coda->head;
    }
    return tmp;    
}