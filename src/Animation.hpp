#pragma once
#include "SDL3/SDL_rect.h"
#include <SDL3_image/SDL_image.h>
#include <gsl/zstring>

typedef struct SheetLayout {
  int row;
  int col;
  int frame_count;
  int offset_x;
  int offset_y;
} SheetLayout;

class Animation {
public:
  Animation();
  ~Animation();

  void NextFrame(const double delta);
  bool Play();

  // assuming all frames' size are the same
  SDL_FRect _srect;
  SDL_FRect _drect;
  SheetLayout _layout;
  int _curFcnt;
  int _delay;         // ms
  int _frameDuration; // indicate the duration of the current frame
  bool flipped;
};
