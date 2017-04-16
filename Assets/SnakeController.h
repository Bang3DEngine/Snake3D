#ifndef SnakeController_H 
#define SnakeController_H 

#include "Bang/Behaviour.h" 

// Here go your includes 

class SnakeController : public Behaviour 
{ 
OBJECT(SnakeController) 
public: 
    void OnStart() override; 
    void OnUpdate() override; 

    void MoveBodyParts();

    bool m_skyView = true;
    Camera *p_skyCamera   = nullptr;
    Camera *p_snakeCamera = nullptr;

    GameObject *p_body = nullptr;
    GameObject *p_head = nullptr;
    const float c_rotSpeed  = 1.0f;
    float m_moveSpeed = 4.0f;

    float m_time = Math::Infinity<float>();

    List<Vector3> m_headPositions;
}; 

#endif // SnakeController_H 

BANG_BEHAVIOUR_CLASS(SnakeController);
