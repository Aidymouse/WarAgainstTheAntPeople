#include <state/GraphicsManager.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

std::map<std::string, std::shared_ptr<sf::Texture>> GraphicsManager::textures;

std::string GraphicsManager::graphics_path =
    (std::string)RESOURCE_PATH + "/graphics";

void GraphicsManager::load_texture(std::string tex_name,
                                   std::string tex_filename) {
  textures[tex_name] = std::make_shared<sf::Texture>();
  textures[tex_name]->loadFromFile(tex_filename);
}

