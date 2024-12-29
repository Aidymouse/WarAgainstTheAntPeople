#include <SFML/Graphics/Texture.hpp>

#include <SFML/System/Vector2.hpp>
#include <data/TextureBank.h>
#include <data/EntityAttributes.h>


#include <entity/Tool.h>
#include <entity/Mallet.h>

Mallet::Mallet() : Tool::Tool(&TextureBank::mallet) {
    sprite.setOrigin({EntityAttributes::Mallet.origin_x, EntityAttributes::Mallet.origin_y});
    sprite.setTextureRect({{0, 0}, {32, 32}});
    x=100; y=100;
    sprite.setPosition({100, 100});
}

CollisionShape Mallet::get_collision_shape() {

    CollisionShape mallet_shape = {
        CollisionShapeType::CIRCLE,
        x,
        y,
        16,
    };

    return mallet_shape;

}

void Mallet::handle_mousemove(sf::Vector2i mouse_pos) {
    x = mouse_pos.x;
    y = mouse_pos.y;

    sprite.setPosition({(float) x, (float) y});
}

void Mallet::handle_click() {}
