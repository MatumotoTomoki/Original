#pragma once
//ステージ2クラス
class Stage2 :public IGameObject
{
	bool Start();
	~Stage2();
	//描画関数
	void Render(RenderContext& rc);

	//モデルレンダ―。        
	ModelRender m_modelRender;
	PhysicsStaticObject physicsStaticObject;
	Vector3 m_position;
};

