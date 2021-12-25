/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:21:43 by skim              #+#    #+#             */
/*   Updated: 2021/12/25 16:43:04 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

namespace ft
{
	template <typename T>
	class vectorIterator;

	template <typename T>
	class vectorConstIterator;

	template <typename T>
	class vectorReverseIterator;

	template <typename T>
	class vectorReverseConstIterator;

	template <typename T>
	class vectorIterator
	{
		private :
			T	*ptr;
		public :
			vectorIterator(T *ptr = NULL) : ptr(ptr) {}
			vectorIterator(const vectorIterator<T> &origin) : ptr(origin.ptr) {}\
			vectorIterator<T> &operator=(const vectorIterator<T> &origin)
			{
				ptr = origin.ptr;
				return (*this);
			}
			~vectorIterator(void) {}

			T	*getPtr() const { return (ptr); }

			T	&operator*(void) const { return (*ptr); }
			T	*operator->(void) const { return (&(this->operator*())); }

			vectorIterator<T>&	operator++(void)
			{
				ptr++;
				return (*this);
			}
			vectorIterator<T>	operator++(int)
			{
				vectorIterator<T> tmp(*this);
				ptr++;
				return (tmp);
			}
			vectorIterator<T>&	operator--(void)
			{
				ptr--;
				return (*this);
			}
			vectorIterator<T>	operator--(int)
			{
				vectorIterator<T> tmp(*this);
				ptr--;
				return (tmp);
			}

			vectorIterator<T>	operator+(unsigned int n) const
			{
				return (vectorIterator<T>(ptr + n));
			}
			int					operator+(const vectorConstIterator<T> target) const
			{
				return (ptr + target.getPtr());
			}
			int					operator+(const vectorIterator<T> target) const
			{
				return (ptr + target.getPtr());
			}
			vectorIterator<T>	operator-(unsigned int n) const
			{
				return (vectorIterator<T>(ptr - n));
			}
			int					operator-(const vectorConstIterator<T> target) const
			{
				return (ptr - target.getPtr());
			}
			int					operator-(const vectorIterator<T> target) const
			{
				return (ptr - target.getPtr());
			}

			vectorIterator<T>	&operator+=(unsigned int n)
			{
				ptr += n;
				return (*this);
			}
			vectorIterator<T>	&operator-=(unsigned int n)
			{
				ptr -= n;
				return (*this);
			}

			T		&operator[](unsigned int n)
			{
				return (*(this->operator+(n)));
			}
			bool	operator==(const vectorConstIterator<T> &target) const
			{
				return (ptr == target.getPtr());
			}
			bool	operator==(const vectorIterator<T> &target) const
			{
				return (ptr == target.getPtr());
			}
			bool	operator!=(const vectorConstIterator<T> &target) const
			{
				return (!(this->operator==(target)));
			}
			bool	operator!=(const vectorIterator<T> &target) const
			{
				return (!(this->operator==(target)));
			}
			bool	operator<(const vectorConstIterator<T> &target) const
			{
				return (ptr < target.getPtr());
			}
			bool	operator<(const vectorIterator<T> &target) const
			{
				return (ptr < target.getPtr());
			}
			bool	operator<=(const vectorConstIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator<(target));
			}
			bool	operator<=(const vectorIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator<(target));
			}
			bool	operator>(const vectorConstIterator<T> &target) const
			{
				return (ptr > target.getPtr());
			}
			bool	operator>(const vectorIterator<T> &target) const
			{
				return (ptr > target.getPtr());
			}
			bool	operator>=(const vectorConstIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator>(target));
			}
			bool	operator>=(const vectorIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator>(target));
			}
	};

	template<typename T>
	vectorIterator<T>	operator+(unsigned int n, vectorIterator<T> &target)
	{
		return (&(*target) + n);
	}

	template <typename T>
	class vectorConstIterator
	{
		private :
			T	*ptr;
		public :
			vectorConstIterator(T *ptr = NULL) : ptr(ptr) {}
			vectorConstIterator(const vectorConstIterator<T> &origin) : ptr(origin.ptr) {}
			vectorConstIterator(const vectorIterator<T> &origin) : ptr(origin.getPtr()) {}

			vectorConstIterator<T> &operator=(const vectorConstIterator<T> &origin)
			{
				ptr = origin.ptr;
				return (*this);
			}
			vectorConstIterator<T> &operator=(const vectorIterator<T> &origin)
			{
				ptr = origin.getPtr();
				return (*this);
			}
			~vectorConstIterator(void) {}

			T	*getPtr() const { return (ptr); }

			const T	&operator*(void) const { return (*ptr); }
			const T	*operator->(void) const { return (&(this->operator*())); }

			vectorConstIterator<T>	&operator++(void)
			{
				ptr++;
				return (*this);
			}
			vectorConstIterator<T>	operator++(int)
			{
				vectorConstIterator<T> tmp(*this);
				ptr++;
				return (tmp);
			}
			vectorConstIterator<T>	&operator--(void)
			{
				ptr--;
				return (*this);
			}
			vectorConstIterator<T>	operator--(int)
			{
				vectorConstIterator<T> tmp(*this);
				ptr--;
				return (tmp);
			}

			vectorConstIterator<T>	operator+(unsigned int n) const
			{
				return (vectorConstIterator<T>(ptr + n));
			}
			int						operator+(const vectorConstIterator<T> target) const
			{
				return (ptr + target.getPtr());
			}
			int						operator+(const vectorIterator<T> target) const
			{
				return (ptr + target.getPtr());
			}
			vectorConstIterator<T>	operator-(unsigned int n) const
			{
				return (vectorConstIterator<T>(ptr - n));
			}
			int						operator-(const vectorConstIterator<T> target) const
			{
				return (ptr - target.getPtr());
			}
			int						operator-(const vectorIterator<T> target) const
			{
				return (ptr - target.getPtr());
			}

			vectorConstIterator<T>	&operator+=(unsigned int n)
			{
				ptr += n;
				return (*this);
			}
			vectorConstIterator<T>	&operator-=(unsigned int n)
			{
				ptr -= n;
				return (*this);
			}

			T		&operator[](unsigned int n)
			{
				return (*(this->operator+(n)));
			}
			bool	operator==(const vectorConstIterator<T> &target) const
			{
				return (ptr == target.getPtr());
			}
			bool	operator==(const vectorIterator<T> &target) const
			{
				return (ptr == target.getPtr());
			}
			bool	operator!=(const vectorConstIterator<T> &target) const
			{
				return (!(this->operator==(target)));
			}
			bool	operator!=(const vectorIterator<T> &target) const
			{
				return (!(this->operator==(target)));
			}
			bool	operator<(const vectorConstIterator<T> &target) const
			{
				return (ptr < target.getPtr());
			}
			bool	operator<(const vectorIterator<T> &target) const
			{
				return (ptr < target.getPtr());
			}
			bool	operator<=(const vectorConstIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator<(target));
			}
			bool	operator<=(const vectorIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator<(target));
			}
			bool	operator>(const vectorConstIterator<T> &target) const
			{
				return (ptr > target.getPtr());
			}
			bool	operator>(const vectorIterator<T> &target) const
			{
				return (ptr > target.getPtr());
			}
			bool	operator>=(const vectorConstIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator>(target));
			}
			bool	operator>=(const vectorIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator>(target));
			}
	};

	template<typename T>
	vectorConstIterator<T>	operator+(unsigned int n, vectorConstIterator<T> &target)
	{
		return (&(*target) + n);
	}

	template <typename T>
	class vectorReverseIterator
	{
		private :
			T	*ptr;
		public :
			vectorReverseIterator(T *ptr = NULL) : ptr(ptr) {}
			vectorReverseIterator(const vectorReverseIterator<T> &origin) : ptr(origin.ptr) {}
			vectorReverseIterator(const vectorIterator<T> &origin) : ptr(origin.getPtr() - 1) {}

			vectorReverseIterator<T> &operator=(const vectorReverseIterator<T> &origin)
			{
				ptr = origin.ptr;
				return (*this);
			}
			~vectorReverseIterator(void) {}

			T	*getPtr() const { return (ptr); }
			vectorIterator<T>	base()
			{
				return (vectorIterator<T>(ptr + 1));
			}

			T	&operator*(void) const { return (*ptr); }
			T	*operator->(void) const { return (&(this->operator*())); }

			vectorReverseIterator<T>	&operator++(void)
			{
				ptr--;
				return (*this);
			}
			vectorReverseIterator<T>	operator++(int)
			{
				vectorReverseIterator<T> tmp(*this);
				ptr--;
				return (tmp);
			}
			vectorReverseIterator<T>	&operator--(void)
			{
				ptr++;
				return (*this);
			}
			vectorReverseIterator<T>	operator--(int)
			{
				vectorReverseIterator<T> tmp(*this);
				ptr++;
				return (tmp);
			}

			vectorReverseIterator<T>	operator+(unsigned int n) const
			{
				return (vectorReverseIterator<T>(ptr - n));
			}
			int							operator+(const vectorReverseConstIterator<T> target) const
			{
				return (ptr - target.getPtr());
			}
			int							operator+(const vectorReverseIterator<T> target) const
			{
				return (ptr - target.getPtr());
			}
			vectorReverseIterator<T>	operator-(unsigned int n) const
			{
				return (vectorReverseIterator<T>(ptr + n));
			}
			int							operator-(const vectorReverseConstIterator<T> target) const
			{
				return (ptr + target.getPtr());
			}
			int							operator-(const vectorReverseIterator<T> target) const
			{
				return (ptr + target.getPtr());
			}

			vectorReverseIterator<T>	&operator+=(unsigned int n)
			{
				ptr -= n;
				return (*this);
			}
			vectorReverseIterator<T>	&operator-=(unsigned int n)
			{
				ptr += n;
				return (*this);
			}

			T		&operator[](unsigned int n)
			{
				return (*(this->operator+(n)));
			}
			bool	operator==(const vectorReverseIterator<T> &target) const
			{
				return (ptr == target.getPtr());
			}
			bool	operator==(const vectorReverseConstIterator<T> &target) const
			{
				return (ptr == target.getPtr());
			}
			bool	operator!=(const vectorReverseIterator<T> &target) const
			{
				return (!(this->operator==(target)));
			}
			bool	operator!=(const vectorReverseConstIterator<T> &target) const
			{
				return (!(this->operator==(target)));
			}
			bool	operator<(const vectorReverseIterator<T> &target) const
			{
				return (ptr > target.getPtr());
			}
			bool	operator<(const vectorReverseConstIterator<T> &target) const
			{
				return (ptr > target.getPtr());
			}
			bool	operator<=(const vectorReverseIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator<(target));
			}
			bool	operator<=(const vectorReverseConstIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator<(target));
			}
			bool	operator>(const vectorReverseIterator<T> &target) const
			{
				return (ptr < target.getPtr());
			}
			bool	operator>(const vectorReverseConstIterator<T> &target) const
			{
				return (ptr < target.getPtr());
			}
			bool	operator>=(const vectorReverseIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator>(target));
			}
			bool	operator>=(const vectorReverseConstIterator<T> &target) const
			{
				return (this->operator==(target) || this->operator>(target));
			}
	};

	template<typename T>
	vectorReverseIterator<T>	operator+(unsigned int n, vectorReverseIterator<T> &target)
	{
		return (&(*target) - n);
	}

	template <typename T>
	class vectorReverseConstIterator
	{
		private :
			T	*ptr;
		public :
			vectorReverseConstIterator(T *ptr = NULL) : ptr(ptr) {}
			vectorReverseConstIterator(const vectorReverseConstIterator<T> &origin) : ptr(origin.ptr) {}
			vectorReverseConstIterator(const vectorReverseIterator<T> &origin) : ptr(origin.getPtr()) {}
			vectorReverseConstIterator(const vectorConstIterator<T> &origin) : ptr(origin.getPtr() - 1) {} 
			vectorReverseConstIterator(const vectorIterator<T> &origin) : ptr(origin.getPtr() - 1) {}

			vectorReverseConstIterator<T>	&operator=(const vectorReverseConstIterator<T> &target)
			{
				ptr = target.ptr;
				return (*this);
			}
			vectorReverseConstIterator<T>	&operator=(const vectorReverseIterator<T> &target)
			{
				ptr = target.getPtr();
				return (*this);
			}
			~vectorReverseConstIterator(void) {}

			T						*getPtr(void) const
			{
				return (ptr);
			}
			vectorConstIterator<T>	base()
			{
				return (vectorConstIterator<T>(ptr + 1));
			}

			const T	&operator*(void) const
			{
				return (*ptr);
			}
			const T	*operator->(void) const
			{
				return (&(this->operator*()));
			}

			vectorReverseConstIterator<T>	&operator++(void)
			{
				ptr--;
				return (*this);
			}
			vectorReverseConstIterator<T>	operator++(int)
			{
				vectorReverseConstIterator<T>	tmp(*this);
				ptr--;
				return (tmp);
			}
			vectorReverseConstIterator<T>	&operator--(void)
			{
				ptr++;
				return (*this);
			}
			vectorReverseConstIterator<T>	operator--(int)
			{
				vectorReverseConstIterator<T>	tmp(*this);
				ptr++;
				return (tmp);
			}

			vectorReverseConstIterator<T>	operator+(unsigned int n) const
			{
				return (vectorReverseConstIterator<T>(ptr - n));
			}
			int								operator+(const vectorReverseConstIterator<T> &target) const
			{
				return (ptr - target.getPtr());
			}
			int								operator+(const vectorReverseIterator<T> &target) const
			{
				return (ptr - target.getPtr());
			}
			vectorReverseConstIterator<T>	operator-(unsigned int n) const
			{
				return (vectorReverseConstIterator<T>(ptr + n));
			}
			int								operator-(const vectorReverseConstIterator<T> &target) const // 확인을 해보자
			{
				return (target.getPtr() - ptr);
				// return (ptr + target.getPtr());
			}
			int								operator-(const vectorReverseIterator<T> &target) const
			{
				return (target.getPtr() - ptr);
				// return (ptr + target.getPtr());
			}

			vectorReverseConstIterator<T>	&operator+=(unsigned int n)
			{
				ptr -= n;
				return (*this);
			}
			vectorReverseConstIterator<T>	&operator-=(unsigned int n)
			{
				ptr += n;
				return (*this);
			}

			T		&operator[](unsigned int n) const
			{
				return (*(this->operator+(n)));
			}
			bool	operator==(const vectorReverseConstIterator<T> &target) const
			{
				return (ptr == target.getPtr());
			}
			bool	operator==(const vectorReverseIterator<T> &target) const
			{
				return (ptr == target.getPtr());
			}
			bool	operator!=(const vectorReverseConstIterator<T> &target) const
			{
				return (!(this->operator==(target)));
			}
			bool	operator!=(const vectorReverseIterator<T> &target) const
			{
				return (!(this->operator==(target)));
			}
			bool	operator<(const vectorReverseConstIterator<T> &target) const
			{
				return (ptr > target.getPtr());
			}
			bool	operator<(const vectorReverseIterator<T> &target) const
			{
				return (ptr > target.getPtr());
			}
			bool	operator<=(const vectorReverseConstIterator<T> &target) const
			{
				return ((this->operator<(target)) || (this->operator==(target)));
			}
			bool	operator<=(const vectorReverseIterator<T> &target) const
			{
				return ((this->operator<(target)) || (this->operator==(target)));
			}
			bool	operator>(const vectorReverseConstIterator<T> &target) const
			{
				return (ptr < target.getPtr());
			}
			bool	operator>(const vectorReverseIterator<T> &target) const
			{
				return (ptr < target.getPtr());
			}
			bool	operator>=(const vectorReverseConstIterator<T> &target) const
			{
				return ((this->operator>(target)) || (this->operator==(target)));
			}
			bool	operator>=(const vectorReverseIterator<T> &target) const
			{
				return ((this->operator>(target)) || (this->operator==(target)));
			}
	};

	template<typename T>
	vectorReverseConstIterator<T>	operator+(unsigned int n, const vectorReverseConstIterator<T> &target)
	{
		return (vectorReverseConstIterator<T>(&(*target) - n));
	}
}

#endif
