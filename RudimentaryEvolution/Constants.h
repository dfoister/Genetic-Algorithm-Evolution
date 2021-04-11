#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <random>

//  File Name : Constants.hpp    Purpose : Global Constants
namespace constants
{
	const int POPULATION_SIZE = 20;    
	const int NO_OF_FOOD = 15;
	const int NO_OF_POISON = 10;

	inline static std::mt19937 mt;

	const int FITTEST_POPULATION_SIZE = 10;
	const int TOURNAMENT_SIZE = 3;
	const int SURVIVORS = 1;
	
	const float MUTATION_CHANCE = 10.0f;

	const float GENERATION_TIME_IN_SECONDS = 30.0f;

	const int FRAMERATE_LIMIT = 30;
}
#endif
