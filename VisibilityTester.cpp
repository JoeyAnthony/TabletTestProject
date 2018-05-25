#include "stdafx.h"
#include "VisibilityTester.h"

using namespace vrlib::tien;

bool VisibilityTester::isVisible(float & onScreenValue)
{
	//max amount of pixels vs zero
	return false;
}

void VisibilityTester::drawForwardPass()
{
	//check if query result is available
	if (query.resultsAvailable())


	query.beginQuery();
	//render quad
	query.endQuery();
}

/*
* Treshhold is a value between 1 and 0 where 1 means that all pixels have to be on screen
*/
VisibilityTester::VisibilityTester(float treshold) : treshold(treshold)
{
	//build a quad

	
}


VisibilityTester::~VisibilityTester()
{
	//delete query and mesh
}
