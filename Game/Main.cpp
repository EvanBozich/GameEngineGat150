// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>
#include "Audio.h"
#include "Assets.h"
#include "SpaceGame.h"
#include <memory>
using namespace nu;

class Object
{
public:
    Object() { std::cout << "Constructor\n"; }
    ~Object() { std:: cout << "Destructor\n"; }

    Object(const Object& object) { std::cout << "Copy constructor\n"; }

    Object& operator =(const Object& object) { std::cout << "assignment\n"; return *this; }

private:
};


int main()
{

    std::cout << "============================Object===================================" << std::endl;
    {
        Object objectA;
        Object objectB = objectA;
        Object objectC;
        objectC = objectA;



    }
    std::cout << "================Raw Pointer============================" << std::endl;
    {
        Object* objectA = new Object();
        std::cout << objectA << std::endl;
        Object* objectB = new Object(*objectA);
        std::cout << objectB << std::endl;
        Object* objectC = nullptr;
        objectC = objectA;
        std::cout << objectC << std::endl;

        delete objectA;
        delete objectB;
        //delete objectC;
    }
    std::cout << "================Smart Pointer============================" << std::endl;
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectB.get() << std::endl;

        objectB.reset();
    }







    SetWorkingDirectory("assets");
    //Initialize
   
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();
  
 
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
        
        game.Update(dt);

        game.Draw(nu::Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());


        nu::Engine::Get().GetRenderer().Present();
    }

    //shutdown
    Engine::Get().Shutdown();

    return 0;
}


