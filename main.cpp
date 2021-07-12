#include "MenuHelper.h"
#include "SystemInterface.h"

int main() {
  // Load From Disk.
  SystemInterface::getInstance().loadDataBeansFromDisk();

  // Start Menu Loop.
  MenuHelper menuHelper;
  menuHelper.menu_main();
}
