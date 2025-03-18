#pragma once
#define _USE_MATH_DEFINES
#include "Animation.hpp"
#include "SDL3/SDL_video.h"
#include <SDL3_image/SDL_image.h>
#include <cmath>
#include <gsl/span>
#include <gsl/zstring>
#include <random>

class Pet {
public:
  Pet();
  Pet(gsl::czstring &texPath);
  Pet(Pet &&other) noexcept;
  ~Pet();
  Pet(const Pet &) = delete;
  Pet &operator=(const Pet &) = delete;
  Pet &operator=(Pet &&other) noexcept;
  void LoadTexture(const gsl::czstring &texPath);
  void RenderPet(const double delta);
  inline SDL_Window *GetWindow() { return _window; }
  void SetWindowPosition(int x, int y);
  void MoveToDirec();
  void RandomStrafe(const double delta);
  void Idle(const double delta);
  void LogInfo() const;
  inline int GetPosX() const { return _posX; }
  inline int GetPosY() const { return _posY; }
  void Update(const double delta);
  void MouseDrag();

private:
  struct DeltaCoord {
    double dx, dy;
    double bufx, bufy;
    DeltaCoord() : dx(0.0), dy(0.0), bufx(0.0), bufy(0.0) {}
  };
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Texture *_texture;
  Animation _anim;
  gsl::czstring _filePath;
  Uint32 _state;
  int _posX, _posY;
  Uint32 _actionDuration;
  double _angle;
  double _speed;
  DeltaCoord _deltaCoord;

  std::mt19937 _rng;
};
