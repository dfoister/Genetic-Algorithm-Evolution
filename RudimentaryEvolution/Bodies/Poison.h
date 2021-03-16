#include "BaseObject.h"

class Poison : public BaseObject
{
public:
	Poison();
	~Poison();
	bool updateObject(float dt) override;
};

