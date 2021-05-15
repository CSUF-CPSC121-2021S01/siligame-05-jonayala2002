#include "game.h"
#include <iostream>
#include "cpputils/graphics/image.h"

void Game::Init() {
  player_.SetX(400);
  player_.SetY(300);
  GameScreen.AddMouseEventListener(*this);
  GameScreen.AddAnimationEventListener(*this);
}

void Game::UpdateScreen() {
  GameScreen.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  GameScreen.DrawText(0, 0, "Score: " + std::to_string(GetScore()), 30,
                      graphics::Color(0, 0, 0));

  for (int a = 0; a < Opponents.size(); a++) {
    if (Opponents[a]->GetIsActive()) {
      Opponents[a]->Draw(GetGameScreen());
    }
  }
  for (int b = 0; b < OpponentProjectiles.size(); b++) {
    if (OpponentProjectiles[b]->GetIsActive()) {
      OpponentProjectiles[b]->Draw(GetGameScreen());
    }
  }
  for (int c = 0; c < PlayerProjectiles.size(); c++) {
    if (PlayerProjectiles[c]->GetIsActive()) {
      PlayerProjectiles[c]->Draw(GetGameScreen());
    }
  }
  if (player_.GetIsActive()) {
    player_.Draw(GetGameScreen());
  } else {
    GameScreen.DrawText(235, 250, "GAME OVER", 70, graphics::Color(0, 0, 0));
  }
}

void Game::Start() { GameScreen.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < Opponents.size(); i++) {
    if (Opponents[i]->GetIsActive()) {
      Opponents[i]->Move(GameScreen);
    }
  }
  for (int j = 0; j < OpponentProjectiles.size(); j++) {
    if (OpponentProjectiles[j]->GetIsActive()) {
      OpponentProjectiles[j]->Move(GameScreen);
    }
  }
  for (int k = 0; k < PlayerProjectiles.size(); k++) {
    if (PlayerProjectiles[k]->GetIsActive()) {
      PlayerProjectiles[k]->Move(GameScreen);
    }
  }
}

void Game::OnAnimationStep() {
  if (Opponents.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  GameScreen.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &event) {
  if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    int new_x = event.GetX() - player_.GetWidth() / 2;
    int new_y = event.GetY() - player_.GetHeight() / 2;
    int old_x = player_.GetX();
    int old_y = player_.GetY();
    player_.SetX(new_x);
    player_.SetY(new_y);
    if (player_.IsOutOfBounds(GameScreen)) {
      player_.SetX(old_x);
      player_.SetY(old_y);
    }
  }
  if (event.GetMouseAction() == graphics::MouseAction::kPressed) {
    std::unique_ptr<PlayerProjectile> brain =
        std::make_unique<PlayerProjectile>(event.GetX(), event.GetY() + 25);
    PlayerProjectiles.push_back(std::move(brain));
  }
  if (event.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> brain =
        std::make_unique<PlayerProjectile>(event.GetX(), event.GetY() + 25);
    PlayerProjectiles.push_back(std::move(brain));
  }
}

void Game::FilterIntersections() {
  // PlayerProjectile and Opponent

  for (int i = 0; i < PlayerProjectiles.size(); i++) {
    for (int j = 0; j < Opponents.size(); j++) {
      if (PlayerProjectiles[i]->IntersectsWith(Opponents[j].get()) == true) {
        PlayerProjectiles[i]->SetIsActive(false);
        Opponents[j]->SetIsActive(false);
        if (player_.GetIsActive() == true) {
          score_++;
        }
      }
    }
  }

  for (int k = 0; k < OpponentProjectiles.size(); k++) {
    if (OpponentProjectiles[k]->IntersectsWith(&player_) == true) {
      OpponentProjectiles[k]->SetIsActive(false);
      player_.SetIsActive(false);
      active_ = true;
    }
  }

  for (int l = 0; l < Opponents.size(); l++) {
    if (player_.IntersectsWith(Opponents[l].get()) == true) {
      player_.SetIsActive(false);
      Opponents[l]->SetIsActive(false);
      active_ = true;
    }
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < Opponents.size(); i++) {
    if (Opponents[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> brain;
      brain = std::make_unique<OpponentProjectile>();
      brain->SetX(Opponents[i]->GetX());
      brain->SetY(Opponents[i]->GetY());
      OpponentProjectiles.push_back(std::move(brain));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = PlayerProjectiles.size() - 1; i >= 0; i--) {
    if (PlayerProjectiles[i]->GetIsActive() == false) {
      PlayerProjectiles.erase(PlayerProjectiles.begin() + i);
    }
  }
  for (int i = OpponentProjectiles.size() - 1; i >= 0; i--) {
    if (OpponentProjectiles[i]->GetIsActive() == false) {
      OpponentProjectiles.erase(OpponentProjectiles.begin() + i);
    }
  }
  for (int i = Opponents.size() - 1; i >= 0; i--) {
    if (!Opponents[i]->GetIsActive()) {
      Opponents.erase(Opponents.begin() + i);
    }
  }
}
