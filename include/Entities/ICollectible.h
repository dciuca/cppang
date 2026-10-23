#pragma once

#include "IEntity.h"
#include "GameTypes.h"

class ICollectible : public IEntity 
{
public:
   virtual CollectibleType GetCollectibleType() const = 0; 
};