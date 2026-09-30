#pragma once
#include "Component.h"
#include "../../../Manager/Generic/ResourceManager.h"


class MeshComponent : public Component
{
public:

	/// @brief コンストラクタ
	/// @param _owner 所有者となるアクターのポインタ
	MeshComponent(ActorBase* _owner);

	/// @brief デストラクタ
	~MeshComponent(void) override = default;

	/// @brief 3Dモデルリソースの読み込み
	/// @param _src リソース識別子
	void LoadModel(ResourceManager::SRC _src);

	/// @brief 初期化処理
	void Init(void) override;

	/// @brief 更新処理（アクターの位置や回転をモデルに適用）
	void Update(void) override;

	/// @brief 描画処理
	void Draw(void) override;

	/// @brief 解放処理
	void Release(void) override;

	/// @brief 描画するかどうかのフラグ設定
	/// @param _isVisible 描画する場合はtrue
	void SetIsVisible(bool _isVisible) { isVisible_ = _isVisible; }

	/// @brief 描画するかどうかのフラグ取得
	/// @return 描画する場合はtrue
	bool GetIsVisible(void) const { return isVisible_; }

	/// @brief モデルハンドルの取得
	/// @return DXライブラリのモデルハンドル
	int GetModelId(void) const { return modelId_; }

private:

	int modelId_;		// DXライブラリのモデルハンドル
	bool isVisible_;	// 描画フラグ（表示・非表示）
};