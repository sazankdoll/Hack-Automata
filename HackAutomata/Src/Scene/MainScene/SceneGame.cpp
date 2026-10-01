#define NOMINMAX

#include "../../Manager/Generic/KeyConfInputManager.h"
#include "../../Manager/Generic/SceneManager.h"
#include "../../Manager/System/TimeManager.h"
#include "../../Common/Loading.h"
#include "../../Camera/Camera.h"
#include "../../Utility/UtilityMath.h"
#include "../../Application.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "SceneGame.h"

SceneGame::SceneGame()
	: stage_(std::make_unique<Stage>())
	, isDebugMode_(false)
	, SceneBase()

{
	
}

void SceneGame::Load(void)
{
	SceneBase::Load();

	
	//時間カウントリセット
	TimeManager::GetInstance().Reset();
	stage_->Load();

}

void SceneGame::EndLoad(void)
{
	SceneBase::EndLoad();
}

void SceneGame::Initialize(void)
{

	if (Loading::GetInstance()->IsLoading()) { return; }

	auto& camera = SceneManager::GetInstance().GetCamera();
	


	// マウスを表示しない設定にする
	SetMouseDispFlag(false);

	stage_->Init();
	
	
}

void SceneGame::Update(void)
{

	stage_->Update();

	auto& keyConfInputManager = KeyConfInputManager::GetInstance();
	if (keyConfInputManager.isTrigerDown("OK"))
	{
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneResult>());
	}
}

void SceneGame::Draw(void)
{
	stage_->Draw();

#ifdef _DEBUG

	DrawFormatString(0, 0, 0xFFFFFF, "SceneGame");
	auto& camera = SceneManager::GetInstance().GetCamera();
	DrawFormatString(0, 20, 0xFFFFFF, "CameraPos: (%.2f, %.2f, %.2f)", camera->GetPos().x, camera->GetPos().y, camera->GetPos().z);

#endif
}

void SceneGame::Release(void)
{
	
}

