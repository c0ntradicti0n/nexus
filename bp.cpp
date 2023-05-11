#ifndef _BP_
#define _BP_

#include "io_util.h"
#include "basis.cpp"
#include "globals.h"

feldtyp *testbrett[ende + 1];
Spielfeld *testspiel[ende + 1];
howitends __end = nothing;

double evaluate(Spielfeld &spiel, int farbe, int alpha, double beta, int stufe, int _stopp, int NullFlag, int i, denkpaar &aktueller_zug, Spielfeld *testspiel);

int bp(Spielfeld &spiel, int farbe, int alpha, double beta, int stufe, int _stopp, int NullFlag) {
  spiel.Farbe = NullFlag == 3 ? -farbe : farbe;
  srand(time(NULL));
  spiel.makeZugstapel();
  if (spiel.spezial == SCHACH)
      return -MAX_WERT; // assuming MAX_WERT is the maximum possible value

  int nn = 0;
  for (int i = 0; i < spiel.n; i++) {
    sort(zugstapel[spiel.getStufe()], spiel.n, stufe, i);
    testspiel[stufe]->copy(spiel);
    testspiel[stufe]->zug(zugstapel[spiel.getStufe()][i]);
    double wertung = rand() % 3 - 1;

    if (spiel.last_moves() == nothing) nn++;

    aktueller_zug[stufe] = zugstapel[spiel.getStufe()][i];
    if ((stufe + 1 >= _stopp) || (stufe + 1 >= ende)) {
      wertung = evaluate(spiel, farbe, alpha, beta, stufe, _stopp, NullFlag, i, aktueller_zug[stufe], testspiel[stufe]);
    }

    if (testspiel[stufe]->spezial == SCHACH) {
      testspiel[stufe]->spezial = NICHTS;
      continue;
    }
    zugstapel[spiel.getStufe()][i].bewertung = wertung;

    if (wertung > alpha) {
      bester_zug[stufe] = zugstapel[spiel.getStufe()][i];
      best_one[stufe] = zugstapel[spiel.getStufe()][i];

      if (wertung >= beta) {
        if (!aktueller_zug[stufe].kill)
          historyMoves[aktueller_zug[stufe].z.pos.pos1][aktueller_zug[stufe].z.pos.pos2] += (_stopp - stufe) * (_stopp - stufe);
        spiel.nn = nn;
        return beta;
      }
      alpha = wertung;
    }
  }
  spiel.nn = nn;
  return alpha;
}

double evaluate(Spielfeld &spiel, int farbe, int alpha, double beta, int stufe, int _stopp, int NullFlag, int i, denkpaar &aktueller_zug, Spielfeld *testspiel){
  double wertung = rand() % 3 - 1;

  wertung += (double)1.5 * material(Feld[testspiel->getStufe()], farbe);
  if (alpha < wertung * farbe) {
    wertung += (double)1.55 * entwicklung(Feld[testspiel->getStufe()], farbe);
    wertung += (double)0.09 * zuganzahl(Feld[testspiel->getStufe()], farbe);
  }

  if ((((wertung * farbe > alpha - 150 && wertung * -1 * farbe <= beta + 350 - figurenwert / 48) && aktueller_zug.kill) && stufe < _stopp)) {
    wertung = -bp(*testspiel, -farbe, -beta, -alpha, stufe + 1, _stopp, 1);
  } else {
    wertung = wertung * (farbe);
    if (farbe == 1) {
      wertung -= 10;
    }
  }
  return wertung;
}

#endif


