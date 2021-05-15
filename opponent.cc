#include "opponent.h"
#include <iostream>
#include "cpputils/graphics/image.h"

void Opponent::Draw(graphics::Image &image) {
  graphics::Image zombie;
  zombie.Load("opponent.bmp");
  for (int i = 0; i < GetWidth(); i++) {
    for (int j = 0; j < GetHeight(); j++) {
      image.SetColor(GetX() + j, GetY() + i, zombie.GetColor(j, i));
    }
  }
}

void OpponentProjectile::Draw(graphics::Image &image) {
  graphics::Image brain;
  brain.Load("o_projectile.bmp");
  for (int i = 0; i < GetWidth(); i++) {
    for (int j = 0; j < GetHeight(); j++) {
      image.SetColor(GetX() + j, GetY() + i, brain.GetColor(j, i));
    }
  }
}

void OpponentProjectile::Move(const graphics::Image &image) {
  SetX(GetX() + 3);
  SetY(GetY() + 3);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}

void Opponent::Move(const graphics::Image &image) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}

std::unique_ptr<class OpponentProjectile> Opponent::LaunchProjectile(){
  if(rate >= 10){
    rate = 0;
    std::unique_ptr<OpponentProjectile> brain;
    brain = std::make_unique<OpponentProjectile>();
    return std::move(brain);
  } else {
    rate++;
    return nullptr; 
  }
}
