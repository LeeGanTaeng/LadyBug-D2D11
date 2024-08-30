#include "Framework/Rendering.h"
#include "Framework/Time.h"

#include "Scene.h"

Scene::Scene()
{
    Skin = new Rendering::Component[2];

    //스킨을 2개로 하는 이유는 former와 latter 두개를 가지기 때문에 

    Skin[0].Content = "Background/Former";
    Skin[1].Content = "Background/Latter";

    Skin[0].Length = Skin[1].Length = { 600, 900 };

    Skin[0].Location = Skin[0].Length / 2;
    Skin[1].Location = Skin[0].Location - Vector<2>(0, Skin[0].Length[1] - 5);
}

void Scene::Update()
{
    if (900 + Skin[0].Length[1] / 2 <= Skin[0].Location[1])
    {
        Rendering::Component * const temp = &Skin[0];
        
        Skin[0] = Skin[1];
        Skin[1] = *temp;
        //swap 형식으로 former 이미지가 넘어가면 latter 이미지가 위에 붙어서 내려옴 
   
        
        Skin[1].Location = Skin[0].Location - Vector<2>(0, Skin[0].Length[1] - 5);
    }

    Vector<2> const distance = { 0, Speed * Time::GetDelta() };

    //delta time 동안 speed 25만큼 아래로 계속 이동 

    Skin[0].Location += distance; 
    Skin[1].Location += distance;
}

void Scene::Render()
{
    Skin[0].Render();
    Skin[1].Render();
}