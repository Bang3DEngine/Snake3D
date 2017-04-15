#ifndef SnakeCamera_H 
#define SnakeCamera_H 

#include "Bang/Behaviour.h" 

// Here go your includes 

class SnakeCamera : public Behaviour 
{ 
OBJECT(SnakeCamera) 
public: 
    void OnStart() override; 
    void OnUpdate() override; 

    GameObject *snakeHead = nullptr;
}; 

#endif // SnakeCamera_H 

BANG_BEHAVIOUR_CLASS(SnakeCamera);
