#pragma once

class ActorBase;

/// @brief コンポーネントの基底クラス
class Component
{
public:

	/// @brief コンストラクタ
	/// @param _owner 所有者となるアクターのポインタ
	Component(ActorBase* _owner);

	/// @brief デストラクタ
	virtual ~Component(void) = default;

	/// @brief 初期化処理
	virtual void Init(void) {}

	/// @brief 更新処理
	virtual void Update(void) {}

	/// @brief 描画処理
	virtual void Draw(void) {}

	/// @brief 解放処理
	virtual void Release(void) {}

	/// @brief 有効・無効フラグの設定
	/// @param _enable 有効にするかどうかのフラグ
	void SetEnable(bool _enable) { isEnable_ = _enable; }

	/// @brief 有効状態の取得
	/// @return 有効ならtrue
	bool GetEnable(void) const { return isEnable_; }

protected:

	ActorBase* owner_;	// 所有者のアクターポインタ
	bool isEnable_;		// コンポーネントの有効フラグ
};