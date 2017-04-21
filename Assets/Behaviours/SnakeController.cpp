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
    m_moveSpeed = 15.0f + m_level * 0.5f;
    m_rotSpeed  = 2.0f + m_level * 0.1f;

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
        Lose();
    }

    CheckSelfCollision();
}

void SnakeController::OnFoodEat()
{
    GameObject *newTail = p_tailPrefab->Instantiate();
    // newTail->GetComponent<Renderer>()->UseMaterialCopy();
    // newTail->GetComponent<Renderer>()->GetMaterial()->SetDiffuseColor(
    //          Random::GetColorOpaque());

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

void SnakeController::CheckSelfCollision()
{
    Array<GameObject*> children = p_body->GetChildren().ToArray();
    ENSURE(children.Size() >= 2);

    GameObject *head = p_head;
    for (int i = 2; i < children.Size(); ++i)
    {
        GameObject *bodyPart = children[i];
        if (bodyPart->GetBoundingSphere().CheckCollision(p_collider1->GetBoundingSphere()) ||
            bodyPart->GetBoundingSphere().CheckCollision(p_collider2->GetBoundingSphere()) ||
            bodyPart->GetBoundingSphere().CheckCollision(p_collider3->GetBoundingSphere()))
        {
            Lose();
        }
    }
}

void SnakeController::MoveBodyParts()
{
    float i = 0.0f;
    for (BodyPart &bodyPart : m_bodyParts)
    {
        bodyPart.MovePart();
    }
}

void SnakeController::Lose()
{
    SceneManager::LoadScene( "Scenes/Lose" );
}

void BodyPart::MovePart()
{
    const float c_separation = 1.0f;

    const bool isTheHead = !p_prevPart;
    Vector3 prevBodyPos = p_prevPart ? p_prevPart->p_gameObject->transform->GetPosition() :
                                       Vector3::Zero;
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
             Quaternion::AngleAxis(sign * snake->m_rotSpeed * Time::deltaTime,
                                   Vector3::Up);
            p_gameObject->transform->RotateLocal(rot);
        }
        moveDir = p_gameObject->transform->GetForward();
        p_gameObject->transform->Translate(moveDir * snake->m_moveSpeed *
                                           Time::deltaTime);
    }
    else // Move relative to its prevPart
    {
        moveDir = (prevBodyPos - currentPos).Normalized();
        Vector3 newPos = prevBodyPos - moveDir * c_separation;
        p_gameObject->transform->SetPosition(newPos);
    }

    p_gameObject->transform->LookInDirection(moveDir);
}


BANG_BEHAVIOUR_CLASS_IMPL(SnakeController);
