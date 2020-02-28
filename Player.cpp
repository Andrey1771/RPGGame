#include "Player.h"

extern float mainTime;
extern double speedAnimation;
Player::Player(sf::View& view, sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed, double attackTime):Hero(ImageFile, ImageFileAttack, maxFrameX, maxFrameY, maxFrameAttackX, maxFrameAttackY, x, y, speed, attackTime)
{
	//sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed, double attackTime)

	camera = &view;
}
Player::~Player()
{

}
bool Player::moveHero(sf::Event event)
{
	if (event.type == sf::Event::EventType::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W)
			dy = 0;
		if (event.key.code == sf::Keyboard::S)
			dy = 0;
		if (event.key.code == sf::Keyboard::A)
			dx = 0;
		if (event.key.code == sf::Keyboard::D)
			dx = 0;
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			move(-speed * mainTime / sqrt(2), -speed * mainTime / sqrt(2));
			y -= speed * mainTime / sqrt(2);
			x -= speed * mainTime / sqrt(2);

			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
				animation(3);

			dx = -speed * mainTime / sqrt(2);
			dy = -speed * mainTime / sqrt(2);

			setCoordinationCamera(0, 0, 40 * 64, 64 * 25);
			return true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			move(speed * mainTime / sqrt(2), -speed * mainTime / sqrt(2));
			y -= speed * mainTime / sqrt(2);
			x += speed * mainTime / sqrt(2);

			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
				animation(3);

			dx = speed * mainTime / sqrt(2);
			dy = -speed * mainTime / sqrt(2);

			setCoordinationCamera(0, 0, 40 * 64, 64 * 25);
			return true;
		}

		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			animation(3);
		move(0, -speed * mainTime);
		y -= speed * mainTime;

		dy = -speed * mainTime;

		setCoordinationCamera(0, 0, 40 * 64, 64 * 25);
		return true;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{

			move(-speed * mainTime / sqrt(2), speed * mainTime / sqrt(2));
			y += speed * mainTime / sqrt(2);
			x -= speed * mainTime / sqrt(2);

			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
				animation(4);

			dx = -speed * mainTime / sqrt(2);
			dy = speed * mainTime / sqrt(2);

			setCoordinationCamera(0, 0, 40 * 64, 64 * 25);
			return true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			move(speed * mainTime / sqrt(2), speed * mainTime / sqrt(2));
			y += speed * mainTime / sqrt(2);
			x += speed * mainTime / sqrt(2);

			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
				animation(4);

			dx = speed * mainTime / sqrt(2);
			dy = speed * mainTime / sqrt(2);

			setCoordinationCamera(0, 0, 40 * 64, 64 * 25);
			return true;

		}

		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			animation(4);
		move(0, speed * mainTime);
		y += speed * mainTime;

		dy = speed * mainTime;

		setCoordinationCamera(0, 0, 40 * 64, 64 * 25);
		return true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{

		move(-speed * mainTime, 0);
		x -= speed * mainTime;
		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			animation(1);
		dx = -speed * mainTime;

		setCoordinationCamera(0, 0, 40 * 64, 64 * 25);
		return true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move(speed * mainTime, 0);
		x += speed * mainTime;

		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			animation(2);
		dx = speed * mainTime;

		setCoordinationCamera(0, 0, 40 * 64, 64 * 25);
		return true;
	}

	return false;
}
void Player::attackHero(sf::Event event, bool ok)
{

	//if(dx < 0)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		animation(8);//8 - attack left
		return;
	}
	//if (dx > 0)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		animation(9);//9 - attack right
		return;
	}
	//if (dy > 0)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		animation(10);//10 - attack up
		return;
	}
	//if (dy <= 0)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		animation(7);//7 - attack down
		return;
	}

	if (event.type == sf::Event::EventType::KeyReleased && !ok)
	{
		animation(5);
		return;
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (dx > 0)
			animation(9);//9 - attack right
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if(dy > 0)
			animation(10);//10 - attack up
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if(dy <= 0)
			animation(7);//7 - attack down
		return;
	}*/
}

void Player::update(sf::Event event)
{
	attackHero(event, moveHero(event));
}

void Player::setCoordinationCamera(float x0, float y0, float width, float height)
{
	float lastX = camera->getCenter().x, lastY = camera->getCenter().y;

	
	camera->setCenter(movementTexture.sprite->getPosition().x + movementTexture.sprite->getTextureRect().width/2.0, movementTexture.sprite->getPosition().y + movementTexture.sprite->getTextureRect().height/2.0);
	 
	if (camera->getCenter().x - camera->getSize().x / 2 < x0 || camera->getCenter().x + camera->getSize().x / 2 > x0 + width)
	{
		camera->setCenter(lastX, camera->getCenter().y);
	}
	if (camera->getCenter().y - camera->getSize().y / 2 < y0 || camera->getCenter().y + camera->getSize().y / 2 > y0 + height)
	{
		camera->setCenter(camera->getCenter().x, lastY);
	}
}

void Player::animation(int direction)// 1 - left, 2 - right, 3 - up, 4 - down
{
	Hero::animation(direction);
}
