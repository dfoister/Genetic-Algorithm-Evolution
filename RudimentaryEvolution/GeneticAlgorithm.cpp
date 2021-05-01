#include "GeneticAlgorithm.h"
#include <iostream>


std::mt19937 engine;

GeneticAlgorithm::GeneticAlgorithm()
{
	selection_ = GLOBAL::SELECTION_TYPE;
	crossover_ = GLOBAL::CROSSOVER_TYPE;
	mutationFirst_ = GLOBAL::MUTATION_ONE_TYPE;
	mutationSecond_ = GLOBAL::MUTATION_TWO_TYPE;
	//computeAlgorithm();

}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

GeneticAlgorithm::GeneticAlgorithm(std::vector<Organism*> organisms) 
{
	selection_ = GLOBAL::SELECTION_TYPE;
	crossover_ = GLOBAL::CROSSOVER_TYPE;
	mutationFirst_ = GLOBAL::MUTATION_ONE_TYPE;
	mutationSecond_ = GLOBAL::MUTATION_TWO_TYPE;
	population_ = organisms;
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

float GeneticAlgorithm::getFitness(Organism* o)
{
	return o->getHealth() + o->getLifetime();
}


void GeneticAlgorithm::computePopulationFitness()
{
	std::sort(population_.begin(), population_.end(), [](Organism* o1, Organism* o2) { return o1->getHealth()+o1->getLifetime() < o2->getHealth() + o2->getLifetime(); });
/*
	for (Organism* o : population_) {
		std::cout << "Chromosome 1: ";

		for (float g : o->chromosome_) {
			std::cout << g << ", ";
		}
		std::cout << "\n";


	}
	std::cout << "\n\n\n\n\n\n";
	*/
}

void GeneticAlgorithm::selectionProcess()
{
	std::random_device rdSelection;

	if (selection_ == 1) selectionRandom();
	if (selection_ == 0) selectionRouletteWheel();
	//if (selection_ == SelectionType::STOCHASTIC) selectionStochasticUniversalSampling();
	if (selection_ == 2) selectionTournament();

	for(size_t i = 0; i < fittestPopulation_.size(); i++){

		std::vector<float> tempChromosome;
		tempChromosome = fittestPopulation_[i]->chromosome_;

		fittestPopulation_[i] = new Organism();
		fittestPopulation_[i]->setChromosome(tempChromosome);

	}

	
}

void GeneticAlgorithm::crossoverProcess()
{
	std::random_device rdCrossover;
	

	std::shuffle(fittestPopulation_.begin(), fittestPopulation_.end(), std::default_random_engine(rdCrossover()));
		
	int temp = 0;

	for (int i = 0; i < static_cast <int>(fittestPopulation_.size()); i++) {
		
		if (temp == 1) {
			temp = 0;
			continue;
		}

		if (temp == 0) {

			matingPair pair(fittestPopulation_.at(i), fittestPopulation_.at(i + 1));

			matingPairs.emplace_back(pair);

			temp = 1;
		}
	}

	
	if (crossover_ == 0) crossoverUniform();
	if (crossover_ == 1) crossoverSinglePoint();
	if (crossover_ == 2) crossoverMultiPoint();

}

void GeneticAlgorithm::mutationProcess()
{
	std::random_device rdMutation;

	engine.seed(rdMutation());

	if (mutationFirst_ == 2) mutationScramble();
	if (mutationFirst_ == 1) mutationSwap();
	if (mutationFirst_ == 3) mutationInversion();

	if (mutationSecond_ == 0) mutationCreep();
	if (mutationSecond_ == 1) mutationRandomResetting();

}

std::vector<Organism*> GeneticAlgorithm::createNewPopulation()
{
	return fittestPopulation_;
}

void GeneticAlgorithm::selectionRouletteWheel()
{
	float totalFitness = 0;

	for (Organism* i : population_) {
		totalFitness += getFitness(i);
	}
	
	std::cout << "Total Fitness: " << totalFitness << "\n";
	std::cout << "Population Size: " << population_.size() << "\n";

	std::uniform_real_distribution<> distrWheel(0.0f, totalFitness);
	std::cout << "New Population Size: " << fittestPopulation_.size() << "\n";
	
	bool next = 0;
	for (int i = 0; i < GLOBAL::SURVIVORS; i++) {

		float tempSpin = static_cast <float> (distrWheel(engine));
		float tempFitnessHolder = 0;

			for (Organism* i : population_) {
				tempFitnessHolder += getFitness(i);
				if (tempSpin <= tempFitnessHolder) {
					fittestPopulation_.emplace_back(i);
					break;
				}
			}



	}

	std::cout << "New Population Size: " << fittestPopulation_.size() << "\n";
}

void GeneticAlgorithm::selectionTournament()
{
	std::uniform_int_distribution<> distrPopulation(0, population_.size() - 1);

	for (int i = 0; i < GLOBAL::SURVIVORS; i++) {

		std::vector<Organism*> competitors;

		for (int j = 0; j < GLOBAL::TOURNAMENT_SIZE; i++) {
			
			competitors.emplace_back(population_[distrPopulation(engine)]);
		}


		std::sort(competitors.begin(), competitors.end(), [](Organism* o1, Organism* o2) { return o1->getHealth() + o1->getLifetime() < o2->getHealth() + o2->getLifetime(); });

		fittestPopulation_.emplace_back(competitors.at(0));

	}


}

void GeneticAlgorithm::selectionStochasticUniversalSampling()
{
}


void GeneticAlgorithm::selectionRandom()
{
	std::vector<int> numbers;

	for (int i = 0; i < 20; i++)      
		numbers.push_back(i);

	std::random_device rand;
	std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(rand()));

	for (int i = 0; i < GLOBAL::SURVIVORS; i++) {
		fittestPopulation_.emplace_back(population_[numbers[i]]);
	}

}



void GeneticAlgorithm::crossoverUniform()
{
	
	for (matingPair mp : matingPairs) {

		Organism* o1 = mp.getParentA();
		Organism* o2 = mp.getParentB();

		std::vector<float> o1Chromosome;
		std::vector<float> o2Chromosome;

		std::cout << "Chromosome 1: ";

		for (float g : o1->chromosome_) {
			std::cout << g << ", ";
		}

		std::cout << "\nChromosome 2: ";

		for (float g : o2->chromosome_) {
			std::cout << g << ", ";
		}

		std::cout << "\n";

		for (int i = 0; i < 6; i++) {

			
			if ((rand() % 2) != 0) {

				o1Chromosome.emplace_back(o2->getChromosome().at(i));
				o2Chromosome.emplace_back(o1->getChromosome().at(i));
			}
			else {

				o1Chromosome.emplace_back(o1->getChromosome().at(i));
				o2Chromosome.emplace_back(o2->getChromosome().at(i));
			}
		}
		
		std::cout << "\nChromosome 3: ";

		for (float g : o1Chromosome) {
			std::cout << g << ", ";
		}

		std::cout << "\nChromosome 4: ";

		for (float g : o2Chromosome) {
			std::cout << g << ", ";
		}

		std::cout << "\n\n";
		

		fittestPopulation_.emplace_back(new Organism(o1Chromosome));
		fittestPopulation_.emplace_back(new Organism(o2Chromosome));
	}


}

void GeneticAlgorithm::crossoverSinglePoint()
{

std::random_device crossoverSP;
engine.seed(crossoverSP());

std::uniform_int_distribution<> distrPopulation(1, 5);
int randomPop = distrPopulation(engine);

for (matingPair mp : matingPairs) {

	Organism* o1 = mp.getParentA();
	Organism* o2 = mp.getParentB();

	std::vector<float> o1Chromosome;
	std::vector<float> o2Chromosome;

	std::cout << "Chromosome 1: ";

	for (float g : o1->chromosome_) {
		std::cout << g << ", ";
	}

	std::cout << "\nChromosome 2: ";

	for (float g : o2->chromosome_) {
		std::cout << g << ", ";
	}

	std::cout << "\n";

	for (int i = 0; i < randomPop; i++) {

		o1Chromosome.emplace_back(o1->getChromosome().at(i));
		o2Chromosome.emplace_back(o2->getChromosome().at(i));

	}

	for (int i = randomPop; i < 6; i++) {
		o1Chromosome.emplace_back(o2->getChromosome().at(i));
		o2Chromosome.emplace_back(o1->getChromosome().at(i));
	}



	std::cout << "\nChromosome 3: ";

	for (float g : o1Chromosome) {
		std::cout << g << ", ";
	}

	std::cout << "\nChromosome 4: ";

	for (float g : o2Chromosome) {
		std::cout << g << ", ";
	}

	std::cout << "\n\n";

	fittestPopulation_.emplace_back(new Organism(o1Chromosome));
	fittestPopulation_.emplace_back(new Organism(o2Chromosome));
}


}

void GeneticAlgorithm::crossoverMultiPoint()
{

	std::vector<Organism*> newOrganisms;

	for (matingPair mp : matingPairs) {

		std::random_device rdNumbers;
		std::vector<int> numbers{ 1,2,3,4,5 };
		std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(rdNumbers()));

		std::vector<int> numbers2;
		numbers2.emplace_back(numbers.at(0));
		numbers2.emplace_back(numbers.at(1));

		std::sort(numbers2.begin(), numbers2.end());


		Organism* o1 = mp.getParentA();
		Organism* o2 = mp.getParentB();

		std::vector<float> o1Chromosome;
		std::vector<float> o2Chromosome;

		std::cout << "Chromosome 1: ";

		for (float g : o1->chromosome_) {
			std::cout << g << ", ";
		}

		std::cout << "\nChromosome 2: ";

		for (float g : o2->chromosome_) {
			std::cout << g << ", ";
		}

		std::cout << "\n";

		for (int i = 0; i < numbers2.at(0); i++) {

			o1Chromosome.emplace_back(o1->getChromosome().at(i));
			o2Chromosome.emplace_back(o2->getChromosome().at(i));

		}

		for (int i = numbers2.at(0); i < numbers2.at(1); i++) {
			o1Chromosome.emplace_back(o2->getChromosome().at(i));
			o2Chromosome.emplace_back(o1->getChromosome().at(i));
		}

		for (int i = numbers2.at(1); i < 6; i++) {
			o1Chromosome.emplace_back(o1->getChromosome().at(i));
			o2Chromosome.emplace_back(o2->getChromosome().at(i));
		}


		std::cout << "\nChromosome 3: ";

		for (float g : o1Chromosome) {
			std::cout << g << ", ";
		}

		std::cout << "\nChromosome 4: ";

		for (float g : o2Chromosome) {
			std::cout << g << ", ";
		}

		std::cout << "\n\n";

		fittestPopulation_.emplace_back(new Organism(o1Chromosome));
		fittestPopulation_.emplace_back(new Organism(o2Chromosome));
	}
}

void GeneticAlgorithm::mutationRandomResetting()
{
}

void GeneticAlgorithm::mutationCreep()
{
	std::random_device mutationCreep;
	engine.seed(mutationCreep());

	std::uniform_real_distribution<> distrPopulation(0.0f, 100.0f);

	for (Organism* o : fittestPopulation_) {

		for (size_t i = 0; i < o->chromosome_.size(); i++) {

			if (distrPopulation(engine) <= GLOBAL::MUTATION_CHANCE) {

				std::uniform_real_distribution<> distrCreep(-15.0f, 15.0f);
				float creep = distrCreep(engine);

				o->chromosome_[i] += creep;

			}
		}
	}

}

void GeneticAlgorithm::mutationScramble()
{
	std::random_device mutationScramble;
	engine.seed(mutationScramble());

	std::uniform_real_distribution<> distrPopulation(0.0f, 100.0f);

	std::random_device rdNumbers;


	std::vector<float> tempArray;

	for (Organism* o : fittestPopulation_) {

		if (distrPopulation(engine) <= GLOBAL::MUTATION_CHANCE) {

			std::vector<int> numbers{ 0,1,2,3,4,5 };
			std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(rdNumbers()));

			std::vector<int> numbers2;
			numbers2.emplace_back(numbers.at(0));
			numbers2.emplace_back(numbers.at(1));

			std::sort(numbers2.begin(), numbers2.end());

			for (int i = numbers2[0]; i <= numbers2[1]; i++) {
				tempArray.emplace_back(o->chromosome_[i]);
			}

			std::shuffle(tempArray.begin(), tempArray.end(), std::default_random_engine(rdNumbers()));

			for (int i = numbers[0]; i <= numbers[1]; i++) {
				o->chromosome_[i] = tempArray.back();
				tempArray.pop_back();
			}
		}
	}


}

void GeneticAlgorithm::mutationInversion()
{

	std::random_device mutationInversion;
	engine.seed(mutationInversion());

	std::uniform_real_distribution<> distrPopulation(0.0f, 100.0f);

	std::random_device rdNumbers;


	std::vector<float> tempArray;

	for (Organism* o : fittestPopulation_) {

			if (distrPopulation(engine) <= GLOBAL::MUTATION_CHANCE) {
				
				std::vector<int> numbers{ 0,1,2,3,4,5 };
				std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(rdNumbers()));

				std::vector<int> numbers2;
				numbers2.emplace_back(numbers.at(0));
				numbers2.emplace_back(numbers.at(1));

				std::sort(numbers2.begin(), numbers2.end());

				for (int i = numbers2[0]; i <= numbers2[1]; i++) {
					tempArray.emplace_back(o->chromosome_[numbers2[i]]);
				}

				for (int i = numbers[0]; i <= numbers[1]; i++) {
					o->chromosome_[i] = tempArray.back();
					tempArray.pop_back();
				}
			}
	}


}

void GeneticAlgorithm::mutationSwap()
{

	std::random_device mutationSwap;
	engine.seed(mutationSwap());

	std::uniform_real_distribution<> distrPopulation(0.0f, 100.0f);

	for (Organism* o : fittestPopulation_) {
		
		for (int i = 0; i < 2; i++) {

			if (distrPopulation(engine) <= GLOBAL::MUTATION_CHANCE) {

				std::uniform_int_distribution<> distrSwap(0,5);
				int index2 = distrSwap(engine);
				int index = distrSwap(engine);

				float temp = o->chromosome_[index];

				o->chromosome_[index] = o->chromosome_[index2];
				o->chromosome_[index2] = temp;
			}
		}
	}
}

void GeneticAlgorithm::mutationSwapTest()
{


	int counter = 0;
	std::uniform_real_distribution<> distrRandomTest(0.0f, 100.0f);
	for (int i = 0; i < 1000; i++) {
		if (distrRandomTest(engine) <= GLOBAL::MUTATION_CHANCE) {
			counter++;
		}
	}
	std::cout << "Chromosomes Mutated: " << counter;




	std::cout << "\n\n\n\n";

	std::vector<Organism*> fitpop(10);

	for (size_t i = 0; i < fitpop.size(); i++) {

		fitpop[i] = new Organism();
		std::cout << "\nChromosome " << i << ": ";
		for (float g : fitpop[i]->chromosome_) {
			std::cout << g << ", ";
		}


	}

	std::cout << "\n";






	std::random_device mutationSwap;
	engine.seed(mutationSwap());
	std::uniform_real_distribution<> distrPopulation(0.0f, 100.0f);

	for (Organism* o : fitpop) {

		if (distrPopulation(engine) <= GLOBAL::MUTATION_CHANCE) {

			for (int i = 0; i < 2; i++) {

				std::uniform_int_distribution<> distrSwap(0, 5);
				int index2 = distrSwap(engine);
				int index = distrSwap(engine);

				float temp = o->chromosome_[index];

				o->chromosome_[index] = o->chromosome_[index2];
				o->chromosome_[index2] = temp;
			}
		}
	}


	for (size_t i = 0; i < fitpop.size(); i++) {

		std::cout << "\nChromosome " << i << ": ";
		for (float g : fitpop[i]->chromosome_) {
			std::cout << g << ", ";
		}


	}


}

void GeneticAlgorithm::mutationScrambleTest()
{
	std::random_device mutationScramble;
	engine.seed(mutationScramble());

	std::uniform_real_distribution<> distrPopulation(0.0f, 100.0f);

	std::random_device rdNumbers;


	std::vector<Organism*> fitpop(10);

	for (size_t i = 0; i < fitpop.size(); i++) {

		fitpop[i] = new Organism();
		std::cout << "\nChromosome " << i << ": ";
		for (float g : fitpop[i]->chromosome_) {
			std::cout << g << ", ";
		}


	}

	std::cout << "\n";


	std::vector<float> tempArray;

	for (Organism* o : fitpop) {

		if (distrPopulation(engine) <= GLOBAL::MUTATION_CHANCE) {

			std::vector<int> numbers{ 0,1,2,3,4,5 };
			std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(rdNumbers()));

			std::vector<int> numbers2;
			numbers2.emplace_back(numbers.at(0));
			numbers2.emplace_back(numbers.at(1));

			std::sort(numbers2.begin(), numbers2.end());

			for (int i = numbers2[0]; i <= numbers2[1]; i++) {
				tempArray.emplace_back(o->chromosome_[i]);
			}

			std::shuffle(tempArray.begin(), tempArray.end(), std::default_random_engine(rdNumbers()));

			for (int i = numbers2[0]; i <= numbers2[1]; i++) {
				o->chromosome_[i] = tempArray.back();
				tempArray.pop_back();
			}
		}
	}


	for (size_t i = 0; i < fitpop.size(); i++) {

		std::cout << "\nChromosome " << i << ": ";
		for (float g : fitpop[i]->chromosome_) {
			std::cout << g << ", ";
		}


	}

}

void GeneticAlgorithm::mutationInversionTest()
{

	std::random_device mutationInversion;
	engine.seed(mutationInversion());

	std::uniform_real_distribution<> distrPopulation(0.0f, 100.0f);

	std::random_device rdNumbers;

	std::vector<Organism*> fitpop(10);

	for (size_t i = 0; i < fitpop.size(); i++) {

		fitpop[i] = new Organism();
		std::cout << "\nChromosome " << i << ": ";
		for (float g : fitpop[i]->chromosome_) {
			std::cout << g << ", ";
		}


	}

	std::cout << "\n";



	std::vector<float> tempArray;

	for (Organism* o : fitpop) {

		if (distrPopulation(engine) <= GLOBAL::MUTATION_CHANCE) {

			std::vector<int> numbers{ 0,1,2,3,4,5 };
			std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(rdNumbers()));

			std::vector<int> numbers2;
			numbers2.emplace_back(numbers.at(0));
			numbers2.emplace_back(numbers.at(1));

			std::sort(numbers2.begin(), numbers2.end());

			for (int i = numbers2[0]; i <= numbers2[1]; i++) {
				tempArray.emplace_back(o->chromosome_[i]);
			}

			for (int i = numbers2[0]; i <= numbers2[1]; i++) {
				o->chromosome_[i] = tempArray.back();
				tempArray.pop_back();
			}
		}
	}

	for (size_t i = 0; i < fitpop.size(); i++) {

		std::cout << "\nChromosome " << i << ": ";
		for (float g : fitpop[i]->chromosome_) {
			std::cout << g << ", ";
		}

	}

}

void GeneticAlgorithm::mutationCreepTest()
{
	std::random_device mutationCreep;
	engine.seed(mutationCreep());

	std::uniform_real_distribution<> distrPopulation(0.0f, 100.0f);

	std::vector<Organism*> fitpop(10);

	for (size_t i = 0; i < fitpop.size(); i++) {

		fitpop[i] = new Organism();
		std::cout << "\nChromosome " << i << ": ";
		for (float g : fitpop[i]->chromosome_) {
			std::cout << g << ", ";
		}


	}

	std::cout << "\n";


	for (Organism* o : fitpop) {

		for(size_t i = 0; i < o->chromosome_.size(); i++){

			if (distrPopulation(engine) <= GLOBAL::MUTATION_CHANCE) {

				std::uniform_real_distribution<> distrCreep(-15.0f, 15.0f);
				float creep = distrCreep(engine);

				o->chromosome_[i] += creep;

			}
		}
	}


	for (size_t i = 0; i < fitpop.size(); i++) {

		std::cout << "\nChromosome " << i << ": ";
		for (float g : fitpop[i]->chromosome_) {
			std::cout << g << ", ";
		}

	}
}


