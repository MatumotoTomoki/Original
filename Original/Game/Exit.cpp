#include "stdafx.h"
#include "Exit.h"
#include "Player.h"
#include "Claypipe.h"

bool Exit::Start()
{
	m_modelRender.Init("Assets/modelData/OriginalGoal.tkm");
	m_position.x = 3002.6f;
	m_position.y = 3000.0f;
	m_position.z = 279.1f;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_player = FindGO<Player>("player");
	return true;
}

Exit::~Exit()
{

}

void Exit::Update()
{
	Vector3 toPlayer = m_position - m_player->m_position;
	if (toPlayer.Length() <= 90.0f and g_pad[0]->IsTrigger(enButtonDown))
	{
		m_player->m_exitWarp = true;
	}
}

void Exit::Render(RenderContext& rc)
{
	//モデルを描画する
	m_modelRender.Draw(rc);
}