# Tetris-PSL
Progetto per l'esame di Programmazione del corso di laurea in Informatica, eseguito da Leonardo Signorini, Francesco Passarella e Filippo Luppi

# Descrizione
Tetris-PSL è un classico Tetris.
Il gioco è basato sulla caduta dall'alto di blocchi di diverse forme, detti tetramini, che si depositano e impilano l'uno sull'altro in uno spazio rettangolare. 
Lo scopo del gioco è cercare di formare delle righe composte interamente da singoli blocchi per far si che tali righe si cancellino, la finestra si svuoti e si facciano punti.
I tetramini possono essere mossi a destra o sinistra con le frecce e fatti roteare con la BARRA SPAZIATRICE.
Il gioco ha un punteggio e un timer che indica il tempo passato dall'inizio della partita e da punti extra.
Completando righe si ottengono punti (più punti nel caso di più righe) e si aumenta la difficoltà, che aumenta la velocità di discesa dei tetramini.
La sconfitta avviene quando non è più possibile far scendere altri blocchi e impilarli fra di loro.
All'inizio si visualizza un menù principale dal quale premendo INVIO si può fare una partita, visualizzare una classifica dei punteggi o uscire.
La classifica elenca tutti i punteggi delle partite fatte, elencate in ordine decrescente.
A fine partita viene elencato il punteggio fatto e si ha la possibilità di tornare al menù principale, di uscire o di fare un'altra partita.

# Librerie
Le librerie utilizzate sono quelle elencate nelle richieste o viste a lezione, quindi curses.h, fstream, chrono e cstdlib.

