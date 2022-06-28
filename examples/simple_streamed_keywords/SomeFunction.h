#pragma once

#include <stdio.h>
#include "keyclass.h"

// Prototype for example function using CKWargs.
// 
// Note that ckw defaults to an empty ckw() so that the calling function
// does not need to specify keywords()
//
void SomeFunction(const char * sTitle, const keyclass::ckw & kwx = keyclass::ckw());

