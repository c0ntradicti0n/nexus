#pragma once

#include "io_util.h"

#include "basis.cpp"
#include "globals.h"
#include <plog/Log.h>

feldtyp *testbrett[ende + 1];

Spielfeld *testspiel[ende + 1];

howitends __end = nothing;

int bp(Spielfeld &spiel, int farbe, int alpha, double beta, int stufe,
       int _stopp, int NullFlag) {

  if (NullFlag == 3) {
    spiel.Farbe = -farbe;
  } else
    spiel.Farbe = farbe; //*/

  double wertung;

  srand(time(NULL));

  spiel.makeZugstapel();
  if (spiel.valid_n == 0) {
    PLOGI << "bp: no moves";
    return -10;
  }
  if (spiel.spezial == SCHACH) {
    return alpha;
  }

  int n = spiel.n; // number of possibly legal moves
  int nn = 0;      // number of legal moves

  for (int i = 0; i < n; i++) {

    aktueller_zug[stufe] = zugstapel[spiel.getStufe()][i];
    if (aktueller_zug[stufe].z.id == -1)
      continue;

    sort(zugstapel[spiel.getStufe()], spiel.n, stufe, i);
    testspiel[stufe]->copy(spiel);
    testspiel[stufe]->zug(zugstapel[spiel.getStufe()][i]);

    __end = spiel.last_moves();
    if (__end == nothing) {
      nn += 1;
    }

    /* LMR*/

    if (((stufe + 1 >= _stopp) || (stufe + 1 >= ende))) {

      wertung = rand() % 3 - 1;
      // wertung = 0;

      wertung += (double)1.5 * material(Feld[testspiel[stufe]->getStufe()],
                                        farbe); // 8.75-9		90
      if (alpha < wertung * farbe) {
        wertung +=
            (double)1.55 *
            entwicklung(Feld[testspiel[stufe]->getStufe()],
                        farbe); // 0.375-0.4		-->160		1.6
        wertung += (double)0.09 * zuganzahl(Feld[testspiel[stufe]->getStufe()],
                                            farbe); // 0,8;0.076
      }

      if ((((wertung * farbe > alpha - 150 &&
             wertung * -1 * farbe <= beta + 350 - figurenwert / 48) &&
            aktueller_zug[stufe].kill) &&
           stufe < _stopp)) {

        wertung = -bp(*testspiel[stufe], farbe * -1, -beta, -alpha, stufe + 1,
                      _stopp, 1);

      } else {
        wertung = wertung * (farbe);
        if (farbe == 1) {
          wertung -= 10;
        }
      }
    }

    else {

      if ((NullFlag == 1) && (_stopp - stufe) > 2) {

        int wertungn = 0;

        wertungn = -bp(*testspiel[stufe], farbe, -beta, -beta + 1, stufe + 1,
                       _stopp - 2, 3);

        if (wertungn >= beta && abs(beta) != MAX_WERT) {
          return beta;
        }
      }

      if (NullFlag == 1) {
        if ((_stopp - stufe) > 2) {
          if (i > 8 && (_stopp - stufe > 3) & !aktueller_zug[stufe].kill) {

            wertung = -bp(*testspiel[stufe], farbe * -1, -alpha - 1, -alpha,
                          stufe + 1, _stopp - 1, 4);

          } else
            wertung = alpha + 1;

          if (wertung > alpha) {

            wertung = -bp(*testspiel[stufe], -farbe, -beta, -alpha, stufe + 1,
                          _stopp, 4);
          }
        } else {
          if (i > 8 && (_stopp - stufe > 3) & !aktueller_zug[stufe].kill) {

            wertung = -bp(*testspiel[stufe], farbe * -1, -alpha - 1, -alpha,
                          stufe + 1, _stopp - 1, 1);

          } else
            wertung = alpha + 1;

          if (wertung > alpha) {
            wertung = -bp(*testspiel[stufe], farbe * -1, -beta, -alpha,
                          stufe + 1, _stopp, 1);
          }
        }
      } else {
        if (i > 8 && (_stopp - stufe > 3) & !aktueller_zug[stufe].kill) {

          wertung = -bp(*testspiel[stufe], farbe * -1, -alpha - 1, -alpha,
                        stufe + 1, _stopp - 1, 2);

        } else
          wertung = alpha + 1;

        if (wertung > alpha) {
          wertung = -bp(*testspiel[stufe], farbe * -1, -beta, -alpha, stufe + 1,
                        _stopp, 2);

          zugstapel[spiel.getStufe()][i].bewertung = wertung;
        } //}
      }
    }

    if (testspiel[stufe]->spezial == SCHACH) {

      testspiel[stufe]->spezial = NICHTS;
      continue;
    }

    zugstapel[spiel.getStufe()][i].bewertung = wertung;

    if (wertung > alpha) {

      if (zugstapel[spiel.getStufe()][i].z.id == -1)
        continue;

      bester_zug[stufe] = zugstapel[spiel.getStufe()][i];
      best_one[stufe] = zugstapel[spiel.getStufe()][i];

      if (spiel.Stufe == 0) {
        /*spiel.display();

        cout << "BESTER ZUG" << spiel.Stufe << " "
             << grundfeld_bezeichnungen[bester_zug[stufe].z.pos.pos1] << " "
             << grundfeld_bezeichnungen[best_one[stufe].z.pos.pos2] << " "
             << best_one[stufe].z.id << " " << best_one[stufe].kill << " "
             << best_one[stufe].bewertung << flush << "\n";
        cout << zugToString(best_one[stufe]) << endl;

        int x = 0;*/
      }

      if (wertung >= beta) {

        if (!aktueller_zug[stufe].kill)
          historyMoves[aktueller_zug[stufe].z.pos.pos1]
                      [aktueller_zug[stufe].z.pos.pos2] +=
              (_stopp - stufe) * (_stopp - stufe);

        spiel.nn = nn;

        return beta;
      }

      alpha = wertung;
    }
  }
  spiel.nn = nn;

  return alpha;
}
