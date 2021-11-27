#include "map.hpp"

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

int     main(void)
{
    ft::map<char, int> m;

    m['a']=20;
	m['b']=40;
	m['c']=60;
	m['d']=80;
	m['e']=100;

	m.nodePrint();
	printSize(m);

	std::cout << "=====erase test=====" << std::endl;
	std::cout << "erase 'a'" << std::endl;
	m.erase('a');
	m.nodePrint();
	std::cout << "erase 'b'" << std::endl;
	m.erase('b');
	m.nodePrint();
	std::cout << "erase 'c'" << std::endl;
	m.erase('c');
	m.nodePrint();
	std::cout << "erase 'd'" << std::endl;
	m.erase('d');
	m.nodePrint();
	std::cout << "erase 'e'" << std::endl;
	m.erase('e');
	m.nodePrint();
}
