#include <ncurses.h>
#include <string>
#include <iostream>
using namespace std;

void gameOverMenu(int score){

        // IMPORTANTE!!! Bisogna mettere delwin(finestra) per cancellare la finestre prima di far apparire questa e non causare frammentazione

        int ymax, xmax;                         // Stores the screen dimension info

        getmaxyx(stdscr, ymax, xmax);           // ymax = height, xmax = width

        string gameOver = " Game over ";

        string yourScore = "Your score is " + to_string(score);

        string gameOverChoice = "Press p to play again or q to quit";

        //const int MENU_YSIZE = END_GAME_CHOICES;// Specify the height of endGameMenu to be number of choices


        attron(A_REVERSE);        //Mostra 'Gameover

        mvwprintw(stdscr,(ymax-3)/2-5,(xmax-gameOver.length())/2,gameOver.c_str());

        attroff(A_REVERSE);

                                  //Mostra punteggio

        mvwprintw(stdscr,(ymax-3)/2-2,(xmax-yourScore.length())/2,yourScore.c_str());

                                 //Da qui parte il check per vedere se ha fatto il punteggio più alto
/*
        int highScore = readHistoryFile();

        if (highScore < score){    //Nuovo punteggio più alto
                string newHighScore = "CONGRATULATIONS, YOU'VE GOT A NEW HIGH SCORE!";
                attron(A_BLINK);
                mvwprintw(stdscr,(ymax-3)/2-3,(xmax-newHighScore.length())/2,newHighScore.c_str());
                attroff(A_BLINK);
        }
*/
        refresh();                              // Refresh the standard screen such that the changes are applied

        char choice;
        mvwprintw(stdscr,(ymax-3)/2-3,(xmax-gameOverChoice.length())/2,gameOverChoice.c_str());  //da aggiustare la posizione
}
         /*
        bool notifyWriteFailed = !writeToHistoryTextFile(getCurrentDateTime(), score);

        cin>>choice;

        switch(choice)
        {
                case 'p':
                        clear();
                        gameInit();
                        break;

                case 'q':
                        endwin();
                        cout << "Had a great time with you. See you ! =w=" << endl;
                        if (notifyWriteFailed)
                        {
                                cout << "We could not write the score history file." << endl;
                        }
                        exit(0);
                        break;
        }
}
*/
