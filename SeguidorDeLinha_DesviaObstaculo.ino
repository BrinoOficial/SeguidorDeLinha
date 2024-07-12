// [Br.ino] Seguir linhas +Desviar de Obstáculo
// Definição dos pinos

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

#define ENA 5
#define ENB 6

#define sensorEsquerdo A0
#define sensorDireito A1

#define trigPin 7
#define echoPin 6

void setup() {
  // Configuração dos pinos dos motores como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configuração dos pinos PWM dos motores como saída
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Configuração dos pinos dos sensores de linha como entrada
  pinMode(sensorEsquerdo, INPUT);
  pinMode(sensorDireito, INPUT);

  // Configuração dos pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Leitura dos sensores de linha
  int leituraSensorEsquerdo = digitalRead(sensorEsquerdo);
  int leituraSensorDireito = digitalRead(sensorDireito);

  // Leitura do sensor ultrassônico
  long duracao;
  int distancia;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao * 0.034 / 2;

  // Se um obstáculo for detectado a uma distância menor que 20 cm, parar
  if (distancia < 20) {
    parar();
  } else {
    // Caso contrário, seguir a linha normalmente
    if (leituraSensorEsquerdo == LOW && leituraSensorDireito == LOW) {
      // Ambos os sensores estão sobre a linha
      frente();
    } else if (leituraSensorEsquerdo == HIGH && leituraSensorDireito == LOW) {
      // Apenas o sensor esquerdo está fora da linha
      direita();
    } else if (leituraSensorEsquerdo == LOW && leituraSensorDireito == HIGH) {
      // Apenas o sensor direito está fora da linha
      esquerda();
    } else {
      // Ambos os sensores estão fora da linha
      parar();
    }
  }

  delay(100);
}

void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void direita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void esquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
