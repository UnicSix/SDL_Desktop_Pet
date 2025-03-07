#define _USE_MATH_DEFINES
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <SDL3_image/SDL_image.h>
#include <cstdint>
#include <gsl/zstring>
#include <random>
#include "precomp.h"
#include "Animation.h"

class Pet{
public:
  Pet();
  Pet(gsl::czstring& texPath);
  Pet(Pet&& other) noexcept;
  ~Pet();
  Pet(const Pet&) = delete;
  Pet& operator=(const Pet&) = delete;
  void LoadTexture(const gsl::czstring& texPath);
  void RenderPet();
  inline SDL_Window* GetWindow(){ return _window; }
  void SetWindowPosition(int x, int y);
  void MoveToDirec();
  void RandomStrafe(const double delta);
  void PrintInfo() const;
  inline int GetPosX() const { return _posX; }
  inline int GetPosY() const { return _posY; }
  void Update(const double delta);
  Pet& operator=(Pet&& other) noexcept;
  // Pet& operator=(const Pet& other);

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
  double _moveDirecX, _moveDirecY;
  double _speed;
  DeltaCoord _deltaCoord;

  std::mt19937 _rng;
};

enum PetState : int {
  IDLE,
  MOVING,
  DRAGGED
};
