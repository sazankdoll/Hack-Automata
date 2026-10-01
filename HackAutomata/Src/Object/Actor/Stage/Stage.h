#pragma once
#include "../ActorBase.h"

/// @brief ステージアクタークラス
class Stage : public ActorBase
{
public:

	/// @brief コンストラクタ
	Stage(void);

	/// @brief デストラクタ
	~Stage(void) override = default;

	/// @brief リソースの読み込み
	void Load(void) override;

	/// @brief 初期化処理
	void Init(void) override;

	/// @brief 更新処理
	void Update(void) override;

	/// @brief 描画処理
	void Draw(void) override;

private:

	static constexpr float STAGE_SCALE = 10.0f;	// ステージの拡大率
};