#pragma once
class Player;
class Claypipe;
//土管の出口のクラス

class Exit : public IGameObject
{
	bool Start();
	~Exit();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);

	//メンバ変数。
	ModelRender m_modelRender;	//モデルレンダ―。
	Vector3 m_position;			//座標。
	Player* m_player;//プレイヤー
	Claypipe* m_clayPipe;//土管
	PhysicsStaticObject physicsStaticObject;
};

