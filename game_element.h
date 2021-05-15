#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H
#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement() {
    x_ = 0;
    y_ = 0;
    width_ = 50;
    height_ = 50;
  }
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}
  int GetX() { return x_; }
  int GetY() { return y_; }
  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }
  int GetWidth() { return width_; }
  int GetHeight() { return height_; }
  bool GetIsActive() { return is_active_; }
  void SetIsActive(bool is_active) { is_active_ = is_active; }

  virtual void Draw(graphics::Image &image) = 0;
  virtual void Move(const graphics::Image &image) = 0;
  bool IntersectsWith(GameElement* gameelement);
  bool IsOutOfBounds(const graphics::Image &image);

 private:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active_ = true;
};

#endif
