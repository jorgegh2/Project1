#include "Application.h"
#include "Globals.h"
#include "MemLeaks.h"
#include<time.h>
#include "ModulePowerUp.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char* argv[])
{

	ReportMemoryLeaks();

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
			case MAIN_CREATION:
			{
				LOG("Application Creation --------------");
				App = new Application();
				state = MAIN_START;
			}	break;

			case MAIN_START:
			{
				LOG("Application Init --------------");
				if(App->Init() == false)
				{
					LOG("Application Init exits with error -----");
					state = MAIN_EXIT;
				}
				else
				{
					state = MAIN_UPDATE;
					LOG("Application Update --------------");
				}

			}	break;

			case MAIN_UPDATE:
			{
				int update_return = App->Update();

				if (App->power_up->IsEnabled() == true && App->power_up->State == App->power_up->Power_Up_State::None) {
					srand(time(NULL));

					App->power_up->random_init = rand() % 4 + 1;
				}

				if (update_return == UPDATE_ERROR)
				{
					LOG("Application Update exits with error -----");
					state = MAIN_EXIT;
				} else if (update_return == UPDATE_STOP)
					state = MAIN_FINISH;
			}
				break;

			case MAIN_FINISH:
			{
				LOG("Application CleanUp --------------");
				if(App->CleanUp() == false)
				{
					LOG("Application CleanUp exits with error -----");
				}
				else
					main_return = EXIT_SUCCESS;

				state = MAIN_EXIT;

			} break;

		}
	}

	delete App;
	LOG("Bye :)\n");
	return main_return;
}