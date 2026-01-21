#include "stdafx.h"
#include "WarpManager.h"
#include "Player.h"

WarpManager::~WarpManager()
{

}


bool WarpManager::Start()
{
	m_player = FindGO<Player>("player");
	return true;
}