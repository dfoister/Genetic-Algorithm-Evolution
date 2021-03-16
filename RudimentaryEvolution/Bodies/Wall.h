#include "BaseObject.h"

class Wall : public BaseObject
{
public:
	Wall();
	Wall(CollisionBounds* col, Vector2f position);
	~Wall();

	bool updateObject(float dt) override;

};

