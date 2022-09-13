/********************************************************************************
****
**		MQ2ConstantAffinity.cpp by gimp
****	
********************************************************************************/

#include <math.h>
#include <mq/Plugin.h>

PreSetup("MQ2ConstantAffinity");
PLUGIN_VERSION(1.0);

HANDLE		myProcessHandle = 0;
int	        myCores			= 1;

void init()
{
	SYSTEM_INFO SystemInfo;
	const uint64_t tick = GetTickCount64();
	myProcessHandle = GetCurrentProcess();
	GetSystemInfo(&SystemInfo);
	myCores = SystemInfo.dwNumberOfProcessors;

	int m = int(pow(2, myCores) - 1);
	DebugSpewAlways("Setting processor affinity to %d (%d logical cores)", m, myCores);
	SetProcessAffinityMask(myProcessHandle, m);
}

// Called once, when the plugin is to initialize
PLUGIN_API VOID InitializePlugin()
{
    DebugSpewAlways("Initializing setConstantAffinity");
	init();
}

// Called once, when the plugin is to shutdown
PLUGIN_API VOID ShutdownPlugin()
{
    DebugSpewAlways("Shutting down setConstantAffinity");
}
