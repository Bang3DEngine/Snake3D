#ifndef SnakeController_H 
#define SnakeController_H 

#include "Bang/Behaviour.h" 

struct BodyPart
{
    static constexpr float c_rotSpeed  = 2.0f;
    static constexpr float m_moveSpeed = 6.0f;

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

    int m_cameraMode = 0;
    Camera *p_camera   = nullptr;

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
