#include "SmartHomeSystem.h"
#include "Light.h"
#include "Devices.h"
#include <fstream>

SmartHomeSystem::SmartHomeSystem() {}

#pragma region load devices
void SmartHomeSystem::loadDevices(const std::string& filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string deviceType, deviceName;
    while (file >> deviceType >> deviceName) {
      addDevice(deviceType, deviceName);
    }
    file.close();
  }
}
#pragma endregion

#pragma region save devices
// Save devices to a file
void SmartHomeSystem::saveDevices(const std::string& filename) {
  std::ofstream file(filename);
  if (file.is_open()) {
    for (const auto& device : devices) {
      file << device->getType() << " " << device->getName() << std::endl;
    }
    file.close();
  }
}
#pragma endregion

#pragma region list devices
void SmartHomeSystem::listDevices() const // WORKING ON THIS RN
{
  for (const auto& device : devices) {
    device->quickView(); // quickView for quick summary, display() is for detailed summary
  }
}
#pragma endregion

#pragma region sorting devices
// Sort devices by name
void SmartHomeSystem::sortByName() {
  std::sort(devices.begin(), devices.end(), [](const std::unique_ptr<Devices>& a, const std::unique_ptr<Devices>& b) {
    return a->getName() < b->getName();
    });
}

// Sort devices by device type and then by name
void SmartHomeSystem::sortByDeviceType() {
  std::sort(devices.begin(), devices.end(), [](const std::unique_ptr<Devices>& a, const std::unique_ptr<Devices>& b) {
    if (a->getType() == b->getType()) {
      return a->getName() < b->getName();
    }
    return a->getType() < b->getType();
    });
}
#pragma endregion

#pragma region add device
void SmartHomeSystem::addDevice() {
  int deviceTypeChoice;
  std::string deviceName;

  std::string addMenu = R"(
        Enter a Device Type
        ------------------------
        Please select a device:
        1. Light
        2. Socket
        3. Speaker
        4. Thermostat
        5. Temperature & Humidity Sensor
        6. Radiator Valve

        9. Main Menu )";
  std::cout << addMenu << std::endl;
  std::cin >> deviceTypeChoice;

  if (std::cin.fail() || deviceTypeChoice < 1 || deviceTypeChoice > 6) {
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cout << "Invalid choice. Device not added.\n";
    return;
  }

  // Step 2: Prompt for the device name
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
  std::cout << "Enter the name of the device: ";
  std::getline(std::cin, deviceName);

  switch (deviceTypeChoice) {
  case 1: // Light
    devices.push_back(std::make_unique<Light>(deviceName));
    std::cout << "Added Light: " << deviceName << "\n";
    break;
  case 2: // Socket
    // not done
    devices.push_back(std::make_unique<Socket>(deviceName));
    std::cout << "Added Socket: " << deviceName << "\n";
    break;
  case 3: // Speaker
    // not done
    devices.push_back(std::make_unique<Speaker>(deviceName));
    std::cout << "Added Speaker: " << deviceName << "\n";
    break;
  case 4: // Thermostat
    //not done
    break;
  case 5: // temperature & humidity sensor
    // not done
    break;
  case 6: // Radiator Valve
    // not done
    break;
  default:
    std::cout << "Invalid choice. Device not added.\n";
    break;
  }
}
#pragma endregion

#pragma region interact devices
// Interact with a specific device
void SmartHomeSystem::interactWithDevice(const std::string& deviceName) {
  auto it = std::find_if(devices.begin(), devices.end(), [&deviceName](const std::unique_ptr<Devices>& device) {
    return device->getName() == deviceName;
    });
  if (it != devices.end()) {
    // not done yet
  }
}
#pragma endregion

#pragma region main menu
// Display the main menu using a verbatim string, learnt this in Year One C# for readability
void SmartHomeSystem::displayMenu() const {
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
}

// Run the Smart Home System
void SmartHomeSystem::run() {
  loadDevices("devices.txt"); // this needs to be changed to a list of current devices 

  int selection;
  do {
    displayMenu();
    std::cin >> selection;

    if (std::cin.fail()) {
      std::cin.clear(); // clearin
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
      std::cout << "Invalid input. Enter a number from the menu." << std::endl;
      continue;
    }

    switch (selection) {
    case 1: // List all devices
      listDevices();
      break;
    case 2: // Sort devices by name
      sortByName();
      break;
    case 3: // Sort devices by type
      sortByDeviceType();
      break;
    case 4: { // Interact with a specific device
      std::string deviceName;
      std::cout << "Enter the device name to interact with: ";
      std::cin.ignore();
      std::getline(std::cin, deviceName);
      interactWithDevice(deviceName);
      break;
    }
    case 5: 
      addDevice(); 
      break;
    case 9: // Quit and save devices
      saveDevices("devices.txt");
      std::cout << "Devices saved. Exiting...\n";
      break;
    default:
      std::cout << "Invalid option. Try again." << std::endl;
    }
  } while (selection != 9);
}
#pragma endregion