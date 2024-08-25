/*
    Lookup Table Sound is used by the buzzer to lookup melodies and node frequencies.
*/

#ifndef _LUT_SOUND_H_
#define _LUT_SOUND_H_
#include <stdint.h>

#define SILENCE 108
/* NOTE IDs */
#define C0	0
#define CS0	1
#define D0	2
#define DS0	3
#define E0	4
#define F0	5
#define FS0	6
#define G0	7
#define GS0	8
#define A0	9
#define AS0	10
#define B0	11
#define C1	12
#define CS1	13
#define D1	14
#define DS1	15
#define E1	16
#define F1	17
#define FS1	18
#define G1	19
#define GS1	20
#define A1	21
#define AS1	22
#define B1	23
#define C2	24
#define CS2	25
#define D2	26
#define DS2	27
#define E2	28
#define F2	29
#define FS2	30
#define G2	31
#define GS2	32
#define A2	33
#define AS2	34
#define B2	35
#define C3	36
#define CS3	37
#define D3	38
#define DS3	39
#define E3	40
#define F3	41
#define FS3	42
#define G3	43
#define GS3	44
#define A3	45
#define AS3	46
#define B3	47
#define C4	48
#define CS4	49
#define D4	50
#define DS4	51
#define E4	52
#define F4	53
#define FS4	54
#define G4	55
#define GS4	56
#define A4	57
#define AS4	58
#define B4	59
#define C5	60
#define CS5	61
#define D5	62
#define DS5	63
#define E5	64
#define F5	65
#define FS5	66
#define G5	67
#define GS5	68
#define A5	69
#define AS5	70
#define B5	71
#define C6	72
#define CS6	73
#define D6	74
#define DS6	75
#define E6	76
#define F6	77
#define FS6	78
#define G6	79
#define GS6	80
#define A6	81
#define AS6	82
#define B6	83
#define C7	84
#define CS7	85
#define D7	86
#define DS7	87
#define E7	88
#define F7	89
#define FS7	90
#define G7	91
#define GS7	92
#define A7	93
#define AS7	94
#define B7	95
#define C8	96
#define CS8	97
#define D8	98
#define DS8	99
#define E8	100
#define F8	101
#define FS8	102
#define G8	103
#define GS8	104
#define A8	105
#define AS8	106
#define B8	107

extern const uint16_t NOTES[109];

// positions in array
#define SIZE 2
#define NOTE 0
#define TIME 1


extern const uint8_t MELODY_PLAYER_DAMAGE[8][2]; // player taking damage
extern const uint8_t MELODY_PLAYER_CRASH[6][2]; // player died
extern const uint8_t MELODY_SCOM[49][2]; // Guns and roses - sweet child of mine
extern const uint8_t MELODY_SHOOT[6][2]; // used by dying enemies and powerups



#endif /* _LUT_SOUND_H_ */
