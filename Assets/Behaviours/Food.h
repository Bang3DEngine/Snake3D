#ifndef Food_H 
#define Food_H 

#include "Bang/Behaviour.h" 

// Here go your includes 

class Food : public Behaviour 
{ 
OBJECT(Food) 
public: 
    void OnStart() override; 
    void OnUpdate() override; 

private:
    float m_time = 0.0f;
    GameObject *snakeHead = nullptr;
}; 

#endif // Food_H 

BANG_BEHAVIOUR_CLASS(Food);
