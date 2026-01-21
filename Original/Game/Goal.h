//ゴールクラス
#pragma once
class Player;
class Stage;
class Claypipe;
class Goal : public IGameObject
{
public:
	bool Start();
	~Goal();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);

	//メンバ変数。
	ModelRender m_modelRender;	//モデルレンダ―。
	Vector3 m_position;			//座標。
	Player* m_player;//プレイヤー
	Stage* m_stage;//ステージ
	Claypipe* m_clayPipe;//土管
	PhysicsStaticObject physicsStaticObject;
	bool m_appearance = false;
};

