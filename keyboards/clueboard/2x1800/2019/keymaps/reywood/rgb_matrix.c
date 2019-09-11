#include "rgb_matrix.h"

#define xx NO_LED
#define UG LED_FLAG_UNDERGLOW

led_config_t g_led_config = { {
    // Key Matrix to LED Index
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
    // { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx }
}, {
    // LED Index to Physical Position
//   { 0, 0 }, { 0,  11 }, { 0,  22 }, { 0,  33 }, {  0,  44 }, {  0,  55 }, {  0,  64 },

//   {0, 64}, {9, 64}, {18, 64}, {27, 64}, {36, 64}, {45, 64}, {54, 64}, {63, 64}, {72, 64}, {81, 64}, {90, 64}, {99, 64},
//   {108, 64}, {116, 64}, {125, 64}, {134, 64}, {143, 64}, {152, 64}, {161, 64}, {170, 64}, {179, 64}, {188, 64},
//   {197, 64}, {206, 64}, {215, 64}, {224, 64}

    // top row
    {0, 0}, {9, 0}, {18, 0}, {27, 0}, {36, 0}, {45, 0}, {54, 0}, {63, 0}, {72, 0}, {81, 0}, {90, 0}, {99, 0},
    {108, 0}, {116, 0}, {125, 0}, {134, 0}, {143, 0}, {152, 0}, {161, 0}, {170, 0}, {179, 0}, {188, 0},
    {197, 0}, {206, 0}, {215, 0}, {224, 0},

    // right column
    {224, 0}, {224, 9}, {224, 18}, {224, 27}, {224, 36}, {224, 45}, {224, 54}, {224, 64},

    // bottom row
    {215, 64}, {206, 64}, {197, 64}, {188, 64}, {179, 64}, {170, 64}, {161, 64}, {152, 64}, {143, 64},
    {134, 64}, {125, 64}, {116, 64}, {108, 64}, {99, 64}, {90, 64}, {81, 64}, {72, 64}, {63, 64},
    {54, 64}, {45, 64}, {36, 64}, {27, 64}, {18, 64}, {9, 64},

    // left column
    {0, 64}, {0, 54}, {0, 45}, {0, 36}, {0, 27}, {0, 18}, {0, 9}, {0, 0}
}, {
    // LED Index to Flag
    UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG,

    UG, UG, UG, UG, UG, UG, UG, UG,

    UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG, UG,

    UG, UG, UG, UG, UG, UG, UG, UG,
} };


// x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION
// y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION
