#include "SmartHomeSystem.h"
#include "Light.h"
#include <fstream>

SmartHomeSystem::SmartHomeSystem() {}

// Load devices from a file
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

// List all devices with detailed information
void SmartHomeSystem::listDevices() const {
  if (devices.empty()) {
    std::cout << "No devices found." << std::endl;
  }
  else {
    for (const auto& device : devices) {
      device->display(); // Calls the `display()` function of each derived class
    }
  }
}

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

// Add a new device
void SmartHomeSystem::addDevice(const std::string& deviceType, const std::string& deviceName) {
  if (deviceType == "Light") {
    devices.push_back(std::make_unique<Light>(deviceName));
  }
  // Add other device types here
}

// Interact with a specific device
void SmartHomeSystem::interactWithDevice(const std::string& deviceName) {
  auto it = std::find_if(devices.begin(), devices.end(), [&deviceName](const std::unique_ptr<Devices>& device) {
    return device->getName() == deviceName;
    });
  if (it != devices.end()) {
    // not done yet
  }
}

// Display the main menu
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
    case 1: // Listing the devices 
      listDevices();
      break;
    case 2:
      sortByName(); // Sorting the devices by alphabetical order for name
      break;
    case 3:
      sortByDeviceType(); // Sorting the devices by heating, lighting, etc (and then name as secondary)
      break;
    case 4: {
      std::string deviceName;
      std::cout << "Enter device name: ";
      std::cin >> deviceName;
      interactWithDevice(deviceName); 
      break;
    }
    case 5: {
      std::string deviceType, deviceName; // Adding a new device 
      std::cout << "Enter device type: ";
      std::cin >> deviceType;
      std::cout << "Enter device name: ";
      std::cin >> deviceName;
      addDevice(deviceType, deviceName);
      break;
    }
    case 9: // Quit and save the devices before leaving 
      saveDevices("devices.txt"); 
      break;
    default:
      std::cout << "Invalid option. Try again" << std::endl;
    }
  } while (selection != 9);
}