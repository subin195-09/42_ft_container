#include "set.hpp"
#include <iostream>

int		main(void)
{
	std::set<int> skim_set;

	skim_set.insert(1);
	skim_set.insert(2);
	skim_set.insert(3);
	skim_set.insert(4);

	std::set<int>::iterator it = skim_set.begin();
	for(; it != skim_set.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "upper bound test" << std::endl;
	std::cout << *(skim_set.upper_bound(3)) << std::endl;
}
