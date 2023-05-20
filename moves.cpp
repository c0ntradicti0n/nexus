#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <set>

#include "moves.h"
#include "surge/src/position.h"
#include "surge/src/tables.h"
#include "surge/src/types.h"

using namespace std;

void zuege_append(vector<string> &zuege, string _hash) {
  zuege.insert(zuege.end(), (_hash));
}

bool zuege_wied(vector<string> &_zuege) {
  set<string> unique(_zuege.begin(), _zuege.end());

  std::map<std::string, int> count;

  for (auto x : _zuege)
    ++count[x];

  int val = 2;
  auto it = std::find_if(count.begin(), count.end(),
                         [val](const std::pair<std::string, int> &t) -> bool {
                           return t.second > val;
                         });

  if (it == count.end()) {
    return false;
  } else {
    cout << "position id " << (it->first) << "after moves ";

    int ii = 0;

    for (auto y : _zuege) {
      ii += 1;

      if (y == (it->first))
        cout << (double)ii / 2 << " ";
    }

    return true;
  }
}

std::string moveToString(const Move &m) {

  std::ostringstream stream;
  stream << m;
  std::string moveString = stream.str();
  return moveString.substr(0, 4);
}


std::string zugToString(const denkpaar &z) {
  try {

  if (z.castling && z.z.pos.pos1 == 25 && z.z.pos.pos2 == 27)
    return "e1h1";
  if (z.castling && z.z.pos.pos1 == 25 && z.z.pos.pos2 == 21)
    return "e1a1";
  if (z.castling && z.z.pos.pos1 == 95 && z.z.pos.pos2 == 97)
    return "e8h8";
  if (z.castling && z.z.pos.pos1 == 95 && z.z.pos.pos2 == 91)
    return "e8a8";
    if (z.figur == W_B && z.nw >1 && (z.figur)==W_B && z.z.pos.pos1 > 80) {
      return std::string(grundfeld_bezeichnungen[z.z.pos.pos1]) +
             std::string(grundfeld_bezeichnungen[z.z.pos.pos2]) +
             pieceToFen[z.figur];
    } else if (z.figur == S_B, z.nw >1 && (z.figur)==S_B && z.z.pos.pos1 < 30) {
      return std::string(grundfeld_bezeichnungen[z.z.pos.pos1]) +
             std::string(grundfeld_bezeichnungen[z.z.pos.pos2]) +
             pieceToFen[z.figur];
    }
    
  
  return std::string(grundfeld_bezeichnungen[z.z.pos.pos1]) +
         std::string(grundfeld_bezeichnungen[z.z.pos.pos2]);
  } catch (const std::exception &e) {
    cout << "ERROR" << e.what() << endl;
    throw e;
  }
}