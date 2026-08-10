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
#include <fstream>
using namespace nu;


int main()
{

    nu::SetWorkingDirectory("assets");
    //Initialize

    {
        //read file (input)
        std::ifstream file("data/test.txt");
        if (file.is_open())
        {
            std::string str;
            while (std::getline(file, str))
            {
                std::cout << str << std::endl;
            }
        }
        else
        {
            std::cout << "Can't load the file homie" << std::endl;
        }

        //does automatically if out of scope
        file.close();
    }

    {
        //write to file (output)
        std::ofstream file("data/test.txt", std::ios::app);
        if (file.is_open())
        {
            file << "Have a good day.\n";
        }
    }

    {
        //read/write (input/output)
        std::fstream file("data/test.txt", std::ios::in | std::ios::out | std::ios::app);
        if (file.is_open())
        {
            file << "add a line\n";
            file.seekg(0);
            std::string str;
            while (std::getline(file, str))
            {
                std::cout << str << std::endl;
            }
        }
    }

    {
        std::string name;
        int score;
        bool isAlive;

        //save game data
        bool save = false;

        if (save)
        {
            name = "Evan";
            score = 1234;
            isAlive = true;

            //save game data
            std::ofstream file("data/game.txt");
            if (file.is_open())
            {
                file << name << "\n";
                file << score << "\n";
                file << isAlive << "\n";
            }
        }

        //load game data
        bool load = true;

        if (load)
        {
            std::ifstream file("data/game.txt");
            if (file.is_open())
            {
                std::getline(file, name);
                file >> score;
                file >> isAlive;
            }
        }

        std::cout << name << std::endl;
        std::cout << score << std::endl;
        std::cout << isAlive << std::endl;
    }

    return 0;
   
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


