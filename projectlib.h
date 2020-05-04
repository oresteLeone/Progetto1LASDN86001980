#ifndef projectlib
#define projectlib
#define maxlibri 15     //numero massimo libri 
#define maxstring 30    //lunghezza massima stringhe


// Struttura nodi dell' ABR utilizzato per memorizzare gli studenti(matricola come chiave principale)
typedef struct nodoStudente {
        // chiave primaria matricola come int
    int matricola;
        // stringa del nome studente
    char nomeStudente[maxstring];
        // puntatori al sottoalbero sinistro e destro
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

// Struttura nodi richieste
typedef struct richiesta_libro{
        // stringa contenente il tipo di richiesta (prestito/restituzione)
    char tipo[maxstring];
        // puntatori allo studente e al libro coinvolti
    studente *richiedente;
    libro *oggetto;
        // puntatore alla richiesta successiva nella coda
    struct richiesta_libro *next;
} richiesta;

// struttura coda che contiene le richieste
typedef struct queue_richieste{
    richiesta *head;
    richiesta *tail;
} queue;


// funzione per aggiungere un nodo studente all'ABR dei studenti
void addNodoStudente(studente **rad, int matr, char *nome );

// funzione di ricerca per trovare il minimo nodo di un albero
int ricercaMinABRStudente(studente *rad);

// funzione per eliminare un nodo con una certa matricola dall'ABR studenti 
void eliminaNodoABRStudente(studente **rad,int matr);

// funzione di inserimento nodo nell'ABR libri
void addNodoLibro(libro **rad, char *nome );

// funzione inizializzazione ABR libri
void initializeABRLibro(libro **rad);

// funzione visita in preordine ABR Libri
void visitaInPreordineLibro(libro *rad);

// funzione visita in preordine con output solo di libri in prestito
void visitaInPreordineLibroInPrestito(libro *rad);

// funzione che restituisce il numero di libri in prestito
int nPrestiti(libro *rad);

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
void tryRequest(queue *coda,studente **radStudente);

// funzione che rimuove una richiesta dalla coda
richiesta *deQueue(queue *coda);

// funzione per la stampa della coda
void printQueue(queue *coda, richiesta *request);

// funzione che restituisce se la coda è vuota
int emptyQueue(queue *coda);

// funzione che restituisce la lunghezza della coda
int lenghtQueue(queue *coda,richiesta *request);

#endif