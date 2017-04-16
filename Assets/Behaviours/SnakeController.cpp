#include "SnakeController.h" 

#include "Bang/Camera.h"

#include "SkyCamera.h"
#include "SnakeCamera.h"

// This function will be executed once when created 
void SnakeController::OnStart() 
{ 
    Behaviour::OnStart();
    p_camera   = GameObject::Find("Camera")->GetComponent<Camera>();

    p_body = gameObject->FindInChildren("Body");
    p_head = p_body->FindInChildren("Head");
    m_headPositions.PushBack(p_head->transform->GetPosition());
} 

// This function will be executed every frame 
void SnakeController::OnUpdate() 
{ 
    Behaviour::OnUpdate();

    if (Input::GetKeyDown(Input::Key::Z))
    {
        m_cameraMode = (m_cameraMode + 1) % 3;
    }
    p_camera->gameObject->GetComponent<SkyCamera>()->SetEnabled( m_cameraMode == 0);
    p_camera->gameObject->GetComponent<SnakeCamera>()->SetEnabled( m_cameraMode >= 1 );
    p_camera->gameObject->GetComponent<SnakeCamera>()->camInFront = (m_cameraMode == 1);

    float sign = 0.0f;
    if (Input::GetKey(Input::Key::A)) { sign = 1.0f; }
    else if (Input::GetKey(Input::Key::D)) { sign = -1.0f; }

    if (sign != 0.0f)
    {
        Quaternion rot = Quaternion::AngleAxis(sign * c_rotSpeed * Time::deltaTime,
                                               Vector3::Up);
        p_head->transform->RotateLocal(rot);
    }
    Vector3 forward = p_head->transform->GetForward();
    p_head->transform->Translate(forward * m_moveSpeed * Time::deltaTime);

    m_time += Time::deltaTime;
    if (m_time >= 0.05f)
    {
        m_time = 0.0f;
        m_headPositions.PushBack(p_head->transform->GetPosition());
    }

    MoveBodyParts();
}

void SnakeController::MoveBodyParts()
{
    ENSURE(m_headPositions.Size() >= 2);

    List<GameObject*> listBodyParts = p_body->GetChildren();
    Array<GameObject*> bodyParts = listBodyParts.ToArray();
    Array<Vector3> headPositions = m_headPositions.ToArray();

    for (GameObject *bodyPart : bodyParts)
    {
        if (bodyPart == p_head) { continue; }

        Vector3 bodyPos = bodyPart->transform->GetPosition();
        Vector3 nextPos = m_headPositions.Front();
        for (int i = 0; i < headPositions.Size() - 1; ++i)
        {
            const Vector3 &bodyPosPrev  = headPositions[i];
            const Vector3 &bodyPosNext = headPositions[i+1];
            Vector3 dirToPrev = bodyPosPrev - bodyPos;
            Vector3 dirToNext = bodyPosNext - bodyPos;
            if (Vector3::Dot(dirToPrev, dirToNext) < 0)
            {
                nextPos = bodyPosNext;
            }
        }

        Vector3 dir = (nextPos - bodyPart->transform->GetPosition()).Normalized();
        bodyPart->transform->Translate(dir * m_moveSpeed * Time::deltaTime);
        bodyPart->transform->LookAt(nextPos);
    }
}

BANG_BEHAVIOUR_CLASS_IMPL(SnakeController);
