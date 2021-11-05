/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:23:40 by skim              #+#    #+#             */
/*   Updated: 2021/11/05 19:37:48 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include "../vector/vector.hpp"
# include <stack>

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
		protected:
			container_type		c;
		public:
			explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}
			stack(const stack &other) : c(other.c) {}
			// copy constructor에 대해 좀 더 연구해 볼 것
			stack &operator=(const stack &other)
			{
				c = other.c;
				return (*this);
			}
			~stack() {}

			bool				empty() const { return c.empty(); }
			size_type			size() const { return c.size(); }
			value_type			&top() { return c.back(); }
			const value_type	&top() const { return c.back(); }
			void				push(const value_type &val) { c.push_back(val); }
			void				pop() { c.pop_back(); }

			template <class TT, class CC>
			friend bool	operator==(const stack &lhs, const stack &rhs);

			template <class TT, class CC>
			friend bool	operator!=(const stack &lhs, const stack &rhs);

			template <class TT, class CC>
			friend bool	operator<(const stack &lhs, const stack &rhs);

			template <class TT, class CC>
			friend bool	operator<=(const stack &lhs, const stack &rhs);

			template <class TT, class CC>
			friend bool	operator>(const stack &lhs, const stack &rhs);

			template <class TT, class CC>
			friend bool	operator>=(const stack &lhs, const stack &rhs);
	};
	template <class T, class Container>
 	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
  	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs.c == rhs.c));
	}

	template <class T, class Container>
 	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
  	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c || lhs.c == rhs.c);
	}

	template <class T, class Container>
  	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs.c <= rhs.c));
	}

	template <class T, class Container>
  	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs.c < rhs.c));
	}
}

#endif
