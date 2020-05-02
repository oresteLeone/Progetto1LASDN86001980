#ifndef projectlib
#define projectlib
#define maxlibri 15     //numero massimo libri 
#define maxstring 20


// Struttura nodi dell' ABR utilizzato per memorizzare gli studenti(matricola come chiave principale)
typedef struct nodoStudente {
    int matricola;
    char nomeStudente[maxstring];
    struct nodoStudente *sx;
    struct nodoStudente *dx;
} studente;

// Struttura nodi dell' ABR utilizzato per memorizzare i libri (nome come chiave principale)
typedef struct nodoLibro{
        // il nome del libro come chiave principale del nodo dell'albero
    char nomeLibro[maxstring];
        //puntatore allo studente che ha attualmente il libro (NULL se disponibile in biblioteca)
    studente *prestito;
        // puntatori al sottoalbero sinistro e destro     
    struct nodoLibro *sx;
    struct nodoLibro *dx;
} libro;

typedef struct richiesta_libro{
    char tipo[maxstring];
    studente *richiedente;
    libro *oggetto;
    struct richiesta_libro *next;
} richiesta;

typedef struct queue_richieste{
    richiesta *head;
    richiesta *tail;
} queue;


void addNodoStudente(studente **rad, int matr, char *nome );

// funzione di inserimento nodo nell'ABR libri
void addNodoLibro(libro **rad, char *nome );

// funzione inizializzazione ABR libri
void initializeABRLibro(libro **rad);

// funzione visita in preordine ABR Libri
void visitaInPreordineLibro(libro *rad);

// funzione ricerca libro con restituzione int
int ricercaLibro(libro *rad,char *nome);

// funzione ricerca studente con restituzione int
int ricercaStudente(studente *rad, int matr);

// funzione ricerca libro con restituzione puntatore
libro *referenceLibro(libro *rad,char *nome);

// funzione ricerca studente con restituzione puntatore
studente *referenceStudente(studente *rad, int matr);

// inizializzazione coda
void initializeQueue(queue *coda);

// creazione richiesta
richiesta *addNodoRichiesta(char *tipo, studente *matricola, libro *oggetto );

// funzione per l'impacchettamento e accodamento della richiesta
void catchRequest(studente **radStudente,libro **radLibro, queue *coda);

// funzione per l'accodamento della coda di richieste
void enQueue(queue *coda,richiesta *nodo);

// funzione gestione richieste
void tryRequest(queue *coda);
// funzione che rimuove una richiesta dalla coda
richiesta *deQueue(queue *coda);

// funzione per la stampa della coda
void printQueue(queue *coda);

int emptyQueue(queue *coda);

#endif