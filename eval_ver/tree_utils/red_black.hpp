/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:24:48 by skim              #+#    #+#             */
/*   Updated: 2021/11/29 18:57:06 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_HPP
# define RED_BLACK_HPP

#include "pair.hpp"
#include "../utils/utils.hpp"

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

			void	trans(node<Key, T, Compare> *target, node<Key, T, Compare> *newNode)
			{
				if (newNode->parent != NULL)
				{
					if (newNode->parent->left == newNode)
					{
						if (newNode->left != NULL)
						{
							newNode->parent->left = newNode->left;
							newNode->left->parent = newNode->parent;
						}
						else if (newNode->right != NULL)
						{
							newNode->parent->left = newNode->right;
							newNode->right->parent = newNode->parent;
						}
						else
							newNode->parent->left = NULL;
					}
					else
					{
						if (newNode->left != NULL)
						{
							newNode->parent->right = newNode->left;
							newNode->left->parent = newNode->parent;
						}
						else if (newNode->right != NULL)
						{
							newNode->parent->right = newNode->right;
							newNode->right->parent = newNode->parent;
						}
						else
							newNode->parent->right = NULL;
					}
				}
				if (target->parent != NULL)
				{
					if (target->parent->left == target)
						target->parent->left = newNode;
					else
						target->parent->right = newNode;
					newNode->parent = target->parent;
				}
				else
					newNode->parent = NULL;
				if (target->left != NULL && target->left != newNode)
				{
					newNode->left = target->left;
					target->left->parent = newNode;
				}
				if (target->right != NULL && target->right != newNode)
				{
					newNode->right = target->right;
					target->right->parent = newNode;
				}
			}

			// setNil
			void	setNil(node<Key, T, Compare> *nil, node<Key, T, Compare> *nilParent)
			{
				nil->parent = nilParent;
				nil->left = NULL;
				nil->right = NULL;
				nil->color = BLACK;
			}

			// rotation
			void	rotateLeft(node<Key, T, Compare> *target)
			{
				node<Key, T, Compare>	*newNode;
				node<Key, T, Compare>	*root = getRoot(target);

				newNode = target->right;
				target->right = newNode->left;
				if (newNode->left != NULL)
					newNode->left->parent = target;
				newNode->parent = target->parent;
				if (target == root)
					root = newNode;
				if (target->parent)
				{
					if (target == target->parent->left)
						target->parent->left = newNode;
					else
						target->parent->right = newNode;
				}
				target->parent = newNode;
				newNode->left = target;
			}

			void	rotateRight(node<Key, T, Compare> *target)
			{
				node<Key, T, Compare>	*newNode;
				node<Key, T, Compare>	*root = getRoot(target);

				newNode = target->left;
				target->left = newNode->right;
				if (newNode->right != NULL)
					newNode->right->parent = target;
				newNode->parent = target->parent;
				if (target == root)
					root = newNode;
				if (target->parent)
				{
					if (target == target->parent->left)
						target->parent->left = newNode;
					else
						target->parent->right = newNode;
				}
				target->parent = newNode;
				newNode->right = target;
			}

		public:
			pair<const Key, T>	ip;

			node() : parent(NULL), left(NULL), right(NULL), color(BLACK) {}
			node(Key first, T second = T()) :  parent(NULL), left(NULL), right(NULL) , color(BLACK),ip(first, second) {}
			node(const pair<Key, T> &p) : parent(NULL), left(NULL), right(NULL) ,ip(p), color(BLACK) {}

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

			void					insertFixup(node<Key, T, Compare> *target)
			{
				if (!(target->color == RED && target->parent->color == RED))
					return ;
				node<Key, T, Compare>	*_parent = target->parent;
				node<Key, T, Compare>	*_grand = _parent->parent;
				node<Key, T, Compare>	*_uncle = _grand->left == _parent ? _grand->right : _grand->left;
				node<Key, T, Compare>	*root = getRoot(target);

				if (_uncle != NULL && _uncle->color == RED)
				{
					_parent->color = BLACK;
					_uncle->color = BLACK;
					_grand->color = _grand == root ? BLACK : RED;
					if (_grand->color == RED && _grand->parent->color == RED)
						insertFixup(_grand);
				}
				else
				{
					if (_parent == _grand->left)
					{
						_grand->color = RED;
						if (target == _parent->right && _parent == _grand->left)
						{
							target->color = BLACK;
							rotateLeft(_parent);
						}
						else
							_parent->color = BLACK;
						rotateRight(_grand);
					}
					else
					{
						_grand->color = RED;
						if (target == _parent->left && _parent == _grand->right)
						{
							target->color = BLACK;
							rotateRight(_parent);
						}
						else
							_parent->color = BLACK;
						rotateLeft(_grand);
					}
					_grand->color = RED;
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
					if (root->right == NULL)
					{
						child = new node<Key, T, Compare>(k, v);
						root->right = child;
						child->parent = root;
						child->left = NULL;
						child->right = NULL;
						child->color = RED;
						insertFixup(child);
						return (child);
					}
					return (mergeInsert(root->right, k, v));
				}
				else
				{
					if (root->left == NULL)
					{
						child = new node<Key, T, Compare>(k, v);
						root->left = child;
						child->parent = root;
						child->left = NULL;
						child->right = NULL;
						child->color = RED;
						insertFixup(child);
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
					{
						if (root->parent->ip.first < root->ip.first)
							return (NULL);
						return (root->parent);
					}
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
				std::cout << root->ip.first << ", " << key << std::endl;
				tree_print(getRoot(root), "", true);
				if (cmp(root->ip.first, key)) // first < key
				{
					if (root->right == NULL)
					{
						if (root->parent->ip.first < root->ip.first)
							return (NULL);
						return (NULL);
					}
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

			bool					erase_fix_up_re(node<Key, T, Compare> *target, node<Key, T, Compare> *_parent)
			{
				node<Key, T, Compare>	*nil = new node<Key, T, Compare>();
				node<Key, T, Compare>	*sibling = _parent->left == target ? _parent->right : _parent->left;
				node<Key, T, Compare>	*sibling_left = sibling->left == NULL ? nil : sibling->left;
				node<Key, T, Compare>	*sibling_right = sibling->right == NULL ? nil : sibling->right;

				// case 1
				if (_parent->color == RED && sibling->color == BLACK && sibling_left->color == BLACK && sibling_right->color == BLACK)
				{
					_parent->color = BLACK;
					sibling->color = RED;
					return (true);
				}
				// case 2, case 3
				else if (sibling->color == BLACK && (sibling_right->color == RED || sibling_left->color == RED))
				{
					if (_parent->left == target)
					{
						if (sibling_right->color == RED) // case 2
						{
							sibling->color = _parent->color;
							_parent->color = BLACK;
							sibling_right->color = BLACK;
							rotateLeft(_parent);
						}
						else // case 3
						{
							if (sibling_left->color == RED)
							{
								sibling_left->color = BLACK;
								sibling->color = RED;
								rotateRight(sibling);
								_parent->color = BLACK;
								sibling->color = BLACK;
								rotateLeft(_parent);
							}
						}
						return (true);
					}
					else if (_parent->right == target)
					{
						if (sibling_left->color == RED) // case 2
						{
							sibling->color = _parent->color;
							_parent->color = BLACK;
							sibling_left->color = BLACK;
							rotateRight(_parent);
						}
						else // case 3
						{
							if (sibling_right->color == RED)
							{
								sibling_right->color = BLACK;
								sibling->color = RED;
								rotateLeft(sibling);
							}
						}
						return (true);
					}
				}
				return (false);
			}

			void					erase_fix_up(node<Key, T, Compare> *target, node<Key, T, Compare> *_parent)
			{
				node<Key, T, Compare>	*nil = new node<Key, T, Compare>();
				node<Key, T, Compare>	*sibling = _parent->left == target ? _parent->right : _parent->left;
				node<Key, T, Compare>	*sibling_left = sibling->left == NULL ? nil : sibling->left;
				node<Key, T, Compare>	*sibling_right = sibling->right == NULL ? nil : sibling->right;

				if (erase_fix_up_re(target, _parent))
					return ;
				// case 4 (all black)
				else if (!(_parent->color || sibling->color || sibling_left->color || sibling_right->color))
				{
					sibling->color = RED;
					if (_parent->parent != NULL)
						erase_fix_up(_parent, _parent->parent);
				}
				// case 5
				else if (sibling->color == RED && _parent->color == BLACK && sibling_left->color == BLACK && sibling_right->color == BLACK)
				{
					_parent->color = RED;
					sibling->color = BLACK;
					if (_parent->left == target)
						rotateLeft(_parent);
					else
						rotateRight(_parent);
					erase_fix_up_re(target, _parent);
				}
			}

			void					deleteNode(node<Key, T, Compare> **real_root, node<Key, T, Compare> *target, const Key& key)
			{
				node<Key, T, Compare>	*newNode;
				node<Key, T, Compare>	*nil = new node<Key, T, Compare>();
				bool					checker = false;

				if (target->ip.first == key)
				{
					if (target->left != NULL)
					{
						newNode = getRightest(target->left);
						if (newNode->left == NULL)
						{
							setNil(nil, newNode);
							newNode->left = nil;
						}
						if (newNode->color == BLACK)
						{
							checker = newNode->left->color == BLACK ? true : false;
							if (newNode->left->color == RED)
								newNode->left->color = BLACK;
						}
						else
							newNode->color = target->color;
						trans(target, newNode);
						delete target;
						if (checker)
							erase_fix_up(newNode->left, newNode);
					}
					else if (target->right != NULL)
					{
						newNode = getLeftest(target->right);
						if (newNode->right == NULL)
						{
							setNil(nil, newNode);
							newNode->right = nil;
						}
						if (newNode->color == BLACK)
						{
							checker = newNode->right->color == BLACK ? true : false;
							if (newNode->right->color == RED)
								newNode->right->color = BLACK;
						}
						else
							newNode->color = target->color;
						trans(target, newNode);
						delete target;
						if (checker)
							erase_fix_up(newNode->right, newNode);
					}
					else
					{
						newNode = nil;
						target->left = nil;
						setNil(nil, target);
						trans(target, nil);
						if (target->color == BLACK)
							erase_fix_up(nil, nil->parent);
					}
					*real_root = getRoot(newNode);
					if (nil->parent != NULL)
					{
						if (nil->parent->left == nil)
							nil->parent->left = NULL;
						else if (nil->parent->right == nil)
							nil->parent->right = NULL;
					}
					delete nil;
					nil = NULL;
					return ;
				}
				if (cmp(target->ip.first, key) == false)
					deleteNode(real_root, target->left, key);
				else if (cmp(target->ip.first, key))
					deleteNode(real_root, target->right, key);
			}

			// getter
			node<Key, T, Compare>	*getParent() { return (this->parent); }
			node<Key, T, Compare>	*getLeft() { return (this->left); }
			node<Key, T, Compare>	*getRight() { return (this->right); }

			void					tree_print(node *_root, std::string indent, bool last)
			{
				// print the tree structure on the screen
				if (_root != NULL)
				{
					std::cout << indent;
					if (last)
					{
						std::cout << "R----";
						indent += "     ";
					}
					else
					{
						std::cout << "L----";
						indent += "|    ";
					}
					std::string sColor = (_root->color == RED) ? "RED" : "BLACK";
					std::cout << _root->ip.first << "(" << sColor << ")" << std::endl;
					tree_print(_root->left, indent, false);
					tree_print(_root->right, indent, true);
				}
			}

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
