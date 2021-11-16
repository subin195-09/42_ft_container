/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:38:24 by skim              #+#    #+#             */
/*   Updated: 2021/11/16 17:41:41 by skim             ###   ########.fr       */
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
	target->right = newRoot->left;
	// 새로 root가 될 node의 왼쪽 자식을 target의 오른쫀 자식으로 바꿈
	if (newRoot->left)
		newRoot->left->parent = target;
	newRoot->parent = target->parent;

	if (target->parent == root)
		root = newRoot;
	// target이 target의 부모의 기준으로 왼쪽 방향으로 붙어있다면
	if (target == target->parent->left)
		target->parent->left = newRoot;
	else // target이 target의 부모의 기준으로 오른쪽 방향으로 붙어있다면
		target->parent->right = newRoot;
	target->parent = newRoot;
	newRoot->left = target;
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
	{
		if (_root->parent->left && _root->parent->left->color == RED)
			recoloring(_root, _root->parent->left, _root->parent);
		else
			restructuring(newNode, _root, _root->parent);
	}
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
	{
		if (_root->parent->right && _root->parent->right->color == RED)
			recoloring(_root, _root->parent->right, _root->parent);
		else
			restructuring(newNode, _root, _root->parent);
	}
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
