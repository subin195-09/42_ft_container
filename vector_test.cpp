/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:54:49 by skim              #+#    #+#             */
/*   Updated: 2021/10/31 17:34:37 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};
#define COUNT (MAX_RAM / ((int)sizeof(Buffer) * 8))

int		main(void)
{
	std::vector<int>	vec;
	ft::vector<int>		ft_vec;

	vec.push_back(1);
	ft_vec.push_back(1);

	std::cout << *(vec.begin()) << std::endl;

	std::vector<int>::iterator iter;
	ft::vector<int>::iterator ft_iter;

	for (int i = 0; i < 10; i++)
	{
		vec.push_back(i);
		ft_vec.push_back(i);
	}

	for (iter = vec.begin(); iter != vec.end(); iter++)
		std::cout << *iter << " ";
	std::cout << std::endl;

	for (ft_iter = ft_vec.begin(); ft_iter != ft_vec.end(); ft_iter++)
		std::cout << *ft_iter << " ";
	std::cout << std::endl;

	/** intra_tester **/
	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::vector<Buffer> vector_buffer;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);
	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		//NORMAL ! :P
	}
}
