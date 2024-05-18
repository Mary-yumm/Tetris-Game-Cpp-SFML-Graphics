

#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <sstream>

using namespace sf;
int main()
{   //Made for shadow
    int gridShadow[M][N] = { 0 };
    int blockShadow[8][4] = {
            {0, 2, 4, 6},
            {0, 1, 2, 4},
            {0, 2, 4, 5},
            {0, 1, 2, 3},
            {0, 2, 3, 5},
            {1, 2, 3, 4},
            {0, 2, 3, 4},
            {0}
    };
    int p1[4][2], p2[4][2];

    srand(time(0));

    // Menu Window
win2:
    RenderWindow window2(VideoMode(320, 480), "Menu");
    Texture obj;
    obj.loadFromFile("img/background.png");
    Sprite bg(obj);
    Font Font;
    Text Menu1, Menu2, Menu3, Menu4;
    bg.setColor(sf::Color(255, 255, 255));
    if (!Font.loadFromFile("Oswald-Bold.ttf"))
    {
        std::cerr << "Error loading" << std::endl;
        return (-1);
    }
    //Formatting the text using SFML commands
    Menu1.setFont(Font);
    Menu1.setFillColor(Color::White);
    Menu1.setOutlineColor(Color::Black);
    Menu1.setOutlineThickness(3);
    Menu1.setCharacterSize(25);
    Menu1.setString("1.Start a New Game");
    Menu1.setPosition({ 70.f, 160.f });

    Menu2.setFont(Font);
    Menu2.setFillColor(Color::White);
    Menu2.setOutlineColor(Color::Black);
    Menu2.setOutlineThickness(3);
    Menu2.setCharacterSize(25);
    Menu2.setString("2.See High Scores");
    Menu2.setPosition({ 70.f, 220.f });

    Menu3.setFont(Font);
    Menu3.setFillColor(Color::White);
    Menu3.setOutlineColor(Color::Black);
    Menu3.setOutlineThickness(3);
    Menu3.setCharacterSize(25);
    Menu3.setString("3.Help");
    Menu3.setPosition({ 70.f, 280.f });

    Menu4.setFont(Font);
    Menu4.setFillColor(Color::White);
    Menu4.setOutlineColor(Color::Black);
    Menu4.setOutlineThickness(3);
    Menu4.setCharacterSize(25);
    Menu4.setString("4.Exit");
    Menu4.setPosition({ 70.f, 340.f });

    char keypress;

    while (window2.isOpen())
    {
        Event e;
        while (window2.pollEvent(e))
        {
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window2.close();         // Opened window disposes
            if (e.type == Event::TextEntered)
            {
                if (e.text.unicode < 128)
                {
                    keypress = static_cast<char>(e.text.unicode);
                }
                if (keypress == '1')
                    window2.close();
                if (keypress == '4' || keypress == '3')
                {
                    window2.close();
                }
            }
        }

        window2.clear();
        window2.draw(bg);
        window2.draw(Menu1);
        window2.draw(Menu2);
        window2.draw(Menu3);
        window2.draw(Menu4);
        window2.display();
    }
    if (keypress == '3')
    {
        /// -------------------------------------HELP WINDOW ------------------///
        RenderWindow helpWin(VideoMode(320, 480), "Menu");
        Texture obj;
        obj.loadFromFile("img/background.png");
        Sprite bg(obj);
        Text Menu5;
        bg.setColor(sf::Color(255, 255, 255));
        if (!Font.loadFromFile("OpenSans-Italic.ttf"))
        {
            std::cerr << "Error loading " << std::endl;
            return (-1);
        }

        Menu4.setFillColor(Color::White);
        Menu4.setOutlineColor(Color::Black);
        Menu4.setOutlineThickness(0.3);
        Menu4.setCharacterSize(15);
        Menu4.setPosition({ 2.f, 100.f });
        Menu4.setString("Tetris has very simple rules:\n1.The blocks can be moved only in specific ways \n(left, right, rotate, drop).\n2.The blocks can only be removed from the \n screen by filling all the blank spaces in\n a line and clearing that line.\n3.The game is over if the blocks stack up\n in such a way that the lines are not\n cleared and reach the top of the screen.\n4.Each time a line is cleared in Tetris,\n you are awarded points.\n5.Each time blocks reach the top of the screen,\n the game is over.\n");
        Menu5.setPosition({ 3.f, 400.f });
        Menu5.setFont(Font);
        Menu5.Italic;
        Menu5.setFillColor(Color::White);
        Menu5.setOutlineColor(Color::Black);
        Menu5.setOutlineThickness(0.3);
        Menu5.setCharacterSize(17);
        Menu5.setString("Press Enter to go back to Main Menu");
        while (helpWin.isOpen())
        {
            Event e;
            while (helpWin.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    helpWin.close();         // Opened window disposes
                if (e.type == Event::KeyPressed)
                {
                    if (e.key.code == Keyboard::Enter)
                    {
                        helpWin.close();
                        goto win2;
                    }
                }
            }
            helpWin.clear();
            helpWin.draw(bg);
            helpWin.draw(Menu4);
            helpWin.draw(Menu5);
            helpWin.display();
        }
    }
    if (keypress == '1')
    {
        ////////////-----------------------Tetris Game window---------------------///////////////
    game:
        RenderWindow window(VideoMode(320, 480), title);
        Texture obj1, obj2, obj3, obj;
        obj1.loadFromFile("img/tiles.png");
        obj2.loadFromFile("img/background.png");
        obj3.loadFromFile("img/frame.png");
        Text Menu6, Menu7, Menu8;
        Menu7.setFont(Font);
        Menu7.setFillColor(Color::White);
        Menu7.setOutlineColor(Color::Black);
        Menu7.setOutlineThickness(0.3);
        Menu7.setCharacterSize(20);
        Menu7.setPosition({ 250.f, 250.f });
        Menu7.setString("Score \n\nTime: ");
        obj.loadFromFile("img/tiles.png");
        Sprite sprite(obj1), background(obj2), frame(obj3);
        Sprite shad(obj);
        float totaltime=0;
        int score = 0, level = 1, n = 0;
        int delta_x = 4, colorNum = 1;
        float timer = 0, delay = 0.3;
        bool rotate = 0;
        Clock clock;
        bool wait = 0;
        int space;
        while (window.isOpen())
        {
            space = 0;
            if (n != 7 && level != 2)
            {
                delay = 0.3;
            }
            else if (level == 2)
                delay = 0.1;
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            totaltime += time;
            //---Event Listening Part---//
            Event e;

            while (window.pollEvent(e))
            {
                // Event is occurring - until the game is in running state
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close();          // Opened window disposes
                if (n != 7)
                {
                    if (e.type == Event::KeyPressed)
                    {                                           // If any other key (not cross) is pressed
                        if (e.key.code == Keyboard::Up)         // Check if the other key pressed is UP key
                            rotate = true;                      // Rotation gets on
                        else if (e.key.code == Keyboard::Left)  // Check if the other key pressed is LEFT key
                            delta_x = -1;                       // Change in X-Axis - Negative
                        else if (e.key.code == Keyboard::Right) // Check if the other key pressed is RIGHT key
                            delta_x = 1;                        // Change in X-Axis - Positive
                        else if (e.key.code == Keyboard::Space)
                            space = 1;
                    }
                }
            }
            //Calling level up function
            levelup(totaltime, level, delay);

            if (Keyboard::isKeyPressed(Keyboard::Down)) // Just another way to detect key presses without event listener
                delay = 0.05;
            //For pausing the screen
            if (Keyboard::isKeyPressed(Keyboard::P))
            {
                wait = !wait;
            }
            while (wait == 1)
            {

            mainmenu:
                RenderWindow window2(VideoMode(320, 480), "Menu");
                if (Keyboard::isKeyPressed(Keyboard::P))
                {
                    wait = !wait;
                    window2.close();
                }
                Texture obj;
                obj.loadFromFile("img/background.png");
                Sprite bg(obj);
                //  Font Font;
                Text Menu1, Menu2, Menu3, Menu4, Menu5;
                bg.setColor(sf::Color(255, 255, 255));
                if (!Font.loadFromFile("Oswald-Bold.ttf"))
                {
                    std::cerr << "Error loading" << std::endl;
                    return (-1);
                }
                Menu1.setFont(Font);
                Menu1.setFillColor(Color::White);
                Menu1.setOutlineColor(Color::Black);
                Menu1.setOutlineThickness(3);
                Menu1.setCharacterSize(25);
                Menu1.setString("1.Start a New Game");
                Menu1.setPosition({ 70.f, 160.f });

                Menu2.setFont(Font);
                Menu2.setFillColor(Color::White);
                Menu2.setOutlineColor(Color::Black);
                Menu2.setOutlineThickness(3);
                Menu2.setCharacterSize(25);
                Menu2.setString("2.See High Scores");
                Menu2.setPosition({ 70.f, 220.f });

                Menu3.setFont(Font);
                Menu3.setFillColor(Color::White);
                Menu3.setOutlineColor(Color::Black);
                Menu3.setOutlineThickness(3);
                Menu3.setCharacterSize(25);
                Menu3.setString("3.Help");
                Menu3.setPosition({ 70.f, 280.f });

                Menu4.setFont(Font);
                Menu4.setFillColor(Color::White);
                Menu4.setOutlineColor(Color::Black);
                Menu4.setOutlineThickness(3);
                Menu4.setCharacterSize(25);
                Menu4.setString("4.Exit");
                Menu4.setPosition({ 70.f, 340.f });

                Menu5.setFont(Font);
                Menu5.setFillColor(Color::White);
                Menu5.setOutlineColor(Color::Black);
                Menu5.setOutlineThickness(3);
                Menu5.setCharacterSize(25);
                Menu5.setString("5.Continue");
                Menu5.setPosition({ 70.f, 400.f });
                char keypress;

                while (window2.isOpen())
                {
                    Event e;
                    while (window2.pollEvent(e))
                    {
                        if (e.type == Event::Closed) // If cross/close is clicked/pressed
                            window2.close();         // Opened window disposes
                        if (e.type == Event::TextEntered)
                        {
                            if (e.text.unicode < 128)
                            {
                                keypress = static_cast<char>(e.text.unicode);
                            }
                            if (keypress == '1') {
                                window2.close();
                                goto game;
                            }
                            if (keypress == '3') {
                                window2.close();
                            }
                            if (keypress == '4')
                            {
                                window2.close();
                                window.close();
                                return 0;
                            }
                            if (keypress == '5')
                            {
                                window2.close();
                            }
                        }
                    }
                    if (keypress == '3')
                    {
                        RenderWindow helpWin(VideoMode(320, 480), "Menu");
                        Texture obj;
                        obj.loadFromFile("img/background.png");
                        Sprite bg(obj);
                        Text Menu5;
                        bg.setColor(sf::Color(255, 255, 255));
                        if (!Font.loadFromFile("OpenSans-Italic.ttf"))
                        {
                            std::cerr << "Error loading " << std::endl;
                            return (-1);
                        }

                        Menu4.setFillColor(Color::White);
                        Menu4.setOutlineColor(Color::Black);
                        Menu4.setOutlineThickness(0.3);
                        Menu4.setCharacterSize(15);
                        Menu4.setPosition({ 2.f, 100.f });
                        Menu4.setString("Tetris has very simple rules:\n1.The blocks can be moved only in specific ways \n(left, right, rotate, drop).\n2.The blocks can only be removed from the \n screen by filling all the blank spaces in\n a line and clearing that line.\n3.The game is over if the blocks stack up\n in such a way that the lines are not\n cleared and reach the top of the screen.\n4.Each time a line is cleared in Tetris,\n you are awarded points.\n5.Each time blocks reach the top of the screen,\n the game is over.\n");
                        Menu5.setPosition({ 3.f, 400.f });
                        Menu5.setFont(Font);
                        Menu5.Italic;
                        Menu5.setFillColor(Color::White);
                        Menu5.setOutlineColor(Color::Black);
                        Menu5.setOutlineThickness(0.3);
                        Menu5.setCharacterSize(17);
                        Menu5.setString("Press Enter to go back to Main Menu");
                        while (helpWin.isOpen())
                        {
                            Event e;
                            while (helpWin.pollEvent(e))
                            {
                                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                                    helpWin.close();         // Opened window disposes
                                if (e.type == Event::KeyPressed)
                                {
                                    if (e.key.code == Keyboard::Return)
                                    {
                                        helpWin.close();
                                        goto mainmenu;
                                    }
                                }
                            }
                            helpWin.clear();
                            helpWin.draw(bg);
                            helpWin.draw(Menu4);
                            helpWin.draw(Menu5);
                            helpWin.display();
                        }
                    }
                    window2.clear();
                    window2.draw(bg);
                    window2.draw(Menu1);
                    window2.draw(Menu2);
                    window2.draw(Menu3);
                    window2.draw(Menu4);
                    window2.display();
                }
            }
            //Calling movement function for left and right movement
            movement(delta_x);
            //Rotate functino to rotate the shapes
            rot(rotate);
            //For the falling of the piece
            fallingPiece(timer, delay, colorNum, delta_x, n, space, level);
            //Falling for Shadows
            shadow(gridShadow, blockShadow, timer, delay, delta_x, n, space, level, rotate);
            //Calling Space function
            spacebar(space);
            //Removing lines and calculating scores
            lineremove(score, level);
            //calling and cheking if game should over by game over function
            if (gameOver() == 0)
            {
                window.close();
                RenderWindow gameOverWin(VideoMode(320, 480), "Menu");
                Texture obj;
                obj.loadFromFile("img/background.png");
                Sprite bg(obj);
                Text Menu1, Menu2, Menu3, Menu4;
                bg.setColor(sf::Color(255, 255, 255));
                if (!Font.loadFromFile("Oswald-Bold.ttf"))
                {
                    std::cerr << "Error loading verdanab.ttf" << std::endl;
                    return (-1);
                }
                Menu1.setFont(Font);
                Menu1.setFillColor(Color::White);
                Menu1.setOutlineColor(Color::Black);
                Menu1.setOutlineThickness(3);
                Menu1.setCharacterSize(25);
                Menu1.setString("Game Over! ");
                Menu1.setPosition({ 80.f, 160.f });

                Menu2.setFont(Font);
                Menu2.setFillColor(Color::White);
                Menu2.setOutlineColor(Color::Black);
                Menu2.setOutlineThickness(1);
                Menu2.setCharacterSize(15);
                Menu2.setString("1.Go to Main Menu\n2.Quit ");
                Menu2.setPosition({ 70.f, 200.f });
                char keypress=' ';
                while (gameOverWin.isOpen())
                {
                    Event e;
                    while (gameOverWin.pollEvent(e))
                    {
                        if (e.type == Event::Closed) // If cross/close is clicked/pressed
                            gameOverWin.close();         // Opened window disposes
                        if (e.type == Event::TextEntered)
                        {
                            if (keypress == '1') {
                                gameOverWin.close();
                                goto win2;
                            }
                            if (keypress == '2')
                            {
                                gameOverWin.close();
                                return 0;
                            }
                        }
                    }

                    gameOverWin.clear();
                    gameOverWin.draw(bg);
                    gameOverWin.draw(Menu1);
                    gameOverWin.draw(Menu2);
                    gameOverWin.display();
                }
            }

            Menu6.setFont(Font);
            Menu6.setFillColor(Color::White);
            Menu6.setOutlineColor(Color::Black);
            Menu6.setOutlineThickness(0.3);
            Menu6.setCharacterSize(20);
            Menu6.setPosition({ 250.f, 270.f });
           // Menu6.setString(std::__cxx11::to_string(score));
            Menu6.setString(std::to_string(score));

            Menu8.setFont(Font);
            Menu8.setFillColor(Color::White);
            Menu8.setOutlineColor(Color::Black);
            Menu8.setOutlineThickness(0.3);
            Menu8.setCharacterSize(20);
            Menu8.setPosition({ 250.f, 340.f });
            Menu8.setString(std::to_string(int(totaltime)));

            window.clear(Color::Black);
            window.draw(background);
            window.draw(Menu6);
            window.draw(Menu7);
            window.draw(Menu8);

            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (gameGrid[i][j] == 0)
                        continue;
                    sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                    sprite.setPosition(j * 18, i * 18);
                    sprite.move(28, 31); // offset
                    window.draw(sprite);
                }
            }
            for (int i = 0; i < 4; i++)
            {
                sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
                sprite.move(28, 31);
                window.draw(sprite);
            }
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (gridShadow[i][j] == 0)
                        continue;
                    shad.setTextureRect(IntRect(gridShadow[i][j] * 18, 0, 18, 18));
                    shad.setPosition(j * 18, i * 18);
                    shad.move(28, 31); // offset
                    window.draw(shad);
                }
            }
            for (int i = 0; i < 4; i++)
            {
                shad.setTextureRect(IntRect(8 * 18, 0, 18, 18));
                shad.setPosition(p1[i][0] * 18, p1[i][1] * 18);
                shad.move(28, 31);
                window.draw(shad);
            }
            //---The Final on Which Everything is Drawn Over is Loaded---//
            window.draw(frame);
            //---The Window that now Contains the Frame is Displayed---//
            window.display();
        }
    }

    return 0;
}
