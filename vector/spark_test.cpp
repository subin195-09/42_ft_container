/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spark_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim <skim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:56:22 by skim              #+#    #+#             */
/*   Updated: 2021/11/05 18:56:52 by skim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>

template <typename T>
void print_T(T a, int length)
{
    // std::cout << '<' << typeid(a).name() << "> : ";
    for (int i = 0; i < length; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

int main(void)
{
    ft::vector<int> vec_1;
    std::vector<int> vec_2;
    // ft::vector<int>::iterator iter_1;
    // ft::vector<int>::reverse_iterator iter_2;
    // // std::vector<int> *vec_iter;
    vec_1.push_back(1);
    vec_1.push_back(2);
    vec_1.push_back(3);
    vec_1.push_back(4);
    vec_1.push_back(5);
    vec_1.push_back(6);
    vec_1.push_back(7);
    vec_1.push_back(8);
    vec_1.push_back(9);
    vec_1.push_back(10);
    vec_1.push_back(11);
    vec_1.push_back(12);
    vec_2.push_back(1);
    vec_2.push_back(2);
    vec_2.push_back(3);
    vec_2.push_back(4);
    vec_2.push_back(5);
    vec_2.push_back(6);
    vec_2.push_back(7);
    vec_2.push_back(8);
    vec_2.push_back(9);
    vec_2.push_back(10);
    vec_2.push_back(11);
    vec_2.push_back(12);
    // std::cout << *(vec_1.begin()) << std::endl;
    // std::cout << *(vec_1.end()) << std::endl;
    // std::cout << *(vec_1.rbegin()) << std::endl;
    // std::cout << *(vec_1.rend()) << std::endl;
    std::cout << std::endl;
    std::cout << "========================== my vec ===================== " << std::endl;
    std::cout << vec_1[0] << std::endl;
    std::cout << vec_1[1] << std::endl;
    std::cout << vec_1[2] << std::endl;
    std::cout << vec_1[3] << std::endl;
    std::cout << vec_1[4] << std::endl;
    std::cout << vec_1[5] << std::endl;
    std::cout << vec_2[6] << std::endl;
    std::cout << vec_2[7] << std::endl;
    std::cout << vec_2[8] << std::endl;
    std::cout << vec_2[9] << std::endl;
    std::cout << vec_2[10] << std::endl;
    std::cout << std::endl;
    std::cout << vec_1.capacity() << std::endl;
    print_T(vec_1, 6);
    //->> copy 컨스트럭터 잘 살펴보기!
    std::cout << std::endl;
    std::cout << "========================== real vec ===================== " << std::endl;
    std::cout << vec_2[0] << std::endl;
    std::cout << vec_2[1] << std::endl;
    std::cout << vec_2[2] << std::endl;
    std::cout << vec_2[3] << std::endl;
    std::cout << vec_2[4] << std::endl;
    std::cout << vec_2[5] << std::endl;
    std::cout << vec_2[6] << std::endl;
    std::cout << vec_2[7] << std::endl;
    std::cout << vec_2[8] << std::endl;
    std::cout << vec_2[9] << std::endl;
    std::cout << vec_2[10] << std::endl;
    std::cout << std::endl;
    std::cout << vec_2.capacity() << std::endl;
    print_T(vec_2, 6);
    return 0;
}
