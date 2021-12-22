#ifndef rope_hpp
#define rope_hpp
#include <SFML/Graphics.hpp>
#include <math.h>       /* atan2 */


using namespace sf;

class Rope {
	
private:
	Vector2f m_Position;

	// Player sprite
	Sprite m_Sprite;

	// Player texture
	Texture m_Texture;
public:

	Rope();
	FloatRect getPosition();
	// Where is the centre of the player?
	int& Score(int& score,bool isDoubled);
	
	Vector2f getCenter();
	// Which angle is the player facing?
	float getRotation();
	int Win(int i);
	// Send a copy of the sprite to main
	Sprite getSprite();
	void update(float elapsedTime,float& redSpeed,float& blueSpeed,bool isPressed);
};

#endif
