#ifndef INMAIN
#define INMAIN
#include "tetris.hpp"
#endif
#include "texts.hpp"
#include "scores.hpp" // pour la gestion des scores

// Changing texts output color
void textcolor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Getting cursor current position.
void getCurrentCursorPosition(int &x, int &y)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    x = csbi.dwCursorPosition.X;
    y = csbi.dwCursorPosition.Y;
}

// Hiding or showing console output cursor.
void hide_show_Cursor(int type)
{
    /// pour cacher le curseur
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    switch (type)
    {
    case 1:
        info.bVisible = FALSE;
        break;
    case 2:
        info.bVisible = TRUE;
        break;
    }
    SetConsoleCursorInfo(consoleHandle, &info);
    // For hiding or showing cursor
}

//For moving the cursor at position x y.
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// For printing wchar_t (unicode characters) in console output.
void print_wcharstring(wchar_t *_string)
{
    int len = wcslen(_string);
    UINT originalCodePage = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleW(hConsoleOutput, _string, len, NULL, NULL);
    // Set the console output code page back to the original value
    SetConsoleOutputCP(originalCodePage);
}

// For Home menu
int menu()
{
    int i = 0;
    int cursor_x, cursor_y;
    int set[] = {2, 7, 7, 7};
    int counter = 1;
    char key;

    print_wcharstring(tet);
    cout << endl
         << endl;

    getCurrentCursorPosition(cursor_x, cursor_y);

    hide_show_Cursor(1);

    // Stopping old playin musics
    PlaySound(NULL, NULL, SND_ASYNC);

    for (i = 0;;)
    {
        if (_kbhit())
        {
            PlaySound(TEXT("sounds/btnSelect.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }

        gotoxy(cursor_x + 27, cursor_y);
        textcolor(set[0]);
        cout << "1. Jouer";

        gotoxy(cursor_x + 27, cursor_y + 1);
        textcolor(set[1]);
        cout << "2. Scores";

        gotoxy(cursor_x + 27, cursor_y + 2);
        textcolor(set[2]);
        cout << "3. Regles";

        gotoxy(cursor_x + 27, cursor_y + 3);
        textcolor(set[3]);
        cout << "4. Quitter";
        textcolor(7);

        key = _getch();

        switch (key)
            {
            case 49:
                return 1;
                break;
            case 50:
                return 2;
                break;
            case 51:
                return 3;
                break;
            case 52:
                return 4;
                break;
            }

        if (key == 72 && (counter >= 2 && counter <= 4)) // up buton
        {
            counter--;
        }

        if (key == 80 && (counter >= 1 && counter <= 3)) // down buton
        {
            counter++;
        }
        if (key == '\r') // enter bunton
        {
            PlaySound(TEXT("sounds/btnSelect.wav"), NULL, SND_FILENAME | SND_ASYNC);
            switch (counter)
            {
            case 1:
                return 1;
                break;
            case 2:
                return 2;
                break;
            case 3:
                return 3;
                break;
            case 4:
                return 4;
                break;
            }
        }
        set[0] = 7;
        set[1] = 7;
        set[2] = 7;
        set[3] = 7;
        if (counter == 1)
        {
            set[0] = 2;
        }
        if (counter == 2)
        {
            set[1] = 2;
        }
        if (counter == 3)
        {
            set[2] = 2;
        }
        if (counter == 4)
        {
            set[3] = 2;
        }
    }

    hide_show_Cursor(2);

    return i;
}

// For rules SECTION
void rules()
{
    print_wcharstring(rule);
    cout << endl
         << endl;
    wchar_t sentence[] = L"Vous disposez de 4 formes carre(■), losange(♦), cercle(●) et triangle(▲).";
    print_wcharstring(sentence);
    cout << endl
         << "Ces formes varieront suivant 4 couleurs";
    textcolor(4);
    cout << " rouge";
    textcolor(7);
    cout << ", ";
    textcolor(6);
    cout << " jaune";
    textcolor(7);
    cout << ", ";
    textcolor(2);
    cout << " vert";
    textcolor(7);
    cout << ", et";
    textcolor(1);
    cout << " bleu";
    textcolor(7);
    cout << "." << endl;
    cout << "Lorsque vous aligner trois formes de memes types ou trois elements de memes couleur vous gagner 10 pts." << endl
         << "Lorsque le plateau atteint 15 elements vous perdez la parties" << endl;
    cout << endl << "Appuyer n'importe quel boutton pour retourner au Menu";
    hide_show_Cursor(2);
    getch();
    hide_show_Cursor(1);
}

// For Decalage management

int listlength(const string _list[])
{
    int i = 0;
    while (!_list[i].empty())
        ++i;
    return i;
}

void print_list(const string _list[])
{
    int length = listlength(_list);
    for (int i = 0; i < length; i++)
        cout << (i + 1) << ". " << _list[i] << "    ";
}

void wipelines(int x, int y, int ymax)
{
    // VIDER L'ECRAN
    while (y <= ymax)
    {
        gotoxy(x, y);
        cout << "\033[2K"; // Efface la ligne courante
        y++;
    }
}

int decalage_menu(FormList *l, int x, int y, int ymax)
{
    int i = 0, j = 0, first = 1, length, select1_x, select1_y, start_x, start_y;
    int actionIndex = 1;
    char k;
    Node *node;
    gotoxy(x, y);
    cout << "------------------ Decalage Menu ---------------------------" << endl;
    cout << "1. Decalage Forme     2. Decalage Couleur    3. Quitter" << endl
         << endl
         << endl;
    hide_show_Cursor(1);
    getCurrentCursorPosition(start_x, start_y);

start:

    do
    {
        k = _getch();
        i = (int)k - 48;
    } while (i <= 0 || i > 3);
    switch (i)
    {
    case 1:

        actionIndex += 4;
        if (!first)
            gotoxy(select1_x, select1_y - 2);
        length = listlength(shapes_name);
        cout << "------ Decalage Forme -------" << endl;
        print_list(shapes_name);
        cout << endl;
        if (first)
        {
            getCurrentCursorPosition(select1_x, select1_y);
            first = 0;
        }
        do
        {
            k = _getch();
            j = (int)k - 48;
        } while (j <= 0 || j > length);
        actionIndex += j;
        if (j == length)
        {
            wipelines(start_x, start_y, select1_y);
            goto start;
        }
        node = l->HeadShapes[shapesList[j - 1]];
        // cout << "Appuyer sur une des touches directionnels pour faire le decalage: ";
        // print_wcharstring(directions[0]); cout << " ou "; print_wcharstring(directions[1]);
        // do
        // {
        //     k = getch();
        // } while (k != 75 && k != 77);

        // setting action index

        k = 75;

        switch (k)
        {
        case 75: // Flèche vers la gauche
            l->DecalageShapeToLeft(node);
            break;
        case 77: // Flèche vers la droite
            l->DecalageShapeToRight(node);
            break;
        }

        break;
    case 2:
        if (!first)
            gotoxy(select1_x, select1_y - 2);
        length = listlength(colors_name);
        cout << "------ Decalage Couleur -------" << endl;
        print_list(colors_name);
        cout << endl;
        if (first)
        {
            getCurrentCursorPosition(select1_x, select1_y);
            first = 0;
        }
        do
        {
            k = _getch();
            j = (int)k - 48;
        } while (j <= 0 || j > length);
        actionIndex += j;
        if (j == length)
        {
            wipelines(start_x, start_y, select1_y);
            goto start;
        }
        node = l->HeadColors[colorsList[j - 1]];
        // cout << "Appuyer sur une des touches directionnels pour faire le decalage: ";
        // print_wcharstring(directions[0]); cout << " ou "; print_wcharstring(directions[1]);
        // do
        // {
        //     k = getch();
        // } while (k != 75 && k != 77);

        // setting action index

        k = 75;

        switch (k)
        {
        case 75: // Flèche vers la gauche
            l->DecalageColorToLeft(node);
            break;
        case 77: // Flèche vers la droite
            l->DecalageColorToRight(node);
            break;
        }

        break;
    }

    // VIDAGE DE L'ECRAN
    wipelines(x, y, ymax);

    return actionIndex;
}

// For score management

void add_to_scorefile(string playername, int sc)
{
    Score manager("scores.json");
    manager.addScore(playername, sc);
}

void print_scores()
{
    int pos_x, pos_y, xmax, ymax;
    char k;
    Score manager("scores.json");
    cout << "Appuyer les fleches bas et haut pour voir plus ou moins de scores et tout autre bouton pour retourner au Menu" << endl
         << endl;
    getCurrentCursorPosition(pos_x, pos_y);
    manager.show10Scores();
    int stay = 1; // Set to 1 by default
    bool conInputscore = false, wipe = false;
    do
    {
        if (_kbhit())
        {
            k = _getch();
            if(k == -32) k = _getch();
            conInputscore = true;
        }
        if (conInputscore)
        {

            if (k == 72) // up arrow
            {
                if(wipe) wipelines(pos_x, pos_y, ymax);
                gotoxy(pos_x, pos_y);
                manager.show10Scores();
                wipe = false;
            }
            else if (k == 80) // down arrow
            {
                gotoxy(pos_x, pos_y);
                manager.showScores();
                cout << "Appuyer les fleches bas et haut pour voir plus ou moins de scores et tout autre bouton pour retourner au Menu. ";
                getCurrentCursorPosition(xmax, ymax);
                wipe = true;
            }
            else
            {
                stay = 0; // Set to 0 if any other key is pressed
            }
            conInputscore = false;
        }
    } while (stay);
}

void best_action(FormList *l, FormList *next, vector<string> &bestpath, vector<int> &bestpathIndexes, int &highscore)
{
    Tree *AiTree = new Tree{l, next, 5};
    bestpath = AiTree->GetBestPath(highscore);
    bestpathIndexes = AiTree->GetBestPathIndexs();
    delete AiTree;
}

void partie()
{
    char i;
    int en_cours = 1, k, highscore = 0;
    int cur_size, old_size, score;
    int size_pos_x, size_pos_y;
    int list_pos_x, list_pos_y;
    int ai_x, ai_y, ai_ymax, ai_cpt = 0, ai_cptmax = 3, cur_index = -1, j;
    bool showAi = false, wipeAi = false, fromAI = false;
    vector<string> bestpath;
    vector<int> bestIndexes;
    FormList *l = new FormList;
    FormList *nextElements = new FormList;
    string playername;

    cout << "Veuillez saisir votre nom d'utilisateur: ";
    getline(cin, playername);
    system("cls");
    print_wcharstring(goodluck);

    // Music de fond
    PlaySound(TEXT("sounds/background_music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    while (l->getSize() < 5)
    {
        if (l->isEmpty())
            l->InsertRandomForms(5);
        else
            l->InsertRandomForms(5 - l->getSize());
        l->DeleteSimilarElementsGetNumberOfDeletedElements();
    }
    nextElements->InsertRandomForms(5);
    cout << endl
         << endl;
    getCurrentCursorPosition(size_pos_x, size_pos_y);
    list_pos_x = size_pos_x + 16;
    list_pos_y = size_pos_y + 13;
    ai_x = 0;
    ai_y = list_pos_y + 2;
    ai_ymax = ai_y + 4;
    hide_show_Cursor(1);
    gotoxy(list_pos_x, list_pos_y);
    l->toString();
    cur_size = old_size = l->getSize();
    while (en_cours && cur_size <= 15)
    {
        gotoxy(size_pos_x, size_pos_y);
        l->print_size_score();
        cout << endl;
        cout << "Prochain blocks: ";
        nextElements->toString();
        cout << endl;
        // Form *maform = nextElements->DeleteAndGetLastForm();
        // Node *node = new Node();
        // node->item = (void *)maform;
        // if (!node)
        // {
        //     cout << "Erreur d'allocation" << endl;
        //     exit(1);
        // }

        cout << endl << " 1. Insertion Gauche   2. Insertion Droite   3. Decalage   A. IA   Q. Quitter" << endl;
        do
        {
            i = getch();
            switch (i)
            {
            case 49:
                l->InsertFormFirst(nextElements->DeleteAndGetLastForm());
                cur_index = 0;
                break;
            case 50:
                l->InsertFormLast(nextElements->DeleteAndGetLastForm());
                cur_index = 1;
                break;
            case 51: // decalage
                // gotoxy(0, list_pos_y);
                // cout << "\033[2K"; // Efface la ligne courante
                // gotoxy(list_pos_x, (list_pos_y + 5));
                // l->toString();
                // nextElements->InsertFirst(node);
                cur_index = decalage_menu(l, 0, size_pos_y + 5, (list_pos_y));
                break;
            case 'a':
                if (!showAi && ai_cpt < ai_cptmax)
                {
                    best_action(l, nextElements, bestpath, bestIndexes, highscore);
                    showAi = true;
                    ai_cpt++;
                    j = 0;
                    cur_index = -1;
                }
                else
                {
                    gotoxy(ai_x, ai_y);
                    cout << "AH AH AH je t'ai assez aider." << endl;
                    //wipelines(ai_x, ai_y, ai_ymax);
                }
                break;
            case 'A':
                if (!showAi && ai_cpt < ai_cptmax)
                {
                    best_action(l, nextElements, bestpath, bestIndexes, highscore);
                    showAi = true;
                    ai_cpt++;
                    j = 0;
                    cur_index = -1;
                }
                else
                {
                    gotoxy(ai_x, ai_y);
                    cout << "AH AH AH je t'ai assez aider." << endl;
                    fromAI = true;
                    //wipelines(ai_x, ai_y, ai_ymax);
                }
                break;
            case 83: // PAUSE pour s
                break;
            case 115: // PAUSE pour S
                break;
            case 81: // QUITTER pour Q
                en_cours = 0;
                break;
            case 113: // QUITTER pour q
                en_cours = 0;
                break;
            case 0: // ENTRER
                break;
            default:
                i = '#';
            }
        } while (i == '#');

        // ai section in execution
        if (showAi)
        {
            gotoxy(ai_x, ai_y);
            cout << "Si tu suis mes instructions tu marqueras " << ((5 * highscore) - 5) << " points" << endl;
            // wchar_t head2[] = L"\u1F600";
            // print_wcharstring(head2);
            if (cur_index != -1 && j < bestpath.size() && cur_index != bestIndexes[j - 1])
            {
                wipelines(ai_x, ai_y, ai_ymax);
                gotoxy(ai_x, ai_y);
                cout << "Oh vous voulez continuer seul ?" << endl
                    << "Bonne chance" << endl;
                getch();
                score = l->DeleteSimilarElementsGetNumberOfDeletedElements();
                if(score > 0) {
                    l->setScore(l->getScore() + (5*score - 5));
                    cout << "Au moins vous avez marquer : " << (5*score - 5) << "points" << endl;
                }
                showAi = false;
                wipeAi = true;
            }
            if (j < bestpath.size())
            {
                cout << "\033[2K"; // Efface la ligne courante
                cout << " Le prochain meilleur cout est: ";
                cout << bestpath[j] << endl;
                j++;
            }
            else
            {
                wipelines(ai_x, ai_y, ai_ymax);
                gotoxy(ai_x, ai_y);
                score = l->DeleteSimilarElementsGetNumberOfDeletedElements();
                if(score > 0) l->setScore(l->getScore() + (5*score - 5));
                cout << "Bravo tu viens de marquer " << ((5 * highscore) - 5) << " points" << endl;
                gotoxy(size_pos_x, size_pos_y);
                cout << "\033[2K"; // Efface la ligne courante
                l->print_size_score();
                gotoxy(list_pos_x, list_pos_y);
                cout << "\033[2K"; // Efface la ligne courante
                l->toString();
                getch();
                showAi = false;
                wipeAi = true;
            }
        }

        if (wipeAi)
        {
            gotoxy(ai_x, ai_y);
            wipelines(ai_x, ai_y, ai_ymax);
            wipeAi = false;
        }

        if(!showAi){
            score = l->DeleteSimilarElementsGetNumberOfDeletedElements();
            if(score > 0) {
                l->setScore(l->getScore() + (5*score - 5));
            }
        }
        old_size = cur_size;
        cur_size = l->getSize();
        k = cur_size - old_size;
        gotoxy(list_pos_x , list_pos_y);
        if(k < 0 || old_size == 0)
            cout << "\033[2K"; // Efface la ligne courante
        l->toString();
        if(!showAi)
        {
            if(score > 0)
            {
                cout << endl << endl;
                cout << "\033[2K";
                cout << "vous avez marquer : " << (5*score - 5) << "points" << endl;
                fromAI = false;
            }
            else
            {
                cout << endl << endl;
                if(!fromAI) cout << "\033[2K";
            }
        }
    }

    // after parti section
    PlaySound(TEXT("sounds/overP.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    hide_show_Cursor(2);
    system("cls");
    l->print_size_score();
    cout << endl;
    print_wcharstring(over);
    cout << endl
         << endl;

    // score saving section;
    add_to_scorefile(playername, l->getScore());

    // END
    cout << "Appuyer n'importe quel boutton pour continuer...";

    getch();
}

// Application function that calls the main subfunctions
void tetris()
{
    int i = 0, goback_menu = 1;
    while (i < 4)
    {
        if (goback_menu)
        {
            system("cls");
            i = menu();
            goback_menu = 0;
        }
        system("cls");
        switch (i)
        {
        case 1:
            partie();
            goback_menu = 1;
            break;
        case 2:
            print_wcharstring(scores);
            cout << endl
                 << endl;
            print_scores();
            goback_menu = 1;
            break;
        case 3:
            rules();
            goback_menu = 1;
            break;
        case 4:
            print_wcharstring(bye);
            cout << endl;
            break;
        }
    }
}
