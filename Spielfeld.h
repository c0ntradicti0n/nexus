#ifndef MY_PROJECT_SPIELFELD_H
#define MY_PROJECT_SPIELFELD_H
#include "chess_types.h"
#include "consts.h"
#include "surge/src/position.h"
#include "surge/src/tables.h"
#include "surge/src/types.h"
using namespace std;

class Spielfeld {

public:
  int zuggenerator();
  inline void add_zug(const int &pos1, const int &pos2, const int &n,
                      const bool &_kill, const int &_figur, const double &order,
                      const bool &castling = false, const bool &enpassant = false);
  inline void add_verwandelung(const int &farbe, const int &pos, const int &was,
                               const int &n);
  inline bool test_drohung(int feld[], int farbe, int pos);
  inline howitends check_end(vector<string> &_zuege);
  inline howitends last_moves();

  int convert_piece(char piece);
  void read_fen(std::string fen);
  inline std::string to_fen();
  template <Color Us> MoveList<Us> move_gen();

  int move_number = 0;
  int n;
  int nn;
  int valid_n;
  bool Z;
  int Stufe;
  int Farbe;
  int spezial;
  int wking = 99;
  int bking = 99;
  int test = 0;

  Spielfeld();
  Spielfeld(int _feld[120], int _farbe, int _stufe);
  void zug_reset();

  // Spielfeld (Spielfeld & spiel);
  feldtyp *to_feldtyp(feldtyp *neues);
  feldtyp *to_feldtyp();
  int *to_feld(int _feld[120]);
  int *to_feld();
  void copy(Spielfeld &_spiel);

  void setFarbe(int _farbe);

  int getStufe();
  void setStufe(int i);

  bool look_richtung_td(const int feld[], const int &farbe, const int &pos,
                        const int &step);
  bool look_richtung_ld(const int feld[], const int &farbe, const int &pos,
                        const int &step);

  void find_kings();

  void setPos(int _feld[120], int _farbe, int _stufe, vector<string> &_zuege);
  string hash();

  void display();
  void disp_cleanest();
  void write();
  void print_zugstapel();
  denkpaar *makeZugstapel();

  void zug(denkpaar &);
  void realer_zug(denkpaar &, vector<string> &_zuege);
};
#endif // MY_PROJECT_SPIELFELD_H
