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
    bool PointInsideSomeFoodBall(const Vector3& point) const;

    const float randomRangeAroundHead = 20.0f;

    Prefab *foodPrefab = nullptr;

    List<GameObject*> currentFoodBalls;
}; 

#endif // FoodGenerator_H 

BANG_BEHAVIOUR_CLASS(FoodGenerator);
