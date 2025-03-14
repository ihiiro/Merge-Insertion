#include "mi.hpp"

#include <iostream>

#include <cmath>
#include <cstdlib>

size_t compute_b ( int k )
{

	return ( std::pow ( 2 ,  k + 1 ) + std::pow ( -1 , k ) ) / 3;
	
}





template < typename T >
size_t binsert ( ATOM target , T& S , long L , long R , long end )
{
	
	size_t m = ( L + R ) / 2;

	if ( L > R )
	{
	
		S.insert ( S.begin() + L , target );
		return L;

	}

	if ( S [ m ].integer < target.integer )
		return binsert ( target , S , m + 1 , R , end );
	else
		return binsert ( target , S , L , m - 1 , end );

}








template < typename T >
size_t INSERT ( ATOM target , T& S , long end )
{

	return binsert ( target , S , 0 , end , end );

}








 
ATOM* pair_chain_lookup ( ATOM atom , int R )
{
	ATOM* ptr = &atom;
	int chain_length = R;
	for ( int i = 0 ; i < chain_length ; i++ )
		ptr = ptr->pair_chain;

	return ptr;
	
} 








template < typename T >
void insert ( T& container , T& S , int R )
{

	T main_chain = S;
	int k = 2;
	size_t prev_group_end = 1;
	bool odd_container = container.size() % 2;
	ATOM container_last = container [ container.size() - 1 ];
	ATOM* pairing;
	size_t b;
	size_t b_copy;
	size_t insertion_index;

	for ( size_t i = 0 ; i < main_chain.size() ; i++ )
		main_chain [ i ].p = 0;

	while ( 1 )
	{
		
		b = compute_b ( k );
		b_copy = b;

		if ( b > main_chain.size() - 1 )
		{

			b = main_chain.size() - 1;
			if ( odd_container )
			{
				
				insertion_index = INSERT ( container_last , S , S.size() - 1 );
				for ( size_t i = 0 ; i < main_chain.size() ; i++ )
					if ( insertion_index <= ( i + main_chain [ i ].p ) )
						main_chain [ i ].p++;				
				
			}
			while ( b > prev_group_end )
			{
				
				pairing = pair_chain_lookup ( main_chain [ b ] , R );
				insertion_index = INSERT ( *pairing , S , ( b + main_chain [ b ].p ) - 1 );
				for ( size_t i = 0 ; i < main_chain.size() ; i++ )
					if ( insertion_index <= ( i + main_chain [ i ].p ) )
						main_chain [ i ].p++;
				b--;

			}

			return;

		}

		while ( b > prev_group_end )
		{
			
			pairing = pair_chain_lookup ( main_chain[ b ] , R );
			insertion_index = INSERT ( *pairing , S , ( b + main_chain [ b ].p ) - 1 );
			for ( size_t i = 0 ; i < main_chain.size() ; i++ )
				if ( insertion_index <= ( i + main_chain [ i ].p ) )
					main_chain [ i ].p++;
			b--;
			
		}

		prev_group_end = b_copy;
		k++;
		
	}

}






template < typename T >
T pairwise_reduce ( T& container , int R )
{
	
	T reduced;
	ATOM *smaller;
	ATOM *larger;
	ATOM *ptr;
	int chain_length;

	for ( size_t i = 0 ; i + 1 < container.size() ; i += 2 )
	{
		
		if ( container [ i ].integer < container [ i + 1 ].integer )
		{
			
			larger = &container [ i + 1 ];
			smaller = &container [ i ];

		}
		else
		{

			larger = &container [ i ];
			smaller = &container [ i + 1 ];
			
		}
		ptr = larger;
		chain_length = R - 1;
		for ( int j = 0 ; j < chain_length ; j++ )
			ptr = ptr->pair_chain;
		ptr->pair_chain = smaller;
		reduced.push_back ( *larger );

	}

	return reduced;
	
}









template < typename T >
void merge_insertion ( T& container , T& S , int R )
{
	
	if ( container.size() == 1 )
	{
		
		S.push_back( container[ 0 ] );
		return;	
			
	}

	T container_of_largest_in_pairs = pairwise_reduce ( container , R );
	merge_insertion ( container_of_largest_in_pairs , S , R * 2 );
	ATOM *a1_pairing = pair_chain_lookup ( S[ 0 ] , R );
	S.insert ( S.begin() , *a1_pairing );
	insert ( container , S , R );
 }