#include "Injector.h"
#include <windows.h>

int main() {
	std::cout << R"(
                                                                
 ,---.                   ,-----.,--.,--.                 ,--.   
'   .-',--. ,--.,--,--, '  .--./|  |`--' ,---. ,--,--, ,-'  '-. 
`.  `-. \  '  / |      \|  |    |  |,--.| .-. :|      \'-.  .-' 
.-'    | \   '  |  ||  |'  '--'\|  ||  |\   --.|  ||  |  |  |   
`-----'.-'  /   `--''--' `-----'`--'`--' `----'`--''--'  `--'   
       `---'                                                    

                        Hit Enter to proceed
)" << std::endl;
    
    if (std::cin.get()) {
        Injector::performinjection();
        std::cout << "Injected! You may close this window.";
        std::cin.get();
    }
}