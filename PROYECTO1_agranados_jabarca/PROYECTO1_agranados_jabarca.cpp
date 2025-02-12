#include <iostream>
#include "Archive.h"
#include "List.h"
#include "Invoice.h"
#include "Segment.h"
#include "ReportViewer.h"
#include "Client.h"
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ConfigEvent.h"
#include <sstream>
#include <iomanip>
using namespace std;
using namespace sf;


const int maxTotalSeats = 100;
const int SEAT_SIZE = 40; 
const int SEAT_SPACING = 10; 
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 50;

string getUserInputs(RenderWindow& window, Font& font, const string& prompt) {
    string input = "";
    Text textInput, label, errorText;
    RectangleShape inputBox(Vector2f(400, 50));
    Button acceptButton(Vector2f(100, 50), Vector2f(350, 250), font, "Aceptar", Color::Green);

    inputBox.setPosition(200, 150);
    inputBox.setFillColor(Color::White);
    textInput.setFont(font);
    textInput.setCharacterSize(24);
    textInput.setFillColor(Color::Black);
    textInput.setPosition(210, 160);
    label.setFont(font);
    label.setCharacterSize(20);
    label.setFillColor(Color::White);
    label.setString(prompt);
    label.setPosition(200, 100);
    errorText.setFont(font);
    errorText.setCharacterSize(18);
    errorText.setFillColor(Color::Red);
    errorText.setPosition(200, 210);

    bool isActive = true;
    while (isActive && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::TextEntered) {
                if (event.text.unicode == 8 && !input.empty()) {
                    input.pop_back();
                }
                else if (event.text.unicode < 128) {
                    input += static_cast<char>(event.text.unicode);
                }
            }
            if (acceptButton.ButtonIsClicked(window)) {
                if (!input.empty()) isActive = false;
                else errorText.setString("Campo vacío. Intente de nuevo.");
            }
        }
        textInput.setString(input);
        window.clear(Color(50, 50, 50));
        window.draw(inputBox);
        window.draw(textInput);
        window.draw(label);
        window.draw(errorText);
        acceptButton.draw(window);
        window.display();
    }
    return input;
}

void clearFile(const string& filename) 
{
    ofstream file(filename, ofstream::out | ofstream::trunc);
    if (file.is_open()) {
        file.close();
        cout << "El archivo \"" << filename << "\" ha sido limpiado correctamente." << endl;
    }
    else {
        cerr << "Error: no se pudo abrir \"" << filename << "\" para limpiarlo." << endl;
    }
}

int getNumericInputs(RenderWindow& window, Font& font, const string& prompt, int minValue = 1, int maxValue = 1000) {
    string input = "";
    Text textInput, label, errorText;
    RectangleShape inputBox(Vector2f(400, 50));
    Button acceptButton(Vector2f(100, 50), Vector2f(350, 250), font, "Aceptar", Color::Green);

    inputBox.setPosition(200, 150);
    inputBox.setFillColor(Color::White);

    textInput.setFont(font);
    textInput.setCharacterSize(24);
    textInput.setFillColor(Color::Black);
    textInput.setPosition(210, 160);

    label.setFont(font);
    label.setCharacterSize(20);
    label.setFillColor(Color::White);
    label.setString(prompt);
    label.setPosition(200, 100);

    errorText.setFont(font);
    errorText.setCharacterSize(18);
    errorText.setFillColor(Color::Red);
    errorText.setPosition(200, 210);

    bool isActive = true;
    while (isActive && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered) {
                if (event.text.unicode == 8 && !input.empty()) {
                    input.pop_back();
                }
                else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    input += static_cast<char>(event.text.unicode);
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                int num = input.empty() ? -1 : stoi(input);
                if (num >= minValue && num <= maxValue) {
                    isActive = false;
                }
                else {
                    errorText.setString("Valor inválido. Debe ser un número entre " + to_string(minValue) + " y " + to_string(maxValue) + ".");
                    input = "";
                }
            }
            if (acceptButton.ButtonIsClicked(window)) {
                int num = input.empty() ? -1 : stoi(input);
                if (num >= minValue && num <= maxValue) {
                    isActive = false;
                }
                else {
                    errorText.setString("Valor inválido. Debe ser un número entre " + to_string(minValue) + " y " + to_string(maxValue) + ".");
                    input = "";
                }
            }
        }
        textInput.setString(input);
        window.clear(Color(50, 50, 50));
        window.draw(inputBox);
        window.draw(textInput);
        window.draw(label);
        window.draw(errorText);
        acceptButton.draw(window);
        window.display();
    }
    return stoi(input);
}

int getNumericInputsTwo(RenderWindow& window, Font& font, const string& prompt, int minValue = 1, int maxValue = 1000) {
    string input = "";
    Text textInput, label, errorText;
    RectangleShape inputBox(Vector2f(400, 50));
    Button acceptButton(Vector2f(100, 50), Vector2f(350, 250), font, "Aceptar", Color::Green);

    inputBox.setPosition(200, 150);
    inputBox.setFillColor(Color::White);

    textInput.setFont(font);
    textInput.setCharacterSize(24);
    textInput.setFillColor(Color::Black);
    textInput.setPosition(210, 160);

    label.setFont(font);
    label.setCharacterSize(20);
    label.setFillColor(Color::White);
    label.setString(prompt);
    label.setPosition(200, 100);

    errorText.setFont(font);
    errorText.setCharacterSize(18);
    errorText.setFillColor(Color::Red);
    errorText.setPosition(200, 210);

    bool isActive = true;
    while (isActive && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered) {
                if (event.text.unicode == 8 && !input.empty()) {
                    input.pop_back();
                }
                else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    input += static_cast<char>(event.text.unicode);
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                int num = input.empty() ? -1 : stoi(input);
                if (num >= minValue && num <= maxValue) {
                    isActive = false;
                }
                else {
                    errorText.setString("Valor inválido. Debe ser un número entre " + to_string(minValue) + " y " + to_string(maxValue) + ".");
                    input = "";
                }
            }
            if (acceptButton.ButtonIsClicked(window)) {
                int num = input.empty() ? -1 : stoi(input);
                if (num >= minValue && num <= maxValue) {
                    isActive = false;
                }
                else {
                    errorText.setString("Valor inválido. Debe ser un número entre " + to_string(minValue) + " y " + to_string(maxValue) + ".");
                    input = "";
                }
            }
        }
        textInput.setString(input);
        window.clear(Color(50, 50, 50));
        window.draw(inputBox);
        window.draw(textInput);
        window.draw(label);
        window.draw(errorText);
        acceptButton.draw(window);
        window.display();
    }
    return stoi(input);
}

float getFloatInputs(RenderWindow& window, Font& font, const string& prompt, float minValue = 1.0, float maxValue = 100000000000000.0) { //obtiene flotantes
    string input = "";
    Text textInput, label, errorText;
    RectangleShape inputBox(Vector2f(400, 50));
    Button acceptButton(Vector2f(100, 50), Vector2f(350, 250), font, "Aceptar", Color::Green);

    inputBox.setPosition(200, 150);
    inputBox.setFillColor(Color::White);

    textInput.setFont(font);
    textInput.setCharacterSize(24);
    textInput.setFillColor(Color::Black);
    textInput.setPosition(210, 160);

    label.setFont(font);
    label.setCharacterSize(20);
    label.setFillColor(Color::White);
    label.setString(prompt);
    label.setPosition(200, 100);

    errorText.setFont(font);
    errorText.setCharacterSize(18);
    errorText.setFillColor(Color::Red);
    errorText.setPosition(200, 210);

    bool isActive = true;
    while (isActive && window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered) 
            {
                if (event.text.unicode == 8 && !input.empty()) 
                {
                    input.pop_back();
                }
                else if ((event.text.unicode >= '0' && event.text.unicode <= '9') || event.text.unicode == '.') 
                {
                    input += static_cast<char>(event.text.unicode);
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) 
            {
                float num = input.empty() ? -1 : stof(input);
                if (num >= minValue && num <= maxValue) {
                    isActive = false;
                }
                else {
                    errorText.setString("Valor inválido. Debe ser un número entre " + to_string(minValue) + " y " + to_string(maxValue) + ".");
                    input = "";
                }
            }
            if (acceptButton.ButtonIsClicked(window)) 
            {
                float num = input.empty() ? -1 : stof(input);
                if (num >= minValue && num <= maxValue) 
                {
                    isActive = false;
                }
                else {
                    errorText.setString("Valor inválido. Debe ser un número entre " + to_string(minValue) + " y " + to_string(maxValue) + ".");
                    input = "";
                }
            }
        }
        textInput.setString(input);
        window.clear(Color(50, 50, 50));
        window.draw(inputBox);
        window.draw(textInput);
        window.draw(label);
        window.draw(errorText);
        acceptButton.draw(window);
        window.display();
    }
    return stof(input);
}

void collectClientInformation(RenderWindow& window, Font& font, Client& client, DateProcessorTool& dateProcessor) {
    string identification;
    do {
        identification = getUserInputs(window, font, "Ingrese su número de cédula (9 dígitos):");
        client.validateID(identification);
        if (!client.isValidClient(identification)) {
            identification = ""; 
        }
    } while (identification.empty());
    client.addIdentificationList(identification);

    string name;
    do {
        name = getUserInputs(window, font, "Ingrese su nombre completo:");
    } while (name.empty());
    client.setPersonName(name);

    string birthDate;
    do {
        birthDate = getUserInputs(window, font, "Ingrese su fecha de nacimiento (DD/MM/YYYY):");
    } while (!dateProcessor.isDateValid(birthDate) || !dateProcessor.isAdult(birthDate));
    client.setBirthdayDate(birthDate);
}

void printInvoice(RenderWindow& window,List<PurchasedSeat>& purchasedSeats,ConfigEvent& configEvent,Client& client,Font* font)
{ 
    float totalBase = 0, totalDiscount = 0, totalFinal = 0;
    List<PurchasedSeat>::Node* node = purchasedSeats.getHead();
    while (node != nullptr) {
        totalBase += node->data.basePrice;
        totalDiscount += node->data.discountAmount;
        totalFinal += node->data.finalPrice;
        node = node->next;
    }
    int numSegments = configEvent.getSizeSegmentsSpace();
    string seatsGroup[100]; 
    for (int i = 0; i < numSegments; i++) {
        seatsGroup[i] = "";
    }
    node = purchasedSeats.getHead();
    while (node != nullptr) {
        int segIndex = node->data.segmentIndex;
        if (!seatsGroup[segIndex].empty()) {
            seatsGroup[segIndex] += ", ";
        }
        seatsGroup[segIndex] += node->data.seatCode;
        node = node->next;
    }
    string invoiceLines[50];  
    int lineCount = 0;
    invoiceLines[lineCount++] = "Factura de Compra";
    invoiceLines[lineCount++] = "Evento: " + configEvent.getNameEvent();
    invoiceLines[lineCount++] = "Fecha del evento: " + configEvent.getDateEvent();
    invoiceLines[lineCount++] = "Cliente: " + client.getPersonName();
    invoiceLines[lineCount++] = "Cedula: " + client.getIdentification();
    invoiceLines[lineCount++] = "----------------------------------------";

    for (int i = 0; i < numSegments; i++) {
        if (!seatsGroup[i].empty()) {
            stringstream ss;
            ss << "Segmento " << (i + 1) << ": " << seatsGroup[i];
            invoiceLines[lineCount++] = ss.str();
        }
    }
    invoiceLines[lineCount++] = "----------------------------------------";
    {
        stringstream ss;
        ss << "Precio base: $" << fixed << setprecision(2) << totalBase;
        invoiceLines[lineCount++] = ss.str();
    }
    {
        stringstream ss;
        ss << "Descuento aplicado: $" << fixed << setprecision(2) << totalDiscount;
        invoiceLines[lineCount++] = ss.str();
    }
    {
        stringstream ss;
        ss << "Precio final: $" << fixed << setprecision(2) << totalFinal;
        invoiceLines[lineCount++] = ss.str();
    }

    bool invoiceOpen = true;
    while (invoiceOpen && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
                invoiceOpen = false;
        }

        window.clear(Color::Black);
        float y = 30.0f;
        for (int i = 0; i < lineCount; i++) {
            Text text;
            text.setFont(*font);
            text.setString(invoiceLines[i]);
            text.setCharacterSize(24);
            text.setFillColor(Color::White);
            text.setPosition(30, y);
            window.draw(text);
            y += 40;
        }
        window.display();
    }
}

void saveEventDataFree(const string& filename, ConfigEvent& configEvent) {
    ofstream file(filename, ofstream::out | ofstream::trunc);
    if (!file.is_open()) {
        cerr << "Error: no se pudo abrir " << filename << " para guardar los datos del evento." << endl;
        return;
    }

    file << configEvent.getNameEvent() << "\n";

    file << configEvent.getDateEvent() << "\n";

    int numSegments = configEvent.getSizeSegmentsSpace(); 
    file << numSegments << "\n";

    for (int i = 0; i < numSegments; i++) {
        Segment* seg = configEvent.getSegment(i);
        if (seg != nullptr) {
            file << seg->getNumberSeatingRows() << " "
                << seg->getNumberSeatingColumns() << " "
                << seg->getPrice() << "\n";
        }
        else {
            file << "0 0 0\n";
        }
    }

    file << configEvent.getCodeDiscount() << "\n";

    file << configEvent.getDiscount() << "\n";
    List<string>& codes = configEvent.getDiscountCodes();
    List<string>::Node* node = codes.getHead();
    while (node != nullptr) {
        file << node->data << " ";
        node = node->next;
    }
    file << "\n";

    file.close();
    cout << "Datos del evento guardados correctamente en " << filename << endl;
}

void editSegmentUI(RenderWindow& window, Font* font, ConfigEvent& configEvent) {
    int numSegments = (configEvent.getSizeSegmentsSpace()/2);
    if (numSegments <= 0) {
        cout << "No hay segmentos registrados." << endl;
        return;
    }
    Button** segButtons = new Button * [numSegments];
    for (int i = 0; i < numSegments; i++) {
        segButtons[i] = new Button(Vector2f(200, 50), Vector2f(100, 100 + i * 60),
            *font, "Segmento " + to_string(i + 1), Color::Blue);
    }

    int selectedSegment = -1;
    bool selecting = true;
    while (selecting && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(50, 50, 50));
        for (int i = 0; i < numSegments; i++) {
            segButtons[i]->draw(window);
            if (segButtons[i]->ButtonIsClicked(window)) {
                selectedSegment = i;
                selecting = false;
            }
        }
        window.display();
    }
    for (int i = 0; i < numSegments; i++) {
        delete segButtons[i];
    }
    delete[] segButtons;

    if (selectedSegment < 0 || selectedSegment >= numSegments) {
        cout << "No se seleccionó ningún segmento." << endl;
        return;
    }

    Segment* seg = configEvent.getSegment(selectedSegment);
    if (seg == nullptr) {
        cout << "Error: segmento no encontrado." << endl;
        return;
    }
    bool updated = false;

    if (seg->hasPurchasedSeats()) {
        float newPrice = getFloatInputs(window, *font,
            "Ingrese el nuevo precio para el segmento (asientos vendidos, solo precio):", 1.0, 10000.0);
        seg->setPrice(newPrice);
        cout << "Segmento " << (selectedSegment + 1) << " actualizado (solo precio modificado, asientos vendidos)." << endl;
        updated = true;
    }
    else {

        int newRows = getNumericInputs(window, *font, "Ingrese el nuevo número de filas:", 1, 100);
        int newCols = getNumericInputs(window, *font, "Ingrese el nuevo número de columnas:", 1, 100);
        float newPrice = getFloatInputs(window, *font, "Ingrese el nuevo precio para el segmento:", 1.0, 10000.0);
        seg->setNumberRows(newRows);
        seg->setNumberColumns(newCols);
        seg->setPrice(newPrice);
        seg->updateData(*font);
        cout << "Segmento " << (selectedSegment + 1) << " actualizado (filas, columnas y precio)." << endl;
        updated = true;
    }
    if (updated) {
        saveEventDataFree("event.txt", configEvent);
    }
    Text msg;
    msg.setFont(*font);
    msg.setCharacterSize(24);
    msg.setFillColor(Color::White);
    msg.setString("Segmento actualizado correctamente.");
    msg.setPosition(100, 100);
    window.clear(Color(50, 50, 50));
    window.draw(msg);
    window.display();
    sf::sleep(sf::seconds(2));
}

void loadEventData(const string& filename, ConfigEvent& configEvent) {
    configEvent.deleteEvent();  
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << " para cargar el evento." << endl;
        return;
    }

    string line;

    if (getline(file, line)) {
        configEvent.setNameEvent(line);
    }
    else {
        cerr << "Error leyendo el nombre del evento." << endl;
        return;
    }
    if (getline(file, line)) {
        configEvent.setDateEvent(line);
    }
    else {
        cerr << "Error leyendo la fecha del evento." << endl;
        return;
    }
    int numSegments = 0;
    if (getline(file, line)) {
        istringstream iss(line);
        iss >> numSegments;
        configEvent.setSegmentSpace(numSegments);
    }
    else {
        cerr << "Error leyendo el número de segmentos." << endl;
        return;
    }
    for (int i = 0; i < numSegments; i++) 
    {
        if (getline(file, line)) 
        {
            istringstream iss(line);
            int filas, columnas;
            float precio;
            if (iss >> filas >> columnas >> precio) 
            {
                Segment* newSegment = new Segment();
                newSegment->setNumberRows(filas);
                newSegment->setNumberColumns(columnas);
                newSegment->setPrice(precio);
                configEvent.addSegment(newSegment);
            }
            else {
                cerr << "Error leyendo los datos del segmento " << (i + 1) << endl;
            }
        }
        else {
            cerr << "No se encontraron datos para el segmento " << (i + 1) << endl;
        }
    }
    int discountSeats = 0;
    if (getline(file, line)) {
        istringstream iss(line);
        iss >> discountSeats;
        configEvent.setCodeDiscount(discountSeats);
    }
    else {
        cerr << "Error leyendo la cantidad de asientos con descuento." << endl;
    }
    int discountPercentage = 0;
    if (getline(file, line)) {
        istringstream iss(line);
        iss >> discountPercentage;
        configEvent.setDiscount(discountPercentage);
    }
    else {
        cerr << "Error leyendo el porcentaje de descuento." << endl;
    }
    if (getline(file, line)) {
        istringstream iss(line);
        string code;
        while (iss >> code) {
            configEvent.addDiscountCode(code);
        }
    }
    else {
        cerr << "No se encontraron códigos de descuento." << endl;
    }
    file.close();
    cout << "Evento cargado correctamente desde " << filename << endl;
}

void deleteSegmentUI(RenderWindow& window, Font* font, ConfigEvent& configEvent) {
    
    int numSegments = configEvent.getSizeSegmentsSpace();
    numSegments = numSegments / 2;
    if (numSegments <= 0) {
        cout << "No hay segmentos para eliminar." << endl;
        return;
    }

    Button** segButtons = new Button * [numSegments];
    for (int i = 0; i < numSegments; i++) {
        segButtons[i] = new Button(Vector2f(200, 50), Vector2f(100, 100 + i * 60),
            *font, "Segmento " + to_string(i + 1), Color::Blue);
    }

    int selectedSegment = -1;
    bool selecting = true;
    while (selecting && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(50, 50, 50));
        for (int i = 0; i < numSegments; i++) {
            segButtons[i]->draw(window);
            if (segButtons[i]->ButtonIsClicked(window)) {
                selectedSegment = i;
                selecting = false;
            }
        }
        window.display();
    }

    for (int i = 0; i < numSegments; i++) {
        delete segButtons[i];
    }
    delete[] segButtons;

    Segment* seg = configEvent.getSegment(selectedSegment);
    if (seg == nullptr) {
        cout << "Error: segmento no encontrado." << endl;
        return;
    }

    if (seg->hasPurchasedSeats()) {
        cout << "No se puede eliminar el segmento " << (selectedSegment + 1)
            << " porque tiene asientos vendidos." << endl;

        Text msg;
        msg.setFont(*font);
        msg.setCharacterSize(24);
        msg.setFillColor(Color::White);
        msg.setString("No se puede eliminar: asientos vendidos.");
        msg.setPosition(100, 100);
        window.clear(Color(50, 50, 50));
        window.draw(msg);
        window.display();
        sf::sleep(seconds(2));
        return;
    }
    Button yesButton(Vector2f(150, 50), Vector2f(400, 300), *font, "Sí", Color::Green);
    Button noButton(Vector2f(150, 50), Vector2f(600, 300), *font, "No", Color::Red);

    Text confirmMsg;
    confirmMsg.setFont(*font);
    confirmMsg.setCharacterSize(24);
    confirmMsg.setFillColor(Color::White);
    confirmMsg.setString("¿Desea eliminar el segmento " + to_string(selectedSegment + 1) + "?");
    confirmMsg.setPosition(100, 200);

    bool decisionMade = false;
    bool confirmed = false;
    while (!decisionMade && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(50, 50, 50));
        window.draw(confirmMsg);
        yesButton.draw(window);
        noButton.draw(window);
        window.display();

        if (yesButton.ButtonIsClicked(window)) {
            confirmed = true;
            decisionMade = true;
        }
        else if (noButton.ButtonIsClicked(window)) {
            confirmed = false;
            decisionMade = true;
        }
    }
    if (confirmed) {
        configEvent.deleteSegment(selectedSegment);
        cout << "Segmento " << (selectedSegment + 1) << " eliminado correctamente." << endl;
        Text msg;
        msg.setFont(*font);
        msg.setCharacterSize(24);
        msg.setFillColor(Color::White);
        msg.setString("Segmento eliminado correctamente.");
        msg.setPosition(100, 100);
        window.clear(Color(50, 50, 50));
        window.draw(msg);
        window.display();
        sf::sleep(seconds(2));
        saveEventDataFree("event.txt", configEvent);
        loadEventData("event.txt", configEvent);
    }
    else {
        cout << "Operación cancelada." << endl;
        Text msg;
        msg.setFont(*font);
        msg.setCharacterSize(24);
        msg.setFillColor(Color::White);
        msg.setString("Operación cancelada.");
        msg.setPosition(100, 100);
        window.clear(Color(50, 50, 50));
        window.draw(msg);
        window.display();
        sf::sleep(seconds(2));
    }
}

void deleteDiscountCodeUI(RenderWindow& window, Font* font, ConfigEvent& configEvent) {
    
    List<string>& codes = configEvent.getDiscountCodes();
    int numCodes = codes.getSize();  

    if (numCodes <= 0) {
        cout << "No hay códigos de descuento para eliminar." << endl;
        Text msg;
        msg.setFont(*font);
        msg.setCharacterSize(24);
        msg.setFillColor(Color::White);
        msg.setString("No hay códigos de descuento disponibles.");
        msg.setPosition(100, 100);
        window.clear(Color(50, 50, 50));
        window.draw(msg);
        window.display();
        sleep(seconds(2));
        return;
    }

    Button** codeButtons = new Button * [numCodes];
    List<string>::Node* node = codes.getHead();
    for (int i = 0; i < numCodes; i++) {
        if (node) {
            codeButtons[i] = new Button(Vector2f(300, 50), Vector2f(100, 100 + i * 60), *font, node->data, Color::Blue);
            node = node->next;
        }
    }

    int selectedCodeIndex = -1;
    bool selecting = true;
    while (selecting && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(50, 50, 50));

        for (int i = 0; i < numCodes; i++) {
            codeButtons[i]->draw(window);
            if (codeButtons[i]->ButtonIsClicked(window)) {
                selectedCodeIndex = i;
                selecting = false;
            }
        }
        window.display();
    }
    for (int i = 0; i < numCodes; i++) {
        delete codeButtons[i];
    }
    delete[] codeButtons;

    if (selectedCodeIndex < 0 || selectedCodeIndex >= numCodes) {
        cout << "No se seleccionó ningún código." << endl;
        return;
    }
    string codeToDelete;
    int index = 0;
    node = codes.getHead();
    while (node != nullptr && index < selectedCodeIndex) {
        node = node->next;
        index++;
    }
    if (node != nullptr) {
        codeToDelete = node->data;
    }
    else {
        cout << "Error al recuperar el código seleccionado." << endl;
        return;
    }

    Button yesButton(Vector2f(150, 50), Vector2f(100, 400), *font, "Sí", Color::Green);
    Button noButton(Vector2f(150, 50), Vector2f(300, 400), *font, "No", Color::Red);

    Text confirmMsg;
    confirmMsg.setFont(*font);
    confirmMsg.setCharacterSize(24);
    confirmMsg.setFillColor(Color::White);
    confirmMsg.setString("¿Eliminar el código: " + codeToDelete + " ?");
    confirmMsg.setPosition(100, 350);

    bool decisionMade = false;
    bool confirmed = false;
    while (!decisionMade && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(50, 50, 50));
        window.draw(confirmMsg);
        yesButton.draw(window);
        noButton.draw(window);
        window.display();

        if (yesButton.ButtonIsClicked(window)) {
            confirmed = true;
            decisionMade = true;
        }
        else if (noButton.ButtonIsClicked(window)) {
            confirmed = false;
            decisionMade = true;
        }
    }

    if (confirmed) {

        configEvent.deleteCode(codeToDelete);
        cout << "Código de descuento \"" << codeToDelete << "\" eliminado." << endl;
        Text msg;
        msg.setFont(*font);
        msg.setCharacterSize(24);
        msg.setFillColor(Color::White);
        msg.setString("Código eliminado correctamente.");
        msg.setPosition(100, 100);
        window.clear(Color(50, 50, 50));
        window.draw(msg);
        window.display();
        sleep(seconds(2));
        saveEventDataFree("event.txt", configEvent);
        loadEventData("event.txt", configEvent);
    }
    else {
        cout << "Operación cancelada." << endl;
        Text msg;
        msg.setFont(*font);
        msg.setCharacterSize(24);
        msg.setFillColor(Color::White);
        msg.setString("Operación cancelada.");
        msg.setPosition(100, 100);
        window.clear(Color(50, 50, 50));
        window.draw(msg);
        window.display();
        sleep(seconds(2));
    }
}

void deleteClientFromFile(const string& filename, List<Client>& clientList, const string& identification) {
    ofstream file(filename, ofstream::out | ofstream::trunc);
    if (!file.is_open()) {
        cerr << "Error: no se pudo abrir " << filename << " para eliminar el cliente." << endl;
        return;
    }
    typename List<Client>::Node* node = clientList.getHead();
    while (node != nullptr) {
        if (node->data.getIdentification() != identification) 
        {
            file << node->data.getIdentification() << ","
                << node->data.getPersonName() << ","
                << node->data.getBirthdayDate() << "\n";
        }
        node = node->next;
    }
    file.close();
    cout << "Cliente eliminado correctamente de " << filename << endl;
}

void refundPurchaseUI(RenderWindow& window, Font* font, ConfigEvent& configEvent, List<Client>& clientList) {
    int numClients = clientList.getSize();
    if (numClients <= 0) {
        cout << "No hay clientes registrados." << endl;
        Text msg;
        msg.setFont(*font);
        msg.setCharacterSize(24);
        msg.setFillColor(Color::White);
        msg.setString("No hay clientes registrados.");
        msg.setPosition(100, 100);
        window.clear(Color(50, 50, 50));
        window.draw(msg);
        window.display();
        sleep(seconds(2));
        return;
    }

   
    Button** clientButtons = new Button * [numClients];
    List<Client>::Node* cnode = clientList.getHead();
    for (int i = 0; i < numClients; i++) {
        if (cnode != nullptr) {
            clientButtons[i] = new Button(Vector2f(300, 50), Vector2f(100, 100 + i * 60),
                *font, cnode->data.getPersonName(), Color::Blue);
            cnode = cnode->next;
        }
    }
    int selectedClient = -1;
    bool selecting = true;
    while (selecting && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(50, 50, 50));
        for (int i = 0; i < numClients; i++) {
            clientButtons[i]->draw(window);
            if (clientButtons[i]->ButtonIsClicked(window)) {
                selectedClient = i;
                selecting = false;
            }
        }
        window.display();
    }

    for (int i = 0; i < numClients; i++) {
        delete clientButtons[i];
    }
    delete[] clientButtons;

    if (selectedClient < 0 || selectedClient >= numClients) {
        cout << "No se selecciono ningun cliente." << endl;
        return;
    }
    Client targetClient = clientList.getAt(selectedClient);

    Button yesButton(Vector2f(150, 50), Vector2f(100, 400), *font, "Sí", Color::Green);
    Button noButton(Vector2f(150, 50), Vector2f(300, 400), *font, "No", Color::Red);

    Text confirmMsg;
    confirmMsg.setFont(*font);
    confirmMsg.setCharacterSize(24);
    confirmMsg.setFillColor(Color::White);
    confirmMsg.setString("¿Cancelar la compra para " + targetClient.getPersonName() + "?");
    confirmMsg.setPosition(100, 350);

    bool decisionMade = false;
    bool confirmed = false;
    while (!decisionMade && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(50, 50, 50));
        window.draw(confirmMsg);
        yesButton.draw(window);
        noButton.draw(window);
        window.display();

        if (yesButton.ButtonIsClicked(window)) {
            confirmed = true;
            decisionMade = true;
        }
        else if (noButton.ButtonIsClicked(window)) {
            confirmed = false;
            decisionMade = true;
        }
    }
    if (!confirmed) {
        cout << "Operación cancelada." << endl;
        Text msg;
        msg.setFont(*font);
        msg.setCharacterSize(24);
        msg.setFillColor(Color::White);
        msg.setString("Operación cancelada.");
        msg.setPosition(100, 100);
        window.clear(Color(50, 50, 50));
        window.draw(msg);
        window.display();
        sleep(seconds(2));
        return;
    }

 
    List<PurchasedSeat>& purchaseList = targetClient.getPurchasedSeats();
    List<PurchasedSeat>::Node* pnode = purchaseList.getHead();
    while (pnode != nullptr) {
        int segIndex = pnode->data.segmentIndex;
        Segment* seg = configEvent.getSegment(segIndex);
        if (seg != nullptr) {
            seg->resetSeats(pnode->data.seatCode);
        }
        pnode = pnode->next;
    }

    purchaseList.clear();

    deleteClientFromFile("clientes.txt", clientList, targetClient.getIdentification());


    std::cout << "Compra cancelada para el cliente: " << targetClient.getPersonName() << std::endl;
    Text msg;
    msg.setFont(*font);
    msg.setCharacterSize(24);
    msg.setFillColor(Color::White);
    msg.setString("Compra cancelada para " + targetClient.getPersonName());
    msg.setPosition(100, 100);
    window.clear(Color(50, 50, 50));
    window.draw(msg);
    window.display();
    sf::sleep(seconds(2));
}

void saveClientsToFile(const string& filename, List<Client>& clientList) {
    
    if (clientList.getSize() == 0) {
        cout << "La lista de clientes está vacía." << endl;
    }
    else {
        cout << "La lista de clientes tiene " << clientList.getSize() << " elementos." << endl;
    }

    ofstream file(filename, ofstream::out | ofstream::trunc);
    if (!file.is_open()) {
        cerr << "Error: no se pudo abrir " << filename << " para guardar los clientes." << endl;
        return;
    }

    typename List<Client>::Node* node = clientList.getHead();
    while (node != nullptr) {
      
        file << node->data.getIdentification() << ","
            << node->data.getPersonName() << ","
            << node->data.getBirthdayDate() << "\n";
        cout << "Guardando cliente: " << node->data.getPersonName() << endl;
        node = node->next;
    }

    file.close();
    cout << "Clientes guardados correctamente en " << filename << endl;
}

void loadClientsFromFile(const string& filename, List<Client>& clientList) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: no se pudo abrir " << filename << " para cargar los clientes." << endl;
        return;
    }

    clientList.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        istringstream iss(line);
        string identification, name, birthday;
        if (getline(iss, identification, ',') &&
            getline(iss, name, ',') &&
            getline(iss, birthday)) {
            Client client;
            client.setIdentification(identification);
            client.setPersonName(name);
            client.setBirthdayDate(birthday);
            clientList.insertAtTheEnd(client);
            cout << "Cliente cargado: " << name << endl;
        }
    }
    file.close();
    cout << "Clientes cargados correctamente desde " << filename << endl;
}

int main() {
    ConfigEvent configEvent;
    DateProcessorTool dateProcessor;
    Client client;
    List<Client> clientList;

    bool showSeatSelection = false;
    RectangleShape** seatGrid = nullptr;
    int rows = 0, cols = 0;

    RenderWindow window(VideoMode(1800, 900), "Menu Principal", Style::Close);
    window.setFramerateLimit(60);

    Color Gray(128, 128, 128); 

    Sprite* background = new Sprite();

    Texture* eventTexture = new Texture();
    if (!eventTexture->loadFromFile("Multimedia/FondoEvento.png")) {
        cout << "error fondo evento";
    }
    background->setTexture(*eventTexture);

    Font* font = new Font();
    if (!font->loadFromFile("Multimedia/TimesNewRoman.ttf")) {
        cout << "error font";
    }

    bool showSegmentButtons = false;
    bool showSeats = false;
    int selectedSegment = -1;
    int segmentCount = 0;
    Button** segmentButtons = new Button * [segmentCount];

    Button confirmButton(Vector2f(500, 300), Vector2f(1400, 800), *font, "Confirmar Compra", Color::Green);
    bool confirmVisible = false;

    Text* discountCodesText = new Text();
    discountCodesText->setFont(*font);
    discountCodesText->setCharacterSize(20);
    discountCodesText->setFillColor(Color::Green);
    discountCodesText->setPosition(100, 100);

    const int numButtons = 9;
    Button buttons[numButtons] = {
        Button(Vector2f(200, 50), Vector2f(40, 20), *font, "Configurar Evento", Color::Black),
        Button(Vector2f(200, 50), Vector2f(260, 20), *font, "Ver Codigos Descuento", Color::Black),
        Button(Vector2f(200, 50), Vector2f(480, 20), *font, "Comprar Entrada", Color::Black),
        Button(Vector2f(200, 50), Vector2f(700, 20), *font, "Disponibilidad", Color::Black),
        Button(Vector2f(200, 50), Vector2f(920, 20), *font, "Reembolsar Entrada", Color::Black),
        Button(Vector2f(200, 50), Vector2f(1140, 20), *font, "Cargar Evento", Color::Black),
        Button(Vector2f(200, 50), Vector2f(1360, 20), *font, "Editar Evento", Color::Black),
        Button(Vector2f(200, 50), Vector2f(1580, 20), *font, "Salir", Color::Black),
        Button(Vector2f(200, 50), Vector2f(80, 820), *font, "Acera de", Color::Black)
    };

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(); 

        window.draw(*background);
        
        for (int i = 0; i < numButtons; ++i) {
            if (buttons[i].ButtonIsClicked(window)) {
                buttons[i].setTextColor(Color::Red);
                buttons[i].setOutlineThickness(3);
                buttons[i].setOutlineColor(Color::White);

                switch (i) {
                case 0: {
                    configEvent.~configEvent();
                    ConfigEvent configEvent;
                    clearFile("reserved_seats.txt");
                    clearFile("event.txt");
                    clearFile("clientes.txt");
                    saveEventDataFree("event.txt", configEvent);
                    string eventName = getUserInputs(window, *font, "Ingrese el nombre del evento:");
                    string eventDate;
                    do {
                        eventDate = getUserInputs(window, *font, "Ingrese la fecha del evento (DD/MM/YYYY):");
                    } while (!dateProcessor.isDateValid(eventDate) || !dateProcessor.isFutureDateEvent(eventDate));

                    int numSegments = getNumericInputs(window, *font, "Ingrese el número de segmentos:", 1, 100);

                    configEvent.setNameEvent(eventName);
                    configEvent.setDateEvent(eventDate);
                   
                    segmentCount = numSegments;  
                    segmentButtons = new Button * [segmentCount];

                    for (int i = 0; i < segmentCount; i++) {
                        segmentButtons[i] = new Button(
                            Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
                            Vector2f(50, 100 + i * (BUTTON_HEIGHT + 10)),
                            *font,
                            "Segmento " + to_string(i + 1),
                            Color::Blue
                        );
                    }
                    int totalSeats = 0;
                    for (int s = 0; s < numSegments; ++s) {
                        int remainingSeats = maxTotalSeats - totalSeats;
                        float price;
                        do {
                            rows = getNumericInputsTwo(window, *font, "Segmento " + to_string(s + 1) + " - Ingrese filas (quedan " + to_string(remainingSeats) + " asientos):", 1, remainingSeats);
                            cols = getNumericInputs(window, *font, "Segmento " + to_string(s + 1) + " - Ingrese columnas:", 1, remainingSeats / rows);
                            price = getFloatInputs(window, *font, "Segmento " + to_string(s + 1) + " - Ingrese el precio por asiento:", 1.0);
                        } while ((totalSeats + (rows * cols)) > maxTotalSeats);

                        totalSeats += (rows * cols);
                        Segment* newSegment = new Segment();
                        newSegment->setNumberRows(rows);
                        newSegment->setNumberColumns(cols);
                        newSegment->setPrice(price);

                        configEvent.addSegment(newSegment);
                    }
                    int discountSeats = getNumericInputsTwo(window, *font, "Ingrese la cantidad de asientos con descuento:", 0, totalSeats);
                    int discountPercentage;
                    if (discountSeats != 0)
                    {
                        discountPercentage = getNumericInputsTwo(window, *font, "Ingrese el porcentaje de descuento:", 1, 100);
                    }
                    else{
                        discountPercentage = 0;
                    }
                    configEvent.setCodeDiscount(discountSeats);
                    configEvent.setDiscount(discountPercentage);
                    configEvent.generateDiscountCodes();
                    saveEventDataFree("event.txt", configEvent);
                    configEvent.setSegmentSpace(configEvent.getSizeSegmentsSpace() / 2);

                    loadEventData("event.txt", configEvent);
                    numSegments = configEvent.getSizeSegmentsSpace();
                    numSegments = numSegments / 2;
                    for (int i = 0; i < numSegments; i++) {
                        Segment* seg = configEvent.getSegment(i);
                        if (seg != nullptr) {
                            seg->updateData(*font);  
                        }
                    }
                    loadReservedSeats(configEvent);
                    loadEventData("event.txt", configEvent);
                    break;
                }
                case 1:
                {
                    if (!configEvent.isDiscountNumExist()) {
                        discountCodesText->setString("No hay códigos de descuento disponibles.");
                    }
                    else {
                        string codeDisplay = "Códigos disponibles:\n";
                        List<string>::Node* current = configEvent.getDiscountCodes().getHead();
                        int count = 0;  
                        while (current != nullptr) {
                            codeDisplay += current->data + "  ";
                            count++;
                            if (count == 5) {
                                codeDisplay += "\n"; 
                                count = 0;  
                            }
                            current = current->next;
                        }
                        discountCodesText->setString(codeDisplay);
                    }
                    break;
                }
                case 2: {
                    List<PurchasedSeat> purchasedSeats;
                    string identification, birthDate;
                    do {
                        identification = getUserInputs(window, *font, "Ingrese una cédula válida:");
                    } while (!client.validateID(identification) || !client.isValidClient(identification));

                    string userName = getUserInputs(window, *font, "Ingrese su nombre:");
                    do {
                        birthDate = getUserInputs(window, *font, "Ingrese fecha de nacimiento (Debe ser mayor de edad):");
                    } while (!dateProcessor.isDateValid(birthDate) || !dateProcessor.isAdult(birthDate));

                    client.setBirthdayDate(birthDate);
                    client.setPersonName(userName);
                    client.setIdentification(identification);

                    saveClientsToFile("clientes", clientList);

                    int seatsToBuy = getNumericInputs(window, *font, "Ingrese la cantidad de asientos a comprar:", 1, 5);
                    client.setSeatsToBuy(seatsToBuy);

                    int totalSelected = 0;
                    string reservedSeats = "";
                    while (totalSelected < client.getSeatsToBuy() && window.isOpen()) {
                       
                        segmentCount = configEvent.getSizeSegmentsSpace();
                        
                        segmentButtons = new Button * [segmentCount];
                        for (int i = 0; i < segmentCount; i++) {
                            segmentButtons[i] = new Button(
                                Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
                                Vector2f(50, 100 + i * (BUTTON_HEIGHT + 10)),
                                *font,
                                "Segmento " + to_string(i + 1),
                                Color::Blue
                            );
                        }
                        bool showSegmentButtons = true;
                        int selectedSegment = -1;
                        while (showSegmentButtons && window.isOpen()) {
                            Event event;
                            while (window.pollEvent(event)) {
                                if (event.type == Event::Closed)
                                    window.close();
                            }
                            window.clear();
                            window.draw(*background);
                            for (int i = 0; i < segmentCount / 2; i++) {
                                segmentButtons[i]->draw(window);
                                if (segmentButtons[i]->ButtonIsClicked(window)) {
                                    selectedSegment = i;
                                    showSegmentButtons = false;
                                }
                            }
                            window.display();
                        }
                        for (int i = 0; i < segmentCount; i++) {
                            delete segmentButtons[i];
                        }
                        delete[] segmentButtons;
                        if (selectedSegment > -1) {
                            Segment* segment = configEvent.getSegment(selectedSegment);
                            segment->updateData(*font); 
                            Button changeSegmentButton(Vector2f(150, 50), Vector2f(1600, 20), *font, "Cambiar Segmento", Color::Cyan);
                            bool selectingSeats = true;
                            while (selectingSeats && window.isOpen() && totalSelected < client.getSeatsToBuy()) {
                                Event event;
                                while (window.pollEvent(event)) {
                                    if (event.type == Event::Closed)
                                        window.close();
                                }
                                if (changeSegmentButton.ButtonIsClicked(window)) {
                                    selectingSeats = false;
                                    break;
                                }

                              
                                string seatCode = segment->handleSeatClick(window);
                                if (!seatCode.empty()) {
                                    sf::Text discountQuestion;
                                    discountQuestion.setFont(*font);
                                    discountQuestion.setCharacterSize(24);
                                    discountQuestion.setFillColor(sf::Color::White);
                                    discountQuestion.setString("¿Tiene código de descuento para el asiento " + seatCode + "?");
                                    discountQuestion.setPosition(1100, 350);
                                    Button yesButton(Vector2f(100, 50), Vector2f(1100, 400), *font, "Sí", Color::Green);
                                    Button noButton(Vector2f(100, 50), Vector2f(1300, 400), *font, "No", Color::Red);
                                    bool answerGiven = false;
                                    bool useDiscount = false;
                                    while (!answerGiven && window.isOpen()) {
                                        Event event;
                                        while (window.pollEvent(event)) {
                                            if (event.type == Event::Closed)
                                                window.close();
                                        }
                                        if (yesButton.ButtonIsClicked(window)) {
                                            useDiscount = true;
                                            answerGiven = true;
                                        }
                                        else if (noButton.ButtonIsClicked(window)) {
                                            useDiscount = false;
                                            answerGiven = true;
                                        }
                                        window.clear();
                                        window.draw(*background);
                                        segment->drawSeats(window);
                                        window.draw(discountQuestion);
                                        yesButton.draw(window);
                                        noButton.draw(window);
                                        window.display();
                                    }
                                    if (useDiscount) {
                                        if (configEvent.isDiscountNumExist()) {
                                            string discountCodeForSeat = "";
                                            do {
                                                discountCodeForSeat = getUserInputs(window, *font, "Ingrese su código de descuento para el asiento " + seatCode + ":");
                                            } while (!configEvent.isCodeExist(discountCodeForSeat));
                                            configEvent.deleteCode(discountCodeForSeat);
                                            cout << "Código de descuento aplicado para el asiento " << seatCode
                                                << ": " << discountCodeForSeat << endl;
                                        }
                                        else {
                                            cout << "No hay códigos de descuento disponibles." << endl;
                                        }
                                        while (Mouse::isButtonPressed(Mouse::Left)) {
                                            sleep(milliseconds(50));
                                        }
                                    }
                                    float basePrice = segment->getPrice();
                                    bool discountApplied = useDiscount;
                                    float discountAmount = 0.0f;
                                    float finalPrice = basePrice;
                                    if (discountApplied) {
                                        discountAmount = basePrice * configEvent.getDiscount() / 100.0f;
                                        finalPrice = basePrice - discountAmount;
                                    }

                                    PurchasedSeat ps;
                                    ps.segmentIndex = selectedSegment;
                                    ps.seatCode = seatCode;
                                    ps.basePrice = basePrice;
                                    ps.discountApplied = discountApplied;
                                    ps.discountAmount = discountAmount;
                                    ps.finalPrice = finalPrice;
                                    purchasedSeats.insertAtTheEnd(ps);

                                    totalSelected++;
                                    reservedSeats += seatCode + " ";
                                    cout << "Asiento reservado en segmento " << (selectedSegment + 1)
                                        << ": " << seatCode << endl;
                                    saveReservedSeat(selectedSegment, seatCode);
                                }
                                window.clear();
                                window.draw(*background);
                                segment->drawSeats(window);      
                                changeSegmentButton.draw(window); 
                                window.display();
                            }
                           
                        }
                    }
                    bool confirmVisible = true;
                    Button confirmButton(Vector2f(500, 300), Vector2f(1400, 800), *font, "Confirmar Compra", Color::Green);
                    while (confirmVisible && window.isOpen()) {
                        Event event;
                        while (window.pollEvent(event)) {
                            if (event.type == Event::Closed)
                                window.close();
                        }
                        window.clear();
                        window.draw(*background);
                        confirmButton.draw(window);
                        if (confirmButton.ButtonIsClicked(window)) {
                            cout << "Compra confirmada! Asientos reservados: " << reservedSeats << endl;
                            confirmVisible = false;
                        }
                        window.display();
                    }
                    printInvoice(window, purchasedSeats, configEvent, client, font);
                    clientList.insertAtTheEnd(client);
                    saveClientsToFile("clientes.txt", clientList);
                    break;
                }
                case 3: {
                    int numSegments = configEvent.getSizeSegmentsSpace();
                    numSegments = numSegments / 2;
                    if (numSegments <= 0) {
                        std::cout << "No hay un evento configurado. Primero crea o carga un evento." << std::endl;
                        break;
                    }
                    for (int i = 0; i < numSegments; i++) {
                        
                        Segment* seg = configEvent.getSegment(i);
                        if (seg != nullptr) {
                            seg->updateData(*font);
                        }
                    }
                    int currentSegment = 0;
                    Button leftArrow(Vector2f(50, 50), Vector2f(50, 400), *font, "<", Color::Blue);
                    Button rightArrow(Vector2f(50, 50), Vector2f(1700, 400), *font, ">", Color::Blue);
                    Button backButton(Vector2f(200, 50), Vector2f(1600, 800), *font, "Volver", Color::Black);

                    bool viewing = true;
                    while (viewing && window.isOpen()) {
                        Event event;
                        while (window.pollEvent(event)) {
                            if (event.type == Event::Closed)
                                window.close();
                            if (event.type == Event::KeyPressed)
                                viewing = false;
                        }
                        if (leftArrow.ButtonIsClicked(window)) {
                            if (currentSegment > 0)
                                currentSegment--;
                            while (Mouse::isButtonPressed(Mouse::Left)) {
                                sleep(milliseconds(50));
                            }
                        }
                        if (rightArrow.ButtonIsClicked(window)) {
                            if (currentSegment < numSegments - 1)
                                currentSegment++;
                            while (Mouse::isButtonPressed(Mouse::Left)) {
                                sleep(milliseconds(50));
                            }
                        }
                        if (backButton.ButtonIsClicked(window)) {
                            viewing = false;
                            break;
                        }

                        window.clear(Color(50, 50, 50));
                        Segment* seg = configEvent.getSegment(currentSegment);
                        if (seg != nullptr) {
                            seg->drawSeats(window);
                        }
                        leftArrow.draw(window);
                        rightArrow.draw(window);
                        backButton.draw(window);
                        Text segInfo;
                        segInfo.setFont(*font);
                        segInfo.setCharacterSize(24);
                        segInfo.setFillColor(Color::White);
                        segInfo.setString("Segmento " + to_string(currentSegment + 1) + " de " + to_string(numSegments));
                        segInfo.setPosition(900, 50);
                        window.draw(segInfo);
                        window.display();
                    }
                    break;
                }
                case 4:
                    refundPurchaseUI(window, font, configEvent, clientList);
                    break;
                case 5: {
                    loadClientsFromFile("clientes.txt", clientList);
                    loadEventData("event.txt", configEvent);
                    int numSegments = configEvent.getSizeSegmentsSpace();
                    numSegments = numSegments / 2;
                    for (int i = 0; i < numSegments; i++) {
                        Segment* seg = configEvent.getSegment(i);
                        if (seg != nullptr) {
                            seg->updateData(*font);  
                        }
                    }
                    loadReservedSeats(configEvent);
                    cout << "Evento cargado exitosamente." << endl;
                    Text message;
                    message.setFont(*font);
                    message.setCharacterSize(24);
                    message.setFillColor(Color::White);
                    message.setString("Evento cargado correctamente.");
                    message.setPosition(200, 400);
                    Clock clock;
                    while (window.isOpen() && clock.getElapsedTime().asSeconds() < 2.0f) {
                        Event event;
                        while (window.pollEvent(event)) {
                            if (event.type == Event::Closed)
                                window.close();
                        }
                        window.clear();
                        window.draw(*background);
                        window.draw(message);
                        window.display();
                    }
                    break;
                }
                case 6: {
                    Button editSegmentButton(Vector2f(300, 50), Vector2f(400, 200), *font, "Editar Segmento", Color::Blue);
                    Button deleteSegmentButton(Vector2f(300, 50), Vector2f(400, 300), *font, "Eliminar Segmento", Color::Blue);
                    Button deleteDiscountButton(Vector2f(300, 50), Vector2f(400, 400), *font, "Eliminar Código de Descuento", Color::Blue);
                    Button backButton(Vector2f(200, 50), Vector2f(400, 500), *font, "Volver", Color::Red);

                    bool editing = true;
                    while (editing && window.isOpen()) {
                        sf::Event event;
                        while (window.pollEvent(event)) {
                            if (event.type == sf::Event::Closed)
                                window.close();
                        }

                        window.clear(sf::Color(50, 50, 50));
                        editSegmentButton.draw(window);
                        deleteSegmentButton.draw(window);
                        deleteDiscountButton.draw(window);
                        backButton.draw(window);
                        window.display();

                        if (editSegmentButton.ButtonIsClicked(window)) {
                           
                            editSegmentUI(window, font, configEvent);
                        }
                        else if (deleteSegmentButton.ButtonIsClicked(window)) {
                            
                            deleteSegmentUI(window, font, configEvent);
                           
                        }
                        else if (deleteDiscountButton.ButtonIsClicked(window)) {
                            deleteDiscountCodeUI(window, font, configEvent);
                        }
                        else if (backButton.ButtonIsClicked(window)) {
                            editing = false;
                        }
                        sleep(milliseconds(100));
                    }
                    break;
                }
                case 7:
                    saveClientsToFile("clientes.txt", clientList);
                    window.close();
                    break;
                case 8:
                    Text msgSegmento;
                    msgSegmento.setFont(*font);
                    msgSegmento.setCharacterSize(24);
                    msgSegmento.setFillColor(Color::White);
                    msgSegmento.setString("ACERCA DE");
                    msgSegmento.setPosition(840, 30);

                    Texture texture;
                    if (!texture.loadFromFile("Multimedia/acercade.png")) {
                        cerr << "No se pudo cargar la imagen.\n";
                        break;
                    }
                    Sprite sprite;
                    sprite.setTexture(texture);
                    sprite.setPosition(500, 70);  

                    Button backButton(Vector2f(200, 50), Vector2f(1480, 780), *font, "Volver", Color::Red);
                    bool editing = true;
                    while (editing && window.isOpen()) {
                        Event event;
                        while (window.pollEvent(event)) {
                            if (event.type == Event::Closed)
                                window.close();
                            if (event.type == Event::MouseButtonPressed)
                            {
                                if (backButton.ButtonIsClicked(window))
                                {
                                    editing = false; 
                                }
                            }
                        }
                        window.clear(Color(50, 50, 50));
                        window.draw(sprite);      
                        window.draw(msgSegmento); 
                        backButton.draw(window);  
                        window.display();
                    }
                    break;
                }
            }
            else if (buttons[i].isMouseOver(window)) {
                buttons[i].setTextColor(Color::Red);
            }
            else {
                buttons[i].setTextColor(Color::White);
                buttons[i].setOutlineThickness(0);
            }
        }
        if (showSeats && selectedSegment != -1) {
            Segment* segment = configEvent.getSegment(selectedSegment);
            if (segment != nullptr) {
                segment->drawSeats(window);
            }
        }
        if (showSeats && selectedSegment != -1) {
        for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            window.draw(seatGrid[r][c]);
        }
    }
}
        if (confirmVisible) {
            confirmButton.draw(window);
            if (confirmButton.ButtonIsClicked(window)) {
                cout << "Compra confirmada!" << endl;
            }
        }
        for (int i = 0; i < numButtons; ++i) {
            buttons[i].draw(window); 
        }
        
        if (configEvent.isDiscountNumExist()) {
            window.draw(*discountCodesText);
        }

        window.display();
    }
    delete font;
    delete background;
    delete eventTexture;
    
    return 0;
}

