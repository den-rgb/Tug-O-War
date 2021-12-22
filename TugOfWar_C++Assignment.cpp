#include <iostream>
#include <sstream>
#include "textureHolder.h"
#include "red.h"
#include "rope.h"
#include "blue.h"
#include "drops.h"
#include <SFML/Audio.hpp>
using namespace std;

int main()
{

	TextureHolder holder;
	




	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	RenderWindow window(VideoMode(resolution.x, resolution.y), "Tug Of War", Style::Default);
	
	// Create an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	// Clock for timing everything
	Clock clock;
	Clock timer;
	// How long has the PLAYING state been active?
	Time gameTimeTotal;
	
	Rope rope;
	Drops drops;
	Blue blue;
	
	// Create an instance of the Player class
	Red red;
	Vector2f redPosition(red.getCenter());
	
	

	// Make the view centre around the player 
	mainView.setCenter(redPosition.x-300,redPosition.y-200);
	//background
	Texture textureBackground = TextureHolder::GetTexture("graphics/background2.png");
	Sprite background;
	background.setTexture(textureBackground);
	background.setOrigin(resolution.x, resolution.y);
	background.setScale(-2.7, 2);
	background.setPosition(-4525,1200);
	
	//multiplierSprite
	Texture textureMulti = TextureHolder::GetTexture("graphics/multiplier.png");
	Sprite multi;
	multi.setTexture(textureMulti);
	multi.setOrigin(25, 25);
	multi.setScale(0.035, 0.035);
	multi.setPosition(800, -1000);

	//flags
	Texture redFlag= TextureHolder::GetTexture("graphics/redflag.png");
	Sprite rFlag;
	rFlag.setTexture(redFlag);
	rFlag.setOrigin(0, 0);
	rFlag.setScale(0.2, 0.2);
	rFlag.setPosition(red.getCenter().x-260, red.getCenter().y-550);

	Texture blueFlag = TextureHolder::GetTexture("graphics/blueflag.png");
	Sprite bFlag;
	bFlag.setTexture(blueFlag);
	bFlag.setOrigin(0, 0);
	bFlag.setScale(-0.2, 0.2);
	bFlag.setPosition(blue.getCenter().x - 350, blue.getCenter().y - 550);

	//pointAreas
	Texture greenArea = TextureHolder::GetTexture("graphics/green.png");
	Sprite gArea;
	gArea.setTexture(greenArea);
	gArea.setOrigin(0, 0);
	gArea.setScale(4, 9);
	gArea.setPosition(-495, -1075);

	Texture yellowArea = TextureHolder::GetTexture("graphics/yellow.png");
	Sprite yArea;
	yArea.setTexture(yellowArea);
	yArea.setOrigin(0, 0);
	yArea.setScale(6, 9);
	yArea.setPosition(-639, -1075);

	Sprite yArea2;
	yArea2.setTexture(yellowArea);
	yArea2.setOrigin(0, 0);
	yArea2.setScale(6, 9);
	yArea2.setPosition(-539, -1075);

	Texture redArea = TextureHolder::GetTexture("graphics/red.png");
	Sprite rArea;
	rArea.setTexture(redArea);
	rArea.setOrigin(0, 0);
	rArea.setScale(8, 9);
	rArea.setPosition(-802, -1075);

	Sprite rArea2;
	rArea2.setTexture(redArea);
	rArea2.setOrigin(0, 0);
	rArea2.setScale(8, 9);
	rArea2.setPosition(-563, -1075);

	enum class State { PAUSED, GAME_OVER, PLAYING,START ,DISPLAY};

	State state = State::START;

	
	bool acceptInput = false;

	Text messageText;
	Text instruction1;
	Text hint;
	Text plus10;
	Text plus5;
	Text plus52;
	Text plus2;
	Text plus22;
	
	plus22.setFillColor(Color::White);
	plus2.setFillColor(Color::White);
	plus10.setFillColor(Color::White);
	plus52.setFillColor(Color::White);
	plus5.setFillColor(Color::White);
	messageText.setFillColor(Color::White);
	instruction1.setFillColor(Color::White);
	hint.setFillColor(Color::Black);
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	// Set font for message
	plus22.setFont(font);
	plus2.setFont(font);
	plus10.setFont(font);
	plus52.setFont(font);
	plus5.setFont(font);
	messageText.setFont(font);
	instruction1.setFont(font);
	hint.setFont(font);
	FloatRect textRect = messageText.getLocalBounds();
	FloatRect plus10Rect = plus10.getLocalBounds();
	plus2.setOrigin(plus10Rect.left + plus10Rect.width / 2.0f,
		plus10Rect.top + plus10Rect.height / 2.0f);
	plus22.setOrigin(plus10Rect.left + plus10Rect.width / 2.0f,
		plus10Rect.top + plus10Rect.height / 2.0f);
	plus5.setOrigin(plus10Rect.left + plus10Rect.width / 2.0f,
		plus10Rect.top + plus10Rect.height / 2.0f);
	plus52.setOrigin(plus10Rect.left + plus10Rect.width / 2.0f,
		plus10Rect.top + plus10Rect.height / 2.0f);
	plus10.setOrigin(plus10Rect.left + plus10Rect.width / 2.0f,
		plus10Rect.top + plus10Rect.height / 2.0f);
	messageText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	instruction1.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	hint.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	instruction1.setString("Press Enter To Start!!!");
	instruction1.setPosition(-650, -300);
	instruction1.setCharacterSize(50);


	hint.setString("Hints:\nPress Space as fast as you can!!\n\nTry keep the rope in the\n middle for a higher \nscore!!");
	hint.setPosition(-1200, -100);
	hint.setCharacterSize(30);

	plus10.setString("+10");
	plus10.setPosition(-323, -600);
	plus10.setCharacterSize(20);

	plus52.setString("+5");
	plus52.setPosition(-370, -650);
	plus52.setCharacterSize(25);

	plus5.setString("+5");
	plus5.setPosition(-270, -650);
	plus5.setCharacterSize(25);

	plus22.setString("+2");
	plus22.setPosition(-450, -700);
	plus22.setCharacterSize(30);

	plus2.setString("+2");
	plus2.setPosition(-200, -700);
	plus2.setCharacterSize(30);
		
		
	int hasWon = 0;
	
	int score = 0;

	

	Time timerTime;
	bool doubler=false;

	while (window.isOpen()) {

		Time dt = clock.restart();
		

		// Update the total game time
		gameTimeTotal += dt;

		// Make a decimal fraction of 1 from the delta time
		float dtAsSeconds = dt.asSeconds();

		Event event;

		while (window.pollEvent(event)) {

			if (event.type == Event::KeyReleased) {
				//Listen for key presses again
				acceptInput = true;
			}

			if (event.type == Event::KeyPressed) {
				// Pause game while playing
				if (event.key.code == Keyboard::Return && state == State::PLAYING) {
					state = State::PAUSED;
					
				}
				else if (event.key.code == Keyboard::Return && state == State::START) {
					state = State::PLAYING;

					// Reset the clock so there isn't a frame jump
					clock.restart();
				}
				// Restart while paused
				else if (event.key.code == Keyboard::Return && state == State::PAUSED) {
					state = State::PLAYING;

					// Reset the clock so there isn't a frame jump
					clock.restart();
				}
				
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (state == State::PLAYING) {
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				if (acceptInput) {
					red.setSpeed(1);
					rope.Score(score,doubler);
					stringstream ss;
					ss << score;
					messageText.setString(ss.str());
					
					//cout << "\n"<<red.getSpeed();
					acceptInput = false;
				}
			}
			else {
				red.stop();
			}
			
			blue.pull(gameTimeTotal);

			if (rope.Win(hasWon) == 1) {
				messageText.setString("Red Won!");
				state = State::GAME_OVER;
			}
			else if(rope.Win(hasWon) == 2) {
				messageText.setString("Blue Won!");
				state = State::GAME_OVER; 
			}
			
			
			

			Time tdt=timer.restart();
			timerTime += tdt;
			float timerTimeasSec = timerTime.asSeconds();
			float timerAsSec = tdt.asSeconds();
			//cout << timerTime.asSeconds()<< "\n";
			/*if (drops.Pickup(red.getPosition(), drops.getPosition())) {
				cout << "yes";
				timerTime = timer.restart();
			}*/
			
			int x=drops.Spawn(gameTimeTotal, dtAsSeconds, red.getSpeed(), drops.Pickup(red.getPosition(), drops.getPosition()));
			
			
			if (x == 0) {
				timerTime = timer.restart();

				if (timerTimeasSec < 1) {
					blue.setSpeed(2);
					//cout << "\ntimer: " << timerTimeasSec << "\n";
					
				}
				
			}
			if (x == 1) {
				timerTime = timer.restart();

				if (timerTimeasSec < 1) {
					red.setSpeed(2);
					//cout << "\ntimer1: " << timerTimeasSec << "\n";
					
				}
				
			}
			if (x == 2) {
				timerTime = timer.restart();

				if (timerTimeasSec < 1) {
					doubler = true;
					multi.setPosition(550, -625);
					//cout << "timer2: " << timerTimeasSec << "\n";
				}
			}

			if (timerTimeasSec > 3 && doubler) {
				cout << "off2";
				multi.setPosition(800, -1000);
				doubler = false;
			}
			//cout << "timer2: " << timerTimeasSec << "\n";
			cout << doubler ;
			//cout<<"\nspeed: "<<blue.getSpeed();
			rope.update(dtAsSeconds, red.getSpeed(), blue.getSpeed(), red.space_Pressed);


			bool changeDir = false;

			if (blue.getSpeed() > red.getSpeed()) {
				changeDir = true;
				red.update(dtAsSeconds, changeDir, blue.getSpeed());
				blue.update(dtAsSeconds, changeDir, red.getSpeed());
			}

			if (blue.getSpeed() < red.getSpeed()) {
				changeDir = false;
				red.update(dtAsSeconds, changeDir, blue.getSpeed());
				blue.update(dtAsSeconds, changeDir, red.getSpeed());
			}
		}


		if (state ==State::START) {
			window.clear();
			window.setView(mainView);
			window.draw(background);
			messageText.setString("START GAME!");
			messageText.setPosition(-900, -500);
			messageText.setCharacterSize(200);
			window.draw(messageText);
			window.draw(instruction1);
			window.draw(hint);
			messageText.setString("");
			}
			
		if (state == State::GAME_OVER) {
			messageText.setPosition(-650, -300);
			messageText.setCharacterSize(200);
			window.draw(messageText);
		}

		
			if (state == State::PLAYING) {
				window.clear();
				window.setView(mainView);
				window.draw(background);
				window.draw(gArea);
				window.draw(yArea);
				window.draw(yArea2);
				window.draw(rArea);
				window.draw(rArea2);
				window.draw(rFlag);
				window.draw(bFlag);
				window.draw(multi);
				window.draw(plus10);
				window.draw(plus52);
				window.draw(plus5);
				window.draw(plus2);
				window.draw(plus22);
				window.draw(blue.getSprite());
				window.draw(red.getSprite());
				messageText.setPosition(500, -700);
				messageText.setCharacterSize(50);
				window.draw(messageText);
				window.draw(rope.getSprite());
				window.draw(drops.RandSprite());
				
			}
			else if(state == State::PAUSED) {
				messageText.setString("Paused");
				messageText.setPosition(-650, -300);
				messageText.setCharacterSize(200);
				window.draw(messageText);
			}


			
			
				// Draw our message
			
			
			
			
			window.display();
		
	}
	return 0;

}

