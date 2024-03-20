#include "Entity.h"

class FloorPanel : public Entity {
public:
  sf::Sprite sprite;
  std::shared_ptr<sf::Texture> tex;

  sf::Vector3<float> offset;

  int strength = 100;
  int shake_timer = 0;
  int shake_force = 0;

  FloorPanel(float x, float y);
  void update(float dt) override;
  void draw(sf::RenderWindow *window) override;
  void say_type() override;
  void handle_collision(Collision collision) override;
};
