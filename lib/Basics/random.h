////////////////////////////////////////////////////////////////////////////////
/// @brief random functions
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2014 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2014, ArangoDB GmbH, Cologne, Germany
/// @author Copyright 2011-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef LIB_BASICS_RANDOM_H
#define LIB_BASICS_RANDOM_H 1

#ifdef _WIN32
#define _CRT_RAND_S
#endif

#include "Basics/Common.h"


////////////////////////////////////////////////////////////////////////////////
/// @brief generates a 16 bit random unsigned integer
////////////////////////////////////////////////////////////////////////////////

uint16_t TRI_UInt16Random(void);

////////////////////////////////////////////////////////////////////////////////
/// @brief generates a 32 bit random unsigned integer
////////////////////////////////////////////////////////////////////////////////

uint32_t TRI_UInt32Random(void);



////////////////////////////////////////////////////////////////////////////////
/// @brief initializes the random components
////////////////////////////////////////////////////////////////////////////////

void TRI_InitializeRandom(void);

////////////////////////////////////////////////////////////////////////////////
/// @brief shuts down the random components
////////////////////////////////////////////////////////////////////////////////

void TRI_ShutdownRandom(void);

#endif


