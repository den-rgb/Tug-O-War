#include "drops.h"
#include "textureHolder.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "red.h"
#include "rope.h"


Drops::Drops(){
	m_Speed = &START_SPEED;
	chosen = 0;
	m_Sprite_BF = Sprite(TextureHolder::GetTexture("graphics/blueFist.png"));
	m_Sprite_BF.setOrigin(25, 25);
	m_Sprite_BF.setScale(0.05, 0.05);
	m_Sprite_BF.setPosition(0, -1000);
	

	m_Sprite_RF = Sprite(TextureHolder::GetTexture("graphics/redFist.png"));
	m_Sprite_RF.setOrigin(25, 25);
	m_Sprite_RF.setScale(0.05, 0.05);
	m_Sprite_RF.setPosition(0, -1000);

	m_Sprite_M = Sprite(TextureHolder::GetTexture("graphics/multiplier.png"));
	m_Sprite_M.setOrigin(25, 25);
	m_Sprite_M.setScale(0.05, 0.05);
	m_Sprite_M.setPosition(0, -1000);
	hasPickedUp = false;
	

	pickupBuffer.loadFromFile("sound/pickup.ogg");

	

	pickup.setBuffer(pickupBuffer);
}



Sprite Drops::RandSprite() {
	
	Sprite chosenSprite;
	//int chosen = rand() % 3;
	if (chosen == 0) {
		chosenSprite = m_Sprite_BF;

	}
	if (chosen == 1) {
		chosenSprite = m_Sprite_RF;
	}
	if (chosen == 2) {
		chosenSprite = m_Sprite_M;
	}
	//RandSprite().setPosition(0, m_Position.y);

	return chosenSprite;
}

int Drops::Spawn(Time& t,float elapsedTime,float& redSpeed,bool pickedUp) {
	
	srand(time(NULL));
	Time startSpawn;
	Time despawnTime;
	float point = rand()%150-150;

	
	bool startDespawn=false;

	if (t.asSeconds() - startSpawn.asSeconds()> 10) {
		
		//std::cout << startSpawn.asMilliseconds();
		
		m_Position.y += *m_Speed * elapsedTime;
		m_Sprite_BF.setPosition(point, m_Position.y);
		m_Sprite_RF.setPosition(point, m_Position.y);
		m_Sprite_M.setPosition(point, m_Position.y);

		if (m_Position.y >= -200) {

			m_Position.y -= *m_Speed * elapsedTime;
			startDespawn = true;
			if (startDespawn) {
				if (t.asSeconds() - despawnTime.asSeconds() > 5) {
					m_Position.y = -1000;
					startDespawn = false;
					
					despawnTime = t;
					startSpawn = t;
					if (!startDespawn) {
						chosen++;
						if (chosen > 2) chosen = 0;
					}
					
					return 3;
				}
				
			}
		}if (pickedUp) {
			//std::cout << "picked";
			m_Position.y = -1000;
			startDespawn = false;
			despawnTime = t;
			startSpawn = t;
			pickedUp = false;
			int chosenNum;
   			if (chosen == 0) {
				
				chosen++;
				chosenNum = 2;
				
			}
			else if (chosen == 1) {
				
				chosen++;
				chosenNum = 0;
				
			}
			else if (chosen == 2) {
				
				chosen=0;
				chosenNum = 1;
				
			}

			return chosenNum;
			
		}
	}
	return 3;
}




FloatRect Drops::getPosition() {
	return m_Sprite_RF.getGlobalBounds();
}



bool Drops::Pickup(FloatRect redPos,FloatRect dropPos) {
	Red r;
	redPos.height = redPos.height - 100;
	redPos.top = redPos.top + 50;
	redPos.width = redPos.width- 280;
	redPos.left = redPos.left + 160;
	dropPos.height = dropPos.height -88;
	//std::cout << "height: " << redPos.height << "width: " << redPos.width<<"\n";
	//std::cout << "height: " << dropPos.height << "width: " << dropPos.width<<"\n";
	//dropPos.width = dropPos.width - 20;
	if (redPos.intersects(dropPos)) {
		//std::cout << "t\n";
		pickup.play();
		return true;
		
	}
	else {
		//std::cout << "f";
		return false;
	}

	//if (r.getPosition().intersects(getPosition())) {
		//std::cout << "gotit";
	//}
}


Vector2f Drops::getCenter() {
	return m_Position;
}