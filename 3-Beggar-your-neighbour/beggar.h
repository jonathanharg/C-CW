#ifndef BEGGAR_H
#define BEGGAR_H
typedef struct
{
    int* start;
    int* head;
    int* tail;
} Hand;

int beggar(int Nplayers, int* deck, int talkative);
void talk(int talkative, const char* format, ...);
Hand* hand_create();
void hand_push(Hand* self, int card);
#endif