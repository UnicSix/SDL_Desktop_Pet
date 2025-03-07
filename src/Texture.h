#include "precomp.h"
#include <SDL3_image/SDL_image.h>
#include <gsl/zstring>

class Texture{
public:
  Texture();
  ~Texture();
  void LoadFromFile(gsl::czstring filePath);

private:
  SDL_Texture mTexture;
  int mWidth;
  int mHeight;
};
