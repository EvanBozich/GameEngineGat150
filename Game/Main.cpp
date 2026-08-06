// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>
#include "Audio.h"
#include "Assets.h"
#include "SpaceGame.h"
#include <memory>
#include <random>
using namespace nu;


uint32_t seed = 1243;


uint32_t rng()
{
    seed = (seed * 1103515245) + 12345;

    return seed;
}


int main()
{
    //rand()
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << rng() << " ";
    }

    std::cout << std::endl;

    seed = 1234;
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << rng() << " ";
    }

    std::cout << std::endl;

    srand((unsigned int)time(NULL));
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << rand() << " ";
    }

    std::cout << std::endl;
    //random
    std::random_device randomDevice;

    std::cout << randomDevice.min() << std::endl;
    std::cout << randomDevice.max() << std::endl;
    std::cout << randomDevice.entropy() << std::endl;

    std::mt19937 generator(randomDevice());

    std::uniform_int_distribution<> dist(0, 20);

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << dist(generator) << " ";
    }

    std::cout << std::endl;

    std::uniform_real_distribution<float> distReal(-10, 40);

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << distReal(generator) << " ";
    }

    std::cout << std::endl;

    return 0;

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

        Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("textures/player.png", Engine::Get().GetRenderer()), 30, 30);

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());


        nu::Engine::Get().GetRenderer().Present();
    }

    //shutdown
    Engine::Get().Shutdown();

    return 0;
}


