#include "SceneTitle.h"
#include "../../Manager/Generic/SceneManager.h"
#include "../../Manager/Generic/KeyConfInputManager.h"
#include "SceneGame.h"
#include "../../Application.h"
#include "../../Manager/System/TimeManager.h"
#include "../../Common/Loading.h"
#include "../../Utility/UtilityMath.h"


SceneTitle::SceneTitle(void)
   
{
    
}

void SceneTitle::Load(void)
{
  
    //時間カウントリセット
    TimeManager::GetInstance().Reset();

}

void SceneTitle::EndLoad(void)
{
    SceneBase::EndLoad();
}

void SceneTitle::Initialize(void)
{

    if (Loading::GetInstance()->IsLoading()) { return; }

    SetMouseDispFlag(true);

}


void SceneTitle::Update(void)
{
    if (Loading::GetInstance()->IsLoading()) { return; }

    auto& keyConfInputManager = KeyConfInputManager::GetInstance();

    if (keyConfInputManager.isTrigerDown("OK"))
    {
        SceneManager::GetInstance().ChangeScene(std::make_shared<SceneGame>());
    }

#ifdef _DEBUG

#endif

 

}

void SceneTitle::Draw(void)
{

#ifdef _DEBUG

	DrawFormatString(0, 0, 0xFFFFFF, "SceneTitle");

#endif
}

void SceneTitle::Release(void)
{
}


