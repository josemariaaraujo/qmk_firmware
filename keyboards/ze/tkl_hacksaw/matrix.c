#include "matrix.h"
#include "gpio.h"

static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
static const pin_t row_pins[MATRIX_MUX_ROWS] = MATRIX_ROW_MUX_PINS;
#define COL_SHIFTER ((uint32_t)1)

/* Rows 0 - 16
 * These rows use two 74HC138 3 to 8 bit demultiplexer. row_pins[3], row_pins[4] is the enable pin, must be set high (1) to use it.
 *
 * row/pin: row_pins[2]  [1]  [0]  [3]  [4]
 * 0:                0 ── 0 ── 0    0 ── 1
 * 1:                0 ── 0 ── 1    0 ── 1
 * 2:                0 ── 1 ── 0    0 ── 1
 * 3:                0 ── 1 ── 1    0 ── 1
 * 4:                1 ── 0 ── 0    0 ── 1
 * 5:                1 ── 0 ── 1    0 ── 1
 * 6:                1 ── 1 ── 0    0 ── 1
 * 7:                1 ── 1 ── 1    0 ── 1
 * 8:                0 ── 0 ── 0    1 ── 0
 * 9:                0 ── 0 ── 1    1 ── 0
 *10:                0 ── 1 ── 0    1 ── 0
 *11:                0 ── 1 ── 1    1 ── 0
 *12:                1 ── 0 ── 0    1 ── 0
 *13:                1 ── 0 ── 1    1 ── 0
 *14:                1 ── 1 ── 1    1 ── 0
 *15:                1 ── 1 ── 0    1 ── 0
 *
 */
static void select_row(uint8_t row) {
    switch (row) {
        case 0:
          writePinLow(row_pins[2]);
          writePinLow(row_pins[1]);
          writePinLow(row_pins[0]);
          writePinLow(row_pins[3]);
          break;
        case 1:
          writePinLow(row_pins[2]);
          writePinLow(row_pins[1]);
          writePinHigh(row_pins[0]);
          writePinLow(row_pins[3]);
          break;
        case 2:
          writePinLow(row_pins[2]);
          writePinHigh(row_pins[1]);
          writePinLow(row_pins[0]);
          writePinLow(row_pins[3]);
          break;
        case 3:
          writePinLow(row_pins[2]);
          writePinHigh(row_pins[1]);
          writePinHigh(row_pins[0]);
          writePinLow(row_pins[3]);
          break;
        case 4:
          writePinHigh(row_pins[2]);
          writePinLow(row_pins[1]);
          writePinLow(row_pins[0]);
          writePinLow(row_pins[3]);
          break;
        case 5:
          writePinHigh(row_pins[2]);
          writePinLow(row_pins[1]);
          writePinHigh(row_pins[0]);
          writePinLow(row_pins[3]);
          break;
        case 6:
          writePinHigh(row_pins[2]);
          writePinHigh(row_pins[1]);
          writePinLow(row_pins[0]);
          writePinLow(row_pins[3]);
          break;
        case 7:
          writePinHigh(row_pins[2]);
          writePinHigh(row_pins[1]);
          writePinHigh(row_pins[0]);
          writePinLow(row_pins[3]);
          break;
        case 8:
          writePinLow(row_pins[2]);
          writePinLow(row_pins[1]);
          writePinLow(row_pins[0]);
          writePinLow(row_pins[4]);
          break;
        case 9:
          writePinLow(row_pins[2]);
          writePinLow(row_pins[1]);
          writePinHigh(row_pins[0]);
          writePinLow(row_pins[4]);
          break;
        case 10:
          writePinLow(row_pins[2]);
          writePinHigh(row_pins[1]);
          writePinLow(row_pins[0]);
          writePinLow(row_pins[4]);
          break;
        case 11:
          writePinLow(row_pins[2]);
          writePinHigh(row_pins[1]);
          writePinHigh(row_pins[0]);
          writePinLow(row_pins[4]);
          break;
        case 12:
          writePinHigh(row_pins[2]);
          writePinLow(row_pins[1]);
          writePinLow(row_pins[0]);
          writePinLow(row_pins[4]);
          break;
        case 13:
          writePinHigh(row_pins[2]);
          writePinLow(row_pins[1]);
          writePinHigh(row_pins[0]);
          writePinLow(row_pins[4]);
          break;
        case 14:
          writePinHigh(row_pins[2]);
          writePinHigh(row_pins[1]);
          writePinHigh(row_pins[0]);
          writePinLow(row_pins[4]);
          break;
        case 15:
          writePinHigh(row_pins[2]);
          writePinHigh(row_pins[1]);
          writePinLow(row_pins[0]);
          writePinLow(row_pins[4]);
          break;
    }
}

static void unselect_rows(void) {
    //Demultiplexer
    writePinHigh(row_pins[3]);
    writePinHigh(row_pins[4]);
    writePinHigh(row_pins[2]);
    writePinHigh(row_pins[1]);
    writePinHigh(row_pins[0]);
}

static void init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
    setPinOutput(row_pins[2]);
    setPinOutput(row_pins[1]);
    setPinOutput(row_pins[0]);
    setPinOutput(row_pins[3]);
    setPinOutput(row_pins[4]);
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    bool matrix_changed = false;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    matrix_io_delay();

    matrix_row_t new_row_value = 0;
    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        // Check col pin state
        if (readPin(col_pins[col_index]) == 0) {
            // Pin LO, set row bit
            new_row_value |= (COL_SHIFTER << col_index);
        }

    }
    // Determine if the matrix changed state
    if (new_row_value != current_matrix[current_row]) {
        matrix_changed = true;
        current_matrix[current_row] = new_row_value;
    }
    // Unselect row
    unselect_rows();

    return matrix_changed;
}

void matrix_init_custom(void) {
    // initialize key pins
    init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
    }

    return changed;
}

