#ifndef __RSA_H__
#define __RSA_H__ 

#include "vlong.h"

class public_key
{
  public:
  vlong n,e;
  vlong encrypt( const vlong& plain ); // Requires 0 <= plain < n
};

class private_key : public public_key
{
  public:
  vlong p,q;
  vlong decrypt( const vlong& cipher );

  void create( const char * r1, const char * r2 );
  // r1 and r2 should be null terminated random strings
  // each of length around 35 characters (for a 500 bit modulus)
};

#endif