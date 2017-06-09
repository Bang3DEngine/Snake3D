#include "TreeMove.h" 

// This function will be executed once when created 
void TreeMove::OnStart() 
{ 
    Behaviour::OnStart(); 
} 

// This function will be executed every frame 
void TreeMove::OnUpdate() 
{ 
    Behaviour::OnUpdate(); 

    for (Renderer *renderer :
         gameObject->GetComponentsInThisAndChildren<Renderer>())
    {
        renderer->UseMaterialCopy();
        renderer->GetMaterial()->SetDiffuseColor(treeColor);
    }
    transform->Translate( Vector3::Up * speed );
} 

BANG_BEHAVIOUR_CLASS_IMPL(TreeMove);
