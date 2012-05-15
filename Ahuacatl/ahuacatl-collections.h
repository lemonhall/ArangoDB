////////////////////////////////////////////////////////////////////////////////
/// @brief Ahuacatl, collections
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2012 triagens GmbH, Cologne, Germany
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
/// @author Jan Steemann
/// @author Copyright 2012, triagens GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_DURHAM_AHUACATL_COLLECTIONS_H
#define TRIAGENS_DURHAM_AHUACATL_COLLECTIONS_H 1

#include <BasicsC/common.h>
#include <BasicsC/vector.h>
#include <BasicsC/logging.h>

#include "VocBase/vocbase.h"
#include "VocBase/barrier.h"
#include "VocBase/document-collection.h"

#include "Ahuacatl/ahuacatl-context.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// --SECTION--                                                           defines
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Ahuacatl
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief max number of collections usable in a query
////////////////////////////////////////////////////////////////////////////////

#define AQL_MAX_COLLECTIONS  32

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Ahuacatl
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief a collection container
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_aql_collection_s {
  char* _name;
  bool _readLocked;
  TRI_vocbase_col_t* _collection;
  TRI_barrier_t* _barrier;
}
TRI_aql_collection_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Ahuacatl
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief lookip a collection in the internal vector
////////////////////////////////////////////////////////////////////////////////

TRI_aql_collection_t* TRI_GetCollectionAql (const TRI_aql_context_t* const,
                                            const char* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief unlock all collections used
////////////////////////////////////////////////////////////////////////////////

void TRI_UnlockCollectionsAql (TRI_aql_context_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief lock all collections used
////////////////////////////////////////////////////////////////////////////////

bool TRI_LockCollectionsAql (TRI_aql_context_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief lock all collections used
////////////////////////////////////////////////////////////////////////////////

bool TRI_ReadLockCollectionsAql (TRI_aql_context_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief read-unlocks all collections used in a query
////////////////////////////////////////////////////////////////////////////////

void TRI_ReadUnlockCollectionsAql (TRI_aql_context_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a gc marker for all collections used in a query
////////////////////////////////////////////////////////////////////////////////

bool TRI_AddBarrierCollectionsAql (TRI_aql_context_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief removes the gc markers for all collections used in a query
////////////////////////////////////////////////////////////////////////////////

void TRI_RemoveBarrierCollectionsAql (TRI_aql_context_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|// --SECTION--\\|/// @\\}\\)"
// End:
