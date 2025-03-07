#include "Pet.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_video.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <utility>

Pet::Pet() {
  printf("Pet Null Constructor\n");
  _window = nullptr;
  _renderer = nullptr;
  _texture = nullptr;
  return;
}
Pet::Pet(gsl::czstring& texPath) {
  printf("Pet Load Texture Constructor\n");
  _filePath = texPath;
  _window = SDL_CreateWindow("Pet", 160, 160, 
                             SDL_WINDOW_RESIZABLE | 
                             SDL_WINDOW_TRANSPARENT |
                             SDL_WINDOW_BORDERLESS);
  SDL_SetWindowPosition(_window, 800, 300);
  if (!_window){
    SDL_Log("Couldn't create window: %s", SDL_GetError());
    return;
  }
  SDL_SetWindowAlwaysOnTop(_window, true);
  _renderer = SDL_CreateRenderer(_window, NULL);
  if (!_renderer) {
    SDL_Log("Couldn't create renderer: %s", SDL_GetError());
    return;
  }
  _texture = IMG_LoadTexture(_renderer, _filePath);
  if (!_texture) {
    SDL_Log("Failed to load texture: %s\n", SDL_GetError());
    SDL_Log("Path attempted: %s\n", _filePath);
  }

  _state = PetState::IDLE;
  _actionDuration = 0;
  _angle = 0;
  _moveDirecX = 0.0;
  _moveDirecY = 0.0;
  _speed = 100.0f;
  _rng = std::mt19937(std::random_device{}());
  std::cout << "Create Window\n";
  SDL_GetWindowPosition(_window, &_posX, &_posY);
  return;
}

Pet::Pet(Pet&& other) noexcept {
  printf("Move Constructor\n");
  _window = std::move(other._window);
  _renderer = std::move(other._renderer);
  _texture = std::move(other._texture);
  _filePath = other._filePath;
  _state = other._state;
  _posX = other._posX;
  _posY = other._posY;
  _actionDuration = other._actionDuration;
  _speed = other._speed;
  _moveDirecX = other._moveDirecX;
  _moveDirecY = other._moveDirecY;
  _rng = other._rng;
  _deltaCoord = other._deltaCoord;

  other._texture = nullptr;
  other._renderer = nullptr;
  other._window = nullptr;
}


Pet::~Pet(){
  std::cout << "Destroy\n";
  SDL_DestroyTexture(_texture);
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  _texture = nullptr;
  _renderer = nullptr;
  _window = nullptr;
  return;
}

Pet& Pet::operator=(Pet&& other) noexcept {
  printf("Move Assignment\n");
  if (this != &other) {
    _window = std::move(other._window);
    _renderer = std::move(other._renderer);
    _texture = std::move(other._texture);
    _filePath = other._filePath;
    _state = other._state;
    _posX = other._posX;
    _posY = other._posY;
    _actionDuration = other._actionDuration;
    _speed = other._speed;
    _moveDirecX = other._moveDirecX;
    _moveDirecY = other._moveDirecY;
    _rng = other._rng;
    _deltaCoord = other._deltaCoord;

    other._texture = nullptr;
    other._renderer = nullptr;
    other._window = nullptr;
  }
  return *this;
}

void Pet::LoadTexture(const gsl::czstring& texPath){
  _texture = IMG_LoadTexture(_renderer, texPath);
  if (!_texture) {
    SDL_Log("Failed to load texture: %s\n", SDL_GetError());
    SDL_Log("Path attempted: %s\n", texPath);
  }
}

void Pet::Update(double delta) {
  RandomStrafe(delta);
  RenderPet();
  _anim.NextFrame(delta);
  _actionDuration--;
  return;
}

void Pet::RenderPet() {
  SDL_RenderClear(_renderer);
  if (!SDL_RenderTexture(_renderer, _texture, &_anim._srect, &_anim._drect)) {
    SDL_Log("Failed to Render Texture: %s\n", SDL_GetError());
  }
  else {
  }
  SDL_RenderPresent(_renderer);
}

void Pet::SetWindowPosition(int x, int y){
  if(!SDL_SetWindowPosition(_window, x, y)){
    SDL_Log("Failed to move window: %s", SDL_GetError());
  }
}

void Pet::MoveToDirec(){
  _deltaCoord.bufx += _deltaCoord.dx;
  _deltaCoord.bufy += _deltaCoord.dy;
  int bufx = trunc(_deltaCoord.bufx);
  int bufy = trunc(_deltaCoord.bufy);
  int newPosX = _posX + bufx;
  int newPosY = _posY + bufy;
  _deltaCoord.bufx -= bufx;
  _deltaCoord.bufy -= bufy;
  if((newPosX)>1920 || (newPosX)<0 ||
     (newPosY)>1080-_texture->h || (newPosY)<0) {
    // // printf("Hit Monitor Bound\n");
    _actionDuration = 0;
    // _moveDirecX = 0.0;
    // _moveDirecY = 0.0;
    // _deltaCoord.bufx = 0.0;
    // _deltaCoord.bufy = 0.0;
    printf("Reset Position\n");
    return;
  }
  else {
    _posX = newPosX;
    _posY = newPosY;
    // printf("New Position: %d, %d\n", _posX, _posY);
  }
  if(!SDL_SetWindowPosition(_window, _posX, _posY)) {
    SDL_Log("Failed to Set Window Position: %s", SDL_GetError());
    return;
  }
  // SDL_GetWindowPosition(_window, &_posX, &_posY);
  return;
}

void Pet::RandomStrafe(double delta) {
  if (_actionDuration > 0) {
    MoveToDirec();
  }
  if (_actionDuration == 0) {
    _state = PetState::MOVING;
    std::uniform_real_distribution<double> angle(0, 360);
    std::uniform_int_distribution<int> duration(600, 1200);
    // randomly select a direction, and a duration of time
    // duration range: 30~90 frames
    _actionDuration = duration(_rng);
    // pick a angle and transform to direction using sin() and cos()
    _angle = angle(_rng);
    // _moveDirecX = delta * _speed * cos(_angle*M_PI/180.0);
    // _moveDirecY = delta * _speed * sin(_angle*M_PI/180.0);
    _deltaCoord.dx = delta * _speed * cos(_angle*M_PI/180.0);
    _deltaCoord.dy = delta * _speed * sin(_angle*M_PI/180.0);
    _deltaCoord.bufx = 0.0;
    _deltaCoord.bufy = 0.0;
    printf("Move: %f, %f; dt: %f\n", _deltaCoord.dx, _deltaCoord.dy, delta);
  }
}

void Pet::PrintInfo() const {
  printf("Position: %d, %d\n", _posX, _posY);
  printf("Speed: %f\n", _speed);
  printf("Move Direction: %f, %f\n", _moveDirecX, _moveDirecY);
  printf("_action_duration: %u\n", _actionDuration);
  return;
}
