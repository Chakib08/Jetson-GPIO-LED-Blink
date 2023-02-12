#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

/*
 * Change this values according to the GPIO pin used in your hardware setup
 * PIN : Check in Jetson's PINMUX the used GPIO pin
 * GPIO : Run the following commands to get reference of the GPIO
 * sudo su
 * cat /sys/kernel/debug/gpio | grep <PIN>
 */
const int PIN = 305;
const std::string GPIO = "PAA.00";

std::string GPIO_EXPORT = "/sys/class/gpio/export";
std::string GPIO_DIRECTION = "/sys/class/gpio/%s/direction";
std::string GPIO_VALUE = "/sys/class/gpio/" + GPIO + "/value";

void exportGPIO(int pin)
{
  std::fstream fs;
  fs.open(GPIO_EXPORT, std::fstream::out);
  fs << pin;
  fs.close();
}

void setDirection(std::string gpio, std::string direction)
{
  std::fstream fs;
  fs.open(GPIO_DIRECTION.replace(GPIO_DIRECTION.find("%s"), 2, gpio));
  fs << direction;
  fs.close();
}

void setValue(int value)
{
  std::fstream fs;
  fs.open(GPIO_VALUE, std::fstream::out);
  fs << value;
  fs.close();
}

int main ()
{
  // Define default values
  int value = 1;
  std::string direction = "out";
  bool isBlinking = true;

  // Export GPIO
  exportGPIO(PIN);

  // Set direction to out
  setDirection(GPIO, direction);

  // Blinking 
  while(isBlinking)
  {
    setValue(value);
    usleep(500000); // wait for 500ms
    value ^= 1;
    if(value == 1)
    {
      std::cout << "ON" << std::endl;
    }
    else
    {
      std::cout << "OFF" << std::endl;
    }
  }

  return 0;
}