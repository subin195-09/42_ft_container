/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:41:05 by skim              #+#    #+#             */
/*   Updated: 2022/01/25 17:41:54 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include "vector_iterator.hpp"
#include "../utils/template_utils.hpp"
#include "../utils/utils.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		private :
			T		*arr;
			size_t	num_of_element;
			size_t	cap;
			Alloc	_alloc;

			void	expand(unsigned int to_size)
			{
				if (num_of_element >= to_size)
					return ;

				T	*temp = _alloc.allocate(to_size);
				if (num_of_element > 0)
				{
					for (size_t i = 0; i < num_of_element; i++)
						_alloc.construct(temp + i, *(arr + i));
					_alloc.destroy(arr);
					_alloc.deallocate(arr, num_of_element);
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
				_alloc.construct(pos, val);
			}

			void	shift(T *pos, unsigned int shift_size)
			{
				unsigned int	i = getIdxFromPtr(pos);

				if (shift_size + num_of_element >= cap)
					expand(num_of_element + (shift_size * 2));
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

		public :
			typedef ptrdiff_t									difference_type;
			typedef T											value_type;
			typedef T											*pointer;
			typedef T											&reference;

			typedef Alloc										allocator_type;
			typedef size_t										size_type;
			typedef const T										&const_reference;
			typedef const T										*const_pointer;

			typedef vectorIterator<T>							iterator;
			typedef vectorConstIterator<T>						const_iterator;
			typedef vectorReverseIterator<T>					reverse_iterator;
			typedef vectorReverseConstIterator<T>				const_reverse_iterator;

			explicit vector (const allocator_type& alloc = allocator_type()) : arr(NULL), num_of_element(0), cap(0)
			{
				(void)alloc;
				expand(10);
			}

			explicit vector (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : arr(NULL), num_of_element(0), cap(0)
			{
				(void)alloc;
				expand(10);
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			template <class InputIterator>
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type dummy = 0) : arr(NULL), num_of_element(0), cap(0)
			{
				(void)alloc;
				dummy = 0;
				expand(10);
				for (InputIterator it = first; it != last; it++)
					push_back(*it);
			}

			vector (const vector &x)
			: arr(NULL), num_of_element(0), cap(0)
			{
				expand(10);
				insert(begin(), x.begin(), x.end());
			}

			vector<T>	&operator= (const vector &x)
			{
				clear();
				insert(begin(), x.begin(), x.end());
				return (*this);
			}

			~vector()
			{
				_alloc.destroy(arr);
				_alloc.deallocate(arr, cap);
			}

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
				return (reverse_iterator(arr + num_of_element - 1));
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
				return (_alloc.max_size());
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
					throw std::out_of_range("vector::at");
			}

			const_reference	at(size_type n) const
			{
				if (n < num_of_element)
					return (arr[n]);
				else
					throw std::out_of_range("vector::at");
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
				T		*pos_ptr = position.getPtr();
				size_t	pos_ptr_idx = this->getIdxFromPtr(pos_ptr);
				shift(pos_ptr, 1);
				setValue(arr + pos_ptr_idx, val);
				num_of_element++;
				return (arr + pos_ptr_idx);
			}

			void		insert(iterator position, size_type n, const value_type &val)
			{
				T		*pos_ptr = position.getPtr();
				size_t	pos_ptr_idx = this->getIdxFromPtr(pos_ptr);
				shift(pos_ptr, n);
				for (unsigned int i = 0; i < n; i++)
					setValue(arr + pos_ptr_idx + i, val);
				num_of_element += n;
			}

			template <class InputIterator>
			void		insert \
			(iterator position, InputIterator first, InputIterator last, \
			typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type dummy = 0)
			{
				dummy = 0;
				unsigned int	len = 0;
				T				*pos_ptr = position.getPtr();
				size_t			pos_ptr_idx = this->getIdxFromPtr(pos_ptr);

				for (InputIterator it = first; it != last; it++)
					len++;
				shift(pos_ptr, len);

				unsigned int i = 0;
				for (InputIterator it = first; it != last; it++)
					setValue(arr + pos_ptr_idx + i++, *it);
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
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool 	operator!= (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator< (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
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
