#include "Button.h"

Button::Button(const Vector2f& size, const Vector2f& position, const Font& font, string aText, Color color)
    : shape(size), text(aText, font, 20) {
    shape.setPosition(position);
    shape.setFillColor(color);
    text.setPosition(position.x + (size.x - text.getLocalBounds().width) / 2.0f,
        position.y + (size.y - text.getLocalBounds().height) / 2.0f);
    text.setFillColor(Color::White);
}
void Button::draw(RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}
bool Button::isMouseOver(const RenderWindow& window) {
    Vector2i mousePos = Mouse::getPosition(window);
    FloatRect bounds = shape.getGlobalBounds();
    return bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}
bool Button::ButtonIsClicked(const RenderWindow& window) {
    return isMouseOver(window) && Mouse::isButtonPressed(Mouse::Left);
}
void Button::setText(const string& aText) {
    text.setString(aText);
}
void Button::setOutlineThickness(float thickness) {
    shape.setOutlineThickness(thickness);
}

void Button::setOutlineColor(const Color& color) {
    shape.setOutlineColor(color);
}
void Button::setTextColor(const Color& color) {
    text.setFillColor(color);
}

void Button::setFillColor(const Color& color)
{
    shape.setFillColor(color);
}

Color Button::getFillColor() const
{
    return shape.getFillColor();
}

string Button::getText() const
{
    return text.getString();
}
