#pragma once
#include <DxLib.h>
#include "../Common/Quaternion.h"
#include "../Object/Actor/ActorBase.h"
#include "FollowCameraComponent.h"
#include "PointCameraComponent.h"

class Transform;

/// @brief シーン上でカメラアクターとして動作し、複数カメラコンポーネントを切り替えるクラス
class Camera : public ActorBase
{
public:

	/// @brief カメラの動作モード
	enum class MODE
	{
		POINT,	// 定点カメラモード
		FOLLOW	// 追従カメラモード
	};

	/// @brief コンストラクタ
	Camera(void);

	/// @brief デストラクタ
	~Camera(void) override = default;

	/// @brief 初期化処理
	void Init(void) override;

	/// @brief 更新処理
	void Update(void) override;

	/// @brief 描画前のカメラ設定
	void SetBeforeDraw(void);

	/// @brief カメラモードの切り替え
	/// @param _mode 設定するモード
	void ChangeMode(MODE _mode) { mode_ = _mode; }

	/// @brief 追従対象の設定
	/// @param _follow 追従対象のTransformポインタ
	void SetFollow(const Transform* _follow);

	/// @brief 定点カメラの位置・注視点を設定
	/// @param _pos カメラ位置
	/// @param _targetPos 注視点位置
	void SetPointCameraParam(const VECTOR& _pos, const VECTOR& _targetPos);

	/// @brief カメラ位置の取得
	/// @return 現在の座標
	const VECTOR& GetPos(void) const { return transform_.pos; }

	/// @brief 注視点の取得
	/// @return 現在の注視点
	VECTOR GetTargetPos(void) const;

	/// @brief カメラの前方ベクトルを取得
	/// @return 前方方向の単位ベクトル
	VECTOR GetForward(void) const;

	/// @brief 衝突解消処理（SceneManagerとの互換性維持のため）
	void ResolveCollision(void) {}

private:

	MODE mode_;									// 現在アクティブなカメラモード
	PointCameraComponent* pointCameraComp_;	// 定点カメラコンポーネント
	FollowCameraComponent* followCameraComp_;	// 追従カメラコンポーネント
};