#include <iostream>

#include <hidapi/hidapi.h>

#include "Keyboards/RedSquareKeyroxTKL/detectKeyroxTKL.hpp"

int main()
{
  hid_init();
  hid_device* keyboardDevice{};
  try
  {
    keyboardDevice = detectKeyboard();
  }
  catch (const std::exception& e)
  {
    std::cerr << "Can't open device: " << e.what();
    hid_exit();
    return 1;
  }
  hid_exit();
}