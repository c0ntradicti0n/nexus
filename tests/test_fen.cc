#include <bp.cpp>
#include <gtest/gtest.h>

TEST(FEN, BasicAssertions) {
  initialise_all_databases();
  zobrist::initialise_zobrist_keys();

  Spielfeld spiel = Spielfeld(grundfeld);
  int depth = 4;
  auto test_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  spiel.read_fen(test_fen);
  auto assert_fen = spiel.to_fen();
  EXPECT_STRCASEEQ(assert_fen.c_str(), test_fen);
}
