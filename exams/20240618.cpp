/*
Soluzione appello del 18/06/2024
*/
#include <iostream>
#include <cstring>
using namespace std;

int get_giorni(char data_inizio[], char data_fine[]) {
	return 0;
}

struct PRENOTAZIONE {
	char codice [18+1];
	char data_emissione [10+1];
	char data_inizio [10+1];
	char data_fine [10+1];
	char albergo [10+1];
	int camera;
	int categoria_camera;
	float prezzo;
	int stato;
};

struct NODO {
	PRENOTAZIONE dato;
	NODO *next;
};


int ins_testa( NODO *&head, PRENOTAZIONE dato ) {
	NODO *t;
	t = new NODO;
	if( t == NULL )
	{
	cout << "Errore Allocazione";
	return 1;
	}
	t->dato = dato;
	t->next = head;
	head = t;
	return 0;
}

int cerca_albergo(char albergo[], char *alberghi[], int size) {
	for(int i=0; i < size; i++) {
		if( strcmp(albergo, alberghi[i])==0 )
			return i;
		}
	return -1; // albergo non trovato
}

// con una sola scansione, calcola i contatori e i sommatori
void Calcola(NODO *listaIn,char *alberghi[], int size, int contatori[], int sommatori[], char dataInizio[]) {
	NODO *p;
	int i;
	int pos_albergo;
	//inizializzazione dei contatori
	for(i=0; i < size; i++) {
		contatori[i]=0;
		sommatori[i]=0;
	}
	// Una sola scansione per calcolare
	// i contatori e i sommatori
	p = listaIn;
	while(p != NULL) {
		pos_albergo = cerca_albergo(p->dato.albergo, alberghi, size);
		if( pos_albergo >= 0) {
			if( strcmp(p->dato.data_inizio, dataInizio)==0 ) {
				contatori[pos_albergo]++;
				sommatori[pos_albergo] +=
				get_giorni(p->dato.data_inizio, p->dato.data_fine);
			}
		}
		p = p->next;
	}
}

int CalcolaMax(int contatori[], int sommatori[], int size) {
	int max_pos=-1;
	float max = -1;
	float media;
	for(int i=0; i < size; i++) {
		if( contatori[i] > 0 ) {
			media = sommatori[i] / (float)contatori[i];
			if(media > max) {
				max_pos = i;
				max = media;
			}
		}
	}
	return max_pos;
}

NODO *CopiaPrenotazioni(NODO *listaIn, char albergo[], char dataInizio[]) {
	NODO *listaOut = NULL;
	NODO *p;
	p = listaIn;
	while(p != NULL) {
		if( strcmp(p->dato.albergo, albergo)==0 && strcmp(p->dato.data_inizio, dataInizio)==0 ) {
			if( ins_testa(listaOut, p->dato))
				return NULL;
		}
		p = p->next;
	}
	return listaOut;
}

NODO *PrenotazioniAlbergoMaxDurataMedia(NODO *listaIn, char dataInizio[],char *alberghi[], int size) {
	if(size < 1)
		return NULL;
	int contatori[size];
	int sommatori[size];
	Calcola(listaIn, alberghi, size, contatori, sommatori, dataInizio);
	int max_pos = CalcolaMax(contatori, sommatori, size);
	if( max_pos < 0)
		return NULL;
	NODO *listaOut = CopiaPrenotazioni(listaIn, alberghi[max_pos], dataInizio);
	return listaOut;
}