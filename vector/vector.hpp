/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:41:05 by skim              #+#    #+#             */
/*   Updated: 2021/11/05 02:21:47 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include "vector_iterator.hpp"
#include "../template_util.hpp"
// #include <vector>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		private :
			T		*arr;
			size_t	num_of_element;
			size_t	cap;

			void	expand(unsigned int to_size)
			{
				if (num_of_element >= to_size)
					return ;

				Alloc alloc;

				T	*temp = alloc.allocate(to_size);
				if (num_of_element > 0)
				{
					for (size_t i = 0; i < num_of_element; i++)
						alloc.construct(temp + i, *(arr + i));
					alloc.destroy(arr);
					alloc.deallocate(arr, num_of_element);
				}
				cap = to_size;
				arr = temp;
			}

			unsigned int	getIdxFromPtr(T *target)
			{
				return (target - arr);
			}

			void	setValue(T *pos, const T &val)
			{
				Alloc alloc;
				alloc.construct(pos, val);
			}

			void	shift(T *pos, unsigned int shift_size)
			{
				Alloc			alloc;
				unsigned int	i = getIdxFromPtr(pos);

				if (shift_size + num_of_element >= cap)
					expand((num_of_element + shift_size) * 2);
				for (unsigned int j = 0; j < num_of_element - i; j++)
					setValue(arr + num_of_element - 1 + shift_size - j, *(arr + num_of_element - 1 - j));
			}

			void	shift_back(T *pos, unsigned int shift_size)
			{
				unsigned int	idx = getIdxFromPtr(pos);

				for (unsigned int i = idx; i < num_of_element - shift_size; i++)
					setValue(arr + i, *(arr + i + shift_size));
				num_of_element -= shift_size;
			}

			class	OutOfRangeException : public std::exception
			{
				virtual const char	*what() const throw()
				{
					return ("Out Of Range");
				}
			};

		public :
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef size_t										size_type;
			typedef ptrdiff_t									difference_type;
			typedef T											&reference;
			typedef const T										&const_reference;
			typedef T											*pointer;
			typedef const T										*const_pointer;
			typedef vectorIterator<T>							iterator;
			typedef vectorConstIterator<T>						const_iterator;
			typedef vectorReverseIterator<T>					reverse_iterator;
			typedef vectorReverseConstIterator<T>				const_reverse_iterator;

			/** constructor **/
			// default constructor
			// explicit : 자동 형변환을 막기 위함
			explicit vector (const allocator_type& alloc = allocator_type()) : arr(NULL), num_of_element(0), cap(0)
			{
				(void)alloc;
				// cap = 42, arr를 42개를 할당한 것으로 초기화
				expand(42);
			}

			// fill constructor
			explicit vector (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : arr(NULL), num_of_element(0), cap(0)
			{
				(void)alloc;
				expand(42);
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			// range constructor
			// iterator를 구현 후 좀 더 공부해 볼 것
			// 참고 자료: https://github.com/pearan2/ft_containers/wiki/4.-template-%ED%95%A8%EC%88%98-(%ED%81%B4%EB%A0%88%EC%8A%A4%EB%82%B4%EB%B6%80%EC%97%90%EC%84%9C%EC%9D%98-%EB%A9%94%EC%86%8C%EB%93%9C)-%EC%97%90%EC%84%9C-%EC%96%B4%EB%8A%90%ED%95%A8%EC%88%98%EB%A5%BC-%EC%8B%A4%ED%96%89%ED%95%B4%EC%95%BC-%ED%95%A0%EC%A7%80-%EB%AA%A8%ED%98%B8%ED%95%A0%EB%95%8C
			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type dummy = 0) : arr(NULL), num_of_element(0), cap(0)
			{
				(void)alloc;
				dummy = 0;
				expand(42);
				for (InputIterator it = first; it != last; it++)
					push_back(*it);
			}

			// copy constructor
			vector (const vector &x)
			: arr(NULL), num_of_element(0), cap(0)
			{
				expand(42);
				insert(begin(), x.begin(), x.end());
			}

			/** = assign operator **/
			vector<T>	&operator= (const vector &x)
			{
				clear();
				insert(begin(), x.begin(), x.end());
				return (*this);
			}

			/** destructor **/
			~vector()
			{
				Alloc alloc;

				alloc.destroy(arr);
				alloc.deallocate(arr, cap);
			}

			/** iterator **/
			iterator				begin()
			{
				return (iterator(arr));
			}

			const_iterator			begin() const
			{
				return (const_iterator(arr));
			}

			iterator				end()
			{
				return (iterator(arr + num_of_element));
			}

			const_iterator			end() const
			{
				return (const_iterator(arr + num_of_element));
			}

			reverse_iterator		rbegin()
			{
				return (reverse_iterator(arr + num_of_element) - 1);
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(arr + num_of_element) - 1);
			}

			reverse_iterator		rend()
			{
				return (reverse_iterator(arr - 1));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(arr - 1));
			}

			/** cap **/
			size_type	size() const
			{
				return (num_of_element);
			}

			size_type	max_size() const
			{
				return (Alloc().max_size());
			}

			void		resize(size_type n, value_type val = value_type())
			{
				unsigned int	noe = num_of_element;
				if (num_of_element < n)
				{
					for (unsigned int i = 0; i < (n - noe); i++)
						push_back(val);
				}
				else
				{
					for (unsigned int i = 0; i < (noe - n); i++)
						pop_back();
				}
			}

			size_type	capacity() const
			{
				return (cap);
			}

			bool		empty() const
			{
				return (num_of_element == 0);
			}

			void		reserve(size_type n)
			{
				if (num_of_element < n)
					expand(n);
			}

			/** element access **/
			reference		at(size_type n)
			{
				if (n < num_of_element)
					return (arr[n]);
				else
					throw OutOfRangeException();
			}

			const_reference	at(size_type n) const
			{
				if (n < num_of_element)
					return (arr[n]);
				else
					throw OutOfRangeException();
			}

			reference		operator[](size_type n)
			{
				return (at(n));
			}

			const_reference	operator[](size_type n) const
			{
				return (at(n));
			}

			reference		front()
			{
				return (at(0));
			}

			const_reference	front() const
			{
				return (at(0));
			}

			reference		back()
			{
				return (at(num_of_element - 1));
			}

			const_reference	back() const
			{
				return (at(num_of_element - 1));
			}

			/** modifiers **/
			void		push_back(const value_type &val)
			{
				if (num_of_element >= cap)
					expand(cap * 2);
				setValue(arr + num_of_element, val);
				num_of_element++;
			}

			void		pop_back()
			{
				if (num_of_element > 0)
					num_of_element--;
			}

			iterator	insert(iterator position, const value_type &val)
			{
				T	*pos_ptr = position.getPtr();
				shift(pos_ptr, 1);
				setValue(pos_ptr, val);
				num_of_element++;
				return (pos_ptr);
			}

			void		insert(iterator position, size_type n, const value_type &val)
			{
				T	*pos_ptr = position.getPtr();
				shift(pos_ptr, n);
				for (unsigned int i = 0; i < n; i++)
					setValue(pos_ptr + i, val);
				num_of_element += n;
			}

			// range constructor와 함께 공부할 것
			template <class InputIterator>
			void		insert \
			(iterator position, InputIterator first, InputIterator last, \
			typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type dummy = 0)
			{
				dummy = 0;
				unsigned int	len = 0;
				T				*pos_ptr = position.getPtr();

				for (InputIterator it = first; it != last; it++)
					len++;
				shift(pos_ptr, len);

				unsigned int i = 0;
				for (InputIterator it = first; it != last; it++)
					setValue(pos_ptr + i++, *it);
				num_of_element += len;
			}

			void		swap(vector &x)
			{
				T	*temp = this->arr;
				this->arr = x.arr;
				x.arr = temp;

				unsigned int temp_num = this->num_of_element;
				this->num_of_element = x.num_of_element;
				x.num_of_element = temp_num;

				unsigned int temp_cap = this->cap;
				this->cap = x.cap;
				x.cap = temp_cap;
			}

			void		clear()
			{
				num_of_element = 0;
			}

			void		assign(size_type n, const value_type &val)
			{
				clear();
				for (size_type i = 0; i < n; i++)
					setValue(arr + i, val);
				num_of_element += n;
			}

			template <class InputIterator>
			void		assign  \
			(InputIterator first, InputIterator last,\
			typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type dummy = 0)
			{
				dummy = 0;
				clear();
				unsigned int i = 0;
				for (InputIterator it = first; it != last; it++)
					setValue(arr + i++, *it);
				num_of_element += i;
			}

			iterator	erase(iterator position)
			{
				unsigned int	idx = getIdxFromPtr(position.getPtr());

				shift_back(position.getPtr(), 1);
				return (iterator(arr + idx));
			}

			iterator	erase(iterator first, iterator last)
			{
				unsigned int	idx = getIdxFromPtr(first.getPtr());

				unsigned int	i = 0;
				for (iterator it = first; it != last; it++)
					i++;
				shift_back(first.getPtr(), i);
				return (iterator(arr + idx));
			}
	};

	/** assign operators **/
	template <class T, class Alloc>
	bool	operator== (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		// utils.hpp에서 구현해야함
		return (equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool 	operator!= (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator< (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		// utils.hpp에서 구현해야함
		return (lexicographical_less(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<= (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ((lhs == rhs) || (lhs < rhs));
	}

	template <class T, class Alloc>
	bool	operator> (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs <= rhs));
	}

	template <class T, class Alloc>
	bool	operator>= (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ((lhs == rhs) || (lhs > rhs));
	}

	template <class T, class Alloc>
	void	swap(vector<T, Alloc> &lhs, vector<T, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
