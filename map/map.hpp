/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:59:26 by skim              #+#    #+#             */
/*   Updated: 2021/11/10 19:56:51 by skim             ###   ########.fr       */
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

			void	setSV() { saver->root = root; }

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
			// default constructor
			explict map (const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : root(NULL), num_of_ele(0)
			{
				(void)comp;
				(void)alloc;
				saver = new saver<Key, T, Compare>();
			}
			// range constructor
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : root(NULL), num_of_ele(0)
			{
				(void)comp;
				(void)alloc;
				saver = new saver<Key, T, Compare>();
				insert(first, last);
			}
			// copy constructor
			map (const map &x) : root(NULL), num_of_ele(0)
			{
				root = new node<Key, T, Compare>(*(x.root));
				num_of_ele = x.num_of_ele;
				sv = new saver<Key, T, Compare>();
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
				delete (saver);
			}

			/**iterator**/
			iterator				begin() { return iterator(root->getLeftest(root), saver); }
			const_iterator			begin() const { return (const_iterator(root->getLeftest(root), saver)); }
			iterator				end() { return iterator(NULL, saver); }
			const_iterator			end() const { return (const_iterator(NULL, saver)); }
			reverse_iterator		rbegin() { return reverse_iterator(reverse_iterator(root->getRightest(root), saver)); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(reverse_iterator(root->getRightest(root), saver))); }
			reverse_iterator		rend() { return reverse_iterator((NULL, saver)); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(NULL, saver)); }

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
					if ((ret = root->find(root, key)) != NULL)\
						return (root->ip.second);
					else
					{
						num_of_ele++;
						retrun (root->mergeInsert(root, key)->ip.second);
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
					return (pair<iterator, bool>(iterator(root, saver), true));
				}
				else
				{
					if ((ret = root->find((root, x.first)) != NULL))
						return (pair<iterator, bool>(iterator(ret, saver), false));
					else
					{
						num_of_ele++;
						ret = root->mergeInsert(root, x.first, x.second);
						return (pair<iterator, bool>(iterator(ret, saver), true));
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
						root->deleteNode(&root, root, k);
						setSV();
						num_of_ele--;
						if (num_of_ele == 0)
						{
							root = NULL;
							setSV();
						}
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
				deleteAll(root);
				root = NULL;
			}

			/**observers**/
			key_compare		key_comp() const { return (Compare()); }
			value_compare	value_comp() const { return (value_compare()); }

			/**operator**/
			iterator		find(const key_type &key)
			{
				if (num_of_ele == 0)
					return (iterator(NULL, saver));
				return (ierator(root->find(root, key), saver));
			}

			const_iterator	find(const key_type &key) const
			{
				if (num_of_ele == 0)
					return (const_iterator(NULL, saver));
				return (const_iterator(root->find(root, key), saver));
			}

			size_type		count(const key_type &key) const
			{
				if (num_of_ele == 0 || root->find(root, key) == NULL)
					return (0);
				return (1);
			}

			// lower_bount, upper_bound에 대해 좀 더 알아볼 것!
			iterator		lower_bound(const key_type &key)
			{
				if (num_of_ele == 0)
					return (iterator(NULL, saver));
				return (iterator(root->getLowerBound((root, key), saver));
			}

			const_iterator	lower_bound(const key_type &key) const
			{
				if (num_of_ele == 0)
					return (const_iterator(NULL, saver));
				else
					return (const_iterator(root->getLowerBound(root, key), saver));
			}

			iterator		upper_bound(const key_type &key)
			{
				if (num_of_ele == 0)
					return (iterator(NULL, saver));
				return (iterator(root->getUpperBound((root, key), saver));
			}

			const_iterator	upper_bound(const key_type &key) const
			{
				if (num_of_ele == 0)
					return (const_iterator(NULL, saver));
				else
					return (const_iterator(root->getUpperBound(root, key), saver));
			}

			pair<iterator, iterator>	equal_range(const key_type &key)
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
