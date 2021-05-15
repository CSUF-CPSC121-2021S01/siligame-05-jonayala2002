#include "player.h"
#include <iostream>
#include "cpputils/graphics/image.h"
#include "opponent.h"

void Player::Draw(graphics::Image &image) {
  graphics::Image soldier;
  soldier.Load("player.bmp");
  for (int i = 0; i < GetWidth(); i++) {
    for (int j = 0; j < GetHeight(); j++) {
      image.SetColor(GetX() + j, GetY() + i, soldier.GetColor(j, i));
    }
  }
}

void PlayerProjectile::Draw(graphics::Image &image) {
  graphics::Image bullet;
  bullet.Load("p_projectile.bmp");
  for (int i = 0; i < GetWidth(); i++) {
    for (int j = 0; j < GetHeight(); j++) {
      image.SetColor(GetX() + j, GetY() + i, bullet.GetColor(j, i));
    }
  }
}

void Player::Move(const graphics::Image &image) {}

void PlayerProjectile::Move(const graphics::Image &image) {
  SetX(GetX() + 3);
  SetY(GetY() + 3);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}
