#include "TongueMove.h" 

// This function will be executed once when created 
void TongueMove::OnStart() 
{ 
    Behaviour::OnStart(); 
    m_originalPos = transform->GetLocalPosition();
} 

// This function will be executed every frame 
void TongueMove::OnUpdate() 
{ 
    Behaviour::OnUpdate(); 

    m_time += Time::deltaTime;
    Vector3 movement = Vector3::Forward *
                        (Math::Sin(m_time * 5.0f) * 0.25f - 0.01f);
    transform->SetLocalPosition(m_originalPos  + movement);
} 

BANG_BEHAVIOUR_CLASS_IMPL(TongueMove);
