//
// Created by stefan on 10/23/22.
//
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;
#include "io_util.h"

void display(int feld[120], int form) {
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
            if (feld[j * 10 + i] != RAND)
                switch (form) {
                case 0: {
                    cout << setw(breite) << " | " << setw(breite)
                         << figuren_char[feld[j * 10 + i] + figurenanzahl];
                    break;
                }

                case 1: {
                    cout << setw(breite) << " | " << setw(breite)
                         << feld[j * 10 + i];
                    break;
                }
                }
        }
        cout << setw(breite) << "| " << j - 1 << "\n"
             << "      "
             << "^ >-----+-----+-----+-----+-----+-----+-----+-----< ^\n"
             << "      ";
    }
    cout << "  >--A--+--B--+--C--+--D--+--E--+--F--+--G--+--H--<  \n";
    cout << "\n";
}

void print_zugstapel(int n, denkpaar zugstapel[200]) {
    for (int i = 0; i < n; i++) {
        cout << figuren_char[zugstapel[i].figur + figurenanzahl] << ": "
             << int(zugstapel[i].z.pos.pos1) << "("
             << grundfeld_bezeichnungen[zugstapel[i].z.pos.pos1] << ")  => "
             << int(zugstapel[i].z.pos.pos2) << "("
             << grundfeld_bezeichnungen[zugstapel[i].z.pos.pos2] << ")";

        if (zugstapel[i].nw) {
            cout << " | ";
            int max = zugstapel[i].nw;

            for (int j = 0; j < max; j++) {
                cout << int(zugstapel[i].verwandelung[j].pos1) << "("
                     << grundfeld_bezeichnungen
                            [zugstapel[i].verwandelung[j].pos1]
                     << ")  <= "
                     << figuren_char[zugstapel[i].verwandelung[j].fig +
                                     figurenanzahl];

                if (j < max - 1)
                    cout << ", ";
            }
        }

        cout << "\n";
    }
}

void disp_cleanest(int feld[120]) {
    cout << "\n";

    for (int j = 9; j > 1; j--) {
        for (int i = 1; i < 9; i++) {
            if (feld[j * 10 + i] != RAND)
                cout << figuren_char[feld[j * 10 + i] + figurenanzahl];

            if (j * 10 + i != 28)
                cout << ",";
        }
        cout << "\n";
    }
    cout << "\n";
}


struct endofinput : public exception {
    const char *what() const throw() { return "end of file in input stream!"; }
};

int eingabe() {
    bool okay = false;
    int i, j;

    do {
        cout << "Feld ('.' fuer 'zieh doch selber!'):";
        char buchstabe;
        cin >> buchstabe;

        if (buchstabe == '.')
            return 666;

        char zahl;
        cin >> zahl;

        if (zahl == '.')
            return 666;

        if ((buchstabe == 'x') && (zahl == 'x')) {
            cout << "\n";
            return false;
        }

        for (i = 0; i <= 7; i++)
            if ((buchstabe == buchstaben1[i]) || (buchstabe == buchstaben2[i]))
                for (j = 0; j <= 7; j++) {
                    if (zahl == zahlen[j]) {
                        okay = true;
                        return 21 + j * 10 + i;
                    }
                }

        if (cin.eof())
            throw endofinput();
    } while (!okay);
    return 0;
}
