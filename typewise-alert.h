#pragma once
#include <vector>

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
  NUM_OF_COOLINGTYPE
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);


typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

// structure to store information on a particular cooling type
struct stCoolingTypeInfo  // st ->Structure
{
   CoolingType m_coolingType;
   int m_lowerLimit;
   int m_upperLimit;
   stCoolingTypeInfo(CoolingType oCoolingType, int lowerLimit,int upperLimit)
   : m_coolingType(oCoolingType)
   , m_lowerLimit(lowerLimit)
   , m_upperLimit(upperLimit)
   {
   } 
};

// creator a vector of stCoolingTypeInfo.
std::vector<stCoolingTypeInfo> oVectorCoolingTypeInfo {
    stCoolingTypeInfo(CoolingType::PASSIVE_COOLING,0,35),
    stCoolingTypeInfo(CoolingType::HI_ACTIVE_COOLING,0,45),
    stCoolingTypeInfo(CoolingType::MED_ACTIVE_COOLING,0,40),
};


//functions
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
void vDisplayBreachTypeForEmail(BreachType breachType);
stCoolingTypeInfo getCurrentCoolingTypeInfo(CoolingType coolingType);
