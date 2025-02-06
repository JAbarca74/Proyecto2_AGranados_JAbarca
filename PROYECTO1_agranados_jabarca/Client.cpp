#include "Client.h"

void Client::collectAllInformation()
{
	cout << YELLOW << "INFORMACION NECESARIA PARA EFECTUAR LA COMPRA" << RESET << endl;
	
	cout << "Digite numero de cedula: ";
	cin.ignore();
	getline(cin, identification);
	validateID(identification);
	while (!isValidClient(identification))
	{
		cout << RED << "ERROR." << RESET << "Identificacion ya utilizada, por favor ingrese otra: ";
		getline(cin, identification);
	}
	cout << GREEN << "Su cedula de identificacion se cargo correctamente." << RESET << endl;
	cout << endl;
	addIdentificationList(identification);

	cout << "Digite nombre completo: ";
	getline(cin, personName);
	while (personName.empty())
	{
		cout << RED << "ERROR. " << RESET << "Ingrese un nombre verdadero de usuario: ";
		getline(cin, personName);
	}
	cout << GREEN << "Su nombre se cargo correctamente." << RESET << endl;
	cout << endl;
	cout << "Digite fecha de nacimiento: ";
	cin >> birthdayDate;
	dateProcessorTool.confirmDateBirthDay(birthdayDate);
	cout << GREEN << "Su fecha de nacimiento se cargo correctamente." << RESET << endl;
}

void Client::addIdentificationList(string identification)
{
	collectIdentification.insertAtTheEnd(identification);
}

//CAMBIAR
bool Client::isValidClient(string identification)
{
	if (collectIdentification.findData(identification) == false)
	{
		return true;
	}
	return false;
}

void Client::validateID(string identification)
{
	bool flag = false;
	while (!flag) {
		string idClean = "";
		for (char c : identification) {
			if (c != ' ') {
				idClean += c;
			}
		}
		if (idClean.length() != 9) {
			cout << RED << "Debe tener 9 digitos. " << RESET << "Ingrese nuevamente la cedula: ";
			getline(cin, identification);
			continue;
		}
		if (idClean[0] < '1' || idClean[0] > '8') {
			cout << RED << "Comienza con digito entre 1 y 8. " << RESET << "Ingrese nuevamente la cedula: ";
			getline(cin, identification);
			continue;
		}
		if (idClean[5] != '0') {
			cout << RED << "El sexto digito '0'. " << RESET << "Ingrese nuevamente la cedula: ";
			getline(cin, identification);
			continue;
		}
		bool allDigits = true;
		for (char c : idClean) {
			if (c < '0' || c > '9') {
				allDigits = false;
				break;
			}
		}
		if (!allDigits) {
			cout << RED << "Solo contiene numeros. " << RESET << "Ingrese nuevamente la cedula: ";
			getline(cin, identification); 
			continue;
		}
		flag = true;
	}
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