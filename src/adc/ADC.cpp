#ifdef USE_ADC

#include "ADC.h"

void setUpADC()
{
    ADMUX = 0x00;
    ADCSRA = 0x0;

    //setup adc prescaler
    #if ADC_PRESCALER == 128
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    #elif ADC_PRESCALER == 64
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1);
    #elif ADC_PRESCALER == 32
    ADCSRA |= (1<<ADPS2)|(1<<ADPS0);
    #elif ADC_PRESCALER == 16
    ADCSRA |= (1<<ADPS2);
    #else
    #error Incorrect ADC prescaler setting. Valid values are 128, 64, 32 and 16.
    #endif

    //setup voltage reference
    #ifdef VREF_AREF
    //nothing, this is default setting
    #elif defined (VREF_AVCC)
    ADMUX |= (1<<REFS0);
    #elif defined (VREF_INTERNAL_2V56)
    ADMUX |= (1<<REFS0) | (1<<REFS1);
    #elif defined (VREF_INTERNAL_1V1)
    ADMUX |= (1<<REFS1);
    #else
    #error "No ADC reference selected or setting is invalid. Valid options are VREF_AREF, VREF_AVCC, VREF_INTERNAL_2V56 and VREF_INTERNAL_1V1"
    #endif

    //enable ADC
    ADCSRA |= (1<<ADEN);
}

#endif