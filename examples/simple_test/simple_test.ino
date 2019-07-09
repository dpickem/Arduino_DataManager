/**********************************************************
 Copyright (C) 2019 Daniel Pickem - All Rights Reserved

 This is test sketch for the DataManager class.

 MIT license, all text above must be included in any
 redistribution
***********************************************************/

// Include Arduino dependencies.
#include "Arduino.h"

// Include DataManager dependencies.
#include "data_manager.h"

// Instantiate a data manager for float values.
DataManager<float> dm;

void print_all_entries(DataManager<float>* dm) {
    // Test print value.
    for (int i = 0; i < dm->get_size(); i++) {
        Serial.print(dm->get_name(i));
        Serial.print(": ");
        Serial.println(dm->get_value(i));
    }
    Serial.println("----------------");
}

void print_status(DataManager<float>* dm) {
    Serial.print("Number of variables: ");
    Serial.println(dm->get_size());

    Serial.print("Does variable 'temperature' exist: ");
    Serial.println(dm->exists("temperature"));

    Serial.print("Does variable 'humidity' exist: ");
    Serial.println(dm->exists("humidity"));

    Serial.print("Does non-existing variable exist: ");
    Serial.println(dm->exists("boolean"));
    Serial.println("----------------");
}

void setup() {
    // Instantiate Serial connection.
    Serial.begin(115200);

    // Add new data to container.
    dm.update("temperature", 23.5);
    dm.update("humidity", 78.5);

    // Show status and print all contained entries.
    print_status(&dm);
    print_all_entries(&dm);

    // Update one variable and add a new variable as well.
    dm.update("temperature", 29.3);
    dm.update("boolean", false);

    // Print status and all variables.
    print_status(&dm);
    print_all_entries(&dm);
}

void loop() {
    delay(10);
}
