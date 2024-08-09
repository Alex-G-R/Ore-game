
#include "Game.h"

Game::Game()
    : window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle)
{
    window.setFramerateLimit(framerateLimit);
};


void Game::Initialize()
{

    // Initialize the tilemap
    loadLevelFromFile("data/level.txt", level, gridWidth, mapSize);

    if (!map.load("assets/tilemap.png", sf::Vector2u(50, 50), level, gridWidth, gridHeight)) {
        throw std::runtime_error("Error loading tilemap");
    }

    // if (!map.load("assets/tilemap.png", sf::Vector2u(50, 50), level, gridWidth, gridHeight))
    //     throw "Can not load tileset.png";

    // load Fonts
    font.loadFromFile("Fonts/nulshock.otf");

    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(20.f, 20.f);
    text.setString("TEST");


    // Init tileSelector
    tileSelector.setSize(sf::Vector2f(tileSizeF, tileSizeF));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(3.f);
    tileSelector.setOutlineColor(sf::Color::Red);
}

void Game::Update()
{
    // Update DT
    deltaTime = dtClock.restart().asSeconds();

    // Update mouse pos
    updateMousePositions();

    // Update game elements
    tileSelector.setPosition(mousePosGrid.x * tileSizeF, mousePosGrid.y * tileSizeF);

    // Update Ui
    updateMouseInfoUI();

    // Update view
    camera.Update(deltaTime);

    // Update level on click
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        changeTile();
    }
    else
    {
        isLeftMouseButtonHeld = false; // Reset the state when the button is released
    }


    // Update grid render distance
    window.setView(camera.getView());

    fromY = camera.getView().getCenter().y / tileSizeF - 8;
    toY =  camera.getView().getCenter().y / tileSizeF + 10;

    fromX = camera.getView().getCenter().x / tileSizeF - 8;
    toX = camera.getView().getCenter().x / tileSizeF + 10;

    if(fromX < 0)
        fromX = 0;
    else if (fromX >= mapSize)
        fromX = mapSize - 1;
    if(toX < 0)
        toX = 0;
    else if (toX >= mapSize)
        toX = mapSize - 1;

    if(fromY < 0)
        fromY = 0;
    else if (fromY >= mapSize)
        fromY = mapSize - 1;
    if(fromX < 0)
        fromX = 0;
    else if (fromX >= mapSize)
        fromX = mapSize - 1;

    std::cout << "From X: " << fromX << ", toX: " << toX << ", fromY: " << fromY << ", toY: " << toY << std::endl;
}

void Game::Render()
{
    //Clear background
    window.clear(sf::Color::Black);

    window.setView(camera.getView());

    // Begin rendering
    map.render(window, fromX, toX, fromY, toY);


    window.draw(tileSelector);

    // Ui
    window.setView(window.getDefaultView());
    window.draw(text);


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
                SaveLevelToFile("data/level.txt", level, gridWidth, gridHeight); // Save level before quitting
                window.close();
            }
        }

        Update();
        Render();
    }
}

void Game::loadLevelFromFile(const std::string& filename, std::vector<int>& level, int& gridWidth, int& gridHeight) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening level file: " << filename << std::endl;
        throw "error level.txt";
    }

    std::string line;
    std::vector<std::vector<int>> tempLevel;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<int> row;
        int tileID;
        while (ss >> tileID) {
            row.push_back(tileID);
        }
        if (!row.empty()) {
            tempLevel.push_back(row);
        }
    }

    // Close the file
    file.close();

    if (tempLevel.empty()) {
        std::cerr << "Level file is empty or malformed." << std::endl;
        throw "error level.txt";
    }

    gridHeight = tempLevel.size();
    gridWidth = tempLevel[0].size();

    level.clear();
    for (const auto& row : tempLevel) {
        level.insert(level.end(), row.begin(), row.end());
    }
}

void Game::SaveLevelToFile(const std::string& filename, const std::vector<int>& level, int gridWidth, int gridHeight)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file " + filename);
    }

    for (int i = 0; i < gridHeight; ++i)
    {
        for (int j = 0; j < gridWidth; ++j)
        {
            file << level[i * gridWidth + j] << ' ';
        }
        file << '\n'; // New line at the end of each row
    }

    file.close();
}

void Game::changeTile()
{
    if (!isLeftMouseButtonHeld) // If the mouse button was not held in the previous frame
    {
        isLeftMouseButtonHeld = true; // Update the state to held

        // Ensure the grid position is within bounds
        if (mousePosGrid.x >= 0 && mousePosGrid.x < gridWidth &&
            mousePosGrid.y >= 0 && mousePosGrid.y < gridHeight)
        {
            int index = mousePosGrid.y * gridWidth + mousePosGrid.x; // Corrected index calculation

            if (level[index] >= 5)
            {
                level[index] = 0;
            }
            else
            {
                level[index] += 1;
            }

            if (!map.load("assets/tilemap.png", sf::Vector2u(50, 50), level, gridWidth, gridHeight))
                throw "Can not load tileset.png";
        }
    }
}
void Game::updateMousePositions()
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(window);
    window.setView(camera.getView());
    mousePosView = static_cast<sf::Vector2i>(window.mapPixelToCoords(mousePosWindow));
    mousePosGrid.x = static_cast<int>(mousePosView.x) / tileSizeF;
    mousePosGrid.y = static_cast<int>(mousePosView.y) / tileSizeF;
    window.setView(window.getDefaultView());
}

void Game::updateMouseInfoUI()
{
    std::stringstream ss;
    ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
        << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
        << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
        << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";

    text.setString(ss.str());
}

