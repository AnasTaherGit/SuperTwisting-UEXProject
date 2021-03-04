typedef union
{
    float number;
    uint8_t bytes[4];
} FLOATUNION_t;

FLOATUNION_t var;
FLOATUNION_t buffer;

float u = 0;
float DesiredPosition = 0;
float ActualPosition = 0;
float error = 0;
float error_temp = 0;
float S, ua;
float ub = 0;
float Ka = 10;
float Kb = 5;
float c = 1;
float deltatime = 0.01;

void setup()
{
    Serial.begin(115200);
}
void loop()
{
    buffer.number = getFloat();
    if (!isnan(buffer.number))
    {
        var.number = constrain(buffer.number, -3.14, 3.14);
        super_t();
        // Sending header to sync
        Serial.write('A');
        // Sending bytes (matlab single)
        for (int i = 0; i < 4; i++)
        {
            Serial.write(var.bytes[i]);
        }
        // Sending closing character
        Serial.print('\n');
    }
    else
    {
        buffer.number = 0;
        Serial.write('A');
        for (int i = 0; i < 4; i++)
        {
            Serial.write(buffer.bytes[i]);
        }
        Serial.print('\n');
    }
    delay(10);
}

float getFloat()
{
    int cont = 0;
    FLOATUNION_t f;
    while (cont < 4)
    {
        // read 4 consecutive bytes from serial
        f.bytes[cont] = Serial.read();
        cont = cont + 1;
    }
    return f.number;
}

void super_t()
{
    ActualPosition = var.number;
    error = ActualPosition - DesiredPosition;
    S = (error - error_temp) / deltatime + c * error;
    error_temp = error;
    ua = sqrt(abs(S)) * sgn(S);
    ub = sgn(S) * deltatime + ub;
    u = -Ka * ua - Kb * ub;
    u = constrain(u, -6, 6);
    var.number = u;
}

float sgn(float x)
{
    if (x == 0)
        return 0;
    else
        return x / abs(x);
}