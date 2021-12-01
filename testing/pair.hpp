/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:37:37 by skim              #+#    #+#             */
/*   Updated: 2021/11/30 18:45:47 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template<class T1, class T2>
	class pair
	{
		public:
			T1 first;
			T2 second;

			pair(void) : first(), second() {};
			pair(const T1 &_first, const T2 &_second) : first(_first), second(_second) {};
			pair(const pair<T1, T2> &other) : first(other.first), second(other.second) {};

			template <typename U, typename V>
			pair(const pair<U, V> &other) : first(other.first), second(other.second) {};
			~pair() {};

			pair	&operator=(const pair<T1, T2> &other)
			{
				if (this != &other)
				{
					this->first = other.first;
					this->second = other.second;
				}
				return (*this);
			}
	};


template < class T1, class T2 >
bool operator==(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs) {
  return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template < class T1, class T2 >
bool operator!=(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs) {
  return !(lhs == rhs);
}

template < class T1, class T2 >
bool operator<(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs) {
  return lhs.first < rhs.first ||
         (!(rhs.first < lhs.first) && (lhs.second < rhs.second));
}

template < class T1, class T2 >
bool operator<=(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs) {
  return (!(rhs < lhs));
}

template < class T1, class T2 >
bool operator>(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs) {
  return (rhs < lhs);
}

template < class T1, class T2 >
bool operator>=(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs) {
  return !(lhs < rhs);
}

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}
}

#endif
