#pragma once
#include <DxLib.h>
#include "../Object/Actor/Component/Component.h"
#include "../Common/Quaternion.h"

class Transform;

/// @brief 三人称追従カメラ機能を提供するコンポーネント
class FollowCameraComponent : public Component
{
public:

	/// @brief コンストラクタ
	/// @param _owner 所有者となるアクターのポインタ
	FollowCameraComponent(ActorBase* _owner);

	/// @brief デストラクta
	~FollowCameraComponent(void) override = default;

	/// @brief 初期化処理
	void Init(void) override;

	/// @brief 更新処理
	void Update(void) override;

	/// @brief 描画前処理（DXライブラリのカメラ位置を決定）
	void SetBeforeDraw(void);

	/// @brief 追従対象の設定
	/// @param _follow 追従対象のTransformポインタ
	void SetFollow(const Transform* _follow) { followTransform_ = _follow; }

	/// @brief 注視点の取得
	/// @return 現在の注視点座標
	const VECTOR& GetTargetPos(void) const { return targetPos_; }

	/// @brief カメラ角度の取得
	/// @return 現在の回転角度（ラジアン）
	const VECTOR& GetAngles(void) const { return angles_; }

	/// @brief Y軸回転のクォータニオン取得
	/// @return Y軸回転クォータニオン
	const Quaternion& GetQuaRotY(void) const { return rotY_; }

private:

	/// @brief 入力によるカメラの回転処理
	void ProcessRot(void);

	/// @brief 追従対象との位置・角度同期処理
	void SyncFollow(void);

private:

	// クリップ範囲設定
	static constexpr float VIEW_NEAR = 10.0f;			// 近クリップ面距離
	static constexpr float VIEW_FAR = 20000.0f;			// 遠クリップ面距離

	// カメラの追従オフセット値
	static constexpr VECTOR FOLLOW_LOCAL_POS = { 0.0f, 50.0f, -200.0f };		// カメラ位置の相対座標
	static constexpr VECTOR FOLLOW_TARGET_LOCAL_POS = { 0.0f, 30.0f, 0.0f };	// 注視点の相対座標

	// 回転感度と角度制限
	static constexpr float ROT_POW_MOUSE = 0.005f;		// マウス回転倍率
	static constexpr float ROT_POW_RAD = 0.03f;			// ゲームパッド回転倍率
	static constexpr float LIMIT_X_UP = 40.0f * (DX_PI_F / 180.0f);		// 上方向回転上限
	static constexpr float LIMIT_X_DOWN = 35.0f * (DX_PI_F / 180.0f);	// 下方向回転上限

	const Transform* followTransform_;	// 追従対象のTransformポインタ
	VECTOR targetPos_;					// 注視点座標
	VECTOR angles_;						// カメラ回転角 (x: ピッチ, y: ヨー, z: ロール)
	Quaternion rotY_;					// Y軸回転クォータニオン
};