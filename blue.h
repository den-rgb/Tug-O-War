#ifndef blue_hpp
#define blue_hpp
#include <SFML/Graphics.hpp>
#include <math.h>       /* atan2 */

using namespace sf;


class Blue {
	friend class Rope;
private:
	float START_SPEED = 100;

	// Where is the player?
	Vector2f m_Position;

	// Player sprite
	Sprite m_Sprite;

	// Player texture
	Texture m_Texture;

	// What is the screen resolution?
	Vector2f m_Resolution;

	bool space_Pressed;
	float* m_Speed;
	Time m_LastPull;
public:
	Blue();
	
	float& getSpeed();
	float setSpeed(float speed);

	
	// How long since player hit?
	Time getLastHitTime();

	// Where is the player?
	FloatRect getPosition();
	// Where is the centre of the player?
	Vector2f getCenter();
	// Which angle is the player facing?
	float getRotation();

	// Send a copy of the sprite to main
	Sprite getSprite();

	void pull(Time& t);
	void stop();

	// Called every frame
	void update(float elapsedTime, bool change, float newSpeed);

	//void upgradeSpeed();

};
#endif 


