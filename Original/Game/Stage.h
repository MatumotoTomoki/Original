#pragma once

//ステージクラス
class Stage:public IGameObject
{
public:
	bool Start();
	~Stage();
	//描画関数
	void Render(RenderContext& rc);
	
	//モデルレンダ―。        
	ModelRender m_modelRender;
	PhysicsStaticObject physicsStaticObject;
	Vector3 m_position;

};

