#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include "matingPair.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
		~GeneticAlgorithm();

	GeneticAlgorithm(std::vector <Organism*> organisms);


	void computeAlgorithm();

	std::vector<Organism*> getSortedPopulation();
	std::vector<Organism*> getFittestSelection();
	float getFitness(Organism* o);

	void computePopulationFitness();
	void selectionProcess();
	void crossoverProcess();
	void mutationProcess();
	std::vector<Organism*> createNewPopulation();

	void selectionRouletteWheel();
	void selectionTournament();
	void selectionStochasticUniversalSampling();
	void selectionRandom();

	void crossoverUniform();
	void crossoverSinglePoint();
	void crossoverMultiPoint();

	void mutationRandomResetting();
	void mutationCreep();

	void mutationScramble();
	void mutationInversion();
	void mutationSwap();

	void mutationSwapTest();
	void mutationScrambleTest();
	void mutationInversionTest();
	void mutationCreepTest();
	void mutationRandomResettingTest();


protected:
	std::vector<Organism*> population_;
	std::vector<Organism*> fittestPopulation_;
	std::vector<Organism*> newPopulation_;
	std::vector<matingPair> matingPairs;

	int selection_; // 0 = Uniform, 1 = SinglePoint, 2 = MultiPoint
	int crossover_; // 0 = Roulette, 1 = Random, 2 = Tournament
	int mutationFirst_; // 0 = None 1 = Swap, 2 = Shuffle, 3 = Inversion
	int mutationSecond_; // 0 = Creep, 1 = Random Resetting



};
#endif

