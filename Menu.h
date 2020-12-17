#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Header.h"
#include "Camera.h"
#include <windows.h>
#include <winuser.h>

namespace Menu
{
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

		sf::Font font;  // Основной шрифт
		std::vector<std::pair<sf::Text, sf::String>> textVector;  // Вектор <Текст пункта меню (Text), К какому меню относится> 
		std::pair<sf::String, sf::String> nameArray[numOfMenuButtons] =  // Массив <Текст пункта меню (sf::String), К какому меню относится>
		{
			std::pair < sf::String, sf::String>(L"Новая игра", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"Бестиарий", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"Выход из игры" , L"mainMenu"),
			std::pair < sf::String, sf::String>(L"Продолжить", L"pauseMenu"),
			std::pair < sf::String, sf::String>(L"Настройки", L"pauseMenu"),
			std::pair < sf::String, sf::String>(L"Главное меню", L"pauseMenu"),
			std::pair < sf::String, sf::String>(L"Режим:", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"Оконный", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"Полноэкранный", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"Звук: Вкл", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"Звук: Выкл", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"Громкость", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"Назад", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"Разрешение экрана:", L"settingsMenu"),
			std::pair < sf::String, sf::String>(L"Продолжить", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"Настройки", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"Авторы", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"Загрузка", L"mainMenu"),
			std::pair < sf::String, sf::String>(L"Сохранение", L"pauseMenu"),
			std::pair < sf::String, sf::String>(L"Загрузка", L"pauseMenu")
		};

		std::vector<sf::Texture> textureVec;  // Вектор текстур бэкграунда Главного Меню
		std::vector<sf::Sprite> spriteVec;  // Вектор спрайтов бэкграунда Главного Меню

		sf::Music mainMenuMusic; // Музыка Главного Меню

		std::vector<sf::Texture> texPauseVec;  // Вектор текстур бэкграунда Меню Паузы
		std::vector<sf::Sprite> sprPauseVec;  // Вектор спрайтов бэкграунда Меню Паузы

		bool isNewDisplay;  // Флаг наличия нового пользовательского разрешения экрана
		int whatDisplay;  // Индикатор текущего разрешения экрана
		std::vector<std::pair< sf::Text, std::pair<int, int>>>displayVector;  // Вектор параметров разрешения экрана
		std::pair< sf::String, std::pair<int, int>> displayArray[numOfDisplay]  // Массив параметров разрешения экрана
		{
			std::pair < sf::String, std::pair<int, int>>("1920x1080",std::pair<int,int>(1920, 1080)),
			std::pair < sf::String, std::pair<int, int>>("1366x768",std::pair<int,int>(1366, 768)),
			std::pair < sf::String, std::pair<int, int>>("1280x1024",std::pair<int,int>(1280, 1024)),
			std::pair < sf::String, std::pair<int, int>>("1024x768",std::pair<int,int>(1024, 768)),
			std::pair < sf::String, std::pair<int, int>>("640x480",std::pair<int,int>(640, 480)),
			std::pair < sf::String, std::pair<int, int>>("",std::pair<int,int>(0, 0)),
			std::pair < sf::String, std::pair<int, int>>("",std::pair<int,int>(0, 0))
		};

		sf::Texture arrow;  // Текстура стрелок в Настройках
		sf::Sprite volArrows;  // Спрайт стрелок в Настройках

		bool isDisp = 1;  // Индикатор полноэкранного режима (Да/Нет)
		bool isVol = 1;  // Индикатор работы звука (Да/Нет)
		int volValue = 4;  // Текущее значение громкости (0 - 0%, 1 - 25%, 2 - 50%, 3 - 75%, 4 - 100%)

		sf::Music bestiaryMusic;  // Музыка бестиария
		sf::Font bestiaryFont;  // Шрифт бестиария
		std::pair<sf::String, sf::String> bestiaryArray[numOfMonstres] =  // Массив текста бестиария
		{
			std::pair < sf::String, sf::String>(L"Раб", L"Самый обыкновенный служитель\nпреисподней. Ничего необычного"),
			std::pair < sf::String, sf::String>(L"Бес", L"Самый маленький прислужник\nада. Совет: не подпускайте его\nблизко"),
			std::pair < sf::String, sf::String>(L"Ифрит", L"Порождение чистого пламени.\nОчень боится воды"),
			std::pair < sf::String, sf::String>(L"Дьявол", L"Владыка преисподней\n(После Биг Босса)")
		};
		std::vector<std::pair<sf::Text, sf::Text>> bestiaryVector;  // Вектор текста бестиария

		sf::String buttonArray[numOfButton] =  // Массив кнопок бестиария
		{
			L"Бестиарий",
			L"Выбор",
			L"Назад"
		};
		std::vector<sf::Text> buttonVector;  // Вектор кнопок бестиария

		std::vector<sf::Texture> bestiaryTextureVec;  // Вектор текстур бестиария
		std::vector<sf::Sprite> bestiarySpriteVec;  // Вектор спрайтов бестиария

		sf::Texture bestiaryBgTexture;  // Текстура бэкграунда бестиария
		sf::Sprite bestiaryBg;  // Вектор бэкграунда бестриария

		int whatMonster;  // Индикатор отображения текущего монстра в бестриарии

		sf::RectangleShape authorsBg;  // Бэкграунд меню "Авторы"
		sf::String authorsTextArray[numOfAuthors] =  // Массив текста меню "Авторы"
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

		std::vector<sf::Text> authorsTextVec;  // Вектор текста меню "Авторы"
		sf::Music authorsMusic;  // Музыка менб "Авторы"

		std::vector<sf::Texture> authorsTextureVec;  // Вектор текстур меню "Авторы"
		std::vector<sf::Sprite> authorsSpriteVec;  // Вектор спрайтов меню "Авторы"

		sf::SoundBuffer buttonBuffer;  // Буфер звука нажатия кнопки
		sf::Sound buttonSound;  // Звук нажатия кнопки

		sf::Window window;  // Окно
		sf::Event event;  // Событие
		bool isMenu;  // Индикатор работы меню (да/нет)
		int key;  // Номер текущей кнопки
		sf::Clock* clock;
		sf::Clock clock2;  // Часы
		float CurrentFrame;  // Таймер для анимации бэкграунда 
		float menuTimer;  // Таймер для нажатия клавиш
		sf::Image* windowIcon{ nullptr };
		Camera* camera{ nullptr };
		void closeMainMenu(sf::Music& musicToStop);  // Закрытие главного меню
		void openBestiary(sf::RenderWindow& window, sf::Music& musicToStop);  // Открытие бестиария
		void closeGame(sf::RenderWindow& window);  // Закрытие игры
		void chooseMonster(bool leftArrow);  // Переключение монстров в бестиарии
		void closeBestiary(sf::RenderWindow& window, sf::Music& musicToStop);  // Закрытие бестиария
		void openMainMenu(sf::RenderWindow& window, sf::Music& musicToStop);  // Открытие главного меню
		void openSettingsMenu(sf::RenderWindow& window, sf::Music& musicToStop);  // Открытие меню настроек
		void closePauseMenu();  // Закрытие меню паузы
		void screenModes(sf::RenderWindow& window);  // Переключение между полноэкранным и оконным режимами
		void screenResolutions(sf::RenderWindow& window, bool leftArrow);  // Переключение разрешения экрана
		void onOffMusic(sf::Music& music);  // Включение/выключение музыки и звуков
		void closeSettingsMenu(sf::RenderWindow& window, sf::Music& music);  // Закрытие меню настроек
		void frameCreator(sf::RenderWindow& window);  // Создание текущего кадра и обработки события закрытия окна
		void chooseVolume(sf::Music& music, bool leftArrow);  // Переключение громкости музыки и звуков
		void createKeys(int numOfKeys);  // Создание кнопок
		void usersResolution(sf::RenderWindow& window);  // Обработка пользовательского разрешения экрана
		void playSound(sf::Sound& sound);  // Включить звук с текущим уровнем громкости
		void authors(sf::RenderWindow& window, sf::Music& musicToStop);  // Меню "Авторы"
		void drawAuthorsText(sf::RenderWindow& window, int numOfElem, int startFrame, int duration);  // Отрисовка текста меню "Авторы"
		void closeAuthors();  // Закрытие меню "Авторы"
		void playMusic(sf::Music& music);  // Включить музыку с текущим уровнем громкости
		void drawAuthorsSprites(sf::RenderWindow& window);  // Отрисовка спрайтов меню "Авторы"
		void updateSize();  // Обновление размеров всех текстур под текущее разрешение окна

	public:
		Menu(sf::RenderWindow& window, sf::Music& music, Camera* camera, sf::Clock& clock);  // Конструктор - ВАЖНО: ЗАГРУЖАЕТ ВСЕ НЕОБХОДИМЫЕ ФАЙЛЫ В ОПЕРАТИВКУ
		~Menu();  // Деструктор
		void mainMenu(sf::RenderWindow& window, sf::Music& musicToStop);  // Главное Меню
		void pauseMenu(sf::RenderWindow& window, sf::Music& music);  // Меню Паузы
		void settingsMenu(sf::RenderWindow& window, sf::Music& music);  // Меню настройки
		void bestiary(sf::RenderWindow& window, sf::Music& musicToStop);  // Бестиарий
		void setCamera(Camera* camera) { this->camera = camera; };  // Хз что это такое, но мб нужно)
		bool isMenuOn() { return isMenu; };  // Индикатор работы меню, нужен для мейна
	};

}