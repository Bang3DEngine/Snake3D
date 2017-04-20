#include "SnakeController.h" 

#include "Bang/Camera.h"

#include "SkyCamera.h"
#include "SnakeCamera.h"
#include "WallsManager.h"

// This function will be executed once when created 
void SnakeController::OnStart() 
{ 
    Behaviour::OnStart();
    p_camera   = GameObject::Find("Camera")->GetComponent<Camera>();

    p_tailPrefab = AssetsManager::Load<Prefab>("Prefabs/Tail.bprefab");
    p_body = gameObject->FindInChildren("Body");
    p_head = p_body->FindInChildren("Head");
    p_collider1 = gameObject->FindInChildren("Collider1");
    p_collider2 = gameObject->FindInChildren("Collider2");
    p_collider3 = gameObject->FindInChildren("Collider3");

    BodyPart bodyPart;
    bodyPart.snake        = this;
    bodyPart.p_gameObject = p_head;
    bodyPart.p_prevPart   = nullptr;
    m_bodyParts.PushBack(bodyPart);
} 

// This function will be executed every frame 
void SnakeController::OnUpdate() 
{ 
    Behaviour::OnUpdate();

    m_time += Time::deltaTime;
    m_level = m_bodyParts.Size();
    m_moveSpeed = 5.0f + m_level * 1.5f;

    if (Input::GetKeyDown(Input::Key::Z))
    {
        m_cameraMode = (m_cameraMode + 1) % 3;
    }
    p_camera->gameObject->GetComponent<SkyCamera>()->SetEnabled( m_cameraMode == 0);
    p_camera->gameObject->GetComponent<SnakeCamera>()->SetEnabled( m_cameraMode >= 1 );
    p_camera->gameObject->GetComponent<SnakeCamera>()->camInFront = (m_cameraMode == 1);

    MoveBodyParts();

    if (WallsManager::CollidesWithWall(p_collider1) ||
        WallsManager::CollidesWithWall(p_collider2) ||
        WallsManager::CollidesWithWall(p_collider3))
    {
        SceneManager::LoadScene( "Scenes/Lose" );
    }
}

void SnakeController::OnFoodEat()
{
    GameObject *newTail = p_tailPrefab->Instantiate();

    BodyPart bodyPart;
    bodyPart.snake        = this;
    bodyPart.p_gameObject = newTail;
    bodyPart.p_prevPart   = &(m_bodyParts.Back());
    m_bodyParts.PushBack(bodyPart);

    Vector3 latestTailPos = p_body->GetChildren().Back()->transform->GetPosition();
    Vector3 newTailPos = latestTailPos - p_head->transform->GetForward() * 1.0f;
    newTail->transform->SetPosition(newTailPos);
    newTail->SetParent(p_body);
}

void SnakeController::MoveBodyParts()
{
    for (BodyPart &bodyPart : m_bodyParts)
    {
        bodyPart.MovePart();
    }
}

void BodyPart::MovePart()
{
    const float c_partSeparation = 1.2f;

    const bool isTheHead = !p_prevPart;
    float speedFactor = 1.0f;
    Vector3 prevPos;
    Vector3 currentPos = p_gameObject->transform->GetPosition();
    Vector3 moveDir = p_gameObject->transform->GetForward();
    if (isTheHead) // Head
    {
        float sign = 0.0f;
        if (Input::GetKey(Input::Key::A)) { sign = 1.0f; }
        else if (Input::GetKey(Input::Key::D)) { sign = -1.0f; }

        if (sign != 0.0f)
        {
            Quaternion rot =
             Quaternion::AngleAxis(sign * snake->c_rotSpeed * Time::deltaTime,
                                   Vector3::Up);
            p_gameObject->transform->RotateLocal(rot);
        }
        moveDir = p_gameObject->transform->GetForward();
    }
    else // Move relative to its prevPart
    {
        prevPos = p_prevPart->p_gameObject->transform->GetPosition();
        moveDir = (prevPos - currentPos).Normalized();
        speedFactor = (prevPos - currentPos).Length() * c_partSeparation;
    }

    p_gameObject->transform->LookInDirection(moveDir);
    p_gameObject->transform->Translate(moveDir * speedFactor *
                                       snake->m_moveSpeed * Time::deltaTime);
}


BANG_BEHAVIOUR_CLASS_IMPL(SnakeController);
