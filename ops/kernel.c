#include "kernel/tty.h" //terminal handling
#include "kernel/io.h"  //input/output handling
#include "kernel/kbd.h" //keyboard driver
#include "libc/include/string.h" //string functions
#include "kernel/memc/page.h"

void kernel_early(void) {
	terminal_initialize(); //initializes the terminal before main kernel execution
	page_init(); //initializes the page table
	initialize_memory();
	
}

int main(void) {
	char *buff; //initializes the buffer for storing user input
	strcpy(&buff[strlen(buff)], ""); //initializes the buffer to an empty string
	printprompt(); //prints a prompt for the user to enter input
	while (1) { 
		uint8_t byte; 											   //variable to store the byte read from the keyboard
		while (byte = scan()) { 								   //reads a byte from the keyboard
			if (byte == 0x1c) { 								   //if the byte is the enter key
				if (strlen(buff) > 0 && strcmp(buff, "exit") == 0) //"exit" terminates prompt
					printf("\nGoodbye!");
				printprompt();
				memset(&buff[0], 0, sizeof(buff));
				break;
			} else {
				char c = normalmap[byte]; 	//maps the byte to a character
				char *s; 					//initializes a string to store the character
				
				//converts the character to a string
				s = ctos(s, c);
				printf("%s", s);
				strcpy(&buff[strlen(buff)], s);
			}
			move_cursor(get_terminal_row(), get_terminal_col()); //moves the cursor to the current position
		}
	}
	return 0;
}
