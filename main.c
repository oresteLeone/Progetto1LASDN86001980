#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

    printf("\n dovrei inizializzare i libri \n");

    int choice=0;
    printf("\n1. Aggiungere una richiesta ");
    printf("\n2. Gestire le richieste ");
    printf("\n3. Terminare ");
    printf("\n input: ");
    do{
        scanf("%d",&choice);
    }while(choice<0 && choice>4);
    printf("\n ho selezionato %d",choice);
    return 0; 
}
