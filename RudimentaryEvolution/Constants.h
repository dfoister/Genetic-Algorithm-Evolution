#ifndef CONSTANTS_H
#define CONSTANTS_H

//  File Name : Constants.h   Purpose : Global Constants
namespace constants
{
	inline int POPULATION_SIZE;
	inline int NO_OF_FOOD;
	inline int NO_OF_POISON;

	inline int FITTEST_POPULATION_SIZE = 10;
	inline int TOURNAMENT_SIZE = 3;
	inline int SURVIVORS = 1;
	
	inline float MUTATION_CHANCE;

	inline float GENERATION_TIME_IN_SECONDS;

	const int FRAMERATE_LIMIT = 30;
}
#endif
