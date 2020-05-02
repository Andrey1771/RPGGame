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
	this->image.loadFromFile(tileds);//��������� ���� ��� �����
	this->texture.loadFromImage(this->image);//�������� �������� ���������
	this->sprite.setTexture(this->texture);//�������� �������� ��������
}

void Map::loadMap()
{
	magicTieldsVector.clear();
	/////////////////////////////������ �����/////////////////////
	std::vector<sf::Sprite> vect;
	//temp
	TextureData movementTexture0;

	movementTexture0.image = new sf::Image;
	movementTexture0.texture = new sf::Texture;
	movementTexture0.sprite = new sf::Sprite;

	movementTexture0.image->loadFromFile("resource\\Map_Tileds\\Dungeon\\Animation_Objects\\boiler.png");//sf::String ImageFile, sf::String ImageFileAttack, int maxFrameX, int maxFrameY, int maxFrameAttackX, int maxFrameAttackY, double x, double y, double speed, double attackTime)
	movementTexture0.texture->loadFromImage(*movementTexture0.image);
	movementTexture0.sprite->setTexture(*movementTexture0.texture);

	movementTexture0.maxFrameX = 4;
	movementTexture0.maxFrameY = 1;

	SizeXY sizeXY(movementTexture0.texture->getSize().x/movementTexture0.maxFrameX, movementTexture0.texture->getSize().y / movementTexture0.maxFrameY);
	//temp
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
				sprite.setPosition(j * tieldWidth, i * tieldHeight);
				magicTieldsVector.push_back(std::pair<sf::Sprite, int>(sprite, 2));

				movementTexture0.sprite->setPosition(j * tieldWidth, i * tieldHeight);
				animatedTields.push_back(new AnimatedTield(movementTexture0, sizeXY, 0));
				continue;
			}
			if (tieldMaps[i][j] == '7')  sprite.setTextureRect(sf::IntRect(tieldWidth * 7, 0, tieldWidth, tieldHeight));
			if ((tieldMaps[i][j] == '8')) sprite.setTextureRect(sf::IntRect(tieldWidth * 8, 0, tieldWidth, tieldHeight));
			sprite.setPosition(j * tieldWidth, i * tieldHeight);
			magicTieldsVector.push_back(std::pair<sf::Sprite, int> (sprite, 0));
		}
	}
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
		/////////////////////////////������ �����///////////////////// sprite.setPosition(j * tieldWidth, i * tieldHeight);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������
	std::vector<std::pair<sf::Sprite, int>>::iterator tieldsIter = magicTieldsVector.begin();
	for (int i = 0; i < heightMap; i++)
	{
		for (int j = 0; j < widthMap; j++)
		{

			if(!((*tieldsIter).second & 1))
				window->draw((*tieldsIter).first);//������ ���������� �� �����
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
