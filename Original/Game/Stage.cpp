#include "stdafx.h"
#include "Stage.h"

bool Stage::Start()
{
	//当たり判定
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_modelRender.Init("Assets/modelData/OriginalStage1.tkm");
	m_modelRender.Update();
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	return true;
}

Stage::~Stage()
{

}

void Stage::Render(RenderContext& rc)
{
	//モデルを描画する
	m_modelRender.Draw(rc);
}