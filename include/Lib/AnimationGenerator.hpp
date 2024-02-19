#include <SFML/Graphics.hpp>
#include <vector>

class AnimationGenerator {
public:
	static std::vector<sf::IntRect> generate_texture_rects(int sheet_width, int sheet_height, int frame_width, int frame_height);
};


 std::vector<sf::IntRect> AnimationGenerator::generate_texture_rects(int sheet_width, int sheet_height, int frame_width, int frame_height) {
	int sprites_high = sheet_height / frame_height;
	int sprites_wide = sheet_width / frame_width;

	std::vector<sf::IntRect> rects;
	for (int row = 0; row < sprites_high; row++) {
		for (int col = 0; col < sprites_wide; col++) {
			int rect_index = row * sprites_wide + col;
			rects.push_back(sf::IntRect(col * frame_width, row * frame_height, frame_width, frame_height));
		}
	}

	return rects;
}