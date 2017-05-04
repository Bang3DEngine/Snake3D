#include "FoodGenerator.h" 

#include "WallsManager.h"

// This function will be executed once when created 
void FoodGenerator::OnStart() 
{ 
    Behaviour::OnStart(); 
    foodPrefab = AssetsManager::Load<Prefab>("Prefabs/FoodBall.bprefab");
} 

// This function will be executed every frame 
void FoodGenerator::OnUpdate() 
{ 
    Behaviour::OnUpdate();
    while (currentFoodBalls.Size() < 25)
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
        while ( FoodBallPositionInvalid(foodBallPos) );

        foodBall->transform->SetPosition(foodBallPos);

        currentFoodBalls.Add(foodBall);
    }
}

bool FoodGenerator::FoodBallPositionInvalid(const Vector3 &point) const
{
    for (GameObject *foodBall : currentFoodBalls)
    {
        if (foodBall->GetAABBox().Contains(point)) { return true; }
    }

    if (WallsManager::CollidesWithWall(point))
    {
        return true;
    }

    return false;
}

BANG_BEHAVIOUR_CLASS_IMPL(FoodGenerator);
