#include "pch.h"
#include "../RudimentaryEvolution/GeneticAlgorithm.h"
#include "../RudimentaryEvolution/Bodies/Organism.h"
#include <vector>



TEST(TestCaseName, TestName) {

	std::vector<Organism*> population(20);

	for (Organism* o : population) {
		o = new Organism();
	}

	


	GeneticAlgorithm* GA = new GeneticAlgorithm();


  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}