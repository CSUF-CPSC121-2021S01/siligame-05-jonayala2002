#ifndef PLAYER_H
#define PLAYER_H
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

class Player : public GameElement {
 public:
  Player() {
    x_ = 0;
    y_ = 0;
  }
  Player(int x, int y) : GameElement(x, y, 50, 50) {}

  int GetWidth() { return kWidth_; }
  int GetHeight() { return kHeight_; }

  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;

 private:
  int x_;
  int y_;
  const int kWidth_ = 50;
  const int kHeight_ = 50;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() {
    x_ = 0;
    y_ = 0;
  }
  PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  int GetWidth() { return kWidth_; }
  int GetHeight() { return kHeight_; }

  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;

 private:
  int x_;
  int y_;
  const int kWidth_ = 5;
  const int kHeight_ = 5;
};

#endif
