#include "Segment.h"

Segment::~Segment()
{
    clearSeats();
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

void Segment::updateData(int numberSeatingRows_, int numberSeatingColumns_, float price_)
{
    numberSeatingRows = numberSeatingRows_;
    numberSeatingColumns = numberSeatingColumns_;
    price = price_;

    seatOfSegment = new string * [numberSeatingRows];
    for (int letter = 0; letter < numberSeatingRows; letter++)
    {
        seatOfSegment[letter] = new string[numberSeatingColumns];
        for (int number = 0; number < numberSeatingColumns; number++)
        {
            string seatLabel;
            if (letter < 26) {
                seatLabel = string(1, 'A' + letter);
            }
            else {
                char firstLetter = 'A' + (letter / 26) - 1;
                char secondLetter = 'A' + (letter % 26);
                seatLabel = string(1, firstLetter) + string(1, secondLetter);
            }
            seatOfSegment[letter][number] = seatLabel + to_string(number + 1);
        }
    }
}

void Segment::printSeats() 
{
    for (int i = 0; i < numberSeatingRows; i++)
    {
        for (int j = 0; j < numberSeatingColumns; j++)
        {
            if (seatOfSegment[i][j] != "XX")
            {
                cout << GREEN << "[ |_" << seatOfSegment[i][j] << "_| ] " << RESET;
            }
            else {
                cout << RED << "[ |_" << seatOfSegment[i][j] << "_| ] " << RESET;
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool Segment::reserveSeat(string seatCode)
{
    for (int i = 0; i < numberSeatingRows; i++)
    {
        for (int j = 0; j < numberSeatingColumns; j++)
        {
            if (seatOfSegment[i][j] == seatCode) 
            {
                seatOfSegment[i][j] = "XX";
                return true;
            }
        }
    }
    return false;
}
void Segment::resetSeats(string& seatCode)
{
    for (int i = 0; i < numberSeatingRows; i++)
    {
        for (int j = 0; j < numberSeatingColumns; j++)
        {
            if (seatOfSegment[i][j] == "XX")
            {
                seatOfSegment[i][j] = seatCode;
                return;
            }
        }
    }
}

bool Segment::isSeatReserved(string& seatCode)
{
    for (int i = 0; i < numberSeatingRows; ++i)
    {
        for (int j = 0; j < numberSeatingColumns; ++j)
        {
            if (seatOfSegment[i][j] == seatCode)
            {
                return true;
            }
        }
    }
    return false;
}

int Segment::getTotalSeats() {
    return numberSeatingColumns * numberSeatingRows;
}

bool Segment::isFullTheEvent()
{
    for (int i = 0; i < numberSeatingRows; i++)
    {
        for (int j = 0; j < numberSeatingColumns; j++)
        {
            if (seatOfSegment[i][j] != "XX")
            {
                return false;
            }
        }
    }
    return true;
}

void Segment::clearSeats()
{
    if (seatOfSegment != nullptr)
    {
        for (int i = 0; i < numberSeatingRows; i++)
        {
            delete[] seatOfSegment[i];
        }
        delete[] seatOfSegment;
        seatOfSegment = nullptr;
    }
}

bool Segment::isEmpty()
{
    for (int i = 0; i < numberSeatingRows; ++i) 
    {
        for (int j = 0; j < numberSeatingColumns; ++j) 
        {
            if (seatOfSegment[i][j] == "XX") 
            {
                return false;
            }
        }
    }
    return true;
}

bool Segment::hasReservedSeats()
{
    for (int i = 0; i < numberSeatingRows; ++i)
    {
        for (int j = 0; j < numberSeatingColumns; ++j)
        {
            if (seatOfSegment[i][j] == "XX")
            {
                return true;
            }
        }
    }
    return false;
}

string** Segment::getSeatOfSegment()
{
    return seatOfSegment;
}
