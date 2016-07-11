
#include "SynthyTwo.h"


//u8             midi_notesON[88];

void            arpeggios_descend(void)
{
    if (!arpeg)
    {
        while (midi_notesON[arpeg])
            arpeg++;
    }
    arpeg--;
    midi_note = midi_notesON[arpeg];
    calculatePitch(read_period_preset(&OSC1), &OSC1);
    calculatePitch(read_period_preset(&OSC2), &OSC2);
}

void            arpeggios_ascend(void)
{
    arpeg++;
    if (midi_notesON[arpeg] == 0)
        arpeg = 0;
    midi_note = midi_notesON[arpeg];
    calculatePitch(read_period_preset(&OSC1), &OSC1);
    calculatePitch(read_period_preset(&OSC2), &OSC2);
}

void            arpeggios(void)
{
    static u16  count = 0;
    static u8   way = 0;

    if (count < 5000000 * cur_preset.ARPG_Speed)
        count++;
    else if (cur_preset.ARPG_Type == 1 || (cur_preset.ARPG_Type == 3 && !way))
    {
        count = 0;
        way ^= 1;
        arpeggios_ascend();
    }
    else if (cur_preset.ARPG_Type == 2 || (cur_preset.ARPG_Type == 3 && way))
    {
        count = 0;
        way ^= 1;
        arpeggios_descend();
    }
}
