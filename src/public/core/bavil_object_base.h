#pragma once

#include <concepts>

namespace bavil
{

  class ObjectBase
  {
   public:
	virtual ~ObjectBase() {}

	/**
	 * @brief オブジェクトの構築時に呼ばれる
	 */
	virtual void construct() = 0;
	/**
	 * @brief オブジェクトの削除時に呼ばれる
	 */
	virtual void destruct() = 0;

  };


  template <class T>
  concept ObjectConcepts = requires(T obj)
  {
	std::derived_from<T, ObjectBase>;
  };

}  // namespace bavil
