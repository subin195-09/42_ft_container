/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:03:33 by skim              #+#    #+#             */
/*   Updated: 2021/11/25 01:27:55 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "../tree_utils/red_black.hpp"
# include "../utils/utils.hpp"

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
			saver<Key, T, Compare>	*svr;
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
			mapIterator(node<Key, T, Compare> *now, saver<Key, T, Compare> *svr) : now(now), svr(svr){}
			mapIterator(const mapIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			~mapIterator() {}

			mapIterator<Key, T, Compare>	&operator=(const mapIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}

			pair<const Key, T> &operator*(void) const { return (now->ip); }
			pair<const Key, T> *operator->(void) const { return (&(this->operator*())); }

			mapIterator<Key, T, Compare>	&operator++(void)
			{
				now = getNext();
				return (*this);
			}
			mapIterator<Key, T, Compare>	operator++(int)
			{
				mapIterator<Key, T, Compare> tmp(*this);
				now = getNext();
				return (tmp);
			}
			mapIterator<Key, T, Compare>	&operator--(void)
			{
				now = getPrev();
				return (*this);
			}
			mapIterator<Key, T, Compare>	operator--(int)
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
			saver<Key, T, Compare> 	*getSV(void) const { return (svr); }

			node<Key, T, Compare>	*getPrev(void) const
			{
				if (now == NULL)
					return (now->getRightest(svr->root));
				if (now->getLeft() != NULL)
					return (now->getRightest(now->getLeft()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(now->ip.first, parent->ip.first))
					parent = parent->getParent();
				return (parent);
			}

			node<Key, T, Compare>	*getNext(void) const
			{
				if (now == NULL)
					return (now->getLeftest(svr->root));
				if (now->getRight() != NULL)
					return (now->getLeftest(now->getRight()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(parent->ip.first, now->ip.first))
					parent = parent->getParent();
				return (parent);
			}
	};

	template <typename Key, typename T, class Compare = ft::less<Key> >
	class mapConstIterator
	{
		private:
			node<Key, T, Compare>	*now;
			saver<Key, T, Compare>	*svr;
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
			mapConstIterator(node<Key, T, Compare> *now, saver<Key, T, Compare> *svr) : now(now), svr(svr) {}
			mapConstIterator(const mapConstIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			mapConstIterator(const mapIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			~mapConstIterator() {}

			mapConstIterator<Key, T, Compare>	&operator=(const mapConstIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}
			mapConstIterator<Key, T, Compare>	&operator=(const mapIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}

			const pair<const Key, T> &operator*(void) const { return (now->ip); }
			const pair<const Key, T> *operator->(void) const { return (&(this->operator*())); }

			mapConstIterator<Key, T, Compare>	&operator++(void)
			{
				now = getNext();
				return (*this);
			}
			mapConstIterator<Key, T, Compare>	operator++(int)
			{
				mapConstIterator<Key, T, Compare> tmp(*this);
				now = getNext();
				return (tmp);
			}
			mapConstIterator<Key, T, Compare>	&operator--(void)
			{
				now = getPrev();
				return (*this);
			}
			mapConstIterator<Key, T, Compare>	operator--(int)
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
			saver<Key, T, Compare>	*getSV(void) const { return (svr); }
			node<Key, T, Compare>	*getPrev(void) const
			{
				if (now == NULL)
					return (now->getRightest(svr->root));
				if (now->getLeft() != NULL)
					return (now->getRightest(now->getLeft()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(now->ip.first, parent->ip.first))
					parent = parent->getParent();
				return (parent);
			}
			node<Key, T, Compare>	*getNext(void) const
			{
				if (now == NULL)
					return (now->getLeftest(svr->root));
				if (now->getRight() != NULL)
					return (now->getLeftest(now->getRight()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(parent->ip.first, now->ip.first))
					parent = parent->getParent();
				return (parent);
			}
	};

	template <typename Key, typename T, class Compare = ft::less<Key> >
	class mapReverseIterator
	{
		private:
			node<Key, T, Compare>	*now;
			saver<Key, T, Compare>	*svr;
			Compare					cmp;

			class OutOfRangeException : public std::exception
			{
				virtual const char *what() const throw()
				{
					return ("Iterator is out of range");
				}
			};

		public:
			mapReverseIterator() {}
			mapReverseIterator(node<Key, T, Compare> *now, saver<Key, T, Compare> *svr) : now(now), svr(svr) {}
			mapReverseIterator(const mapReverseIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			mapReverseIterator(const mapIterator<Key, T, Compare> &origin) : now(origin.getPrev()), svr(origin.getSV()) {}
			~mapReverseIterator() {}

			mapReverseIterator<Key, T, Compare>	&operator=(const mapReverseIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}
			mapReverseIterator<Key, T, Compare>	&operator=(const mapIterator<Key, T, Compare> &origin)
			{
				now = origin.getPrev();
				svr = origin.getSV();
				return (*this);
			}

			pair<const Key, T> &operator*(void) const { return (now->ip); }
			pair<const Key, T> *operator->(void) const { return (&(this->operator*())); }

			// next, prev가 반대여야 하지 않나..??
			mapReverseIterator<Key, T, Compare>	&operator++(void)
			{
				now = getNext();
				return (*this);
			}
			mapReverseIterator<Key, T, Compare>	operator++(int)
			{
				mapReverseIterator<Key, T, Compare> tmp(*this);
				now = getNext();
				return (tmp);
			}
			mapReverseIterator<Key, T, Compare>	&operator--(void)
			{
				now = getPrev();
				return (*this);
			}
			mapReverseIterator<Key, T, Compare>	operator--(int)
			{
				mapReverseIterator<Key, T, Compare> tmp(*this);
				now = getPrev();
				return (tmp);
			}

			bool	operator==(const mapReverseIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator==(const mapReverseConstIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator!=(const mapReverseIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }
			bool	operator!=(const mapReverseConstIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }

			node<Key, T, Compare>	*getNow(void) const { return (now); }
			saver<Key, T, Compare>	*getSV(void) const { return (svr); }
			node<Key, T, Compare>	*getPrev(void) const
			{
				if (now == NULL)
					return (now->getLeftest(svr->root));
				if (now->getRight() != NULL)
					return (now->getLeftest(now->getRight()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(parent->ip.first, now->ip.first))
					parent = parent->getParent();
				return (parent);
			}
			node<Key, T, Compare>	*getNext(void) const
			{
				if (now == NULL)
					return (now->getRightest(svr->root));
				if (now->getLeft() != NULL)
					return (now->getRightest(now->getLeft()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(now->ip.first, parent->ip.first))
					parent = parent->getParent();
				return (parent);
			}

			mapIterator<Key, T, Compare>	base(void) const
			{
				return (mapIterator<Key, T, Compare>(getPrev(), svr));
			}
	};

	template <typename Key, typename T, class Compare = ft::less<Key> >
	class mapReverseConstIterator
	{
		private:
			node<Key, T, Compare>	*now;
			saver<Key, T, Compare>	*svr;
			Compare					cmp;

			class OutOfRangeException : public std::exception
			{
				virtual const char *what() const throw()
				{
					return ("Iterator is out of range");
				}
			};

		public:
			mapReverseConstIterator() {}
			mapReverseConstIterator(node<Key, T, Compare> *now, saver<Key, T, Compare> *svr) : now(now), svr(svr) {}
			mapReverseConstIterator(const mapReverseConstIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			mapReverseConstIterator(const mapReverseIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			mapReverseConstIterator(const mapConstIterator<Key, T, Compare> &origin) : now(origin.getPrev()), svr(origin.getSV()) {}
			mapReverseConstIterator(const mapIterator<Key, T, Compare> &origin) : now(origin.getPrev()), svr(origin.getSV()) {}
			~mapReverseConstIterator() {}

			mapReverseConstIterator<Key, T, Compare>	&operator=(const mapReverseConstIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}
			mapReverseConstIterator<Key, T, Compare>	&operator=(const mapReverseIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}
			mapReverseConstIterator<Key, T, Compare>	&operator=(const mapConstIterator<Key, T, Compare> &origin)
			{
				now = origin.getPrev();
				svr = origin.getSV();
				return (*this);
			}
			mapReverseConstIterator<Key, T, Compare>	&operator=(const mapIterator<Key, T, Compare> &origin)
			{
				now = origin.getPrev();
				svr = origin.getSV();
				return (*this);
			}

			const pair<const Key, T>	&operator*(void) const { return (now->ip); }
			const pair<const Key, T>	*operator->(void) const { return (&(this->operator*())); }

			mapReverseConstIterator<Key, T, Compare>	&operator++(void)
			{
				now = getNext();
				return (*this);
			}
			mapReverseConstIterator<Key, T, Compare>	operator++(int)
			{
				mapReverseConstIterator<Key, T, Compare> tmp(*this);
				now = getNext();
				return (tmp);
			}
			mapReverseConstIterator<Key, T, Compare>	&operator--(void)
			{
				now = getPrev();
				return (*this);
			}
			mapReverseConstIterator<Key, T, Compare>	operator--(int)
			{
				mapReverseConstIterator<Key, T, Compare> tmp(*this);
				now = getPrev();
				return (tmp);
			}

			bool	operator==(const mapReverseConstIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator==(const mapReverseIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator!=(const mapReverseConstIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }
			bool	operator!=(const mapReverseIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }

			node<Key, T, Compare>	*getNow(void) const { return (now); }
			saver<Key, T, Compare>	*getSV(void) const { return (svr); }
			node<Key, T, Compare>	*getPrev(void) const
			{
				if (now == NULL)
					return (now->getLeftest(svr->root));
				if (now->getRight() != NULL)
					return (now->getLeftest(now->getRight()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(parent->ip.first, now->ip.first))
					parent = parent->getParent();
				return (parent);
			}
			node<Key, T, Compare>	*getNext(void) const
			{
				if (now == NULL)
					return (now->getRightest(svr->root));
				if (now->getLeft() != NULL)
					return (now->getRightest(now->getLeft()));
				node<Key, T, Compare> *parent = now->getParent();
				while (parent != NULL && cmp(now->ip.first, parent->ip.first))
					parent = parent->getParent();
				return (parent);
			}

			mapConstIterator<Key, T, Compare>	base(void) const
			{
				return (mapConstIterator<Key, T, Compare>(getPrev(), svr));
			}
	};
}

#endif
