////////////////////////////////////////////////////////////////////////////////
/// @brief threads in win32
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2012 triagens GmbH, Cologne, Germany
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
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2011-2012, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#include "threads.h"

#include "BasicsC/logging.h"

// -----------------------------------------------------------------------------
// --SECTION--                                                            THREAD
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                     private types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief data block for thread starter
////////////////////////////////////////////////////////////////////////////////

typedef struct thread_data_s {
  void (*starter) (void*);
  void* _data;
}
thread_data_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                 private functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief starter function for thread
////////////////////////////////////////////////////////////////////////////////

static DWORD __stdcall ThreadStarter (void* data) {
  thread_data_t* d;

  d = data;
  d->starter(d->_data);

  TRI_Free(TRI_CORE_MEM_ZONE, d);

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a thread
////////////////////////////////////////////////////////////////////////////////

void TRI_InitThread (TRI_thread_t* thread) {
  *thread = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Threading
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the current process identifier
////////////////////////////////////////////////////////////////////////////////

TRI_pid_t TRI_CurrentProcessId () {
  return _getpid();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the current thread process identifier
////////////////////////////////////////////////////////////////////////////////

TRI_tpid_t TRI_CurrentThreadProcessId () {
  return _getpid();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the current thread identifier
////////////////////////////////////////////////////////////////////////////////

TRI_tid_t TRI_CurrentThreadId () {
  return GetCurrentThreadId();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief starts a thread
////////////////////////////////////////////////////////////////////////////////

bool TRI_StartThread (TRI_thread_t* thread, void (*start)(void*), void* data) {
  DWORD threadId;
  thread_data_t* d;

  d = TRI_Allocate(TRI_CORE_MEM_ZONE, sizeof(thread_data_t), false);

  d->starter = start;
  d->_data = data;

  *thread = CreateThread(0, // default security attributes
                         0, // use default stack size
                         ThreadStarter, // thread function name
                         d, // argument to thread function
                         0, // use default creation flags
                         &threadId); // returns the thread identifier

  if (*thread == 0) {
    TRI_Free(TRI_CORE_MEM_ZONE, d);
    LOG_ERROR("could not start thread: %s ", strerror(errno));
    return false;
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief waits for a thread to finish
////////////////////////////////////////////////////////////////////////////////

void TRI_JoinThread (TRI_thread_t* thread) {
  WaitForSingleObject(*thread, INFINITE);
}

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|// --SECTION--\\|/// @\\}\\)"
// End:

