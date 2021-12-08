#include "common.hpp"
#include <map>

#define T1 int

int		main(void)
{
	ft::set<T1> const st;
	ft::set<T1>::iterator it = st.begin(); // <-- no error, actually ! set allows for const_iterator => iterator conversion

	(void)it;
	return (0);
}
