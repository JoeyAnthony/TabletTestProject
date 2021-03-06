// TabletTestProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TabletStart.h"
#include <cstdlib>
#include <VrLib/Kernel.h>
#include <VrLib\ServerConnection.h>

int main(int argc, char* argv[])
{
	vrlib::Kernel* kernel = vrlib::Kernel::getInstance();
	TabletStart* application = new TabletStart();

	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "--config") == 0)
		{
			i++;
			kernel->loadConfig(argv[i]);
		}
	}

	kernel->setApp(application);
	kernel->start();
	return 0;
}




extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}