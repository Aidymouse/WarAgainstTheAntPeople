#pragma once

#include "components/Components.hpp"
#include "engine/Collisions.h"
#include <ecs/ComponentManager.hpp>
#include <ecs/Entity.hpp>
#include <ecs/SystemManager.hpp>
#include <memory>
#include <queue>
#include <unordered_map>

#include <ProjectConfig.h>

const bool debug = false;

class ECS {
  std::queue<Entity> free_ids;

  std::unordered_map<Entity, Signature> signatures;

  std::shared_ptr<ComponentManager> component_manager =
      std::make_shared<ComponentManager>();
  std::shared_ptr<SystemManager> system_manager =
      std::make_shared<SystemManager>(component_manager);

public:
  Entity num_entities = 0;

  ECS() {
    for (int e = 0; e < MAX_ENTITIES; e++) {
      free_ids.push(e);
    }
  };

  Entity add_entity() {
    Entity id = free_ids.front();
    signatures[id] = 0;
    free_ids.pop();
    return id;
  };

  void remove_entity(Entity id) {
    signatures[id] = 0;
    component_manager->entity_removed(id);
    /*system_manager->entity_changed(id, signatures[id]);*/
    free_ids.push(id);
  };

  template <typename T> bool entity_has_component(Entity ent) {
    return get_signature_for_entity(
               ent)[component_manager->get_signature_index_for_type<T>()] == 1;
  }

  Signature get_signature_for_entity(Entity id) { return signatures[id]; }

  // Components
  template <typename T> void register_component(COMP_SIG idx) {
    component_manager->add_component<T>(idx);
  }

  template <typename T> void add_component_to_entity(Entity id, T data) {
    int sig_index = component_manager->get_signature_index_for_type<T>();
    if (debug) {
      std::cout << "Adding entity " << id << " to component " << sig_index
                << std::endl;
    }
    if (signatures[id][sig_index]) {
      // std::cout << "Entity " << id << " already has " << typeid(T).name()
      //           << std::endl;
    } else {
      component_manager->get_component_array<T>()->add_entity(id, data);
      signatures[id][sig_index] = 1;
      system_manager->entity_changed(id, signatures[id]);
    }

    // std::cout << "Added component " << typeid(T).name() << " to entity " <<
    // id
    //           << " (" << signatures[id] << ")" << std::endl;
  }

  template <typename T> void remove_component_from_entity(Entity id) {
    int sig_index = component_manager->get_signature_index_for_type<T>();

    if (not signatures[id][sig_index]) {
      // std::cout << "Entity " << id << "(" << signatures[id] << ")"
      //           << " does not have " << typeid(T).name()
      //           << ", so it will not be removed" << std::endl;
    } else {
      component_manager->get_component_array<T>()->remove_entity(id);
      signatures[id][sig_index] = 0;
      system_manager->entity_changed(id, signatures[id]);
    }
  }

  template <typename T> T *get_component_for_entity(Entity id) {
    if (!entity_has_component<T>(id)) {
      std::cout << "!!! [" << id
                << "] Attempting to get component I don't have "
                << typeid(T).name() << std::endl;
    }
    return component_manager->get_component_data<T>(id);
  };

  template <typename T>
  std::shared_ptr<ComponentArray<T>> get_component_array() {
    return component_manager->get_component_array<T>();
  }

  // System
  template <typename T>
  std::shared_ptr<T> register_system(Signature signature) {
    return system_manager->add_system<T>(signature);
  };

  template <typename T>
  std::shared_ptr<T> register_system(COMP_SIG *sigs, short num_sigs) {
    Signature sig;
    for (short i = 0; i < num_sigs; i++) {
      sig[sigs[i]] = 1;
    }
    return register_system<T>(sig);
  };

  /** Debug */
  void debug_cout_entity_state(Entity id) {
    Signature ent_sig = get_signature_for_entity(id);
    std::cout << "[" << id << "] " << ent_sig << ": ";
    for (int i = 0; i < MAX_COMPONENTS; i++) {
      if (ent_sig[i]) {
        std::cout << component_manager->get_type_from_index(i).name();
        std::cout << ", ";
      }
    }
    std::cout << std::endl;
    for (int i = 0; i < MAX_COMPONENTS; i++) {
      if (ent_sig[i]) {
        debug_cout_component_state(id, (COMP_SIG)i);
      }
    }
  }

  void debug_cout_component_state(Entity id, COMP_SIG comp_idx) {
    if (get_signature_for_entity(id)[comp_idx] == 0) {
      std::cout << "Entity (" << id << ") does not have component "
                << component_manager->get_type_from_index(comp_idx).name()
                << std::endl;
      return;
    }
    switch (comp_idx) {
    case COMP_SIG::POSITION: {
      Position *p = get_component_for_entity<Position>(id);
      std::cout << "[" << id << "] Position: " << p->x << ", " << p->y
                << std::endl;
      break;
    }
    case COMP_SIG::COLLIDER: {
      Collider *c = get_component_for_entity<Collider>(id);
      std::string col_shape_type;
      switch (c->type) {
      case CollisionShapeType::CIRCLE: {
        col_shape_type = "circle";
        break;
      }
      // case CollisionShapeType::RECT: {
      //   col_shape_type = "rect";
      //   break;
      // }
      default: {
        col_shape_type = "Not in debugger collider print out yet";
        break;
      }
      }
      std::cout << "[" << id << "] Collider: " << col_shape_type << " {";
      if (c->type == CollisionShapeType::CIRCLE) {
        std::cout << c->shape.circle.x << ", " << c->shape.circle.y << ", "
                  << c->shape.circle.radius;
      }
      std::cout << "} - " << c->collision_data.type << std::endl;
      // std::cout << "} - collider at " << c << " - shape at " << &c->shape
      //           << std::endl;
      break;
    }
    default:
      std::cout << comp_idx << " not in debug output yet" << std::endl;
      break;
    }
  }
};
