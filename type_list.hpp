/* Modifiable tuple of types
 * Copyright (C) 2018  Jan Lafferton
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef TYPE_LIST_HPP
#define TYPE_LIST_HPP

#include <type_traits>
#include <utility>

template<typename ... Ts>
struct type_list;

namespace tl {
	/* Concat */
	template<typename TypeList1, typename TypeList2>
	struct concat_impl;

	template<typename ... Types1, typename ... Types2>
	struct concat_impl<type_list<Types1...>, type_list<Types2...>> {
		using type = type_list<Types1..., Types2...>;
	};

	template<typename ... Types>
	struct concat_impl<type_list<Types...>, type_list<>> {
		using type = type_list<Types...>;
	};

	/* Remove */
	template<typename Type, typename TypeList, bool All>
	struct remove_impl;

	template<typename Type, typename Head, bool All>
	struct remove_impl<Type, type_list<Head>, All> {
		using type = type_list<Head>;
	};
	
	template<typename Type, bool All>
	struct remove_impl<Type, type_list<Type>, All>  {
		using type = type_list<>;
	};

	template<typename Type, typename Head, typename ... Tail, bool All>
	struct remove_impl<Type, type_list<Head, Tail...>, All> {
		using type = typename concat_impl<type_list<Head>, typename remove_impl<Type, type_list<Tail...>, All>::type>::type;
	};

	template<typename Type, typename ... Tail>
	struct remove_impl<Type, type_list<Type, Tail...>, false> {
		using type = type_list<Tail...>;
	};

	template<typename Type, typename ... Tail>
	struct remove_impl<Type, type_list<Type, Tail...>, true> {
		using type = typename remove_impl<Type, type_list<Tail...>, true>::type;
	};

	/* Recursive remove */
	template<typename TypeList, typename ... Types>
	struct recursive_remove_impl;

	template<typename TypeList, typename Type>
	struct recursive_remove_impl<TypeList, Type> {
		using type = typename remove_impl<Type, TypeList, true>::type;
	};

	template<typename TypeList, typename Type, typename ... Types>
	struct recursive_remove_impl<TypeList, Type, Types...> {
		using type = typename recursive_remove_impl<typename remove_impl<Type, TypeList, true>::type, Types...>::type;
	};

	/* Get */
	template<size_t I, typename TypeList>
	struct get_impl;

	template<typename Head, typename ... Tail>
	struct get_impl<0, type_list<Head, Tail...>> {
		using type = Head;
	};

	template<size_t I, typename Head, typename ... Tail>
	struct get_impl<I, type_list<Head, Tail...>> {
		using type = typename get_impl<I - 1, type_list<Tail...>>::type;
	};
}

template<typename ... Types>
struct type_list {
	template<typename ... Types2>
	using add = type_list<Types..., Types2...>;

	template<typename T>
	using remove = typename tl::remove_impl<T, type_list<Types...>, false>::type;

	template<typename ... Types2>
	using remove_all = typename tl::recursive_remove_impl<type_list<Types...>, Types2...>::type;

	template<typename TypeList>
	using concat = typename tl::concat_impl<type_list<Types...>, TypeList>::type;

	template<size_t I>
	using get = typename tl::get_impl<I, type_list<Types...>>::type;

	static const constexpr size_t size = sizeof...(Types);
};

template<>
struct type_list<> {
	template<typename ... Types>
	using add = type_list<Types...>;

	template<typename T>
	using remove = type_list<>;

	template<typename ... Types>
	using remove_all = type_list<>;

	template<typename TypeList>
	using concat = TypeList;

	static const constexpr size_t size = 0;
};

#endif // TYPE_LIST_HPP