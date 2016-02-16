// Main class, here is where the main method is and where the game starts.

#include <iostream>
#include "GameLogic.h"
#include <Windows.h>
#include <time.h>

using namespace std;

int main(){
	
	/*bool sigale = true;
	clock_t time = clock();
	char message = ' ';
	int counter = 0;
	while (sigale){	
		char old_message = message;
			if (GetAsyncKeyState(VK_UP)){
				message = 'u';
				if (message == old_message || counter <= 5){
					counter++;
				}
				else {
					cout << 'u' << endl;
					counter = 0;
				}
				
				
			}
			else if (GetAsyncKeyState(0X4B)){
				message = 'k';
				if (message == old_message || counter <= 5){
					counter++;
				}
				else {
					cout << message << endl;
					counter = 0;
				}
				
			}
			else if (GetAsyncKeyState(0X5A)){
				message = 'z';
				if (message == old_message || counter <= 5){
					counter++;
				}
				else {
					cout << message << endl;
					counter = 0;
				}
				
				sigale = false;
			}
			

		
	}
	system("pause");*/
	Gamelogic logic;
	logic.Start();

	return 0;
}