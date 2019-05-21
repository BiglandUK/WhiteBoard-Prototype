#include "App.h"

int main(int argc, char* argv[]) {
	// Program entry point
	{
		App app; // Creating our app object

		while (!app.GetWindow()->IsDone()) {
			// Game loop
			app.Update();
			app.Render();
			app.LateUpdate();
		}
	}
	system("PAUSE");
}