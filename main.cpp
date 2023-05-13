#include "basis.cpp"
#include "bp.cpp"
#include "io_util.h"
#include "moves.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Log.h"
#include <algorithm>
#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <time.h>
#include <unistd.h>

using namespace std;

string read_file_str(string filename) {
  fstream f(filename, fstream::in);
  string s;
  getline(f, s, '\0');
  f.close();
  return s;
}

const char *fen_char[] = { // bei writ()
    "S_Tr",   "S_Kr",   "S_K",    "S_D",    "S_T",  "S_L",  "S_P",
    "S_B",    "S_Bu",   "S_Bp_r", "S_Bp_l", "S_Bx", "LEER", "W_Bx",
    "W_Bp_l", "W_Bp_r", "W_Bu",   "W_B",    "W_P",  "W_L",  "W_T",
    "W_D",    "W_K",    "W_Kr",   "W_Tr",   "RAND"};


template <class T, size_t N> constexpr size_t size(T (&)[N]) { return N; }

int main(int argc, char **argv) {
  plog::init(plog::debug, "log/nexus.log");
  LOGD << "Start";

  int index;
  char *fvalue = NULL;
  string svalue;
  int ladefeld[120] = {RAND};
  opterr = 0;
  vector<string> zuege;
  std::regex rgx_feld("(\\.|[A-Za-y]{3})");
  std::smatch matches;
  string s;
  int c;
  int ii = 0;
  int pos = 0;
  int figur;
  bool geladen = false;
  bool play_alone = false;
  bool _user = false;
  feldtyp *xbrettchen = new feldtyp;
  denkpaar *xzugstapel = new denkpaar[200];

  bool exit = false;
  int pos1;
  int pos2;
  int wert;
  int zug_nummer = 1;
  timeline = 0;
  time_t t1, t2, t0;

  // Kommandozeilenargumente

  while ((c = getopt(argc, argv, "aus:f:")) != -1)
    switch (c) {
    case 'f': { // Farbe setzen
      fvalue = optarg;
      eigene_farbe = atoi(fvalue);
    } break;
    case 'u': { // User modus
      _user = true;
    } break;
    case 'a': { // play_alone mit sich spielen
      play_alone = true;
    } break;

    case 's': { 
  
      *grundfeld = *ladefeld;
      svalue = optarg;
      cout << svalue;
      s = read_file_str(svalue);
      cout << "|" << s << "|";

      cout << s;
      for (std::sregex_iterator i =
               std::sregex_iterator(s.begin(), s.end(), rgx_feld);
           // Figuren finden
           i != std::sregex_iterator(); ++i) {
        cout << "@";
        std::smatch m = *i;
        int x = std::distance(
            figuren_char,
            std::find(figuren_char, figuren_char + 27, m[1].str()));
        cout << ii << ":" << x << " " << flush;

        pos = 120 - (21 + ((int)(ii) / 8) * 10 + 8 - ii % 8);

        figur = x - figurenanzahl;

        grundfeld[pos] = x - figurenanzahl;

        ii++;
      }
      cout << " geladenes Spielfeld: \n";
      display(grundfeld);
      geladen = true;
    } break;
    case '?':
      if (optopt == 'c')
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
      return 1;
    default:
      abort();
    }

  {
    for (int i = 0; i < ende + 2; i++) {
      testbrett[i] = new feldtyp;
      testspiel[i] = new Spielfeld();
    }
  }

  Spielfeld spiel(grundfeld, +1, 0);

  spiel.to_feldtyp(xbrettchen);

  // UCI Protokoll
  if (!_user)
    do {

      string command;
      cin >> command;

      PLOGI << command;


    beginning:

      if (command == "-user") {
        status = user;
        break;
      }
      if (command == "-show") {
        spiel.display();
      }
      if (command == "-show_csv") {
        spiel.disp_cleanest();
      }

      if (command == "uci") {
        cout << "id name NEXUS 221014 NeuNull\n"; // 750250 6000
        cout << "id author Albrecht Fiebiger & Stefan Werner\n";
        cout << "uciok\n";
      }

      if (command == "isready") {
        cout << "readyok\n";
      }
      if (command == "quit") {
        return 0;
      }

      // Spielkommandos...
      if (command == "position") {
        cin >> command;

        if (command == "startpos") {
          spiel.setPos(grundfeld, +1, 0, zuege);
          zug_nummer = 1;

          cin >> command;

          if (command == "moves") {
            PLOGI << "MOVE";
            while (true) {
              cin >> command;

              PLOGI << command << " turn " << spiel.Farbe << flush << "\n";

              denkpaar _zug;
              int i;
              int j;
              for (i = 0; i <= 7; i++) {
                if ((command[0] == buchstaben1[i]) ||
                    (command[0] == buchstaben2[i])) {
                  for (j = 0; j <= 7; j++) {
                    if (command[1] == zahlen[j]) {
                      _zug.z.pos.pos1 = 21 + j * 10 + i;
                    }
                  }
                }
              }
              for (i = 0; i <= 7; i++) {
                if ((command[2] == buchstaben1[i]) ||
                    (command[2] == buchstaben2[i])) {
                  for (j = 0; j <= 7; j++) {
                    if (command[3] == zahlen[j]) {
                      _zug.z.pos.pos2 = 21 + j * 10 + i;
                    }
                  }
                }
              }

              spiel.makeZugstapel();
              bool falsch = true;
              for (i = 0; i < spiel.n; i++) {
                if ((zugstapel[spiel.Stufe][i].z.id == _zug.z.id)) {
                  spiel.realer_zug(zugstapel[spiel.Stufe][i], zuege);

                  spiel.zug_reset();
                  _zug = zugstapel[spiel.Stufe][i];

                  falsch = false;
                  break;
                }
              }

              if (falsch == true)
                goto beginning; 
              zug_nummer += 1;
            }
          }
        }
      }

      int Restzeit = 40000000;
      int Restzeit_W = 4000000;
      int Restzeit_S = 4000000;

      if (command == "movetime") {

        cin >> Restzeit;
        cin >> command;
      }

      if (command == "wtime") {

        cin >> Restzeit_W;
        cin >> command;
      }

      if (command == "btime") {
        cin >> Restzeit_S;
      }

      if (spiel.Farbe == 1) {
        Restzeit = Restzeit_W;
      } else
        Restzeit = Restzeit_S;

      if (command == "go") {

        t1 = clock();
        spiel.setStufe(0);
        for (int i = 21; i < 99; i++) {
          for (int j = 21; j < 99; j++) {
            historyMoves[i][j] = 0;
          }
        }

        for (int _stopp = 1;; _stopp++) {

          wert = bp(spiel, spiel.Farbe, -MAX_WERT, MAX_WERT, 0, _stopp, 1);

          int Zeitfaktor = 1;
          if (zug_nummer <= 120)
            Zeitfaktor = 60 - zug_nummer / 4;
          else
            Zeitfaktor = 30;

          if ((clock() - t1) * 1.5 >= Restzeit / Zeitfaktor) {
            stopp_tatsaechlich = _stopp;
            break;
          }
        }

        t2 = clock();
        timeline = (double)(timeline * (zug_nummer - 1) / zug_nummer +
                            (t2 - t1) / zug_nummer);
        int spez;
        denkpaar *zugstapel = new denkpaar[200];

        exit = true;
        switch (spiel.check_end(zuege)) {
        case matt: {
          cout << "looser\n";
          break;
        }
        case patt: {
          cout << "patt\n";
          break;
        }
        case remis: {
          cout << "stalemate\n";
          break;
        }
        case schachmatt: {
          cout << "hero\n";
          break;
        }
        case nothing: {
          exit = false;
          break;
        }
        default: {
          cout << "unknown end";
          break;
        }
        }

        cout << "info depth " << stopp_tatsaechlich << " score cp "
             << wert / 1.5 << " pv "
             << grundfeld_bezeichnungen[bester_zug[0].z.pos.pos1]
             << grundfeld_bezeichnungen[bester_zug[0].z.pos.pos2] << " "
             << grundfeld_bezeichnungen[bester_zug[1].z.pos.pos1]
             << grundfeld_bezeichnungen[bester_zug[1].z.pos.pos2] << " "
             << grundfeld_bezeichnungen[bester_zug[2].z.pos.pos1]
             << grundfeld_bezeichnungen[bester_zug[2].z.pos.pos2] << " "
             << grundfeld_bezeichnungen[bester_zug[3].z.pos.pos1]
             << grundfeld_bezeichnungen[bester_zug[3].z.pos.pos2] << " "
             << grundfeld_bezeichnungen[bester_zug[4].z.pos.pos1]
             << grundfeld_bezeichnungen[bester_zug[4].z.pos.pos2] << "\n";
        cout << "bestmove " << grundfeld_bezeichnungen[bester_zug[0].z.pos.pos1]
             << grundfeld_bezeichnungen[bester_zug[0].z.pos.pos2] << "\n";

        zug_nummer += 1;
      }
    } while (true);

  // user mode

  do {
    display(spiel.to_feld());

    if (!((zug_nummer == 1) && (eigene_farbe == 1))) { // user move
      bool ok = false;
      do {
        if (play_alone) {
          eigene_farbe *= -1;
          break;
        }
        denkpaar *zugstapel = new denkpaar[200];
        int spez;
        int n = spiel.zuggenerator();

        cout << "Zug " << zug_nummer << ", von ";
        pos1 = eingabe();
        if (pos1 == 666 || pos2 == 666) {
          eigene_farbe *= -1;
          break;
        }
        cout << "nach ";
        pos2 = eingabe();

        if (pos1 == 666 || pos2 == 666) {
          eigene_farbe *= -1;
          break;
        }

        for (int i = 0; i < n; i++) {
          if ((zugstapel[i].z.pos.pos1 == pos1) &&
              (zugstapel[i].z.pos.pos2 == pos2)) {
            ok = true;
            spiel.realer_zug(zugstapel[i], zuege);

            spiel.zug_reset();
            break;
          }
        }
        if (ok == false)
          cout << "\nwrong input. retry\n";
        delete[] zugstapel;
      } while (!ok);
    }

    bewertet = 0;
    t1 = clock();

    spiel.setStufe(0);

    for (int _stopp = 1;; _stopp++) {

      cout << "Suchtiefe " << _stopp << "\n";


      wert = bp(spiel, spiel.Farbe, -MAX_WERT, MAX_WERT, 0, _stopp, 1);
      
      if ((clock() - t1 >= 300) && (_stopp >= stopp))
        break;
    }

    t2 = clock();
    timeline = (double)(timeline * (zug_nummer - 1) / zug_nummer +
                        (t2 - t1) / zug_nummer);
    int spez;
    denkpaar *zugstapel = new denkpaar[200];

    cout << "\nmove " << (double)zug_nummer / 2 << ": "
         << ((spiel.Farbe > 0) ? "white" : "black") << ", "
         << "time " << (double)(t2 - t1) / CLOCKS_PER_SEC << "s, "
         << "average " << (double)(timeline) / CLOCKS_PER_SEC << "s, "
         << "total " << (double)(clock() - t0) / CLOCKS_PER_SEC << "s, "
         << "evaluations " << bewertet << "\n";

    cout << "result     " << grundfeld_bezeichnungen[bester_zug[0].z.pos.pos1]
         << " => " << grundfeld_bezeichnungen[bester_zug[0].z.pos.pos2] << "\n";

    spiel.realer_zug(bester_zug[0], zuege);

    exit = true;
    switch (spiel.check_end(zuege)) {
    case matt: {
      cout << "looser\n";
      break;
    }
    case patt: {
      cout << "nn = " << spiel.nn;
      cout << "patt\n";
      break;
    }
    case remis: {
      cout << "stalemate\n";
      break;
    }
    case schachmatt: {
      cout << "hero/n";
      break;
    }
    case nothing: {
      exit = false;
      break;
    }
    default: {
      cout << "unknown end";
      break;
    }
    }

    spiel.zug_reset();
    zug_nummer++;

  } while (!exit);

  return 0;
}
