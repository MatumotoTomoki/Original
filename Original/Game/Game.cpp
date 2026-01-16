#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "Stage.h"
#include "Goal.h"
#include "Stage2.h"
#include "Claypipe.h"
#include "Exit.h"

bool Game::Start()
{
	//プレイヤーを作る
	m_player = NewGO<Player>(0, "player");

	//ゲームカメラを作る
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//ステージを作る
	m_stage = NewGO<Stage>(0, "stage");

	//土管を作る
	m_clayPipe = NewGO<Claypipe>(0, "clayPipe");

	//土管の出口を作る
	m_exit = NewGO<Exit>(0, "exit");

	//ゴールを作る
	m_goal = NewGO<Goal>(0, "goal");
	
	return true;
}

void Game::Update()
{
	if (m_player->m_warp == true)
	{
		m_stage2 = NewGO<Stage2>(0, "stage2");
		DeleteGO(m_stage);
	}
}

void Game::Render(RenderContext& rc)
{
		//プレイヤーの座標を表示する。
	    //表示する座標を設定する。
		m_fontRender.SetPosition({ -600.0f,100.0f,0.0f });
		//表示する色を設定する。
		m_fontRender.SetColor(g_vec4White);
		//プレイヤーの座標を取得
		Vector3 pos = m_player->GetPosition();
		//座標を文字列に変換
		wchar_t buf[128];
		swprintf(buf, 128, L"Player Pos: X=%.1f Y=%.1f Z=%.1f", pos.x, pos.y, pos.z);
		//テキストをセット
		m_fontRender.SetText(buf);
		//フォントを描画
		m_fontRender.Draw(rc);
}