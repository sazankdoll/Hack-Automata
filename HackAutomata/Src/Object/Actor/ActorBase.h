#pragma once
#include "../Common/Transform.h"
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>

class Component;
class TimeManager;

/// @brief コンポーネント指向におけるゲームオブジェクト基底クラス
class ActorBase
{
public:

	/// @brief コンストラクタ
	ActorBase(void);

	/// @brief デストラクタ
	virtual ~ActorBase(void);

	/// @brief リソースの読み込み
	virtual void Load(void);

	/// @brief 初期化処理
	virtual void Init(void);

	/// @brief 更新処理
	virtual void Update(void);

	/// @brief 描画処理
	virtual void Draw(void);

	/// @brief 解放処理
	virtual void Release(void);

	/// @brief コンポーネントの追加
	/// @tparam T 追加するコンポーネントの型
	/// @return 生成されたコンポーネントのポインタ
	template <typename T, typename... Args>
	T* AddComponent(Args&&... _args)
	{
		T* newComponent = new T(this, std::forward<Args>(_args)...);
		components_.push_back(newComponent);
		return newComponent;
	}

	/// @brief 特定のコンポーネントを取得する
	/// @tparam T 取得したいコンポーネントの型
	/// @return 該当するコンポーネントのポインタ（無ければnullptr）
	template <typename T>
	T* GetComponent(void) const
	{
		for (auto* component : components_)
		{
			T* casted = dynamic_cast<T*>(component);
			if (casted != nullptr)
			{
				return casted;
			}
		}
		return nullptr;
	}

	/// @brief Transform情報の取得(const)
	/// @return Transform情報
	const Transform& GetTransform(void) const { return transform_; }

	/// @brief Transform情報の取得
	/// @return Transform情報
	Transform& GetTransform(void) { return transform_; }

	/// @brief 生存状態の取得
	/// @return 生存していればtrue
	bool GetIsActive(void) const { return isActive_; }

	/// @brief 生存状態の設定
	/// @param _isActive 生存状態
	void SetIsActive(bool _isActive) { isActive_ = _isActive; }

protected:

	TimeManager& timeManager_;		// タイムマネージャーの参照
	Transform transform_;			// 位置・回転・スケール情報
	std::vector<Component*> components_;	// 所有するコンポーネント配列
	bool isActive_;					// アクターの有効フラグ
};