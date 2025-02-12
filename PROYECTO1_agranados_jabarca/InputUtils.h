#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

inline int getNumericInput(RenderWindow& window, Font& font, const string& prompt, int minValue = 1, int maxValue = 1000) {
    string input = "";
    Text textInput, label, errorText;
    RectangleShape inputBox(Vector2f(400, 50));


    bool isActive = true;
    while (isActive && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
            if (event.type == Event::TextEntered) {
                if (event.text.unicode == 8 && !input.empty()) {
                    input.pop_back();
                }
                else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    input += static_cast<char>(event.text.unicode);
                }
            }
        }
        textInput.setString(input);
        window.clear(Color(50, 50, 50));
        window.draw(inputBox);
        window.draw(textInput);
        window.draw(label);
        window.draw(errorText);
        window.display();
    }
    return stoi(input);
}
#endif