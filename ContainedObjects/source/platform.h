/*
 * platform.h
 *
 *  Created on: Oct 20, 2010
 *      Author: Ernesto Badillo
 */

#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>


#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>

#include "Error.h"
