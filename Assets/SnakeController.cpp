#include "SnakeController.h" 

#include "Bang/Camera.h"

// This function will be executed once when created 
void SnakeController::OnStart() 
{ 
    Behaviour::OnStart();
    p_skyCamera   = GameObject::Find("SkyCamera")->GetComponent<Camera>();
    p_snakeCamera = GameObject::Find("SnakeCamera")->GetComponent<Camera>();

    p_body = gameObject->FindInChildren("Body");
} 

// This function will be executed every frame 
void SnakeController::OnUpdate() 
{ 
    Behaviour::OnUpdate();

    if (Input::GetKeyDown(Input::Key::Z))
    {
        m_skyView = !m_skyView;
        Camera *cam = m_skyView ? p_skyCamera : p_snakeCamera;
        SceneManager::GetActiveScene()->SetCamera(cam);
    }

    float sign = 0.0f;
    if (Input::GetKey(Input::Key::A)) { sign = 1.0f; }
    else if (Input::GetKey(Input::Key::D)) { sign = -1.0f; }

    BodyTransform bodyTrans;

    bodyTrans.rotationDelta =
            Quaternion::AngleAxis(sign * c_rotSpeed * Time::deltaTime,
                                  Vector3::Up);
    bodyTrans.positionDelta =
            m_moveSpeed * Vector3::Forward * bodyTrans.rotationDelta;

    m_bodyTransforms.PushBack(bodyTrans);
    MoveBodyParts();
}

void SnakeController::MoveBodyParts()
{
    List<GameObject*> listBodyParts = p_body->GetChildren();
    Array<GameObject*> bodyParts = listBodyParts.ToArray();

    int i = 0;
    for (const BodyTransform &bodyTrans : m_bodyTransforms)
    {
        if (i >= bodyParts.Size()) { break; }

        bodyParts[i]->transform->RotateLocal(bodyTrans.rotationDelta);
        bodyParts[i]->transform->TranslateLocal(bodyTrans.positionDelta);
        ++i;
    }

    if (m_bodyTransforms.Size() > bodyParts.Size())
    {
        m_bodyTransforms.PopFront();
    }
}

BANG_BEHAVIOUR_CLASS_IMPL(SnakeController);
