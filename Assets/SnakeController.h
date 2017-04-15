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
    const float c_rotSpeed  = 0.0f;
    float m_moveSpeed = 1.0f;

    float m_time = 0.0f;

    struct BodyTransform
    {
        Vector3 positionDelta;
        Quaternion rotationDelta;
    };
    List<BodyTransform> m_bodyTransforms;
}; 

#endif // SnakeController_H 

BANG_BEHAVIOUR_CLASS(SnakeController);
