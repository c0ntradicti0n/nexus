#pragma once

#include "surge/src/position.h"
#include "surge/src/tables.h"
#include "surge/src/types.h"
#include <string>
#include <vector>
using namespace std;

#include "chess_types.h"
#include "consts.h"

bool zuege_wied(vector<string> &_zuege);
void zuege_append(vector<string> &zuege, string _hash);

std::string moveToString(const Move &m);    // Function declaration
std::string zugToString(const denkpaar &z); // Function declaration

template <Color Us>
bool isMoveInList(const std::string &moveStr, const MoveList<Us> &moveList) {
  for (Move m : moveList) {

    if (moveToString(m) == moveStr) {
      return true;
    }
  }
  return false;
}
template <Color Us>
int filterZugstapelByMoveList(MoveList<Us> &moveList, denkpaar zugstapel[200],
                              int n) {
  int valid_n = 0;
  denkpaar * zug;
  for (int j = 0; j < n; ++j) {

    zug = &zugstapel[j];
    if (zug->en_passant) {
      valid_n += 1;

      continue;
      }
    if (zug->z.id == -1) {
      continue;
    }
    std::string zugStr = zugToString(*zug);
    if (!isMoveInList(zugStr, moveList)) {
      zugstapel[j].z.id = -1;
    } else {
      valid_n += 1;
    }
  }
  return valid_n;
}
