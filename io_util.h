//
// Created by stefan on 10/23/22.
//

#ifndef NEXUS_IO_UTIL_H
#define NEXUS_IO_UTIL_H

#include "chess_types.h"
#include "consts.h"

void display(int feld[120], int form = 0);
void print_zugstapel(int n, denkpaar zugstapel[200]);
void disp_cleanest(int feld[120]);
int eingabe();

#endif // NEXUS_IO_UTIL_H
