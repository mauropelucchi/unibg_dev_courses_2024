/*
Soluzione appello del 02/07/2024
*/
#include <iostream>
#include <cstring>
using namespace std;

struct PRENOTAZIONE
{
	char codice[18 + 1];
	char data_emissione[10 + 1];
	char data_inizio[10 + 1];
	char data_fine[10 + 1];
	char albergo[10 + 1];
	int camera;
	int categoria_camera;
	float prezzo;
	int stato;
};

struct NODO {
	PRENOTAZIONE dato;
	NODO *next;
};


int ins_testa(NODO * &head, PRENOTAZIONE dato) {
	NODO *t;
	t = new NODO;
	if (t == NULL) {
		cout << "Errore Allocazione";
		return 1;
	}
	t->dato = dato;
	t->next = head;
	head = t;
	return 0;
}

int estrai_valore(char data[], int ini, int len) {
	char buffer[len + 1];
	int i;
	for (i = 0; i < len; i++)
		buffer[i] = data[ini + i];
	buffer[i] = '\0';
	return atoi(buffer);


int verifica_date(char inizio[], char fine[]) {
	int anno1, anno2, mese1, mese2; 
	anno1 = estrai_valore(inizio, 0, 4);
	anno2 = estrai_valore(fine, 0, 4);
	mese1 = estrai_valore(inizio, 4, 2);
	mese2 = estrai_valore(fine, 4, 2);
	if (anno1 == anno2 && mese1 + 1 == mese2)
		return 1;
	return 0;
}


int cerca_albergo(char albergo[], char *alberghi[], int size) {
	for (int i = 0; i < size; i++) {
		if (strcmp(albergo, alberghi[i]) == 0)
			return i;
	}
	return -1; // albergo non trovato
}

void CalcolaContatori(NODO * listaIn, char *alberghi[], int size, int contatori[]) {
	NODO *p;
	int i;
	int pos_albergo;
	// inizializzazione dei contatori
	for (i = 0; i < size; i++)
		contatori[i] = 0;
	// Una sola scansione per calcolare i contatori
	p = listaIn;
	while (p != NULL) {
		pos_albergo = cerca_albergo(p->dato.albergo,
									alberghi, size);
		if (pos_albergo >= 0) {
			if (verifica_date(p->dato.data_inizio, p->dato.data_fine))
				contatori[pos_albergo]++;
		}
		p = p->next;
	}
}

int CalcolaMax(int contatori[], int size) {
	int max_pos = -1;
	int max = -1;
	for (int i = 0; i < size; i++) {
		if (contatori[i] > 0) {
			if (contatori[i] > max) {
				max_pos = i;
				max = contatori[i];
			}
		}
	}
	return max_pos;
}

NODO *CopiaPrenotazioni(NODO * listaIn, char albergo[]) {
	NODO *listaOut = NULL;
	NODO *p;
	p = listaIn;
	while (p != NULL) {
		if (strcmp(p->dato.albergo, albergo) == 0 &&
			verifica_date(p->dato.data_inizio,
						  p->dato.data_fine)) {
			if (ins_testa(listaOut, p->dato))
				return NULL;
		}
		p = p->next;
	}
	return listaOut;
}

NODO *PrenotazioniAlbergoMaxDueMesi(NODO * listaIn, char *alberghi[], int size)  {
	if (size < 1)
		return NULL;
	int contatori[size];
	CalcolaContatori(listaIn, alberghi, size, contatori);
	int max_pos = CalcolaMax(contatori, size);
	if (max_pos < 0)
		return NULL;
	NODO *listaOut = CopiaPrenotazioni(listaIn, alberghi[max_pos]);
	return listaOut;
}