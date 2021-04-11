#include "matingPair.h"

class GeneticAlgorithm
{
public:
	enum class SelectionType {
		ROULETTE,
		TOURNAMENT,
		STOCHASTIC,
		RANDOM,
		DEFAULT
	};

	enum class CrossoverType {
		SINGLEPOINT,
		MULTIPOINT,
		UNIFORM,
		DEFAULT
	};

	enum class MutationType {
		RANDOM,
		SCRAMBLE,
		INVERSION,
		SWAP,
		DEFAULT
	};

	GeneticAlgorithm();
		~GeneticAlgorithm();

	GeneticAlgorithm(std::vector <Organism*> organisms);
	GeneticAlgorithm(std::vector <Organism*> organisms, SelectionType selection, CrossoverType crossover, MutationType mutation);


	void computeAlgorithm();

	std::vector<Organism*> getSortedPopulation();
	std::vector<Organism*> getFittestSelection();

	void computePopulationFitness();
	void selectionProcess();
	void crossoverProcess();
	void mutationProcess();
	void createNewPopulation();

	void selectionRouletteWheel();
	void selectionTournament();
	void selectionStochasticUniversalSampling();
	void selectionRandom();

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
	std::vector<matingPair> matingPairs;

	SelectionType selection_;
	CrossoverType crossover_;
	MutationType mutation_;



};

