#pragma once
#include <cstdlib>


namespace nu 
{

	inline int RandomInt()
	{
		return rand();
	}

	/// <summary>
	/// Get random integer value [0, max)
	/// </summary>
	/// <param name="max">exclusive max</param>
	/// <returns>Returns a random number between 0 and max exclusive</returns>
	inline int RandomInt(int max) 
	{
		return rand() % max;
	}

	/// <summary>
	/// Get a random integer value between to [min, max]
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns>Random num between min and max</returns>
	inline int RandomInt(int min, int max)
	{
		return min + RandomInt((max - min) + 1);
	}

	inline float Randomfloat()
	{
		//rand() = 0 <- RAND_MAX
		return rand() / (float)RAND_MAX;
	}

	inline float Randomfloat(float max)
	{
		//0 <-> 1 * max
		return Randomfloat() * max;
	}

	inline float Randomfloat(float min, float max)
	{
		return min + Randomfloat() * (max - min);
	}
}