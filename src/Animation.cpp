#include "Animation.h"
#include <SDL3_image/SDL_image.h>
#include <cstdio>

Animation::Animation() {
  _srect = {0.0f, 0.0f, 160.0f, 160.0f};
  _drect = {0.0f, 0.0f, 160.0f, 160.0f};
  _layout = {1, 5, 160, 160};
  _curFcnt = 0;
  _delay = 150;
  _frameDuration = 0;
}

Animation::~Animation() {
}

void Animation::NextFrame(double delta) {
  if (_delay >= _frameDuration) {
    _frameDuration += static_cast<int>(delta*1000);
    // printf("%d\n", _frameDuration);
  }
  else {
    _srect.x = (int)(_curFcnt%_layout.col) * _layout.offset_x;
    _srect.y = (int)(_curFcnt/_layout.col) * _layout.offset_y;
    _curFcnt = (_curFcnt+1)%(_layout.row*_layout.col);
    _frameDuration = 0;
  }
  return;
}
