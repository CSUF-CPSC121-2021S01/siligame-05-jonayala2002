#ifndef GAME_H
#define GAME_H
#include <memory>
#include <vector>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : GameScreen(800, 600) {}
  Game(int width, int height)
      : GameScreen(width, height), width_(width), height_(height) {}

  graphics::Image &GetGameScreen() { return GameScreen; }
  int GetScore() const { return score_; }
  bool HasLost() const { return active_; }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return Opponents; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return OpponentProjectiles;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return PlayerProjectiles;
  }
  Player &GetPlayer() { return player_; }
  void CreateOpponents() {
    for (int i = 0; i < 1; i++) {
      Opponents.push_back(std::make_unique<Opponent>(100 * i + 15, 100));
    }
  }
  void Init();
  void UpdateScreen();
  void Start();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep();
  void RemoveInactive();
  void LaunchProjectiles();
  void OnMouseEvent(const graphics::MouseEvent &event);

 private:
  graphics::Image GameScreen;
  std::vector<std::unique_ptr<Opponent>> Opponents;
  std::vector<std::unique_ptr<OpponentProjectile>> OpponentProjectiles;
  std::vector<std::unique_ptr<PlayerProjectile>> PlayerProjectiles;
  Player player_;
  int width_;
  int height_;
  int score_;
  bool active_;
};
#endif
