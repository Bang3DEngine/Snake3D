#include "Food.h" 

#include "SnakeController.h"

// This function will be executed once when created 
void Food::OnStart() 
{ 
    Behaviour::OnStart(); 
    m_time = Random::Value() * 100.0f;
    snakeHead = GameObject::Find("Snake")->FindInChildren("Body")->FindInChildren("Head");
} 

// This function will be executed every frame 
void Food::OnUpdate() 
{ 
    Behaviour::OnUpdate(); 

    transform->Rotate( Quaternion::AngleAxis(1.0f * Time::deltaTime, Vector3::Up) );

    m_time += Time::deltaTime;
    float scale = Math::Sin(m_time * 4.0f);
    scale = Math::Map(scale, -1.0f, 1.0f, 0.5f, 0.8f);

    Sphere foodSphere = gameObject->GetBoundingSphere();
    if ( snakeHead->GetBoundingSphere().CheckCollision(foodSphere) )
    {
        SnakeController *snakeController = snakeHead->GetComponentInParent<SnakeController>();
        if (snakeController)
        {
            snakeController->OnFoodEat();
        }

        GameObject::Destroy(gameObject);
    }

    transform->SetScale(scale);
} 

BANG_BEHAVIOUR_CLASS_IMPL(Food);
