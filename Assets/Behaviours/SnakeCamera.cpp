#include "SnakeCamera.h" 

#include "SnakeController.h"

// This function will be executed once when created 
void SnakeCamera::OnStart() 
{ 
    Behaviour::OnStart();
    snakeHead = GameObject::Find("Snake")->FindInChildren("Body")->
                FindInChildren("Head");
    p_snakeController = snakeHead->GetComponentInParent<SnakeController>();
} 

// This function will be executed every frame 
void SnakeCamera::OnUpdate()
{
    Behaviour::OnUpdate();

    Vector3 snakeHeadPos = snakeHead->transform->GetPosition();

    float mouseY = 0.5f; // Input::GetMouseCoordsNDC().y;
    if (Math::Abs(mouseY) >= 0.3f)
    {
        m_angleVerticalDest  = Math::Map(mouseY, -1.0f, 1.0f, -60.0f, -5.0f);
    }
    m_angleVertical = Math::Lerp(m_angleVertical, m_angleVerticalDest,
                                 Time::deltaTime);

    Vector3 offset = -snakeHead->transform->GetForward();
    offset = Quaternion::AngleAxis(Math::Deg2Rad(m_angleVertical),
                                   snakeHead->transform->GetRight()) * offset;

    float newZoom = (25.0f + p_snakeController->m_level * 0.5f);
    m_zoom = Math::Lerp(m_zoom, newZoom, Time::deltaTime);
    m_zoom = Math::Max(m_zoom, 25.0f);

    offset *= m_zoom;;

    Vector3 newPosition = snakeHeadPos + offset;

    transform->SetPosition(newPosition);
    transform->LookAt(snakeHeadPos, Vector3::Up);
}

BANG_BEHAVIOUR_CLASS_IMPL(SnakeCamera);
