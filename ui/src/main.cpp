#include <iostream>
#include <string>
#include <memory>
#include "../../base/base.h"

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable, public sf::Transformable {
public:
    Button(std::string text, sf::Font& font, unsigned int characterSize,
           sf::Vector2f position, sf::Vector2f size)
        : m_rect{std::make_unique<sf::RectangleShape>(size)}, // Создаем прямоугольник кнопки
        m_text{std::make_unique<sf::Text>(font, text, characterSize)} { // Создаем текст на кнопке

        m_rect->setPosition(position); // Задаем позицию кнопки
        m_rect->setFillColor(sf::Color(200, 200, 200)); // Серый фон
        m_rect->setOutlineColor(sf::Color::Black); // Черная обводка
        m_rect->setOutlineThickness(2); // Толщина обводки

        m_text->setPosition(sf::Vector2f(position.x + 1, position.y + 1));
        m_text->setFillColor(sf::Color::Black); // цвет текста
    }

    void pressEffect() { // Эффект нажатия — меняем цвет
        m_rect->setFillColor(sf::Color(150, 150, 150));
        m_rect->setOutlineColor(sf::Color(150, 150, 150));
    }

    void releaseEffect() { // Эффект отпускания — возвращаем исходный цвет
        m_rect->setFillColor(sf::Color(200, 200, 200));
        m_rect->setOutlineColor(sf::Color::Black);
    }

    std::string getText() const { // Получаем текст кнопки
        return m_text->getString();
    }

    sf::FloatRect getGlobalBounds() const { // Границы кнопки с учетом трансформаций
        return getTransform().transformRect(m_rect->getGlobalBounds());
    }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override { // Отрисовка кнопки
        states.transform *= getTransform();
        target.draw(*m_rect, states); // Рисуем прямоугольник
        target.draw(*m_text, states); // Рисуем текст
    }

    std::unique_ptr<sf::RectangleShape> m_rect;
    std::unique_ptr<sf::Text> m_text;
};

class UI: public sf::Drawable, public sf::Transformable {
public:
    explicit UI(sf::Font& font) {
        const int fontSize = 16;
        m_button = std::make_unique<Button>(
            "Segment",
            font,
            fontSize,
            sf::Vector2f(20, 20),
            sf::Vector2f(80, 20)
            );
    }

    void addSegment(double x1, double y1, double x2, double y2){
        segment seg{{x1,y1}, {x2,y2}};
        segStore.add(seg);
    }

    void handleEvent(const sf::Event& event, sf::RenderWindow& window) { // Обработка событий
        if ( const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>() ){
            if (mouseButtonPressed->button == sf::Mouse::Button::Left){
                if (m_button->getGlobalBounds().contains(
                        static_cast<sf::Vector2f>(mouseButtonPressed->position)))  {
                    m_button->pressEffect();
                }
            }
        }
        if (const auto* mouseButtonReleased = event.getIf<sf::Event::MouseButtonReleased>() ){
            if ( mouseButtonReleased->button == sf::Mouse::Button::Left) {
                m_button->releaseEffect();
            }
        }
    }
    void drawSegment(double x1,double y1,double x2,double y2)const{
        std::array line =
            {
                sf::Vertex{sf::Vector2f(static_cast<float>(x1), static_cast<float>(y1))},
                sf::Vertex{sf::Vector2f(static_cast<float>(x2), static_cast<float>(y2))}
            };
        m_target->draw(line.data(), line.size(), sf::PrimitiveType::Lines);

    }
    void drawPoint(double x,double y)const{
        sf::CircleShape shape(3.f);
        shape.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
        shape.setFillColor(sf::Color(150, 50, 250));

        shape.setOutlineThickness(1.f);
        shape.setOutlineColor(sf::Color(250, 150, 100));

        m_target->draw(shape);
    }
private:
    Storage<segment> segStore;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override { // Отрисовка калькулятора
        states.transform *= getTransform();
        target.draw(*m_button, states);
        m_target = &target;

        drawSegment(100.0,100.0,200.0,150.0);
        drawPoint(100.0,100.0);
        drawPoint(200.0,150.0);
    }
    std::unique_ptr<Button> m_button;



    mutable sf::RenderTarget* m_target;
};






int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    auto font = std::make_unique<sf::Font>(); // Загружаем шрифт
    if (!font->openFromFile("calibri.ttf")) {
        std::cerr << "Не удалось загрузить шрифт!\n";
        return -1;
    }

    UI ui(*font); // Создаем UI

    while (window.isOpen()) { // Главный цикл

        while ( const std::optional event  = window.pollEvent() ) {
            if (event->is<sf::Event::Closed>() )
                window.close(); // Закрытие окна
            ui.handleEvent(*event, window); // Обработка событий
        }
        window.clear(); // Очистка экрана
        window.draw(ui); // Отрисовка UI
        window.display(); // Показываем результат
    }
    return 0;
}
