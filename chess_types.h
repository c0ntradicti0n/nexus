
#ifndef NEXUS_CHESS_TYPES_H
#define NEXUS_CHESS_TYPES_H

// TYPEN
struct wandel {
    int pos1;
    int fig;
};
union zug {
    struct {
        char pos1 : 8;
        char pos2 : 8;
    } pos;
    int id : 16;
};
struct denkpaar {
    zug z;
    int farbe;
    int figur;
    int spezial;
    int bewertung;
    int i;
    wandel verwandelung[20];
    int nw;
    bool reckoning;
    bool kill;
    double order;
    int finds[120]; // Find
};

struct figurtyp {
    int pos1;
    int pos2;
    bool schach;
    bool bewegt;
};
struct feldtyp {
    int feld[120];
    int x;
};
enum state { user, uci, gone, position };

#endif
