#pragma once


//前方宣言
class Player;

//ワープマネージャークラス
class WarpManager :public IGameObject
{
	WarpManager();
	~WarpManager();


public:
	bool Start() override;


private:
	Player* m_player = nullptr;

};

