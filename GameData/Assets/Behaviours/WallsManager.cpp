#include "WallsManager.h" 

List<GameObject*> WallsManager::s_walls;

// This function will be executed once when created 
void WallsManager::OnStart() 
{ 
    Behaviour::OnStart(); 
    s_walls.Clear();

    GameObject *walls = GameObject::Find("Scenario")->FindInChildren("Walls");
    for (GameObject *wall : walls->GetChildren())
    {
        s_walls.PushBack(wall);
    }

} 

// This function will be executed every frame 
void WallsManager::OnUpdate() 
{ 
    Behaviour::OnUpdate(); 

}

bool WallsManager::CollidesWithWall(GameObject *go)
{
    Sphere goSphere = go->GetBoundingSphere(false);
    for (GameObject *wall : WallsManager::s_walls)
    {
        if (goSphere.CheckCollision(wall->GetAABBox()))
        {
            return true;
        }
    }
    return false;
}

BANG_BEHAVIOUR_CLASS_IMPL(WallsManager);
