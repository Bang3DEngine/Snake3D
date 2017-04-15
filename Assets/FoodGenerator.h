#ifndef FoodGenerator_H 
#define FoodGenerator_H 

#include "Bang/Behaviour.h" 

// Here go your includes 

class FoodGenerator : public Behaviour 
{ 
OBJECT(FoodGenerator) 
public: 
    void OnStart() override; 
    void OnUpdate() override; 

    Prefab *foodPrefab = nullptr;
    GameObject *currentFoodBall = nullptr;
}; 

#endif // FoodGenerator_H 

BANG_BEHAVIOUR_CLASS(FoodGenerator);
