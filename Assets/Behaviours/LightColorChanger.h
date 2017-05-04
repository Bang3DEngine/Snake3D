#ifndef LightColorChanger_H 
#define LightColorChanger_H 

#include "Bang/Behaviour.h" 

// Here go your includes 

class LightColorChanger : public Behaviour 
{ 
OBJECT(LightColorChanger) 
public: 
    void OnStart() override; 
    void OnUpdate() override; 

    Color nextColor;
    float nextRange, nextIntensity;
    EpochTime nextChangeTime = 0;
    float changeSpeed = 1.0f;
}; 

#endif // LightColorChanger_H 

BANG_BEHAVIOUR_CLASS(LightColorChanger);
