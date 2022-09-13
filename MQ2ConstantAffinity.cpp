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
DWORD		myProcessID		= 0;
int	        myCores			= 1;

void init()
{
	SYSTEM_INFO SystemInfo;
	const uint64_t tick = GetTickCount64();
	myProcessHandle = GetCurrentProcess();
	myProcessID = GetCurrentProcessId();
	GetSystemInfo(&SystemInfo);
	myCores = SystemInfo.dwNumberOfProcessors;
	WriteChatf("MQ2ConstantAffinity detected %d logical cores", myCores);
}

void setConstantAffinity()
{
	int m = int(pow(2, myCores) - 1);
	WriteChatf("Setting processor affinity to %d", m);
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

// Called after entering a new zone
PLUGIN_API VOID OnZoned()
{
    DebugSpewAlways("MQ2ConstantAffinity::OnZoned()");
	setConstantAffinity();
}


// Called once directly after initialization, and then every time the gamestate changes
PLUGIN_API VOID SetGameState(DWORD GameState)
{
    DebugSpewAlways("MQ2ConstantAffinity::SetGameState()");
    if (GameState==GAMESTATE_INGAME)
	{
		setConstantAffinity();
	}
}

// This is called every time MQ pulses
PLUGIN_API VOID OnPulse()
{
}
