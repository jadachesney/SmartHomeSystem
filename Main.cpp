#include <iostream>
#include <vector>
#include <functional>
#include <limits>

// Assuming these functions are defined elsewhere
void listDevices(const std::vector<std::string>& devices);
void nameSort(std::vector<std::string>& devices);
void deviceSort(std::vector<std::string>& devices);
void addDevice(std::vector<std::string>& devices);
void interactWithDevice(const std::string& deviceName);

int main()
{
  std::vector<std::string> devices; // Assuming devices is a vector of strings

  std::vector<std::function<void()>> menuActions = {
    [&]() { listDevices(devices); },
    [&]() { nameSort(devices); },
    [&]() { deviceSort(devices); },
    [&]() {
      std::string deviceName;
      std::cout << "Enter device name: ";
      std::cin >> deviceName;
      interactWithDevice(deviceName);
    },
    [&]() { addDevice(devices); }
  };

  int selection;
  do
  {
    // Using verbatim string for better readability. I used this in my Year One C# main menu project.
    std::string menuMsg = R"( 
     Smart Home Device Menu
    ------------------------
    Please select an option:
    1. List devices
    2. Sort by name
    3. Sort by device type
    4. Select device to interact with its full feature set
    5. Add device

    9. Quit )";

    std::cout << menuMsg << std::endl;
    std::cin >> selection;

    if (std::cin.fail()) {
      std::cin.clear(); // clear the error flag
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discarding invalid input
      std::cout << "Invalid input. Enter a number from the menu." << std::endl;
      continue;
    }

    if (selection >= 1 && selection <= 5) {
      menuActions[selection - 1]();
    }
    else if (selection != 9) {
      std::cout << "Invalid option. Try again" << std::endl;
    }
  } while (selection != 9);

  return 0;
}