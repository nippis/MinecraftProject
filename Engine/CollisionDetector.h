#pragma once

#include "Game/Entity.h"

class CollisionDetector
{
public:
  CollisionDetector();
  ~CollisionDetector();

  bool CollideY(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2);
};

