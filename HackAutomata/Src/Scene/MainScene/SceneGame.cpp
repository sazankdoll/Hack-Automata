#define NOMINMAX
#include "SceneGame.h"
#include "../../Manager/Generic/KeyConfInputManager.h"
#include "../../Manager/Generic/SceneManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/System/TimeManager.h"
#include "../../Common/Loading.h"
#include "../../Camera/Camera.h"
#include "../../Utility/UtilityMath.h"
#include "../../Application.h"
#include "SceneTitle.h"
#include "SceneResult.h"

SceneGame::SceneGame()
{
	
}

void SceneGame::Load(void)
{
	SceneBase::Load();

	//時間カウントリセット
	TimeManager::GetInstance().Reset();

}

void SceneGame::EndLoad(void)
{
	SceneBase::EndLoad();
}

void SceneGame::Initialize(void)
{

	if (Loading::GetInstance()->IsLoading()) { return; }

	// マウスを表示しない設定にする
	SetMouseDispFlag(false);
	
}

void SceneGame::Update(void)
{

	auto& keyConfInputManager = KeyConfInputManager::GetInstance();
	if (keyConfInputManager.isTrigerDown("OK"))
	{
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneResult>());
	}
}

void SceneGame::Draw(void)
{
#ifdef _DEBUG

	DrawFormatString(0, 0, 0xFFFFFF, "SceneGame");

#endif
}

void SceneGame::Release(void)
{
	
}

