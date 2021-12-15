/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bound.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:38:38 by skim              #+#    #+#             */
/*   Updated: 2021/11/12 17:35:53 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>

int		main(void)
{
	std::map<char, int>	m;
	m['a'] = 11;
	m['b'] = 12;
	m['c'] = 13;
	m['d'] = 14;
	m['e'] = 15;
	std::map<char, int>::iterator it;
	std::pair<std::map<char, int>::iterator, bool> ret = m.insert(std::pair<char, int>('a', 13));
	std::cout << (*(ret.first)).second << std::endl;

	for (it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " => " << it->second << std::endl;
	// std::cout << m.lower_bound('c')->first << std::endl;
	// std::cout << m.upper_bound('c')->first << std::endl;
}
