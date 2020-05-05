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
    for(i=0;i<maxlibri;i++){    // immissione automatica di 15 libri qui definiti in stringhe
        if(i==0) 
                addNodoLibro(rad,"harry_potter");
        else if(i==1) 
                addNodoLibro(rad,"il_signore_degli_anelli");
        else if(i==2) 
                addNodoLibro(rad,"il_silmarillion");
        else if(i==3)
                addNodoLibro(rad,"guerra_e_pace");
        else if(i==4) 
                addNodoLibro(rad,"uno_nessuno_e_centomila");
        else if(i==5) 
                addNodoLibro(rad,"1984");
        else if(i==6) 
                addNodoLibro(rad,"orgoglio_e_pregiudizio");
        else if(i==7) 
                addNodoLibro(rad,"moby_dick");
        else if(i==8)
                addNodoLibro(rad,"delitto_e_castigo");
        else if(i==9) 
                addNodoLibro(rad,"il_trono_di_spade");
        else if(i==10) 
                addNodoLibro(rad,"hunger_games");
        else if(i==11) 
                addNodoLibro(rad,"i_miserabili");
        else if(i==12) 
                addNodoLibro(rad,"notre_dame_de_paris");
        else if(i==13) 
                addNodoLibro(rad,"il_codice_da_vinci");
        else if(i==14)
                addNodoLibro(rad,"i_tre_moschettieri");
            
    }
    
}

// funzione visita in ordine ABR Libri
void visitaInOrdineLibro(libro *rad){
    if(rad){
        visitaInOrdineLibro(rad->sx);
        printf("|%s| ",rad->nomeLibro);
        visitaInOrdineLibro(rad->dx);
    }
}

// funzione visita in ordine con output solo di libri in prestito
void visitaInOrdineLibroInPrestito(libro *rad){
    if(rad){
        visitaInOrdineLibroInPrestito(rad->sx);
        if(rad->prestito!=NULL)
                printf("%s ->Matricola: %d %s \n",rad->nomeLibro,rad->prestito->matricola,rad->prestito->nomeStudente);
        visitaInOrdineLibroInPrestito(rad->dx);
    }
}

// funzione che restituisce il numero di libri in prestito
int nPrestiti(libro *rad){
    int count=0;
    if(rad){
        if(rad->prestito!=NULL)
                count++;
        count=count+nPrestiti(rad->sx);
        count=count+nPrestiti(rad->dx);
    }
    return count;
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
    }else printf("\nErrore in allocazione Richiesta!");
    return temp;
}

// funzione per l'impacchettamento e accodamento della richiesta
void catchRequest(studente **radStudente,libro **radLibro, queue *coda){
    // inizializzazioni variabili locali
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

    if(caso){       // CASO PRESTITO
        
        strcpy(tipo,"prestito");
        printf("\nInserisci dati studente ");
        printf("\nNome: ");
        scanf("%s",nomeStudente);
        printf("\nMatricola: ");
        scanf("%d",&matr);
        foundStud=ricercaStudente(*radStudente,matr);   // Se lo studente è già presente nell'albero vuol dire 
        if(foundStud){                                  // che ha già presentato una richiesta di prestito
            printf("\nLo studente ha presentato in precedenza una richiesta di prestito,\nnon e' consentito effettuarne un altra...\toperazione annullata");
            return; 
        }
        printf("\nInserisci nome libro richiesto in prestito: ");
        scanf("%s",nomeObj);
        foundLib=ricercaLibro(*radLibro,nomeObj);
        if(foundLib){   // se il libro è presente, aggiungo il nodo dello studente
            printf("\nElaborazione dati ");
            addNodoStudente(radStudente,matr,nomeStudente);
            
        }else{
            printf("\nIl libro richiesto non e' presente in catalogo...\toperazione annullata");
            return; 
        }
    }else{      // CASO RESTITUZIONE

        strcpy(tipo,"restituzione");
        printf("\nInserisci nome libro da restituire: ");
        scanf("%s",nomeObj);
        foundLib=ricercaLibro(*radLibro,nomeObj);
        if(!foundLib){
            printf("\nIl libro presentato non e' presente in catalogo...\toperazione annullata");
            return; 
        }else 
            printf("\nElaborazione dati ");
            
    }
    libro *refLib=referenceLibro(*radLibro,nomeObj);    // creo i puntatori di riferimento al libro e allo studente
    studente *refStud=NULL;                             // in preparazione della richiesta
    if(strcmp(tipo,"restituzione")==0){
        if(refLib->prestito==NULL){         // se uno studente cerca di restituire un libro che però non è in prestito annulla l'operazione
            printf("\nIl libro presentato non appartiene a questa libreria in quanto e' ancora disponibile al prestito...\toperazione annullata");
            return;
            }else {
                refStud=referenceStudente(*radStudente,refLib->prestito->matricola);
            } 
    }else {
        refStud=referenceStudente(*radStudente,matr);
    }

    richiesta *request=addNodoRichiesta(tipo, refStud , refLib);    // creo la richiesta e l'aggiungo alla coda
    enQueue(coda, request);
    printf("\nOperazione effettuata con successo! Gestiremo la richiesta il prima possibile...\n");

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


// funzione ricorsiva per la stampa della coda
void printQueue(queue *coda,richiesta *request){
   if(!emptyQueue(coda)){
        if(request->next!=coda->head){
            printf("%s\t%d\t%s\n",request->tipo,request->richiedente->matricola,request->oggetto->nomeLibro);
            printQueue(coda,request->next);
        }else
            printf("%s\t%d\t%s\n",request->tipo,request->richiedente->matricola,request->oggetto->nomeLibro);
   }
}

// funzione che restituisce se la coda è vuota
int emptyQueue(queue *coda){
    return coda->head==NULL;
}

// funzione che restituisce la lunghezza della coda
int lenghtQueue(queue *coda,richiesta *request){
    int count=0;
    if(!emptyQueue(coda)){
        if(request->next!=coda->head)
            count=lenghtQueue(coda,request->next);
        count++;
        //richiesta *temp = coda->head;
        //while(temp->next!=coda->head){
        //        count++;
        //        temp=temp->next;
       // }
       // count++;
    }
    return count;
}

// funzione gestione richieste
void tryRequest(queue *coda,studente **radStudente){
    richiesta *tmp=NULL;

    if(strcmp(coda->head->tipo,"prestito")==0){ // Se la richiesta è di PRESTITO

        if(coda->head->oggetto->prestito==NULL){    // se il libro è disponibile
            coda->head->oggetto->prestito=coda->head->richiedente;  // aggiorno la sua condizione col puntatore 
            tmp=deQueue(coda);  // rimuovo la richiesta dalla coda

        }else{  // se il libro NON è momentaneamente disponibile
                // chiedo all'operatore se lo studente è disposto ad aspettare che ritorni disponibile
            printf("\nIl libro %s e' attualmente in prestito alla matricola %d... ",coda->head->oggetto->nomeLibro,coda->head->oggetto->prestito->matricola);
            printf("\nLo studente desidera attendere che sia nuovamente disponibile?(1.SI 0.NO): ");
            int chc=-1;
            do{
                scanf("%d",&chc);
                if(chc!=1 && chc !=0)     printf("\nPerfavore, inserisci 1 o 0; ");
            }while(chc!=1 && chc !=0);
            tmp=deQueue(coda);
            if(chc==1){     // Se vuole attendere lo inserisco in coda alla Queue
                enQueue(coda,tmp);
            }else if(chc==0){   // se non vuole attendere per poter richiedere un'altro libro
                eliminaNodoABRStudente(radStudente,tmp->richiedente->matricola);
                // eliminando il nodo, lo studente è in grado di effettuare una nuova richiesta di prestito
            }
        }
    }else{  // se la richiesta è di RESTITUZIONE

        tmp=deQueue(coda);      // rimuovo dalla coda e aggiorno la disponibilità del libro
        tmp->oggetto->prestito=NULL;
        eliminaNodoABRStudente(radStudente,tmp->richiedente->matricola); 
        // rimuovo il nodo dello studente affinché possa effettuare nuove richieste di prestito

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