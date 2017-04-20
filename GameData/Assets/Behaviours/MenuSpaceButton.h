#ifndef MenuSpaceButton_H 
#define MenuSpaceButton_H 

#include "Bang/Behaviour.h" 

// Here go your includes 

class MenuSpaceButton : public Behaviour 
{ 
OBJECT(MenuSpaceButton) 
public: 
    void OnStart() override; 
    void OnUpdate() override; 
}; 

#endif // MenuSpaceButton_H 

BANG_BEHAVIOUR_CLASS(MenuSpaceButton);