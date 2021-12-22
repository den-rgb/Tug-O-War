#ifndef red_hpp
#define red_hpp
#include <SFML/Graphics.hpp>
#include <math.h>       /* atan2 */


using namespace sf;

class Red {
	friend class Rope;
private:
	float* m_Speed = 0;
    float START_SPEED =100;

	// Where is the player?
	Vector2f m_Position;

	// Player sprite
	Sprite m_Sprite;

	// Player texture
	Texture m_Texture;

	// What is the screen resolution?
	Vector2f m_Resolution;

	
	
	Time m_LastHit;
public:
	Red();
	//~Red();
	bool space_Pressed;
	
	float& getSpeed();
	float setSpeed(float speed);
	// Where is the player?
	FloatRect getPosition();
	// Where is the centre of the player?
	Vector2f getCenter();
	// Which angle is the player facing?
	float getRotation();

	// Send a copy of the sprite to main
	Sprite getSprite();

	void pull();
	void stop();

	// Called every frame
	void update(float elapsedTime,bool change,float newSpeed);

	//void upgradeSpeed();

};
#endif 
