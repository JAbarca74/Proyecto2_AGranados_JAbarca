#pragma once
#include "DateProcessorTool.h"
#include "Segment.h"
#include "Client.h"
#include "List.h"
#include <iostream>
#include <string>
#define RED "\033[31m"
#define BRIGHT_YELLOW "\033[93m"
#define GREEN "\033[32m"
#define BRIGHT_CYAN "\033[96m" 
#define YELLOW "\033[33m" 
#define BRIGHT_WHITE "\033[97m"
#define LIGHT_PURPLE "\033[1;95m"
#define RESET "\033[0m"
using namespace std;

class ConfigEvent {
private:
	int segmentsEvent;
	int sizeSegmentsSpace;
	int totalRows;
	int totalColumns;
	int discountedTicketsSold;
	int acountWithDiscount;
	int discount;
	int codes;
	int freeSeats;
	string nameEvent;
	string dateEvent;
	string reserveSeats;
	string separatorIdeas;
	List<string> discountCodesList;
    List<string> temporalCodesList;
	string** availableSeats;
	Segment segment;
    List<Segment> segmentsList; 
	Client client;
	DateProcessorTool dateProcessorTool;

public:
	ConfigEvent() : nameEvent("-"), dateEvent("-"), segmentsEvent(0), freeSeats(),
        totalRows(0), totalColumns(0), availableSeats(), reserveSeats(""),
		discountedTicketsSold(0), acountWithDiscount(0), discount(0), codes(0), 
        sizeSegmentsSpace(0), client(), segment(), dateProcessorTool(),
		separatorIdeas("--------------------//----------------------") {
	};
    string getNameEvent();
    string getDateEvent();
    void setNameEvent(string _nameEvent);
    void setDateEvent(string _dateEvent);
    void setSegmentSpace(int _segmentSpace);
    void printSeparatorIdeas();
    void printInicializeEventData();
    void confirmSegment();
    void setCodeDiscount(int codeDiscount);
    void setDiscount(int _discount);
    int getSizeSegmentsSpace();
    int calculateTotalSeats();
    void addSegment( Segment& segment);
    void removeSegment(int pos);
    bool isSegmentExists();
    void prepareEventData();
    void printExportCurrentEvent();
    void deleteEvent();
    void configureMatrixDimensions(int segmentNumber);
    void inicializateSeatsSpace(int segmentNumber);
    void getReserveSeat(string& reserveSeats);
    bool isEmptyTheEvent();
    void createVectorDiscounts(int size);
    void generateDiscountCodes();
    void printCodes();
    void deleteCode(string aCode);
    float applyCodeDiscount(Segment* spaceSegment);
    void processPurchase(int seatsPurchased, string& numberReserveSeats);
    int getTotalSeatsPurchase();
    int getSegmentSelection();
    string getDiscountCode();
    bool reserveSeatInSegment(int temporalSegment, string& numberReserveSeats);
    float calculateTotalPrice(string auxCode, int temporalSegment);
    float calculateTotalDiscount(string auxCode, int temporalSegment);
    void numberOfSeatsPurchase();
    void controlTicketSoldEvent();
    void reserveSeatInSegment(int segmentIndex, const string& seatCode);
    void showStatusOfEvent();
    Segment* getSegment(int pos);
    bool isSegmentExistTwo();
    bool isDiscountNumExist();
    bool isCodeExist(string code);
    bool isSeatAvailable(string& reserveSeats);
    bool isFullEventTwo();
    void captureEventData(int& temporalRows, int& temporalColumns, float temporalPrice);
    void printInvoice(int seatsPurchased, float anApplyDiscount, float aTotalPrice, float anFinalPrice);
    void aboutUs();
    void resizeSegmentsSpace(int newSize);
    void changeSegmentDimension();
    void changePosicSegmentDimension(int pos);
    void deleteSpecificCodeDiscount();
    void restoreDiscountCode(string& code);
    void deleteTickets();
};
