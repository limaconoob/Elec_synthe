/*
 * File:   AudioBuffer.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

/*
u16     audio_buffer[500];
u8      audio_buffer_wr = 100;
u8      audio_buffer_rd = 0;
*/

u16     generateAudioSample(void)
{
    u16     cur_sample = 1;

    if (notesON || cur_env == REL)
    {
        if (!phi)
        {
            phase = (!phase);

            if (reste < 100)
            {
                phi = pitch;
                cursor = ((0xFFFF - cur_amplitude) / pitch);
            }
            else
            {
                reste -= 100;
                phi = pitch + 1;
                cursor = ((0xFFFF - cur_amplitude) / (pitch + 1));
            }
            reste += pitch_adjust;
        }

//        cur_amplitude = 0x3FFF;
       generateur_enveloppe();
       if (presetOnde == CARRE)
            cur_sample = onde_carre();
       else if (presetOnde == SAWTOOTH)
            cur_sample = onde_sawtooth();
       else if (presetOnde == TRIANGLE)
            cur_sample = onde_triangle();

       if (cur_sample == 0)
           cur_sample = 1;
   }
   else
   {
  //      phi = 0;
        cur_sample = 1;
        reste = 0;
   }
   return (cur_sample);
}

/*
void    fillAudioBuffer(void)
{
    if (notesON || cur_env == REL)
    {
        audio_buffer[audio_buffer_wr] = generateAudioSample();
        audio_buffer_wr++;
    }
    else
        audio_buffer[audio_buffer_wr++] = 1;

    if (audio_buffer_wr == 499)
        audio_buffer_wr = 0;
}
*/

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) sampleClock(void)
{
    if (notesON || cur_env == REL)
        DAC_value = generateAudioSample();
    else
        DAC_value = 1;
    IFS0bits.T2IF = FALSE;
}





/*
    DAC_value = audio_buffer[audio_buffer_rd];
    audio_buffer[audio_buffer_rd] = 1;
    audio_buffer_rd++;

    if (audio_buffer_rd == 499)
        audio_buffer_rd = 0;

 *
 *

*/
