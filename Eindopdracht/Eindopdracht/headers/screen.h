
/*
 * screen.h
 *
 * Created: 29-3-2019 13:43:45
 *  Author: Bram
 */ 

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_command(unsigned char byte);
