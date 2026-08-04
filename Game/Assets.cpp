#include "Assets.h"

namespace Assets
{
	nu::Mesh mesh1{ { nu::Vector2{6,0}, nu::Vector2{-3,-5}, nu::Vector2{0,3}, nu::Vector2{-3,0 }, nu::Vector2{0,-3} }, nu::Color{1.0f, 1.0f, 1.0f} };
	nu::Mesh mesh2{ { nu::Vector2{6,0}, nu::Vector2{-3,-5}, nu::Vector2{-2,0}, nu::Vector2{6,0}, nu::Vector2{-3,5}, nu::Vector2{-2,0} }, nu::Color{0.5f, 0.52f, 1.58f} };
	nu::Mesh mesh4{ { nu::Vector2{-2,0}, nu::Vector2{-5,-2}, nu::Vector2{-4,0}, nu::Vector2{-5,2}, nu::Vector2{-2,0} }, nu::Color{2.07f, 0.05f, 0.02f} };
	nu::Mesh bulletMesh
	{
	  {
		nu::Vector2{ -1, -1 },
		nu::Vector2{ 1, 0 },
		nu::Vector2{ -1, 1 },
		nu::Vector2{ -1, -1 },
	  },
	  nu::Color{ 1.0f, 0.0f, 0.0f }
	};

	nu::Mesh asteriodMesh
	{
		{
			nu::Vector2{ 0, -4 },
			nu::Vector2{ -3, -3 },
			nu::Vector2{ -4, -1 },
			nu::Vector2{ -4, 1 },
			nu::Vector2{ -3, 3 },
			nu::Vector2{ 0, 4 },
			nu::Vector2{ 3, 3 },
			nu::Vector2{ 4, 1 },
			nu::Vector2{ 4, -1 },
			nu::Vector2{ 3, -3 },
			nu::Vector2{ 0, -4 },
		},
		nu::Color{1.0f, 1.0f, 1.0f}
	};


	//nu::Mesh playerMesh { mesh2, mesh4 };
	std::shared_ptr<nu::Model> playerModel = std::make_shared<nu::Model>(std::vector<nu::Mesh>{ mesh2, mesh4 });
	std::shared_ptr<nu::Model> enemyModel = std::make_shared<nu::Model>(std::vector<nu::Mesh>{ mesh1 });
	std::shared_ptr<nu::Model> bulletModel = std::make_shared<nu::Model>(std::vector<nu::Mesh>{ bulletMesh });
	std::shared_ptr<nu::Model> asteriodModel = std::make_shared<nu::Model>(std::vector<nu::Mesh>{ asteriodMesh });





} 