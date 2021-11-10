/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:03:33 by skim              #+#    #+#             */
/*   Updated: 2021/11/10 20:41:21 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "red_black.hpp"
# include "../utils.hpp"

namespace ft
{
	template <typename Key, typename T, class Compare>
	class mapIterator;

	template <typename Key, typename T, class Compare>
	class mapConstIterator;

	template <typename Key, typename T, class Compare>
	class mapReverseIterator;

	template <typename Key, typename T, class Compare>
	class mapReverseConstIterator;

	template <typename Key, typename T, class Compare = ft::less<Key> >
	class mapIterator
	{
		private:
			node<Key, T, Compare>	*now;
			saver<Key, T, Compare>	*saver;
			Compare					cmp;

			class OutOfRangeException : public std::exception
			{
				virtual const char *what() const throw()
				{
					return ("Iterator is out of range");
				}
			};

		public:
			mapIterator() {}
			mapIterator(node<Key, T, Compare> *now, saver<Key, T, Compare> *saver) : now(now), saver(saver) {}
			mapIterator(const mapIterator<Key, Tm Compare> &origin) : now(origin.getNow()), saver(origin.getSV()) {}
			~mapIterator() {}

			mapIterator<Key, T, Compare> &operator=(const mapIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				saver = origin.getSV();
				return (*this);
			}

			pair<const Key, T> operator*(void) const { return (now->ip); }
			pair<const Key, T> *operator->(void) const { return (&(this->operator*())); }

			mapIterator<Key, T, Compare> &operator++(void)
			{
				now = getNext();
				return (*this);
			}
			mapIterator<Key, T, Compare> operator++(int)
			{
				mapIterator<Key, T, Compare> tmp(*this);
				now = getNext();
				return (tmp);
			}
			mapIterator<Key, T, Compare> &operator--(void)
			{
				now = getPrev();
				return (*this);
			}
			mapIterator<Key, T, Compare> operator--(int)
			{
				mapIterator<Key, T, Compare> tmp(*this);
				now = getPrev();
				return (tmp);
			}

			bool	operator==(const mapIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator==(const mapConstIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator!=(const mapIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }
			bool	operator!=(const mapConstIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }

			// red_black tree를 구성 후 좀 더 연구해볼 것
			node<Key, T, Compare>	*getNow(void) const { return (now); }
			saver<Key, T, Compare> 	*getSV(void) const { return (saver); }
			node<Key, T, Compare>	getPrev(void) const
			{
				if (now == NULL)
					return (now->getRightest(saver->root));
				if (now->getLeft() != NULL)
					return (now->getRightest(now->getLeft()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(now->ip.first, parent->ip.first))
					parent = parent->getParent();
				return (parent);
			}
			noed<Key, T, Compare>	getNext(void) const
			{
				if (now == NULL)
					return (now->getLeftest(saver->root));
				if (now->getRight() != NULL)
					return (now->getLeftest(now->getRight()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(now->ip.first, parent->ip.first))
					parent = parent->getParent();
				return (parent);
			}
	};

	template <typename Key, typename T, class Compare = ft::less<Key> >
	class mapConstIterator
	{
		private:
			node<Key, T, Compare>	*now;
			saver<Key, T, Compare>	*saver;
			Compare					cmp;

			class OutOfRangeException : public std::exception
			{
				virtual const char *what() const throw()
				{
					return ("Iterator is out of range");
				}
			};

		public:
			mapConstIterator() {}
			mapConstIterator(node<Key, T, Compare> *now, saver<Key, T, Compare> *saver) : now(now), saver(saver) {}
			mapConstIterator(const mapConstIterator<Key, T, Compare> &origin) : now(origin.getNow()), saver(origin.getSV()) {}
			mapConstIterator(const mapIterator<Key, T, Compare> &origin) : now(origin.getNow()), saver(origin.getSV()) {}
			~mapConstIterator() {}

			mapConstIterator<Key, T, Compare> &operator=(const mapConstIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				saver = origin.getSV();
				return (*this);
			}
			mapConstIterator<Key, T, Compare> &operator=(const mapIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				saver = origin.getSV();
				return (*this);
			}

			const pair<const Key, T> &operator*(void) const { return (now->ip); }
			const pair<const Key, T> *operator->(void) const { return (&(this->operator*())); }

			mapConstIterator<Key, T, Compare> &operator++(void)
			{
				now = getNext();
				return (*this);
			}
			mapConstIterator<Key, T, Compare> operator++(int)
			{
				mapConstIterator<Key, T, Compare> tmp(*this);
				now = getNext();
				return (tmp);
			}
			mapConstIterator<Key, T, Compare> &operator--(void)
			{
				now = getPrev();
				return (*this);
			}
			mapConstIterator<Key, T, Compare> operator--(int)
			{
				mapConstIterator<Key, T, Compare> tmp(*this);
				now = getPrev();
				return (tmp);
			}

			bool	operator==(const mapConstIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator==(const mapIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator!=(const mapConstIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }
			bool	operator!=(const mapIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }

			node<Key, T, Compare>	*getNow(void) const { return (now); }
			saver<Key, T, Compare>	*getSV(void) const { return (saver); }
			node<Key, T, Compare>	getPrev(void) const
			{
				if (now == NULL)
					return (now->getRightest(saver->root));
				if (now->getLeft() != NULL)
					return (now->getRightest(now->getLeft()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(now->ip.first, parent->ip.first))
					parent = parent->getParent();
				return (parent);
			}
			node<Key, T, Compare>	getNext(void) const
			{
				if (now == NULL)
					return (now->getLeftest(saver->root));
				if (now->getRight() != NULL)
					return (now->getLeftest(now->getRight()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(now->ip.first, parent->ip.first))
					parent = parent->getParent();
				return (parent);
			}
	};
}

#endif
