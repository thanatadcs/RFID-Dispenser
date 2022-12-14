#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN         9
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

int card[] = {0x70, 0x24, 0x1E, 0x21};

Servo myservo_a;

void setup() {
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	myservo_a.attach(3);
}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	int readCard[4];
	for (int i = 0; i < mfrc522.uid.size; i++) {  // for size of uid.size write uid.uidByte to readCard
   	 readCard[i] = mfrc522.uid.uidByte[i];
	}
	int isCard = 1;
	for (int i=0;i<4;i++) {
		isCard &= readCard[i] == card[i];
	}
	Serial.println(isCard);
	if (isCard) {
		myservo_a.write(90);
		delay(500);
		myservo_a.write(180);
	}
	delay(500);
}
