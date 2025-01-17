#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "wall.h"
#include <condition_variable>
#include <mutex>
#include <random>
#include <thread>

enum class GameState { kActive, kDead };

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  void timerThreadFunction(bool &running);

private:
  Snake snake;
  Wall wall;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int round{0};

  void PlaceFood();
  // void Update();
  GameState Update();

  void restart();
  void updateScoreHistory();

  bool slowSpeed{false};
  std::mutex _mutex;
  std::condition_variable _condvar;
};

#endif