// Main class, here is where the main method is and where the game starts.

#include <iostream>
#include "GameLogic.h"
#include <Windows.h>
#include <time.h>

using namespace std;

int main(){
	
	bool sigale = true;
	char message = ' ';
	clock_t time = clock();

	
	while (sigale){	
		//TODO: Left here, figure out how to sanitize the inputs
		if (((clock() - time) / CLOCKS_PER_SEC) > 1){
			char old_message = message;
			if (GetAsyncKeyState(VK_UP)){
				message = 'u';
			}
			else if (GetAsyncKeyState(0X4B)){
				message = 'k';
			}
			else if (GetAsyncKeyState(0X5A)){
				message = 'z';
				sigale = false;
			}
			cout << message << endl;

			time = clock();
		}
		
	}
	system("pause");
	
	//Gamelogic logic;
	//logic.Start();

	return 0;
}