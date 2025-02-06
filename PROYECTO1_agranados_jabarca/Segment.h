#pragma once
#include <iostream>
#include <string>
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
	string** seatOfSegment;
	int totalSeats;
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
	int getTotalSeats();
	void updateData(int numberSeatingRows_, int numberSeatingColumns_, float price_);
	void printSeats();
	bool reserveSeat(string seatCode);
	void resetSeats(string& seatCode);
	bool isFullTheEvent();
	void clearSeats();
	bool isEmpty();
	bool isSeatReserved(string& seatCode);
	bool hasReservedSeats();
	string** getSeatOfSegment();
	~Segment();
};