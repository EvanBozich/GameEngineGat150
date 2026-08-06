#pragma once
#include <cstdlib>
#include <random>


namespace nu 
{
	
	inline std::mt19937& Generator()
	{
		static std::random_device randDevice;
		static std::mt19937 generator(randDevice());

		return generator;
	}

	inline void SeedRandom(unsigned int seed)
	{
		Generator().seed(seed);
	}

	inline int RandomInt()
	{
		static std::uniform_int_distribution<> dist;
		return dist(Generator());
	}

	/// <summary>
	/// Get random integer value [0, max)
	/// </summary>
	/// <param name="max">exclusive max</param>
	/// <returns>Returns a random number between 0 and max exclusive</returns>
	inline int RandomInt(int max) 
	{
		std::uniform_int_distribution<> dist(0, max - 1);
		return dist(Generator());
	}

	/// <summary>
	/// Get a random integer value between to [min, max]
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns>Random num between min and max</returns>
	inline int RandomInt(int min, int max)
	{
		std::uniform_int_distribution<> dist(min, max);
		return dist(Generator());
	}

	inline float Randomfloat()
	{
		static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		return dist(Generator());
	}

	inline float Randomfloat(float max)
	{
		std::uniform_real_distribution<float> dist(0, max);
		return dist(Generator());
	}

	inline float Randomfloat(float min, float max)
	{
		std::uniform_real_distribution<float> dist(min, max);
		return dist(Generator());
	}

	inline bool RandomBool()
	{
		std::bernoulli_distribution dist(0.5f);
		return dist(Generator());
	}
}