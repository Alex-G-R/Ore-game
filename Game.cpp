#include "Game.h"

Game::Game()
    : window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle)
{
    window.setFramerateLimit(framerateLimit);
};

void Game::Initialize()
{

    // Initialize the tilemap
    map.loadLevelFromFile("data/map.bin");

    if (!map.load("assets/tilemap.png")) {
        throw std::runtime_error("Error loading tilemap");
    }

    // load Fonts
    coordinatesUI.initText();

}

void Game::Update()
{
    // Update DT
    deltaTime = dtClock.restart().asSeconds();

    // Update mouse pos
    updateMousePositions();

    // Update tileselector
    tileselector.Update(mousePosGrid, map);

    // Update Ui
    coordinatesUI.updateText(mousePosScreen, mousePosWindow, mousePosView, mousePosGrid, map.tileMap, map.mapSize);

    // Update view
    camera.Update(deltaTime);

    map.update(map);

    // Update level on click
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        map.addOre(mousePosGrid, map);
    }
    else
    {
        map.isLeftMouseButtonHeld = false; // Reset the state when the button is released
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        map.subtractOre(mousePosGrid, map);
    }
    else
    {
        map.isRightMouseButtonHeld = false; // Reset the state when the button is released
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
    {
        map.changeOreType(mousePosGrid, map);
    }
    else
    {
        map.isMiddleMouseButtonHeld = false; // Reset the state when the button is released
    }

    // Clear map on R
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        map.resetTiles(map);


    // Update grid render distance
    window.setView(camera.getView());

    camera.updateRenderDistance(map.tileSizeF, map.mapSize);
}

void Game::Render()
{
    //Clear background
    window.clear(sf::Color::Black);
    window.setView(camera.getView());

    // Begin rendering
    map.render(window, camera.fromX, camera.toX, camera.fromY, camera.toY);
    tileselector.Render(window);

    // Ui
    window.setView(window.getDefaultView());
    coordinatesUI.Render(window);
    coordinatesUI.displayControls(window);

    //End render
    window.display();
}


void Game::Run()
{
    Initialize();

    //Event loop
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                map.SaveLevelToFile("data/map.bin"); // Save level before quitting
                window.close();
            }
        }

        Update();
        Render();
    }
}

void Game::updateMousePositions()
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(window);
    window.setView(camera.getView());
    mousePosView = static_cast<sf::Vector2i>(window.mapPixelToCoords(mousePosWindow));
    mousePosGrid.x = static_cast<int>(static_cast<float>(mousePosView.x) / map.tileSizeF);
    mousePosGrid.y = static_cast<int>(static_cast<float>(mousePosView.y) / map.tileSizeF);
    window.setView(window.getDefaultView());
}

