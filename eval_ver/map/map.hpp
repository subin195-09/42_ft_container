/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:59:26 by skim              #+#    #+#             */
/*   Updated: 2021/12/21 15:26:32 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <memory>
#include "../utils/utils.hpp"
#include "../tree_utils/red_black.hpp"
#include "../tree_utils/pair.hpp"
#include "map_iterator.hpp"

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{
		public:
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef pair<const Key, T>									value_type;
			typedef Compare												key_compare;
			typedef node<Key, T, Compare>								node_type;
			typedef Alloc												allocator_type;
			typedef typename Alloc::template rebind<node_type>::other	node_allocator_type;
			typedef value_type											&reference;
			typedef const value_type									&const_reference;
			typedef value_type											*pointer;
			typedef const value_type									*const_pointer;
			typedef ptrdiff_t											difference_type;
			typedef size_t												size_type;
			typedef mapIterator<Key, T, Compare>						iterator;
			typedef mapConstIterator<Key, T, Compare>					const_iterator;
			typedef mapReverseIterator<Key, T, Compare>					reverse_iterator;
			typedef mapReverseConstIterator<Key, T, Compare>			const_reverse_iterator;

		private:
			node<Key, T, Compare>	*root;
			saver<Key, T, Compare>	*svr;
			unsigned int			num_of_ele;

			void	setSV() { svr->root = root; }

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
					bool operator()(const value_type &x, const value_type &y) const
					{
						return comp(x.first, y.first);
					}
			};

			/**constructor**/
			// default constructor
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : root(NULL), num_of_ele(0)
			{
				(void)comp;
				(void)alloc;
				svr = new ft::saver<Key, T, Compare>();
			}
			// range constructor
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : root(NULL), num_of_ele(0)
			{
				(void)comp;
				(void)alloc;
				svr = new ft::saver<Key, T, Compare>();
				insert(first, last);
			}
			// copy constructor
			map (const map &x) : root(NULL), num_of_ele(0)
			{
				root = new node<Key, T, Compare>(*(x.root));
				num_of_ele = x.num_of_ele;
				svr = new ft::saver<Key, T, Compare>();
				setSV();
			}

			// =operator
			map<Key, T, Compare, Alloc>	&operator=(const map<Key, T, Compare, Alloc> &x)
			{
				root->deleteAll(root);
				root = new node<Key, T, Compare>(*(x.root));
				num_of_ele = x.num_of_ele;
				setSV();
				return (*this);
			}
			// destructor
			~map()
			{
				if (num_of_ele > 0)
					root->deleteAll(root);
				delete (svr);
			}

			/**iterator**/
			iterator				begin() { return iterator(root->getLeftest(root), svr); }
			const_iterator			begin() const { return (const_iterator(root->getLeftest(root), svr)); }
			iterator				end() { return iterator(NULL, svr); }
			const_iterator			end() const { return (const_iterator(NULL, svr)); }
			reverse_iterator		rbegin() { return (reverse_iterator(root->getRightest(root), svr)); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(root->getRightest(root), svr)); }
			reverse_iterator		rend() { return reverse_iterator(NULL, svr); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(NULL, svr)); }

			/**capacity**/
			bool		empty() const { return (num_of_ele == 0); }
			size_type	size() const { return (num_of_ele); }
			size_type	max_size() const { return (Alloc().max_size()); }

			/**element_access**/
			mapped_type	&operator[](const key_type &key)
			{
				node<Key, T, Compare> *ret;
				if (num_of_ele == 0)
				{
					num_of_ele++;
					root = new node<Key, T, Compare>(key);
					setSV();
					return (root->ip.second);
				}
				else
				{
					if ((ret = root->find(root, key)) != NULL)
						return (ret->ip.second);
					else
					{
						num_of_ele++;
						mapped_type &ret = root->mergeInsert(root, key)->ip.second;
						root = root->getRoot(root);
						setSV();
						return (ret);
					}
				}
			}

			/**modifiers**/
			// map의 insert 구조에 대해 좀 더 파악해 볼 것
			// 모든 insert가 첫번째 insert를 call 하게 됨
			pair<iterator, bool>	insert(const value_type &x)
			{
				node<Key, T, Compare>	*ret;

				if (num_of_ele == 0)
				{
					num_of_ele++;
					root = new node<Key, T, Compare>(x.first, x.second);
					setSV();
					return (pair<iterator, bool>(iterator(root, svr), true));
				}
				else
				{
					if ((ret = root->find(root, x.first)) != NULL)
						return (pair<iterator, bool>(iterator(ret, svr), false));
					else
					{
						num_of_ele++;
						ret = root->mergeInsert(root, x.first, x.second);
						root = root->getRoot(root);
						setSV();
						return (pair<iterator, bool>(iterator(ret, svr), true));
					}
				}
			}

			iterator				insert(iterator position, const value_type &x)
			{
				(void)position;
				return (insert(x).first);
			}

			template <class InputIterator>
			void					insert(InputIterator first, InputIterator last)
			{
				for (InputIterator it = first; it != last; it++)
					insert(pair<const Key, T>(it->first, it->second));
			}

			size_type				erase(const key_type &key)
			{
				if (num_of_ele == 0)
					return (0);
				else
				{
					if (root->find(root, key) == NULL)
						return (0);
					else
					{
						if (num_of_ele == 1)
						{
							delete (root);
							root = NULL;
							setSV();
							num_of_ele--;
							return (1);
						}
						root->deleteNode(&root, root, key);
						setSV();
						num_of_ele--;
						return (1);
					}
				}
			}

			void					erase(iterator position)
			{
				erase(position->first);
			}

			void					erase(iterator first, iterator last)
			{
				iterator	iter = first;
				iterator	iter_next;
				while (iter != last)
				{
					iter_next = iter;
					iter_next++;
					erase(iter->first);
					iter = iter_next;
					if (iter == last)
						break;
				}
			}

			void					swap(map &x)
			{
				node<Key, T, Compare>	*tmp = root;
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

			/**observers**/
			key_compare		key_comp() const { return (Compare()); }
			value_compare	value_comp() const { return (value_compare()); }

			/**operator**/
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

			// lower_bound, upper_bound에 대해 좀 더 알아볼 것!
			iterator		lower_bound(const key_type &key)
			{
				// if (num_of_ele == 0)
				// 	return (iterator(NULL, svr));
				// return (iterator(root->getLowerBound(root, key), svr));
				iterator it = begin();

				for (; it != end(); ++it)
					if (key <= it->first)
						break;
				return it;
			}

			const_iterator	lower_bound(const key_type &key) const
			{
				const_iterator it = begin();

				for (; it != end(); ++it)
					if (key <= it->first)
						break;
				return it;
			}

			iterator		upper_bound(const key_type &key)
			{
				iterator it = begin();

				for (; it != end(); ++it)
					if (key < it->first)
						break;
				return it;
			}

			const_iterator	upper_bound(const key_type &key) const
			{
				const_iterator it = begin();

				for (; it != end(); ++it)
					if (key < it->first)
						break;
				return it;
			}

			pair<iterator, iterator>				equal_range(const key_type &key)
			{
				return (pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}

			pair<const_iterator, const_iterator>	equal_range(const key_type &key) const
			{
				return (pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
			}

			Alloc	get_allocator() const { return (Alloc()); }

			void	nodePrint(void)
			{
				root->tree_print(root, "", true);
			}
	};

	template < class Key, class T, class Compare, class Alloc >
	bool	operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template < class Key, class T, class Compare, class Alloc >
	bool	operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template < class Key, class T, class Compare, class Alloc >
	bool	operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template < class Key, class T, class Compare, class Alloc >
	bool	operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template < class Key, class T, class Compare, class Alloc >
	bool	operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
	{
		return (!(lhs > rhs));
	}

	template < class Key, class T, class Compare, class Alloc >
	bool	operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key,T,Compare,Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template < class Key, class T, class Compare, class Alloc >
	void swap(map< Key, T, Compare, Alloc >& x, map< Key, T, Compare, Alloc >& y)
	{
	  x.swap(y);
	}
}

#endif
