#include "blue.h"
#include "textureHolder.h"
#include <iostream>


Blue::Blue() {

	m_Speed = &START_SPEED;
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/blueMan.png"));
	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(-550, -200);
	m_Sprite.setScale(-3, 3);

}



FloatRect Blue::getPosition() {
	return m_Sprite.getGlobalBounds();
}

Vector2f Blue::getCenter() {
	return m_Position;
}

float Blue::getRotation() {
	return m_Sprite.getRotation();
}

Sprite Blue::getSprite() {
	return m_Sprite;
}



void Blue::stop() {
	space_Pressed = false;
}

float& Blue::getSpeed() {
	return *m_Speed;
}
float Blue::setSpeed(float speed) {
	return *m_Speed += speed;
}


void Blue::pull(Time& t) {
	
	if (t.asMilliseconds() - m_LastPull.asMilliseconds() > 200) {
		setSpeed(1);
		//std::cout << "\nspeed " << getSpeed();
		m_LastPull = t;
	}
	
}
void Blue::update(float elapsedTime, bool change, float newSpeed) {
	
	
	if (change) {
		m_Position.x -= getSpeed() * elapsedTime;
	}
	else {
		m_Position.x += newSpeed * elapsedTime;
	}
	m_Sprite.setPosition(m_Position.x - 600, m_Position.y-200);
}
