#include "hand.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Initialize a player hand or a pile.
 * @return Returns a pointer to the hand.
 */
Hand* hand_create() {
    /* The size of a players hand cannot exceed 52. Therefore we can allocate an int array of size
    52, and with some careful pointer arithmetic we store a whole pack in each hand. We need to
    make sure to wrap the pointers around whenever the reach the beginning/end of the array. This
    is more efficient than a linked list implementation since all of the cards are next to each
    other in memory. */

    Hand* hand = malloc(sizeof(Hand));

    int* p_start = (int*)malloc(52 * sizeof(int));
    if (p_start == NULL || hand == NULL)
        fprintf(stderr, "Failed to allocate enough memory to create a hand.\n");

    /* [ 4  5  6  7  8  -  -  -  -  -  -  -  -  -  1  2  3 ] */
    /* ^                ^                          ^       ^ */
    /* start          top                       tail     end */

    hand->start = p_start;
    hand->end = p_start + 51;
    hand->tail = p_start;
    hand->top = p_start;
    hand->empty = 1;

    return hand;
}

/**
 * @brief Increment a pointer to a card in a hand without overflowing.
 * @param self The hand struct the pointer is tied to.
 * @param pointer The pointer to increment.
 */
void hand_increment_pointer(Hand* self, int** pointer) {
    if (*pointer == self->end) {
        /* We have reached the end of the array, wrap back around to the beginning */
        *pointer = self->start;
    } else {
        (*pointer)++;
    }
}

/**
 * @brief Decrement a pointer to a card in a hand without overflowing.
 * @param self The hand struct the pointer is tied to.
 * @param pointer The pointer to decrement.
 */
void hand_decrement_pointer(Hand* self, int** pointer) {
    if (*pointer == self->start) {
        /* We have reached the beginning of the array, wrap back around to the end */
        *pointer = self->end;
    } else {
        (*pointer)--;
    }
}

/**
 * @brief Push a card to the top of a Hand.
 * @param self The hand to push to.
 * @param card The card to push.
 */
void hand_push(Hand* self, int card) {
    if ((self->top == self->tail) && !self->empty) {
        fprintf(stderr, "Hand is full! Cannot add another card without overwriting an existing one!\n");
        return;
    }
    self->empty = 0;
    *(self->top) = card;
    hand_increment_pointer(self, &(self->top));
}

/**
 * @brief Peek at the top card of a Hand stack.
 * @param self The Hand to peek.
 * @return The value of the card at the top of the stack.
 */
int hand_peek(Hand* self) {
    int* p_last = self->top;
    /* We need to decrement last, since the Hand's top points to the next empty space
    rather than the last value. */
    hand_decrement_pointer(self, &p_last);
    return *p_last;
}

/**
 * @brief Pop a value from a Hand stack.
 * @param self The Hand to pop from.
 * @return The value of the card at the top of the stack, or 0 if the stack is empty.
 */
int hand_pop(Hand* self) {
    if (self->empty) {
        return 0;
    }

    hand_decrement_pointer(self, &(self->top));

    if (self->tail == self->top) {
        /* We are just about to pop the last card in the hand */
        self->empty = 1;
    }

    int popped = *(self->top);
    *(self->top) = 0;
    return popped;
}

/**
 * @brief Add a pile to the bottom of a Hand stack.
 * @param self The players hand to add the pile to.
 * @param pile The pile to add to the players hand.
 */
void hand_give_pile(Hand* self, Hand* pile) {
    /* Add from the top of the pile to the bottom of a players hand.
    This reverses the order of the pile, like how the pile would be flipped upside down
    before being added to a players hand. */

    if (pile->empty)
        return;

    /* we can use tail++ since the always begins at the start and never wraps */
    for (; pile->tail < pile->top; pile->tail++) {
        hand_decrement_pointer(self, &(self->tail));
        *(self->tail) = *(pile->tail);
    }
    self->empty = 0;

    pile->tail = pile->start;
    pile->top = pile->start;
    pile->empty = 1;

    // TODO: Remove this
    int i;
    for (i = 0; i < 52; i++) {
        pile->start[i] = 0;
    }
}

/**
 * @brief Print a Hand struct.
 * @param self The hand struct to print.
 * @param reverse If we should reverse the order of the cards to be more human readable.
 */
void hand_print(Hand* self, int reverse) {
    if (self->empty) {
        printf("No cards.\n");
        return;
    }

    int* p_visiting;
    int* p_goal;

    if (reverse) {
        p_visiting = self->top;
        p_goal = self->tail;
        /* Since top points to the next empty space we have to decrement it so that it points to
        the last entered element */
        hand_decrement_pointer(self, &p_visiting);
        hand_decrement_pointer(self, &p_goal);
    } else {
        p_visiting = self->tail;
        p_goal = self->top;
    }

    printf("%i", *p_visiting);
    if (reverse)
        hand_decrement_pointer(self, &p_visiting);
    else
        hand_increment_pointer(self, &p_visiting);

    while (p_visiting != p_goal) {
        printf(", %i", *p_visiting);
        if (reverse)
            hand_decrement_pointer(self, &p_visiting);
        else
            hand_increment_pointer(self, &p_visiting);
    }
    printf("\n");
}