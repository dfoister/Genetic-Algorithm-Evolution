#include <vector>
#include "Bodies/Organism.h"
#include "Constants.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm() {};
	~GeneticAlgorithm() {};

	GeneticAlgorithm(std::vector <Organism*> organisms) {
		computePopulationFitness();
		crossoverHealthyPopulation();
		mutateHealthyPopulation();
		createNewPopulation();
	};

	enum class SelectionType {
		ROULETTE,
		TOURNAMENT,
		STOCHASTIC,
		RANK,
		DEFAULT
	};

	enum class CrossoverType {
		SINGLEPOINT,
		MULTIPOINT,
		UNIFORM,
		DEFAULT
	};

	enum class MutationType {

	};

	std::vector<Organism*> getSortedPopulation();
	std::vector<Organism*> getFittestSelection();

	void computePopulationFitness();
	void crossoverHealthyPopulation();
	void mutateHealthyPopulation();
	void createNewPopulation();

	void selectionRouletteWheel();
	void selectionTournament();
	void selectionStochasticUniversalSampling();
	void selectionRank();

	void crossoverUniform();
	void crossoverSinglePoint();
	void crossoverMultiPoint();

	void mutationRandomValue();
	void mutationScramble();
	void mutationInversion();
	void mutationSwap();

protected:
	std::vector<Organism*> population_;
	std::vector<Organism*> fittestPopulation_;
	std::vector<Organism*> newPopulation_;



};

