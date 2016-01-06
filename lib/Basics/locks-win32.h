////////////////////////////////////////////////////////////////////////////////
/// @brief mutexes, locks and condition variables in win32
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

#ifndef LIB_BASICS_LOCKS_WIN32_H
#define LIB_BASICS_LOCKS_WIN32_H 1

#include "Basics/Common.h"

#ifdef TRI_HAVE_WIN32_THREADS


////////////////////////////////////////////////////////////////////////////////
/// @brief mutex type
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_mutex_s {
// as of VS2013, exclusive SRWLocks tend to be faster than native mutexes
#if TRI_WINDOWS_VISTA_LOCKS
  HANDLE _mutex;
#else
  SRWLOCK _mutex;
#endif
} TRI_mutex_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief spin-lock type
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_FAKE_SPIN_LOCKS

#define TRI_spin_t TRI_mutex_t
#define TRI_InitSpin TRI_InitMutex
#define TRI_DestroySpin TRI_DestroyMutex
#define TRI_LockSpin TRI_LockMutex
#define TRI_UnlockSpin TRI_UnlockMutex
#else

#define TRI_spin_t CRITICAL_SECTION

#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief read-write-lock type
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_read_write_lock_s {
#if TRI_WINDOWS_VISTA_LOCKS
  HANDLE _writerEvent;
  HANDLE _readersEvent;

  int _readers;
  CRITICAL_SECTION _lockWriter;
  CRITICAL_SECTION _lockReaders;
#else
  SRWLOCK _lock;
#endif
} TRI_read_write_lock_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief condition variable
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_condition_s {
  CRITICAL_SECTION _lockWaiters;
  CONDITION_VARIABLE _conditionVariable;
} TRI_condition_t;

#endif

#endif


