#pragma once
class Player;
class Exit;
//土管クラス
class Claypipe : public IGameObject
{
public:
	bool Start();
	~Claypipe();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
	//自分の位置
	void SetPosition(const Vector3& pos);
	//行き先
	void SetWarpDestination(const Vector3& dest);

	//メンバ変数。
	ModelRender m_modelRender;	//モデルレンダ―。
	Vector3 m_position;			//座標。
	Vector3 m_warpDestination;//行き先
	Player* m_player;//プレイヤー
	Exit* m_exit;
	PhysicsStaticObject physicsStaticObject;
};

