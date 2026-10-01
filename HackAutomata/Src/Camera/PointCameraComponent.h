#pragma once
#include <DxLib.h>
#include "../Object/Actor/Component/Component.h"
#include "../Utility/UtilityMath.h"

// 前方宣言（ActorBaseクラスが存在することを伝える）
class ActorBase;

/// @brief 指定した座標から注視点を見つめる定点カメラコンポーネント
class PointCameraComponent : public Component
{
public:

	/// @brief コンストラクタ
	/// @param _owner 所有者となるアクターのポインタ
	PointCameraComponent(ActorBase* _owner);

	/// @brief デストラクタ
	~PointCameraComponent(void) override = default;

	/// @brief 初期化処理
	void Init(void) override;

	/// @brief 更新処理
	void Update(void) override;

	/// @brief 描画前処理（DXライブラリへカメラパラメータを設定）
	void SetBeforeDraw(void);

	/// @brief カメラの固定位置を設定
	/// @param _pos 設定する座標
	void SetPosition(const VECTOR& _pos) { pointPos_ = _pos; }

	/// @brief カメラの注視点を設定
	/// @param _targetPos 設定する注視点座標
	void SetTargetPos(const VECTOR& _targetPos) { targetPos_ = _targetPos; }

	/// @brief 注視点の取得
	/// @return 現在の注視点座標
	const VECTOR& GetTargetPos(void) const { return targetPos_; }

private:

	// クリップ範囲設定
	static constexpr float VIEW_NEAR = 10.0f;		// 近クリップ面距離
	static constexpr float VIEW_FAR = 20000.0f;		// 遠クリップ面距離

	VECTOR pointPos_;	// カメラの固定位置
	VECTOR targetPos_;	// カメラの注視点
};