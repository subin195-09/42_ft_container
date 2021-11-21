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
node	*nil = new node();
size_t	size = 0;

void	rotate_left(node *target)
{
	node	*newRoot;

	newRoot = target->right;
	// 새로 root가 될 node의 왼쪽 자식을 target의 오른쫀 자식으로 바꿈
	target->right = newRoot->left;
	// 리프노드가 아니라면 부모를 바꿔준다.
	if (newRoot->left != nil)
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
	if (newRoot->right != nil)
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

	if (uncle != nil && uncle->color == RED)
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
			grand->color = RED;
			if (target == parent->right && parent == grand->left)
			{
				target->color = BLACK;
				rotate_left(parent);
			}
			else
				parent->color = BLACK;
			rotate_right(grand);
		}
		else
		{
			grand->color = RED;
			if (target == parent->left && parent == grand->right)
			{
				target->color = BLACK;
				rotate_right(parent);
			}
			else
				parent->color = BLACK;
			rotate_left(grand);
		}
		grand->color = RED;
	}
}

void	insert_left(node *_root, node *newNode)
{
	_root->left = newNode;
	newNode->parent = _root;
	newNode->left = nil;
	newNode->right = nil;
	newNode->color = RED;
	size++;
	if (newNode->parent->color == RED)
		fix_up(newNode);
}

void	insert_right(node *_root, node *newNode)
{
	_root->right = newNode;
	newNode->parent = _root;
	newNode->left = nil;
	newNode->right = nil;
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
		newNode->parent = nil;
		newNode->left = nil;
		newNode->right = nil;
		size++;
	}
	else
	{
		if (_root->value > newNode->value)
		{
			if (_root->left != nil)
				insert(_root->left, newNode);
			else
				insert_left(_root, newNode);
		}
		else
		{
			if (_root->right != nil)
				insert(_root->right, newNode);
			else
				insert_right(_root, newNode);
		}
	}
}

#define C_RED  "\033[31m"
#define C_NRML "\033[0m"


void	node_print(node *target)
{
	if (target->color == RED)
		std::cout << C_RED << target->value;
	else
		std::cout << C_NRML << target->value;
}

void	tab_print(int num)
{
	for (int i = 0; i < num; i++)
		std::cout << '\t';
}

int		tree_left(node *target)
{
	int	i = 0;

	while (target != nil)
	{
		i++;
		target = target->left;
	}
	return (i);
}

void	tree_print(node *target)
{
	if (target == root)
	{
		tab_print(tree_left(target));
		node_print(target);
	}
	std::cout << '\n';

	if (target->left != nil)
	{
		tab_print(tree_left(target->left) );
		std::cout << "  /";
	}
	if (target->right != nil)
	{
		tab_print(tree_left(target->right) + 1);
		std::cout << '\\';
	}
	std::cout << '\n';
	if (target->left != nil)
	{
		tab_print(tree_left(target->left));
		node_print(target->left);
	}
	if (target->right != nil)
	{
		tab_print(tree_left(target->right) + 1);
		node_print(target->right);
	}
	if (target->left != nil)
		tree_print(target->left);
	if (target->right != nil)
		tree_print(target->right);
}

int		main(void)
{
	node *newNode = new node();
	node *newNode2 = new node();
	node *newNode3 = new node();
	node *newNode4 = new node();
	node *newNode5 = new node();
	node *newNode6 = new node();

	nil->parent = NULL;
	nil->left = NULL;
	nil->right = NULL;

	newNode->value = 16;
	newNode2->value = 15;
	newNode3->value = 12;
	newNode4->value = 13;
	newNode5->value = 14;
	newNode6->value = 11;
	
	// insert
	insert(root, newNode);
	insert(root, newNode2);
	insert(root, newNode3);
	insert(root, newNode4);
	insert(root, newNode5);
	insert(root, newNode6);

	tree_print(root);
	// delete
}
