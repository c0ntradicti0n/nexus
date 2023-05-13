#include <gtest/gtest.h>
#include <bp.cpp>





TEST(Plan, BasicAssertions) {
  Spielfeld spiel = Spielfeld(grundfeld);
  int depth = 4;
  spiel.read_fen("5rk1/2p1npp1/1p1q4/3p1b1p/5b1P/3n1P2/6K1/r7");
  int res = bp(spiel,   spiel.Farbe, -MAX_WERT, MAX_WERT, 0, depth, 1);
        cout << "\nbestmove " << grundfeld_bezeichnungen[bester_zug[0].z.pos.pos1]
             << grundfeld_bezeichnungen[bester_zug[0].z.pos.pos2] << "\n";
   EXPECT_EQ(2, 1);
   //EXPECT_EQ("e2e4", strcat(const_cast<char*> (grundfeld_bezeichnungen[bester_zug[0].z.pos.pos1]), grundfeld_bezeichnungen[bester_zug[0].z.pos.pos2]));
}
