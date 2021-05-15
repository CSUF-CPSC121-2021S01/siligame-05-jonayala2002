#include "game_element.h"
#include <iostream>
#include "cpputils/graphics/image.h"

void GameElement::Draw(graphics::Image &image) {
  graphics::Color black(0, 0, 0);
  image.DrawRectangle(GetX(), GetY(), 5, 5, black);
}

bool GameElement::IntersectsWith(GameElement* gameelement) {
  int x = gameelement->GetX();
  int y = gameelement->GetY();
  int width = gameelement->GetWidth();
  int height = gameelement->GetHeight();
  if (GetX() >= x && GetX() <= (x + width) && GetY() >= y &&
      GetY() <= (y + height)) {
    return true;
  } else if ((GetX() + GetWidth()) >= x &&
             (GetX() + GetWidth()) <= (x + width) && GetY() >= y &&
             GetY() <= (y + height)) {
    return true;
  } else if (GetX() >= x && GetX() <= (x + width) &&
             (GetY() + GetHeight()) >= y &&
             (GetY() + GetHeight()) <= (y + height)) {
    return true;
  } else if ((GetX() + GetWidth()) >= x &&
             (GetX() + GetWidth()) <= (x + width) &&
             (GetY() + GetHeight()) >= y &&
             (GetY() + GetHeight()) <= (y + height)) {
    return true;
  } else {
    return false;
  }
}

bool GameElement::IsOutOfBounds(const graphics::Image &image) {
  if (GetX() < 0 || GetX() + GetWidth() > image.GetWidth() || GetY() < 0 ||
      GetY() + GetHeight() > image.GetHeight()) {
    return true;
  } else {
    return false;
  }
}
