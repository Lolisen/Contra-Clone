#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Characters.h"
#include "Enemy.h"
#include "Entity.h"
#include "Player.h"
#include "Platform.h"
#include "Bullet.h"
#include "Boss.h"
#include <fstream>
#include "PowerUp.h"


using namespace std;

int main()
{
    // Init
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Contra", sf::Style::Close | sf::Style::Resize);
    sf::View menuView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1024.0f, 768.0f));
    sf::View gameView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1024.0f, 768.0f));

    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);
    int healthPoints{ 3 };
    vector<sf::Sprite> drawposhp;

        sf::Music music;
        music.openFromFile("music/level1.ogg");
        music.play();

    // Define Textures
    sf::Texture bullet;
    bullet.loadFromFile("images/bullet.png");

    sf::Texture bossBullet;
    bossBullet.loadFromFile("images/bossBullet.png");

    sf::Texture playerTexture;
    playerTexture.loadFromFile("images/playerTexture.png");

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("images/Enemy.png");

    sf::Texture bossTexture;
    bossTexture.loadFromFile("images/Boss.png");

    sf::Texture background;
    background.loadFromFile("images/1.png");

    sf::Texture heart;
    heart.loadFromFile("images/inSovietRussia.png");

    sf::Texture poweruptexture;
    poweruptexture.loadFromFile("images/powerup.png");

    sf::Texture lava;
    lava.loadFromFile("images/lava.png");

    sf::Texture ground1;
    ground1.loadFromFile("images/level1ground.jpg");

    sf::Texture bossGround;
    bossGround.loadFromFile("images/bossplatform.png");

    sf::Texture portal;
    portal.loadFromFile("images/door.png");

    sf::Texture powerupFireRate;
    powerupFireRate.loadFromFile("images/fireRate.png");

    sf::Sprite level1;
    level1.setTexture(background);
    level1.setOrigin(500.0f, 300.0f);

    sf::Sprite door;
    door.setTexture(portal);
    door.setScale(2.5f, 4.0f);
    door.setPosition(4400, 50);

    sf::Sprite health;
    health.setTexture(heart);
    health.setScale(0.5f, 0.5f);

    sf::Text text;
    sf::Font font;
    font.loadFromFile("images/Arial.ttf");

    text.setFont(font);
    text.setString("Run!");
    text.setCharacterSize(100);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::Text startGameText;
    startGameText.setFont(font);
    startGameText.setString("(1) Start Game");
    startGameText.setCharacterSize(25);
    startGameText.setPosition(0, -300);
    startGameText.setFillColor(sf::Color::Red);


    sf::Text viewHighscoreText;
    viewHighscoreText.setFont(font);
    viewHighscoreText.setString("(2) View Highscore");
    viewHighscoreText.setCharacterSize(25);
    viewHighscoreText.setPosition(0, -250);
    viewHighscoreText.setFillColor(sf::Color::Red);


    sf::Text exitGameText;
    exitGameText.setFont(font);
    exitGameText.setString("(3) Exit Game");
    exitGameText.setCharacterSize(25);
    exitGameText.setPosition(0, -200);
    exitGameText.setFillColor(sf::Color::Red);


    sf::Text backToMenuText;
    backToMenuText.setFont(font);
    backToMenuText.setString("(1) Menu");
    backToMenuText.setCharacterSize(25);
    backToMenuText.setPosition(0, -300);
    backToMenuText.setFillColor(sf::Color::Red);


    sf::Text highscoreText;
    highscoreText.setFont(font);
    highscoreText.setCharacterSize(20);
    highscoreText.setPosition(0, -250);
    highscoreText.setFillColor(sf::Color::White);

    startGameText.setOrigin(startGameText.getLocalBounds().left + startGameText.getLocalBounds().width / 2.0f, 0);
    viewHighscoreText.setOrigin(viewHighscoreText.getLocalBounds().left + viewHighscoreText.getLocalBounds().width / 2.0f, 0);
    exitGameText.setOrigin(exitGameText.getLocalBounds().left + exitGameText.getLocalBounds().width / 2.0f, 0);
    backToMenuText.setOrigin(backToMenuText.getLocalBounds().left + backToMenuText.getLocalBounds().width / 2.0f, 0);

    sf::Clock textTime;
    sf::Time elapsed;

    sf::Vector2f distance; //Distance between player and Enemy
    sf::Vector2f bossDistance; //Distance between player and boss

    // Define Objects	
    float setview;
    std::vector<Enemy> enemyArray;
    enemyArray.push_back(Enemy(sf::Vector2f(700, 0), 100, 100, 10, 10, &enemyTexture, sf::Vector2i(3, 4), 0.2f, &bullet));
    enemyArray.push_back(Enemy(sf::Vector2f(1200, 0), 100, 100, 10, 10, &enemyTexture, sf::Vector2i(3, 4), 0.2f, &bullet));
    enemyArray.push_back(Enemy(sf::Vector2f(1500, 0), 100, 100, 10, 10, &enemyTexture, sf::Vector2i(3, 4), 0.2f, &bullet));
    enemyArray.push_back(Enemy(sf::Vector2f(2500, 0), 100, 100, 10, 10, &enemyTexture, sf::Vector2i(3, 4), 0.2f, &bullet));
    enemyArray.push_back(Enemy(sf::Vector2f(2900, 0), 100, 100, 10, 10, &enemyTexture, sf::Vector2i(3, 4), 0.2f, &bullet));
    enemyArray.push_back(Enemy(sf::Vector2f(3500, 0), 100, 100, 10, 10, &enemyTexture, sf::Vector2i(3, 4), 0.2f, &bullet));
    enemyArray.push_back(Enemy(sf::Vector2f(3900, 0), 100, 100, 10, 10, &enemyTexture, sf::Vector2i(3, 4), 0.2f, &bullet));

    Player player(sf::Vector2f(200, -0), 100, 100, 400, 200, &playerTexture, sf::Vector2i(3, 4), 0.2f, &bullet);
    Boss boss(sf::Vector2f(7600, 100), 100, 100, 10, 10, &bossTexture, sf::Vector2i(3, 4), 0.2f, &bossBullet);

    vector<PowerUp> powerups;
    powerups.push_back(PowerUp(&poweruptexture, sf::Vector2f(80.0f, 80.0f), sf::Vector2f(4300, 25), "life"));
    powerups.push_back(PowerUp(&powerupFireRate, sf::Vector2f(80.0f, 80.0f), sf::Vector2f(2000, 25), "fireRate"));

    std::vector<Bullet> bulletVector;

    // Platform Vector Array

    std::vector<Platform> lavaArray;
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(500, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(600, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(700, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(800, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(1000, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(1100, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(1300, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(1400, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(1500, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(1600, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(1700, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(2700, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(2800, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(3200, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(3300, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(3400, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(3000, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(3100, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(4000, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(4100, 400)));
    lavaArray.push_back(Platform(&lava, sf::Vector2f(100.0f, 250.0f), sf::Vector2f(4200, 400)));

	
    std::vector<Platform> platformArray;
    //	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(100, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(200, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(300, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(400, 400)));
    // platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(700, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(900, 400)));
    // platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(1100, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(1200, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(1800, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(1900, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(2000, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(2500, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(2600, 400)));
    //platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(2800, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(2900, 400)));
    //platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(3100, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(3500, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(3600, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(3700, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(3800, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(3900, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(4300, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(4400, 400)));
    platformArray.push_back(Platform(&ground1, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(4500, 400)));

    std::vector<Platform> bossPlatform;
    platformArray.push_back(Platform(&bossGround, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(7000, 400)));
    platformArray.push_back(Platform(&bossGround, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(7100, 400)));
    platformArray.push_back(Platform(&bossGround, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(7200, 400)));
    platformArray.push_back(Platform(&bossGround, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(7300, 400)));
    platformArray.push_back(Platform(&bossGround, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(7400, 400)));
    platformArray.push_back(Platform(&bossGround, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(7500, 400)));
    platformArray.push_back(Platform(&bossGround, sf::Vector2f(100.0f, 300.0f), sf::Vector2f(7600, 400)));

    float deltaTime = 0.0f;
    sf::Clock clock;
    sf::Clock totalClock;
    sf::Time totalTime = sf::seconds(0);

    bool menuScreen{ true };
    bool scoreScreen{ false };
    bool mainGameScreen{ false };
    bool viewHighscore{ false };
    bool writeOnce{ true };

    // Main Game
    while (window.isOpen())
    {
	sf::Event event;
	while (window.pollEvent(event))
	{
	    switch (event.type)
	    {
	    case sf::Event::Closed:
		window.close();
		break;
	    case sf::Event::KeyPressed:
		if (scoreScreen)
		{
		    if (event.key.code == sf::Keyboard::Num1)
		    {
			scoreScreen = false;
			mainGameScreen = false;
			menuScreen = true;
			viewHighscore = false;
		    }
		    break;
		}
		if (menuScreen)
		{
		    window.setView(menuView);
		   
		    if (event.key.code == sf::Keyboard::Num1)
		    {
			scoreScreen = false;
			mainGameScreen = true;
			menuScreen = false;
			break;
		    }
		    if (event.key.code == sf::Keyboard::Num2)
		    {
			scoreScreen = true;
			mainGameScreen = false;
			menuScreen = false;
			break;
		    }
		    if (event.key.code == sf::Keyboard::Num3)
		    {
			window.close();
			break;
		    }
		}
		if (mainGameScreen)
		{
		    if (event.key.code == sf::Keyboard::Escape)
		    {
			scoreScreen = false;
			mainGameScreen = false;
			menuScreen = true;
			break;
		    }
		}
		break;
	    case sf::Event::Resized:
		cout << "New width:  " << event.size.width << endl;
		cout << "New height: " << event.size.height << endl;
		break;
	    case sf::Event::TextEntered:
		if (event.text.unicode < 128) {}
			    //cout << "ASCII chaaracter typed: " << static_cast<char>(event.text.unicode) << endl;
	    }
	    break;
	}

	if (menuScreen)
	{
	    window.clear(sf::Color(0, 0, 0));
	    window.draw(startGameText);
	    window.draw(viewHighscoreText);
	    window.draw(exitGameText);
	    window.setView(menuView);
	    window.display();
	}

	if (scoreScreen)
	{
	    if (!viewHighscore)
	    {
		ifstream fin("Highscore.txt");
		string highscoreStr((istreambuf_iterator<char>(fin)),
				    (istreambuf_iterator<char>()));
		fin.close();
		highscoreText.setString(highscoreStr);
		highscoreText.setOrigin(highscoreText.getLocalBounds().left + highscoreText.getLocalBounds().width / 2.0f, 0);
		viewHighscore = true;
	    }
	    window.clear(sf::Color(0, 0, 0));
	    window.draw(backToMenuText);
	    window.draw(highscoreText);
	    window.setView(menuView);
	    window.display();
	}
	if (mainGameScreen)
	{
	    deltaTime = clock.restart().asSeconds();
	    if (deltaTime > 1.0f / 60.0f)
		deltaTime = 1.0f / 60.0f;

	    //-------------Update---------------
	    player.Update(deltaTime);
	    boss.Update(deltaTime);
	    

	    sf::Vector2f direction;

	    for(Bullet & bullet : player.bulletArray)
	    {
		boss.CheckIfHit(bullet);
	    }

	    for(Platform & platform : platformArray)
	    {
		Collider temp = boss.getCollider();
		if(platform.GetCollider().CheckCollision(temp, direction))
		{
		    boss.onCollision(direction);
		}
	    }


	    for (Enemy & enemy : enemyArray)
	    {
		enemy.Update(deltaTime);
		for (Bullet & bullet : player.bulletArray)
		{
		    enemy.CheckIfHit(bullet);

		}

		for (Bullet & bullet : enemy.bulletArray)
		{
		    player.CheckIfHit(bullet);
		}

		for(Bullet & bullet : boss.bulletArray)
		{
		    player.CheckIfHit(bullet);
		}

		for (PowerUp & powerup : powerups)
		{
		    if(player.CheckIfOnPowerUp(powerup) && powerup.name == "life")
		    {
			powerup.body.setPosition(0,1000.0f);
			player.lives++;
		    }

		    if(player.CheckIfOnPowerUp(powerup) && powerup.name == "fireRate")
		    {
			powerup.body.setPosition(0,1000.0f);
			player.reloadTime0 = player.reloadTime0 / 2;
		    }
		}


		for (Platform & platform : platformArray)
		{
		    Collider temp = enemy.GetCollider();
		    if (platform.GetCollider().CheckCollision(temp, direction))
		    {
			enemy.OnCollision(direction);
		    }
		}

		for (Platform & platform : lavaArray)
		{
		    Collider temp2 = enemy.GetCollider();
		    if (platform.GetCollider().CheckCollision(temp2, direction))
		    {
			enemy.OnCollision(direction);
		    }
		}
	    

		distance.x = abs(enemy.getPosition().x - player.getPosition().x);
		distance.y = abs(enemy.getPosition().y - player.getPosition().y);
		enemy.Intelligence(distance);

	    }  
  
	    for (Platform & platform : platformArray)
	    {
		Collider temp = player.GetCollider();
		if (platform.GetCollider().CheckCollision(temp, direction))
		{
		    player.OnCollision(direction);
		}
	    }

	    for (Platform & platform : bossPlatform)
	    {
		Collider temp = player.GetCollider();
		if (platform.GetCollider().CheckCollision(temp, direction))
		{
		    player.OnCollision(direction);
		}
	    }

	    

	    for(Platform& platform : lavaArray)
	    {
		Collider temp2 = player.GetCollider();
		if (platform.GetCollider().CheckCollision(temp2, direction))
		{
		    if(player.lives <= 0)
		    {
			player.end = true;
		    }
		    else
		    {
			player.lives--;
			player.body.setPosition(100, 100);
		    }

		}
	    }
	    if(player.getPosition().x >= 4400 && player.getPosition().x < 5000)
	    {
		player.body.setPosition(7000, 200);
	    }
	    else if(player.getPosition().x >= 7000)
	    {
		player.atBoss = true;
		boss.bossActivated = true;
		boss.bossIntelligence(bossDistance);
	    }

	    bossDistance.x = abs(boss.getPosition().x - player.getPosition().x);
	    bossDistance.y = abs(boss.getPosition().y - player.getPosition().y);

	    if (player.lives == 0) // Game Over
	    {
		player.end = true;

		if (player.end)
		{
		    textTime.restart();
		    player.end = false;
		}
		elapsed = textTime.getElapsedTime();
		text.setString("Game Over");
		text.setCharacterSize(100);
		window.draw(text);

		if (elapsed.asSeconds() >= 3.0)
		{
		    window.close();
		}
	    }
	    
	    totalTime = totalClock.getElapsedTime();
	    if (boss.lives == 0)
	    {
		if (writeOnce)
		{
		    ofstream fout;
		    fout.open ("Highscore.txt", std::ios_base::app);
		    fout << totalTime.asSeconds() << endl;
		    cout << totalTime.asSeconds() << endl;
		    fout.close();
		    text.setPosition(player.getPosition().x - 300 , player.getPosition().y - 250);
		    text.setString("Victory");
		    text.setCharacterSize(200);
		    window.draw(text);
		    writeOnce = false;
		}
	    }
	    else
	    {
		//-------------View-----------------
		setview = player.getPosition().x;
		if (player.getPosition().x < 15)
		    setview = 15;
		gameView.setCenter(setview, 85);
		window.setView(gameView);
		//-------------Clear----------------
		window.clear(sf::Color(200, 0, 0));
		//-------------Draw-----------------
		window.draw(level1);
		for (PowerUp& powerup : powerups)
		    powerup.Draw(window);
		window.draw(door);
		boss.Draw(window);
		elapsed = textTime.getElapsedTime();

		if (elapsed.asSeconds() < 3.0)
		    window.draw(text);

		for (Enemy& enemy : enemyArray)
		    enemy.Draw(window);

		for(Platform& platform : lavaArray)
		    platform.Draw(window);

		player.Draw(window);

		for (Platform& platform : platformArray)
		    platform.Draw(window);

		float currentPos{ player.getPosition().x };
		if (player.getPosition().x < 15)
		    currentPos = 15;
		int tempHealthPos = currentPos - 512;
		for (int i{ 0 }; i < player.lives; i++)
		{
		    health.setPosition(tempHealthPos + (i * 70), -300);
		    drawposhp.push_back(health);
		}

		for (sf::Sprite& health : drawposhp)
		{
		    window.draw(health);

		}
		drawposhp.erase(drawposhp.begin(), drawposhp.end());

	    }
	    window.display();
	}
    
    }
    window.close();
    music.stop();

    return 0;
}


