#include <msp430.h>

// Define pins for sensors and outputs
#define LED_MOTION BIT0 // P1.0 for motion LED
#define LED_LIGHT   BIT1 // P1.1 for light LED
#define LED_TEMP    BIT2 // P1.2 for temperature LED
#define LED_GAS     BIT3 // P1.3 for gas LED
#define BUZZER      BIT4 // P1.4 for buzzer

#define MOTION_SENSOR BIT5 // P1.5 for motion sensor
#define LIGHT_SENSOR  BIT6 // P1.6 for light sensor (photoresistor)
#define GAS_SENSOR    BIT7 // P1.7 for gas sensor
#define TEMP_SENSOR   BIT0 // P1.0 for temperature sensor (analog)

void initialize_gpio(void);
void configure_adc(void);

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    initialize_gpio();
    configure_adc();

    while(1)
    {
        // Simulate sensor reading checks
        if (P1IN & MOTION_SENSOR) // Motion detected
        {
            P1OUT |= LED_MOTION; // Turn on motion LED
            P1OUT |= BUZZER;     // Activate buzzer
        }
        else
        {
            P1OUT &= ~LED_MOTION; // Turn off motion LED
            P1OUT &= ~BUZZER;     // Deactivate buzzer
        }

        // Dummy condition for light, gas, and temperature
        // Replace with actual ADC reading conditions
        if (P1IN & LIGHT_SENSOR) // Low light
        {
            P1OUT |= LED_LIGHT; // Turn on light LED
        }
        else
        {
            P1OUT &= ~LED_LIGHT; // Turn off light LED
        }

        if (P1IN & GAS_SENSOR) // Gas detected
        {
            P1OUT |= LED_GAS; // Turn on gas LED
        }
        else
        {
            P1OUT &= ~LED_GAS; // Turn off gas LED
        }

        // Assuming TEMP_SENSOR is an ADC result
        // This is a placeholder
        if (ADC10MEM < 0x200) // Low temperature
        {
            P1OUT |= LED_TEMP; // Turn on temp LED
        }
        else
        {
            P1OUT &= ~LED_TEMP; // Turn off temp LED
        }
    }
}

void initialize_gpio(void)
{
    // Initialize LED and buzzer pins as output
    P1DIR |= LED_MOTION | LED_LIGHT | LED_TEMP | LED_GAS | BUZZER;
    P1OUT &= ~(LED_MOTION | LED_LIGHT | LED_TEMP | LED_GAS | BUZZER); // Start with all LEDs and buzzer off

    // Initialize sensor pins
    P1DIR &= ~(MOTION_SENSOR | LIGHT_SENSOR | GAS_SENSOR); // Set sensor pins as input
    P1REN |= MOTION_SENSOR | LIGHT_SENSOR | GAS_SENSOR;    // Enable pull-up/pull-down resistors
    P1OUT |= MOTION_SENSOR | LIGHT_SENSOR | GAS_SENSOR;    // Select pull-up resistors
}

void configure_adc(void)
{
    ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON; // Vcc/Vss as reference, sample hold time, ADC on
    ADC10CTL1 = INCH_0; // Channel 0 (P1.0 for temperature), single channel single conversion
    ADC10AE0 |= TEMP_SENSOR; // Enable analog input from temperature sensor
}
