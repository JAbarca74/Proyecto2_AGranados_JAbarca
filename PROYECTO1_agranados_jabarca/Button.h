#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sf;

class Button {
private:
	RectangleShape shape;
	Text text;
public:
	Button() {};
	Button(const Vector2f& size, const  Vector2f& position, const  Font& font, string text, Color color);
	void draw(RenderWindow& window);
	bool isMouseOver(const RenderWindow& window);
	bool ButtonIsClicked(const RenderWindow& window);
	void setText(const string& aText);
	void setOutlineThickness(float thickness);
	void setOutlineColor(const Color& color);
	void setTextColor(const Color& color);
	void setFillColor(const Color& color);
	Color getFillColor() const;
	string getText() const;
	
};
