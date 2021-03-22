#include "GeneticAlgorithm.h"

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
