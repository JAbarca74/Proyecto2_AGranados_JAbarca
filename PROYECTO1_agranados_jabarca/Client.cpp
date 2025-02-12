#include "Client.h"

Client::~Client(){}


void Client::addIdentificationList(string identification)
{
	collectIdentification.insertAtTheEnd(identification);
}

void Client::setPersonName(string aName) {
	personName = aName;
}

void Client::setBirthdayDate(string aDate) {
	birthdayDate = aDate;
}

bool Client::isValidClient(string identification)
{
	if (collectIdentification.findData(identification) == false)
	{
		return true;
	}
	return false;
}

bool Client::validateID(const string& identification)
{
	string idClean = "";

	
	for (char c : identification) {
		if (c != ' ') {
			idClean += c;
		}
	}

	if (idClean.length() != 9) {
		return false;
	}


	if (idClean[0] < '1' || idClean[0] > '8') {
		return false;
	}

	
	if (idClean[5] != '0') {
		return false;
	}

	
	for (char c : idClean) {
		if (c < '0' || c > '9') {
			return false;
		}
	}

	return true; 
}
void Client::addReservedSeat(string& seatCode)
{
	reservedSeats.insertAtTheEnd(seatCode);
}

void Client::showReservedSeats()
{
	List<string>::Node* temp = reservedSeats.getHead();
	while (temp != nullptr) {
		cout << temp->data << " ";
		temp = temp->next;
	}
}

void Client::cleanIdentificationList()
{
	collectIdentification = List<string>();
}

void Client::inputSum(float price) {
	totalInvoice += price;
}

float Client::getTotalInvoce() {
	return totalInvoice;
}

float Client::getApplyDiscount() {
	return applyDiscount;
}

void Client::setApplyDiscount(float anAmount) {
	applyDiscount = anAmount;
}

void Client::setTotalInvoice(float anAmount) {
	totalInvoice = anAmount;
}
string Client::getIdentification()
{
	return identification;
}

string Client::getPersonName()
{
	return personName;
}

string Client::getBirthdayDate()
{
	return birthdayDate;
}

void Client::setIdentification(string aId) {
	identification = aId;
}

void Client::setSeatsToBuy(int anAmount) {
	seatsToBuy = anAmount;
}

int Client::getSeatsToBuy() {
	return seatsToBuy;
}

void Client::clearPurchasedSeats() {
	purchasedSeats.clear();
}

void Client::addPurchasedSeat(PurchasedSeat& seat)
{
	purchasedSeats.insertAtTheEnd(seat);
}

List<PurchasedSeat>& Client::getPurchasedSeats() {
	return purchasedSeats;
}