/***********************************************************************
 * Header File:
 *    main file
 * Author:
 *    Chris Mijangos and Seth Chen
 * Summary:
 *    Everything we need to know about main
 ************************************************************************/

#include "simulator.h"  // The orbit simulator

#include "test.h" // for tests

const double DEFAULT_ZOOM = 128000.0 /* 128km equals 1 pixel */;

const double SCREEN_SIZE = 1000.0; // The size of the window (currenly square)
const double SCREEN_SIZE_X = SCREEN_SIZE; // The horizonal length of the window
const double SCREEN_SIZE_Y = SCREEN_SIZE; // The vertical length of the window

using namespace std;

void callBack(const Interface* pUI, void* p)
{
    Simulator* pSim = (Simulator*)p;
    pSim->getInput(pUI);
    pSim->update();
    pSim->display();
}

#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR pCmdLine,
    _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{

    testRunner();


    // Initialize OpenGL
    Position ptUpperRight;
    ptUpperRight.setZoom(DEFAULT_ZOOM);
    ptUpperRight.setPixelsX(SCREEN_SIZE_X);
    ptUpperRight.setPixelsY(SCREEN_SIZE_Y);
    Interface ui(0, NULL,
        "Orbit Lab",
        ptUpperRight);

    // Initialize the Simulator
    Simulator sim = Simulator();

    // set everything into action
    ui.run(callBack, &sim);

    return 0;
}