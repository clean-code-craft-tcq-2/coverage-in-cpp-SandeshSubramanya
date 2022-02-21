#include "typewise-alert.h"
#include <stdio.h>
#include <iostream>
using namespace std;

/*typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;


typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter; */

BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
  if(value < lowerLimit) 
  {
    return TOO_LOW;
  }
  if(value > upperLimit) 
  {
    return TOO_HIGH;
  }
  return NORMAL;
}

class tclIAlterTarget      //  I-> interface
{
  public:
  virtual void vSend(BreachType oBreachType) = 0;
};

class tclEmail : public tclIAlterTarget    // tcl-> type class
{
    virtual void vSend(BreachType oBreachType)
    {
    /*    const char* recepient = "a.b@c.com";
        switch(oBreachType) 
        {
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
    }*/
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
  virtual void setAltertTarget(AlertTarget eAlertTarget) = 0;   //sets the target alert
  virtual BreachType inferBreach (double value) = 0;
  virtual void vSendBreachToTargetAlert(BreachType oBreachType) = 0;
};



// client interface
// client has to know only strategy + the alter target type + temperature value

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
  
    BreachType inferBreach (double temp_value)
    {
      return ( strategy_coolingtype ->inferBreach(temp_value) );
    }
    
    void vSend(BreachType oBreachType)
    {
        strategy_coolingtype -> vSendBreachToTargetAlert(oBreachType);
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
   virtual BreachType inferBreach(double value)
   {
        return ::inferBreach(value,lower_limit,upper_limit);
   }
   void vSendBreachToTargetAlert(BreachType oBreachType)
   {
       cout<<"Breached";
   }
};




