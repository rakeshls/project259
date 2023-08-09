#include <Keypad.h>

#define ROW_NUM     4 // four rows
#define COLUMN_NUM  4 // four columns

char key = '\0';  //  null key
String input_password = "";
String user_password = "";

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM]      = {19, 18, 5, 17}; // GIOP19, GIOP18, GIOP5, GIOP17 connect to the row pins
byte pin_column[COLUMN_NUM] = {16, 4, 2, 15};   // GIOP16, GIOP4, GIOP0, GIOP2 connect to the column pins

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup() {
  Serial.begin(115200);
  train();
  delay(3000);
  Serial.println("You are now trained");
}

void loop() {

}

void train(){
  Serial.println("Welcome to your personal lock services");
  delay(1000);
  Serial.println("Press # to set a new password");
  while(true){
    key = keypad.getKey();
    if (key  ==  '#')break;
  }
  set_new_password();
  check_password();
}

void set_new_password(){
  Serial.println("Enter a new password. Press # when password set : ");
  while (true){
    key = keypad.getKey();
    if (key){
      if (key  ==  '#'){
        Serial.println();
        Serial.println("Password set");
        break;
      }
      else{
        user_password.concat(key);
        Serial.print('@');
      }
    }
  }
}

void check_password(){
  delay(3000);
  Serial.println("Enter Password. Press # when password entered : ");
  while (true){
    key = keypad.getKey();
    if (key){
      if (key  ==  '#'){
        if (input_password  ==  user_password){
          Serial.println();
          Serial.println("Access granted");
          break;
        }
        else{
          Serial.println();
          Serial.println("Access denied, try again");
          input_password = "";
        }
      }
      else{
        input_password.concat(key);
        Serial.print('@');
      }
    }
  }
}