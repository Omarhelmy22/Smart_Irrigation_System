//MACROS FUNCTIONS
#define SET_BIT(ADDRESS,BIT) ADDRESS |=(1<<BIT)
#define CLEAR_BIT(ADDRESS,BIT) ADDRESS &=~(1<<BIT)
#define TOGGLE_BIT(ADDRESS,BIT) ADDRESS ^=(1<<BIT)

//ADC FUNCTIONS
void adc_init_int();
uint16_t adc_read_int(uint8_t ch);
