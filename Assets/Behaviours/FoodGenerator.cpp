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
    while (currentFoodBalls.Size() < 5)
    {
        GameObject *foodBall = foodPrefab->Instantiate();

        GameObject *snakeHead = GameObject::Find("Snake")->
                                    FindInChildren("Body")->
                                    FindInChildren("Head");
        Vector3 headPos = snakeHead->transform->GetPosition();

        Vector3 foodBallPos;
        do
        {
            Vector3 randOffset = Vector3::Zero;
            randOffset.x = Math::Lerp(-randomRangeAroundHead,
                                      randomRangeAroundHead,
                                      Random::Value());
            randOffset.z = Math::Lerp(-randomRangeAroundHead,
                                      randomRangeAroundHead,
                                      Random::Value());
            foodBallPos = headPos + randOffset;
        }
        while ( PointInsideSomeFoodBall(foodBallPos) );

        foodBall->transform->SetPosition(foodBallPos);

        currentFoodBalls.Add(foodBall);
    }
}

bool FoodGenerator::PointInsideSomeFoodBall(const Vector3 &point) const
{
    for (GameObject *foodBall : currentFoodBalls)
    {
        if (foodBall->GetAABBox().Contains(point)) { return true; }
    }
    return false;
}

BANG_BEHAVIOUR_CLASS_IMPL(FoodGenerator);
