#include <SFML/Graphics/Texture.hpp>

#include <data/TextureBank.h>
#include <data/EntityAttributes.h>


#include <entity/Tool.h>
#include <entity/Mallet.h>

Mallet::Mallet() : Tool::Tool(&TextureBank::mallet) {
    sprite.setOrigin({EntityAttributes::Mallet.origin_x, EntityAttributes::Mallet.origin_y});
    sprite.setTextureRect({{0, 0}, {32, 32}});
    sprite.setPosition({100, 100});
}

