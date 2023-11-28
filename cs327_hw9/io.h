#ifndef IO_H
# define IO_H

# include "pair.h"

class character;

void io_init_terminal(void);
void io_reset_terminal(void);
void io_display(void);
void io_handle_input(pair_t dest);
void io_queue_message(const char *format, ...);
void io_battle(character *aggressor, character *defender);
void io_encounter_pokemon();
void io_choose_starter();

#endif
