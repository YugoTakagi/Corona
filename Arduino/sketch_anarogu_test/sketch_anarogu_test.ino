int potpin = 0 ; 
int val = 0 ; 

void setup()
{
    Serial.begin(9600);
}
void loop()
{
    delay(50);
    val =  analogRead(potpin);
    Serial.println(val) ;
}
