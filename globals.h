#ifndef _GLOBAL_
#define _GLOBAL_

// VARIABLEN
int zug_nummer;
denkpaar aktueller_zug[ende];
denkpaar bester_zug[ende];
int __FELD[ende + 2][120];
int Feld[ende + 2][200];
denkpaar zugstapel[ende + 2][200];
denkpaar best_one[ende + 2];
int sort_schema[ende][200];
denkpaar sort_schema_bewertung[ende][200];
int bewertet; // MaÔ¨Ç f¬∏r die Partieeinheit
int timeline; // Entscheidung Endspiel oder ErÀÜffnung, Einfluss
// auf Bewertung und Suchtiefe
spiel_status partie_status; // Ereoffnung, Mittelspiel....
double kingzone[120];
double zugzone_ich[120];
double zugzone_du[120];
// double					OpenLines_weiss[8] =
// {1,1,1,1,1,1,1,1};
// double					OpenLines_schwarz[8] =
// {1,1,1,1,1,1,1,1};
// double     OpenLines[8] = {1,1,1,1,1,1,1,1};
static state status = uci;

#endif