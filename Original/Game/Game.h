#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class Stage;
class Goal;
class Stage2;
class Claypipe;
class Exit;

//Gameシーンを管理するクラス
class Game : public IGameObject
{
public:
	
	bool Start();
	//更新処理。
	void Update();
	//描画関数
	void Render(RenderContext& rc);
	Player* m_player; //プレイヤー
	GameCamera* m_gameCamera; //ゲームカメラ
	Stage* m_stage; //ステージ
	Goal* m_goal;//ゴール
	Stage2* m_stage2;//ステージ2
	Claypipe* m_clayPipe;//土管
	Exit* m_exit;//出口
	FontRender m_fontRender;


};

