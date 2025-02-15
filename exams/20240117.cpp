struct PRENOTAZIONE {
	char codice_prenotazione[18 + 1];
	char data_emissione[11]; //yyyy-mm-aa
	char data_inizio[11];
	int durata;
	char codice_albergo[11];
	int numero_camera;
	int categoria;
	float prezzo;
	int stato_prenotazione;
};
 
struct NODO {
	PRENOTAZIONE info;
	NODO *next;
};

#include <iostream>
#include <cstring>
#include <cstdlib>


int ins_testa(NODO *&head, PRENOTAZIONE info) {
	NODO *t = new NODO;
	if (t == NULL) {
		cout << "Errore allocazione";
		return 1;
	}
	t->info = info;
	t->next = head;
	head = t;
	return 0;
}

int cerca_albergo (char *alberghi[], int size, char albergo[]) {
	for (int i = 0; i < size; i++) {
		if (strcmp(albergo, alberghi[i]) == 0) {
			return i;
		}
	}
	return -1;
}

void calcolaPrenotazioni(NODO* listaIn, char dataSoggiorno[], char* alberghi[], int size, int contatori[]){
	  for(int i= 0; i<size; i++){
	    contatori[i] = 0;
	  }
	
	  NODO* t = listaIn;
	  while(t != NULL){
	    if(strcmp(t->dato.datainizio, dataSoggiorno)){
	      int pos = cercaAlbergo(alberghi, size, t->dato.codiceAlbergo);
	      if(pos >= 0){
	        contatori[pos]++;
	      }
	    }
	    t = t->next;
	  }
	}

int CalcolaMax(int contatori[], int size) {
	int max = 0;
	int max_pos = -1;
	for (int i = 0; i < size; i++) {
		if (contatori[i] > max) { // in caso di due massimi, prendo il primo
			max = contatori[i];
			max_pos = i;
		}
	}
	return max_pos;
}

NODO *CopiaPrenotazioni(NODO *listaIn, char albergo[], char dataSoggiorno[]) {
	NODO *listaOut = NULL;
	NODO *t = listaIn;
	while (t != NULL) {
		if ( (strcmp(t->info.codice_albergo, albero) == 0) &&
		     (strcmp(t->info.data_inizio, dataSoggiorno) == 0)) {
			int controllo = ins_testa(listaOut, t->info);
			if (controllo == 1) {
				return NULL;
			}
		}
		t = t->next;
	}
	return listaOut;
}


NODO *PrenotazioniAlbergoAffollato(NODO *listaIn, char data_soggiorno[],
				   char *alberghi[], int size) {
	if(listaIn == NULL) {
		return NULL;
	}
	if( size < 1) {
		return NULL;
	}
	int contatori[size];
	calcolaPrenotazioni(listaIn, data_soggiorno, alberghi, size, contatori);
	int posizioneMax = CalcolaMax(contatori, size);
	if (posizioneMax == -1) {
		return NULL;
	}
	NODO *listaOut= CopiaPrenotazioni(listaIn, alberghi[posizioneMax] , data_soggiorno);
	return listaOut;
}