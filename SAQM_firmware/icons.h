#pragma once

#include <map>

const unsigned char sun [] PROGMEM = {
	// 'sol, 48x48px
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xf1, 
	0xfe, 0x7f, 0x8f, 0xff, 0xff, 0xf1, 0xfe, 0x7f, 0x8f, 0xff, 0xff, 0xf8, 0xfe, 0x7f, 0x1f, 0xff, 
	0xff, 0xf8, 0x7e, 0x7e, 0x1f, 0xff, 0xff, 0xfc, 0x7f, 0xfe, 0x3f, 0xff, 0xff, 0xfe, 0x7f, 0xfe, 
	0x7f, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0xff, 0xff, 0xfe, 0x3e, 0x00, 0x00, 0x7c, 0x7f, 0xfe, 0x1c, 0x00, 0x00, 0x38, 0x7f, 
	0xff, 0x18, 0x00, 0x00, 0x18, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xe0, 
	0x00, 0x00, 0x07, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x60, 0x00, 0x00, 0x06, 0x03, 
	0xc0, 0x60, 0x00, 0x00, 0x06, 0x03, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xe0, 0x00, 0x00, 
	0x07, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 
	0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 0x18, 0x00, 0x00, 0x18, 0xff, 
	0xfe, 0x1c, 0x00, 0x00, 0x38, 0x7f, 0xfe, 0x3e, 0x00, 0x00, 0x7c, 0x7f, 0xff, 0xff, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xfe, 
	0x7f, 0xfe, 0x7f, 0xff, 0xff, 0xfc, 0x7f, 0xfe, 0x3f, 0xff, 0xff, 0xfc, 0x7e, 0x7e, 0x1f, 0xff, 
	0xff, 0xf8, 0xfe, 0x7f, 0x1f, 0xff, 0xff, 0xf0, 0xfe, 0x7f, 0x8f, 0xff, 0xff, 0xf1, 0xfe, 0x7f, 
	0x8f, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

std::map<std::uint8_t, const unsigned char*> iconMap = {{0, sun}};
