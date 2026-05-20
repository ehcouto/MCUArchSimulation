/** MOCKUP **/

#ifndef ATOD_H
#define ATOD_H
#include "C_Extensions.h"
#include "Atod_prm.h"

typedef enum
{
    ATOD_CH0,
    ATOD_CH1,
    ATOD_CH2,
    ATOD_CH3,
    ATOD_CH4,
    ATOD_CH5,
    ATOD_CH6,
    ATOD_CH7,
    ATOD_CH8,
    ATOD_CH9,
    ATOD_CH10,
    ATOD_CH11,
    ATOD_CH12,
    ATOD_CH13,
    ATOD_CH14,
    ATOD_CH15,
    ATOD_CH16,
    ATOD_CH17,
    ATOD_CH18,
    ATOD_CH19,
    ATOD_CH20,
    ATOD_CH21,
    ATOD_CH22,
    ATOD_CH23,
    ATOD_CH24,
    ATOD_CH25,
    ATOD_CH26,
    ATOD_CH27,
    ATOD_CH28,
    ATOD_CH29,
    ATOD_CH30,
    ATOD_CH31,
    ATOD_CH32,
    ATOD_CH33,
    ATOD_CH34,
    ATOD_CH35,
    ATOD_CH36,
    ATOD_CH37,
    ATOD_CH38,
    ATOD_CH39,
    ATOD_CH40,
    ATOD_CH41,
    ATOD_CH42,
    ATOD_CH43,
    ATOD_CH44,
    ATOD_CH45,
    ATOD_CH46,
    ATOD_CH47,
    ATOD_CH48,
    ATOD_CH49,
    ATOD_CH50,
    ATOD_CH51,
    ATOD_CH52,
    ATOD_CH53,
    ATOD_CH54,
    ATOD_CH55,
    ATOD_CH56,
    ATOD_CH57,
    ATOD_CH58,
    ATOD_CH59,
    ATOD_CH60,
    ATOD_CH61,
    ATOD_CH62,
}ATOD_CHANNEL_DEF;


//! ATOD_CHANNEL_RESOLUTION_DEF defines the possible resolution with which the channels can be read
typedef enum
{
    ATOD_RESOLUTION_04BITS,
    ATOD_RESOLUTION_08BITS,
    ATOD_RESOLUTION_10BITS,
    ATOD_RESOLUTION_12BITS,
    ATOD_RESOLUTION_14BITS,
    ATOD_RESOLUTION_16BITS
} ATOD_CHANNEL_RESOLUTION_DEF;

// Main Function
uint16 Atod__Convert(ATOD_CHANNEL_DEF channel,ATOD_CHANNEL_RESOLUTION_DEF resolution);

#endif

// Debug functions
void Atod_Output_Current(uint16 value);
void Atod_Output_Voltage(uint16 value);
void Atod_Output_Hall(uint16 value);

