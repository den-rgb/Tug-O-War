#include "rope.h"
#include "textureHolder.h"
#include "red.h"
#include "blue.h"
#include <iostream>

Rope::Rope() {
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/rope.png"));
	m_Sprite.setPosition(-1850, -25);
	m_Sprite.setScale(8, 1.5);
}

FloatRect Rope::getPosition() {
	return m_Sprite.getGlobalBounds();
}

Vector2f Rope::getCenter() {
	return m_Position;
}

float Rope::getRotation() {
	return m_Sprite.getRotation();
}

Sprite Rope::getSprite() {
	return m_Sprite;
}

int Rope::Win(int i) {
	if (getCenter().x >160) {
		i = 1;
		return i;
	}

	if (getCenter().x < -210) {
		i = 2;
		return i;
	}
}

int& Rope::Score(int& score, bool isDoubled) {
	int* addedScore;
	addedScore = &score;
	if(getCenter().x<0&&getCenter().x>-50){
		if (isDoubled) *addedScore += 20;
		else *addedScore += 10;
	}
	else if (getCenter().x < 50 && getCenter().x > -100) {
		if (isDoubled) *addedScore += 10;
		else *addedScore += 5;
	}
	else if (getCenter().x <200  && getCenter().x > -210) {
		if (isDoubled) *addedScore +=4;
		else *addedScore += 2;
	}
	//std::cout <<"\n" <<score;
	return score;
}




void Rope::update(float elapsedTime,float& redSpeed,float& blueSpeed,bool isPressed) {	
	
	
	if (redSpeed != 0 && redSpeed > blueSpeed) {
		m_Position.x += redSpeed * elapsedTime;
		
		//std::cout << "rSpeed " << redSpeed;
	}

	if (blueSpeed != 0 && blueSpeed > redSpeed) {
		m_Position.x -= blueSpeed * elapsedTime;
		
		//std::cout << "bSpeed\n " << blueSpeed;
	}

	
	

	
	

	m_Sprite.setPosition(m_Position.x - 1800,m_Position.y - 225);
}

