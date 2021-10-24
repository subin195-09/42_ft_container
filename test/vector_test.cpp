/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 17:08:35 by skim              #+#    #+#             */
/*   Updated: 2021/10/24 18:09:44 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>

int		main(void)
{
	std::vector<int>	vec;

	vec.push_back(1);

	std::vector<int>::iterator	it = vec.begin();

	for(int i = 0; i < 100; i++)
		vec.push_back(i);

	it = vec.begin();

	while (it != vec.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
}
