#include "Archive.h"

/*void Archive::generateReport()
{
	string direccion = "C:/Users/eduar/Downloads/Original Proyect/PROYECTO1_agranados_jabarca/PROYECTO1_agranados_jabarca/InformaEvento.txt";
	ofstream outFile(direccion);
	if (outFile.is_open())
	{
		int totalAvailableSeats = 0;
		int totalSoldSeats = 0;
		float totalRevenue = 0.0f;

		outFile << "Reporte del Evento: " << configEvent.getNameEvent() << endl;
		outFile << "----------------------------------------" << endl;

		typename List<Segment>::Node* current = segments.getHead();
		while (current != nullptr) 
		{
			Segment& segment = current->data;
			int availableSeats = 0;
			int soldSeats = 0;

			for (int i = 0; i < segment.getNumberSeatingRows(); ++i) {
				for (int j = 0; j < segment.getNumberSeatingColumns(); ++j) 
				{
					string seatCode = segment.getSeatOfSegment()[i][j];
					if (segment.isSeatReserved(seatCode)) 
					{
						soldSeats++;
					}
					else {
						availableSeats++;
					}
				}
			}
			totalAvailableSeats += availableSeats;
			totalSoldSeats += soldSeats;
			totalRevenue += soldSeats * segment.getPrice();

			outFile << "Segmento: " << endl;
			outFile << "Asientos disponibles: " << availableSeats << endl;
			outFile << "Asientos vendidos: " << soldSeats << endl;
			outFile << "----------------------------------------" << endl;

			current = current->next;
		}
		outFile << "Total de asientos disponibles: " << totalAvailableSeats << endl;
		outFile << "Total de asientos vendidos: " << totalSoldSeats << endl;
		outFile << "Ganancias generadas: $" << totalRevenue << endl;
	}
	outFile.close();
}*/

void Archive::loadFromFile() {
    string direccion = "C:/Users/eduar/Downloads/Original Proyect/PROYECTO1_agranados_jabarca/PROYECTO1_agranados_jabarca/InformeEvento.txt";
    ifstream reportEvent(direccion);
    if (reportEvent.is_open())
    {
        string line;

        // Leer y establecer el nombre del evento
        if (getline(reportEvent, line)) {
            configEvent.setNameEvent(line);
            cout << "Nombre del evento: " << line << endl; // Mensaje de depuración
        }
        else {
            cerr << "Error al leer el nombre del evento" << endl;
            return;
        }

        // Leer y establecer la fecha del evento
        if (getline(reportEvent, line)) {
            configEvent.setDateEvent(line);
            cout << "Fecha del evento: " << line << endl; // Mensaje de depuración
        }
        else {
            cerr << "Error al leer la fecha del evento" << endl;
            return;
        }

        // Leer y establecer el espacio de segmentos
        if (getline(reportEvent, line)) {
            int segmentSpace = stoi(line);
            configEvent.setSegmentSpace(segmentSpace);
            cout << "Espacio de segmentos: " << segmentSpace << endl; // Mensaje de depuración
        }
        else {
            cerr << "Error al leer el espacio de segmentos" << endl;
            return;
        }

        // Leer y establecer el código de descuento
        if (getline(reportEvent, line)) {
            int discountCode = stoi(line);
            configEvent.setCodeDiscount(discountCode);
            cout << "Código de descuento: " << discountCode << endl; // Mensaje de depuración
        }
        else {
            cerr << "Error al leer el código de descuento" << endl;
            return;
        }

        // Leer y establecer el porcentaje de descuento
        if (getline(reportEvent, line)) {
            int percentajeCode = stoi(line);
            configEvent.setDiscount(percentajeCode);
            cout << "Porcentaje de descuento: " << percentajeCode << endl; // Mensaje de depuración
        }
        else {
            cerr << "Error al leer el porcentaje de descuento" << endl;
            return;
        }

        // Leer y actualizar los segmentos
        for (int i = 0; i < configEvent.getSizeSegmentsSpace(); i++)
        {
            if (getline(reportEvent, line))
            {
                int rowsEvent = stoi(line);
                cout << "Filas del segmento " << i + 1 << ": " << rowsEvent << endl; // Mensaje de depuración
                if (getline(reportEvent, line))
                {
                    int columnsEvent = stoi(line);
                    cout << "Columnas del segmento " << i + 1 << ": " << columnsEvent << endl; // Mensaje de depuración
                    if (getline(reportEvent, line))
                    {
                        float priceEvent = stof(line);
                        cout << "Precio del segmento " << i + 1 << ": " << priceEvent << endl; // Mensaje de depuración
                        segment.updateData(rowsEvent, columnsEvent, priceEvent);
                        configEvent.addSegment(segment);
                    }
                }
            }
        }
    }
    else {
        cerr << "Error al abrir el archivo" << endl;
    }
    reportEvent.close();
}
/*stringstream iss(line);
		int numberSeatingRows, numberSeatingColumns;
		float price;

		if (!(iss >> numberSeatingRows >> numberSeatingColumns >> price)) {
			cerr << "Error al leer los datos del segmento" << endl;
			continue;
		}
		Segment segment;
		segment.updateData(numberSeatingRows, numberSeatingColumns, price);
		segments.insertAtTheEnd(segment);*/