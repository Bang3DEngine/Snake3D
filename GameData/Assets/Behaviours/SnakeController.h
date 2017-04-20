#ifndef SnakeController_H 
#define SnakeController_H 

#include "Bang/Behaviour.h" 

class SnakeController;
struct BodyPart
{
    SnakeController *snake     = nullptr;
    GameObject *p_gameObject   = nullptr;
    const BodyPart *p_prevPart = nullptr;

    void MovePart();
};

class SnakeController : public Behaviour 
{ 
OBJECT(SnakeController) 
public: 
    void OnStart() override;
    void OnUpdate() override; 

    void OnFoodEat();
    void MoveBodyParts();

    const float c_rotSpeed  = 2.0f;
    float m_moveSpeed;

    int m_cameraMode = 0;
    Camera *p_camera   = nullptr;

    int m_level = 0;

    List<BodyPart> m_bodyParts;
    Prefab *p_tailPrefab    = nullptr;
    GameObject *p_body      = nullptr;
    GameObject *p_head      = nullptr;
    GameObject *p_collider1 = nullptr;
    GameObject *p_collider2 = nullptr;
    GameObject *p_collider3 = nullptr;

    float m_time = Math::Infinity<float>();
}; 

#endif // SnakeController_H 

BANG_BEHAVIOUR_CLASS(SnakeController);