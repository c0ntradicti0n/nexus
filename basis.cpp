#ifndef _BASIS_
#define _BASIS_

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <regex>

#include "chess_types.h"
#include "consts.h"
#include "evalutation.h"
#include "globals.h"
#include "moves.h"
#include "Spielfeld.h"

using namespace std;



howitends Spielfeld::check_end(vector<string> &_zuege) {
  find_kings();
  // print_zugstapel();
  // cout << "STUFE::: "<< this ->getStufe() << " w king: "<< this->wking << "
  // b king: " << this->bking;

  if (this->wking == 0 || this->bking == 0) {
    // display);
    cout << "He took the king!\n";
    //  tests = 1;
    return schachmatt;
  }

  if (this->test_drohung(Feld[this->getStufe()], 1, this->wking)) {
    // cout << "weiss hat schach/n";
    if (Farbe > 0) {
      // return matt;        // verloren
    } else { /*tests = 1;*/
      return schachmatt;
    }
  }

  if (this->test_drohung(Feld[this->getStufe()], -1, this->bking)) {
    // cout << "schwarz hat schach/n";
    if (Farbe < 0) {
      // return matt;        // verloren
    } else { /*tests = 1;*/
      return schachmatt;
    }
  }

  if (bester_zug[0].z.pos.pos1 == 0 && bester_zug[0].z.pos.pos2 == 0) {
    if (Farbe > 0) {

      if (this->test_drohung(Feld[this->getStufe()], this->Farbe,
                             this->wking)) { /*tests = 1;*/
        return matt;
      } // verloren

      if (this->test_drohung(Feld[this->getStufe()], this->Farbe * -1,
                             this->bking)) { /*tests = 1;*/
        return schachmatt;
      } // gewonnen
    }

    if (Farbe < 0) {
      if (this->test_drohung(Feld[this->getStufe()], this->Farbe * -1,
                             this->wking)) { /*tests = 1;*/
        return schachmatt;
      } // gewonnen

      if (this->test_drohung(Feld[this->getStufe()], this->Farbe,
                             this->bking)) { /*tests = 1;*/
        return matt;
      } // verloren
    }
    return patt; // kein zug
  }              // moeglich  (was
                 // ist mit remis
                 // bei
                 // gefesselten

  if (zuege_wied(_zuege))
    return remis;
  else
    return nothing;
}

int gegner;
howitends Spielfeld::last_moves() {
  // testet, ob, nachdem der Zug gesetzt wurde, noch Schach ist; wenn der
  // Gegner nach seinem Zug noch im Schach steht,hat er einen falschen gemacht
  gegner = this->Farbe;

  find_kings();

  if (Farbe < 0) {
    if (this->test_drohung(Feld[this->getStufe()], 1, this->wking)) {
      // cout << "weiss hat schach";

      /* tests =1;*/
      return schaach; // verloren
    }
  }

  if (Farbe > 0) {
    if (this->test_drohung(Feld[this->getStufe()], -1, this->bking)) {
      // cout << "schwarz hat schach";
      /*tests = 1;*/
      return schaach;
    }
  }
  return nothing;
}

Spielfeld::Spielfeld() {
  Farbe = 0;
  Stufe = 0;
  {
    for (int i = 0; i < 120; i++) {
      Feld[Stufe][i] = 0;
    }
  }
}

Spielfeld::Spielfeld(int _feld[120], int _farbe = 0, int _stufe = 0) {
  setFarbe(_farbe);
  setStufe(_stufe);
  {
    for (int i = 0; i < 120; i++) {
      Feld[Stufe][i] = _feld[i];
    }
  }
}

string int_array_to_string(int int_array[], int size_of_array) {
  ostringstream oss("");

  for (int temp = 0; temp < size_of_array; temp++)
    oss << int_array[temp];
  return oss.str();
}

string Spielfeld::hash() {
  Feld[1][0] = Farbe;
  string str = int_array_to_string(Feld[1], 120);
  Feld[1][0] = RAND;
  string str2 = int_array_to_string(Feld[1], 120);

  std::size_t str_hash =
      std::hash<std::string>{}(str) + std::hash<std::string>{}(str2);

  // std::cout << "hash(" << std::quoted(str) << ") = " << str_hash << '\n';

  return to_string(str_hash);
}

inline void Spielfeld::zug_reset() {
  Stufe = 0;

  for (int i = 0; i < 120; i++) {
    Feld[Stufe][i] = Feld[Stufe + 1][i];
  }

  for (int j = 0; j < ende; j++) {
    bester_zug[j].z.pos.pos1 = 0;
    bester_zug[j].z.pos.pos2 = 0;
  }
}

feldtyp *Spielfeld::to_feldtyp(feldtyp *neues) {
  {
    for (int i = 0; i < 120; i++) {
      neues->feld[i] = Feld[Stufe][i];
    }
  }
  return neues;
}

feldtyp *Spielfeld::to_feldtyp() {
  feldtyp *neues = new feldtyp;
  {
    for (int i = 0; i < 120; i++) {
      neues->feld[i] = Feld[Stufe][i];
    }
  }

  return neues;
}

inline int *Spielfeld::to_feld(int _feld[120]) {
  {
    for (int i = 0; i < 120; i++) {
      _feld[i] = Feld[Stufe][i];
    }
  }
  return _feld;
}

inline int *Spielfeld::to_feld() {
  int *_feld = new int[120];
  {
    for (int i = 0; i < 120; i++) {
      _feld[i] = Feld[Stufe][i];
    }
  }

  return _feld;
}

inline void Spielfeld::copy(Spielfeld &_spiel) {
  Farbe = _spiel.Farbe;
  Stufe = _spiel.Stufe;
}

inline void Spielfeld::setPos(int _feld[], int _farbe, int _stufe,
                              vector<string> &_zuege) {
  setFarbe(_farbe);
  setStufe(_stufe);
  {
    for (int i = 0; i < 120; i++) {
      Feld[Stufe][i] = _feld[i];
    }
  }
  _zuege.clear();
  return;
}

inline void Spielfeld::setFarbe(int _farbe) { Farbe = _farbe; }

inline void Spielfeld::setStufe(int _stufe) { Stufe = _stufe; }

inline int Spielfeld::getStufe() { return Stufe; }



inline void Spielfeld::zug(denkpaar &_zug) {
  setStufe(Stufe + 1);

  for (int i = 0; i < 120; i++) {
    Feld[Stufe][i] = Feld[Stufe - 1][i];
  }

  Feld[Stufe][_zug.z.pos.pos2] = Feld[Stufe][_zug.z.pos.pos1];
  Feld[Stufe][_zug.z.pos.pos1] = LEER;

  if ((_zug.nw)) {
    int max = _zug.nw;

    for (int j = 0; j < max; j++) {
      Feld[Stufe][_zug.verwandelung[j].pos1] = _zug.verwandelung[j].fig;
    }
  }

  setFarbe(Farbe * -1);

  Z = false;
}



int Spielfeld::convert_piece(char piece) {
    /* converts a piece character to a piece integer */
    switch (piece) {
        case 'p': return S_P;
        case 'r': return S_T;
        case 'n': return S_L;
        case 'b': return S_L;
        case 'q': return S_D;
        case 'k': return S_K;
        case 'P': return W_P;
        case 'R': return W_T;
        case 'N': return W_L;
        case 'B': return W_L;
        case 'Q': return W_D;
        case 'K': return W_K;
        default: return LEER;
    }
}

void Spielfeld::read_fen(std::string fen) {
    /* FEN is a space-separated string
     * 1st part: piece placement on the board
     * 2nd part: active color
     * 3rd part: castling availability
     * 4th part: en passant target square
     * 5th part: halfmove clock
     * 6th part: fullmove number
     */

    int rank = 7; // 8th rank first
    int file = 0; // a file first

    for (char ch : fen) {
        if (ch == '/') { // next rank
            --rank;
            file = 0;
        } else if (isdigit(ch)) { // empty squares
            file += ch - '0';
        } else { // piece
            Feld[rank][file] = convert_piece(ch);
            ++file;
        }

        if (rank < 0 || file > 7) break; // Only parse the pieces part of the FEN
    }
}

inline void Spielfeld::realer_zug(denkpaar &_zug, vector<string> &_zuege) {
  zug(_zug);
  zuege_append(_zuege, this->hash());
  return;
}

inline void Spielfeld::add_zug(const int &pos1, const int &pos2, const int &_n,
                               const bool &_kill, const int &_figur,
                               const double &_order) {

  zugstapel[Stufe][_n].z.pos.pos1 = pos1;
  zugstapel[Stufe][_n].z.pos.pos2 = pos2;
  zugstapel[Stufe][_n].kill = _kill;
  zugstapel[Stufe][_n].figur = _figur;
  zugstapel[Stufe][_n].order = _order;
  n++;
  return;
}

inline void Spielfeld::add_verwandelung(const int &farbe, const int &pos,
                                        const int &was, const int &n) {
  zugstapel[Stufe][n].verwandelung[zugstapel[Stufe][n].nw].pos1 = pos;
  zugstapel[Stufe][n].verwandelung[zugstapel[Stufe][n].nw].fig = was * farbe;
  zugstapel[Stufe][n].nw++;
}

inline bool Spielfeld::look_richtung_td(const int feld[], const int &farbe,
                                        const int &pos, const int &step) {
  int zielfeld, farbvorzeichen, i;
  for (i = pos + step; 19 < i && i < 100; i += step) {
    zielfeld = feld[i];
    if (zielfeld == RAND)
      break;
    if (zielfeld == LEER)
      continue;

    farbvorzeichen = abs(zielfeld) / zielfeld;

    if (farbvorzeichen == farbe)
      break;

    if ((zielfeld == W_D * farbe * -1) || (zielfeld == W_T * farbe * -1) ||
        (zielfeld == W_Tr * farbe * -1))
      return true;
    else
      break;
  }
  return false;
}

inline bool Spielfeld::look_richtung_ld(const int feld[], const int &farbe,
                                        const int &pos, const int &step) {
  int zielfeld, farbvorzeichen, i;
  for (i = pos + step; 19 < i && i < 100; i += step) {
    zielfeld = feld[i];
    if (zielfeld == RAND)
      break;
    if (zielfeld == LEER)
      continue;

    farbvorzeichen = abs(zielfeld) / zielfeld;

    if (farbvorzeichen == farbe)
      break;

    if ((zielfeld == W_D * farbe * -1) || (zielfeld == W_L * farbe * -1))
      return true;
    else
      break;
  }
  return false;
}

inline bool Spielfeld::test_drohung(int feld[], int farbe, int pos) {
  if ((pos < 0) || (pos > 99)) {
    cout << pos << " ";
    return false;
  }

  return look_richtung_td(feld, farbe, pos, 10) ||
         look_richtung_td(feld, farbe, pos, -10) ||
         look_richtung_td(feld, farbe, pos, 1) ||
         look_richtung_td(feld, farbe, pos, -1) ||
         look_richtung_ld(feld, farbe, pos, 9) ||
         look_richtung_ld(feld, farbe, pos, -9) ||
         look_richtung_ld(feld, farbe, pos, 11) ||
         look_richtung_ld(feld, farbe, pos, -11) ||

         (feld[pos + 21 * farbe] == W_P * farbe * -1) ||
         (feld[pos + 12 * farbe] == W_P * farbe * -1) ||
         (feld[pos + 19 * farbe] == W_P * farbe * -1) ||
         (feld[pos + 8 * farbe] == W_P * farbe * -1) ||
         (feld[pos + 9 * farbe] == W_B * farbe * -1) ||
         (feld[pos + 11 * farbe] == W_B * farbe * -1) ||

         (feld[pos + 11 * farbe] == W_K * farbe * -1 ||
          feld[pos + -11 * farbe] == W_K * farbe * -1 ||
          feld[pos + 1 * farbe] == W_K * farbe * -1 ||
          feld[pos + -1 * farbe] == W_K * farbe * -1 ||
          feld[pos + 10 * farbe] == W_K * farbe * -1 ||
          feld[pos + -10 * farbe] == W_K * farbe * -1 ||
          feld[pos + 9 * farbe] == W_K * farbe * -1 ||
          feld[pos + -9 * farbe] == W_K * farbe * -1);
}

inline void Spielfeld::find_kings() {
  // setzt wking und bking auf entsprechende Werte

  wking = 0;
  bking = 0;
  int farbvorzeichen;
  int figur;

  for (int i = 21; i <= 98; i++) {

    figur = (abs(Feld[Stufe][i]));

    if ((figur == LEER) || (figur == RAND))
      continue;

    farbvorzeichen = figur / Feld[Stufe][i];

    if ((figur == W_K) || (figur == W_Kr)) {
      if (farbvorzeichen > 0)
        wking = i;
      else
        bking = i;
    }
  }
}

int Spielfeld::zuggenerator() {
  int pos1, pos2;
  int enp_l, enp_r;
  int ziel, zielfeld;
  int farbvorzeichen, figur;

  int zugnr = 0;

  n = 0; // Variable der Klasse, wenn man es neu deklarieren wuerde,
         // kommt es zu einem seltsamen Fehler in der Zugsortierung,
         // weil n lokal dann 0 bleibt
  int en_passent_bauer = 0;
  spezial = NICHTS;
  test = 0;

  for (int o = 0; o < 199; o++)
    zugstapel[Stufe][o].nw = 0;

  for (int i = 21; i <= 98; i++) {
    figur = (abs(Feld[Stufe][i]));

    if ((figur == LEER) || (figur == RAND))

      continue;

    farbvorzeichen = figur / Feld[Stufe][i];

    pos1 = i;

    if (farbvorzeichen == Farbe) {
      if ((figur == W_Bx) || (figur == W_B) || (figur == W_Bp_r) ||
          (figur == W_Bp_l)) {
        // Bauernschlag fuer Startbauer, normalen Bauern, en
        // passant-Bauer
        if ((figur == W_Bp_r) || (figur == W_Bp_l)) {
          // en passant bauer, der nicht gezogen wird, kann spaeter
          // nicht mehr
          en_passent_bauer = pos1;
        }

        ziel = pos2 = pos1 + farbvorzeichen * 9;

        // links vor und schlagen
        zielfeld = Feld[Stufe][ziel];

        if (figur == W_Bp_l) {
          add_verwandelung(farbvorzeichen, pos2 - 10 * farbvorzeichen, LEER, n);
          add_verwandelung(farbvorzeichen, pos2, W_B, n);
          add_zug(pos1, pos2, n, true, figur, 0);
        }

        if (zielfeld != RAND) {
          if (zielfeld != LEER) {
            // schraeg schlagen
            if (zielfeld == -1 * W_K * farbvorzeichen ||
                zielfeld == -1 * W_Kr * farbvorzeichen) {
              spezial = SCHACH; /*tests = 1;*/
              return 0;
            }

            if (zielfeld / abs(zielfeld) != farbvorzeichen) {
              spezial = UNRUH;

              if (figur == W_Bx) {
                add_verwandelung(farbvorzeichen, pos2, W_B, n);
              } else if (figur == W_B) { // Bauernumwandelung per schlag
                if (Farbe > 0) {
                  if ((91 <= pos2) && (pos2 <= 98)) {
                    add_verwandelung(farbvorzeichen, pos2, W_D, n);
                    add_zug(pos1, pos2, n, true, W_D, 900);
                    add_verwandelung(farbvorzeichen, pos2, W_P, n);
                    add_zug(pos1, pos2, n, true, W_P, 300);

                    //		break;
                  }
                } else if (Farbe < 0) {
                  if ((21 <= pos2) && (pos2 <= 28)) {
                    add_verwandelung(farbvorzeichen, pos2, W_D, n);
                    add_zug(pos1, pos2, n, true, W_D, 900);
                    add_verwandelung(farbvorzeichen, pos2, W_P, n);
                    add_zug(pos1, pos2, n, true, W_P, 300);

                    //		break;
                  }
                }
              }
              add_zug(pos1, pos2, n, true, figur,
                      materialwert[abs(zielfeld)] -
                          materialwert[abs(figur)] * 0.1);
            }
          }
        }

        // rechts vor
        pos2 = ziel = pos1 + farbvorzeichen * 11;
        zielfeld = Feld[Stufe][ziel];

        if (figur == W_Bp_r) {
          add_verwandelung(farbvorzeichen, pos2 - 10 * farbvorzeichen, LEER, n);
          add_verwandelung(farbvorzeichen, pos2, W_B, n);
          add_zug(pos1, pos2, n, true, figur, 0);
        } else

            if (((zielfeld = Feld[Stufe][ziel]) != RAND)) {
          if (zielfeld != LEER) { // schraeg schlagen
            if (zielfeld == -1 * W_K * farbvorzeichen) {
              spezial = SCHACH; /*tests = 1;*/
              return 0;
            }

            if (zielfeld / abs(zielfeld) != farbvorzeichen) {
              spezial = UNRUH;

              if (figur == W_Bx)
                add_verwandelung(farbvorzeichen, pos2, W_B, n);
              else if (figur == W_B) { // Bauernumwandelung per schlag
                if (Farbe > 0) {
                  if ((91 <= pos2) && (pos2 <= 98)) {
                    add_verwandelung(farbvorzeichen, pos2, W_D, n);
                    add_zug(pos1, pos2, n, true, figur, 900);
                    add_verwandelung(farbvorzeichen, pos2, W_P, n);
                    add_zug(pos1, pos2, n, true, figur, 300);

                    //		break;
                  }
                } else if (Farbe < 0) {
                  if ((21 <= pos2) && (pos2 <= 28)) {
                    add_verwandelung(farbvorzeichen, pos2, W_D, n);
                    add_zug(pos1, pos2, n, true, figur, 900);
                    add_verwandelung(farbvorzeichen, pos2, W_P, n);
                    add_zug(pos1, pos2, n, true, figur, 300);

                    //		break;
                  }
                }
              }
              add_zug(pos1, pos2, n, true, figur,
                      materialwert[abs(zielfeld)] -
                          materialwert[abs(figur)] * 0.1);
            }
          }
        }
      } // Bauer endet hier

      // andere figuren
      for (int richtung = 0; richtung <= bewegung[figur][0]; richtung++) {
        for (int weite = 0; weite <= bewegung[figur][1]; weite++) {
          pos2 = pos1 +
                 farbvorzeichen * bewegung[figur][2 + richtung] * (weite + 1);
          int zielfeld = Feld[Stufe][pos2];

          // schlagen
          if (zielfeld != LEER) {
            int zielfigur = abs(zielfeld);

            if (zielfeld == RAND) // Aus!
              break;

            if (zielfeld / zielfigur == farbvorzeichen) // eigene Figur
              break;

            if ((figur == W_Bx) || (figur == W_Bp_l) || (figur == W_B) ||
                (figur == W_Bp_r)) // kein Bauer schlaegt geradeaus
              break;

            if ((zielfeld == -1 * W_K * farbvorzeichen) ||
                (zielfeld == -1 * W_Kr * farbvorzeichen)) {
              spezial = SCHACH; /*tests = 1;*/

              return 0;
            }

            if ((figur == W_Kr) || (figur == W_K)) {
              if (test_drohung(Feld[Stufe], Farbe, pos1)) {
                test = 1;
              }
              if (test_drohung(Feld[Stufe], Farbe, pos2)) {
                test = 1;
                break;
              }
            }

            if (figur == W_Kr) {
              add_verwandelung(farbvorzeichen, pos2, W_K, n);
            } else if (figur == W_Tr) {
              add_verwandelung(farbvorzeichen, pos2, W_T, n);
            }

            spezial = UNRUH;
            add_zug(pos1, pos2, n, true, figur,
                    materialwert[abs(zielfeld)] -
                        materialwert[abs(figur)] * 0.1);

            break;
          }

          // gehen
          if (figur == W_B) { // Bauernumwandelung
            if (Farbe > 0) {
              if ((91 <= pos2) && (pos2 <= 98)) {
                add_verwandelung(farbvorzeichen, pos2, W_D, n);
                add_zug(pos1, pos2, n, false, figur, 900);
                add_verwandelung(farbvorzeichen, pos2, W_P, n);
                add_zug(pos1, pos2, n, false, figur, 300);

                //		break;
              }
            } else if (Farbe < 0) {
              if ((21 <= pos2) && (pos2 <= 28)) {
                add_verwandelung(farbvorzeichen, pos2, W_D, n);
                add_zug(pos1, pos2, n, false, figur, 900);
                add_verwandelung(farbvorzeichen, pos2, W_P, n);
                add_zug(pos1, pos2, n, false, figur, 300);

                //		break;
              }
            }
          } else

              if ((figur == W_Bp_r) || (figur == W_Bp_l))
            add_verwandelung(farbvorzeichen, pos2, W_B, n);
          else if (figur == W_Bx) {
            add_verwandelung(farbvorzeichen, pos2, W_B, n);

            if (weite == 1) {
              enp_r = Feld[Stufe][pos2 + farbvorzeichen];
              enp_l = Feld[Stufe][pos2 - farbvorzeichen];

              if (enp_r == -1 * W_B * farbvorzeichen) {
                add_verwandelung(farbvorzeichen * -1, pos2 + farbvorzeichen,
                                 W_Bp_r, n);
              }

              if (enp_l == -1 * W_B * farbvorzeichen) {
                add_verwandelung(farbvorzeichen * -1, pos2 - farbvorzeichen,
                                 W_Bp_l, n);
              }
            }
          }

          if ((figur == W_Kr) || (figur == W_K)) {
            if (test_drohung(Feld[Stufe], Farbe, pos1)) {
              test = 1;
            }
            if (test_drohung(Feld[Stufe], Farbe, pos2)) {
              //    tests = 1;
              break;
            }
          }

          if (figur == W_Kr) {
            add_verwandelung(farbvorzeichen, pos2, W_K, n);
          } else if (figur == W_Tr) {
            add_verwandelung(farbvorzeichen, pos2, W_T, n);
          }

          add_zug(pos1, pos2, n, false, figur, 0);
        }
      }
    }
  }

  // Rochade

  if ((Feld[Stufe][25] == W_Kr) || (Feld[Stufe][95] == S_Kr)) {
    if (Farbe < 0) {
      if ((Feld[Stufe][95] == S_Kr) && (Feld[Stufe][96] == LEER) &&
          (Feld[Stufe][97] == LEER) && (Feld[Stufe][98] == S_Tr)) {
        if (!test_drohung(Feld[Stufe], Farbe, 95) &&
            !test_drohung(Feld[Stufe], Farbe, 96) &&
            !test_drohung(Feld[Stufe], Farbe, 97)) {
          add_verwandelung(Farbe, 97, W_K, n);
          add_verwandelung(Farbe, 96, W_T, n);
          add_verwandelung(Farbe, 98, LEER, n);
          add_zug(95, 97, n, false, figur, 150);
        }
      }

      if ((Feld[Stufe][95] == S_Kr) && (Feld[Stufe][94] == LEER) &&
          (Feld[Stufe][93] == LEER) && (Feld[Stufe][92] == LEER) &&
          (Feld[Stufe][91] == S_Tr)) {
        if (!test_drohung(Feld[Stufe], Farbe, 95) &&
            !test_drohung(Feld[Stufe], Farbe, 94) &&
            !test_drohung(Feld[Stufe], Farbe, 93)) {
          add_verwandelung(Farbe, 93, W_K, n);
          add_verwandelung(Farbe, 94, W_T, n);
          add_verwandelung(Farbe, 91, LEER, n);
          add_zug(95, 93, n, false, figur, 150);
        }
      }
    } else if (Farbe > 0) {
      if ((Feld[Stufe][25] == W_Kr) && (Feld[Stufe][26] == LEER) &&
          (Feld[Stufe][27] == LEER) && (Feld[Stufe][28] == W_Tr)) {
        if (!test_drohung(Feld[Stufe], Farbe, 25) &&
            !test_drohung(Feld[Stufe], Farbe, 26) &&
            !test_drohung(Feld[Stufe], Farbe, 27)) {
          add_verwandelung(Farbe, 27, W_K, n);
          add_verwandelung(Farbe, 26, W_T, n);
          add_verwandelung(Farbe, 28, LEER, n);
          add_zug(25, 27, n, false, figur, 150);
        }
      }

      if ((Feld[Stufe][25] == W_Kr) && (Feld[Stufe][24] == LEER) &&
          (Feld[Stufe][23] == LEER) && (Feld[Stufe][22] == LEER) &&
          (Feld[Stufe][21] == W_Tr)) {
        if (!test_drohung(Feld[Stufe], Farbe, 25) &&
            !test_drohung(Feld[Stufe], Farbe, 24) &&
            !test_drohung(Feld[Stufe], Farbe, 23)) {
          add_verwandelung(Farbe, 23, W_K, n);
          add_verwandelung(Farbe, 24, W_T, n);
          add_verwandelung(Farbe, 21, LEER, n);
          add_zug(25, 23, n, false, figur, 150);
        }
      }
    }
  }

  // wenn ein en passent bauer gefunden wurde, dann musser bei allen zuegen,
  // ausser bei seinen eigenen im naechsten zug umgewandelt werden
  if (en_passent_bauer != 0) {
    int q;

    for (q = 0; q < n; q++) {
      figur = zugstapel[Stufe][q].figur;

      if (!((figur == W_Bp_l) || (figur == W_Bp_r))) {
        add_verwandelung(Farbe, en_passent_bauer, W_B, q);
      }
    }
  }
  return n;
}

inline denkpaar *Spielfeld::makeZugstapel() {
  zuggenerator();
  Z = true;
  return zugstapel[Stufe];
}

int schach_bewegung[15][15] = // Richtung, Weite, wohin[richtung]
    {
        {0, 0, 0},                                // NIL!
        {7, 0, 21, -21, 12, -12, 19, -19, 8, -8}, // Pferd
        {7, 6, 1, -1, 9, -9, 10, -10, 11, -11},   // Dame;
};

void Spielfeld::display() {
  cout << "\n";
  int breite = 3;

  cout << "      "
       << "  >--A--v--B--v--C--v--D--v--E--v--F--v--G--v--H--<\n";
  cout << "      "
       << "v >-----+-----+-----+-----+-----+-----+-----+-----< v\n"
       << "      ";

  for (int j = 9; j > 1; j--) {
    cout << j - 1;

    for (int i = 1; i < 9; i++) {
      if (Feld[Stufe][j * 10 + i] != RAND)
        cout << setw(breite) << " | " << setw(breite)
             << figuren_char[Feld[Stufe][j * 10 + i] + figurenanzahl];
    }
    cout << setw(breite) << "| " << j - 1 << "\n"
         << "      "
         << "^ >-----+-----+-----+-----+-----+-----+-----+-----< ^\n"
         << "      ";
  }
  cout << "  >--A--+--B--+--C--+--D--+--E--+--F--+--G--+--H--< ^\n";
  cout << "\n";
}

void Spielfeld::disp_cleanest() {
  cout << "\n";

  for (int j = 9; j > 1; j--) {
    for (int i = 1; i < 9; i++) {
      if (Feld[Stufe][j * 10 + i] != RAND)
        cout << figuren_char[Feld[Stufe][j * 10 + i] + figurenanzahl];

      if (j * 10 + i != 28)
        cout << ",";
    }
    cout << "\n";
  }
  cout << "\n";
}

void Spielfeld::print_zugstapel() {
  for (int i = 0; i < n; i++) {
    cout << figuren_char[zugstapel[Stufe][i].figur + figurenanzahl] << ": "
         << int(zugstapel[Stufe][i].z.pos.pos1) << "("
         << grundfeld_bezeichnungen[zugstapel[Stufe][i].z.pos.pos1] << ")  => "
         << int(zugstapel[Stufe][i].z.pos.pos2) << "("
         << grundfeld_bezeichnungen[zugstapel[Stufe][i].z.pos.pos2] << ")";

    if (zugstapel[Stufe][i].nw) {
      cout << " | ";
      int max = zugstapel[Stufe][i].nw;

      for (int j = 0; j < max; j++) {
        cout
            << int(zugstapel[Stufe][i].verwandelung[j].pos1) << "("
            << grundfeld_bezeichnungen[zugstapel[Stufe][i].verwandelung[j].pos1]
            << ")  <= "
            << figuren_char[zugstapel[Stufe][i].verwandelung[j].fig +
                            figurenanzahl];

        if (j < max - 1)
          cout << ", ";
      }
    }

    cout << "\n";
  }
}

void Spielfeld::write() {
  ofstream partie("partie.txt", ios::app);

  partie << "\n{\n";
  partie << "RAND,	RAND,	RAND,	RAND,	RAND,	RAND,	RAND,	"
            "RAND,	RAND,	RAND,\n"
         << "RAND,	RAND,	RAND,	RAND,	RAND,	RAND,	RAND,	"
            "RAND,	RAND,	RAND,\n";

  for (int j = 2; j < 10; j++) {
    partie << "RAND, ";

    for (int i = 1; i < 9; i++) {
      if (Feld[Stufe][j * 10 + i] != RAND)
        partie << setw(6)
               << figuren_intern[Feld[Stufe][j * 10 + i] + figurenanzahl]
               << ", ";
    }
    partie << "  RAND,";
    partie << "\n";
  }
  partie << "RAND,	RAND,	RAND,	RAND,	RAND,	RAND,	RAND,	"
            "RAND,	RAND,	RAND,\n"
         << "RAND,	RAND,	RAND,	RAND,	RAND,	RAND,	RAND,	"
            "RAND,	RAND,	RAND\n";
  partie << "};";
  partie << "\n";
  partie.close();
}

inline double entwicklung(int feld[120], int farbe) {
  double wertung = 0;
  int dieses_feld;

  for (int i = 21; i <= 98; i++) {
    // dieses_feld = feld[i];

    if (feld[i] == RAND || (abs(feld[i]) > 6 && abs(feld[i]) < 10))
      continue;

    if (feld[i] == __STARTFELD[i])
      wertung += 2 * __STARTPUNKTE[i]; // -kingzone_ich[i]*10;	//4.1
    if (feld[i] == __STARTFELDx[i])
      wertung -=
          2 *
          __STARTPUNKTEx[i]; // -kingzone_gegner[i]*10;//-kingzone_ich[i]*10;
                             // //4.1
    //	else wertung -= 1 *
    //__STARTPUNKTEx[i];}//-kingzone_gegner[i]*10;*/
    if (feld[i] == __STARTFELDx2[i])
      wertung += 1.7 * __STARTPUNKTEx2[i]; // +kingzone_ich[i]*10;	//1.17
    if (feld[i] == __STARTFELDx3[i])
      wertung -= 1.7 * __STARTPUNKTEx3[i]; // -kingzone_gegner[i]*10;
    // REST PSQ
    /*    if (feld[i] == __STARTFELDx4[i]) wertung += 0.55*
       __STARTPUNKTEx4[i];
       // +kingzone_ich[i]*10;	//1.17 if (feld[i] == __STARTFELDx5[i])
       wertung
       -=  0.55* __STARTPUNKTEx5[i];//*/
    /* if (feld[i] == __STARTFELDx6[i]) wertung +=  __STARTPUNKTEx6[i];  //
      +kingzone_ich[i]*10;	//1.17 if (feld[i] == __STARTFELDx7[i]) wertung
      -=  __STARTPUNKTEx7[i]; if (feld[i] == __STARTFELDx8[i]) wertung +=
      __STARTPUNKTEx8[i];  // +kingzone_ich[i]*10;	//1.17 if (feld[i] ==
      __STARTFELDx9[i]) wertung -=  __STARTPUNKTEx9[i];*/
    if (feld[i] == __STARTFELDx10[i])
      wertung += (figurenwert - 4100) * 0.001 *
                 __STARTPUNKTEx10[i]; // +kingzone_ich[i]*10;	//1.17
    if (feld[i] == __STARTFELDx11[i])
      wertung -= (figurenwert - 4100) * 0.001 * __STARTPUNKTEx11[i]; //*/
  }
  return wertung;
}

inline double material(int feld[120], int farbe) {
  double wert = 0;
  int figur;
  // figurenwert_weiss = 0;
  //   figurenwert_schwarz = 0;
  figurenwert = 0;
  for (int j = 21; j < 99; ++j) {
    kingzone[j] = 0;
  }
  for (int i = 21; i <= 98; i++) {
    figur = feld[i];

    if ((figur == RAND) || (figur == LEER))
      continue;
    wert += figur * materialwert[abs(figur)];

    if (abs(figur) != W_K && abs(figur) != W_Kr) {
      //    if (figur>0) figurenwert_weiss += abs(figur) *
      //    materialwert[abs(figur)];
      //   if (figur<0) figurenwert_schwarz += abs(figur) *
      //   materialwert[abs(figur)];
      figurenwert += abs(figur) * materialwert[abs(figur)];
    } //*/

    //	cout << OpenLines[3] << "\n";
    /*	if (abs(figur)<6) {
        if (figur>0)OpenLines_weiss[i%10-1]=0;
        if (figur<0)OpenLines_schwarz[i%10-1]=0; }*/
    //  OpenLines[i%10-1]=0; }//*/

    //	cout << OpenLines[3] << "\n";

    /*	if (figur == W_K||figur == W_Kr)
           {
           kingzone[i+9] = 1;
           kingzone[i+10] = 1;
           kingzone[i+11] = 1;
           /*kingzone[i+19] = 1;
           kingzone[i+20] = 1;
           kingzone[i+21] = 1;*/
    //}//*/
    if (abs(figur) == W_K || abs(figur) == W_Kr) {
      //  cout << "Koenig: " << i << "\n";

      kingzone[i - 9] = figur / abs(figur);
      kingzone[i - 10] = figur / abs(figur);
      kingzone[i - 11] = figur / abs(figur);
      kingzone[i - 1] = figur / abs(figur);
      kingzone[i] = figur / abs(figur);
      kingzone[i + 1] = figur / abs(figur);
      kingzone[i + 9] = figur / abs(figur);
      kingzone[i + 10] = figur / abs(figur);
      kingzone[i + 11] = figur / abs(figur);
    }

    /* kingzone[i-19] = 1;
     kingzone[i-20] = 1;
     kingzone[i-21] = 1;
     }//*/
  }

  return wert;
}

inline int zuganzahl(int feld[120], int _eigene_farbe) { // Zaehlt Zuege von
                                                         // Offizieren und
                                                         // Bauern inclusive
                                                         // Deckung und
                                                         // Schlagen,
  // bei Bauern jedoch kein Schlagen
  // , was auch unterschiedlich gewichtet werden kann
  int pos2;
  int figur;
  int farbvorzeichen;
  int Attack = 0;
  double schlagzone_ich[120] = {0};
  double schlagzone_gegner[120] = {0};
  for (int j = 21; j < 99; ++j) {
    zugzone_ich[j] = 0;
    zugzone_du[j] = 0;
  }

  double n = 0;
  int Anzahl_Angreifer_w = 0;
  int Anzahl_Angreifer_s = 0;
  double Angreifer_Wert_w = 0;
  double Angreifer_Wert_s = 0;
  double K_Safety_Wert = 0; //*/
  // displayfeld);
  for (int i = 21; i <= 98; i++) {
    int C_flag = 0;
    figur = abs(feld[i]);

    if (feld[i] > 0) {
      farbvorzeichen = +1;
    } else {
      farbvorzeichen = -1;
    }

    if ((figur == LEER) || (figur == RAND))
      continue;

    if ((figur == W_D)) {
      int Attack_Dame = 0;

      for (int richtung = 0; richtung <= bewegung[figur][0]; richtung++) {
        for (int weite = 0; weite <= bewegung[figur][1]; weite++) {
          pos2 =
              i + farbvorzeichen * bewegung[figur][2 + richtung] * (weite + 1);
          int zielfeld = feld[pos2];

          /*    for (int richtung = 0; richtung <= bewegung[W_K][0];
             richtung++)
              {
             for (int weite = 0; weite <= bewegung[W_K][1]; weite++) {
             pos2 = i + farbvorzeichen * bewegung[W_K][2+richtung] *
             (weite+1); int zielfeldk = feld[pos2]; if (zielfeld ==
             zielfeldk) n -= 400*farbvorzeichen;return n;}}*/
          if (zielfeld == RAND) // Aus!
            break;

          if (farbvorzeichen == _eigene_farbe)
            zugzone_ich[pos2] += 10;
          else
            zugzone_du[pos2] += 10;
          if (kingzone[pos2] == -farbvorzeichen) {
            if (farbvorzeichen == _eigene_farbe) {
              if (farbvorzeichen == 1) {
                Angreifer_Wert_w += KSafety;
                if (C_flag == 0)
                  Anzahl_Angreifer_w += 1;
              } else {
                Angreifer_Wert_s += KSafety;
                if (C_flag == 0)
                  Anzahl_Angreifer_s += 1;
              };
              C_flag = 1;
            } else {
              if (farbvorzeichen == 1) {
                Angreifer_Wert_w += KSafety * 0.5;
                if (C_flag == 0)
                  Anzahl_Angreifer_w += 1;
              } else {
                Angreifer_Wert_s += KSafety * 0.5;
                if (C_flag == 0)
                  Anzahl_Angreifer_s += 1;
              };
              C_flag = 1;
            }
          }

          // if (Angreifer_Wert_s == 11000) cout << "Dame: " << i <<
          // "\n";
          //      if (kingzone[i] == 1) Attack_Dame += KSafety;

          if (zielfeld != LEER) {
            int zielfigur = abs(zielfeld);

            /*   if (abs(zielfeld) == W_K)
                    break;*/

            if (farbvorzeichen != _eigene_farbe) {
              if (zielfeld / _eigene_farbe >
                  0) { // Gegner greift meine Figur an
                if (schlagzone_gegner[pos2] != 1)
                  schlagzone_gegner[pos2] = 1;
                else
                  Attack_Dame += KooIch;
                //    Attack_Dame += kingzone_ich[pos2] *
                //    Koenigsangriff_Er;

                Attack_Dame +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)] - 40) *
                    AttackIch;

              } else {
                Attack_Dame += DefIch1;

                if (abs(zielfeld) < 6)
                  Attack_Dame -= DefIch2;
              } // Gegner deckt seine Figuren

            } else {
              if (zielfeld / _eigene_farbe < 0) { // Ich greife Gegner an
                if (schlagzone_ich[pos2] != 1)
                  schlagzone_ich[pos2] = 1;
                else
                  Attack_Dame += KooEr;
                //  Attack_Dame += kingzone_gegner[pos2] *
                //  Koenigsangriff_Ich;

                if (zielfigur == W_K || zielfigur == W_Kr)
                  break;
                Attack_Dame +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)]) / AttackEr;
              } else {
                Attack_Dame += DefEr1;

                if (abs(zielfeld) < 6)
                  Attack_Dame -= DefEr2;
              }
            } // Ich decke meine Figuren
            break;
          }
        }
      }
      Attack_Dame *= farbvorzeichen;
      //  cout << MobDame * n_Dame + AttDame * Attack_Dame << "\n";
      n += AttDame * Attack_Dame;
    }

    if ((figur == W_T) || (figur == W_Tr)) {
      int n_Turm = -10;
      int Attack_Turm = 0;

      for (int richtung = 0; richtung <= bewegung[figur][0]; richtung++) {
        for (int weite = 0; weite <= bewegung[figur][1]; weite++) {
          pos2 =
              i + farbvorzeichen * bewegung[figur][2 + richtung] * (weite + 1);
          int zielfeld = feld[pos2];
          if (zielfeld == RAND) // Aus!
            break;
          /*    for (int richtung = 0; richtung <= bewegung[W_K][0];
             richtung++)
              {
             for (int weite = 0; weite <= bewegung[W_K][1]; weite++) {
             pos2 = i + farbvorzeichen * bewegung[W_K][2+richtung] *
             (weite+1); int zielfeldk = feld[pos2]; if (zielfeld ==
             zielfeldk) n -= 400*farbvorzeichen;return n;}}*/
          if (farbvorzeichen == _eigene_farbe)
            zugzone_ich[pos2] += 100;
          else
            zugzone_du[pos2] += 100;
          if (kingzone[pos2] == -farbvorzeichen) {
            if (farbvorzeichen == _eigene_farbe) {
              if (farbvorzeichen == 1) {
                Angreifer_Wert_w += KSafety * K_Angriff_Turm;
                if (C_flag == 0)
                  Anzahl_Angreifer_w += 1;
              } else {
                Angreifer_Wert_s += KSafety * K_Angriff_Turm;
                if (C_flag == 0)
                  Anzahl_Angreifer_s += 1;
              };
              C_flag = 1;
            } else {
              if (farbvorzeichen == 1) {
                Angreifer_Wert_w += KSafety * K_Angriff_Turm * 0.5;
                if (C_flag == 0)
                  Anzahl_Angreifer_w += 1;
              } else {
                Angreifer_Wert_s += KSafety * K_Angriff_Turm * 0.5;
                if (C_flag == 0)
                  Anzahl_Angreifer_s += 1;
              };
              C_flag = 1;
            }
          }

          //     if (kingzone[i] == 1) Attack_Turm += KSafety;
          if (zielfeld != LEER) {
            int zielfigur = abs(zielfeld);

            /*   if (abs(zielfeld) == W_K)
                    break;*/

            if (farbvorzeichen != _eigene_farbe) {
              if (zielfeld / _eigene_farbe > 0) { // Gegner greift meine Figur
                                                  // an
                if (schlagzone_gegner[pos2] != 1)
                  schlagzone_gegner[pos2] = 1;
                else
                  Attack_Turm += KooIch;

                //         Attack_Turm += kingzone_ich[pos2]/* *
                //         Koenigsangriff_Er*/;
                n_Turm += 3;

                if ((n_Turm > 6) && (n_Turm < 11))
                  n_Turm += 2;

                if ((n_Turm > 10) && (n_Turm < 14))
                  n_Turm += 1;

                Attack_Turm +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)] - 40) *
                    AttackIch;
              } else {
                Attack_Turm += DefIch1;

                if (abs(zielfeld) < 6)
                  Attack_Turm -= DefIch2;
              } // Gegner deckt seine Figuren

            } else {
              if (zielfeld / _eigene_farbe < 0) { // Ich greife Gegner an
                if (schlagzone_ich[pos2] != 1)
                  schlagzone_ich[pos2] = 1;
                else
                  Attack_Turm += KooEr;
                //   Attack_Turm += kingzone_gegner[pos2] *
                //   Koenigsangriff_Ich;
                if (n_Turm < 7)
                  n_Turm += 3;

                if ((n_Turm > 6) && (n_Turm < 11))
                  n_Turm += 2;

                if ((n_Turm > 10) && (n_Turm < 14))
                  n_Turm += 1;

                if (zielfigur == W_K || zielfigur == W_Kr)
                  break;
                Attack_Turm +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)]) / AttackEr;
              } else {
                Attack_Turm += DefEr1;

                if (abs(zielfeld) < 6)
                  Attack_Turm -= DefEr2;
              }
            } // Ich decke meine Figuren
            break;
          }

          if (farbvorzeichen != _eigene_farbe) {
            //        Attack_Turm += kingzone_ich[pos2]/* *
            //        Koenigsangriff_Er*/;

            if (n_Turm < 7)
              n_Turm += 3;

            if ((n_Turm > 6) && (n_Turm < 11))
              n_Turm += 2;

            if ((n_Turm > 10) && (n_Turm < 14))
              n_Turm += 1;
          } else {
            //  Attack_Turm += kingzone_gegner[pos2] *
            //  Koenigsangriff_Ich;
            if (n_Turm < 7)
              n_Turm += 3;

            if ((n_Turm > 6) && (n_Turm < 11))
              n_Turm += 2;

            if ((n_Turm > 10) && (n_Turm < 14))
              n_Turm += 1;
          }
        }
      }
      n_Turm *= farbvorzeichen;
      Attack_Turm *= farbvorzeichen;
      n += MobTurm * n_Turm + AttTurm * Attack_Turm;
    }

    if ((figur == W_L)) {
      int n_Laeufer = -15;
      int Attack_Laeufer = 0;

      for (int richtung = 0; richtung <= bewegung[figur][0]; richtung++) {
        for (int weite = 0; weite <= bewegung[figur][1]; weite++) {
          pos2 =
              i + farbvorzeichen * bewegung[figur][2 + richtung] * (weite + 1);
          int zielfeld = feld[pos2];
          if (zielfeld == RAND) // Aus!
            break;
          /*    for (int richtung = 0; richtung <= bewegung[W_K][0];
             richtung++)
              {
             for (int weite = 0; weite <= bewegung[W_K][1]; weite++) {
             pos2 = i + farbvorzeichen * bewegung[W_K][2+richtung] *
             (weite+1); int zielfeldk = feld[pos2]; if (zielfeld ==
             zielfeldk) n -= 400*farbvorzeichen;return n;}}*/
          if (farbvorzeichen == _eigene_farbe)
            zugzone_ich[pos2] += 1000;
          else
            zugzone_du[pos2] += 1000;
          if (kingzone[pos2] == -farbvorzeichen) {
            if (farbvorzeichen == _eigene_farbe) {
              if (farbvorzeichen == 1) {
                Angreifer_Wert_w += KSafety * K_Angriff_Laeufer;
                if (C_flag == 0)
                  Anzahl_Angreifer_w += 1;
              } else {
                Angreifer_Wert_s += KSafety * K_Angriff_Laeufer;
                if (C_flag == 0)
                  Anzahl_Angreifer_s += 1;
              };
              C_flag = 1;
            } else {
              if (farbvorzeichen == 1) {
                Angreifer_Wert_w += KSafety * K_Angriff_Laeufer * 0.5;
                if (C_flag == 0)
                  Anzahl_Angreifer_w += 1;
              } else {
                Angreifer_Wert_s += KSafety * K_Angriff_Laeufer * 0.5;
                if (C_flag == 0)
                  Anzahl_Angreifer_s += 1;
              };
              C_flag = 1;
            }
          }

          //     if (kingzone[i] == 1) Attack_Laeufer += KSafety;
          if (zielfeld != LEER) {
            int zielfigur = abs(zielfeld);

            /*   if (abs(zielfeld) == W_K)
                break;*/

            if (farbvorzeichen != _eigene_farbe) {
              if (zielfeld / _eigene_farbe > 0) { // Gegner greift meine Figur
                                                  // an
                if (schlagzone_gegner[pos2] != 1)
                  schlagzone_gegner[pos2] = 1;
                else
                  Attack_Laeufer += KooIch;
                //           Attack_Laeufer +=
                //           kingzone_ich[pos2]/* *
                //           Koenigsangriff_Er*/;
                if (n_Laeufer == -15)
                  n_Laeufer += 5; // 12

                if ((n_Laeufer > -11) && (n_Laeufer < 10))
                  n_Laeufer += 4;

                if ((n_Laeufer > 9) && (n_Laeufer < 16))
                  n_Laeufer += 3;

                if ((n_Laeufer > 15) && (n_Laeufer < 22))
                  n_Laeufer += 2;

                if (n_Laeufer > 21)
                  n_Laeufer += 1;

                Attack_Laeufer +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)] - 40) *
                    AttackIch;
              } else {
                Attack_Laeufer += DefIch1;

                if (abs(zielfeld) < 6)
                  Attack_Laeufer -= DefIch2;
              } // Gegner
                // deckt
                // seine
                // Figuren
                //    1
            } else {
              if (zielfeld / _eigene_farbe < 0) { // Ich
                                                  // greife
                                                  // Gegner
                                                  // an
                if (schlagzone_ich[pos2] != 1)
                  schlagzone_ich[pos2] = 1;
                else
                  Attack_Laeufer += KooEr;
                //      Attack_Laeufer += kingzone_gegner[pos2]
                //      * Koenigsangriff_Ich;
                if (n_Laeufer == -15)
                  n_Laeufer += 5; // 12

                if ((n_Laeufer > -11) && (n_Laeufer < 10))
                  n_Laeufer += 4;

                if ((n_Laeufer > 9) && (n_Laeufer < 16))
                  n_Laeufer += 3;

                if ((n_Laeufer > 15) && (n_Laeufer < 22))
                  n_Laeufer += 2;

                if (n_Laeufer > 21)
                  n_Laeufer += 1;

                if (zielfigur == W_K || zielfigur == W_Kr)
                  break;
                Attack_Laeufer +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)]) / AttackEr;
              } else {
                Attack_Laeufer += DefEr1;

                if (abs(zielfeld) < 6)
                  Attack_Laeufer -= DefEr2;
              }
            } // Ich decke meine Figuren
            break;
          }

          if (farbvorzeichen != _eigene_farbe) {
            //               Attack_Laeufer += kingzone_ich[pos2]/*
            //               * Koenigsangriff_Er*/;

            if (n_Laeufer == -15)
              n_Laeufer += 5; // 12

            if ((n_Laeufer > -11) && (n_Laeufer < 10))
              n_Laeufer += 4;

            if ((n_Laeufer > 9) && (n_Laeufer < 16))
              n_Laeufer += 3;

            if ((n_Laeufer > 15) && (n_Laeufer < 22))
              n_Laeufer += 2;

            if (n_Laeufer > 21)
              n_Laeufer += 1;
          } else {
            //   Attack_Laeufer += kingzone_gegner[pos2] *
            //   Koenigsangriff_Ich;
            if (n_Laeufer == -15)
              n_Laeufer += 5; // 12

            if ((n_Laeufer > -11) && (n_Laeufer < 10))
              n_Laeufer += 4;

            if ((n_Laeufer > 9) && (n_Laeufer < 16))
              n_Laeufer += 3;

            if ((n_Laeufer > 15) && (n_Laeufer < 22))
              n_Laeufer += 2;

            if (n_Laeufer > 21)
              n_Laeufer += 1;
          }
        }
      }
      n_Laeufer *= farbvorzeichen;
      Attack_Laeufer *= farbvorzeichen;

      n += MobLau * n_Laeufer + AttLau * Attack_Laeufer;
    }

    if ((figur == W_P)) {
      int Attack_Pferd = 0;

      for (int richtung = 0; richtung <= bewegung[figur][0]; richtung++) {
        for (int weite = 0; weite <= bewegung[figur][1]; weite++) {
          pos2 =
              i + farbvorzeichen * bewegung[figur][2 + richtung] * (weite + 1);
          int zielfeld = feld[pos2];
          if (zielfeld == RAND) // Aus!
            break;
          /*    for (int richtung = 0; richtung <= bewegung[W_K][0];
             richtung++)
              {
             for (int weite = 0; weite <= bewegung[W_K][1]; weite++) {
             pos2 = i + farbvorzeichen * bewegung[W_K][2+richtung] *
             (weite+1); int zielfeldk = feld[pos2]; if (zielfeld ==
             zielfeldk) n -= 400*farbvorzeichen;return n;}}*/
          if (farbvorzeichen == _eigene_farbe)
            zugzone_ich[pos2] += 1000;
          else
            zugzone_du[pos2] += 1000;
          if (kingzone[pos2] == -farbvorzeichen) {
            if (farbvorzeichen == _eigene_farbe) {
              if (farbvorzeichen == 1) {
                Angreifer_Wert_w += KSafety * K_Angriff_Springer;
                if (C_flag == 0)
                  Anzahl_Angreifer_w += 1;
              } else {
                Angreifer_Wert_s += KSafety * K_Angriff_Springer;
                if (C_flag == 0)
                  Anzahl_Angreifer_s += 1;
              };
              C_flag = 1;
            } else {
              if (farbvorzeichen == 1) {
                Angreifer_Wert_w += KSafety * K_Angriff_Springer * 0.5;
                if (C_flag == 0)
                  Anzahl_Angreifer_w += 1;
              } else {
                Angreifer_Wert_s += KSafety * K_Angriff_Springer * 0.5;
                if (C_flag == 0)
                  Anzahl_Angreifer_s += 1;
              };
              C_flag = 1;
            }
          }

          //     if (kingzone[i] == 1) Attack_Pferd += KSafety;
          if (zielfeld != LEER) {
            int zielfigur = abs(zielfeld);

            /*   if (abs(zielfeld) == W_K)
                break;*/

            if (farbvorzeichen != _eigene_farbe) {
              if (zielfeld / _eigene_farbe > 0) { // Gegner greift meine Figur
                                                  // an
                if (schlagzone_gegner[pos2] != 1)
                  schlagzone_gegner[pos2] = 1;
                else
                  Attack_Pferd += KooIch;
                //      Attack_Pferd += kingzone_ich[pos2]/* *
                //      Koenigsangriff_Er*/;
                Attack_Pferd +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)] - 40) *
                    AttackIch;
              } else {
                Attack_Pferd += DefIch1;

                if (abs(zielfeld) < 6)
                  Attack_Pferd -= DefIch2;
              } // Gegner deckt seine Figuren 1
            } else {
              if (zielfeld / _eigene_farbe < 0) { // Ich greife Gegner an
                if (schlagzone_ich[pos2] != 1)
                  schlagzone_ich[pos2] = 1;
                else
                  Attack_Pferd += KooEr;

                if (zielfigur == W_K || zielfigur == W_Kr)
                  break;
                //      Attack_Pferd += kingzone_gegner[pos2] *
                //      Koenigsangriff_Ich;
                Attack_Pferd +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)]) / AttackEr;
              } else {
                Attack_Pferd += DefEr1;

                if (abs(zielfeld) < 6)
                  Attack_Pferd -= DefEr2;
              }
            } // Ich decke meine Figuren
            break;
          }

          /*    if (farbvorzeichen != _eigene_farbe)  {
              //        Attack_Pferd += kingzone_ich[pos2]/* *
             Koenigsangriff_Er*/
          ;

          //  }
          //  else  {
          //   Attack_Pferd += kingzone_gegner[pos2] *
          //   Koenigsangriff_Ich;
          //   }//*/
        }
      }
      Attack_Pferd *= farbvorzeichen;

      n += AttSpr * Attack_Pferd;
    }

    if (((figur == W_B) || (figur == W_Bx))) {
      int Attack_Bauer = 0;
      /*   if (farbvorzeichen == 1)
                  {if (OpenLines_weiss[i%10-2] == 1 &&
         OpenLines_weiss[i%10] == 1) Attack_Bauer -= 200;} else {if
         (OpenLines_schwarz[i%10-2] == 1 && OpenLines_schwarz[i%10] == 1)
         Attack_Bauer -= 200;}*/
      // if (feld[i+1] == feld[i]) n += 200;
      for (int richtung = 0; richtung <= bewegung[13][0]; richtung++) {
        for (int weite = 0; weite <= bewegung[13][1]; weite++) {
          pos2 = i + farbvorzeichen * bewegung[13][2 + richtung] * (weite + 1);
          int zielfeld = feld[pos2];
          if (zielfeld == RAND) // Aus!
            break;
          /*    for (int richtung = 0; richtung <= bewegung[W_K][0];
             richtung++)
              {
             for (int weite = 0; weite <= bewegung[W_K][1]; weite++) {
             pos2 = i + farbvorzeichen * bewegung[W_K][2+richtung] *
             (weite+1); int zielfeldk = feld[pos2]; if (zielfeld ==
             zielfeldk) n -= 400*farbvorzeichen;return n;}}_*/
          //    if (kingzone[pos2] == -farbvorzeichen &&
          //    farbvorzeichen == _eigene_farbe) {if (farbvorzeichen
          //    == 1) {Angreifer_Wert_w += KSafety*K_Angriff_Bauer; if
          //    (C_flag == 0) Anzahl_Angreifer_w += 1;} else
          //    {Angreifer_Wert_s += KSafety*K_Angriff_Bauer; if
          //    (C_flag == 0) Anzahl_Angreifer_s += 1;}; C_flag = 1;}
          //   if (kingzone[pos2] == -farbvorzeichen && farbvorzeichen
          //   != _eigene_farbe) {if (farbvorzeichen == 1)
          //   {Angreifer_Wert_w += KSafety*K_Angriff_Bauer*0.2; if
          //   (C_flag == 0) Anzahl_Angreifer_w
          //   += 1;} else {Angreifer_Wert_s +=
          //   KSafety*K_Angriff_Bauer; if (C_flag == 0)
          //   Anzahl_Angreifer_s += 1;}; C_flag = 1;}
          //       if (kingzone[i] == 1) Attack_Bauer += KSafety;
          if (farbvorzeichen == _eigene_farbe)
            zugzone_ich[pos2] += 10000;
          else
            zugzone_du[pos2] += 10000;
          if (zielfeld != LEER) {
            int zielfigur = abs(zielfeld);

            /*   if (abs(zielfeld) == W_K)
                    break;*/
            if (farbvorzeichen != _eigene_farbe) {
              if (zielfeld / _eigene_farbe > 0) { // Gegner greift meine Figur
                                                  // an
                if (schlagzone_gegner[pos2] != 1)
                  schlagzone_gegner[pos2] = 1;
                else
                  Attack_Bauer += KooIch;
                //         Attack_Bauer += kingzone_ich[pos2]/*
                //         * Koenigsangriff_Er*/;
                Attack_Bauer +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)] - 40) *
                    AttackIch;
              } else {
                Attack_Bauer += DefIch1 / 2;
                //         if (abs(zielfeld) < 6) Attack_Bauer
                //         -= DefIch2;
              } // Gegner deckt seine Figuren
                //    1
            } else {
              if (zielfeld / _eigene_farbe < 0) { // Ich greife Gegner an
                if (schlagzone_ich[pos2] != 1)
                  schlagzone_ich[pos2] = 1;
                else
                  Attack_Bauer += KooEr;

                if (zielfigur == W_K || zielfigur == W_Kr)
                  break;
                //        Attack_Bauer += kingzone_gegner[pos2]
                //        * Koenigsangriff_Ich;
                Attack_Bauer +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)]) / AttackEr;
              } else {
                Attack_Bauer += DefEr1 / 2;
                //         if (abs(zielfeld) < 6) Attack_Bauer
                //         -= DefIch2;
              }
            } // Ich decke meine Figuren
            break;
          }

          //   if (farbvorzeichen != _eigene_farbe)  {
          //         Attack_Bauer += kingzone_ich[pos2]/* *
          //         Koenigsangriff_Er*/;

          //   }
          //   else  {
          //  Attack_Bauer += kingzone_gegner[pos2] *
          //  Koenigsangriff_Ich;
          //   }//*/
        }
      }
      Attack_Bauer *= farbvorzeichen;

      n += AttBau * Attack_Bauer;
    }

    if (((figur == W_K) || (figur == W_Kr))) {
      int Attack_Koenig = 0;
      //  int KSafety = 0;

      for (int richtung = 0; richtung <= bewegung[figur][0]; richtung++) {
        for (int weite = 0; weite <= bewegung[figur][1]; weite++) {
          pos2 =
              i + farbvorzeichen * bewegung[figur][2 + richtung] * (weite + 1);
          int zielfeld = feld[pos2];
          //   if (feld[i + 9 * farbvorzeichen] !=
          //   W_Bx*farbvorzeichen) KSafety
          //   -= KSafe*(figurenwert - 3000)*farbvorzeichen; if
          //   (feld[i + 9 * farbvorzeichen] != W_Bx*farbvorzeichen)
          //   KSafety -= KSafe*(figurenwert - 3000)*farbvorzeichen;
          //   if (feld[i + 9 * farbvorzeichen] !=
          //   W_Bx*farbvorzeichen) KSafety -= KSafe*(figurenwert -
          //   3000)*farbvorzeichen; KSafety -= (i - 48) *
          //   (figurenwert - 4000) * farbvorzeichen;
          /*    for (int richtung = 0; richtung <= bewegung[W_K][0];
             richtung++)
              {
             for (int weite = 0; weite <= bewegung[W_K][1]; weite++) {
             pos2 = i + farbvorzeichen * bewegung[W_K][2+richtung] *
             (weite+1); int zielfeldk = feld[pos2]; if (zielfeld ==
             zielfeldk) n -= 400*farbvorzeichen;return n;}}*/
          if (zielfeld == RAND) // Aus!
            break;
          if (farbvorzeichen == _eigene_farbe)
            zugzone_ich[pos2] += 1;
          else
            zugzone_du[pos2] += 1;
          if (zielfeld != LEER) {
            int zielfigur = abs(zielfeld);

            /*   if (abs(zielfeld) == W_K)
                       break;*/
            if (farbvorzeichen != _eigene_farbe) {

              /*if (OpenLines[i%10-2] == 1) KSafety -= 550;
                          if (OpenLines[i%10] == 1) KSafety -=
                 550; if (OpenLines[i%10-1] == 1) KSafety -=
                 550;//*/
              if (zielfeld / _eigene_farbe >
                  0) { // Gegner greift meine Figur an
                if (schlagzone_gegner[pos2] != 1)
                  schlagzone_gegner[pos2] = 1;
                else
                  Attack_Koenig += KooIch;
                //    Attack_Koenig += kingzone_ich[pos2]/* *
                //    Koenigsangriff_Er*/;
                Attack_Koenig +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)] - 40) *
                    AttackIch;
              } else {
                Attack_Koenig += DefIch1; /*if (abs(zielfeld)<6)
                                             Attack_Koenig
                                             += figurenwert/2;*/
              }
              // Gegner deckt seine Figuren    1
            } else {
              if (zielfeld / _eigene_farbe < 0) { // Ich greife Gegner an
                if (schlagzone_ich[pos2] != 1)
                  schlagzone_ich[pos2] = 1;
                else
                  Attack_Koenig += KooEr;

                if (zielfigur == W_K)
                  break;
                //      Attack_Koenig += kingzone_gegner[pos2] *
                //      Koenigsangriff_Ich;
                Attack_Koenig +=
                    (abs(zielfeld) * materialwert[abs(zielfeld)]) / AttackEr;
              } else {
                Attack_Koenig += DefEr1; /*if (abs(zielfeld)<6) Attack_Koenig
                                            += figurenwert/2;*/
              }

            } // Ich decke meine Figuren
            break;
          }

          /*    if (farbvorzeichen ==1)
                     {
                          if (OpenLines_weiss[i%10-2] == 1)
             Attack_Koenig -= figurenwert/2; if (OpenLines_weiss[i%10]
             == 1) Attack_Koenig -= figurenwert/2; if
             (OpenLines_weiss[i%10-1] == 1) Attack_Koenig -=
             figurenwert/2;}//*/

          /*   else  {
          //     Attack_Koenig += kingzone_gegner[pos2] *
          Koenigsangriff_Ich; if (OpenLines_schwarz[i%10-2] == 1)
          Attack_Koenig -= figurenwert/2; if (OpenLines_schwarz[i%10]
          == 1) Attack_Koenig -= figurenwert/2; if
          (OpenLines_schwarz[i%10-1] == 1) Attack_Koenig -=
          figurenwert/2;//*/
          //   }//
        }
      }
      Attack_Koenig *= farbvorzeichen;

      n += AttKoe * Attack_Koenig /* + KSafety*/; // + KSafety;
    }
  }
  K_Safety_Wert =
      Angreifer_Wert_w * (100 - 100 / (pow(2, (Anzahl_Angreifer_w - 1)))) /
          100 -
      Angreifer_Wert_s * (100 - 100 / (pow(2, (Anzahl_Angreifer_s - 1)))) / 100;

  n += K_Safety_Wert;
  int Koordination_ich = 0;
  int Koordination_du = 0;

  for (int i = 21; i < 99; i++) {
    if (zugzone_ich[i] > zugzone_du[i]) {
      if ((zugzone_ich[i + 1] > zugzone_du[i + 1]) ||
          (zugzone_ich[i - 1] > zugzone_du[i - 1]) ||
          (zugzone_ich[i + 10] > zugzone_du[i + 10]) ||
          (zugzone_ich[i - 10] > zugzone_du[i - 10]))
        Koordination_ich += 1;
      if ((zugzone_ich[i + 1] == zugzone_du[i + 1]) ||
          (zugzone_ich[i - 1] == zugzone_du[i - 1]) ||
          (zugzone_ich[i + 10] == zugzone_du[i + 10]) ||
          (zugzone_ich[i - 10] == zugzone_du[i - 10]))
        Koordination_ich += 0.5;
    }
    if (zugzone_du[i] > zugzone_ich[i]) {
      if ((zugzone_du[i + 1] > zugzone_ich[i + 1]) ||
          (zugzone_du[i - 1] > zugzone_ich[i - 1]) ||
          (zugzone_du[i + 10] > zugzone_ich[i + 10]) ||
          (zugzone_du[i - 10] > zugzone_ich[i - 10]))
        Koordination_du += 1;
      if ((zugzone_du[i + 1] == zugzone_ich[i + 1]) ||
          (zugzone_du[i - 1] == zugzone_ich[i - 1]) ||
          (zugzone_du[i + 10] == zugzone_ich[i + 10]) ||
          (zugzone_du[i - 10] == zugzone_ich[i - 10]))
        Koordination_du += 0.5;
    }
  }

  //   if (Raumzaehler_ich > Raumzaehler_du) {n += (Raumzaehler_ich /
  //   Raumzaehler_du * _eigene_farbe-1)*6; } if (Raumzaehler_du >
  //   Raumzaehler_ich) {n += (Raumzaehler_du / Raumzaehler_ich *
  //   -_eigene_farbe-1)*6; }

  n += (Koordination_ich - Koordination_du) * _eigene_farbe * 45;
  return n;
}

int sort(denkpaar _zugstapel[200], int _n, int _stufe,
         int _i) { // Sortiert Zugstapel neu nach Schema
  int zid;
  int m = _i; // Wieviele Z¬∏ge sind umsortiert?
  int best_wert = 0;
  denkpaar temp;

  for (int j = _i; j < _n; ++j) {
    _zugstapel[j].order +=
        historyMoves[_zugstapel[j].z.pos.pos1][_zugstapel[j].z.pos.pos2] *
        0.005;
    // if (historyMoves[_zugstapel[j].z.pos.pos1][_zugstapel[j].z.pos.pos2]
    // >= 100) cout <<
    // historyMoves[_zugstapel[j].z.pos.pos1][_zugstapel[j].z.pos.pos2] <<
    // "\n";
    if (_zugstapel[j].z.id == best_one[_stufe].z.id)
      _zugstapel[j].order += 225;

    if (_zugstapel[j].order > best_wert /*|| historyMoves[_zugstapel[j].z.pos.pos1][_zugstapel[j].z.pos.pos2] > best_wert*/) {
      best_wert = _zugstapel[j].order;

      temp = _zugstapel[j]; // Vertausche den Zug
      _zugstapel[j] = _zugstapel[m];
      _zugstapel[m] = temp;
      // m++;
      //  break; // und weiter...
    }
  }

  return 0;
}

#endif