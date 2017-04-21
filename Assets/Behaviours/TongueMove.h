#ifndef TongueMove_H 
#define TongueMove_H 

#include "Bang/Behaviour.h" 

// Here go your includes 

class TongueMove : public Behaviour 
{ 
OBJECT(TongueMove) 
public: 
    void OnStart() override; 
    void OnUpdate() override; 

    float m_time = 0.0f;
    Vector3 m_originalPos;
}; 

#endif // TongueMove_H 

BANG_BEHAVIOUR_CLASS(TongueMove);
