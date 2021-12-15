/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:38:24 by skim              #+#    #+#             */
/*   Updated: 2021/11/25 19:58:14 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#define RED		true
#define BLACK	false
#define C_RED	"\033[31m"
#define C_NRML	"\033[0m"

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

void	setNil(node *nilParent)
{
	nil->parent = nilParent;
}

void	tree_print(node *_root, std::string indent, bool last);

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

void	insert_fix_up(node *target)
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
			insert_fix_up(grand);
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
		insert_fix_up(newNode);
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
		insert_fix_up(newNode);
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

void	trans(node *target, node *newNode)
{
	if (target->parent != nil)
	{
		if (target->parent->left == target)
			target->parent->left = newNode;
		else
			target->parent->right = newNode;
		newNode->parent = target->parent;
	}
	if (target->left != newNode)
	{
		newNode->left = target->left;
		target->left->parent = newNode;
	}
	if (target->right != newNode)
	{
		newNode->right = target->right;
		target->right->parent = newNode;
	}
}

bool	erase_fix_up_re(node *target, node *parent)
{
	node	*sibling = parent->left == target ? parent->right : parent->left;
	node	*sibling_left = sibling->left;
	node	*sibling_right = sibling->right;

	// case 1
	if (parent->color == RED && sibling->color == BLACK && sibling_left->color == BLACK && sibling_right->color == BLACK)
	{
		parent->color = BLACK;
		sibling->color = RED;
		return (true);
	}
	// case 2, case 3
	else if (sibling->color == BLACK && (sibling_right->color == RED || sibling_left->color == RED))
	{
		if (parent->left == target)
		{
			if (sibling_right->color == RED)
			{
				sibling->color = parent->color;
				parent->color = BLACK;
				sibling_right->color = BLACK;
				rotate_left(parent);
			}
			else
			{
				if (sibling_left->color == RED)
				{
					sibling_left->color = BLACK;
					sibling->color = RED;
					rotate_right(sibling);
				}
			}
			return (true);
		}
		else if (parent->right == target)
		{
			if (sibling_left->color == RED)
			{
				sibling->color = parent->color;
				parent->color = BLACK;
				sibling_left->color = BLACK;
				rotate_right(parent);
			}
			else
			{
				if (sibling_right->color == RED)
				{
					sibling_right->color = BLACK;
					sibling->color = RED;
					rotate_left(sibling);
				}
			}
			return (true);
		}
	}
	return (false);
}

void	erase_fix_up(node *target, node *parent)
{
	node	*sibling = parent->left == target ? parent->right : parent->left;
	node	*sibling_left = sibling->left;
	node	*sibling_right = sibling->right;

	if (erase_fix_up_re(target, parent))
	{
		return ;
	}
	// case 4 (all black)
	else if (!(parent->color || sibling->color || sibling_left->color || sibling_right->color))
	{
		sibling->color = RED;
		erase_fix_up_re(parent, parent->parent);
	}
	// case 5
	else if (sibling->color == RED && parent->color == BLACK && sibling_left->color == BLACK && sibling_right->color == BLACK)
	{
		parent->color = RED;
		sibling->color = BLACK;
		if (parent->left == target)
			rotate_left(parent);
		else
			rotate_right(parent);
		erase_fix_up_re(target, parent);
	}
}

void	erase(node *target)
{
	node	*newNode;
	node	*child;

	if (target->left != nil)
	{
		newNode = target->left;
		while (newNode->right != nil)
			newNode = newNode->right;
		if (newNode->left == nil)
			setNil(newNode);
		child = newNode->left;
		if (newNode->color == BLACK && newNode->left->color == RED)
		{
			newNode->left->color = BLACK;
			trans(target, newNode);
			delete target;
			size--;
		}
		else if (newNode->color == BLACK && child->color == BLACK)
		{
			trans(target, newNode);
			delete target;
			size--;
			erase_fix_up(child, child->parent);
		}
	}
	else if (target->right != nil)
	{
		newNode = target->right;
		while (newNode->left != nil)
			newNode = newNode->left;
		if (newNode->right == nil)
			setNil(newNode);
		child = newNode->right;
		if (newNode->color == BLACK && newNode->right->color == RED)
		{
			newNode->right->color = BLACK;
			trans(target, newNode);
			delete target;
			size--;
		}
		else if (newNode->color == BLACK && child->color == BLACK)
		{
			trans(target, newNode);
			delete target;
			size--;
			erase_fix_up(child, child->parent);
		}
	}
	else
	{
		newNode = target->right;
		trans(target, newNode);
		if (target->color == BLACK)
			erase_fix_up(newNode->left, newNode);
		delete target;
		size--;
	}
}

// void	node_print(node *target)
// {
// 	if (target->color == RED)
// 		std::cout << C_RED << target->value;
// 	else
// 		std::cout << C_NRML << target->value;
// }

// void	tab_print(int num)
// {
// 	for (int i = 0; i < num; i++)
// 		std::cout << '\t';
// }

// int		tree_left(node *target)
// {
// 	int	i = 0;

// 	while (target != nil)
// 	{
// 		i++;
// 		target = target->left;
// 	}
// 	return (i);
// }

// void	tree_print(node *target)
// {
// 	if (target == root)
// 	{
// 		tab_print(tree_left(target));
// 		node_print(target);
// 	}
// 	std::cout << '\n';

// 	if (target->left != nil)
// 	{
// 		tab_print(tree_left(target->left) );
// 		std::cout << "  /";
// 	}
// 	if (target->right != nil)
// 	{
// 		tab_print(tree_left(target->right) + 1);
// 		std::cout << '\\';
// 	}
// 	std::cout << '\n';
// 	if (target->left != nil)
// 	{
// 		tab_print(tree_left(target->left));
// 		node_print(target->left);
// 	}
// 	if (target->right != nil)
// 	{
// 		tab_print(tree_left(target->right) + 1);
// 		node_print(target->right);
// 	}
// 	if (target->left != nil)
// 		tree_print(target->left);
// 	if (target->right != nil)
// 		tree_print(target->right);
// }

void	tree_print(node *_root, std::string indent, bool last)
   {
       // print the tree structure on the screen
       if (_root != nil)
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
           std::cout << _root->value << "(" << sColor << ")" << std::endl;
           tree_print(_root->left, indent, false);
           tree_print(_root->right, indent, true);
       }
   }


int		main(void)
{
	node *newNode[100];

	nil->parent = NULL;
	nil->left = NULL;
	nil->right = NULL;
	nil->color = BLACK;

	for (int i = 0; i < 15; i++)
	{
		newNode[i] = new node();
		newNode[i]->value = i;
		insert(root, newNode[i]);
	}
	tree_print(root, " ", true);

	// delete
	for (int i = 5; i < 10; i++)
	{
		std::cout << "deletion : " << newNode[i]->value << std::endl;
		erase(newNode[i]);
		tree_print(root, " ", true);
	}
	// std::cout << "deletion : " << newNode[6]->value << std::endl;
	// erase(newNode[6]);
	// tree_print(root, " ", true);
}
