/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:29:45 by skim              #+#    #+#             */
/*   Updated: 2021/10/24 18:20:08 by skim             ###   ########.fr       */
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

	skim_alloc.construct(arr_int, -42); // array의 맨 첫부분을 -42로 초기화
	print_arr(arr_int, 5);

	skim_alloc.destroy(arr_int); // 메모리의 할당은 유지한 채 객체만 삭제
	print_arr(arr_int, 5);

	skim_alloc.deallocate(arr_int, 5); // 메모리 할당 제거
	print_arr(arr_int, 5);

	// destroy만 해고 deallocate를 하지 않으면 memory leak이 발생할 수 있음

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
