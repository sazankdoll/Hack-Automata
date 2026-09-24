#include "SceneResult.h"

#include <DxLib.h>

#include "../../Manager/Generic/KeyConfInputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Application.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Generic/SceneManager.h"
#include "SceneTitle.h"
#include "../../Utility/UtilityMath.h"

SceneResult::SceneResult(bool _isGameOver)
	
{
}

void SceneResult::Load(void)
{
	
}

void SceneResult::EndLoad(void)
{
}

void SceneResult::Initialize(void)
{
	
}

void SceneResult::Update(void)
{
	auto& keyConfInputManager = KeyConfInputManager::GetInstance();

	if (keyConfInputManager.isTrigerDown("OK"))
	{
		SceneManager::GetInstance().ChangeScene(std::make_shared<SceneTitle>());
	}
}

void SceneResult::Draw(void)
{


	DrawString(Application::SCREEN_HALF_X+ (Application::SCREEN_HALF_X/2), Application::SCREEN_SIZE_Y - 20, "クリックしてタイトルへ", 0xffffff, true);
#ifdef _DEBUG

	DrawFormatString(0, 0, 0xFFFFFFF, "SceneResult");

#endif
}

void SceneResult::Release(void)
{
}

