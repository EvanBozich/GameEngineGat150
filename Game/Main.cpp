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
    nu::SetWorkingDirectory("assets");

    Factory::Instance().Register<Actor>("Actor");
    Factory::Instance().Register<Object>("Object");
    Factory::Instance().Register<Player>("Player");

    auto actor = Factory::Instance().Create<Actor>("Actor");
    std::cout << actor->IsActive() << std::endl;


    auto object = Factory::Instance().Create<Object>("Object");
    std::cout << object->IsActive() << std::endl;

    auto player = Factory::Instance().Create<Player>("Player");
    json::document_t document;
    if (json::Load("data/scene.json", document))
    {
        player->Read(document);
        std::cout << player->GetName() << std::endl;
        std::cout << player->GetTag() << std::endl;
        std::cout << player->GetTransform().rotation << std::endl;
        std::cout << player->GetSpeed() << std::endl;
        std::cout << player->GetRadius() << std::endl;
    }

    return 0;

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


