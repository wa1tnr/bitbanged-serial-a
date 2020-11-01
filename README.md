# Sun Nov  1 19:02:14 GMT 2020

Bitbanged Serial

Program is working well.  Prints some sample text, then
an endless string of ascii '5' for use when calibrating
the exact value of 'SECU' (see code).

8.68 uSec basic pulse width (115,200 bps)

ItsyBitsyM4 (ATSAMD51G19A) from Adafruit.




Older version of this README follows.

# Sun Nov  1 11:52:16 UTC 2020

Bitbanged Serial

This seems to be a variant of ainsuForth-d51, privately
held as expA (experiment 'A' iirc).

https://github.com/wa1tnr/ainsuForth-d51.git

If that's the case, it's an Atmel Start based experiment
on serial output, using only software.

Hardware: Probably Feather M4 Express.

At this writing (November 2020) there's just the one C source
file, distinguished by 'bit_CLR' and 'bit_SET' utterances

(That will probably identify the correct file uniquely).

