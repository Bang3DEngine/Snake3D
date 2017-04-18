#ifndef WallsManager_H 
#define WallsManager_H 

#include "Bang/Behaviour.h" 

// Here go your includes 

class WallsManager : public Behaviour 
{ 
OBJECT(WallsManager) 
public: 
    void OnStart() override; 
    void OnUpdate() override;

    static bool CollidesWithWall(GameObject *go);

private:
    static List<GameObject*> s_walls;
}; 

#endif // WallsManager_H 

BANG_BEHAVIOUR_CLASS(WallsManager);
