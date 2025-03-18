#define SDL_MAIN_USE_CALLBACKS 1
#include "Pet.hpp"
#include "asset.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_image/SDL_image.h>
#include <cstdio>
#include <ctime>
#include <memory>
#include <spdlog/spdlog.h>
#include <vector>

static gsl::czstring path;
static std::vector<std::unique_ptr<Pet>> petGroup;
static int groupSize = 1;
static float mouse_x, mouse_y;
// static bool is_tracking_mouse=false;
static Uint64 now = 0, last = 0;
static Uint64 init_time = 0;
static double delta = 0.0;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {

  srand(static_cast<unsigned int>(std::time(nullptr)));
  SDL_SetAppMetadata("Desktop Pet", "1.0", "Unic Six");
  path = "../res/textures/piggy_sheet.png";
  groupSize = argc > 1 ? atoi(argv[1]) : 1;
  petGroup.reserve(groupSize);

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  init_time = SDL_GetTicks();
  now = SDL_GetTicks();
  for (int i = 0; i < groupSize; i++) {
    petGroup.emplace_back(std::make_unique<Pet>(path));
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  } else if (event->type == SDL_EVENT_WINDOW_MOUSE_ENTER) {
    SDL_GetGlobalMouseState(&mouse_x, &mouse_y);
    spdlog::info("Mouse Position: {:f}, {:f}", mouse_x, mouse_y);
    return SDL_APP_CONTINUE;
  } else if (event->window.windowID) {
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  now = SDL_GetTicks();
  delta = static_cast<double>((now - last)) / 1000;
  SDL_Delay(10);
  last = now > last ? now : last;

  for (auto &pet : petGroup) {
    pet->Update(delta);
  }

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
