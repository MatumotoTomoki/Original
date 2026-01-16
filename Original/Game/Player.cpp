#include "stdafx.h"
#include "Player.h"
#include "Goal.h"
bool Player::Start()
{
	//アニメーションクリップをロードする。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	//ユニティちゃんのモデルを読み込む。
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);
	m_goal= FindGO<Goal>("goal");
	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, m_position);
	return true;
}

Player::~Player()
{

}

void Player::Update()
{
	//移動処理。
	Move();

	//回転処理。
	Rotation();

	//ステート管理。
	ManageState();

	//アニメーションの再生。
	PlayAnimation();

	//ステージ移動
	Warp();

	//空中回転
	if (m_spin)
	{
		// 回転時間を進める
		m_spinTime += 1.0f / 60.0f;

		// 0.25秒で360度回転させる
		float t = m_spinTime / 0.25f;

		if (t >= 1.0f)
		{
			// 回転終了
			t = 1.0f;
			m_spin = false;
		}

		// 現在の回転角度
		m_spinAngle = 360.0f * t;

		// 回転をセット
		Quaternion q;
		q.SetRotationY(Math::DegToRad(m_spinAngle));
		m_modelRender.SetRotation(q);
	}

	//絵描きさんの更新処理。
	m_modelRender.Update();
}

void Player::Move()
{
	//xzの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;

	////ダッシュ
	float moveSpeedMultiplier = 360.0f;  // 通常移動速度
	Dash(moveSpeedMultiplier);
	//左スティックの入力量と120.0fを乗算。
	right *= stickL.x * moveSpeedMultiplier;
	forward *= stickL.y * moveSpeedMultiplier;

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;

	// 地面に付いていたら。
	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;         // 重力をリセット
		m_jumpCount = 0;              // ジャンプ回数リセット
	}

	// Aボタンが押されたら。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_jumpCount < m_maxJumpCount)
		{
			m_moveSpeed.y = 360.0f;   // ジャンプさせる
			m_jumpCount++;            // ジャンプ回数加算
		}

		if (m_jumpCount == 2)
		{
			m_spin = true;
			m_spinAngle = 0.0f;
			m_spinTime = 0.0f;
		}
	}

	// 地面に付いていなかったら。
	if (!m_characterController.IsOnGround())
	{
		m_moveSpeed.y -= 3.0f;        // 重力を加える
	}

	//キャラクターコントローラーを使って座標を移動させる。
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);
}

void Player::Dash(float& dash)
{
	if (g_pad[0]->IsPress(enButtonX)) {
		dash = 720.0f;    // Xボタンでダッシュ速度
	}
}

void Player::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える。
		m_modelRender.SetRotation(m_rotation);
	}

	if (m_spinAngle > 0.0f)
	{
		float rotateSpeed = 720.0f * g_gameTime->GetFrameDeltaTime(); // 速さ調整

		float rot = min(rotateSpeed, m_spinAngle);
		m_spinAngle -= rot;

		// Y軸回転
		Quaternion addRot;
		addRot.SetRotationDegY(rot);
		m_rotation = addRot * m_rotation;
	}
}

void Player::ManageState()
{
	//地面に付いていなかったら。
	if (m_characterController.IsOnGround() == false)
	{
		//ステートを1(ジャンプ中)にする。
		playerState = 1;
		//ここでManageStateの処理を終わらせる。
		return;
	}

	//地面に付いていたら。
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		if (g_pad[0]->IsPress(enButtonX)) {
			playerState = 3;    // Xボタンでダッシュ中
		}
		else
		{
			playerState = 2;
		}
	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//ステートを0(待機)にする。
		playerState = 0;
	}
}

void Player::PlayAnimation()
{
	//switch文。
	switch (playerState) {
		//プレイヤーステートが0(待機)だったら。
	case 0:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//プレイヤーステートが1(ジャンプ中)だったら。
	case 1:
		//ジャンプアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
		//プレイヤーステートが2(歩き)だったら。
	case 2:
		//歩きアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3://ダッシュアニメーションを再生する
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

void Player::Warp()
{
	
	if (m_warp == true)
	{
		
		m_position.x = 3000.0f;
		m_position.y = 3000.0f;
		m_position.z = 3000.0f;
		/*m_position.x = -3000.0f;
		m_position.y = 606.4f;
		m_position.z = 9673.3f;*/
		m_characterController.SetPosition(m_position);
		m_modelRender.SetPosition(m_position);
		m_modelRender.Update();
		m_warp = false;
	}

	if (m_clayPipeWarp == true)
	{
		m_position.x = 3002.6f;
		m_position.y = 3000.0f;
		m_position.z = 279.1f;
		m_characterController.SetPosition(m_position);
		m_modelRender.SetPosition(m_position);
		m_modelRender.Update();
		m_clayPipeWarp = false;
	}

	if (m_exitWarp == true)
	{
		m_position.x = 3000.0f;
		m_position.y = 3000.0f;
		m_position.z = 3000.0f;
		m_characterController.SetPosition(m_position);
		m_modelRender.SetPosition(m_position);
		m_modelRender.Update();
		m_exitWarp = false;
	}
	
}

void Player::Render(RenderContext& rc)
{
	//ユニティちゃんを描画する。
	m_modelRender.Draw(rc);
}