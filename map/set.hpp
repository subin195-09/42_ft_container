/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:02:54 by skim              #+#    #+#             */
/*   Updated: 2021/12/01 15:26:41 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include <iostream>
#include <memory>
#include "../utils.hpp"
#include "red_black.hpp"
#include "pair.hpp"
#include <set>

namespace ft
{
	template <class Key, class Compare = ft::less<Key>, class Alloc = std::allocator<Key> >
	class set
	{
		public:
			typedef Key					key_type;
			typedef Key					value_type;
			typedef Compare				key_compare;
			typedef key_compare			value_compare;
			typedef Alloc				allocator_type;
			typedef size_t				size_type;
			typedef value_type&			reference;
			typedef const value_type&	const_reference;
			typedef value_type*			pointer;
			typedef const value_type*	const_pointer;

			// allocator
			typedef implementation-defined                   iterator;
			typedef implementation-defined                   const_iterator;
			typedef std::reverse_iterator<iterator>          reverse_iterator;
			typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

		private:
			node<key_type, value_type, key_compare>		*root;
			saver<key_type, value_type, key_compare>	*saver;
			unsigned int								num_of_ele;

			void	setSV() { svr->root = root; }

		public:
			void					swap(map &x)
			{
				node<key_type, value_type, Compare>	*tmp = root;
				root = x.root;
				x.root = tmp;

				unsigned int	temp_size = num_of_ele;
				num_of_ele = x.num_of_ele;
				x.num_of_ele = temp_size;
			}

			void					clear()
			{
				if (num_of_ele == 0)
					return ;
				num_of_ele = 0;
				root->deleteAll(root);
				root = NULL;
			}

			iterator		find(const key_type &key)
			{
				if (num_of_ele == 0)
					return (iterator(NULL, svr));
				return (iterator(root->find(root, key), svr));
			}

			const_iterator	find(const key_type &key) const
			{
				if (num_of_ele == 0)
					return (const_iterator(NULL, svr));
				return (const_iterator(root->find(root, key), svr));
			}

			size_type		count(const key_type &key) const
			{
				if (num_of_ele == 0 || root->find(root, key) == NULL)
					return (0);
				return (1);
			}

			iterator		lower_bound(const key_type &key)
			{
				if (num_of_ele == 0)
					return (iterator(NULL, svr));
				return (iterator(root->getLowerBound(root, key), svr));
			}

			const_iterator	lower_bound(const key_type &key) const
			{
				if (num_of_ele == 0)
					return (const_iterator(NULL, svr));
				else
					return (const_iterator(root->getLowerBound(root, key), svr));
			}

			iterator		upper_bound(const key_type &key)
			{
				if (num_of_ele == 0)
					return (iterator(NULL, svr));
				return (iterator(root->getUpperBound(root, key), svr));
			}

			const_iterator	upper_bound(const key_type &key) const
			{
				if (num_of_ele == 0)
					return (const_iterator(NULL, svr));
				else
					return (const_iterator(root->getUpperBound(root, key), svr));
			}

			key_compare		key_comp() const { return (key_compare()); }
			value_compare	value_comp() const { return (value_compare()); }

			pair<iterator, iterator>				equal_range(const key_type &key)
			{
				return (pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}

			pair<const_iterator, const_iterator>	equal_range(const key_type &key) const
			{
				return (pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
			}
	};
}

#endif
