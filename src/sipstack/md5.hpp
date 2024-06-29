#ifndef _MD5_H_
#define _MD5_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


void md5(const void* msg, size_t len, void* digest);


#endif // _MD5_H_