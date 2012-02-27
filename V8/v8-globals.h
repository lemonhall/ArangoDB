////////////////////////////////////////////////////////////////////////////////
/// @brief V8-vocbase bridge
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

#ifndef TRIAGENS_V8_V8_GLOBALS_H
#define TRIAGENS_V8_V8_GLOBALS_H 1

#include "BasicsC/common.h"

#include <regex.h>

#include <map>
#include <set>
#include <string>
#include <vector>

#include <v8.h>

#include "Basics/ReadWriteLock.h"
#include "VocBase/vocbase.h"

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup V8Globals
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief globals stored in the isolate
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_v8_global_s {

////////////////////////////////////////////////////////////////////////////////
/// @brief constructor
////////////////////////////////////////////////////////////////////////////////

  TRI_v8_global_s ()
    : JSFluentQueries(),
      JSQueries(),
      JSCursors(),
      JSWheres(),
      JSResultSets(),
      JSBarriers(),
      Actions(),
      SystemActions(),
      ActionsLock(),
      EdgesTempl(),
      EdgesColTempl(),
      FluentQueryTempl(),
      QueryTempl(),
      CursorTempl(),
      WhereTempl(),
      VocbaseColTempl(),
      VocbaseTempl(),
      OutputFuncName(),
      PrintFuncName(),
      CollectionQueryType(),
      ContentType(),
      BodyKey(),
      DidKey(),
      FromKey(),
      JournalSizeKey(),
      ParametersKey(),
      ResponseCodeKey(),
      SyncAfterBytesKey(),
      SyncAfterObjectsKey(),
      SyncAfterTimeKey(),
      ToKey(),
      DocumentIdRegex() {
  }

////////////////////////////////////////////////////////////////////////////////
/// @brief fluent query mapping for weak pointers
////////////////////////////////////////////////////////////////////////////////

  std::map< void*, v8::Persistent<v8::Value> > JSFluentQueries;

////////////////////////////////////////////////////////////////////////////////
/// @brief query mapping for weak pointers
////////////////////////////////////////////////////////////////////////////////

  std::map< void*, v8::Persistent<v8::Value> > JSQueries;

////////////////////////////////////////////////////////////////////////////////
/// @brief cursor mapping for weak pointers
////////////////////////////////////////////////////////////////////////////////

  std::map< void*, v8::Persistent<v8::Value> > JSCursors;

////////////////////////////////////////////////////////////////////////////////
/// @brief where clause mapping for weak pointers
////////////////////////////////////////////////////////////////////////////////

  std::map< void*, v8::Persistent<v8::Value> > JSWheres;

////////////////////////////////////////////////////////////////////////////////
/// @brief result set mapping for weak pointers
////////////////////////////////////////////////////////////////////////////////

  std::map< void*, v8::Persistent<v8::Value> > JSResultSets;

////////////////////////////////////////////////////////////////////////////////
/// @brief barrier mapping for weak pointers
////////////////////////////////////////////////////////////////////////////////

  std::map< void*, v8::Persistent<v8::Value> > JSBarriers;

////////////////////////////////////////////////////////////////////////////////
/// @brief map of callbacks for actions
////////////////////////////////////////////////////////////////////////////////

  std::map<std::string, void*> Actions;

////////////////////////////////////////////////////////////////////////////////
/// @brief map of callbacks for system actions
////////////////////////////////////////////////////////////////////////////////

  std::map<std::string, void*> SystemActions;

////////////////////////////////////////////////////////////////////////////////
/// @brief lock for the actions
////////////////////////////////////////////////////////////////////////////////

  triagens::basics::ReadWriteLock ActionsLock;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                       JAVASCRIPT OBJECT TEMPLATES
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup V8Globals
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief TRI_vocbase_t template for edges
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::ObjectTemplate> EdgesTempl;

////////////////////////////////////////////////////////////////////////////////
/// @brief TRI_vocbase_col_t template for edges
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::ObjectTemplate> EdgesColTempl;

////////////////////////////////////////////////////////////////////////////////
/// @brief fluent query template
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::ObjectTemplate> FluentQueryTempl;

////////////////////////////////////////////////////////////////////////////////
/// @brief query template
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::ObjectTemplate> QueryTempl;

////////////////////////////////////////////////////////////////////////////////
/// @brief cursor template
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::ObjectTemplate> CursorTempl;

////////////////////////////////////////////////////////////////////////////////
/// @brief where clause template
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::ObjectTemplate> WhereTempl;

////////////////////////////////////////////////////////////////////////////////
/// @brief TRI_vocbase_col_t template
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::ObjectTemplate> VocbaseColTempl;

////////////////////////////////////////////////////////////////////////////////
/// @brief TRI_vocbase_t template
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::ObjectTemplate> VocbaseTempl;

////////////////////////////////////////////////////////////////////////////////
/// @brief TRI_shaped_json_t template
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::ObjectTemplate> ShapedJsonTempl;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                         JAVASCRIPT FUNCTION NAMES
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup V8Globals
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief "output" function name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> OutputFuncName;

////////////////////////////////////////////////////////////////////////////////
/// @brief "print" function name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> PrintFuncName;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                              JAVASCRIPT KEY NAMES
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup V8Globals
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief "collection" query type
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> CollectionQueryType;

////////////////////////////////////////////////////////////////////////////////
/// @brief "contentType" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> ContentType;

////////////////////////////////////////////////////////////////////////////////
/// @brief "body" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> BodyKey;

////////////////////////////////////////////////////////////////////////////////
/// @brief "_id" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> DidKey;

////////////////////////////////////////////////////////////////////////////////
/// @brief "_from" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> FromKey;

////////////////////////////////////////////////////////////////////////////////
/// @brief "headers" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> HeadersKey;

////////////////////////////////////////////////////////////////////////////////
/// @brief "journalSize" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> JournalSizeKey;

////////////////////////////////////////////////////////////////////////////////
/// @brief "parameters" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> ParametersKey;

////////////////////////////////////////////////////////////////////////////////
/// @brief "responseCode" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> ResponseCodeKey;

////////////////////////////////////////////////////////////////////////////////
/// @brief "_rev" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> RevKey;

////////////////////////////////////////////////////////////////////////////////
/// @brief "syncAfterBytes" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> SyncAfterBytesKey;

////////////////////////////////////////////////////////////////////////////////
/// @brief "syncAfterObjects" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> SyncAfterObjectsKey;

////////////////////////////////////////////////////////////////////////////////
/// @brief "syncAfterTime" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> SyncAfterTimeKey;

////////////////////////////////////////////////////////////////////////////////
/// @brief "_to" key name
////////////////////////////////////////////////////////////////////////////////

  v8::Persistent<v8::String> ToKey;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                               REGULAR EXPRESSIONS
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                 private variables
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup V8Globals
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief document identifier as collection-id:document-id
////////////////////////////////////////////////////////////////////////////////

  regex_t DocumentIdRegex;
}
TRI_v8_global_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|// --SECTION--\\|/// @\\}\\)"
// End:
