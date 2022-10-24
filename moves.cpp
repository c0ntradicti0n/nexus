//
// Created by stefan on 10/23/22.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <set>

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