#ifndef OPPONENT_H
#define OPPONENT_H
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include <memory>

class Opponent : public GameElement {
 public:
  Opponent() {
    x_ = 0;
    y_ = 0;
  }
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}

  int GetWidth() { return kWidth_; }
  int GetHeight() { return kHeight_; }

  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;
  std::unique_ptr<class OpponentProjectile> LaunchProjectile();

 private:
  int x_;
  int y_;
  const int kWidth_ = 50;
  const int kHeight_ = 50;
  int rate;
};

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() {
    x_ = 0;
    y_ = 0;
  }
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

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
