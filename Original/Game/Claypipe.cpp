#include "stdafx.h"
#include "Claypipe.h"
#include "Player.h"
#include "Exit.h"

bool Claypipe::Start()
{
	m_modelRender.Init("Assets/modelData/OriginalGoal.tkm");
	/*m_position.x = 3000.0f;
	m_position.y = 3000.0f;
	m_position.z = 3000.0f;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();*/
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_player = FindGO<Player>("player");
	return true;
}

Claypipe::~Claypipe()
{

}

void Claypipe::Update()
{
	Vector3 toPlayer = m_position - m_player->m_position;
	if (toPlayer.Length() <= 90.0f and g_pad[0]->IsTrigger(enButtonDown))
	{
		//プレイヤーを行き先にワープ
		m_player->SetPosition(m_warpDestination);
		
	}
}

void Claypipe::SetPosition(const Vector3& pos)
{
	m_position = pos;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Claypipe::SetWarpDestination(const Vector3& dest)
{
	m_warpDestination = dest;
}

void Claypipe::Render(RenderContext& rc)
{
	//モデルを描画する
	m_modelRender.Draw(rc);
}
