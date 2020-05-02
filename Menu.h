#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Header.h"
#include "Camera.h"
#include <windows.h>
#include <winuser.h>

using namespace sf;
constexpr auto numOfMenuButtons = 20;  // Количество кнопок основных меню
constexpr auto keyDelay = 1;  // Задержка нажатия клавиш в меню
constexpr auto numOfMonstres = 4;  // Количество монстров в бестиарии
constexpr auto numOfButton = 3;  // Количество текста бестиария
constexpr auto numOfDisplay = 7;  // Количество параметров разрешения экрана
constexpr auto numOfAuthors = 8;  // Количество текста меню "Авторы"
constexpr auto numOfAuthorsTexture = 19;  // Количество текстур меню "Авторы"

class Menu
{
	double cameraOffsetX, cameraOffsetY;  // Смещение камеры
	double kX, kY;  // Сжимающий коэффициент
	double resizeMistakeX, resizeMistakeY;  // Коэффициент, увеличивающий текстуры pauseMenu для полноэкранного режима

	Font font;  // Основной шрифт
	std::vector<std::pair<Text, String>> textVector;  // Вектор <Текст пункта меню (Text), К какому меню относится> 
	std::pair<String, String> nameArray[numOfMenuButtons] =  // Массив <Текст пункта меню (String), К какому меню относится>
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
		std::pair < String, String>(L"Разрешение экрана:", L"settingsMenu"),
		std::pair < String, String>(L"Продолжить", L"mainMenu"),
		std::pair < String, String>(L"Настройки", L"mainMenu"),
		std::pair < String, String>(L"Авторы", L"mainMenu"),
		std::pair < String, String>(L"Загрузка", L"mainMenu"),
		std::pair < String, String>(L"Сохранение", L"pauseMenu"),
		std::pair < String, String>(L"Загрузка", L"pauseMenu")
	};

	std::vector<Texture> textureVec;  // Вектор текстур бэкграунда Главного Меню
	std::vector<Sprite> spriteVec;  // Вектор спрайтов бэкграунда Главного Меню
	
	Music mainMenuMusic; // Музыка Главного Меню

	std::vector<Texture> texPauseVec;  // Вектор текстур бэкграунда Меню Паузы
	std::vector<Sprite> sprPauseVec;  // Вектор спрайтов бэкграунда Меню Паузы

	bool isNewDisplay;  // Флаг наличия нового пользовательского разрешения экрана
	int whatDisplay;  // Индикатор текущего разрешения экрана
	std::vector<std::pair< Text, std::pair<int, int>>>displayVector;  // Вектор параметров разрешения экрана
	std::pair< String, std::pair<int, int>> displayArray[numOfDisplay]  // Массив параметров разрешения экрана
	{
		std::pair < String, std::pair<int, int>>("1920x1080",std::pair<int,int>(1920, 1080)),
		std::pair < String, std::pair<int, int>>("1366x768",std::pair<int,int>(1366, 768)),
		std::pair < String, std::pair<int, int>>("1280x1024",std::pair<int,int>(1280, 1024)),
		std::pair < String, std::pair<int, int>>("1024x768",std::pair<int,int>(1024, 768)),
		std::pair < String, std::pair<int, int>>("640x480",std::pair<int,int>(640, 480)),
		std::pair < String, std::pair<int, int>>("",std::pair<int,int>(0, 0)),
		std::pair < String, std::pair<int, int>>("",std::pair<int,int>(0, 0))
	};

	Texture arrow;  // Текстура стрелок в Настройках
	Sprite volArrows;  // Спрайт стрелок в Настройках

	bool isDisp = 1;  // Индикатор полноэкранного режима (Да/Нет)
	bool isVol = 1;  // Индикатор работы звука (Да/Нет)
	int volValue = 4;  // Текущее значение громкости (0 - 0%, 1 - 25%, 2 - 50%, 3 - 75%, 4 - 100%)
	
	Music bestiaryMusic;  // Музыка бестиария
	Font bestiaryFont;  // Шрифт бестиария
	std::pair<String, String> bestiaryArray[numOfMonstres] =  // Массив текста бестиария
	{
		std::pair < String, String>(L"Раб", L"Самый обыкновенный служитель\nпреисподней. Ничего необычного"),
		std::pair < String, String>(L"Бес", L"Самый маленький прислужник\nада. Совет: не подпускайте его\nблизко"),
		std::pair < String, String>(L"Ифрит", L"Порождение чистого пламени.\nОчень боится воды"),
		std::pair < String, String>(L"Дьявол", L"Владыка преисподней\n(После Биг Босса)")
	};
	std::vector<std::pair<Text, Text>> bestiaryVector;  // Вектор текста бестиария

	String buttonArray[numOfButton] =  // Массив кнопок бестиария
	{
		L"Бестиарий",
		L"Выбор",
		L"Назад"
	};
	std::vector<Text> buttonVector;  // Вектор кнопок бестиария

	std::vector<Texture> bestiaryTextureVec;  // Вектор текстур бестиария
	std::vector<Sprite> bestiarySpriteVec;  // Вектор спрайтов бестиария

	Texture bestiaryBgTexture;  // Текстура бэкграунда бестиария
	Sprite bestiaryBg;  // Вектор бэкграунда бестриария

	int whatMonster;  // Индикатор отображения текущего монстра в бестриарии

	RectangleShape authorsBg;  // Бэкграунд меню "Авторы"
	String authorsTextArray[numOfAuthors] =  // Массив текста меню "Авторы"
	{
		L"Благодарим вас за проявленный интерес к нашей игре",
		L"Андрей Хохлов",
		L"GitHub - Andrey1771",
		L"Павел Соколов",
		L"GitHub - pavelgrafit",
		L"Особая благодарность Давиду Феслияну",
		L"за предоставленную музыку",
		L"Для выхода нажмите Enter"
	};
	
	std::vector<Text> authorsTextVec;  // Вектор текста меню "Авторы"
	Music authorsMusic;  // Музыка менб "Авторы"

	std::vector<Texture> authorsTextureVec;  // Вектор текстур меню "Авторы"
	std::vector<Sprite> authorsSpriteVec;  // Вектор спрайтов меню "Авторы"

	SoundBuffer buttonBuffer;  // Буфер звука нажатия кнопки
	Sound buttonSound;  // Звук нажатия кнопки

	Window window;  // Окно
	Event event;  // Событие
	bool isMenu;  // Индикатор работы меню (да/нет)
	int key;  // Номер текущей кнопки
	Clock clock2;  // Часы
	float CurrentFrame;  // Таймер для анимации бэкграунда 
	float menuTimer;  // Таймер для нажатия клавиш
	
	Camera* camera{ nullptr };
	void closeMainMenu(Music& musicToStop);  // Закрытие главного меню
	void openBestiary(RenderWindow& window, Music& musicToStop);  // Открытие бестиария
	void closeGame(RenderWindow& window);  // Закрытие игры
	void chooseMonster(bool leftArrow);  // Переключение монстров в бестиарии
	void closeBestiary(RenderWindow& window, Music& musicToStop);  // Закрытие бестиария
	void openMainMenu(RenderWindow& window, Music& musicToStop);  // Открытие главного меню
	void openSettingsMenu(RenderWindow& window, Music& musicToStop);  // Открытие меню настроек
	void closePauseMenu();  // Закрытие меню паузы
	void screenModes(RenderWindow& window);  // Переключение между полноэкранным и оконным режимами
	void screenResolutions(RenderWindow& window, bool leftArrow);  // Переключение разрешения экрана
	void onOffMusic(Music& music);  // Включение/выключение музыки и звуков
	void closeSettingsMenu(RenderWindow& window, Music& music);  // Закрытие меню настроек
	void frameCreator(RenderWindow& window);  // Создание текущего кадра и обработки события закрытия окна
	void chooseVolume(Music& music, bool leftArrow);  // Переключение громкости музыки и звуков
	void createKeys(int numOfKeys);  // Создание кнопок
	void usersResolution(RenderWindow& window);  // Обработка пользовательского разрешения экрана
	void playSound(Sound& sound);  // Включить звук с текущим уровнем громкости
	void authors(RenderWindow& window, Music& musicToStop);  // Меню "Авторы"
	void drawAuthorsText(RenderWindow& window, int numOfElem, int startFrame, int duration);  // Отрисовка текста меню "Авторы"
	void closeAuthors();  // Закрытие меню "Авторы"
	void playMusic(Music& music);  // Включить музыку с текущим уровнем громкости
	void drawAuthorsSprites(RenderWindow& window);  // Отрисовка спрайтов меню "Авторы"
	void updateSize();  // Обновление размеров всех текстур под текущее разрешение окна

public:
	Menu(RenderWindow& window, Music& music, Camera* camera);  // Конструктор - ВАЖНО: ЗАГРУЖАЕТ ВСЕ НЕОБХОДИМЫЕ ФАЙЛЫ В ОПЕРАТИВКУ
	~Menu();  // Деструктор
	void mainMenu(RenderWindow& window, Music& musicToStop);  // Главное Меню
	void pauseMenu(RenderWindow& window, Music& music);  // Меню Паузы
	void settingsMenu(RenderWindow& window, Music& music);  // Меню настройки
	void bestiary(RenderWindow& window, Music& musicToStop);  // Бестиарий
	void setCamera(Camera* camera) { this->camera = camera; };  // Хз что это такое, но мб нужно)
	bool isMenuOn() { return isMenu; };  // Индикатор работы меню, нужен для мейна
};

