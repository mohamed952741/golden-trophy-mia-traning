// C++ code
//
String pass;
String attempt;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("serial test"); // to keep track of what is loaded
    while(Serial.available() == 0) { } // waits for input of the first password
  	while (Serial.available()) {
    delay(10);  //delay to allow byte to arrive in input buffer
    char p = Serial.read();
    pass += p;
  }

  if (pass.length() >0) {
    Serial.println(pass);
    Serial.println(1);
  } 
}

void loop() {
 while(Serial.available() == 0) { } // waits for input of the attempt
  while (Serial.available()) {
    delay(2);  //delay to allow byte to arrive in input buffer
    char c = Serial.read();
    attempt += c;
  }

  if (attempt.length() >0) //testing the attempt
  {
    Serial.println(attempt);
	Serial.println(2);
  }
  if(attempt == pass) // comparing the attempt to the password
  {
    pass = caesar_cipher_encryption(pass, 1); // password is changed according to ceaser cipher
    digitalWrite(13, HIGH); // led turned on
    delay(3000);
    digitalWrite(13, LOW);
  }
  else{
  	digitalWrite(13, HIGH); // led blinks
  	delay(500);
    digitalWrite(13, LOW);
    delay(2500);
  }
  Serial.println(pass);
  attempt=""; // attempt is reset
}

String caesar_cipher_encryption(String text, int key) {
  String result = text;
  int transformed_index, char_index, char_ascii;
  for(int i = 0; i < text.length(); i++) {
    char_ascii = (int) text[i];
    char_index = (int) char_ascii % 32;
    if(char_ascii>=48 && char_ascii<=57){ // if the input is a number
      if(char_ascii == 57) transformed_index=48;
      else transformed_index=char_ascii+1; 
    }
 else if (char_ascii != 32) {
      transformed_index = (char_index + key) % 26;
      transformed_index = transformed_index % 26 == 0 ? 26 : transformed_index;
      transformed_index += 96;
      if(char_ascii < 96) transformed_index -= 32;
    }
    else
      transformed_index = char_ascii;
    result[i] = transformed_index;
  }
    return result;
}
