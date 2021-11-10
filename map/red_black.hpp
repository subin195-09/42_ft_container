/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:24:48 by skim              #+#    #+#             */
/*   Updated: 2021/11/10 19:22:00 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_HPP
# define RED_BLACK_HPP

#include "pair.hpp"
#include "../utils.hpp"

namespace ft
{
	template <typename Key, typename T, class Compare = ft::less<Key> >
	class node
	{
		private:
			node	*parent;
			node	*left;
			node	*right;
			Compare	cmp;

			// priate functions

		public:
			pair<const Key, T>	ip;

			node() : parent(NULL), eft(NULL), right(NULL) {}
			node(Key first, T second) = T()) :  parent(NULL), eft(NULL), right(NULL) ,ip(first, second) {}
			node(const pair<Key, T> &p) : parent(NULL), eft(NULL), right(NULL) ,ip(p) {}

			//deep copy 추후 좀 더 연구해 볼 것
			node(const node<Key, T, Compare> &origin, node<key, T, Compare> *parent = NULL) : parent(parent), left(NULL), right(NULL), ip(origin.ip)
			{
				if (origin.left != NULL)
					left = new node<Key, T, Compare>(*origin.left, this);
				if (origin.right != NULL)
					right = new node<Key, T, Compare>(*origin.right, this);
			}

			~node() {}

			void deleteAll(node<Key, T, Compare> *root)
			{
				if (root == NULL)
					return ;
				if (root->left != NULL)
					deleteAll(root->left);
				if (root->right != NULL)
					deleteAll(root->right);
				delete(root);
			}

			// getLeftest, getRightest (iterator)

			// find []operator
			// mergeInsert (insert)

			// deleteNode (erase)

			// getLowerBound, getUpperBound

	};

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
