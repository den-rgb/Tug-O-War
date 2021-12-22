#ifndef drops_hpp
#define drops_hpp
#include <SFML/Graphics.hpp>
#include <math.h>  
#include <SFML/Audio.hpp>

using namespace sf;

class Drops {
private:
	float START_SPEED = 100;
	float* m_Speed;
	Vector2f m_Position;

	//  sprite
	Sprite m_Sprite_BF;
	Sprite m_Sprite_RF;
	Sprite m_Sprite_M;

	//texture
	Texture m_Texture_BF;
	Texture m_Texture_RF;
	Texture m_Texture_M;
	bool hasPickedUp;
	Sound pickup;
	SoundBuffer pickupBuffer;

public:
	int chosen;
	Drops();
	
	Sprite RandSprite();
	Vector2f getCenter();
	int Spawn(Time& t,float elapsedTime,float& redSpeed, bool pickedUp);
	bool Pickup(FloatRect redPos,FloatRect dropPos);

	FloatRect getPosition();

};


#endif
