#include "BaseObject.h"
class Organism : public BaseObject {
public:
	Organism();
	~Organism();
	bool updateObject(float dt) override;


};

