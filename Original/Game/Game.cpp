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

	if (m_goal->m_appearance == true)
	{
		//土管を作る
		Claypipe* pipeA = NewGO<Claypipe>(0, "clayPipeA");
		pipeA->SetPosition({ 3000.0f,3000.0f,3000.0f });
		pipeA->SetWarpDestination({ 4354.5f,3100.0f,-24958.8f });
		Claypipe* pipeB = NewGO<Claypipe>(0,"clayPieB");
		pipeB->SetPosition({ 4354.5f,3000.0f,-24958.8f });
		pipeB->SetWarpDestination({ 3000.0f,3100.0f,3000.0f });
		Claypipe* pipeC = NewGO<Claypipe>(0, "clayPipeC");
		pipeC->SetPosition({ 6507.4f,3000.0f,-24894.8f });
		pipeC->SetWarpDestination({ -1152.3,3388.7,8036.1 });
		Claypipe* pipeD = NewGO<Claypipe>(0, "clayPipeD");
		pipeD->SetPosition({ -1152.3,3288.7,8036.1 });
		pipeD->SetWarpDestination({ 6507.4f,3100.0f,-24894.8f });
		Claypipe* pipeE = NewGO<Claypipe>(0, "clayPipeE");
		pipeE->SetPosition({ 2539.5f,3000.0f,-24909.0f });
		pipeE->SetWarpDestination({ -11783.3f,3100.0f,617.4 });
		Claypipe* pipeF = NewGO<Claypipe>(0, "clayPipeF");
		pipeF->SetPosition({ -11783.3f,3000.0f,617.4 });
		pipeF->SetWarpDestination({ 2539.5f,3100.0f,-24909.0f });
		Claypipe* pipeG = NewGO<Claypipe>(0, "clayPipeG");
		pipeG->SetPosition({ -342.6f,3288.7f,8049.3f });
		pipeG->SetWarpDestination({ 0.0f,-5000.0f,0.0f });
		Claypipe* pipeH = NewGO<Claypipe>(0, "clayPipeH");
		pipeH->SetPosition({ -1950.6f,3288.7f,8013.1f });
		pipeH->SetWarpDestination({ 3000.0f,3100.0f,3000.0f });
		Claypipe* pipeI = NewGO<Claypipe>(0, "clayPipeI");
		pipeI->SetPosition({ -10956.3f,3000.0f,587.0f });
		pipeI->SetWarpDestination({ 3785.2f,3152.1f,-4291.4f });
		Claypipe* pipeJ = NewGO<Claypipe>(0, "clayPipeJ");
		pipeJ->SetPosition({ 3785.2f,3052.1f,-4291.4f });
		pipeJ->SetWarpDestination({ 28383.6f,3502.6f,943.0f });
		//土管の出口を作る
		//m_exit = NewGO<Exit>(0, "exit");
		m_goal->m_appearance = false;
		DeleteGO(m_goal);
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