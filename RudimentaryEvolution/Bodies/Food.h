#include "BaseObject.h"
class Food : public BaseObject
{
public:
	Food();
	~Food();
	bool updateObject(float dt) override;

};

