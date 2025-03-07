#ifndef ECS_PET_H
#define ECS_PET_H

#include "precomp.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace ecsPet{

struct PetContainer{
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
};

struct Position{
  float mX;
  float mY;
};

struct TextureSize{
  int mX;
  int mY;
};

struct TextureFilePath{
  gsl::czstring mFileName;
};
struct PetName{
  gsl::czstring mName;
};
void InitWindowAndRenderer(flecs::iter &it, PetContainer* pw);
}


#ifdef __cplusplus
}
#endif

#endif

