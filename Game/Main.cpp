// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "Engine.h"
#include <memory>
#include <random>
#include <fstream>
using namespace nu;


int main()
{
    //Factory::Instance().Register<Actor>("Actor");
    //auto actor = Factory::Instance().Create<Actor>("Actor");


    nu::SetWorkingDirectory("assets");
    //Initialize
   
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();
  
 
    SDL_Event e;
    bool quit = false;

    // create texture, using shared_ptr so texture can be shared
   // std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    //texture->Load("textures/player.png",Engine::Get().GetRenderer());

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
        
        game.Update(dt);

        game.Draw(nu::Engine::Get().GetRenderer());

        //Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("textures/player.png", Engine::Get().GetRenderer()), 30, 30);

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());


        nu::Engine::Get().GetRenderer().Present();
    }

    //shutdown
    Engine::Get().Shutdown();

    return 0;
}


