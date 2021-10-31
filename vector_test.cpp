/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 15:54:49 by skim              #+#    #+#             */
/*   Updated: 2021/10/31 16:39:59 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>

int		main(void)
{
	std::vector<int>	vec;
	ft::vector<int>		ft_vec;

	vec.push_back(1);
	ft_vec.push_back(1);

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
}
