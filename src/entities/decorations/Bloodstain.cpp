#include <entities/Decorations/Bloodstain.hpp>
#include <helper/AnimationGenerator.hpp>

const std::vector<sf::IntRect> bloodstain_rects = AnimationGenerator::generate_texture_rects(116, 16, 16, 16);

struct {
  animation splat1{bloodstain_rects[1], 0.05, &splat2, 8, 8};
  animation splat2{bloodstain_rects[2], 0.05, &splat3, 8, 8};
  animation splat3{bloodstain_rects[3], 0.05, &splat4, 8, 8};
  animation splat4{bloodstain_rects[4], 0.05, &splat5, 8, 8};
  animation splat5{bloodstain_rects[5], 0.05, &splat6, 8, 8};
  animation splat6{bloodstain_rects[6], 0.05, NULL, 8, 8};
} bloodstain_anims;

Bloodstain::Bloodstain(float x, float y) : Entity::Entity(x, y) {
  decoration = true;

  tex.loadFromFile((std::string)RESOURCE_PATH + "graphics/squish.png");
  sprite.setTexture(tex);
  sprite.setPosition(x, y);

  init_animation(&(bloodstain_anims.splat1));

  ellipse = sf::CircleShape(5.0f);
  ellipse.setScale(1, 0.5);
  ellipse.setFillColor(sf::Color(255, 0, 0));
  ellipse.setPosition(pos.x, pos.y);
}

void Bloodstain::update(float dt) { update_animation(dt); }

void Bloodstain::draw(sf::RenderWindow *window) { window->draw(sprite); }
