// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "SpriteGame/SpriteGame.h"
#include "Engine.h"
#include <memory>
#include <random>
#include <fstream>

using namespace nu;

int main()
{
    nu::SetWorkingDirectory("assets");

    //Initialize
   
    Engine::Get().Initialize();

    //SpriteGame game
    std::unique_ptr game = std::make_unique<SpriteGame>();
    game->Initialize();
  
 
    SDL_Event e;
    bool quit = false;

    //main loop
    while (!quit) 
    {

        //update
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }


        nu::Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();

      
        nu::Engine::Get().GetRenderer().SetColorInt(0, 0, 0);
        nu::Engine::Get().GetRenderer().Clear();
        
        game->Update(dt);

        game->Draw(nu::Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        nu::Engine::Get().GetRenderer().Present();
    }

    game.reset();
    //shutdown
    Engine::Get().Shutdown();

    return 0;
}


