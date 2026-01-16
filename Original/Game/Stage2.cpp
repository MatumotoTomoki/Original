#include "stdafx.h"
#include "Stage2.h"
bool Stage2::Start()
{
	//当たり判定
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_modelRender.Init("Assets/modelData/OriginalStage2.tkm");
	m_position.x = 3000.0f;
	m_position.y = 3000.0f;
	m_position.z = 3000.0f;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	return true;
}

Stage2::~Stage2()
{

}

void Stage2::Render(RenderContext& rc)
{
	//モデルを描画する
	m_modelRender.Draw(rc);
}