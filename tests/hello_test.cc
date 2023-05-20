#include <bp.cpp>
#include <gtest/gtest.h>

#include <bp.cpp>
#include <gtest/gtest.h>

TEST(FEN, BasicAssertions) {
  Spielfeld spiel = Spielfeld(grundfeld);
  auto test_fen = "4k2r/1QP5/4p3/3p1p2/6Rp/2q1P2P/P4PK1/8 w - - 0 47";
  spiel.disp_cleanest();
  spiel.read_fen(test_fen);
  auto assert_fen = spiel.to_fen();
  EXPECT_STRCASEEQ(assert_fen.c_str(), test_fen);
}


TEST(FEN_EN_PASSANT_W_Br, BasicAssertions) {
  Spielfeld spiel = Spielfeld(grundfeld);

  string test_fen =
      "4k3/8/8/3Pp3/8/8/8/4K3 w - e6 0 1";
  string expect_fen =
      "4k3/8/8/3Pp3/8/8/8/4K3 w - e6 0 1";

  spiel.read_fen(test_fen);
  auto assert_fen = spiel.to_fen();
  spiel.display();

  EXPECT_STRCASEEQ(assert_fen.c_str(), expect_fen.c_str());
}
TEST(FEN_EN_PASSANT_W_Bl, BasicAssertions) {
  Spielfeld spiel = Spielfeld(grundfeld);

  string test_fen =
      "4k3/8/8/3pP3/8/8/8/4K3 w - d6 0 1";
  string expect_fen =
      "4k3/8/8/3pP3/8/8/8/4K3 w - d6 0 1";

  spiel.read_fen(test_fen);
  auto assert_fen = spiel.to_fen();
  spiel.display();

  EXPECT_STRCASEEQ(assert_fen.c_str(), expect_fen.c_str());
}
TEST(FEN_EN_PASSANT_S_Br, BasicAssertions) {
  Spielfeld spiel = Spielfeld(grundfeld);

  string test_fen =
      "4k3/8/8/8/3Pp3/8/8/4K3 w - d3 0 1";
  string expect_fen =
      "4k3/8/8/8/3Pp3/8/8/4K3 w - d3 0 1";

  spiel.read_fen(test_fen);
    spiel.display();

  auto assert_fen = spiel.to_fen();

  EXPECT_STRCASEEQ(assert_fen.c_str(), expect_fen.c_str());
}
TEST(FEN_EN_PASSANT_S_Bl, BasicAssertions) {
  Spielfeld spiel = Spielfeld(grundfeld);

  string test_fen =
      "4k3/8/8/8/3pP3/8/8/4K3 w - e3 0 1";
  string expect_fen =
      "4k3/8/8/8/3pP3/8/8/4K3 w - e3 0 1";

  spiel.read_fen(test_fen);
    spiel.display();

  auto assert_fen = spiel.to_fen();

  EXPECT_STRCASEEQ(assert_fen.c_str(), expect_fen.c_str());
}



TEST(EN_PASSANT_MOVE, BasicAssertions) {
  try
  {
    /* code */

  
  cout << "EN_PASSANT_MOVE1" << endl;
  Spielfeld spiel = Spielfeld(grundfeld);
  cout << "EN_PASSANT_MOVE2" << endl;

  string test_fen =
      "4k3/8/8/3Pp3/8/8/8/4K3 w - e6 0 1";

  spiel.read_fen(test_fen);
    cout << "EN_PASSANT_MOVE3" << endl;

  spiel.makeZugstapel();
    cout << "EN_PASSANT_MOVE4" << endl;

  string expect_fen =
      "4k3/8/8/3Pp3/8/8/8/4K3 w - e6 0 1";

  spiel.read_fen(test_fen);

  MoveList<WHITE> move_list = spiel.move_gen<WHITE>();
   int  valid_n_ =
        filterZugstapelByMoveList<WHITE>(move_list, zugstapel[spiel.Stufe], spiel.n);
    for (auto move : move_list) {
      cout << "-" << move << endl;
    }
  auto assert_fen = spiel.to_fen();
  spiel.display();
  EXPECT_STRCASEEQ(assert_fen.c_str(), expect_fen.c_str());
    }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    throw e;
  }
}


TEST(STOP_FEN, BasicAssertions) {
  Spielfeld spiel = Spielfeld(grundfeld);

  string test_fen =
      "r1bqkbnr/p4ppp/2p1p3/1p1pP3/3P4/P1NB1N2/1PQ2PPP/R1B1K2R b KQkq - 1 8";
  spiel.read_fen(test_fen);
  auto assert_fen = spiel.to_fen();
  spiel.display();

  EXPECT_STRCASEEQ(assert_fen.c_str(), test_fen.c_str());
}

TEST(STOP_FEN_1, BasicAssertions) {
  Spielfeld spiel = Spielfeld(grundfeld);

  string test_fen =
      "4k3/8/8/3Pp3/8/8/8/4K3 w - e6 0 1";
  string expect_fen =
      "4k3/8/8/3Pp3/8/8/8/4K3 w - e6 0 1";

  spiel.read_fen(test_fen);
  auto assert_fen = spiel.to_fen();
  spiel.display();

  EXPECT_STRCASEEQ(assert_fen.c_str(), expect_fen.c_str());
}

TEST(ILLEGAL_FEN_2, BasicAssertions) {
  Spielfeld spiel = Spielfeld(grundfeld);

  string test_fen =
      "B1bqkb1r/p1p2p1p/1p2pnp1/3pN3/3P4/2N1P2P/PPP2PP1/R1BQ1RK1 b - - 4 10";
  string expect_fen =
      "B1bqkb1r/p1p2p1p/1p2pnp1/3pN3/3P4/2N1P2P/PPP2PP1/R1BQ1RK1 b - - 1 10";

  spiel.read_fen(test_fen);
  auto assert_fen = spiel.to_fen();
  spiel.display();

  EXPECT_STRCASEEQ(assert_fen.c_str(), expect_fen.c_str());
}

TEST(ILLEGAL_FEN_4, BasicAssertions) {
  Spielfeld spiel = Spielfeld(grundfeld);
  {
    for (int i = 0; i < ende + 2; i++) {
      testbrett[i] = new feldtyp;
      testspiel[i] = new Spielfeld();
    }
  }

  string test_fen =
      "8/2k1P3/5PK1/8/6P1/2p3P1/5r2/8 w - - 0 69";
  string expect_fen =
      "8/2k1P3/5PK1/8/6P1/2p3P1/5r2/8 w - - 0 69";

  spiel.read_fen(test_fen);
  auto assert_fen = spiel.to_fen();
  spiel.display();

  EXPECT_STRCASEEQ(assert_fen.c_str(), expect_fen.c_str());

    MoveList<WHITE> move_list = spiel.move_gen<WHITE>();
   int  valid_n_ =
        filterZugstapelByMoveList<WHITE>(move_list, zugstapel[spiel.Stufe], spiel.n);
    for (auto move : move_list) {
      cout << "-" << move << endl;
    }

  int wert = bp(spiel, spiel.Farbe, -MAX_WERT, MAX_WERT, 0, 5, 1);
  EXPECT_EQ(wert, -10);
  std::string pivot(grundfeld_bezeichnungen[bester_zug[0].z.pos.pos1]);
pivot.append(grundfeld_bezeichnungen[bester_zug[0].z.pos.pos2] );
pivot.push_back(pieceToFen[bester_zug[0].verwandelung[0].fig]);
spiel.display();
  EXPECT_STREQ(pivot.c_str(), "e7e8Q");
}


// 8/1P1K1p2/7p/8/5k2/P7/6p1/2R5 w - - 0 69
//'illegal uci: ''e7e8'' in 8/2k1P3/5PK1/8/6P1/2p3P1/5r2/8 w - - 0 69'
// - 'illegal uci: ''e7e8'' in 8/2k1P3/5PK1/8/6P1/2p3P1/5r2/8 w - - 0 69'
//
//   - 'illegal uci: ''e7e8'' in 8/2k1P3/5PK1/8/6P1/2p3P1/5r2/8 w - - 0 69'
//   - 'illegal uci: ''e7e8'' in 8/2k1P3/5PK1/8/6P1/2p3P1/5r2/8 w - - 0 69'
