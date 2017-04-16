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
    Vector3 newPosition = transform->GetPosition();
    newPosition.x = snakeHeadPos.x;
    newPosition.z = snakeHeadPos.z;
    transform->SetPosition(newPosition);
    //transform->LookAt(snakeHeadPos + snakeHead->transform->GetForward());
} 

BANG_BEHAVIOUR_CLASS_IMPL(SkyCamera);
