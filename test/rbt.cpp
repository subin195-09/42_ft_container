/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:38:24 by skim              #+#    #+#             */
/*   Updated: 2021/11/16 20:42:16 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#define RED		true
#define BLACK	false

struct node {
	node	*parent;
	node	*left;
	node	*right;
	int		value;
	bool	color;
};

node	*root = NULL;
size_t	size = 0;

void	rotate_left(node *target)
{
	node	*newRoot;

	newRoot = target->right;
	// 새로 root가 될 node의 왼쪽 자식을 target의 오른쫀 자식으로 바꿈
	target->right = newRoot->left;
	// 리프노드가 아니라면 부모를 바꿔준다.
	if (newRoot->left)
		newRoot->left->parent = target;
	newRoot->parent = target->parent;

	if (target == root)
		root = newRoot;
	// target이 target의 부모의 기준으로 왼쪽 방향으로 붙어있다면
	if (target == target->parent->left)
		target->parent->left = newRoot;
	else // target이 target의 부모의 기준으로 오른쪽 방향으로 붙어있다면
		target->parent->right = newRoot;
	target->parent = newRoot;
	newRoot->left = target;
}

void	rotate_right(node *target)
{
	node	*newRoot;

	newRoot = target->left;
	target->left = newRoot->right;
	if (newRoot->right)
		newRoot->right->parent = target;
	newRoot->parent = target->parent;
	if (target == root)
		root = newRoot;
	if (target == target->parent->left)
		target->parent->left = newRoot;
	else
		target->parent->right = newRoot;
	target->parent = newRoot;
	newRoot->right = target;
}

void	fix_up(node *target)
{
	node	*parent = target->parent;
	node	*grand = parent->parent;
	node	*uncle = grand->left == parent ? grand->right : grand->left;

	if (uncle && uncle->color == RED)
	{
		parent->color = BLACK;
		uncle->color = BLACK;
		grand->color = grand == root ? BLACK : RED;
		if (grand->color == RED && grand->parent->color == RED)
			fix_up(grand->parent);
	}
	else
	{
		if (parent == grand->left)
		{
			if (target == parent->right && parent == grand->left)
			{
				target->color = BLACK;
				rotate_right(parent);
			}
			else
				parent->color = BLACK;
			rotate_left(grand);
		}
		else
		{
			if (target == parent->left && parent == grand->right)
			{
				target->color = BLACK;
				rotate_left(parent);
			}
			else
				parent->color = BLACK;
			rotate_right(grand);
		}
		grand->color = RED;
	}
}

void	insert_left(node *_root, node *newNode)
{
	_root->left = newNode;
	newNode->parent = _root;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->color = RED;
	size++;
	if (newNode->parent->color == RED)
		fix_up(newNode);
}

void	insert_right(node *_root, node *newNode)
{
	_root->right = newNode;
	newNode->parent = _root;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->color = RED;
	size++;
	if (newNode->parent->color == RED)
		fix_up(newNode);
}


void	insert(node *_root, node *newNode)
{
	if (size == 0)
	{
		root = newNode;
		newNode->color = BLACK;
		newNode->parent = NULL;
		newNode->left = NULL;
		newNode->right = NULL;
		size++;
	}
	else
	{
		if (_root->value > newNode->value)
		{
			if (_root->left != NULL)
				insert(_root->left, newNode);
			else
				insert_left(_root, newNode);
		}
		else
		{
			if (_root->right != NULL)
				insert(_root->right, newNode);
			else
				insert_right(_root, newNode);
		}
	}
}


int		main(void)
{
	node *root = new node();

	// insert

	// delete
}
