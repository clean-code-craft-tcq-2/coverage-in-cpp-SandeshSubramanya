#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("Test infers breach accordingly to the limits") 
{
  // value, lower_limit, upper_limit
  #define Lower_limit 20
  #define Upper_limit 30
  
  REQUIRE(inferBreach(12, Lower_limit, Upper_limit) == TOO_LOW);
  REQUIRE(inferBreach(20, Lower_limit, Upper_limit) == NORMAL);
  REQUIRE(inferBreach(30, Lower_limit, Upper_limit) == NORMAL);
  REQUIRE(inferBreach(31, Lower_limit, Upper_limit) == TOO_HIGH);
}

TEST_CASE("Test infers breach according to the limits set to corresponding CoolingType") 
{  
  for (int icount=0 ; icount < (int)oVectorCoolingTypeInfo.size(); ++icount)
  {
    int lower_limits = oVectorCoolingTypeInfo[icount].m_lowerLimit;
    int upper_limits = oVectorCoolingTypeInfo[icount].m_upperLimit; 
    REQUIRE(inferBreach((lower_limits-1), lower_limits, upper_limits) == TOO_LOW);
    REQUIRE(inferBreach((upper_limits-lower_limits), lower_limits, upper_limits) == NORMAL);
    REQUIRE(inferBreach((upper_limits+10), lower_limits, upper_limits) == TOO_HIGH);
  }
}

TEST_CASE("Test classifyTemperatureBreach for various cooling type defined limits ") 
{  
  int CurrentTemperature = 15;
  for (int icount=0 ; icount < (int)oVectorCoolingTypeInfo.size(); ++icount)
  {
    CoolingType oCurrentCoolingType = oVectorCoolingTypeInfo[icount].m_coolingType;
    int lower_limits = oVectorCoolingTypeInfo[icount].m_lowerLimit;
    int upper_limits = oVectorCoolingTypeInfo[icount].m_upperLimit; 
    REQUIRE(classifyTemperatureBreach(oCurrentCoolingType,(lower_limits-CurrentTemperature)) == TOO_LOW );
    REQUIRE(classifyTemperatureBreach(oCurrentCoolingType,(upper_limits+CurrentTemperature)) == TOO_HIGH);
    if (CurrentTemperature <= (upper_limits-lower_limits))
    {
      REQUIRE(classifyTemperatureBreach(oCurrentCoolingType, CurrentTemperature) == NORMAL);
    }
  }
}

TEST_CASE("Test checkAndAlert functionality for various target types and cooling type temperatures ") 
{
  int CurrentTemperature = 15;
  // check for each target type.
  int numberofTargets = 2;
  for (int itargetcount=0 ; itargetcount < numberofTargets; ++itargetcount)
  {
    for (int icount=0 ; icount < (int)oVectorCoolingTypeInfo.size(); ++icount)
    {
      AlertTarget oCurrentAlertTarget = (AlertTarget)itargetcount;
      CoolingType oCurrentCoolingType = oVectorCoolingTypeInfo[icount].m_coolingType;
      int lower_limits = oVectorCoolingTypeInfo[icount].m_lowerLimit;
      int upper_limits = oVectorCoolingTypeInfo[icount].m_upperLimit; 
      BatteryCharacter oCurrentBatteryCharacter;
      oCurrentBatteryCharacter.coolingType = oCurrentCoolingType;
      checkAndAlert(oCurrentAlertTarget,oCurrentBatteryCharacter,(lower_limits-CurrentTemperature));
      checkAndAlert(oCurrentAlertTarget,oCurrentBatteryCharacter,(upper_limits+CurrentTemperature));
      checkAndAlert(oCurrentAlertTarget,oCurrentBatteryCharacter, CurrentTemperature);
    }
  }
}

