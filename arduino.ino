// Define constants for LM35 sensor and led pins
const int lm35Pin = A0;    // LM35 sensor pin
const int ledPin = 13;  // led pin

// Variables to store temperature, led state, and counters
float temperature;
bool ledState = LOW;
int belowThresholdCounter = 0;
int aboveThresholdCounter = 0;

// Constants for temperature threshold, led intervals, and conversion factor
const float temperatureThreshold = 30.0;
const int belowThresholdInterval = 250;
const int aboveThresholdInterval = 500;
const float temperatureConversionFactor = 0.48876;

// Setup function runs once at the beginning
void setup() 
{
  pinMode(lm35Pin, INPUT);   // Set LM35 sensor pin as input
  pinMode(ledPin, OUTPUT);   // Set led sensor pin as output
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

// Main execution loop
void loop() 
{
  // Read the temperature from LM35 sensor
  temperature = readTemperature();

  //print temperature to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Check temperature conditions and control led accordingly
  if (temperature < temperatureThreshold) 
  {
    manageBelowThresholdled();
  } else 
  {
    manageAboveThresholdled();
  }
}

// Function to read temperature from LM35 sensor
float readTemperature() 
{
  return analogRead(lm35Pin) * temperatureConversionFactor;  // Convert to Celsius
}

// Function to manage led when temperature is below the threshold
void manageBelowThresholdled()
{
  // Increment the below threshold counter
  belowThresholdCounter++;

  // Check if the specified interval has passed
  if (belowThresholdCounter >= belowThresholdInterval / 2) 
  {
    // Reset the counter
    belowThresholdCounter = 0;

    // Toggle the led state
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}

// Function to manage led when temperature is above the threshold
void manageAboveThresholdled() 
{
  // Increment the above threshold counter
  aboveThresholdCounter++;

  // Check if the specified interval has passed
  if (aboveThresholdCounter >= aboveThresholdInterval / 2) 
  {
    // Reset the counter
    aboveThresholdCounter = 0;

    // Toggle the led state
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}
