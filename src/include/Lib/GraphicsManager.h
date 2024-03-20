#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

#pragma once
class GraphicsManager {
public:
  static std::map<std::string, std::shared_ptr<sf::Texture>> textures;

  static std::string graphics_path;
  static void load_texture(std::string tex_name, std::string tex_filename);
};
