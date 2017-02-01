#include <Wire.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;

void setup(void) {
    uint32_t currentFrequency;
    Serial.begin(9600);
    //Title
    Serial.println("Hello!");
    Serial.println("Measuring voltage and current with INA219 ...");
    //Start the Sensor   
    ina219.begin();
    //Set up the column names
    Serial.print("Bus Voltage V          ");
    Serial.print("Shunt Voltage mV          ");
    Serial.print("Load Voltage V          ");
    Serial.print("Current mA          ");
    Serial.print("Time ms");
    Serial.println();
}


// initialize the variables
float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;

//SET INTERVAL HERE
int interval =500;

void loop(void) {

    //Get the measures
    shuntvoltage = ina219.getShuntVoltage_mV();
    busvoltage = ina219.getBusVoltage_V();
    current_mA = ina219.getCurrent_mA();
    loadvoltage = busvoltage + (shuntvoltage / 1000);

    //Print the values
    Serial.print(busvoltage);     Serial.print("                   ");
    if(busvoltage<10){Serial.print(" ");}
    
    Serial.print(shuntvoltage);   Serial.print("                    ");
    if(shuntvoltage<100) {Serial.print(" ");}
    if(shuntvoltage<10){Serial.print(" ");}
    if(shuntvoltage>=0){Serial.print(" ");}

    Serial.print(loadvoltage);    Serial.print("                    ");
    if(loadvoltage<10) {Serial.print(" ");}
    
    Serial.print(current_mA);     Serial.print("           ");
    if(current_mA<1000) {Serial.print(" ");}
    if(current_mA<100) {Serial.print(" ");}
    if(current_mA<10) {Serial.print(" ");}
    if(current_mA>=0) {Serial.print(" ");}
    
    Serial.println(millis());
    
    //Account for processing delay to 
    //deliver at the noted interval
    delay(interval - millis()%interval);
}
