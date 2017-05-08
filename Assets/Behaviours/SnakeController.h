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
    void CheckSelfCollision();
    void MoveBodyParts();
    void Lose();

    float m_rotSpeed, m_moveSpeed;

    bool m_fpsCamera = true;
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
