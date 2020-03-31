#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
constexpr auto C=14;
constexpr auto keyDelay = 1;
constexpr auto numOfMonstres = 4;
constexpr auto numOfButton = 3;
constexpr auto numOfDisplay = 6;

class Menu 
{
	double kX, kY;
	Vector2u startDisplay;
	int whatDisplay;
	std::vector<std::pair< Text, std::pair<int, int>>>displayVector;
	std::pair< String, std::pair<int, int>> displayArray[numOfDisplay]
	{
		std::pair < String, std::pair<int, int>>("1920x1080",std::pair<int,int>(1920, 1080)),
		std::pair < String, std::pair<int, int>>("1366x768",std::pair<int,int>(1366, 768)),
		std::pair < String, std::pair<int, int>>("1280x1024",std::pair<int,int>(1280, 1024)),
		std::pair < String, std::pair<int, int>>("1024x768",std::pair<int,int>(1024, 768)),
		std::pair < String, std::pair<int, int>>("640x480",std::pair<int,int>(640, 480)),
		std::pair < String, std::pair<int, int>>("",std::pair<int,int>(0, 0))
	};

	Font font;  // Шрифт
	std::vector<std::pair<Text, String>> textVector;  // Вектор <Текст пунка меню (Text), К какому меню относится> 
	std::pair<String, String> nameArray[C] =  // Массив <Текст пункта меню (String), К какому меню относится>
	{ 
		std::pair < String, String>(L"Новая игра", L"mainMenu"),
		std::pair < String, String>(L"Бестиарий", L"mainMenu"),
		std::pair < String, String>(L"Выход из игры" , L"mainMenu"),
		std::pair < String, String>(L"Продолжить", L"pauseMenu"),
		std::pair < String, String>(L"Настройки", L"pauseMenu"),
		std::pair < String, String>(L"Главное меню", L"pauseMenu"),
		std::pair < String, String>(L"Режим:", L"settingsMenu"),
		std::pair < String, String>(L"Оконный", L"settingsMenu"),
		std::pair < String, String>(L"Полноэкранный", L"settingsMenu"),
		std::pair < String, String>(L"Звук: Вкл", L"settingsMenu"),
		std::pair < String, String>(L"Звук: Выкл", L"settingsMenu"),
		std::pair < String, String>(L"Громкость", L"settingsMenu"),
		std::pair < String, String>(L"Назад", L"settingsMenu"),
		std::pair < String, String>(L"Разрешение экрана:", L"settingsMenu")
	};

	Music bestiaryMusic;
	Font bestiaryFont;
	Font bestiaryFont_1;
	std::pair<String, String> bestiaryArray[numOfMonstres] =
	{
		std::pair < String, String>(L"Раб", L"Самый обыкновенный служитель\nпреисподней. Ничего необычного"),
		std::pair < String, String>(L"Бес", L"Самый маленький прислужник\nада. Совет: не подпускайте его\nблизко"),
		std::pair < String, String>(L"Ифрит", L"Порождение чистого пламени.\nОчень боится воды"),
		std::pair < String, String>(L"Дьявол", L"Владыка преисподней\n(После Биг Босса)")
	};
	std::vector<std::pair<Text, Text>> bestiaryVector;
	String buttonArray[numOfButton] =
	{
		L"Бестиарий",
		L"Выбор",
		L"Назад"
	};
	std::vector<Text> buttonVector;

	std::vector<Texture> bestiaryTextureVec;  
	std::vector<Sprite> bestiarySpriteVec;

	int whatMonster;

	struct textureData
	{
		sf::Image* image;
		sf::Texture* texture;
		sf::Sprite* sprite;
		int maxFrameX{ 1 };
		int maxFrameY{ 1 };
	}movementTexture;

	Texture aboutTexture;
	Sprite about;
	Window window;  // Окно
	
	Music mainMenuMusic; // Музыка Главного Меню
	Event event;  // Событие
	std::vector<Texture> textureVec;  // Вектор текстур бэкграунда Главного Меню
	std::vector<Sprite> spriteVec;  // Вектор спрайтов бэкграунда Главного Меню

	std::vector<Texture> texPauseVec;  // Вектор текстур бэкграунда Меню Паузы
	std::vector<Sprite> sprPauseVec;  // Вектор спрайтов бэкграунда Меню Паузы

	Texture arrow;  // Текстура стрелок в Настройках
	Sprite volArrows;  // Спрайт стрелок в Настройках

	bool isMenu;  // Индикатор работы меню (да/нет)
	int key;  // Номер текущей кнопки
	Clock clock;  // Часы
	float CurrentFrame;  // Таймер для анимации бэкграунда 
	float menuTimer;  // Таймер для нажатия клавиш

	bool isDisp = 1;  // Индикатор полноэкранного режима (Да/Нет)
	bool isVol = 0;  // Индикатор работы звука (Да/Нет)
	int volValue = 4;  // Текущее значение громкости (0 - 0%, 1 - 25%, 2 - 50%, 3 - 75%, 4 - 100%)
	int oldValue = 0;  // Старое значение звука (для сохранения при выключении звука/выходе в игру)
	bool musicFlag = 0;  // Индикатор работы музыки (Да/Нет)

public:
	Menu(RenderWindow& window, Music& music);  // Конструктор - ВАЖНО: ЗАГРУЖАЕТ ВСЕ НЕОБХОДИМЫЕ ФАЙЛЫ В ОПЕРАТИВКУ
	~Menu();  // Деструктор
	void mainMenu(RenderWindow& window, Music& musicToStop);  // Главное Меню
	void pauseMenu(RenderWindow& window, Music& music);  // Меню Паузы
	void settingsMenu(RenderWindow& window, Music& music);  // Меню настройки
	void bestiary(RenderWindow& window, Music& musicToStop);  // Бестиарий
	void updateSize();
};

