#pragma once
#include <cstdlib>

#include <vector>


typedef struct atom_s
{
	size_t p;
	int integer;
	struct atom_s *pair_chain;
}  ATOM;

template < typename T >
void merge_insertion ( T& container , T& S , int R );
