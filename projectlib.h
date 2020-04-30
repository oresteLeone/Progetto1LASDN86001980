#ifndef projectlib
#define projectlib
#define maxlibri 15     //numero massimo libri 
#define maxrichieste 25 //numero massimo coda richieste 



// Struttura nodi dell' ABR utilizzato per memorizzare gli studenti(matricola come chiave principale)
typedef struct nodoStudente {
    int matricola;
    char *nomeStudente;
    struct nodoStudente *sx;
    struct nodoStudente *dx;
} studente;

// Struttura nodi dell' ABR utilizzato per memorizzare i libri (nome come chiave principale)
typedef struct nodoLibro{
        // il nome del libro come chiave principale del nodo dell'albero
    char *nomeLibro;
        //puntatore allo studente che ha attualmente il libro (NULL se disponibile in biblioteca)
    studente *prestito;
        // puntatori al sottoalbero sinistro e destro     
    struct nodoLibro *sx;
    struct nodoLibro *dx;
} libro;

typedef struct richiesta{
    char *tipo;
    studente *richiedente;
    libro *oggetto;
} richiesta;

richiesta Q[maxrichieste+2];

// funzione di inserimento nodo nell'ABR libri
void addNodoLibro(libro **rad, char *nome );

// funzione inizializzazione ABR libri
void initializeABRLibro(libro **rad);

// funzione visita in preordine ABR Libri
void visitaInPreordineLibro(libro **rad);

#endif