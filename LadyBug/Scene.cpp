#include "Framework/Rendering.h"
#include "Framework/Time.h"

#include "Scene.h"

Scene::Scene()
{
    Skin = new Rendering::Component[2];

    //��Ų�� 2���� �ϴ� ������ former�� latter �ΰ��� ������ ������ 

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
        //swap �������� former �̹����� �Ѿ�� latter �̹����� ���� �پ ������ 
   
        
        Skin[1].Location = Skin[0].Location - Vector<2>(0, Skin[0].Length[1] - 5);
    }

    Vector<2> const distance = { 0, Speed * Time::GetDelta() };

    //delta time ���� speed 25��ŭ �Ʒ��� ��� �̵� 

    Skin[0].Location += distance; 
    Skin[1].Location += distance;
}

void Scene::Render()
{
    Skin[0].Render();
    Skin[1].Render();
}