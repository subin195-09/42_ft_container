/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:24:48 by skim              #+#    #+#             */
/*   Updated: 2021/11/11 20:41:58 by skim             ###   ########.fr       */
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

			node<Key, T, Compare>	*getRoot(node<Key, T, Compare> *root)
			{
				if (root->parent == NULL)
					return (root);
				return (getRoot(root->parent));
			}

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

			// find []operator
			node<Key, T, Compare>	*find(node<Key, T, Compare> *root, const Key &key)
			{
				if ((cmp(root->ip.first, key) == false) && (cmp(key, root->ip.first) == false))
					return (root);
				if (cmp(root->ip.first, key))
				{
					if (root->right == NULL)
						return (NULL);
					return (find(root->right, key));
				}
				else
				{
					if (root->left == NULL)
						return (NULL);
					return (find(root->left, key));
				}
			}

			// mergeInsert (insert) : value를 갱신하거나, key를 추가함

			// getLowerBound, getUpperBound(key 보다 큰값중 가장 작은 값)

			// getLeftest, getRightest (iterator)
			node<Key, T, Compare>	*getLeftest(node<Key, T, Compare> *root)
			{
				if (root == NULL || root->left == NULL)
					return (root);
				return (getLeftest(root->left));
			}

			node<Key, T, Compare>	*getRightest(node<Key, T, Compare> *root)
			{
				if (root == NULL || root->right == NULL)
					return (root);
				return (getRightest(root->right));
			}

			// deleteNode (erase)

			// getter
			node<Key, T, Compare>	*getParent(node<Key, T, Compare> *root) { return (root->parent); }
			node<Key, T, Compare>	*getLeft(node<Key, T, Compare> *root) { return (root->left); }
			node<Key, T, Compare>	*getRight(node<Key, T, Compare> *root) { return (root->right); }

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
