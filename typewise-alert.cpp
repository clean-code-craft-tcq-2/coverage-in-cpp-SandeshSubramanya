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

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{   
    stCoolingTypeInfo =  getCurrentCoolingTypeInfo(coolingType);
    return inferBreach(temperatureInC, stCoolingTypeInfo.m_lowerLimit, stCoolingTypeInfo.m_upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

    switch(alertTarget) 
    {
        case TO_CONTROLLER:
        sendToController(breachType);
        break;
        case TO_EMAIL:
        sendToEmail(breachType);
        break;
    }
}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void vDisplayBreachTypeForEmail(BreachType oBreachType)
{
    const char* recepient = "a.b@c.com";
    if(oBreachType == BreachType::TOO_LOW)
    {    
        printf("To: %s\n", recepient);
        printf("Hi, the temperature is too low\n");
    }
    else
    {
       printf("To: %s\n", recepient);
       printf("Hi, the temperature is too high\n");
    }
}
void sendToEmail(BreachType oBreachType) 
{
   if (oBreachType != BreachType::NORMAL)
       vDisplayBreachTypeForEmail(oBreachType);
}
