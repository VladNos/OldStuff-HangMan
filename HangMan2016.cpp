#include <iostream>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

ifstream finc("cuvinte.in");
ifstream finh("hints.in");

string a[1000];
string b[1000];

int suc[27],fai[27];
int n = -1, cuv, life, fail, succ, win;
int score, level, max_multi, show_hint, subtract_score;
int min_score = 100;
float multi;

int lit[26];

void ft_start_game();

void ft_read()
{
    int m = -1;
    while(getline(finc,a[++n]));
    while(getline(finh,b[++m]));
}

void ft_clean(){
    life = 0;
    fail = 0;
    succ = 0;
    win = 0;
    for(int i = 0; i < 27; i++){
        fai[i] = 0;
        suc[i] = 0;
    }
}

void ft_generate_word()
{
    srand (time(NULL));
    cuv = rand() % n;
    for(int i = 0; i < 26;i++)
        lit[i] = 0;
}

void ft_row()
{
    for(int i = 1; i <= 80; i++)
        cout << '-';
}

void ft_generate_hangman1()
{
    int stage = life;
    ft_row();
    cout << "  _______\n";
    cout << "  |     |\n";
    cout << "  |     ";
    if (stage >= 1) cout << "O\n";
        else cout << '\n';
    cout << "  |    ";
        if(stage >= 4) cout << "/H\\\n";
            else if (stage >= 3) cout << "/H\n";
                else if (stage >= 2) cout << " H\n";
                    else cout << '\n';
    cout << "  |     ";
        if(stage >= 2) cout << "H\n";
                else cout << "\n";
    cout << "  |     ";min_score = 100;
        if(stage >=5) cout << "|\n";
            else cout << '\n';
    cout << "  |\n";
    cout << "__M__\n";
    cout << '\n';
    ft_row();
}

void ft_score(){
    cout << "SCORE: " << score<< " ||  LEVEL: " << level;
    cout << "\npress '/' to ask for hints(- "<< min_score << " score)\n\n";
}

void ft_game_over_screen()
{
    level = 1;
    multi = 1;
    system("cls");
    char x;
    ft_row();
    cout << "\n\n";
    //            G      A         M      E      O     V     E     R
    cout << "   I===   A   I   I I===    I===I \\   / I=== I==I\n";
    cout << "   I =I  /_\\  I\\ /I I===    I   I  \\ /  I=== I==I\n";
    cout << "   I==I /   \\ I V I I===    I===I   V   I=== I \\";
    cout << "\n\n";
    ft_row();
    cout << "The expresion was : " << a[cuv] << "   FINAL SCORE: " << score << '\n';
    score = 0;
    min_score = 100;
    multi = 1;
    cout << "\n\nDo you want to play again?  Y/N";
    cin >> x;
    if(x == 'Y' || x == 'y')ft_start_game();
}

void ft_win_screen()
{
    score += 75 * (level) * 1.25;
    level++;
    max_multi += level;
    system("cls");
    char x;
    ft_row();
    // G G;
    cout << "\n\n";
    cout << "     I====     I====\n";
    cout << "     I         I    \n";
    cout << "     I  =I     I  =I\n";
    cout << "     I===I     I===I\n";
    cout << "\n\n";
    ft_row();
    min_score += 200 * (level - 1);
    cout << "\nPassed level " << level - 1 <<" with SCORE : " << score;
    cout << "\n\nDo you want to keep playing?  Y/N";
    cin >> x;
    if(x == 'Y' || x == 'y')ft_start_game();
}

void ft_start_screen(){
    ft_row();
    // H A N G M A N
    cout << "                                                     _______             \n";
    cout << "|   |    /\\    |\\   | |===|                          |     |             \n";
    cout << "|___|   /__\\   | \\  | |                              |     |       \n";
    cout << "|   |  /    \\  |  \\ | | ¯¯|                          |            \n";
    cout << "|   | /      \\ |   \\| |===|                          |             \n";
    cout << "                                                     |                \n";
    cout << "                    |\\  /|    /\\    |\\   |           |             \n";
    cout << "                    | \\/ |   /__\\   | \\  |           |             \n";
    cout << "                    |    |  /    \\  |  \\ |           |              \n";
    cout << "                    |    | /      \\ |   \\|        ___M___          \n";
    cout << '\n';
    ft_row();
    cout << "                                                             Made by: Persa Vlad";
    cout << "\n Press ENTER to continue!";
    cin.get();

}

void ft_screen(){
    cout << "\n";
    win = 1;
    for(int i = 0; i < a[cuv].size(); i++){
        if(lit[a[cuv][i] - 'a'] == 1)
            cout << a[cuv][i] << ' ';
        else {
            if(a[cuv][i] == ' ')
            cout <<  "  ";
            else {
                cout <<"_ ";
                win = 0;
            }
        }
    }
    if(fail > 0){
        cout << "\nBad guesses :";
        for(int i = 1; i <= fail; i++)
            cout << char(fai[i] + 'a') << ' ';
    }
    if(succ > 0){
        cout << "\nGood guesses :";
        for(int i = 1; i <= succ; i++)
            cout << char(suc[i] + 'a') << ' ';
    }
}

void ft_hint(){
    cout << "\n\n";
    if(show_hint == 1){
        cout << "Too few points, sorry.";
        show_hint = 0;
    }
    if(show_hint == 2)cout << b[cuv];
}

void ft_draw(){
    system("cls");
    ft_score();
    ft_generate_hangman1();
    ft_screen();
    ft_hint();
}

void ft_choose_letter(){
    cout << '\n';
    char letter;
    int ok = 0;
    cin >> letter;
    if(letter == '/'){
        if(show_hint != 2){
            if(score > min_score){
                score -= min_score;
                show_hint = 2;
            }
            else show_hint = 1;
        }
        ft_draw();
        ft_choose_letter();
        return;

    }
    if(letter >= 'A' && letter <= 'Z')
        letter = letter + 'a' - 'A';
    if(letter >= 'a' && letter <= 'z');
        else {
            ft_draw();
            ft_choose_letter();
            return;
        }
    if(lit[letter - 'a'] == 1){
        ft_draw();
        ft_choose_letter();
        return;
    }
    lit[letter - 'a'] = 1;
    life++;
    for(int i = 0; i < a[cuv].size(); i++){
        if(a[cuv][i] == letter){
            score += 10 * multi;
            multi *= 1.5;
            if(multi > max_multi)multi = max_multi;
            life--;
            succ++;
            suc[succ] = letter - 'a';
            ok = 1;
            return;
        }
    }
    if (ok == 0){
        multi /= 1.75;
        if(multi < 1)multi = 1;
        fail++;
        fai[fail] = letter - 'a';
        return;
    }
}

void ft_game(){
    while(life < 6){
        ft_draw();
        if(win)break;
        ft_choose_letter();
    }
    if(win){
        ft_win_screen();
        return;
    }
    ft_game_over_screen();
}

void ft_start_game(){
    show_hint = 0;
    subtract_score = 0;
    ft_generate_word();
    ft_draw();
    ft_clean();
    ft_game();
}

void ft_init(){
    ft_read();
    ft_start_screen();
    max_multi = 5;
    multi = 1;
    level = 1;
    ft_start_game();
}

int main()
{
    ft_init();
    return 0;
}
