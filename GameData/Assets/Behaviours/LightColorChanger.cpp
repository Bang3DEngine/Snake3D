#include "LightColorChanger.h" 

// This function will be executed once when created 
void LightColorChanger::OnStart() 
{ 
    Behaviour::OnStart(); 
} 

// This function will be executed every frame 
void LightColorChanger::OnUpdate() 
{ 
    Behaviour::OnUpdate();

    if (Time::GetNow() >= nextChangeTime)
    {
        nextIntensity = Random::Range(0.1f, 1.0f);
        nextRange = Random::Range(5.0f, 30.0f);
        nextColor = Random::GetColorOpaque();
        nextChangeTime = Time::GetNow() + Random::Range(1000, 2000);
    }

    PointLight *light = gameObject->GetComponent<PointLight>();
    if (light)
    {
        float t = Time::deltaTime * changeSpeed;
        light->SetIntensity( Math::Lerp(light->GetIntensity(), nextIntensity, t) );
        light->SetRange( Math::Lerp(light->GetRange(), nextRange, t) );
        light->SetColor( Color::Lerp(light->GetColor(), nextColor, t) );
    }
} 

BANG_BEHAVIOUR_CLASS_IMPL(LightColorChanger);
