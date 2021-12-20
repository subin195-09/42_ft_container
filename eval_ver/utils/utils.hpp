/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:23:52 by skim              #+#    #+#             */
/*   Updated: 2021/12/20 15:48:40 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_HPP
# define TOOLS_HPP

namespace ft
{
	template <typename T>
	struct less
	{
		bool operator()(const T &lhs, const T &rhs) const
		{
			return lhs < rhs;
		}
	};

	template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, \
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
				return (true);
			else if (*first2 < *first1)
				return (false);
			first1++;
			first2++;
		}
		return (first1 == last1 && first2 != last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_less(InputIterator1 first1, InputIterator1 last1, \
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
				return (true);
			else if (*first2 < *first1)
				return (false);
			first1++;
			first2++;
		}
		return (first1 == last1 && first2 != last2);
	}


}

#endif
