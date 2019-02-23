#include QMK_KEYBOARD_H
#include "raw_hid.h"


enum hid_commands
{
  hid_version = 0x01,
  hid_rgblight_enable,
  hid_rgblight_disable,
  hid_rgblight_toggle 
};


void raw_hid_receive( uint8_t *data, uint8_t length ) {
  switch (data[0])
  {
    case hid_version: 
      data[0] = 0x0;
	    data[1] = 0x2;
	    break;
    case hid_rgblight_enable:
	    rgblight_enable();
	    break;
    case hid_rgblight_disable:
	    rgblight_disable();
	    break;
    case hid_rgblight_toggle:
	    rgblight_toggle();
	    break;
	  default:
	    data[0] = 0xFF;
	    break;
  }

  raw_hid_send(data, length);
}
