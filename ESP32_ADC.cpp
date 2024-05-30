#include<Arduino.h>
#include<esp_adc_cal.h>

static const adc1_channel_t C1 = ADC1_CHANNEL_6;//IO34 
static esp_adc_cal_characteristics_t adc1_chars;

float V=0;
void setup()
{
    esp_adc_cal_characterize(ADC_UNIT_1,ADC_ATTEN_11db,ADC_WIDTH_12Bit,0,&adc1_chars);
    pinMode(34,INPUT_PULLUP);
    Serial.begin(115200);
}
uint32_t readVoltage(adc1_channel_t channel)
{
 uint32_t voltage = 0;
 adc1_config_width(ADC_WIDTH_12Bit);
 adc1_config_channel_atten(channel,ADC_ATTEN_11db);

 int reading = adc1_get_raw(channel);
 voltage = esp_adc_cal_raw_to_voltage(reading,&adc1_chars);

 return voltage;
}

void loop()
{

V+=readVoltage(C1);

Serial.printf("%.3fV\n",V/1000.0);
delay(100);

V=0;
}
