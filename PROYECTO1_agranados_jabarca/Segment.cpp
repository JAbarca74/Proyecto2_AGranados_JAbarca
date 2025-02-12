#include "Segment.h"

Segment::~Segment()
{
}

int Segment::getNumberSeatingRows()
{
    return numberSeatingRows;
}

int Segment::getNumberSeatingColumns()
{
    return numberSeatingColumns;
}

float Segment::getPrice()
{
    return price;
}

void Segment::setNumberRows(int rows)
{
    numberSeatingRows = rows;
}

void Segment::setNumberColumns(int columns)
{
    numberSeatingColumns = columns;
}

void Segment::setPrice(float _price)
{
    price = _price;
}

void Segment::updateData(Font& font) {
    if (isInitialized)
        return;

    seatOfSegment = new Button * [numberSeatingRows];
    for (int row = 0; row < numberSeatingRows; row++) {
        seatOfSegment[row] = new Button[numberSeatingColumns];
        for (int col = 0; col < numberSeatingColumns; col++) {
            string seatLabel;
            if (row < 26) {
                seatLabel = string(1, 'A' + row);
            }
            else {
                char firstLetter = 'A' + (row / 26) - 1;
                char secondLetter = 'A' + (row % 26);
                seatLabel = string(1, firstLetter) + string(1, secondLetter);
            }
            seatLabel += to_string(col + 1);
            seatOfSegment[row][col] = Button(
                Vector2f(40, 40),
                Vector2f(300 + col * 50, 200 + row * 50),
                font,
                seatLabel,
                Color::Green
            );
        }
    }
    isInitialized = true;
}


void Segment::drawSeats(RenderWindow& window) {
    for (int row = 0; row < numberSeatingRows; row++) {
        for (int col = 0; col < numberSeatingColumns; col++) {
            seatOfSegment[row][col].draw(window);
        }
    }
}

bool Segment::reserveSeat(string seatCode) {
    for (int row = 0; row < numberSeatingRows; row++) {
        for (int col = 0; col < numberSeatingColumns; col++) {
            if (seatOfSegment[row][col].getText() == seatCode) {
                seatOfSegment[row][col].setFillColor(Color::Red); 
                return true;
            }
        }
    }
    return false;
}
void Segment::resetSeats(const std::string& seatCode) {
    for (int row = 0; row < numberSeatingRows; row++) {
        for (int col = 0; col < numberSeatingColumns; col++) {
            if (seatOfSegment[row][col].getText() == seatCode) {
                seatOfSegment[row][col].setFillColor(Color::Green);
                return;
            }
        }
    }
}

bool Segment::isFullTheEvent() {
    for (int row = 0; row < numberSeatingRows; row++) {
        for (int col = 0; col < numberSeatingColumns; col++) {
            if (seatOfSegment[row][col].getFillColor() != sf::Color::Red) {
                return false;
            }
        }
    }
    return true;
}

bool Segment::isSeatReserved(const std::string& seatCode) {
    for (int row = 0; row < numberSeatingRows; row++) {
        for (int col = 0; col < numberSeatingColumns; col++) {
            if (seatOfSegment[row][col].getText() == seatCode) {
                return seatOfSegment[row][col].getFillColor() == Color::Red;
            }
        }
    }
    return false;
}

bool Segment::hasPurchasedSeats() {
    for (int i = 0; i < numberSeatingRows; i++) {
        for (int j = 0; j < numberSeatingColumns; j++) {
            if (seatOfSegment[i][j].getFillColor() == Color::Red) {
                return true;
            }
        }
    }
    return false;
}

void Segment::clearSeats() {
    if (seatOfSegment != nullptr) {
        for (int i = 0; i < numberSeatingRows; i++) {
            delete[] seatOfSegment[i];
        }
        delete[] seatOfSegment;
        seatOfSegment = nullptr;
    }
}

bool Segment::hasReservedSeats() {
    for (int row = 0; row < numberSeatingRows; row++) {
        for (int col = 0; col < numberSeatingColumns; col++) {
            if (seatOfSegment[row][col].getFillColor() == Color::Red) {
                return true;
            }
        }
    }
    return false;
}

string Segment::handleSeatClick(RenderWindow& window) {
    
    for (int row = 0; row < numberSeatingRows; row++) {
        for (int col = 0; col < numberSeatingColumns; col++) {
            if (seatOfSegment[row][col].ButtonIsClicked(window)) {
                if (seatOfSegment[row][col].getFillColor() == Color::Green) {
                    seatOfSegment[row][col].setFillColor(Color::Red);
                    return seatOfSegment[row][col].getText();
                }
                else {
                    return "";
                }
            }
        }
    }
    return "";
}
