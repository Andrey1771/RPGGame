#include "Map.h"
#include <vector>
Map::Map(sf::String ImageFolder, int heightMap, int widthMap, int amountTiledsMap)
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
				sprite.setTextureRect(sf::IntRect(tieldWidth * 6, 0, tieldWidth, tieldHeight));
				sprite.setPosition(j * tieldWidth, i * tieldHeight);
				magicTieldsVector.push_back(std::pair<sf::Sprite, int>(sprite, 1));
				continue;
			}
			if (tieldMaps[i][j] == '7')  sprite.setTextureRect(sf::IntRect(tieldWidth * 7, 0, tieldWidth, tieldHeight));
			if ((tieldMaps[i][j] == '8')) sprite.setTextureRect(sf::IntRect(tieldWidth * 8, 0, tieldWidth, tieldHeight));
			sprite.setPosition(j * tieldWidth, i * tieldHeight);
			magicTieldsVector.push_back(std::pair<sf::Sprite, int> (sprite, 0));
		}
	}
}

void Map::updateMap(sf::RenderWindow* window)
{
		/////////////////////////////Рисуем карту///////////////////// sprite.setPosition(j * tieldWidth, i * tieldHeight);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
	std::vector<std::pair<sf::Sprite, int>>::iterator tieldsIter = magicTieldsVector.begin();
	for (int i = 0; i < heightMap; i++)
		for (int j = 0; j < widthMap; j++)
		{
			
			window->draw((*tieldsIter).first);//рисуем квадратики на экран
			if ((i == heightMap - 1) && (j == widthMap - 1))
				return;
			tieldsIter++;
		}
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