
#include "array"
#include <cassert>

constexpr int array_size = 8;
using array_type = int;


std::array<array_type,array_size> origin;
const std::array<array_type,array_size>& corigin = origin;

void foo( array_type (&ar)[array_size] )
{
    ar[0] = 42; 
}

void foo( const array_type (&ar)[array_size] )
{
    assert( &ar == &corigin._M_elems );
}

void foo( array_type (*ar)[array_size] )
{
    *ar[0] = 21;
}

void foo( const array_type (*ar)[array_size] )
{
    assert( ar == &corigin._M_elems );
}

void foo( array_type (&&ar)[array_size] )
{
    ar[0] = 84; 
}

int main()
{
    origin[0] = 12;             
    assert( origin[0] == 12 );

    foo( origin.c_array() );    
    assert( origin[0] == 42 );

    foo( corigin.c_array() );

    foo( &origin.c_array() );
    assert( origin[0] == 21 );

    foo( &corigin.c_array() ); 

    foo( std::array<array_type,array_size>{ 0,1,2,3,4,5,6,7 }.c_array() );
    assert( origin[0] == 21 );

    return 0;
}
