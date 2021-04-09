#include "GeneticAlgorithm.h"


std::mt19937 engine;

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

	for (int i = 0; i < constants::FITTEST_POPULATION_SIZE; i++) {
		fittestPopulation_.emplace_back(population_[i]);
	}


}

void GeneticAlgorithm::selectionProcess()
{
	std::random_device rdSelection;

	if (selection_ == SelectionType::RANK) selectionRank();
	if (selection_ == SelectionType::ROULETTE || selection_ == SelectionType::DEFAULT) selectionRouletteWheel();
	if (selection_ == SelectionType::STOCHASTIC) selectionStochasticUniversalSampling();
	if (selection_ == SelectionType::TOURNAMENT) selectionTournament();
	
}

void GeneticAlgorithm::crossoverProcess()
{
	std::random_device rdCrossover;

	if (crossover_ == CrossoverType::UNIFORM || crossover_ == CrossoverType::DEFAULT) crossoverUniform();
	if (crossover_ == CrossoverType::SINGLEPOINT) crossoverSinglePoint();
	if (crossover_ == CrossoverType::MULTIPOINT) crossoverMultiPoint();

}

void GeneticAlgorithm::mutationProcess()
{
	std::random_device rdCrossover;
	engine.seed(rdCrossover);

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
	int totalFitness = 0;

	for (Organism* i : population_) {
		totalFitness += i->getHealth();
	}

	std::uniform_real_distribution<> distrWheel(0.0f, totalFitness);

	for (int i = 0; i < 5; i++) {

		float tempSpin = static_cast <float> (distrWheel(engine));
		float tempFitnessHolder = 0;

		for (Organism* i : population_) {
			tempFitnessHolder += i->getHealth();
			if (tempSpin <= tempFitnessHolder) {
				fittestPopulation_.emplace_back(i);
				continue;
			}
		}

	}
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
