#ifndef _EVALUATION_
#define _EVALUATION_

// int figurenwert_weiss = 0;
// int figurenwert_schwarz = 0;
int figurenwert = 0;

int KooIch = 365;
int KooEr = 50; //???
double AttackIch = 5;
double AttackEr = 3;
int DefIch1 = 40;
int DefIch2 = 80;
int DefEr1 = 60;
int DefEr2 = 170; //???
double AttDame = 0.11;
int MobTurm = 9;      //???
double AttTurm = 0.5; //???
double MobLau = 21;   //???
double AttLau = 0.7;  //???
double AttSpr = 0.55;
double AttBau = 3.5;
double AttKoe = 2;    //???
double KSafety = 800; // 446 ändern
double K_Angriff_Turm = 0.5;
double K_Angriff_Laeufer = 0.25;
double K_Angriff_Springer = 0.25;
// double K_Angriff_Bauer = 0.05;//*/
// double KSafe = 0.04;
// int Koenigsangriff_Ich = 50;
// int Koenigsangriff_Er = 0;  //25 Koenigsangriff_Ich
/*                BEWERTUNG                 */
int __STARTFELD[120] = // Wei√üer Bauer
    {RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, LEER, LEER, LEER,
     LEER, LEER, LEER, LEER, LEER, RAND, RAND, W_Bx, W_Bx, W_Bx, W_Bx, W_Bx,
     W_Bx, W_Bx, W_Bx, RAND, RAND, W_B,  W_B,  W_B,  W_B,  W_B,  W_B,  W_B,
     W_B,  RAND, RAND, W_B,  W_B,  W_B,  W_B,  W_B,  W_B,  W_B,  W_B,  RAND,
     RAND, W_B,  W_B,  W_B,  W_B,  W_B,  W_B,  W_B,  W_B,  RAND, RAND, W_B,
     W_B,  W_B,  W_B,  W_B,  W_B,  W_B,  W_B,  RAND, RAND, W_B,  W_B,  W_B,
     W_B,  W_B,  W_B,  W_B,  W_B,  RAND, RAND, LEER, LEER, LEER, LEER, LEER,
     LEER, LEER, LEER, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND};
int __STARTFELDx[120] = // Schwarzer Bauer
    {RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, LEER, LEER, LEER,
     LEER, LEER, LEER, LEER, LEER, RAND, RAND, S_B,  S_B,  S_B,  S_B,  S_B,
     S_B,  S_B,  S_B,  RAND, RAND, S_B,  S_B,  S_B,  S_B,  S_B,  S_B,  S_B,
     S_B,  RAND, RAND, S_B,  S_B,  S_B,  S_B,  S_B,  S_B,  S_B,  S_B,  RAND,
     RAND, S_B,  S_B,  S_B,  S_B,  S_B,  S_B,  S_B,  S_B,  RAND, RAND, S_B,
     S_B,  S_B,  S_B,  S_B,  S_B,  S_B,  S_B,  RAND, RAND, S_Bx, S_Bx, S_Bx,
     S_Bx, S_Bx, S_Bx, S_Bx, S_Bx, RAND, RAND, LEER, LEER, LEER, LEER, LEER,
     LEER, LEER, LEER, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND};
int __STARTFELDx2[120] = // Wei√üer Springer
    {RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, W_P,  W_P,  W_P,
     W_P,  W_P,  W_P,  W_P,  W_P,  RAND, RAND, W_P,  W_P,  W_P,  W_P,  W_P,
     W_P,  W_P,  W_P,  RAND, RAND, W_P,  W_P,  W_P,  W_P,  W_P,  W_P,  W_P,
     W_P,  RAND, RAND, W_P,  W_P,  W_P,  W_P,  W_P,  W_P,  W_P,  W_P,  RAND,
     RAND, W_P,  W_P,  W_P,  W_P,  W_P,  W_P,  W_P,  W_P,  RAND, RAND, W_P,
     W_P,  W_P,  W_P,  W_P,  W_P,  W_P,  W_P,  RAND, RAND, W_P,  W_P,  W_P,
     W_P,  W_P,  W_P,  W_P,  W_P,  RAND, RAND, W_P,  W_P,  W_P,  W_P,  W_P,
     W_P,  W_P,  W_P,  RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND};
int __STARTFELDx3[120] = // Schwarzer Springer
    {RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, S_P,  S_P,  S_P,
     S_P,  S_P,  S_P,  S_P,  S_P,  RAND, RAND, S_P,  S_P,  S_P,  S_P,  S_P,
     S_P,  S_P,  S_P,  RAND, RAND, S_P,  S_P,  S_P,  S_P,  S_P,  S_P,  S_P,
     S_P,  RAND, RAND, S_P,  S_P,  S_P,  S_P,  S_P,  S_P,  S_P,  S_P,  RAND,
     RAND, S_P,  S_P,  S_P,  S_P,  S_P,  S_P,  S_P,  S_P,  RAND, RAND, S_P,
     S_P,  S_P,  S_P,  S_P,  S_P,  S_P,  S_P,  RAND, RAND, S_P,  S_P,  S_P,
     S_P,  S_P,  S_P,  S_P,  S_P,  RAND, RAND, S_P,  S_P,  S_P,  S_P,  S_P,
     S_P,  S_P,  S_P,  RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND};

int __STARTFELDx10[120] = // Wei√üer K√∂nig
    {RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, W_K,  W_K,  W_K,
     W_K,  W_Kr, W_K,  W_K,  W_K,  RAND, RAND, W_K,  W_K,  W_K,  W_K,  W_K,
     W_K,  W_K,  W_K,  RAND, RAND, W_K,  W_K,  W_K,  W_K,  W_K,  W_K,  W_K,
     W_K,  RAND, RAND, W_K,  W_K,  W_K,  W_K,  W_K,  W_K,  W_K,  W_K,  RAND,
     RAND, W_K,  W_K,  W_K,  W_K,  W_K,  W_K,  W_K,  W_K,  RAND, RAND, W_K,
     W_K,  W_K,  W_K,  W_K,  W_K,  W_K,  W_K,  RAND, RAND, W_K,  W_K,  W_K,
     W_K,  W_K,  W_K,  W_K,  W_K,  RAND, RAND, W_K,  W_K,  W_K,  W_K,  W_K,
     W_K,  W_K,  W_K,  RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND};
int __STARTFELDx11[120] = // Schwarzer K√∂nig
    {RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, S_K,
     S_K,  S_K,  S_K,  S_K,  S_K,  S_K,  S_K,  RAND, RAND, S_K,  S_K,
     S_K,  S_K,  S_K,  S_K,  S_K,  S_K,  RAND, RAND, S_K,  S_K,  S_K,
     S_K,  S_K,  S_K,  S_K,  S_K,  RAND, RAND, S_K,  S_K,  S_K,  S_K,
     S_K,  S_K,  S_K,  S_K,  RAND, RAND, S_K,  S_K,  S_K,  S_K,  S_K,
     S_K,  S_K,  S_K,  RAND, RAND, S_K,  S_K,  S_K,  S_K,  S_K,  S_K,
     S_K,  S_K,  RAND, RAND, S_K,  S_K,  S_K,  S_K,  S_K,  S_K,  S_K,
     S_K,  RAND, RAND, S_K,  S_K,  S_K,  S_K,  S_Kr, S_K,  S_K,  S_K,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND}; //*/

int __STARTPUNKTEx[120] = // Wei√üe bauern
    {RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, 0,    0,    0,
     0,    0,    0,    0,    0,    RAND, RAND, 8,    16,   24,   32,   32,
     24,   16,   8,    RAND, RAND, 3,    12,   20,   28,   28,   20,   12,
     3,    RAND, RAND, -5,   4,    10,   20,   20,   10,   4,    -5,   RAND,
     RAND, -6,   4,    5,    16,   16,   5,    4,    -6,   RAND, RAND, -6,
     4,    2,    5,    5,    2,    4,    -6,   RAND, RAND, -6,   4,    4,
     -15,  -15,  4,    4,    -6,   RAND, RAND, 0,    0,    0,    0,    0,
     0,    0,    0,    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND};
double __STARTPUNKTE[120] = {
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, 0,    0,    0,
    0,    0,    0,    0,    0,    RAND, RAND, -6,   4,    4,    -15,  -15,
    4,    4,    -6,   RAND, RAND, -6,   4,    2,    5,    5,    2,    4,
    -6,   RAND, RAND, -6,   4,    5,    16,   16,   5,    4,    -6,   RAND,
    RAND, -5,   4,    10,   20,   20,   10,   4,    -5,   RAND, RAND, 3,
    12,   20,   28,   28,   20,   12,   3,    RAND, RAND, 8,    16,   24,
    32,   32,   24,   16,   8,    RAND, RAND, 0,    0,    0,    0,    0,
    0,    0,    0,    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND};
double __STARTPUNKTEx2[120] = // Weiße Springer
    {RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, -53,  -42,  -32,
     -21,  -21,  -32,  -42,  -53,  RAND, RAND, -42,  -32,  -10,  0,    0,
     -10,  -32,  -42,  RAND, RAND, -21,  -10,  0,    0,    0,    0,    -10,
     -21,  RAND, RAND, -18,  0,    3,    21,   21,   3,    0,    -18,  RAND,
     RAND, -18,  0,    10,   21,   21,   10,   0,    -18,  RAND, RAND, -21,
     5,    10,   16,   16,   10,   5,    -21,  RAND, RAND, -42,  -32,  -10,
     0,    0,    -10,  -32,  -42,  RAND, RAND, -53,  -42,  -32,  -21,  -21,
     -32,  -42,  -53,  RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND};

double __STARTPUNKTEx3[120] = {
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, -53,  -42,  -32,
    -21,  -21,  -32,  -42,  -53,  RAND, RAND, -42,  -32,  -10,  0,    0,
    -10,  -32,  -42,  RAND, RAND, -21,  5,    10,   16,   16,   10,   5,
    -21,  RAND, RAND, -18,  0,    10,   21,   21,   10,   0,    -18,  RAND,
    RAND, -18,  0,    3,    21,   21,   3,    0,    -18,  RAND, RAND, -21,
    -10,  0,    0,    0,    0,    -10,  -21,  RAND, RAND, -42,  -32,  -10,
    0,    0,    -10,  -32,  -42,  RAND, RAND, -53,  -42,  -32,  -21,  -21,
    -32,  -42,  -53,  RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND};

double __STARTPUNKTEx10[120] = // K√∂nig
    {RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, 24,   24,   9,
     0,    0,    9,    24,   24,   RAND, RAND, 16,   14,   7,    -3,   -3,
     7,    14,   16,   RAND, RAND, 4,    -2,   -5,   -15,  -15,  -5,   -2,
     4,    RAND, RAND, -10,  -15,  -20,  -25,  -25,  -20,  -15,  -10,  RAND,
     RAND, -15,  -30,  -35,  -40,  -40,  -35,  -30,  -15,  RAND, RAND, -25,
     -35,  -40,  -45,  -45,  -40,  -35,  -25,  RAND, RAND, -22,  -35,  -40,
     -40,  -40,  -40,  -35,  -22,  RAND, RAND, -22,  -35,  -40,  -40,  -40,
     -40,  -35,  -22,  RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
     RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND};
double __STARTPUNKTEx11[120] = {
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, -22,
    -35,  -40,  -40,  -40,  -40,  -35,  -22,  RAND, RAND, -22,  -35,
    -40,  -40,  -40,  -40,  -35,  -22,  RAND, RAND, -25,  -35,  -40,
    -45,  -45,  -40,  -35,  -25,  RAND, RAND, -15,  -30,  -35,  -40,
    -40,  -35,  -30,  -15,  RAND, RAND, -10,  -15,  -20,  -25,  -25,
    -20,  -15,  -10,  RAND, RAND, 4,    -2,   -5,   -15,  -15,  -5,
    -2,   4,    RAND, RAND, 16,   14,   7,    -3,   -3,   7,    14,
    16,   RAND, RAND, 24,   24,   9,    0,    0,    9,    24,   24,
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND}; //*/

double materialwert[15] = // Materialwert 1.15
    {
        0,               // NIL! 0
        100,             // Startbauer 1
        500,             // durchgestarteter Startbauer 2
        33.3,            // en passant Bauer 3
        2250,            // Superbauer 4
        20,              // Bauer 5
        66.666666666667, // Pferd 6
        57.142857,       // Läufer 7
        75,              // Turm 8
        133.3333333,     // Dame 9
        3058,            // König 10
        2780,            // Rochade König 11
        50,              // Rochade Turm 12
};

#endif