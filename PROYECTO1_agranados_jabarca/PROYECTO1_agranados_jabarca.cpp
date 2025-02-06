#include <iostream>
#include "EventController.h"
#include "Archive.h"
#include "List.h"
#include "Segment.h"
#include "ReportViewer.h"

using namespace std;

int main()
{
	EventController eventControllerObject;
	eventControllerObject.controlPrincipalMenuFlow();
	return 0;
}