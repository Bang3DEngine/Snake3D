#include "SkyCamera.h" 

// This function will be executed once when created 
void SkyCamera::OnStart() 
{ 
    Behaviour::OnStart(); 
    snakeHead = GameObject::Find("Snake")->FindInChildren("Body")->
                FindInChildren("Head");
} 

// This function will be executed every frame 
void SkyCamera::OnUpdate() 
{ 
    Behaviour::OnUpdate();

    Vector3 snakeHeadPos = snakeHead->transform->GetPosition();

    transform->SetPosition(snakeHeadPos + Vector3::Up * 70.0f);
    transform->LookInDirection(Vector3::Down, Vector3::Forward);
} 

BANG_BEHAVIOUR_CLASS_IMPL(SkyCamera);
