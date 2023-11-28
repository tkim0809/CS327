#ifndef PAIR_H
# define PAIR_H

typedef enum dim {
  dim_x,
  dim_y,
  num_dims
} dim_t;

typedef int16_t pair_t[num_dims];

#endif
