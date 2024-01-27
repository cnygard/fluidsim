#pragma once

enum GameState {
  GAME_ACTIVE,
  GAME_MENU
};

class Game {
  public:
    // vars
    GameState    State;
    bool         Keys[1024];
    unsigned int Width, Height;

    // funcs
    Game(unsigned int width, unsigned int height);
    ~Game();
    void Init();
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
};
