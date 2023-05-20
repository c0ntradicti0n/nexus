#pragma once
#ifndef CONSTS_H
#define CONSTS_H
#include <map>
using namespace std;

static double historyMoves[120][120];

static int eigene_farbe = 1; // Sicht des Computers --1-0
static int stopp = 5;        // normale Suchtiefe, wird ver‚Ä∞ndert
static int stopp_tatsaechlich = 0;

static const int ende = 15;          // maximale Suchtiefe
static const int figurenanzahl = 12; // bei display)

static const int MAX_WERT = 99999999;
enum howitends {
  matt = -MAX_WERT,
  patt = -1,
  remis = 0,
  schaach = 1,
  schachmatt = +MAX_WERT,
  nothing
};
enum espezial { NICHTS = 0, SCHACH = 1, UNRUH = 2 };
enum spiel_status { Eroeffnung, Mittelspiel, Spaetspiel, Endspiel };

static const char *figuren_char[] = { // bei display)
    "tmr", "knr", "kon", "dam", "tum", "laf", "pdf", "bau", "baU",
    "bar", "bal", "bax", ".",   "BAX", "BAL", "BAR", "BAu", "BAU",
    "PDF", "LAF", "TUM", "DAM", "KON", "KNR", "TMR", "RAND"};

// bei eingabe()
static const char *figuren_intern[] = { // bei writ()
    "S_Tr",   "S_Kr",   "S_K",    "S_D",    "S_T",  "S_L",  "S_P",
    "S_B",    "S_Bu",   "S_Bp_r", "S_Bp_l", "S_Bx", "LEER", "W_Bx",
    "W_Bp_l", "W_Bp_r", "W_Bu",   "W_B",    "W_P",  "W_L",  "W_T",
    "W_D",    "W_K",    "W_Kr",   "W_Tr",   "RAND"};

static char buchstaben1[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
static char buchstaben2[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
static char zahlen[] = {'1', '2', '3', '4', '5', '6', '7', '8'};

static const char *grundfeld_bezeichnungen[120] = {
    // Ausgabe der Felder
    "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND",
    "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND",
    "RAND", "RAND", "RAND", "a1",   "b1",   "c1",   "d1",   "e1",   "f1",
    "g1",   "h1",   "RAND", "RAND", "a2",   "b2",   "c2",   "d2",   "e2",
    "f2",   "g2",   "h2",   "RAND", "RAND", "a3",   "b3",   "c3",   "d3",
    "e3",   "f3",   "g3",   "h3",   "RAND", "RAND", "a4",   "b4",   "c4",
    "d4",   "e4",   "f4",   "g4",   "h4",   "RAND", "RAND", "a5",   "b5",
    "c5",   "d5",   "e5",   "f5",   "g5",   "h5",   "RAND", "RAND", "a6",
    "b6",   "c6",   "d6",   "e6",   "f6",   "g6",   "h6",   "RAND", "RAND",
    "a7",   "b7",   "c7",   "d7",   "e7",   "f7",   "g7",   "h7",   "RAND",
    "RAND", "a8",   "b8",   "c8",   "d8",   "e8",   "f8",   "g8",   "h8",
    "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND",
    "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND", "RAND",
    "RAND", "RAND", "RAND"};

enum figuren { // bei display)
  S_Tr = -12,
  S_Kr = -11,
  S_K = -10,
  S_D,
  S_T,
  S_L,
  S_P,
  S_B,
  S_Bu,
  S_Bp_r,
  S_Bp_l,
  S_Bx,
  LEER = 0,
  W_Bx,
  W_Bp_l,
  W_Bp_r,
  W_Bu,
  W_B,
  W_P,
  W_L,
  W_T,
  W_D,
  W_K = 10,
  W_Kr = 11,
  W_Tr = 12,
  RAND = 13
};
static int grundfeld[120] = {
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, W_Tr,
    W_P,  W_L,  W_D,  W_Kr, W_L,  W_P,  W_Tr, RAND, RAND, W_Bx, W_Bx,
    W_Bx, W_Bx, W_Bx, W_Bx, W_Bx, W_Bx, RAND, RAND, LEER, LEER, LEER,
    LEER, LEER, LEER, LEER, LEER, RAND, RAND, LEER, LEER, LEER, LEER,
    LEER, LEER, LEER, LEER, RAND, RAND, LEER, LEER, LEER, LEER, LEER,
    LEER, LEER, LEER, RAND, RAND, LEER, LEER, LEER, LEER, LEER, LEER,
    LEER, LEER, RAND, RAND, S_Bx, S_Bx, S_Bx, S_Bx, S_Bx, S_Bx, S_Bx,
    S_Bx, RAND, RAND, S_Tr, S_P,  S_L,  S_D,  S_Kr, S_L,  S_P,  S_Tr,
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND,
    RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND, RAND}; // */

// Zahlen fuer den Zuggenerator, Sprenklereinstellungen
static int bewegung[15][15] = // Anzahl, Richtung, Weite, wohin[richtung]
    {
        {0, 0, 0},  // -- unsinn, ignorieren --
        {0, 1, 10}, // Bauer vor seinem Start
        {0, 0, 10}, // durchgestarteter Startbauer (kann kein en passant)
        {0, 0, 10}, // en passant Bauer in Aktion, muss sich umverwandelungn
        {0, 0, 0},  // Umwandelungsbauer auf der anderen Grundlinie
        {0, 0, 10}, // Bauer
        {7, 0, 21, 12, 19, 8, -21, -12, -19, -8}, // Pferd
        {3, 6, 9, 11, -9, -11},                   // Laeufer
        {3, 6, 10, 1, -1, -10},                   // Turm
        {7, 6, 9, 10, 11, 1, -1, -9, -10, -11},   // Dame
        {7, 0, 9, 10, 11, 1, -1, -9, -10, -11},   // Koenig vor Rochade
        {7, 0, 9, 10, 11, 1, -1, -9, -10, -11},   // Koenig
        {3, 6, 10, 1, -1, -10},                   // Turm vor Rochade
        {1, 0, 9, 11},                            // Bauer nach seinem Start
        // { 2, 0, 9, 10, 11}, // Koenig
};

 inline std::map<int, char> pieceToFen = {
      {S_Tr, 'r'},   {S_Kr, 'k'}, {S_K, 'k'},    {S_D, 'q'},    {S_T, 'r'},
      {S_P, 'n'},

      {S_L, 'b'},    {S_B, 'p'},  {S_Bx, 'p'},   {S_Bu, 'p'},   {S_Bp_l, 'p'},
      {S_Bp_r, 'p'}, {S_B, 'b'},  {W_Tr, 'R'},   {W_Kr, 'K'},   {W_K, 'K'},
      {W_P, 'N'},    {W_D, 'Q'},  {W_T, 'R'},    {W_L, 'B'},    {W_B, 'P'},
      {W_Bx, 'P'},   {W_Bu, 'P'}, {W_Bp_l, 'P'}, {W_Bp_r, 'P'}, {W_B, 'B'},
      {LEER, '1'}};


#endif