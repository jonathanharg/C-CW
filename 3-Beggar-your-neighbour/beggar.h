#ifndef BEGGAR_H
#define BEGGAR_H
typedef struct
{
    int* start;
    int* end;
    int* top;
    int* tail;
    int empty;
} Hand;

int beggar(int Nplayers, int* deck, int talkative);
Hand* hand_create();
void hand_push(Hand* self, int card);
int finished(Hand** players, int Nplayers);
int hand_peek(Hand* self);
Hand* take_turn(Hand* player, Hand* pile);
void hand_give_pile(Hand* hand, Hand* pile);
#endif