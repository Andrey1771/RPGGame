#include "Map.h"
#include <vector>
Map::Map(const sf::String& ImageFolder, int heightMap, int widthMap, int amountTiledsMap)
{
	this->image.loadFromFile(ImageFolder);
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);

	this->heightMap = heightMap;
	this->widthMap = widthMap;
	tieldsSettings(amountTiledsMap);
	//std::vector<std::vector<std::string>> mapMassive;
	//mapMassive.push_back()
}
Map::~Map()
{

}

bool Map::setPosBG(int w, int h)
{
	//this->sprite.setPosition(w - image.getSize().x / 2, h - image.getSize().y / 2);
	this->sprite.setPosition(w - 8192 / 2, h - 4096 / 2);
	return true;
}

void Map::loadLevel(const sf::String& mapTiledsPosition, const sf::String& tileds)
{
	this->image.loadFromFile(tileds);//загружаем файл для карты
	this->texture.loadFromImage(this->image);//заряжаем текстуру картинкой
	this->sprite.setTexture(this->texture);//заливаем текстуру спрайтом
}

void Map::loadMap()
{
	magicTieldsVector.clear();
	/////////////////////////////Рисуем карту/////////////////////
	std::vector<sf::Sprite> vect;
	loadObjectAnimations();
	for (int i = 0; i < heightMap; i++)
	{
		for (int j = 0; j < widthMap; j++)
		{
			if (tieldMaps[i][j] == '5')  sprite.setTextureRect(sf::IntRect(0, 0, tieldWidth, tieldHeight));
			if (tieldMaps[i][j] == '1')  sprite.setTextureRect(sf::IntRect(tieldWidth, 0, tieldWidth, tieldHeight));
			if ((tieldMaps[i][j] == '2')) sprite.setTextureRect(sf::IntRect(tieldWidth * 2, 0, tieldWidth, tieldHeight));
			if (tieldMaps[i][j] == '3')  sprite.setTextureRect(sf::IntRect(tieldWidth * 3, 0, tieldWidth, tieldHeight));
			if (tieldMaps[i][j] == '4')  sprite.setTextureRect(sf::IntRect(tieldWidth * 4, 0, tieldWidth, tieldHeight));
			if ((tieldMaps[i][j] == ' ')) sprite.setTextureRect(sf::IntRect(tieldWidth * 5, 0, tieldWidth, tieldHeight));
			if (tieldMaps[i][j] == '0')
			{
				sprite.setTextureRect(sf::IntRect(tieldWidth * 5, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				addAnimationObject(sprite, j * tieldWidth, i * tieldHeight, 0);
				continue;
			}
			if (tieldMaps[i][j] == '7')  sprite.setTextureRect(sf::IntRect(tieldWidth * 7, 0, tieldWidth, tieldHeight));
			if ((tieldMaps[i][j] == '8')) sprite.setTextureRect(sf::IntRect(tieldWidth * 8, 0, tieldWidth, tieldHeight));
			if ((tieldMaps[i][j] == 'q'))
			{
				sprite.setTextureRect(sf::IntRect(tieldWidth * 9, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				continue;;
			}
			if ((tieldMaps[i][j] == 'w')) 
			{ 
				sprite.setTextureRect(sf::IntRect(tieldWidth * 10, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				continue;;
			}
			if ((tieldMaps[i][j] == 'e')) 
			{ 
				sprite.setTextureRect(sf::IntRect(tieldWidth * 11, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				continue;;
			}
			if ((tieldMaps[i][j] == 'r'))
			{
				sprite.setTextureRect(sf::IntRect(tieldWidth * 12, 0, tieldWidth, tieldHeight)); 
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				continue;;
			}
			if ((tieldMaps[i][j] == 'a')) 
			{ 
				sprite.setTextureRect(sf::IntRect(tieldWidth * 13, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				continue;;
			}
			if ((tieldMaps[i][j] == 's')) 
			{ 
				sprite.setTextureRect(sf::IntRect(tieldWidth * 14, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				continue;;
			}
			if ((tieldMaps[i][j] == 'd'))
			{ 
				sprite.setTextureRect(sf::IntRect(tieldWidth * 15, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				continue;;
			}
			if ((tieldMaps[i][j] == 'f'))
			{ 
				sprite.setTextureRect(sf::IntRect(tieldWidth * 16, 0, tieldWidth, tieldHeight)); 
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				continue;;
			}

			if ((tieldMaps[i][j] == '@'))
			{
				sprite.setTextureRect(sf::IntRect(tieldWidth * 5, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				continue;;
			}

			if (tieldMaps[i][j] == 'z')
			{
				sprite.setTextureRect(sf::IntRect(tieldWidth * 5, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				addAnimationObject(sprite, j * tieldWidth, i * tieldHeight, 1);
				continue;
			}
			if (tieldMaps[i][j] == 'x')
			{
				sprite.setTextureRect(sf::IntRect(tieldWidth * 5, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				addAnimationObject(sprite, j * tieldWidth, i * tieldHeight, 2);
				continue;
			}
			if (tieldMaps[i][j] == 'c')
			{
				sprite.setTextureRect(sf::IntRect(tieldWidth * 5, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				addAnimationObject(sprite, j * tieldWidth, i * tieldHeight, 3);
				continue;
			}
			if (tieldMaps[i][j] == 'v')
			{
				sprite.setTextureRect(sf::IntRect(tieldWidth * 5, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				addAnimationObject(sprite, j * tieldWidth, i * tieldHeight, 4);
				continue;
			}
			if (tieldMaps[i][j] == 'b')
			{
				sprite.setTextureRect(sf::IntRect(tieldWidth * 5, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				addAnimationObject(sprite, j * tieldWidth, i * tieldHeight, 5);
				continue;
			}
			if (tieldMaps[i][j] == 'n')//на будущее
			{
				sprite.setTextureRect(sf::IntRect(tieldWidth * 5, 0, tieldWidth, tieldHeight));
				addWallObject(sprite, j * tieldWidth, i * tieldHeight);
				addAnimationObject(sprite, j * tieldWidth, i * tieldHeight, 6);
				continue;
			}
			sprite.setPosition(j * tieldWidth, i * tieldHeight);
			magicTieldsVector.push_back(std::pair<sf::Sprite, int> (sprite, 0));
		}
	}
}



void Map::addWallObject(sf::Sprite& sprite, int jTields, int iTields)// должна принимать флаг 2, 1, 0, Но мы торопимся сдать работу)
{
	sprite.setPosition(jTields, iTields);
	magicTieldsVector.push_back(std::pair<sf::Sprite, int>(sprite, 2));
}
void Map::addAnimationObject(sf::Sprite& sprite, int jTields, int iTields, int number)// Прости за числа, времени мало, а писать списки нет времени XD
{
	movementTexturesAndSizeXY.at(number).first.sprite->setPosition(jTields, iTields);
	double speedAnimation = 0;
	switch (number)
	{
	case 0:
	{
		speedAnimation = 9 * pow(10, -6) / 3;
		break;
	}
	case 1:
	{
		speedAnimation = 9 * pow(10, -6) / 3;
		break;
	case 2:
	{
		speedAnimation = 9 * pow(10, -6) / 3;
		break;
	case 3:
	{
		speedAnimation = 9 * pow(10, -6) / 3;
		break;
	}
	case 4:
	{
		speedAnimation = 9 * pow(10, -6) / 3;
		break;
	}
	case 5:
	{
		speedAnimation = 9 * pow(10, -6) / 3;
		break;
	}
	case 6:
	{
		speedAnimation = 9 * pow(10, -6) / 3;
		break;
	}
	}

	}
	}
	animatedTields.push_back(new AnimatedTield(movementTexturesAndSizeXY.at(number).first, movementTexturesAndSizeXY.at(number).second, 0, speedAnimation));
}

void Map::loadObjectAnimations()
{
	movementTexturesAndSizeXY.clear();
	addAnimatedTexture("resource\\Map_Tileds\\Dungeon\\Animation_Objects\\boiler.png", 4, 1);
	addAnimatedTexture("resource\\Map_Tileds\\Dungeon\\Animation_Objects\\coffin.png", 4, 1);
	addAnimatedTexture("resource\\Map_Tileds\\Dungeon\\Animation_Objects\\gallows.png", 4, 1);
	
	addAnimatedTexture("resource\\Map_Tileds\\Dungeon\\Animation_Objects\\guillotine.png", 4, 1);
	addAnimatedTexture("resource\\Map_Tileds\\Dungeon\\Animation_Objects\\hellTree.png", 4, 1);
	addAnimatedTexture("resource\\Map_Tileds\\Dungeon\\Animation_Objects\\jesus.png", 4, 1);
}

void Map::addAnimatedTexture(const sf::String& fileFolder, int maxFrameX, int maxFrameY)
{
	//temp
	TextureData movementTexture0;

	movementTexture0.image = new sf::Image;
	movementTexture0.texture = new sf::Texture;
	movementTexture0.sprite = new sf::Sprite;

	movementTexture0.image->loadFromFile(fileFolder);//sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed, double attackTime)
	movementTexture0.texture->loadFromImage(*movementTexture0.image);
	movementTexture0.sprite->setTexture(*movementTexture0.texture);

	movementTexture0.maxFrameX = maxFrameX;
	movementTexture0.maxFrameY = maxFrameY;

	SizeXY sizeXY(movementTexture0.texture->getSize().x / movementTexture0.maxFrameX, movementTexture0.texture->getSize().y / movementTexture0.maxFrameY);
	//temp
	movementTexturesAndSizeXY.push_back(std::pair<TextureData, SizeXY>(movementTexture0, sizeXY));
}

void Map::animationTields(sf::RenderWindow* window)
{
	for (AnimatedTield* var : animatedTields)
	{
		var->update();
		window->draw(var->getSprite());
	}
}

void Map::updateMap(sf::RenderWindow* window)
{
		/////////////////////////////Рисуем карту///////////////////// sprite.setPosition(j * tieldWidth, i * tieldHeight);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
	std::vector<std::pair<sf::Sprite, int>>::iterator tieldsIter = magicTieldsVector.begin();
	for (int i = 0; i < heightMap; i++)
	{
		for (int j = 0; j < widthMap; j++)
		{

			if(!((*tieldsIter).second & 1))
				window->draw((*tieldsIter).first);//рисуем квадратики на экран
			if ((i == heightMap - 1) && (j == widthMap - 1))
				break;
			tieldsIter++;
		}
		if ((i == heightMap - 1))
			break;
	}
	animationTields(window);
}

void Map::setSizeMap(int heightMap, int widthMap)
{
	this->heightMap = heightMap;
	this->widthMap = widthMap;
}

const int Map::getHeightMap()
{
	return heightMap;
}

const int Map::getWidthMap()
{
	return widthMap;
}

void Map::tieldsSettings(int amountTieldsMap)
{
	tieldWidth = texture.getSize().x / amountTieldsMap;
	tieldHeight = texture.getSize().y / 1;
}

void Map::setMap(sf::String* tieldMaps, int sizeWidht, int sizeHeight)
{
	this->tieldMaps = tieldMaps;
	loadMap();
	//this->widthMap = sizeWidht;
	//this->heightMap = sizeHeight;
}

sf::Sprite Map::getSprite()
{
	return sprite;
}

const int Map::getTieldWidth()
{
	return tieldWidth;
}
const int Map::getTieldHeight()
{
	return tieldHeight;
}
