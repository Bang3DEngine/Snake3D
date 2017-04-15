#include "FoodGenerator.h" 

// This function will be executed once when created 
void FoodGenerator::OnStart() 
{ 
    Behaviour::OnStart(); 
    foodPrefab = AssetsManager::Load<Prefab>("FoodBall.bprefab");
} 

// This function will be executed every frame 
void FoodGenerator::OnUpdate() 
{ 
    Behaviour::OnUpdate();
    if (!currentFoodBall)
    {
        currentFoodBall = foodPrefab->Instantiate();

        Vector3 minRect, maxRect;

        Vector3 randPoint;
        randPoint.x = Math::Lerp(minRect.x, maxRect.x, Random::Value());
        randPoint.y = Math::Lerp(minRect.y, maxRect.y, Random::Value());
        randPoint.z = Math::Lerp(minRect.z, maxRect.z, Random::Value());
        currentFoodBall->transform->SetPosition(randPoint);
    }
} 

BANG_BEHAVIOUR_CLASS_IMPL(FoodGenerator);
