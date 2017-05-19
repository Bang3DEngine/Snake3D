#include "MenuSpaceButton.h" 

int MenuSpaceButton::score = 0;

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
        SceneManager::LoadScene("Scenes/InGame2");
    }

    if (SceneManager::GetActiveScene()->GetName().Contains("Lose"))
    {
        UIText *scoreText = GameObject::Find("ScoreText")->GetComponent<UIText>();
        scoreText->SetContent( String::ToString(MenuSpaceButton::score) );
    }
} 

BANG_BEHAVIOUR_CLASS_IMPL(MenuSpaceButton);
