#include "CollisionBounds.h"

		class CollisionPair
		{
		protected:
			Vector2f normal;
			float penetration;
			CollisionBounds* a;
			CollisionBounds* b;
		public:
			CollisionPair();
			CollisionPair(CollisionBounds* a, CollisionBounds* b, float penetration, Vector2f normal);
			~CollisionPair();
			CollisionBounds* getCollisionA() const;
			CollisionBounds* getCollisionB() const;
			float getPenetration();
			Vector2f getNormal();
		};