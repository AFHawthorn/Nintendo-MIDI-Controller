/* -NESControllerLightVersion -
 * Converts button presses on a NES controller into emulated keyboard presses.
 * This code is a simple implementation of the NES controller protocol. 
 * It contains repetitive code and unnecessarily function calls. It is made for educational purposes.
 * People with little knowledge in programming should be able to follow along and then improve the code by them self, 
 * with for loops, last button state check etc. 
 * Created by Raspberryfield.life August 2018
 */
 /* *NES Controller Pinout Console (Female)*         
  *          _
  * GND   - |O \
  * Clock - |O O| - VCC (5v)  
  * Latch - |O O| - Data N/A (Zapper etc.)
  * Data  - |O O| - Data N/A (Zapper etc.)
  *         ----
  */
  /* *NES protocol ~20ms between each data cycle*
   *           _
   * Latch - _| |___________________________________________________
   *         ______   ___   ___   ___   ___   ___   ___   ___   ____Note1. Last clock does nothing.
   * Clock -       |_|   |_|   |_|   |_|   |_|   |_|   |_|   |_|
   *            _____________________________________________
   *  Data - __|_A_|_|_B_|_|Sel|_|Sta|_|Up_|_|Dow|_|Lef|_|Rig|______
   *  Note2. After Latch goes HIGH, Data goes HIGH and becomes active low (if a button is pushed 
   *  after clock signal, data wire reads low).
   *  Note3. State of A button is read after latch and before first clock.
   */

//Constants for the pinout in the pro micro board (+5V).
const int nesClock = 2;
const int nesLatch = 3;
const int nesData1 = 4;
const int nesData2 = 5;
int note1 = 40;
int note2 = 40;
const int noteON = 144; //144 = 10010000 in binary, note on command
const int noteOFF = 128; //128 = 10000000 in binary, note off command

void setup() {
  // put your setup code here, to run once:
  Serial.begin(31250);      // 31250
  pinMode(nesData1,INPUT_PULLUP); //input_pullup
  pinMode(nesData2,INPUT_PULLUP); //input_pullup
  pinMode(nesClock,OUTPUT);
  pinMode(nesLatch,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(nesClock, LOW);
  digitalWrite(nesLatch, LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  //Pulse Latch wire:
  note1 = 40;
  note2 = 40;
  digitalWrite(nesLatch, HIGH);
  digitalWrite(nesLatch, LOW);
  //After latch pulse, check if A button is pressed:
    //If low, call library Keyboard function press and set a char for it.
      //Else release all key presses for that char.
  if(digitalRead(nesData1)==LOW){
        note1 = 48;
      }else{
      }
  if(digitalRead(nesData2)==LOW){
        note2 = 58;
      }else{
      } 
  // 1st clock.
  digitalWrite(nesClock, LOW);
  digitalWrite(nesClock, HIGH);
  //After 1st clock, check if B button is pressed:
  if(digitalRead(nesData1)==LOW){
        note1 = 49;
      }else{
      }
  if(digitalRead(nesData2)==LOW){
        note2 = 59;
      }else{
      }
  // 2nd clock.
  digitalWrite(nesClock, LOW);
  digitalWrite(nesClock, HIGH);
  //After 2nd clock, check if SELECT button is pressed:
  if(digitalRead(nesData1)==LOW){
        note1 = 50;
      }else{
      }
  if(digitalRead(nesData2)==LOW){
        note2 = 60;
      }else{
      }
  // 3rd clock.
  digitalWrite(nesClock, LOW);
  digitalWrite(nesClock, HIGH);
  //After 3rd clock, check if START button is pressed:
  if(digitalRead(nesData1)==LOW){
        note1 = 51;
      }else{
      }
  if(digitalRead(nesData2)==LOW){
        note2 = 61;
      }else{
      }
  // 4th clock.
  digitalWrite(nesClock, LOW);
  digitalWrite(nesClock, HIGH);
  //After 4th clock, check if UP button is pressed:
  if(digitalRead(nesData1)==LOW){
        note1 = 52;
      }else{
      }
  if(digitalRead(nesData2)==LOW){
        note2 = 62;
      }else{
      }
  // 5th clock.
  digitalWrite(nesClock, LOW);
  digitalWrite(nesClock, HIGH);
  //After 5th clock, check if DOWN button is pressed:
  if(digitalRead(nesData1)==LOW){
        note1 = 53;
      }else{
      }
  if(digitalRead(nesData2)==LOW){
        note2 = 63;
      }else{
      }
  // 6th clock.
  digitalWrite(nesClock, LOW);
  digitalWrite(nesClock, HIGH);
  //After 6th clock, check if LEFT button is pressed:
  if(digitalRead(nesData1)==LOW){
        note1 = 54;
      }else{
      }
  if(digitalRead(nesData2)==LOW){
        note2 = 64;
      }else{
      }
  // 7th clock.
  digitalWrite(nesClock, LOW);
  digitalWrite(nesClock, HIGH);
  //After 7th clock, check if RIGHT button is pressed:
  if(digitalRead(nesData1)==LOW){
        note1 = 55;
      }else{
      }
  if(digitalRead(nesData2)==LOW){
        note2 = 65;
      }else{
      }
  // 8th clock.
  digitalWrite(nesClock, LOW);
  digitalWrite(nesClock, HIGH);
  if(note1 == 40 && note2 != 40) {
    MIDImessage(noteON, note2, 100);//turn note on
    delay(100);//hold note for 300ms
    MIDImessage(noteOFF, note2, 0);//turn note off
    delay(100);//Wait 20ms for next loop. 10 + 10
  } else if(note1 != 40 && note2 == 40) {
    MIDImessage(noteON, note1, 100);//turn note on
    delay(100);//hold note for 300ms
    MIDImessage(noteOFF, note1, 0);//turn note off
    delay(100);//Wait 20ms for next loop. 10 + 10
  } else if(note1 != 40 && note2 != 40) {
    MIDImessage(noteON, note1, 100);//turn note on
    delay(50);//hold note for 300ms
    MIDImessage(noteOFF, note1, 0);//turn note off
    delay(50);
    MIDImessage(noteON, note2, 100);//turn note on
    delay(50);//hold note for 300ms
    MIDImessage(noteOFF, note2, 0);//turn note off
    delay(50);//Wait 20ms for next loop. 10 + 10 + 10
  } else {
    delay(200);
   }
}//End loop

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  //Serial.write("midi: ");
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}
