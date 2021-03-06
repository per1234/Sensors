/****************************/
/* Author:  MIECIELICA YANN */
/* Date:    07/09/2017 23:00*/
/* P-Name:  Sensors         */
/****************************/

#include "ThermometerDS18B20.h"
#include <OneWire.h>
#include <DallasTemperature.h>

ThermometerDS18B20::ThermometerDS18B20(uint8_t pin)
    :m_pin(pin)
{
  // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
  m_oneWire = new OneWire(pin);

  // Pass our oneWire reference to Dallas Temperature.
  m_sensors = new DallasTemperature(m_oneWire);

  m_currentTemperature = 0;

  // Start up the library
  m_sensors->begin();
}

ThermometerDS18B20::~ThermometerDS18B20()
{
  delete m_sensors;
  delete m_oneWire;
}

float ThermometerDS18B20::temperature()
{
  return temperature(0);
}

float ThermometerDS18B20::temperature(uint8_t device)
{
  DeviceAddress tempDeviceAddress;

  if (m_sensors->getAddress(tempDeviceAddress, device)) {
    m_sensors->requestTemperatures(); // Send the command to get temperatures
    m_currentTemperature = m_sensors->getTempCByIndex(device);
  }
  return m_currentTemperature;
}
