#include "MenuSpaceButton.h" 

// This function will be executed once when created 
void MenuSpaceButton::OnStart() 
{ 
    Behaviour::OnStart(); 
} 

// This function will be executed every frame 
void MenuSpaceButton::OnUpdate() 
{ 
    Behaviour::OnUpdate(); 

    if (Input::GetKeyDown(Input::Key::Space))
    {
        SceneManager::LoadScene("Scenes/InGame");
    }
} 

BANG_BEHAVIOUR_CLASS_IMPL(MenuSpaceButton);
