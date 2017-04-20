#ifndef SkyCamera_H 
#define SkyCamera_H 

#include "Bang/Behaviour.h" 

// Here go your includes 

class SkyCamera : public Behaviour 
{ 
OBJECT(SkyCamera) 
public: 
    void OnStart() override; 
    void OnUpdate() override; 

    GameObject *snakeHead = nullptr;
}; 

#endif // SkyCamera_H 

BANG_BEHAVIOUR_CLASS(SkyCamera);
