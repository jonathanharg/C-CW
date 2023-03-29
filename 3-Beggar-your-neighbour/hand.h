#ifndef HAND_H
#define HAND_H
typedef struct
{
    int* start;
    int* end;
    int* tail;
    int* top;
    int empty;
} Hand;

Hand* hand_create();
void hand_increment_pointer(Hand* self, int** pointer);
void hand_decrement_pointer(Hand* self, int** pointer);
void hand_push(Hand* self, int card);
int hand_peek(Hand* self);
int hand_pop(Hand* self);
void hand_give_pile(Hand* hand, Hand* pile);
void hand_print(Hand* self, int reverse);
#endif