//LIbraries needed for program to work
//LiquidCrystal Library allows for an easy access to use the LCD display
#include <LiquidCrystal.h>
//TimeLib allows use to use Time functions to display the current time
#include <TimeLib.h>

//TIME ASSIGNED: 04/20/2005 9:00 a.m.
//ARDUINO TIME LIBRARY GOES OFF OF EPOCH TIME CONVERSION
unsigned int long DEFAULT_TIME = 1713603600;
unsigned int long TIME = 0;

//set digitalPin 8 to access the Buzzer
int buzzerPin = 8;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//List of tasks the user needs to complete. Since its a prototype, only 3 tasks were used to display functionality
//Can be reprogrammed by the user if needed.
String tasks[3] = {"Clean Dishes", "Dust Furniture", "Clean Windows"};

//sets up the code
void setup() {
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);

  //Currently commented out, allows the user to input the current GMT EPOCH time code which would 
  //then be converted to EST EPOCH time code to allow for current time. For demonstration purposes of the device,
  //date and time were hard coded
  
  /*Serial.println("Please input current time in EPOCH: ");

  lcd.setCursor(0,0);
  lcd.print("Awaiting EPOCH");
  lcd.setCursor(0,1);
  lcd.print("Time Input...");
  delay(2000);

  while (Serial.available() == 0) {

  }

  TIME = Serial.parseInt();

  DEFAULT_TIME = ((TIME - 5) / 86400) + 25569;*/ 

  //sets digital pin 8 to be an OUTPUT pin
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  //clears the screen
  lcd.clear();
  
  // Get current time
  time_t currentTime = now();

  //uses the currentTime variable to count the time passed since DEFAULT_TIME
  digitalClockDisplay(currentTime);

  //during the 1st 10 seconds of the program turning on, the LCD display will display task[0] = "Clean Dishes" and the buzzer will go off
  if((DEFAULT_TIME + currentTime >= DEFAULT_TIME + 10) && (DEFAULT_TIME + currentTime <= DEFAULT_TIME + 20)){

    //sets the cursor to the beginning of the 1st row, column 0. 
    lcd.setCursor(0,0);
    //clears row
    lcd.print("              ");
    //sets cursor back to the beginning of the 1st row, column 0
    lcd.setCursor(0,0);
    //prints "REMINDER:" on the 1st row
    lcd.print("REMINDER:");

    //sets cursor to column 0, row 2
    lcd.setCursor(0,1);
    //clears row
    lcd.print("              ");
    //sets cursor back to column 0, row 2
    lcd.setCursor(0,1);
    //prints tasks[0] = "Clean Dishes" in the 2nd row
    lcd.print(tasks[0]);

    //activate buzzer
    triggerBuzzer();
  }
  //30 seconds after program runtime, display task 2, tasks[1] = "Dust Furniture".
  //follows same operation as the previous if statement
  else if((DEFAULT_TIME + currentTime >= DEFAULT_TIME + 30) && (DEFAULT_TIME + currentTime <= DEFAULT_TIME + 40)){
    
    //sets the cursor to the beginning of the 1st row, column 0. 
    lcd.setCursor(0,0);
    //clears row
    lcd.print("              ");
    //sets cursor back to the beginning of the 1st row, column 0
    lcd.setCursor(0,0);
    //prints "REMINDER:" on the 1st row
    lcd.print("9-5 TING");

    //sets cursor to column 0, row 2
    lcd.setCursor(0,1);
    //clears row
    lcd.print("              ");
    //sets cursor back to column 0, row 2
    lcd.setCursor(0,1);
    //prints tasks[0] = "Dust Furniture" in the 2nd row
    lcd.print(tasks[1]);

    triggerBuzzer();
  }
  //50 seconds after program runtime, display task 2, tasks[2] = "Clean Windows".
  //follows same operation as the previous if statement
  else if((DEFAULT_TIME + currentTime >= DEFAULT_TIME + 50) && (DEFAULT_TIME + currentTime <= DEFAULT_TIME + 60)){
    
    //sets the cursor to the beginning of the 1st row, column 0. 
    lcd.setCursor(0,0);
    //clears row
    lcd.print("              ");
    //sets cursor back to the beginning of the 1st row, column 0
    lcd.setCursor(0,0);
    //prints "REMINDER:" on the 1st row
    lcd.print("9-5 TING:");

    //sets cursor to column 0, row 2
    lcd.setCursor(0,1);
    //clears row
    lcd.print("              ");
    //sets cursor back to column 0, row 2
    lcd.setCursor(0,1);
    //prints tasks[0] = "Clean Windows" in the 2nd row
    lcd.print(tasks[2]);

    triggerBuzzer();
  }
} 

//DigitalClockDisplay function will display and keep updating the time on the LCD display
void digitalClockDisplay(time_t currentTime){
  // digital clock display of the time
  //default will be printed on the 1st row, column 0
  lcd.print("Time ");
  printDigits(hour(DEFAULT_TIME + currentTime));
  lcd.print(":");
  printDigits(minute(DEFAULT_TIME + currentTime));
  lcd.print(":");
  printDigits(second(DEFAULT_TIME + currentTime));

  //sets cursor to the second row, column 0
  lcd.setCursor(0, 1);
  //prints the date
  lcd.print("Date ");
  lcd.print(month(DEFAULT_TIME));
  lcd.print("/");
  lcd.print(day(DEFAULT_TIME));
  lcd.print("/");
  lcd.print(year(DEFAULT_TIME)); 
  
  delay(1000);
}

// utility function for digital clock display: prints leading 0 if the number is less than 10
void printDigits(int digits){
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

// Function to trigger the buzzer
void triggerBuzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(1000); // Buzzer on for 1 second
  digitalWrite(buzzerPin, LOW);
}
