#include "Collider.h"

		class CollisionPair
		{
		protected:
			Vector2f normal_;
			float penetration_;
			Collider* a_;
			Collider* b_;
		public:
			CollisionPair();
			CollisionPair(Collider* a, Collider* b, float penetration, Vector2f normal);
			~CollisionPair();
			Collider* getCollisionA() const;
			Collider* getCollisionB() const;
			float getPenetration();
			Vector2f getNormal();
		};