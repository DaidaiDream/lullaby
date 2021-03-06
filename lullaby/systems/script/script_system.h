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

#ifndef LULLABY_SYSTEMS_SCRIPT_SCRIPT_SYSTEM_H_
#define LULLABY_SYSTEMS_SCRIPT_SCRIPT_SYSTEM_H_

#include "lullaby/generated/script_def_generated.h"
#include "lullaby/modules/ecs/component.h"
#include "lullaby/modules/ecs/system.h"
#include "lullaby/modules/script/script_engine.h"
#include "lullaby/util/clock.h"
#include "lullaby/util/entity.h"
#include "lullaby/util/hash.h"

namespace lull {

// The ScriptSystem allows scripts to be attached to entites, that are run
// when an event fires, or every frame.
class ScriptSystem : public System {
 public:
  explicit ScriptSystem(Registry* registry);

  void Create(Entity e, HashValue type, const Def* def) override;

  void PostCreateInit(Entity e, HashValue type, const Def* def) override;

  void Destroy(Entity e) override;

  void AdvanceFrame(Clock::duration delta_time);

 private:
  struct Scripts : Component {
    Scripts(Entity e, ScriptId id) : Component(e), ids{id} {}
    std::vector<ScriptId> ids;
  };

  static void AddScript(ComponentPool<Scripts>* pool, Entity entity,
                        ScriptId id);

  ScriptId LoadScriptDef(const ScriptDef* data, Entity entity);

  ScriptId LoadScriptDef(const ScriptDef* data);

  ScriptEngine* engine_;
  ComponentPool<Scripts> every_frame_scripts_;
  ComponentPool<Scripts> on_destroy_scripts_;
  ComponentPool<Scripts> event_scripts_;
};

}  // namespace lull

LULLABY_SETUP_TYPEID(lull::ScriptSystem);

#endif  // LULLABY_SYSTEMS_SCRIPT_SCRIPT_SYSTEM_H_
