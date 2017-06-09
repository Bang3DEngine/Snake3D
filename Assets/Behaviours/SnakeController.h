#ifndef SnakeController_H 
#define SnakeController_H 

#include "Bang/Behaviour.h" 
#include ".SnakeController.refl.h"

class SnakeController;
struct BodyPart
{
    SnakeController *snake     = nullptr;
    GameObject *p_gameObject   = nullptr;
    const BodyPart *p_prevPart = nullptr;

    void MovePart();
};

BP_REFLECT_CLASS(SnakeController)
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
    void GrowSnake();

    float m_rotSpeed;

    BP_REFLECT_VARIABLE(MoveSpeed)
    float m_moveSpeed = 15.0f;

    bool m_fpsCamera = true;
    Camera *p_camera   = nullptr;

    int m_level = 0;

    int m_score = 0;
    List<BodyPart> m_bodyParts;
    UIText *p_scoreText     = nullptr;
    Prefab *p_tailPrefab    = nullptr;
    GameObject *p_body      = nullptr;
    GameObject *p_head      = nullptr;
    GameObject *p_collider1 = nullptr;
    GameObject *p_collider2 = nullptr;
    GameObject *p_collider3 = nullptr;

    float m_time = Math::Infinity<float>();

    BP_REFLECT_DEFINITIONS_SnakeController();
}; 

#endif // SnakeController_H 

BANG_BEHAVIOUR_CLASS(SnakeController);
