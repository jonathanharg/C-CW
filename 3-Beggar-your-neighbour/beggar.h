#ifndef BEGGAR_H
#define BEGGAR_H
#include "hand.h"
int beggar(int Nplayers, int* deck, int talkative);
int finished(Hand** players, int Nplayers);
Hand* take_turn(Hand* player, Hand* pile);
#endif