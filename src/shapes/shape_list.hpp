#ifndef GEARX_SHAPE_SHAPE_LIST_HPP
#define GEARX_SHAPE_SHAPE_LIST_HPP
/* chat gpt 命名のgearx という名前
 * ギアの発展形である部品の製作と共に、未来感を感じさせる。 
　*/
#include <variant>
#include <type_traits>
#include <cstddef>
#include <iostream>
#include <utility>

#include "2d/shape2D.hpp"
#include "3d/shape3D.hpp"

namespace gearx {
	using namespace gearx::shape_3d;

	template <typename ...ShapeTypes>
	class ShapeList {
		static_assert(
			(std::conjunction_v<
				std::disjunction<
					std::is_base_of<PrismBase, ShapeTypes>,
					//std::is_base_of<Shape2D, ShapeTypes>
				>...>
			),
			"All template arguments must derive from PrismBase or Shape2D class."
		);

			using ShapeTypeVariant = std::variant<ShapeTypes...>;
			std::vector<ShapeTypeVariant> _shapes;
		public:

			ShapeList () = default;
			~ShapeList() = default;

			// コピーコンストラクタ
			ShapeList(const ShapeList& other)
				: _shapes(other._shapes) {}
			// コピー代入演算子
			ShapeList& operator=(const ShapeList& other) {
				if (this != &other) {
					_shapes = other._shapes;
				}
				return *this;
			}

			// 全要素を描画（std::visit を意識しなくて書く必要がない）
			void renderAll() const {
				for (const auto& shape : _shapes) {
					std::visit([](const auto& shp) {
						// shape.translate();
						shp.render();
					}, shape);
				}
			}

			// イテレータを使って、処理したい場合のヘルパー関数
			template<typename Func>
			void forEach(Func f) {
				for (auto& shape : _shapes) {
					std::visit([&](auto& shp) {
						f(shp);
					}, shape);
				}
			}

			// 読み取り専用　範囲チェックなし
			const ShapeTypeVariant& operator[](size_t i) const {
				return _shapes[i];
			}
			// 読み取り専用　範囲チェックあり
			const ShapeTypeVariant& at(size_t i) const {
					return _shapes.at(i);
			}

			// 要素を1つ追加する
			template< typename T, typename = std::enable_if_t< (std::disjunction_v<std::is_same<T, ShapeTypes>...>) > >
					// ↑ この関数のTの型は、
					// このクラスのテンプレート(BoolObject<...ShapeTypes>)で指定した型のうちのどれかでないといけない。
			void add(T&& object) {
				_shapes.emplace_back(std::forward<T>(object));	
			}

			// グループを追加する
			void addList(const ShapeList<ShapeTypes...>& other) {
				_shapes.reserve(_shapes.size() + other.size());
				for (const auto& obj : other._shapes) {
					_shapes.push_back(obj); 
				}
			}
			//　グループを追加する（ムーブ追加※引数のListは空になる）
			void addList(ShapeList<ShapeTypes...>&& other) {
				_shapes.reserve(_shapes.size() + other.size());
				for (auto& obj : other._shapes) {
					_shapes.push_back(std::move(obj)); // ムーブ
				}
			}

			// 生のポインタを返す
			ShapeTypeVariant* data() noexcept {
				return _shapes.data();
			}
			const ShapeTypeVariant* data() const noexcept {
				return _shapes.data();
			}

			// リストが空かどうか調べる
			bool empty() const {
				return _shapes.empty();
			}

			// リスト内のオブジェクトの数を返す
			std::size_t size() const {
				return _shapes.size();
			}
			    // イテレータ（for を使いたい場合に使用）
			auto begin() noexcept { return _shapes.begin(); }
			auto end() noexcept { return _shapes.end(); }
			auto begin() const noexcept { return _shapes.begin(); }
			auto end() const noexcept { return _shapes.end(); }

			auto rbegin() noexcept { return _shapes.rbegin(); }
			auto rend() noexcept { return _shapes.rend(); }
			auto rbegin() const noexcept { return _shapes.rbegin(); }
			auto rend() const noexcept { return _shapes.rend(); }

	};

}

#endif