/*
Copyright 2017-2019 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS-IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "lullaby/modules/lullscript/functions/functions.h"
#include "lullaby/modules/lullscript/script_env.h"
#include "lullaby/modules/lullscript/script_frame.h"
#include "lullaby/modules/lullscript/script_types.h"

// This file implements the following script functions:
//
// (do [statement] [statement] [statement] ...)
//   Evaluates a sequence of statements, returning the result of the last one.

namespace lull {
namespace {

void Do(ScriptFrame* frame) {
  while (frame->HasNext()) {
    frame->Return(frame->EvalNext());
  }
}

LULLABY_SCRIPT_FUNCTION(Do, "do");

}  // namespace
}  // namespace lull
