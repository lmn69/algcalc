#ifndef app_hpp
#define app_hpp

#define BUFSIZE 64 // <256
#define VERSION "0.1"

typedef enum {
	left,right,
	d1,d2,d3,d4,d5,d6,d7,d8,d9,
} app_input_type;

void app_init();
void app_input(app_input_type inputtype);

#endif