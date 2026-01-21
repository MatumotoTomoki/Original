#include "stdafx.h"
#include "Goal.h"
#include "Player.h"
#include "Claypipe.h"

bool Goal::Start()
{
	m_modelRender.Init("Assets/modelData/OriginalGoal.tkm");
	m_position.x = -20.3f;
	m_position.y = 606.4f;
	m_position.z = 9673.3f;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_player = FindGO<Player>("player");
	return true;
}

Goal::~Goal()
{
	

}

void Goal::Update()
{
	Vector3 toPlayer = m_position - m_player->m_position;
	if (toPlayer.Length() <= 90.0f)
	{
		m_player->m_warp = true;
		m_appearance = true;
		//DeleteGO(this);
	}

	/*if (m_appearance == true)
	{
		m_appearance = false;
	}*/
}

void::Goal::Render(RenderContext& rc)
{
	//モデルを描画する
	m_modelRender.Draw(rc);
}