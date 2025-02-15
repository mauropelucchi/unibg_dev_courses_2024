#include <iostream>
#include <cstring>

using namespace std;

struct VERBALE {
    char codice[16];
    char data_verbalizzazione[11]; // YYYY-MM-DD
    char data_appello[11]; // YYYY-MM-DD
    char data_superamento[11]; // YYYY-MM-DD
    char codice_insegnamento[11];
    char nome_docente[51];
    char matricola[8];
    int voto;
};

struct NODO {
	VERBALE dato;
	NODO *next;
};


int ins_testa(NODO * &head, VERBALE dato) {
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
}

int verifica_date(char data_appello[], char data_verbalizzazione[]) {
	int anno1, anno2, mese1, mese2; 
	anno1 = estrai_valore(data_appello, 0, 4);
	anno2 = estrai_valore(data_verbalizzazione, 0, 4);
	mese1 = estrai_valore(data_appello, 4, 2);
	mese2 = estrai_valore(data_verbalizzazione, 4, 2);
	if (anno1 == anno2 && mese1 == mese2)
		return 1;
	return 0;
}


int cerca_insegnamento(char codice_insegnamento[], char *insegnamenti[], int size) {
	for (int i = 0; i < size; i++) {
		if (strcmp(codice_insegnamento, insegnamenti[i]) == 0)
			return i;
	}
	return -1; // insegnamento non trovato
}

void CalcolaContatori(NODO * listaIn, char *insegnamenti[], int size, int contatori[]) {
	NODO *p;
	int i;
	int pos_ins;
	// inizializzazione dei contatori
	for (i = 0; i < size; i++)
		contatori[i] = 0;
	// Una sola scansione per calcolare i contatori
	p = listaIn;
	while (p != NULL) {
		pos_ins = cerca_insegnamento(p->dato.codice_insegnamento, insegnamenti, size);
		if (pos_ins >= 0) {
			if (verifica_date(p->dato.data_appello, p->dato.data_verbalizzazione))
				contatori[pos_ins]++;
		}
		p = p->next;
	}
}

int CalcolaMin(int contatori[], int size) {
	int min_pos = -1;
	int min;
	for (int i = 0; i < size; i++) { 
		if (contatori[i] != 0) {
			min = contatori[i];
			break;
		}
	}
	for (int i = 0; i < size; i++) {
		if (contatori[i] > 0) {
			if (contatori[i] < min) {
				min_pos = i;
				min = contatori[i];
			}
		}
	}
	return min_pos;
}

int verifica_date_successive(char data_appello[], char data_verbalizzazione[]) {
	int anno1, anno2, mese1, mese2; 
	anno1 = estrai_valore(data_appello, 0, 4);
	anno2 = estrai_valore(data_verbalizzazione, 0, 4);
	mese1 = estrai_valore(data_appello, 4, 2);
	mese2 = estrai_valore(data_verbalizzazione, 4, 2);
	if (anno1 == anno2 && mese2 > mese1)
		return 1;
	return 0;
}

NODO *CopiaVerbali(NODO * listaIn, char codice_insegnamento[]) {
	NODO *listaOut = NULL;
	NODO *p;
	p = listaIn;
	while (p != NULL) {
		if (strcmp(p->dato.codice, codice_insegnamento) == 0 &&
			verifica_date_successive(p->dato.data_appello,
						             p->dato.data_verbalizzazione)) {
			if (ins_testa(listaOut, p->dato) == 1)
				return NULL;
		}
		p = p->next;
	}
	return listaOut;
}


NODO* VerbaliMeseDiverso(NODO* listaIn, char *insegnamenti[], int size) {
	if (size < 1)
		return NULL;
	int contatori[size];
	CalcolaContatori(listaIn, insegnamenti, size, contatori);
	int min_pos = CalcolaMin(contatori, size);
	if (min_pos < 0)
		return NULL;
	NODO *listaOut = CopiaVerbali(listaIn, insegnamenti[min_pos]);
	return listaOut;
}