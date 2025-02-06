#include "ConfigEvent.h"

string ConfigEvent::getNameEvent()
{
	return nameEvent;
}

string ConfigEvent::getDateEvent() 
{
	return dateEvent;
}

void ConfigEvent::setNameEvent(string _nameEvent)
{
	nameEvent = _nameEvent;
}

void ConfigEvent::setDateEvent(string _dateEvent)
{
	dateEvent = _dateEvent;
}

void ConfigEvent::setSegmentSpace(int _segmentSpace)
{
	segmentsEvent = _segmentSpace;
	sizeSegmentsSpace = _segmentSpace;
}

void ConfigEvent::printSeparatorIdeas()
{
	cout << endl << BRIGHT_CYAN << separatorIdeas << RESET << endl << endl;
}

void ConfigEvent::printInicializeEventData()
{
	cout << YELLOW << "INFORMACION DEL EVENTO: " << RESET << endl << endl
		<< "Nombre del evento    |   " << BRIGHT_CYAN << getNameEvent() << RESET << endl
		<< "Fecha del evento     |   " << BRIGHT_CYAN << getDateEvent() << RESET << endl
		<< "Numero de segmentos  |   " << BRIGHT_CYAN << getSizeSegmentsSpace() << RESET << endl
		<< "Numero de asientos   |   " << BRIGHT_CYAN << calculateTotalSeats() << RESET << endl;
}

void ConfigEvent::confirmSegment()
{
	while (segmentsEvent < 1)
	{
		cout << RED << "Numero de segmentos invalido. Intente nuevamente." << RESET << endl
			<< GREEN << "Ingrese el numero de segmentos (mayor a 0): " << RESET;
		cin >> segmentsEvent;
		printSeparatorIdeas();

		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			segmentsEvent = 0;
		}
	}
}

void ConfigEvent::setCodeDiscount(int codeDiscount)
{
	acountWithDiscount = codeDiscount;
}

void ConfigEvent::setDiscount(int _discount)
{
	discount = _discount;
}

int ConfigEvent::getSizeSegmentsSpace()
{
	return sizeSegmentsSpace;
}

int ConfigEvent::calculateTotalSeats()
{
	int totalSeats = 0;

	List<Segment>::Node* current = segmentsList.getHead();


	while (current != nullptr) {
		totalSeats += current->data.getTotalSeats();
		current = current->next;
	}

	return totalSeats;
}

void ConfigEvent::addSegment(Segment& segment) {
	segmentsList.insertAtTheEnd(segment);
	sizeSegmentsSpace++;
	cout << "Se anadio " << segment.getTotalSeats() << endl;
}

void ConfigEvent::removeSegment(int pos) {
	segmentsList.eliminateNode(pos);
	sizeSegmentsSpace--;
}

bool ConfigEvent::isSegmentExists()
{
	if (segmentsList.getHead() == nullptr)
	{
		return false;
	}
	return true;
}

void ConfigEvent::prepareEventData()
{
	int temporalRows = 0;
	int temporalColumns = 0;
	float temporalPrice = 0;
	printInicializeEventData();
	captureEventData(temporalRows, temporalColumns, temporalPrice);
	system("cls");
	printInicializeEventData();
	cout << endl;
	system("pause");
}

void ConfigEvent::printExportCurrentEvent()
{
	system("cls");
	printInicializeEventData();
	cout << endl;
	system("pause");
}


void ConfigEvent::deleteEvent()
{
	segmentsList = List<Segment>();
	discountCodesList = List<string>();
	temporalCodesList = List<string>();
	nameEvent = "-";
	dateEvent = "-";
	segmentsEvent = 0;
	sizeSegmentsSpace = 0;
	codes = 0;
	acountWithDiscount = 0;
	discount = 0;
	cout << GREEN << "El evento ha sido eliminado completamente." << RESET << endl;
	system("pause");
}

void ConfigEvent::configureMatrixDimensions(int segmentNumber)
{
	segmentNumber--;
	if (segmentNumber < 0)
	{
		cout << "Numero de segmento no valido." << endl;
		return;
	}
	List<Segment>::Node* current = segmentsList.getHead();
	int count = 0;

	while (current != nullptr && count < segmentNumber)
	{
		current = current->next;
		count++;
	}
	if (current != nullptr)
	{
		totalRows = current->data.getNumberSeatingRows();
		totalColumns = current->data.getNumberSeatingColumns();
	}
	else
	{
		cout << "Numero de segmento fuera de rango." << endl;
	}
}

void ConfigEvent::inicializateSeatsSpace(int segmentNumber)
{
	configureMatrixDimensions(segmentNumber);
	availableSeats = new string * [totalRows];
	for (int i = 0; i < totalRows; i++)
	{
		availableSeats[i] = new string[totalColumns];
	}
}

void ConfigEvent::getReserveSeat(string& reserveSeats)
{
	for (int letter = 0; letter < totalRows; letter++)
	{
		for (int number = 0; number < totalColumns; number++)
		{
			if (availableSeats[letter][number] == reserveSeats)
			{
				availableSeats[letter][number] = "XX";
				return;
			}
		}
	}
}

bool ConfigEvent::isEmptyTheEvent()
{
	typename List<Segment>::Node* currentNode = segmentsList.getHead();
	while (currentNode != nullptr)
	{
		if (currentNode->data.hasReservedSeats())
		{
			return false; 
		}
		currentNode = currentNode->next;
	}
	return true; 
}

void ConfigEvent::createVectorDiscounts(int size)
{
	List<string> newList;
	List<string>::Node* temp = discountCodesList.getHead();
	int count = 0;

	while (temp != nullptr && count < size)
	{
		newList.insertAtTheEnd(temp->data);
		temp = temp->next;
		count++;
	}
	discountCodesList = newList;
	codes = size;
}

void ConfigEvent::generateDiscountCodes()
{
	int length = 6;
	char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string code = "";
	for (int i = 0; i < acountWithDiscount; i++)
	{
		code = "";
		for (int j = 0; j < length; j++)
		{
			int randomIndex = rand() % 36;
			code += alphanum[randomIndex];
		}
		discountCodesList.insertAtTheEnd(code);
		temporalCodesList.insertAtTheEnd(code);
	}
}

void ConfigEvent::printCodes()
{
	cout << BRIGHT_CYAN << "------------- Codigos Disponibles -------------" << RESET << endl;
	List<string>::Node* codesOfList = discountCodesList.getHead();
	while (codesOfList != nullptr)
	{
		cout << GREEN << codesOfList->data << " || ";
		codesOfList = codesOfList->next;
	}
	cout << endl;
	cout << YELLOW << "Elige la cantidad de codigos que necesites." << endl << endl
		<< LIGHT_PURPLE << "(Cada codigo es valido unicamente para una entrada.)" << RESET;
	cout << endl << endl;
	system("pause");
	system("cls");
}

void ConfigEvent::deleteCode(string aCode)
{
	List<string>::Node* temp = discountCodesList.getHead();
	List<string>::Node* previous = nullptr;
	while (temp != nullptr)
	{
		if (temp->data == aCode)
		{
			discountCodesList.deleteNode(temp);
			return;
		}
		previous = temp;
		temp = temp->next;
	}
	cout << YELLOW << "Codigo no encontrado." << RESET << endl;
}

float ConfigEvent::applyCodeDiscount(Segment* spaceSegment)
{
	float price = spaceSegment->getPrice();
	float priceWithDiscount = price - (price * discount / 100);
	return priceWithDiscount;
}

void ConfigEvent::processPurchase(int seatsPurchased, string& numberReserveSeats)
{
	client.collectAllInformation();
	int totalSeatsPurchase = getTotalSeatsPurchase();
	if (totalSeatsPurchase == -1)
	{
		return;
	}
	system("pause");
	system("cls");

	float temporalTotal = 0.0f;
	float temporalDiscount = 0.0f;
	while (seatsPurchased < totalSeatsPurchase)
	{
		cout << "Estado actual de los segmentos disponibles: " << endl;
		showStatusOfEvent();
		if (sizeSegmentsSpace == 0)
		{
			return;
		}
		int temporalSegment = getSegmentSelection();
		if (temporalSegment == -1) {
			continue;
		}

		string auxCode = getDiscountCode();
		bool asientoReservado = reserveSeatInSegment(temporalSegment, numberReserveSeats);
		if (!asientoReservado)
		{
			continue;
		}
		seatsPurchased++;
		freeSeats--;
		temporalTotal += calculateTotalPrice(auxCode, temporalSegment);
		temporalDiscount += calculateTotalDiscount(auxCode, temporalSegment);

		system("pause");
		system("cls");
	}
	printInvoice(totalSeatsPurchase, temporalDiscount, temporalTotal + temporalDiscount, temporalTotal);
	cout << endl;
	system("pause");
	system("cls");
}

int ConfigEvent::getTotalSeatsPurchase()
{
	float aux = 0.0f;
	int totalSeatsPurchase = 0;
	do
	{
		cout << endl << "Digite la cantidad de asientos que desea comprar: ";
		cin >> aux;
		totalSeatsPurchase = static_cast<int>(aux);
		if (totalSeatsPurchase > 5 || totalSeatsPurchase > freeSeats)
		{
			cout << RED << "ERROR. El maximo son 5 asientos / No hay asientos suficientes. Intente de nuevo: " << RESET << endl;
		}
	} while (totalSeatsPurchase > 5 || totalSeatsPurchase > freeSeats);

	return totalSeatsPurchase;
}

int ConfigEvent::getSegmentSelection()
{
	float aux = 0.0f;
	int temporalSegment = 0;
	cout << "Digite el segmento en el que desea comprar (1 - " << sizeSegmentsSpace << "): ";
	cin >> aux;
	temporalSegment = static_cast<int>(aux);
	if (temporalSegment < 1 || temporalSegment > sizeSegmentsSpace || cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << RED << "Segmento invalido. Por favor, intente de nuevo." << RESET << endl;
		system("pause");
		system("cls");
		return -1;
	}
	return temporalSegment;
}

string ConfigEvent::getDiscountCode()
{
	string auxCode = "";
	int option = 0;
	if (codes > 0)
	{
		do {
			cout << "Posee un codigo de descuento? " << endl <<
				"1. " << GREEN << "SI" << RESET << endl <<
				"2. " << RED << "NO" << RESET << endl <<
				"Opcion: ";
			cin >> option;
			if (cin.fail() || (option < 1 || option > 2)) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << RED << "Opcion invalida. Por favor, intente de nuevo." << RESET << endl;
			}
		} while (option < 1 || option > 2);

		if (option == 1)
		{
			cout << "Digite su codigo de descuento: ";
			cin >> auxCode;
			while (!isCodeExist(auxCode))
			{
				cout << RED << "Error....No se encontro el codigo de descuento." << RESET << endl << endl;
				auxCode = "";
				cout << "Digite nuevamente el codigo: ";
				cin >> auxCode;
			}
			cout << GREEN << "Codigo encontrado" << RESET << endl;
			deleteCode(auxCode);
		}
	}
	return auxCode;
}

bool ConfigEvent::reserveSeatInSegment(int temporalSegment, string& numberReserveSeats)
{
	string chosen_seat;
	bool is_seat_reserved = false;

	typename List<Segment>::Node* currentNode = segmentsList.getHead();
	int index = 1;

	while (currentNode != nullptr && index < temporalSegment)
	{
		currentNode = currentNode->next;
		index++;
	}
	if (currentNode != nullptr)
	{
		do {
			cout << "Introduce el asiento (por ejemplo, A1): ";
			cin >> chosen_seat;
			is_seat_reserved = currentNode->data.reserveSeat(chosen_seat);

			if (!is_seat_reserved)
			{
				cout << RED << "El asiento " << chosen_seat << " no existe o ya esta reservado." << RESET << endl;
			}
		} while (!is_seat_reserved);

		client.addReservedSeat(chosen_seat);
		numberReserveSeats += chosen_seat + " ";
		cout << "Asiento " << chosen_seat << " reservado correctamente." << endl;
	}
	else
	{
		cout << RED << "Segmento no encontrado." << RESET << endl;
	}
	return is_seat_reserved;
}

float ConfigEvent::calculateTotalPrice(string auxCode, int temporalSegment)
{
	float temporalTotal = 0.0f;
	if (auxCode != "")
	{
		float precioConDescuento = applyCodeDiscount(getSegment(temporalSegment - 1));
		temporalTotal += precioConDescuento;
	}
	else
	{
		temporalTotal += getSegment(temporalSegment - 1)->getPrice();
	}
	return temporalTotal;
}

float ConfigEvent::calculateTotalDiscount(string auxCode, int temporalSegment)
{
	float temporalDiscount = 0.0f;
	if (auxCode != "")
	{
		float precioConDescuento = applyCodeDiscount(getSegment(temporalSegment - 1));
		float precioOriginal = getSegment(temporalSegment - 1)->getPrice();
		temporalDiscount += (precioOriginal - precioConDescuento);
	}
	return temporalDiscount;
}

void ConfigEvent::numberOfSeatsPurchase()
{
	int seatsPurchased = 0;
	string numberReserveSeats = "";
	processPurchase(seatsPurchased, numberReserveSeats);
	cout << "Haz comprado estos asientos: " << numberReserveSeats << endl;
}

void ConfigEvent::controlTicketSoldEvent()
{
	numberOfSeatsPurchase();
	system("pause");
	system("cls");
}

void ConfigEvent::reserveSeatInSegment(int segmentIndex, const string& seatCode)
{
	typename List<Segment>::Node* currentNode = segmentsList.getHead();  
	int index = 0;

	while (currentNode != nullptr && index < segmentIndex)
	{
		currentNode = currentNode->next;
		index++;
	}
	if (currentNode != nullptr)
	{
		if (currentNode->data.reserveSeat(seatCode))
		{
			cout << "Asiento " << seatCode << " reservado correctamente." << endl;
		}
		else
		{
			cout << "El asiento " << seatCode << " no esta disponible o no existe." << endl;
		}
	}
	else
	{
		cout << "Segmento invalido." << endl;
	}
}

void ConfigEvent::showStatusOfEvent()
{
	if (segmentsList.getSize() <= 0)
	{
		cout << RED << "ERROR. Configure un evento. " << RESET << endl << endl;
	}
	else
	{
		typename List<Segment>::Node* currentNode = segmentsList.getHead();

		while (currentNode != nullptr)
		{
			if (isFullEventTwo())
			{
				cout << RED << "EL EVENTO ESTA LLENO" << RESET << endl << endl;
				return;
			}
			cout << "Segmento:" << endl;
			currentNode->data.printSeats();
			currentNode = currentNode->next;
		}
	}
}

Segment* ConfigEvent::getSegment(int pos)
{
	typename List<Segment>::Node* currentNode = segmentsList.getHead();
	for (int i = 0; i < pos; ++i)
	{
		if (currentNode == nullptr)
		{
			cout << "Posicion fuera de rango." << endl;
			return nullptr;
		}
		currentNode = currentNode->next;
	}
	return &currentNode->data;
}

bool ConfigEvent::isSegmentExistTwo()
{
	if (getSizeSegmentsSpace() == 0)
	{
		return false;
	}
	return true;
}

bool ConfigEvent::isDiscountNumExist()
{
	if (acountWithDiscount == 0)
	{
		return false;
	}
	return true;
}

bool ConfigEvent::isCodeExist(string code) {
	typename List<string>::Node* currentNode = discountCodesList.getHead();

	while (currentNode != nullptr) { 
		if (code == currentNode->data) { 
			return true; 
		}
		currentNode = currentNode->next; 
	}
	return false;
}

bool ConfigEvent::isSeatAvailable(string& reserveSeats)
{
	for (int letter = 0; letter < totalRows; letter++)
	{
		for (int number = 0; number < totalColumns; number++)
		{
			if (availableSeats[letter][number] == reserveSeats)
			{
				return true;
			}
		}
	}
	return false;
}

bool ConfigEvent::isFullEventTwo()
{
	typename List<Segment>::Node* currentNode = segmentsList.getHead(); 

	while (currentNode != nullptr) { 
		if (!currentNode->data.isFullTheEvent()) { 
			return false;
		}
		currentNode = currentNode->next; 
	}
	return true; 
}

void ConfigEvent::resizeSegmentsSpace(int newSize)
{
	int currentSize = segmentsList.getSize();

	if (newSize > currentSize)
	{
		for (int i = 0; i < newSize - currentSize; ++i)
		{
			Segment newSegment;
			segmentsList.insertAtTheEnd(newSegment);
		}
	}
	else if (newSize < currentSize)
	{
		for (int i = 0; i < currentSize - newSize; ++i)
		{
			segmentsList.removeLast();
		}
	}
}

void ConfigEvent::changeSegmentDimension()
{
	if (!isSegmentExists())
	{
		cout << RED "ERROR. No existen segmentos creados" << RESET << endl;
		cout << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << GREEN << "Cantidad de segmentos actuales: " << getSizeSegmentsSpace() << RESET << endl << endl;
	int segmentToRefer;
	cout << "Ingrese el indice del segmento que desea modificar: ";
	cin >> segmentToRefer;
	while (segmentToRefer < 1 || segmentToRefer > 2)
	{
		cout << RED << "ERROR. Ingrese numero valido: " << RESET;
		cin >> segmentToRefer;
	}
	changePosicSegmentDimension(segmentToRefer - 1);
}

void ConfigEvent::changePosicSegmentDimension(int pos)
{
	typename List<Segment>::Node* currentNode = segmentsList.getHead();
	int index = 0;

	while (currentNode != nullptr && index < pos)
	{
		currentNode = currentNode->next;
		index++;
	}
	if (currentNode != nullptr)
	{
		if (currentNode->data.isEmpty())
		{
			int temporalRows, temporalColumns;
			float temporalPrice;
			cout << "SEGMENTO VACIO." << endl << endl;
			cout << "1. Cambiar dimensiones" << endl;
			cout << "2. Eliminar segmento" << endl;
			int option;
			cin >> option;

			while (option < 1 || option > 2)
			{
				cout << RED << "ERROR. Ingrese numero valido: " << RESET;
				cin >> option;
			}
			if (option == 1)
			{
				cout << "Ingrese nueva fila: ";
				cin >> temporalRows;
				cout << "Ingrese nueva columna: ";
				cin >> temporalColumns;
				cout << "Ingrese el nuevo precio: ";
				cin >> temporalPrice;
				system("cls");
				currentNode->data.updateData(temporalRows, temporalColumns, temporalPrice);
				cout << GREEN << "SEGMENTO ACTUALIZADO CORRECTAMENTE." << RESET << endl;
				cout << endl;
				system("pause");
				system("cls");
			}
			else if (option == 2)
			{
				system("cls");
				removeSegment(pos);
				cout << GREEN << "SEGMENTO ELIMINADO CORRECTAMENTE." << RESET << endl;
				cout << endl;
				system("pause");
				system("cls");
			}
		}
		else
		{
			system("cls");
			cout << RED << "ERROR. el segmento almenos tiene un asiento ocupado." << RESET << endl;
			system("pause");
			system("cls");
		}
	}
}

void ConfigEvent::deleteSpecificCodeDiscount()
{
	string tempCode;
	cout << "Ingrese el codigo que desea eliminar: " << endl;
	cin >> tempCode;

	List<string>::Node* current = discountCodesList.getHead();
	List<string>::Node* previous = nullptr;

	while (current != nullptr)
	{
		if (current->data == tempCode)
		{
			if (previous == nullptr)
			{
				discountCodesList.deleteNode(current);
				current = discountCodesList.getHead();
			}
			else
			{
				previous->next = current->next;
				delete current;
				current = previous->next; 
			}
			system("cls");
			cout << GREEN << "Codigo eliminado exitosamente." << RESET << endl;
			cout << endl;
			system("pause");
			system("cls");
			return;
		}
		previous = current;
		current = current->next;
	}
	system("cls");
	cout << RED << "Codigo no encontrado." << RESET << endl;
	cout << endl;
	system("pause");
	system("cls");
}

void ConfigEvent::restoreDiscountCode(string& code)
{
	discountCodesList.insertAtTheEnd(code);
}

void ConfigEvent::deleteTickets()
{
	int segmentIndex;
	cout << "Ingrese segmento donde desea eliminar el asiento: ";
	cin >> segmentIndex;

	if (segmentIndex < 1 || segmentIndex > sizeSegmentsSpace)
	{
		cout << RED << "Segmento invalido." << RESET << endl;
		return;
	}

	string seatCode;
	cout << "Ingrese el codigo del asiento a eliminar: ";
	cin >> seatCode;
	Segment* segment = getSegment(segmentIndex - 1);
	if (segment == nullptr)
	{
		cout << RED << "Segmento no encontrado." << RESET << endl;
		return;
	}
	if (!segment->isSeatReserved(seatCode))
	{
		segment->resetSeats(seatCode);
		char usedDiscount;
		cout << "¿Se utilizo un codigo de descuento para este asiento? (s/n): ";
		cin >> usedDiscount;

		if (usedDiscount == 's' || usedDiscount == 'S')
		{
			string discountCode;
			bool validCode = false;
			do
			{
				cout << "Ingrese el código de descuento utilizado: ";
				cin >> discountCode;

				if (discountCodesList.findData(discountCode))
				{
					cout << RED << "Codigo vigente. " << RESET << endl;
				}
				else if (temporalCodesList.findData(discountCode))
				{
					restoreDiscountCode(discountCode);
					validCode = true;
				}
				else
				{
					cout << RED << "Codigo no valido. Ingrese un codigo que anteriormente existia." << RESET << endl;
				}
			} while (!validCode);
		}
		cout << "Entrada eliminada y asiento reestablecido correctamente." << endl;
	}
	else
	{
		cout << RED << "El asiento no esta reservado o no existe." << RESET << endl;
	}
}

void ConfigEvent::captureEventData(int& temporalRows, int& temporalColumns, float temporalPrice)
{
	float aux = 0.0;
	cout << endl << BRIGHT_WHITE << "Ingrese el nombre del evento: " << RESET;
	cin.ignore();
	getline(cin, nameEvent);
	while (nameEvent.empty())
	{
		cout << RED << "ERROR. " << RESET << "Ingrese un nombre verdadero de evento: ";
		getline(cin, nameEvent);
	}
	cout << BRIGHT_WHITE << "Ingrese la fecha del evento (formato DD/MM/YYYY): " << RESET;
	getline(cin, dateEvent);
	while (dateEvent.empty())
	{
		cout << RED << "ERROR. " << RESET << "Ingrese una fecha verdadera de evento: ";
		getline(cin, dateEvent);
	}
	dateProcessorTool.confirmDateEvent(dateEvent);
	printSeparatorIdeas();
	cout << BRIGHT_WHITE << "Ingrese el numero de segmentos (mayor a 0): " << RESET;
	cin >> aux;
	segmentsEvent = static_cast<int>(aux);
	printSeparatorIdeas();
	confirmSegment();
	sizeSegmentsSpace = segmentsEvent;
	resizeSegmentsSpace(segmentsEvent);

	cout << BRIGHT_WHITE << "Ingrese la cantidad de entradas que desea que posean descuento: " << RESET;
	cin >> aux;
	acountWithDiscount = static_cast<int>(aux);
	codes = acountWithDiscount;
	createVectorDiscounts(acountWithDiscount);
	generateDiscountCodes();

	if (acountWithDiscount != 0)
	{
		cout << BRIGHT_WHITE << "Ingrese el porcentaje de descuento deseado: " << RESET;
		cin >> aux;
		discount = static_cast<int>(aux);
		printSeparatorIdeas();
	}
	else
	{
		discount = 0;
		printSeparatorIdeas();
	}
	typename List<Segment>::Node* currentNode = segmentsList.getHead(); 
	for (int i = 0; currentNode != nullptr; i++)
	{
		cout << BRIGHT_WHITE << "Ingrese el numero de filas del segmento " << RESET << i + 1 << ": ";
		cin >> aux;
		temporalRows = static_cast<int>(aux);

		cout << BRIGHT_WHITE << "Ingrese el numero de columnas del segmento " << RESET << i + 1 << ": ";
		cin >> aux;
		temporalColumns = static_cast<int>(aux);

		cout << BRIGHT_WHITE << "Ingrese el precio de cada asiento del segmento " << RESET << i + 1 << ": ";
		cin >> temporalPrice;
		printSeparatorIdeas();

		currentNode->data.updateData(temporalRows, temporalColumns, temporalPrice);

		currentNode = currentNode->next;
	}
	freeSeats = calculateTotalSeats();
}

void ConfigEvent::printInvoice(int seatsPurchased, float anApplyDiscount, float aTotalPrice, float anFinalPrice)
{
	cout << endl << BRIGHT_CYAN << "\t     Factura" << endl
		<< " ----------------------------------" << endl << YELLOW << " | "
		<< " | Nombre del evento: " << nameEvent << endl << " | Fecha del evento: " << dateEvent << endl
		<< " ----------------------------------" << endl << LIGHT_PURPLE << " |\t Informacion personal." << endl
		<< " | " << endl << " | Nombre del Usuario:" << client.getPersonName() << endl
		<< " | Numero de Identificacion: " << client.getIdentification() << endl
		<< " | Fecha de nacimiento: " << client.getBirthdayDate() << endl
		<< " | " << endl << BRIGHT_YELLOW << " |\t Informacion de compra." << endl << " |" << endl
		<< " | Cantidad de Asientos adquiridos: " << seatsPurchased << endl << GREEN
		<< " | Precio total (sin descuento): " << aTotalPrice << endl << RED
		<< " | Cantidad del descuento aplicado: " << anApplyDiscount << endl
		<< " | " << endl << YELLOW << " |   Precio total a cancelar: " << anFinalPrice << endl
		<< " | " << endl << " ----------------------------------" << endl << BRIGHT_CYAN
		<< " | Gracias por adquirir cu entrada |" << endl << " |    con nosotros esperamos su    | "
		<< endl << " |     disfrute en este Evento     | " << endl
		<< " -----------------------------------" << endl << RESET;
}

void ConfigEvent::aboutUs()
{
	cout << BRIGHT_CYAN << "\t\t\t\t\t       ABOUT US:\n";
	cout << GREEN << "\t\t\t\t    _    ____  ____  ___    _    _   _ \n";
	cout << "\t\t\t\t   / \\  |  _ \\|  _ \\|_ _|  / \\  | \\ | |\n";
	cout << "\t\t\t\t  / _ \\ | | | | |_) || |  / _ \\ |  \\| |\n";
	cout << "\t\t\t\t / ___ \\| |_| |  _ < | | / ___ \\| |\\  |\n";
	cout << "\t\t\t\t/_/   \\_\\____/|_| \\_\\___/_/   \\_\\_| \\_|\n";
	cout << "\n";
	cout << YELLOW "\t\t\t\t\t\t__   __\n";
	cout << "\t\t\t\t\t\t\\ \\ / /\n";
	cout << "\t\t\t\t\t\t \\ V / \n";
	cout << "\t\t\t\t\t\t  | |  \n";
	cout << "\t\t\t\t\t\t  |_|  \n";
	cout << "\n";
	cout << RED << "\t\t\t\t       _ _____ _____ _____ ______  \n";
	cout << "\t\t\t\t      | | ____|  ___|  ___|  ___/ \n";
	cout << "\t\t\t\t   _  | |  _| | |_  | |_  |  _|   \n";
	cout << "\t\t\t\t  | |_| | |___|  _| |  _| | |___  \n";
	cout << "\t\t\t\t   \\___/|_____|_|   |_|   |_____|\n" << "\n";
	cout << BRIGHT_CYAN << "\t\t\t\t     Aspirantes a Ing.Sistemas." << RESET;
}