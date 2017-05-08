#ifndef SnakeCamera_H 
#define SnakeCamera_H 

#include "Bang/Behaviour.h" 

// Here go your includes 

class SnakeController;
class SnakeCamera : public Behaviour 
{ 
OBJECT(SnakeCamera) 
public:
    SnakeController *p_snakeController = nullptr;
    float m_angleVertical     = 0.0f;
    float m_angleVerticalDest = -30.0f;
    float m_zoom = 0.0f;

    void OnStart() override;
    void OnUpdate() override;

    GameObject *snakeHead = nullptr;
}; 

#endif // SnakeCamera_H 

BANG_BEHAVIOUR_CLASS(SnakeCamera);
