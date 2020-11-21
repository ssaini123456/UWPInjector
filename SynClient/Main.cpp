#include <iostream>
#include <Windows.h>
#include "Injector.h"
int main() {
	std::cout << "Hit enter to inject.";
	if (std::cin.get()) {
		Injector::performinjection();
		std::cout << "Injected! You may now close this window.";
	}
}