////////////////////////////////////////////////////////////////////////////////
/// @brief a basis class for concrete implementations for a shell
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
/// @author Esteban Lombeyda
/// @author Copyright 2014, ArangoDB GmbH, Cologne, Germany
/// @author Copyright 2011-2014, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGODB_UTILITIES_SHELL_IMPLEMENTATION_H
#define ARANGODB_UTILITIES_SHELL_IMPLEMENTATION_H 1

#include "Basics/Common.h"

#include "Completer.h"

namespace triagens {

  class ShellImplementation {
////////////////////////////////////////////////////////////////////////////////
/// @brief state of the console                                  protected types
////////////////////////////////////////////////////////////////////////////////
  protected:
    typedef enum {
      STATE_NONE = 0,
      STATE_OPENED,
      STATE_CLOSED
    }
    console_state_e;

  public:
////////////////////////////////////////////////////////////////////////////////
///                                               public constructor, destructor
////////////////////////////////////////////////////////////////////////////////

    ShellImplementation (std::string const& history, Completer *);

    virtual ~ShellImplementation ();

////////////////////////////////////////////////////////////////////////////////
/// @brief line editor open
////////////////////////////////////////////////////////////////////////////////

    virtual bool open (bool autoComplete)  = 0;

////////////////////////////////////////////////////////////////////////////////
/// @brief line editor shutdown
////////////////////////////////////////////////////////////////////////////////

    virtual bool close () = 0;

////////////////////////////////////////////////////////////////////////////////
/// @brief line editor prompt
////////////////////////////////////////////////////////////////////////////////

    virtual char* prompt (char const* prompt);

////////////////////////////////////////////////////////////////////////////////
/// @brief get the history file path
///
/// The path is "$HOME" plus _historyFilename, if $HOME is set. Else
/// the local file _historyFilename.
////////////////////////////////////////////////////////////////////////////////

    virtual std::string historyPath () = 0;

////////////////////////////////////////////////////////////////////////////////
/// @brief add to history
////////////////////////////////////////////////////////////////////////////////

    virtual void addHistory (const char*) = 0;

////////////////////////////////////////////////////////////////////////////////
/// @brief save the history
////////////////////////////////////////////////////////////////////////////////

    virtual bool writeHistory () = 0;

////////////////////////////////////////////////////////////////////////////////
/// @brief todo!!
////////////////////////////////////////////////////////////////////////////////

    virtual char * getLine (const char*) = 0;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

    // -----------------------------------------------------------------------------
    // --SECTION--                                               protected variables
    // -----------------------------------------------------------------------------

  protected:

////////////////////////////////////////////////////////////////////////////////
/// @brief current text
////////////////////////////////////////////////////////////////////////////////

    std::string _current;

////////////////////////////////////////////////////////////////////////////////
/// @brief history filename
////////////////////////////////////////////////////////////////////////////////

    std::string _historyFilename;

////////////////////////////////////////////////////////////////////////////////
/// @brief current console state
////////////////////////////////////////////////////////////////////////////////

    console_state_e _state;

////////////////////////////////////////////////////////////////////////////////
/// @brief object which defines when the input is finished
////////////////////////////////////////////////////////////////////////////////

    Completer * _completer;

  };
}
#endif
// -----------------------------------------------------------------------------
// --SECTION--                                                       END-OF-FILE
// -----------------------------------------------------------------------------

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End: