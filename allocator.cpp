/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:29:45 by skim              #+#    #+#             */
/*   Updated: 2021/10/24 17:06:49 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>

class Test
{
	public:
		unsigned int	n;
		Test() {};
		Test(unsigned int n) { this->n = n; }
		~Test() { std::cout << "Call Destructor" << std::endl; }
};

void	print_arr(int *arr, int size)
{
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

int		main(void)
{
	std::allocator<int> skim_alloc;
	int					*arr_int;

	arr_int = skim_alloc.allocate(5);

	print_arr(arr_int, 5);

	skim_alloc.construct(arr_int, -42);
	print_arr(arr_int, 5);

	skim_alloc.destroy(arr_int);
	print_arr(arr_int, 5);

	skim_alloc.deallocate(arr_int, 5);
	print_arr(arr_int, 5);

	std::cout << "======class test=======" << std::endl;

	std::allocator<Test> class_alloc;

	Test	t(42);
	Test	*test;

	test = class_alloc.allocate(1);
	std::cout << test->n << std::endl;

	class_alloc.construct(test, t);
	std::cout << test->n << std::endl;

	class_alloc.destroy(test);
	std::cout << test->n << std::endl;

	class_alloc.deallocate(test, 1);
	std::cout << test->n << std::endl;

	return (0);
}
