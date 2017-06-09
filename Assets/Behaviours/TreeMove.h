#ifndef TreeMove_H 
#define TreeMove_H 

#include "Bang/Behaviour.h" 
#include ".TreeMove.refl.h" 

// Here go your includes 

BP_REFLECT_CLASS(TreeMove)
class TreeMove : public Behaviour 
{ 
OBJECT(TreeMove) 
public: 

    BP_REFLECT_VARIABLE(Speed)
    float speed = 0.1f; 

    BP_REFLECT_VARIABLE(MyTreeColor)
    Color treeColor = Color::Red;

    void OnStart() override; 
    void OnUpdate() override; 


    BP_REFLECT_DEFINITIONS(TreeMove)
}; 

#endif // TreeMove_H 

BANG_BEHAVIOUR_CLASS(TreeMove);
