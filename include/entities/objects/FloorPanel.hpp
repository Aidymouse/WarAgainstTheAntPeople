#include <entities/Entity.h>

class FloorPanel : public Entity {
public:
  sf::Sprite sprite;
  std::shared_ptr<sf::Texture> tex;

  sf::Vector3<float> offset;

  int strength = 100;
  float shake_timer = 0;
  float max_shake_timer = 0.2;
  int max_shake_force = 6;

  FloorPanel(float x, float y);
  void update(float dt) override;
  void draw(sf::RenderWindow *window) override;
  void handle_collision(Collision collision) override;
  std::string type() override;
};
