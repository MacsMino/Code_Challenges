/* connect 4 semplice per due giocatori */

#include <stdio.h>
#define L 6 //numero di righe e colonne
#define C 4 //numero di tasselli richiesti per vittoria

void printboard(int board[L][L]) {
		int i, j;
		printf("\n\n");
		for(i = 0; i < L; i++) {
				for(j = 0; j < L; j++) {
						if(board[j][L-1-i] == 0)
								printf(" R ");
						if(board[j][L-1-i] == 1)
								printf(" Y ");
						if(board[j][L-1-i] == 2)
								printf(" _ ");
				}
				printf("\n");
		}
}

int controllavittoria(int board[L][L], int **turno, int colonna, int riga) { //UN MODO MOLTO STUPIDO DI CONTROLLARE LE CONDIZIONI DI VITTORIA
		int i, consecutivi = 0;
		//controllo orizzontale
		for(i = 0; i < L && consecutivi != C; i++) {
				if(board[i][riga] == **turno)
						consecutivi++;
				if(board[i][riga] != **turno)
						consecutivi = 0;
		}
		if(consecutivi == C)
				return 1;
		consecutivi = 0;

		//controllo verticale
		for(i = 0; i < L && consecutivi != C; i++) {
				if(board[colonna][i] == **turno)
						consecutivi++;
				if(board[colonna][i] != **turno)
						consecutivi = 0;
		}
		if(consecutivi == C)
				return 1;

		consecutivi = 0;
		//controllo obliquo basso -> alto, sinistra->destra
		if(colonna >= riga) {
				for(i = 0; i+colonna-riga < L && consecutivi != C; i++) {
						if(board[i+colonna-riga][i] == **turno)
								consecutivi++;
						if(board[i+colonna-riga][i] != **turno)
								consecutivi = 0;
				}
		}
		else if(riga > colonna) {
				for(i = 0; i+riga-colonna < L && consecutivi != C; i++) {
						if(board[i][i+riga-colonna] == **turno)
								consecutivi++;
						if(board[i][i+riga-colonna] != **turno)
								consecutivi = 0;
				}
		}
		if(consecutivi == C)
				return 1;

		//controllo obliquo alto -> basso, sinistra->destra
		if(colonna+riga > L) {
				for(i = 0; i+colonna-L+riga < L && consecutivi != C; i++) {
						if(board[i+colonna-L+riga][L-1-i] == **turno)
								consecutivi++;
						if(board[i+colonna-L+riga][L-1-i] != **turno)
								consecutivi = 0;
				}
		}
		else if(colonna+riga <= L) {
				for(i = 0; i+colonna-L+riga < L && consecutivi != C; i++) {
						if(board[i][colonna+riga-i] == **turno)
								consecutivi++;
						if(board[i][colonna+riga-i] != **turno)
								consecutivi = 0;
				}
		}
		if(consecutivi == C)
				return 1;


		return 0;
}

void mossa(int board[L][L], int *turno, int *vincitore) {
		int c, i = 0; //colonna selezionata, spazio
		printboard(board);
		if(*turno == 0)
				printf("\nturno del rosso, scrivi il numero della colonna dove inserire il tassello\n");
		if(*turno == 1)
				printf("\nturno del giallo, scrivi il numero della colonna dove inserire il tassello\n");

		// IL CONTROLLO DELLA COLONNA DEVE ESSERE PIU RIGOROSO, IMPLEMENTARE UN CONTROLLO SE LA CIMA NON SIA RAGGIUNTA
		do {
				printf("inserisci un numero fra 1 e %d\n", L);
				scanf("%d", &c);
		} while(c < 1 || c > L); //controllo se il giocatore inserisce una colonna valida
		c--; //la rendo agibile nell'array
		while(board[c][i] != 2)
				i++;
		board[c][i] = *turno; //modo per mettere una R o una Y sulla casella corrispondente
		*vincitore = controllavittoria(board, &turno, c,  i);
		if(*vincitore == 0) {
				*turno = (*turno) + 1; //cambio turno
				*turno = (*turno) % 2;
		}
}

int main() {

		int board[L][L]; //utilizzo questa matrice come campo da gioco
		int i, j, turno = 0, vincitore = 0; //turno = 0 -> rosso, turno = 1 -> giallo
		for(i = 0; i < L; i++)  //pulisci la board
				for(j = 0; j < L; j++)
						board[i][j] = 2;
		while(vincitore == 0)
			mossa(board, &turno, &vincitore);
		printboard(board);
		if(turno == 0)
				printf("\n Vince il rosso! Complimenti!\n");
		if(turno == 1)
				printf("\n Vince il giallo! Complimenti!\n");
		return 0;
}

