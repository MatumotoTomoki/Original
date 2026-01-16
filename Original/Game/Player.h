#pragma once
class Goal;
//プレイヤークラス
class Player : public IGameObject
{
public:
	bool Start();
	~Player();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
	//移動処理。
	void Move();
	//回転処理。
	void Rotation();
	//ステート管理。
	void ManageState();
	//アニメーションの再生。
	void PlayAnimation();
	//ダッシュ
	void Dash(float& dash); 
	//ステージ移動
	void Warp();

	//メンバ変数。
	ModelRender m_modelRender;	//モデルレンダ―。
	Vector3 m_position;			//座標。
	Goal* m_goal;
	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];		//アニメーションクリップ。
	CharacterController m_characterController;  //キャラクターコントローラー。
	Vector3 m_moveSpeed;		//移動速度。
	Quaternion m_rotation;  //クォータニオン。
	Vector3 GetPosition() const { return m_position; }
	int playerState = 0;//プレイヤーのステート（状態）を表す変数。
	int m_jumpCount = 0;//ジャンプカウント
	int m_maxJumpCount = 2;//マックスジャンプ回数
	float m_spinAngle = 0.0f;  // 現在の回転角度
	float m_spinTime = 0.0f;   // 回転用タイマー
	bool m_spin = false;       // 回転中フラグ
	bool m_warp = false;//ステージ移動フラグ
	bool m_clayPipeWarp = false;//土管移動フラグ
	bool m_exitWarp = false;//出口土管フラグ
};

