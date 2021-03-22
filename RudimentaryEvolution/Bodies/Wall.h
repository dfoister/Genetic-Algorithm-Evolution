#include "BaseObject.h"

class Wall : public BaseObject
{
public:
	Wall();
	Wall(Collider* col, Vector2f position);
	~Wall();

	bool updateObject(float dt) override;

};

