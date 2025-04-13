#pragma once

#include <ecs/Entity.hpp>
#include <iostream>
#include <unordered_map>
//#include <memory>

class ComponentArrayInterface {
public:
  virtual ~ComponentArrayInterface() = default;
  virtual void entity_destroyed(Entity id) = 0;
};

template <typename T> class ComponentArray : public ComponentArrayInterface {
  T components[MAX_ENTITIES];
  int num_components = 0;
  std::unordered_map<Entity, int> entity_to_component_idx;
  std::unordered_map<int, Entity> component_idx_to_entity;

public:
  void add_entity(Entity id, T data) {
    // std::cout << "Adding entity (" << id << ") data to spot " <<
    // num_components << std::endl;

    entity_to_component_idx[id] = num_components;
    component_idx_to_entity[num_components] = id;

    components[num_components] = data;

    num_components++;
  };

  void remove_entity(Entity id) {
    int old_component_idx = entity_to_component_idx[id];
    // std::cout << "Removing entity (" << id << ") data from spot " <<
    // old_component_idx << std::endl;

    components[old_component_idx] = components[num_components - 1];

    // Entity swap_entity = component_idx_to_entity[num_components-1]; // When
    // an entity is destroyed, the latest entity becomes the one that was just
    // destroyed
    entity_to_component_idx[id] = old_component_idx;
    component_idx_to_entity[old_component_idx] = id;

    num_components--;
  };

  T *get_data(Entity id) {
    // std::cout << "Getting Entity (" << id << ") data from spot " <<
    // entity_to_component_idx[id] << std::endl;
    return &components[entity_to_component_idx[id]];
  }

  T *get_editable_data(Entity id) {
    // std::cout << "Getting Entity (" << id << ") data from spot " <<
    // entity_to_component_idx[id] << std::endl;
    return &components[entity_to_component_idx[id]];
  }

  T get_data_from_idx(int idx) { return components[idx]; }

  int get_num_components() { return num_components; }

  int get_entity_from_idx(int i) { return component_idx_to_entity[i]; }

  void print_carray() {
    std::cout << "Num of components: " << num_components << std::endl;
    for (int i = 0; i < num_components; i++) {
      std::cout << "Component " << i << " (entity "
                << component_idx_to_entity[i] << ")" << std::endl;
    }
  }

  void entity_destroyed(Entity id) override { remove_entity(id); }
};
