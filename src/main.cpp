#include "spaceship.hpp"
#include "asteroid.hpp"
#include "projectile.hpp"


int main() {

    const unsigned int windowWidth = 1200;
    const unsigned int windowHeight = 800;    

    sf::Font font;
    font.loadFromFile("font/AgentOrange.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    text.setPosition(400, 350);

    // create window.
    sf::RenderWindow window {sf::VideoMode(windowWidth, windowHeight), "Asteroids", sf::Style::Titlebar};
    window.setFramerateLimit(60);

    // set the background of the window.
    sf::Texture bgTexture;
    bgTexture.loadFromFile("img/background.jpg");
    bgTexture.setSmooth(true);
    sf::Sprite bg {bgTexture, sf::IntRect(0, 0, windowWidth, windowHeight)};

    sf::Texture spaceshipTexture;
    spaceshipTexture.loadFromFile("img/spaceship.png");
    spaceshipTexture.setSmooth(true);

    // create spaceship object.
    Spaceship *spaceshipPtr = new Spaceship(spaceshipTexture);

    sf::Texture projectileTexture;
    projectileTexture.loadFromFile("img/projectile.png");
    projectileTexture.setSmooth(true);

    // create empty vector of type Projectile
    std::vector<Projectile*> projectileCollection;

    sf::Texture asteroidTexture;
    asteroidTexture.loadFromFile("img/asteroid.png");
    asteroidTexture.setSmooth(true);

    // create empty vector of type Asteroid.
    std::vector<Asteroid*> asteroidCollection;

    int asteroidNum = 10;

    // populate the vector of pointers to asteroid objects.
    for (int i = 0; i < asteroidNum; i++) {
        Asteroid *asteroidPtr = new Asteroid(asteroidTexture);
        asteroidCollection.push_back(asteroidPtr);
    }

    // movements will be stopped when pause is set to true.
    bool pause {false};

    while (window.isOpen()) {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        if (!pause) {
            // spaceship movements.
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
                spaceshipPtr->rotate(5, "clockwise");

            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
                spaceshipPtr->rotate(5, "anticlockwise");

            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
                spaceshipPtr->setThrust(true);
            else
                spaceshipPtr->setThrust(false);

            // populate vector of pointers to projectile object.
            sf::Event event;
            while (window.pollEvent(event)) {
                if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)) {
                        Projectile *projectilePtr = new Projectile(projectileTexture, spaceshipPtr);
                        projectileCollection.push_back(projectilePtr);        
                    }
            }

            // check for collisions between projectiles and asteroids. If
            // collision occurs, make the two colliding objects inactive.
            for (auto &projectilePtr: projectileCollection) {
                for (auto &asteroidPtr: asteroidCollection) {
                    if (projectilePtr->hasCollidedWith(asteroidPtr)) {
                        projectilePtr->setActive(false);
                        asteroidPtr->setActive(false);
                        asteroidNum--;
                    }
                }
            }
            
            spaceshipPtr->updatePosition();

            // update projectile position and remove the inactive ones.
            for (long unsigned int i = 0; i < projectileCollection.size(); i++) {
                projectileCollection.at(i)->updatePosition();
                if (!projectileCollection.at(i)->getActive()) {
                    delete projectileCollection.at(i);
                    projectileCollection.erase(projectileCollection.begin() + i);
                }
            }

            // update asteroid position and remove the inactive ones.
            for (long unsigned int i = 0; i < asteroidCollection.size(); i++) {
                asteroidCollection.at(i)->updatePosition();
                if (!asteroidCollection.at(i)->getActive()) {
                    delete asteroidCollection.at(i);
                    asteroidCollection.erase(asteroidCollection.begin() + i);
                }
            }

            // check for potential collision of the spaceship with any one of the
            // asteroids. If collision occurs, make the spaceship object inactive.
            for (auto &asteroidPtr: asteroidCollection) {
                if (spaceshipPtr->hasCollidedWith(asteroidPtr)) {
                    spaceshipPtr->setActive(false);
                }
            }

        }

        window.clear();
        
        window.draw(bg);

        // draw the active game objects.        
        window.draw(spaceshipPtr->getSprite());

        for (auto &projectilePtr: projectileCollection)
            window.draw(projectilePtr->getSprite());
        
        for (auto &asteroidPtr: asteroidCollection)
            window.draw(asteroidPtr->getSprite());

        // losing condition.
        if (!spaceshipPtr->getActive()) {
            pause = true;
            text.setString("You Lose !");
            window.draw(text);
        }

        // winning conditon.
        if (asteroidNum == 0) {
            pause = true;
            text.setString("You Won !");
            window.draw(text);
        }

        window.display();

    }
    
    // free memory.
    delete spaceshipPtr;

    for (auto &projectilePtr: projectileCollection)
        delete projectilePtr;

    projectileCollection.clear();

    for (auto &asteroidPtr: asteroidCollection)
        delete asteroidPtr;

    asteroidCollection.clear();

    return 0;
}