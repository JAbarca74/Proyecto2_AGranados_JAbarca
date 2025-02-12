#pragma once
#include <iostream>
#include <string>
#include "Button.h"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
using namespace std;
class Segment
{
private:
	int numberSeatingRows;
	int numberSeatingColumns;
	float price;
	Button** seatOfSegment;
	int totalSeats;
	bool isInitialized;
public:
	Segment() : numberSeatingRows(0), numberSeatingColumns(0), price(0.0), seatOfSegment(nullptr),
			totalSeats(0){
	};
	int getNumberSeatingRows();
	int getNumberSeatingColumns();
	float getPrice();
	void setNumberRows(int rows);
	void setNumberColumns(int columns);
	void setPrice(float _price);
	int getTotalSeats() const {
		return numberSeatingRows * numberSeatingColumns;
	}
	void updateData(Font& font);
	bool reserveSeat(string seatCode);
	void resetSeats(const string& seatCode);
	bool isFullTheEvent();
	void clearSeats();
	bool isSeatReserved(const string& seatCode);
	bool hasReservedSeats();
	bool hasPurchasedSeats();
	void drawSeats(RenderWindow& window);
	~Segment();
	string handleSeatClick(RenderWindow& window);
	Button& getSeat(int row, int col) {
		return seatOfSegment[row][col];
	}
};