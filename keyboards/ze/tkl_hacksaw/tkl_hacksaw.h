#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */


//By Zé
#define LAYOUT_tkl_hacksaw( \
KB10,       KB11, KB12, KB13, KB14,       KB15, KB16, KB17, KA40,       KA41, KA42, KA43, KA44,       KA45, KA46, KA47, \
                                                                                                                        \
KA00, KA01, KA02, KA03, KA04, KA05, KA06, KA07, KA50, KA51, KA52, KA53, KA54, KA55,                   KA56, KA57, KB25, \
KA10, KA11, KA12, KA13, KA14, KA15, KA16, KA17, KA60, KA61, KA62, KA63, KA64,                         KA66, KA67, KB26, \
KA20, KA21, KA22, KA23, KA24, KA25, KA26, KA27, KA70, KA71, KA72, KA73, KA74, KA65,                                     \
KB00, KA30, KA31, KA32, KA33, KA34, KA35, KA36, KA37, KA75, KA76, KB04, KB46, KB06,                         KB36,       \
KB01,       KB47, KB02,             KB03,                   KB05, KB45,       KB07,                   KB30, KB37, KB34 \
) { \
    { KA00, KA01, KA02, KA03, KA04, KA05, KA06, KA07}, \
    { KA10, KA11, KA12, KA13, KA14, KA15, KA16, KA17}, \
    { KA20, KA21, KA22, KA23, KA24, KA25, KA26, KA27}, \
    { KA30, KA31, KA32, KA33, KA34, KA35, KA36, KA37}, \
    { KA40, KA41, KA42, KA43, KA44, KA45, KA46, KA47}, \
    { KA50, KA51, KA52, KA53, KA54, KA55, KA56, KA57}, \
    { KA60, KA61, KA62, KA63, KA64, KA65, KA66, KA67}, \
    { KA70, KA71, KA72, KA73, KA74, KA75, KA76, KC_NO}, \
    { KB00, KB01, KB02, KB03, KB04, KB05, KB06, KB07}, \
    { KB10, KB11, KB12, KB13, KB14, KB15, KB16, KB17}, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KB25, KB26, KC_NO}, \
    { KB30, KC_NO, KC_NO, KC_NO, KB34, KC_NO, KB36, KB37}, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KB45, KB46, KB47} \
}
