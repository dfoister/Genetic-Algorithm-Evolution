#ifndef CONSTANTS_H
#define CONSTANTS_H

//  File Name : Constants.h   Purpose : Global Constants
namespace GLOBAL
{
	inline int POPULATION_SIZE;
	inline int NO_OF_FOOD;
	inline int NO_OF_POISON;

	inline int SURVIVORS = 10;
	inline int TOURNAMENT_SIZE = 3;
	inline int TOURNAMENT_SURVIVORS = 1;

	inline int SURVIVOR_PERCENTAGE;
	inline int SELECTION_TYPE;
	inline int CROSSOVER_TYPE;
	inline int MUTATION_ONE_TYPE;
	inline int MUTATION_TWO_TYPE;

	inline float CREEP_RANGE;
	inline float RAND_LOWER;
	inline float RAND_UPPER;
	
	inline float MUTATION_CHANCE;

	inline float GENERATION_TIME_IN_SECONDS;

	const int FRAMERATE_LIMIT = 30;
}
#endif
