spe#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
	selection_ = SelectionType::DEFAULT;
	crossover_ = CrossoverType::DEFAULT;
	mutation_ = MutationType::DEFAULT;
	computeAlgorithm();

	int i = 4;
	int yes = 0;
	int h = i + i;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

GeneticAlgorithm::GeneticAlgorithm(std::vector<Organism*> organisms) 
{
	selection_ = SelectionType::DEFAULT;
	crossover_ = CrossoverType::DEFAULT;
	mutation_ = MutationType::DEFAULT;
	population_ = organisms;
	computeAlgorithm();
}

GeneticAlgorithm::GeneticAlgorithm(std::vector<Organism*> organisms, SelectionType selection, CrossoverType crossover, MutationType mutation)
{
	population_ = organisms;
	selection_ = selection;
	crossover_ = crossover;
	mutation_ = mutation;
	computeAlgorithm();
} 

void GeneticAlgorithm::computeAlgorithm()
{
	computePopulationFitness();
	selectionProcess();
	crossoverProcess();
	mutationProcess();
	createNewPopulation();

}

std::vector<Organism*> GeneticAlgorithm::getSortedPopulation()
{
	return population_;
}

std::vector<Organism*> GeneticAlgorithm::getFittestSelection()
{
	return fittestPopulation_;
}

void GeneticAlgorithm::computePopulationFitness()
{

	std::sort(population_.begin(), population_.end(), [](Organism* o1, Organism* o2) { return o1->getHealth() < o2->getHealth(); });


}

void GeneticAlgorithm::selectionProcess()
{
	if (selection_ == SelectionType::RANK) selectionRank();
	if (selection_ == SelectionType::ROULETTE || selection_ == SelectionType::DEFAULT) selectionRouletteWheel();
	if (selection_ == SelectionType::STOCHASTIC) selectionStochasticUniversalSampling();
	if (selection_ == SelectionType::TOURNAMENT) selectionTournament();
	
}

void GeneticAlgorithm::crossoverProcess()
{
	if (crossover_ == CrossoverType::UNIFORM || crossover_ == CrossoverType::DEFAULT) crossoverUniform();
	if (crossover_ == CrossoverType::SINGLEPOINT) crossoverSinglePoint();
	if (crossover_ == CrossoverType::MULTIPOINT) crossoverMultiPoint();

}

void GeneticAlgorithm::mutationProcess()
{
	if (mutation_ == MutationType::SCRAMBLE || mutation_ == MutationType::DEFAULT) mutationScramble();
	if (mutation_ == MutationType::SWAP) mutationSwap();
	if (mutation_ == MutationType::INVERSION) mutationInversion();
	if (mutation_ == MutationType::RANDOM) mutationRandomValue();
}

void GeneticAlgorithm::createNewPopulation()
{
}

void GeneticAlgorithm::selectionRouletteWheel()
{
}

void GeneticAlgorithm::selectionTournament()
{
}

void GeneticAlgorithm::selectionStochasticUniversalSampling()
{
}

void GeneticAlgorithm::selectionRank()
{
}

void GeneticAlgorithm::crossoverUniform()
{
}

void GeneticAlgorithm::crossoverSinglePoint()
{
}

void GeneticAlgorithm::crossoverMultiPoint()
{
}

void GeneticAlgorithm::mutationRandomValue()
{
}

void GeneticAlgorithm::mutationScramble()
{
}

void GeneticAlgorithm::mutationInversion()
{
}

void GeneticAlgorithm::mutationSwap()
{
}
