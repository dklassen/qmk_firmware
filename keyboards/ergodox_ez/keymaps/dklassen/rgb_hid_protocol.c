#include QMK_KEYBOARD_H
#include "raw_hid.h"


enum hid_commands
{
  hid_version = 0x01,
  hid_rgblight_enable,
  hid_rgblight_disable,
  hid_rgblight_toggle,
  hid_rgblight_set_mode,
  hid_rgblight_get_mode,
  hid_rgblight_sethsv,
  hid_rgblight_increase_val,
  hid_rgblight_decrease_val,
  hid_rgblight_increase_sat,
  hid_rgblight_decrease_sat,
  hid_rgblight_increase_hue,
  hid_rgblight_decrease_hue
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
	  case hid_rgblight_set_mode:
	    rgblight_mode(data[1]);
	    break;
	  case hid_rgblight_get_mode:
	    data[1] = rgblight_get_mode();
	    break;
	  case hid_rgblight_sethsv:
      {
        // Hue is 0 - 360, uint8_t is 0 - 255
        // so we split into two entries.
	      uint16_t hue = (data[1] << 8) + data[2]; 
	      rgblight_sethsv(hue, data[3], data[4]);
        break;
      }
    case hid_rgblight_increase_val:
      rgblight_increase_val();
      break;
    case hid_rgblight_decrease_val:
      rgblight_decrease_val();
      break;
    case hid_rgblight_increase_sat:
      rgblight_increase_sat();
      break;
    case hid_rgblight_decrease_sat:
      rgblight_decrease_sat();
      break;
    case hid_rgblight_increase_hue:
      rgblight_increase_hue();
      break;
    case hid_rgblight_decrease_hue:
      rgblight_increase_hue();
      break;
	  default:
	    data[0] = 0xFF;
	    break;
  }

  raw_hid_send(data, length);
}
