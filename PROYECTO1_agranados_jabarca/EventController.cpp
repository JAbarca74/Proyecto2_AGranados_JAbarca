#include "EventController.h"

void EventController::printPrincipalMenu()
{
	cout << YELLOW << "MENU PRINCIPAL" << RESET << endl << endl
		<< BRIGHT_BLUE "1. " << RESET << "Configurar Evento." << endl << endl
		<< BRIGHT_BLUE "2. " << RESET << "Crear Codigo de Descuento." << RESET << endl << endl
		<< BRIGHT_BLUE "3. " << RESET << "Comprar Entrada." << RESET << endl << endl
		<< BRIGHT_BLUE "4. " << RESET << "Observar Disponibilidad de Asientos." << RESET << endl << endl
		<< BRIGHT_BLUE "5. " << RESET << "Eliminar Entrada Vendida." << RESET << endl << endl
		<< BRIGHT_BLUE "6. " << RESET << "Cargar Evento txt." << RESET << endl << endl
		<< BRIGHT_BLUE "7. " << RESET << "Acerca de." << RESET << endl << endl
		<< BRIGHT_BLUE "8. " << RESET << "Finalizar." << RESET << endl;
}

void EventController::printConfigMenu()
{
	cout << YELLOW << "CONFIGURACION DEL EVENTO " << RESET << endl << endl
		<< BRIGHT_BLUE << "1. " << RESET << "Crear un nuevo evento." << endl << endl
		<< BRIGHT_BLUE << "2. " << RESET << "Ver evento actual." << endl << endl
		<< BRIGHT_BLUE << "3. " << RESET << "Actualizar segmento." << endl << endl
		<< BRIGHT_BLUE << "4. " << RESET << "Finalizar evento." << endl << endl
		<< BRIGHT_BLUE << "5. " << RESET << "Volver." << endl;
}

void EventController::printConfigPriceDiscountMenu()
{
	cout << YELLOW << "CONFIGURACION DE DESCUENTOS " << endl << endl
		<< BRIGHT_BLUE << "1. " << RESET << "Obtener codigo de descuento. " << endl << endl
		<< BRIGHT_BLUE << "2. " << RESET << "Eliminar codigo de descuento. " << endl << endl
		<< BRIGHT_BLUE << "3. " << RESET << "Volver. " << endl;
}

void EventController::printTicketSellMenu()
{
	cout << YELLOW << "TAQUILLA DE TIQUETES " << RESET << endl << endl
		<< BRIGHT_BLUE << "1. " << RESET << "Comprar tiquetes. " << endl << endl
		<< BRIGHT_BLUE << "2. " << RESET << "Visualizar disponibilidad asientos. " << endl << endl
		<< BRIGHT_BLUE << "3. " << RESET << "Volver. " << endl;
}

void EventController::printShowSegmentSeatsFlow(const int& segmentNumber)
{
	for (int i = 0; i < segmentNumber; i++)
	{
		cout << i + 1 << ". Segmento " << i + 1 << endl;
	}
}

void EventController::printMenuDeleteFlow()
{
	cout << YELLOW << "ELIMINAR ENTRADA" << endl << endl
		<< BRIGHT_BLUE << "1. " << RESET << "Eliminar entradas. " << endl << endl
		<< BRIGHT_BLUE << "2. " << RESET << "Volver. " << endl;
}

void EventController::validateUserOption(int& userOption)
{
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << endl << RED << "No se permiten letras, " << RESET
			<< "por favor vuelva a intentarlo: ";
		cin >> userOption;
	}
}

void EventController::captureMenuOption()
{
	cout << endl << endl << BRIGHT_CYAN << "Escoja una opcion: " << RESET;
	cin >> userOption;
	validateUserOption(userOption);
	system("cls");
}

void EventController::controlConfigMenuFlow()
{
	system("cls");
	printConfigMenu();
	captureMenuOption();
	while (userOption < 1 || userOption > 5)
	{
		cout << RED << "Seleccione una opcion entre 1 y 4" << RESET << endl << endl;
		printConfigMenu();
		captureMenuOption();
	}
	if (userOption == 1)
	{
		configEvent.prepareEventData();
		system("cls");
	}
	else if (userOption == 2)
	{
		configEvent.printExportCurrentEvent();
		system("cls");
	}
	else if (userOption == 3)
	{
		configEvent.changeSegmentDimension();
		system("cls");
	}
	else if (userOption == 4)
	{
		configEvent.deleteEvent();
		system("cls");
	}
	else if (userOption == 5)
	{
		cout << GREEN << "Usted sera regresado al menu principal" << RESET << endl << endl;
		system("pause");
		system("cls");
	}
}

void EventController::controlPriceDiscountMenuFlow()
{
	system("cls");
	if (!configEvent.isDiscountNumExist()) {
		cout << RED << "Error....No hay descuentos disponibles." << RESET << endl;
		cout << endl;
		system("pause");
		system("cls");
		return;
	}
	printConfigPriceDiscountMenu();
	captureMenuOption();
	system("cls");

	while (userOption < 1 || userOption > 3)
	{
		cout << RED << "Seleccione una opcion entre 1 y 2" << RESET << endl << endl;
		printConfigPriceDiscountMenu();
		captureMenuOption();
	}
	if (userOption == 1)
	{
		configEvent.printCodes();
	}
	else if (userOption == 2)
	{
		configEvent.deleteSpecificCodeDiscount();
	}
	else if (userOption == 3)
	{
		cout << GREEN << "Usted sera regresado al menu principal" << RESET << endl << endl;
		system("pause");
		system("cls");
	}
}

void EventController::printAboutUs()
{
	system("cls");
	configEvent.aboutUs();
	cout << endl << endl;
	system("pause");
	system("cls");
}

void EventController::controlTicketSellMenuFlow()
{
	system("cls");
	if (!configEvent.isSegmentExistTwo()) {
		cout << RED << "Error....No existen eventos." << RESET << endl;
		cout << endl;
		system("pause");
		system("cls");
		return;
	}
	
	printTicketSellMenu();
	captureMenuOption();
	while (userOption < 1 || userOption > 3)
	{
		cout << RED << "Seleccione una opcion entre 1 y 3" << RESET << endl << endl;
		printTicketSellMenu();
		captureMenuOption();
	}

	if (userOption == 1)
	{
		configEvent.showStatusOfEvent();
		if (configEvent.isFullEventTwo())
		{
			system("pause");
			system("cls");
			return;
		}
		configEvent.numberOfSeatsPurchase();
	}
	else if (userOption == 2)
	{
		configEvent.showStatusOfEvent();
		system("pause");
		system("cls");
	}
	else if (userOption == 3)
	{
		cout << GREEN << "Usted sera regresado al menu principal" << RESET << endl << endl;
		system("pause");
		system("cls");
	}
}

void EventController::controlDeleteTicketMenuFlow()
{
	if (configEvent.isEmptyTheEvent())
	{
		cout << RED << "Error....No hay entradas compradas." << RESET << endl;
		cout << endl;
		system("pause");
		system("cls");
		return;
	}
	printMenuDeleteFlow();
	captureMenuOption();
	while (userOption < 1 || userOption > 3)
	{
		cout << RED << "Seleccione una opcion entre 1 y 2" << RESET << endl << endl;
		printMenuDeleteFlow();
		captureMenuOption();
	}
	if (userOption == 1)
	{
		configEvent.deleteTickets();
	}
	else if (userOption == 2)
	{
		cout << GREEN << "Usted sera regresado al menu principal" << RESET << endl << endl;
		system("pause");
		system("cls");
	}
}

void EventController::controlPrincipalMenuFlow()
{
	while (true)
	{
		printPrincipalMenu();
		captureMenuOption();
		if (userOption == 1)
		{
			controlConfigMenuFlow();
		}
		else if (userOption == 2)
		{
			controlPriceDiscountMenuFlow();
		}
		else if (userOption == 3)
		{
			controlTicketSellMenuFlow();
		}
		else if (userOption == 4)
		{
			configEvent.showStatusOfEvent();
			system("pause");
			system("cls");
		}
		else if (userOption == 5)
		{
			controlDeleteTicketMenuFlow();
		}
		else if (userOption == 6)
		{
			archive.loadFromFile();
			cout << GREEN << "Archivo cargado correctamente" << RESET << endl;
			system("pause");
			system("cls");
		}
		else if (userOption == 7)
		{
			printAboutUs();
		}
		else if (userOption == 8)
		{
			cout << GREEN << "Saliendo del programa... " << RESET << endl;
			break;
		}
		else
		{
			cout << RED << "Numero de opcion no valido para este menu" << RESET << endl << endl;
		}
	}
}