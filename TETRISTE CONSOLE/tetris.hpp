#ifndef TETRIS

#define TETRIS

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>
#include <time.h>
#include <map>
#include <typeinfo>
#include <string>
#include <stdbool.h>
#include <random>
#include <vector>
#include <new>

#include "classes.hpp" // Pour les classes


// Prototypes des fonctions externes

// UTILITAIRE POUR LE CONTROLE DE LA SORTIE DE LA CONSOLE WINDOWS

void textcolor(int color);
void getCurrentCursorPosition(int &x, int &y);
void hide_show_Cursor(int type);
void gotoxy(int x, int y);
void print_wcharstring(wchar_t *_string);

// FOR DECALAGE
const string shapes_name[] = {"Carrer", "Cercle", "Losange", "Triangle", "Retour", ""};
const string colors_name[] = {"Rouge", "jaune", "Vert", "Bleu", "Retour", ""};
wchar_t directions[][100] = {L"\u276F", L"\u276E"};
//int listlength(const string _list[]);
void print_list(const string _list[]);
void wipelines(int x, int y, int ymax);
int decalage_menu(FormList *l, int x, int y, int ymax);

// FOR SCORE MANAGEMENT
void add_to_scorefile(string playername, int sc);
void print_scores();
void best_action(FormList *l, FormList *next, vector<string> &bestpath, vector<int> &bestpathIndexes, int &highscore);

// FONCTION DE DEROULEMENT PRINCIPALES
int menu();
void rules();
void partie();
void tetris();

#endif // TETRIS
