#include "red.h"
#include "textureHolder.h"
#include <iostream>

Red::Red() {

	m_Speed = &START_SPEED;
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/redMan.png"));
	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(1400, 800);
	m_Sprite.setScale(3,3);
}




FloatRect Red::getPosition() {
	return m_Sprite.getGlobalBounds();
}

Vector2f Red::getCenter() {
	return m_Position;
}

float Red::getRotation() {
	return m_Sprite.getRotation();
}

Sprite Red::getSprite() {
	return m_Sprite;
}

float& Red::getSpeed() {
	return *m_Speed;
}

float Red::setSpeed(float speed) {

	return *m_Speed += speed;
}

void Red::pull() {
	space_Pressed = true;
}



void Red::stop() {
	space_Pressed = false;
}

void Red::update(float elapsedTime,bool change,float newSpeed) {

	
	if (change) {
		m_Position.x -= newSpeed * elapsedTime;
	}
	else {
		m_Position.x += getSpeed() * elapsedTime;
	}
	m_Sprite.setPosition(m_Position.x-50,m_Position.y-200);
}