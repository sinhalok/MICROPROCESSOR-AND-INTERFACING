#include &lt;Arduino_FreeRTOS.h&gt;

void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

void setup() {

Serial.begin(9600);

//Now set up two tasks to run independently.
xTaskCreate(
TaskBlink
, (const portCHAR *)&quot;Blink&quot;
, 128   //stack size
, NULL
, 2  //priority
, NULL );

xTaskCreate(
TaskAnalogRead
, (const portCHAR *) &quot;AnalogRead&quot;
, 128  //this stack size can be checked & adjusted by reading. 
, NULL
, 1    //priority
, NULL );
pinMode(2,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
}

void loop()
{

}

void TaskBlink(void *pvParameters) // This is a task.
{
(void) pvParameters;

for (; ;) // A Task shall never return or exit.
{
digitalWrite(2, HIGH);
vTaskDelay(10000 / portTICK_PERIOD_MS );
digitalWrite(2, LOW); // turn the LED off by making the voltage LOW
vTaskDelay(10000 / portTICK_PERIOD_MS ); // wait for one second
}
}

void TaskAnalogRead(void *pvParameters) // This is a task.
{
(void) pvParameters;

for (; ;)
{
if (digitalRead(11) == HIGH){
analogWrite(5,35);
analogWrite(6,35);
while (digitalRead(9) == LOW)
{
Serial.println(&quot;ir1&quot;);
analogWrite(5,250);
}
while (digitalRead(10) == HIGH)

{
Serial.println(&quot;ir2&quot;);
analogWrite(6,250);

}
}
else {
digitalWrite(5,LOW);
digitalWrite(6,LOW);
}
vTaskDelay(1); //one tick delay in between read for stability.
}
}
