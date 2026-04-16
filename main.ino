int distanceRemaining = 1000;
int fuelLitres = 60;
int speedKmph = 0;
int elapsedTicks = 0;

void printMileage() {
  if (fuelLitres <= 0) {
    Serial.println("Estimated mileage: unavailable (fuel is 0)");
    return;
  }

  int mileage = distanceRemaining / fuelLitres;
  Serial.print("Estimated mileage (distance/fuel): ");
  Serial.println(mileage);
}

void askDistance() {
  Serial.println("Enter distance to travel in km (press Enter):");

  while (!Serial.available()) {
    delay(100);
  }

  String input = Serial.readStringUntil('\n');
  input.trim();

  int parsed = input.toInt();
  if (parsed > 0) {
    distanceRemaining = parsed;
  } else {
    Serial.println("Invalid input. Using default distance: 1000 km");
  }

  Serial.print("Distance to travel: ");
  Serial.println(distanceRemaining);
}

void runSpeedCycle() {
  const int minSpeeds[4] = {0, 10, 20, 30};
  const int maxSpeeds[4] = {20, 25, 40, 45};

  for (int i = 0; i < 4; i++) {
    speedKmph = random(minSpeeds[i], maxSpeeds[i]);
    Serial.print("Current speed: ");
    Serial.println(speedKmph);

    fuelLitres -= 2;
    if (fuelLitres < 0) {
      fuelLitres = 0;
    }

    elapsedTicks++;
    delay(1000);
  }
}

void refillFuelIfNeeded() {
  if (fuelLitres > 45) {
    return;
  }

  Serial.println("FUEL LEVEL LOW.");
  Serial.println("Press 'r' to refill, or any other key to continue.");

  while (!Serial.available()) {
    delay(100);
  }

  int refillIntent = Serial.read();
  if (refillIntent != 'r' && refillIntent != 'R') {
    return;
  }

  Serial.println("How much fuel to refill?");
  Serial.println("a -> 60 litres");
  Serial.println("b -> 55 litres");
  Serial.println("c -> 50 litres");
  Serial.println("d -> 45 litres");

  while (!Serial.available()) {
    delay(100);
  }

  int option = Serial.read();
  switch (option) {
    case 'a':
      fuelLitres = 60;
      Serial.println("Filled to 60 litres.");
      break;
    case 'b':
      fuelLitres = 55;
      Serial.println("Filled to 55 litres.");
      break;
    case 'c':
      fuelLitres = 50;
      Serial.println("Filled to 50 litres.");
      break;
    case 'd':
      fuelLitres = 45;
      Serial.println("Filled to 45 litres.");
      break;
    default:
      Serial.println("Unknown choice. Fuel unchanged.");
      break;
  }
}

void checkDestination() {
  if (distanceRemaining <= 0) {
    Serial.println("Destination reached.");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("Keep driving...");
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  askDistance();
  printMileage();
}

void loop() {
  if (fuelLitres > 45) {
    runSpeedCycle();
  } else {
    refillFuelIfNeeded();
  }

  distanceRemaining -= 100;
  if (distanceRemaining < 0) {
    distanceRemaining = 0;
  }

  Serial.print("Distance remaining to destination: ");
  Serial.println(distanceRemaining);
  Serial.print("Fuel remaining: ");
  Serial.println(fuelLitres);

  printMileage();
  checkDestination();
}
