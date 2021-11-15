/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:24:48 by skim              #+#    #+#             */
/*   Updated: 2021/11/15 20:19:49 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_HPP
# define RED_BLACK_HPP

#include "pair.hpp"
#include "../utils.hpp"

#define RED		true
#define BLACK	false

namespace ft
{
	template <typename Key, typename T, class Compare = ft::less<Key> >
	class node
	{
		private:
			node	*parent;
			node	*left;
			node	*right;
			bool	color;
			Compare	cmp;

			// priate functions (deleteNode에 필요, pearan ver)
			void childChange(node *from, node *to)
			{
				if (left == from)
					left = to;
				if (right == from)
					right = to;
			}

			void makeParentChildToMyChild()
			{
				if (parent == NULL)
					return ;
				if (left == NULL)
					parent->childChange(this, right);
				else
					parent->childChange(this, left);
			}

		public:
			pair<const Key, T>	ip;

			node() : parent(NULL), left(NULL), right(NULL) {}
			node(Key first, T second = T()) :  parent(NULL), left(NULL), right(NULL) ,ip(first, second) {}
			node(const pair<Key, T> &p) : parent(NULL), left(NULL), right(NULL) ,ip(p) {}

			//deep copy 추후 좀 더 연구해 볼 것
			node(const node<Key, T, Compare> &origin, node<Key, T, Compare> *parent = NULL) : parent(parent), left(NULL), right(NULL), ip(origin.ip)
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
			node<Key, T, Compare>	*mergeInsert(node<Key, T, Compare> *root, const Key &k, const T &v = T())
			{
				node<Key, T, Compare>	*child;

				if (cmp(root->ip.first, k) == false && cmp(k, root->ip.first) == false)
				{
					root->ip.second = v;
					return (root);
				}
				if (cmp(root->ip.first, k))
				{
					// 새로운 key 추가 (red_black tree 버전으로 수정하여야 함)
					if (root->right == NULL)
					{
						child = new node<Key, T, Compare>(k, v);
						root->right = child;
						child->parent = root;
						return (child);
					}
					return (mergeInsert(root->right, k, v));
				}
				else
				{
					// 새로운 key 추가
					if (root->left == NULL)
					{
						child = new node<Key, T, Compare>(k, v);
						root->left = child;
						child->parent = root;
						return (child);
					}
					return (mergeInsert(root->left, k, v));
				}
			}

			// getLowerBound, getUpperBound(key 보다 큰값중 가장 작은 값)
			// key보다 큰 값 중 제일 제일 작은 값
			node<Key, T, Compare>	*getUpperBound(node<Key, T, Compare> *root, const Key &key)
			{
				if (!cmp(key, root->ip.first)) // first <= key
				{
					if (root->right == NULL)
						return (NULL);
					else
						return (getUpperBound(root->right, key));
				}
				else
				{
					if (root->left == NULL)
						return (root);
					else
						return (getUpperBound(root->left, key));
				}
			}

			// key보다 크거나 같은 값 중 제일 제일 작은 값 (upperbound에서 same을 비교하는 로직만 추가)
			node<Key, T, Compare>	*getLowerBound(node<Key, T, Compare> *root, const Key &key)
			{
				if (root->ip.first == key)
					return (root);

				if (cmp(root->ip.first, key)) // first < key
				{
					if (root->right == NULL)
						return (root); // (key : NULL, value : 마지막에 탐색된 value 값이 리턴되어야 한다.) = > segfault 문제
					else
						return (getLowerBound(root->right, key));
				}
				else
				{
					if (root->left == NULL)
						return (root);
					else
						return (getLowerBound(root->left, key));
				}
			}

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

			// deleteNode (erase) - pearan2 Ver (red_black tree 버전으로 수정하여야 함)
			void deleteNode(node<Key, T, Compare>**real_root, node<Key, T, Compare> *root, const Key& tk)
			{
				node<Key, T, Compare> *newRoot;

				if ((cmp(root->ip.first, tk) == false) && (cmp(tk, root->ip.first) == false))
				{
					if (root->left != NULL)
					{
						newRoot = getRightest(root->left);
						newRoot->makeParentChildToMyChild(); // 부모와 자신자식의 라인을 이어준다. (이떄 newRoot 는 반드시 자식이 하나이므로 반드시 연결된다.)

						////////////
						if (newRoot->left != NULL)
							newRoot->left->parent = newRoot->parent;
						if (newRoot->right != NULL)
							newRoot->right->parent = newRoot->parent;
						///////////

						newRoot->left = root->left;
						newRoot->right = root->right;
						newRoot->parent = root->parent;
						if (root->parent != NULL)
							root->parent->childChange(root, newRoot);
						if (root->left != NULL)
							root->left->parent = newRoot;
						if (root->right != NULL)
							root->right->parent = newRoot;
						if (root == *real_root)
							*real_root = newRoot;
						delete (root);
					}
					else if (root->right != NULL)
					{
						newRoot = getLeftest(root->right);
						newRoot->makeParentChildToMyChild(); // 부모와 자신자식의 라인을 이어준다. (이떄 newRoot 는 반드시 자식이 하나이므로 반드시 연결된다.)

						////////////
						if (newRoot->left != NULL)
							newRoot->left->parent = newRoot->parent;
						if (newRoot->right != NULL)
							newRoot->right->parent = newRoot->parent;
						///////////

						newRoot->left = root->left;
						newRoot->right = root->right;
						newRoot->parent = root->parent;
						if (root->parent != NULL)
							root->parent->childChange(root, newRoot);
						if (root->left != NULL)
							root->left->parent = newRoot;
						if (root->right != NULL)
							root->right->parent = newRoot;
						if (root == *real_root)
							*real_root = newRoot;
						delete (root);
					}
					else // 양쪽 자식 모두 없다. (부모쪽 링크만 없애주면됨. 아래에 아무것도 없다)
					{
						root->makeParentChildToMyChild();
						delete root;
					}
					return ;
				}
				if (cmp(root->ip.first, tk) == false)
					deleteNode(real_root, root->left, tk);
				else if (cmp(root->ip.first, tk))
					deleteNode(real_root, root->right, tk);
			}

			// getter
			node<Key, T, Compare>	*getParent() { return (this->parent); }
			node<Key, T, Compare>	*getLeft() { return (this->left); }
			node<Key, T, Compare>	*getRight() { return (this->right); }

	};

	template <typename Key, typename T, class Compare = ft::less<Key> >
	class saver
	{
		public:
			node<Key, T, Compare>	*root;

			saver(node<Key, T, Compare> *_root = NULL) : root(_root) {}
			~saver() {}
			saver(const saver<Key, T, Compare> &other) : root(other.root) {}
			saver	&operator=(const saver<Key, T, Compare> &other)
			{
				if (this != &other)
					this->root = other.root;
				return (*this);
			}
	};
}

#endif
