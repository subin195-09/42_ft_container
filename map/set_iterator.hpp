/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:36:50 by skim              #+#    #+#             */
/*   Updated: 2021/12/08 16:36:51 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_ITERATOR_HPP
# define SET_ITERATOR_HPP

# include "red_black.hpp"
# include "../utils.hpp"

namespace ft
{
	template <typename Key, typename T, class Compare>
	class setIterator;

	template <typename Key, typename T, class Compare>
	class setConstIterator;

	template <typename Key, typename T, class Compare>
	class setReverseIterator;

	template <typename Key, typename T, class Compare>
	class setReverseConstIterator;

	template <typename Key, typename T, class Compare = ft::less<Key> >
	class setIterator
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
			setIterator() {}
			setIterator(node<Key, T, Compare> *now, saver<Key, T, Compare> *svr) : now(now), svr(svr)
			{
			}
			setIterator(const setIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			~setIterator() {}

			setIterator<Key, T, Compare>	&operator=(const setIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}

			const Key	&operator*(void) const  { return (now->ip.first); }
			const Key	*operator->(void) const { return (&(this->operator*())); }

			setIterator<Key, T, Compare>	&operator++(void)
			{
				now = getNext();
				return (*this);
			}
			setIterator<Key, T, Compare>	operator++(int)
			{
				setIterator<Key, T, Compare> tmp(*this);
				now = getNext();
				return (tmp);
			}
			setIterator<Key, T, Compare>	&operator--(void)
			{
				now = getPrev();
				return (*this);
			}
			setIterator<Key, T, Compare>	operator--(int)
			{
				setIterator<Key, T, Compare> tmp(*this);
				now = getPrev();
				return (tmp);
			}

			bool	operator==(const setIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator==(const setConstIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator!=(const setIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }
			bool	operator!=(const setConstIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }

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
	class setConstIterator
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
			setConstIterator() {}
			setConstIterator(node<Key, T, Compare> *now, saver<Key, T, Compare> *svr) : now(now), svr(svr) {}
			setConstIterator(const setConstIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			setConstIterator(const setIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			~setConstIterator() {}

			setConstIterator<Key, T, Compare>	&operator=(const setConstIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}
			setConstIterator<Key, T, Compare>	&operator=(const setIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}

			const Key	&operator*(void) const { return (now->ip.first); }
			const Key	*operator->(void) const { return (&(this->operator*())); }

			setConstIterator<Key, T, Compare>	&operator++(void)
			{
				now = getNext();
				return (*this);
			}
			setConstIterator<Key, T, Compare>	operator++(int)
			{
				setConstIterator<Key, T, Compare> tmp(*this);
				now = getNext();
				return (tmp);
			}
			setConstIterator<Key, T, Compare>	&operator--(void)
			{
				now = getPrev();
				return (*this);
			}
			setConstIterator<Key, T, Compare>	operator--(int)
			{
				setConstIterator<Key, T, Compare> tmp(*this);
				now = getPrev();
				return (tmp);
			}

			bool	operator==(const setConstIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator==(const setIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator!=(const setConstIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }
			bool	operator!=(const setIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }

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
	class setReverseIterator
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
			setReverseIterator() {}
			setReverseIterator(node<Key, T, Compare> *now, saver<Key, T, Compare> *svr) : now(now), svr(svr) {}
			setReverseIterator(const setReverseIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			setReverseIterator(const setIterator<Key, T, Compare> &origin) : now(origin.getPrev()), svr(origin.getSV()) {}
			~setReverseIterator() {}

			setReverseIterator<Key, T, Compare>	&operator=(const setReverseIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}
			setReverseIterator<Key, T, Compare>	&operator=(const setIterator<Key, T, Compare> &origin)
			{
				now = origin.getPrev();
				svr = origin.getSV();
				return (*this);
			}

			const Key	&operator*(void) const { return (now->ip.first); }
			const Key	*operator->(void) const { return (&(this->operator*())); }

			// next, prev가 반대여야 하지 않나..??
			setReverseIterator<Key, T, Compare>	&operator++(void)
			{
				now = getNext();
				return (*this);
			}
			setReverseIterator<Key, T, Compare>	operator++(int)
			{
				setReverseIterator<Key, T, Compare> tmp(*this);
				now = getNext();
				return (tmp);
			}
			setReverseIterator<Key, T, Compare>	&operator--(void)
			{
				now = getPrev();
				return (*this);
			}
			setReverseIterator<Key, T, Compare>	operator--(int)
			{
				setReverseIterator<Key, T, Compare> tmp(*this);
				now = getPrev();
				return (tmp);
			}

			bool	operator==(const setReverseIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator==(const setReverseConstIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator!=(const setReverseIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }
			bool	operator!=(const setReverseConstIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }

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

			setIterator<Key, T, Compare>	base(void) const
			{
				return (setIterator<Key, T, Compare>(getPrev(), svr));
			}
	};

	template <typename Key, typename T, class Compare = ft::less<Key> >
	class setReverseConstIterator
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
			setReverseConstIterator() {}
			setReverseConstIterator(node<Key, T, Compare> *now, saver<Key, T, Compare> *svr) : now(now), svr(svr) {}
			setReverseConstIterator(const setReverseConstIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			setReverseConstIterator(const setReverseIterator<Key, T, Compare> &origin) : now(origin.getNow()), svr(origin.getSV()) {}
			setReverseConstIterator(const setConstIterator<Key, T, Compare> &origin) : now(origin.getPrev()), svr(origin.getSV()) {}
			setReverseConstIterator(const setIterator<Key, T, Compare> &origin) : now(origin.getPrev()), svr(origin.getSV()) {}
			~setReverseConstIterator() {}

			setReverseConstIterator<Key, T, Compare>	&operator=(const setReverseConstIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}
			setReverseConstIterator<Key, T, Compare>	&operator=(const setReverseIterator<Key, T, Compare> &origin)
			{
				now = origin.getNow();
				svr = origin.getSV();
				return (*this);
			}
			setReverseConstIterator<Key, T, Compare>	&operator=(const setConstIterator<Key, T, Compare> &origin)
			{
				now = origin.getPrev();
				svr = origin.getSV();
				return (*this);
			}
			setReverseConstIterator<Key, T, Compare>	&operator=(const setIterator<Key, T, Compare> &origin)
			{
				now = origin.getPrev();
				svr = origin.getSV();
				return (*this);
			}

			const Key	&operator*(void) const { return (now->ip.first); }
			const Key	*operator->(void) const { return (&(this->operator*())); }

			setReverseConstIterator<Key, T, Compare>	&operator++(void)
			{
				now = getNext();
				return (*this);
			}
			setReverseConstIterator<Key, T, Compare>	operator++(int)
			{
				setReverseConstIterator<Key, T, Compare> tmp(*this);
				now = getNext();
				return (tmp);
			}
			setReverseConstIterator<Key, T, Compare>	&operator--(void)
			{
				now = getPrev();
				return (*this);
			}
			setReverseConstIterator<Key, T, Compare>	operator--(int)
			{
				setReverseConstIterator<Key, T, Compare> tmp(*this);
				now = getPrev();
				return (tmp);
			}

			bool	operator==(const setReverseConstIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator==(const setReverseIterator<Key, T, Compare> &origin) const { return (now == origin.getNow()); }
			bool	operator!=(const setReverseConstIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }
			bool	operator!=(const setReverseIterator<Key, T, Compare> &origin) const { return (!(this->operator==(origin))); }

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

			setConstIterator<Key, T, Compare>	base(void) const
			{
				return (setConstIterator<Key, T, Compare>(getPrev(), svr));
			}
	};
}

#endif
