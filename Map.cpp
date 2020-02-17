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
	this->sprite.setPosition(w - 8192/2, h - 4096/2);
	return true;
}

void Map::loadLevel(const sf::String& mapTiledsPosition, const sf::String& tileds)
{
	this->image.loadFromFile(tileds);//загружаем файл для карты
	this->texture.loadFromImage(this->image);//заряжаем текстуру картинкой
	this->sprite.setTexture(this->texture);//заливаем текстуру спрайтом
}

void Map::updateMap(sf::RenderWindow *window)
{
	//tieldsSettings(7);
	
		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < heightMap; i++)
			for (int j = 0; j < widthMap; j++)
			{
				
				if (tieldMaps[i][j] == ' ')  sprite.setTextureRect(sf::IntRect(0, 0, tieldWidth, tieldHeight)); //если встретили символ пробел, то рисуем 1й квадратик
				if (tieldMaps[i][j] == 's')  sprite.setTextureRect(sf::IntRect(tieldWidth, 0, tieldWidth, tieldHeight));//если встретили символ s, то рисуем 2й квадратик
				if ((tieldMaps[i][j] == '0')) sprite.setTextureRect(sf::IntRect(tieldWidth*2, 0, tieldWidth, tieldHeight));//если встретили символ 0, то рисуем 3й квадратик


				sprite.setPosition(j * tieldWidth, i * tieldHeight);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

				window->draw(sprite);//рисуем квадратики на экран
			}
}

void Map::setSizeMap(int heightMap, int widthMap)
{
	this->heightMap = heightMap;
	this->widthMap = widthMap;
}

void Map::tieldsSettings(int amountTieldsMap)
{
	tieldWidth = texture.getSize().x/amountTieldsMap;
	tieldHeight = texture.getSize().y/1;
}

void Map::setMap(sf::String* tieldMaps, int sizeWidht, int sizeHeight)
{
	this->tieldMaps = tieldMaps;
	//this->widthMap = sizeWidht;
	//this->heightMap = sizeHeight;
}

sf::Sprite Map::getSprite()
{
	return sprite;
}
