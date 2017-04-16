#include "SnakeCamera.h" 

// This function will be executed once when created 
void SnakeCamera::OnStart() 
{ 
    Behaviour::OnStart(); 
    snakeHead = GameObject::Find("Snake")->FindInChildren("Body")->
                FindInChildren("Head");
} 

// This function will be executed every frame 
void SnakeCamera::OnUpdate()
{ 
    Behaviour::OnUpdate(); 

    Vector3 snakeHeadPos = snakeHead->transform->GetPosition();
    Vector3 snakeForward = snakeHead->transform->GetForward();

    Vector3 offset = (camInFront ? 3.0f : -1.0f) * snakeForward +
                      Vector3::Up * 2.5f;
    transform->SetPosition(snakeHeadPos + offset);

    Vector3 lookAtPos = snakeHeadPos;
    lookAtPos += (camInFront ? 0.0f : 1.0f) *
                  snakeHead->transform->GetForward() * 5.0f;
    transform->LookAt(lookAtPos);
}

BANG_BEHAVIOUR_CLASS_IMPL(SnakeCamera);
