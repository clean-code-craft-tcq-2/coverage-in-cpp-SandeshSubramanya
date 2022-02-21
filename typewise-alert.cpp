#include "typewise-alert.h"
#include <stdio.h>
#include <vector>
using namespace std;

// creator a vector of stCoolingTypeInfo.
std::vector<stCoolingTypeInfo> oVectorCoolingTypeInfo {
    stCoolingTypeInfo(CoolingType::PASSIVE_COOLING,0,35),
    stCoolingTypeInfo(CoolingType::HI_ACTIVE_COOLING,0,45),
    stCoolingTypeInfo(CoolingType::MED_ACTIVE_COOLING,0,40),
};

// returns the given cooling type information.
stCoolingTypeInfo getCurrentCoolingTypeInfo(CoolingType coolingType)
{
  std::vector<stCoolingTypeInfo>::iterator itrCoolingType = oVectorCoolingTypeInfo.begin();
  for(;itrCoolingType!= oVectorCoolingTypeInfo.end(); ++ itrCoolingType)
  {
      if(itrCoolingType->m_coolingType == coolingType)
            break;
  }
  return *itrCoolingType;
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  switch(coolingType) {
    case PASSIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 35;
      break;
    case HI_ACTIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 45;
      break;
    case MED_ACTIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 40;
      break;
  }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
