//
// os/input.c
//
// Input device handling functions.
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#include "bus/controller.h"
#include "common.h"
#include "os/input.h"
#include "os/keycodes.h"
#include "si/controller.h"

bool shift_down;

void keyboard_press_callback(struct bus_controller *bus, unsigned key) {
  struct si_controller *si = bus->si;

  //fprintf(stderr, "os/input: Got keypress event: %u\n", key);

  if (key == CEN64_KEY_LSHIFT || key == CEN64_KEY_RSHIFT) {
    shift_down = true;
    return;
  }

  switch (key) {
    // Analog stick.
    case CEN64_KEY_LEFT: si->input[2] = shift_down ? 114 : 38; break;
    case CEN64_KEY_RIGHT: si->input[2] = shift_down ? -114 : -38; break;
    case CEN64_KEY_UP: si->input[3] = shift_down ? 114 : 38; break;
    case CEN64_KEY_DOWN: si->input[3] = shift_down ? -114 : -38; break;

    // L/R flippers.
    case CEN64_KEY_A: si->input[1] |= 1 << 5; break;
    case CEN64_KEY_S: si->input[1] |= 1 << 4; break;

    // A/Z/B/S buttons.
    case CEN64_KEY_X: si->input[0] |= 1 << 7; break;
    case CEN64_KEY_C: si->input[0] |= 1 << 6; break;
    case CEN64_KEY_Z: si->input[0] |= 1 << 5; break;
    case CEN64_KEY_RETURN: si->input[0] |= 1 << 4; break;
  }
}

void keyboard_release_callback(struct bus_controller *bus, unsigned key) {
  struct si_controller *si = bus->si;

  //fprintf(stderr, "os/input: Got keyrelease event: %u\n", key);

  if (key == CEN64_KEY_LSHIFT || key == CEN64_KEY_RSHIFT) {
    shift_down = false;
    return;
  }

  switch (key) {
    // Analog stick.
    case CEN64_KEY_LEFT: si->input[2] = 0; break;
    case CEN64_KEY_RIGHT: si->input[2] = 0; break;
    case CEN64_KEY_UP: si->input[3] = 0; break;
    case CEN64_KEY_DOWN: si->input[3] = 0; break;

    // L/R flippers.
    case CEN64_KEY_A: si->input[1] &= ~(1 << 5); break;
    case CEN64_KEY_S: si->input[1] &= ~(1 << 4); break;

    // A/Z/B/S buttons.
    case CEN64_KEY_X: si->input[0] &= ~(1 << 7); break;
    case CEN64_KEY_C: si->input[0] &= ~(1 << 6); break;
    case CEN64_KEY_Z: si->input[0] &= ~(1 << 5); break;
    case CEN64_KEY_RETURN: si->input[0] &= ~(1 << 4); break;
  }
}
