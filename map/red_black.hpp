/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:24:48 by skim              #+#    #+#             */
/*   Updated: 2021/11/08 17:51:56 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_HPP
# define RED_BLACK_HPP

#include "pair.hpp"
#include "../utils.hpp"

namespace ft
{
	template <typename Key, typename T, class Compate = ft::less<Key> >
	class saver
	{
		public:
			node<Key, T>	*root;

			saver(node<Key, T, Compate> *root = NULL) : root(root) {}
			~saver() {}
			saver(const saver<Key, T, Compate> &other) : root(other.root) {}
			saver	&operator=(const saver<Key, T, Compate> &other)
			{
				if (this != &other)
					this->root = other.root;
				return (*this);
			}
	};
}

#endif
