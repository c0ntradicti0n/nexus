feldtyp *testbrett[ende + 1];

Spielfeld *testspiel[ende + 1];

howitends __end = nothing;

int bp(Spielfeld &spiel, int farbe, int alpha, double beta, int stufe,
       int _stopp, /*int devwert, */ int NullFlag) { // Bewertung, Planung
    // zeit[stufe] = clock() ;

    if (NullFlag == 3) {
        spiel.Farbe = -farbe;
    } else
        spiel.Farbe = farbe; //*/

    double wertung;

    srand(time(NULL));

    //  make_schema(zugstapel[spiel.getStufe()], spiel.n, stufe);

    spiel.makeZugstapel();

    if (spiel.spezial == SCHACH) {
        return alpha;
    }

    int n = spiel.n; // Anzahl der Zuege
    int nn = 0;      // Anzahl der vom Schach her machbaren Zuege

    for (int i = 0; i < n; i++) {

        // cout << zeit[stufe] << "\n";
        sort(zugstapel[spiel.getStufe()], spiel.n, stufe, i);
        testspiel[stufe]->copy(spiel);
        testspiel[stufe]->zug(zugstapel[spiel.getStufe()][i]);

        __end = spiel.last_moves();
        if (__end == nothing) {
            nn += 1;
        }

        aktueller_zug[stufe] = zugstapel[spiel.getStufe()][i];

        /* LMR*/

        if (((stufe + 1 >= _stopp) || (stufe + 1 >= ende))) {

            wertung = rand() % 3 - 1;
            // wertung = 0;

            wertung +=
                (double)1.5 * material(Feld[testspiel[stufe]->getStufe()],
                                       farbe); // 8.75-9		90
            if (alpha < wertung * farbe) {
                wertung +=
                    (double)1.55 *
                    entwicklung(
                        Feld[testspiel[stufe]->getStufe()],
                        farbe); // 0.375-0.4		-->160		1.6
                wertung +=
                    (double)0.09 * zuganzahl(Feld[testspiel[stufe]->getStufe()],
                                             farbe); // 0,8;0.076
            }

            //  int zufallsfaktor = 3;
            // if (wertung*farbe > 0) {zufallsfaktor = abs(wertung)*0.1 + 3;}
            // wertung += rand() % zufallsfaktor - (zufallsfaktor-1)/2;
            // if (((wertung*farbe > alpha  &&  wertung*-1*farbe <=
            // beta+150-figurenwert/48) && aktueller_zug[stufe].kill && stufe <
            // _stopp+5)) {

            //   bool forcing_line = false;
            //  if (zeit[stufe-1]-zeit[stufe-2] < 2) {forcing_line = true;}

            if ((((wertung * farbe > alpha - 150 &&
                   wertung * -1 * farbe <= beta + 350 - figurenwert / 48) &&
                  aktueller_zug[stufe]
                      .kill) /*|| (aktueller_zug[stufe-2].kill &&
                                aktueller_zug[stufe-3].kill)*/
                             /* || forcing_line == true)*/
                 && stufe < _stopp)) {
                //  if (((wertung*farbe > alpha+250  &&  wertung*-1*farbe <=
                //  beta+250-figurenwert/40) && stufe < _stopp)) {

                wertung = -bp(*testspiel[stufe], farbe * -1, -beta, -alpha,
                              stufe + 1, _stopp, 1);

            } else {
                wertung = wertung * (farbe);
                if (farbe == 1) {
                    wertung -= 10;
                }
            }
        }

        else {
            /*if (i > 8 && (_stopp-stufe > 3) &! aktueller_zug[stufe].kill)
        {//cout << "stufe:" << stufe << " alpha" << alpha <<" _stopp" << _stopp
        << "Nullflag" << NullFlag << "\n";

            wertung = - bp(*testspiel[stufe], farbe*-1, -alpha-1, -alpha, stufe
        + 1, _stopp- 1, 1);

        }
        else wertung = alpha + 1;


        if(wertung > alpha){*/
            // cout << "1 \n";
            // cout << _stopp << "\n";

            if ((NullFlag == 1) && (_stopp - stufe) > 2) {

                int wertungn = 0;

                wertungn = -bp(*testspiel[stufe], farbe, -beta, -beta + 1,
                               stufe + 1, _stopp - 2, 3);

                if (wertungn >= beta && abs(beta) != MAX_WERT) {
                    return beta;
                }
            }

            if (NullFlag == 1) {
                if ((_stopp - stufe) > 2) {
                    if (i > 8 &&
                        (_stopp - stufe > 3) & !aktueller_zug[stufe].kill) {
                        // cout << "stufe:" << stufe << " alpha" << alpha <<"
                        // _stopp" << _stopp << "Nullflag" << NullFlag << "\n";

                        wertung = -bp(*testspiel[stufe], farbe * -1, -alpha - 1,
                                      -alpha, stufe + 1, _stopp - 1, 4);

                    } else
                        wertung = alpha + 1;

                    if (wertung > alpha) {

                        wertung = -bp(*testspiel[stufe], -farbe, -beta, -alpha,
                                      stufe + 1, _stopp, 4);
                    }
                } else {
                    if (i > 8 &&
                        (_stopp - stufe > 3) & !aktueller_zug[stufe].kill) {
                        // cout << "stufe:" << stufe << " alpha" << alpha <<"
                        // _stopp" << _stopp << "Nullflag" << NullFlag << "\n";

                        wertung = -bp(*testspiel[stufe], farbe * -1, -alpha - 1,
                                      -alpha, stufe + 1, _stopp - 1, 1);

                    } else
                        wertung = alpha + 1;

                    if (wertung > alpha) {
                        wertung = -bp(*testspiel[stufe], farbe * -1, -beta,
                                      -alpha, stufe + 1, _stopp, 1);
                    }
                }
            } else {
                if (i > 8 &&
                    (_stopp - stufe > 3) & !aktueller_zug[stufe].kill) {
                    // cout << "stufe:" << stufe << " alpha" << alpha <<"
                    // _stopp" << _stopp << "Nullflag" << NullFlag << "\n";

                    wertung = -bp(*testspiel[stufe], farbe * -1, -alpha - 1,
                                  -alpha, stufe + 1, _stopp - 1, 2);

                } else
                    wertung = alpha + 1;

                if (wertung > alpha) {
                    wertung = -bp(*testspiel[stufe], farbe * -1, -beta, -alpha,
                                  stufe + 1, _stopp, 2);

                    zugstapel[spiel.getStufe()][i].bewertung = wertung;
                } //}
            }
        }

        if (testspiel[stufe]->spezial == SCHACH) {

            testspiel[stufe]->spezial = NICHTS;
            continue;
        }

        zugstapel[spiel.getStufe()][i].bewertung = wertung;

        if (stufe == 0 && _stopp == stopp) {
            bewertet++;
            ;
            cout << "" << grundfeld_bezeichnungen[aktueller_zug[0].z.pos.pos1]
                 << " => "
                 << grundfeld_bezeichnungen[aktueller_zug[0].z.pos.pos2]
                 << " Bewertung: " << setw(5) << wertung << ", Zug-ID "
                 << setw(6) << aktueller_zug[0].z.id << "\n";
            cout.flush();
        }
        // else { if (stufe == 0) cout << "*" << flush;}

        if (wertung > alpha) {

            bester_zug[stufe] = zugstapel[spiel.getStufe()][i];
            best_one[stufe] =
                zugstapel[spiel.getStufe()][i]; // Aktueller PV-Zug f�r jede
                                                // Stufe inkl. Zuginformationen
            //  best_one[stufe].bewertung *= 0.5; //ACHTUNG 5

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
