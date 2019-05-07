#include <Windows.h>
#include <crtdbg.h>

#include "src\TestUI.h"
#include "src\PaintTool.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

#ifdef _DEBUG
	//_CrtSetBreakAlloc(232);
	_onexit(_CrtDumpMemoryLeaks);
#endif

	//paint_tool::TestUI *app = new paint_tool::TestUI(hInstance);

	paint_tool::PaintTool *app = new paint_tool::PaintTool(hInstance);

	delete app;

	return 0;
}
