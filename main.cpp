#include "mi.hpp"

#include <iostream>

#include <vector>

#include <deque>

#include <ctime>

/*

	N <- 1,000,000
	DEPTH <- ~21
	RAM <- 12mb
	ATOM <- 24B

*/

int main(int argc, char **argv)
{
	
	std::vector < ATOM > X_vector, S_vector;
	std::deque < ATOM > X_deque, S_deque;
	std::clock_t start, end;
	double us;
	long integer = 0;
	size_t digit_length = 0;
	long pow = 1e9;
	ATOM element;

	if ( argc < 2 )
	{

		std::cerr << "ERROR: usage ./PmergeMe A B ..." << std::endl;
		return 1;
 
	}

	if (argv == NULL)
	{
		
		std::cerr << "ERROR: FATAL: NULL ARGV" << std::endl;
		return 1;
		
	}

	for ( int i = 1 ; i < argc ; i++ )
	{
		
		if ( argv [ i ] == NULL )
		{

			std::cerr << "ERROR: FATAL: NULL POINTER" << std::endl;
			return 1;

		}

		

		for ( int j = 0 ; argv [ i ][ j ] != '\0' ; j++ )
		{

			if ( argv [ i ][ j ] >= '0' and argv [ i ][ j ] <= '9' )
			{
				
				integer += ( argv [ i ][ j ] - '0' ) * pow;
				pow /= 10;
				digit_length++;
				if ( argv [ i ][ j + 1 ] == '\0' or argv [ i ][ j + 1 ] == ' ' )
				{

					if ( pow > 0 )
						integer /= pow * 10;
					if ( digit_length > 10 or integer > INT32_MAX )
					{

						std::cerr << "ERROR: not a positive 32-bit signed integer" << std::endl;
						return 1;

					}
					element.integer = integer;
					element.p = 0;
					element.pair_chain = NULL;
					X_vector.push_back ( element );
					X_deque.push_back ( element );
					pow = 1e9;
					integer = 0;
					digit_length = 0;

				}

			}
			else if ( argv [ i ][ j ] == ' ' )
				continue;
			else
			{
				
				std::cerr << "ERROR: not a digit/space" << std::endl;
				return 1;

			}

		}
		
	}

	if ( X_deque.size() > 1e6 or X_vector.size() > 1e6 )
	{
		std::cerr << "ERROR: maximum number of elements is 1,000,000" << std::endl;
		return 1;
	}
	start = std::clock();
	merge_insertion < std::deque<ATOM> > ( X_deque , S_deque , 1 );
	end = std::clock();
	us = double(end - start) / CLOCKS_PER_SEC * 1e6;

	std::cout << "UNSORTED <- ";
	for ( size_t i = 0 ; i < X_deque.size() ; i++ )
		std::cout << "[" << X_deque [ i ].integer << "]";
	std::cout << std::endl;

	std::cout << "SORTED <- ";
	for ( size_t i = 0 ; i < S_deque.size() ; i++ )
		std::cout << "[" << S_deque [ i ].integer << "]";
	std::cout << std::endl;

	std::cout << "using deque <- " << us << " us" << std::endl;

	start = std::clock();
	merge_insertion < std::vector<ATOM> > ( X_vector , S_vector , 1 );
	end = std::clock();
	us = double(end - start) / CLOCKS_PER_SEC * 1e6;
	std::cout << "using vector <- " << us << " us" << std::endl;

	return 0;
	
}

#include "mi.tpp"
	