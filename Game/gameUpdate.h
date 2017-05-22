#ifndef GAMEUPDATE_H
#define GAMEUPDATE_h
#include "

void updateWholeGame()
{
    
    player.Update(deltaTime);
    sf::Vector2f direction;
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

    if (player.getPosition().y > 1000 || player.end == true) // Game Over
    {

	if (player.end)
	{
	    textTime.restart();
	    player.end = false;
	}
	elapsed = textTime.getElapsedTime();
	text.setString("Game Over");
	text.setCharacterSize(200);
	window.draw(text);

	if (elapsed.asSeconds() >= 3.0)
	{
	    window.close();
	}
    }

}
#endif
