#include "typewise-alert.h"
#include <stdio.h>

/*BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
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

---------------------------------------------------------------*/

#include <iostream>
using namespace std;

class tclIAlterTarget      //  I-> interface
{
  public:
  virtual void vSend(BreachType oBreachType) = 0;
};

class tclEmail : public tclIAlterTarget    // tcl-> type class
{
    virtual void vSend(BreachType oBreachType)
    {
        const char* recepient = "a.b@c.com";
        switch(oBreachType) {
        case BreachType::TOO_LOW :
            printf("To: %s\n", recepient);
            printf("Hi, the temperature is too low\n");
            break;
        case BreachType::TOO_HIGH:
            printf("To: %s\n", recepient);
            printf("Hi, the temperature is too high\n");
            break;
        case BreachType::NORMAL:
            break;
        }
    }
};

class tclController: public tclIAlterTarget
{
    public:
    virtual void vSend(BreachType oBreachType)
    {
        const unsigned short header = 0xfeed;
        printf("%x : %x\n", header, oBreachType);
    }
};

class ICoolingTypeStrategy  // I-> interface
{
    
  protected:
  int lower_limit; // each cooling type will have its own upper limit and lower limit
  int upper_limit;
  
  public:
  virtual void setAltertTarget(AlertTarget eAlertTarget) = 0;
  virtual BreachType inferBreach (double value, double lowerLimit, double upperLimit) = 0;
};



// client interface
// client has to know only strategy + the alter target type + value

class Context
{
    private:
    ICoolingTypeStrategy *strategy_coolingtype;
    
    public:
    Context(AlertTarget oAlertTarget, ICoolingTypeStrategy *strategy_cooling = nullptr) : strategy_coolingtype(strategy_cooling)
    {
        //set alert type set by the user
        strategy_coolingtype ->setAltertTarget(oAlertTarget);
    }
   
    ~Context()
    {
        delete this->strategy_coolingtype;
    }
  
    BreachType inferBreach (double temp_value, double lowerLimit, double upperLimit)
    {
      return (strategy_coolingtype -> inferBreach (value, lowerlimit, upperlimit));
    }
};


class tclPassiveCooling : public ICoolingTypeStrategy
{
   private:
   AlertTarget *poAlertTarget;
   
   public:
   tclPassiveCooling()
   {
       lower_limit = 0;
       upper_limit = 45;
       poAlertTarget = NULL;
   }
   ~tclPassiveCooling()
   {
     delete poAlertTarget;
     poAlertTarget = NULL;
   }
   virtual void setAltertTarget(AlertTarget oAlertTarget)
   {
       poAlertTarget = &oAlertTarget;
   }
   virtual BreachType inferBreach (double value, double lowerLimit, double upperLimit)
   {
        if(value < lower_limit) 
        {
            return BreachType::TOO_LOW;
        }
        if(value > upper_limit) 
        {
            return BreachType::TOO_HIGH;
        }
        return BreachType::NORMAL;
   }
};



