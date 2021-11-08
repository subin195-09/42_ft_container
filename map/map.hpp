/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:59:26 by skim              #+#    #+#             */
/*   Updated: 2021/11/08 17:26:44 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <memory>
#include "../utils.hpp"
#include "red_black.hpp"
#include "pair.hpp"
#include <map>

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<const Key, T>							value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef value_type									&reference;
			typedef const value_type							&const_reference;
			typedef value_type									*pointer;
			typedef const value_type							*const_pointer;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;
			// map_iterator 구현해서 대체할 것
			typedef mapIterator<Key, T, Compare>				iterator;
			typedef mapConstIterator<Key, T, Compare>			const_iterator;
			typedef mapReverseIterator<Key, T, Compare>			reverse_iterator;
			typedef mapReverseConstIterator<Key, T, Compare>	const_reverse_iterator;

		private:
			node<Key, T, Compare>	*root;
			saver<Key, T, Compare>	*saver;
			unsigned int			num_of_ele;

		public:
			class value_compare
			{
				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool 		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					value_compare() {}
					value_compare(const value_compare &other) : comp(other.comp) {}
					~value_compare() {}
					value_compare &operator=(const value_compare &other)
					{
						comp = other.comp;
						return *this;
					}
					bool operato() (const value_type &x, const value_type &y) const
					{
						return comp(x.first, y.first);
					}
			};

			/**constructor**/
			explict map (const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : root(NULL), num_of_ele(0)
			{
				
			}
	};
}

#endif
