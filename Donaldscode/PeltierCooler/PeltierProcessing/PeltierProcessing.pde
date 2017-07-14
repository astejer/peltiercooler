import processing.serial.*;
Serial mySerial;
PrintWriter output;
void setup() {
  print(Serial.list()[1]);
   mySerial = new Serial( this, Serial.list()[1], 9600 );
   output = createWriter("data.txt");
}
void draw() {
    if (mySerial.available() > 0 ) {
         String value = mySerial.readString();
         
         if ( value != null ) {
           //print(value);
           output.println( value );
         }
    }
}

void keyPressed() {
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    exit();  // Stops the program
}