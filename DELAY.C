

#include <htc.h> 		// processor if/def file
#include "delay.h"

//void Delay_1S( char loop_count ) // approximate 1S base delay
//{
//  unsigned int inner; // define/declare auto type int variable
//  unsigned char outer; // define/declare auto type char variable
//  while ( loop_count )
//  {
//    for ( outer = 145; outer > 0; outer-- )
//    for ( inner = 985; inner > 0; inner-- )
//    {
//      NOP();
//      NOP();
//      NOP();
//      NOP();
//      NOP();
//    }
//    loop_count--; // decrement loop iteration counter
//  }
//}

//-------------------------------------------------------------------------

void Delay_10mS( int loop_count ) // approximate 10mS base delay
{
  unsigned int inner; // define/declare auto type int variable
  unsigned int outer; // define/declare auto type char variable
  while ( loop_count )
  {
    for ( outer = 9; outer > 0; outer-- )
      for ( inner = 246; inner > 0; inner-- )
        ;
    loop_count--; // decrement loop iteration counter
  }
}

//-------------------------------------------------------------------------

void Delay_100mS( int loop_count ) // approximate 100mS base delay
{
  unsigned int inner; // define/declare auto type int variable
  unsigned int outer; // define/declare auto type char variable
  while ( loop_count )
  {
    for ( outer = 87; outer > 0; outer-- )
      for ( inner = 255; inner > 0; inner-- )
        ;
    loop_count--; // decrement loop iteration counter
  }
}
