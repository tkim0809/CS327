#ifndef CHARACTER_H
# define CHARACTER_H

# include <stdint.h>

# include "pair.h"

typedef enum __attribute__ ((__packed__)) movement_type {
  move_hiker,
  move_rival,
  move_pace,
  move_wander,
  move_sentry,
  move_explore,
  move_swim,
  move_pc,
  num_movement_types
} movement_type_t;

typedef enum __attribute__ ((__packed__)) character_type {
  char_pc,
  char_hiker,
  char_rival,
  char_swimmer,
  char_other,
  num_character_types
} character_type_t;

extern const char *char_type_name[num_character_types];

class pokemon;

class character {
 public:
  virtual ~character() {}
  pair_t pos;
  char symbol;
  int next_turn;
  int seq_num;
  class pokemon *buddy[6];
};

class npc : public character {
 public:
  character_type_t ctype;
  movement_type_t mtype;
  int defeated;
  pair_t dir;
};

class pc : public character {
 public:
};

int32_t cmp_char_turns(const void *key, const void *with);
void delete_character(void *v);
typedef struct map map_t;
void pathfind(map_t *m);
int pc_move(char);

#endif
