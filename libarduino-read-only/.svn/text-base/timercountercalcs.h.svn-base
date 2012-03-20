/* options for 8bit timer counter 0 (TCO) csbits */
#define OVERFLOW_TC0_OFF	0 /* turn off TC0                    */
#define OVERFLOW_TC0_16US	1 /* TC0 overflows every 16 usec     */
#define OVERFLOW_TC0_128US	2 /* TC0 overflows every 128 usec    */
#define OVERFLOW_TC0_1024US	3 /* TC0 overflows every 1.024 msec  */
#define OVERFLOW_TC0_4096US	4 /* TC0 overflows every 4.096 msec  */
#define OVERFLOW_TC0_16384US	5 /* TC0 overflows every 16.384 msec */

/* options for 16bit timer counter 1 (TC1) csbits */
#define OVERFLOW_TC1_OFF	0 /* turn off TC0                    */
#define OVERFLOW_TC1_4MS	1 /* TC1 overflows every 4.0960 msec */
#define OVERFLOW_TC1_33MS	2 /* TC1 overflows every 32.768 msec */
#define OVERFLOW_TC1_262MS	3 /* TC1 overflows every 262.14 msec */
#define OVERFLOW_TC1_1049MS	4 /* TC1 overflows every 1.0486 sec  */
#define OVERFLOW_TC1_4194MS	5 /* TC1 overflows every 4.1943 sec  */

/* options for 8bit timer counter 2 (TC2) csbits */
#define OVERFLOW_TC2_OFF	0 /* turn off TC0                    */
#define OVERFLOW_TC2_16US	1 /* TC2 overflows every 16 usec     */
#define OVERFLOW_TC2_128US	2 /* TC2 overflows every 128 usec    */
#define OVERFLOW_TC2_512US	3 /* TC2 overflows every 512 usec    */
#define OVERFLOW_TC2_1024US	4 /* TC2 overflows every 1.024 msec  */
#define OVERFLOW_TC2_2048US	5 /* TC2 overflows every 2.028 msec  */
#define OVERFLOW_TC2_4096US	6 /* TC2 overflows every 4.096 msec  */
#define OVERFLOW_TC2_16384US	7 /* TC2 overflows every 16.384 msec */

/* set click slection bits on timer counters to determin overflow freq */
#define timercounter0_setoverflow(overflowfreq) TCCR0B = ((TCCR0B & 0xf8) | (overflowfreq))
#define timercounter1_setoverflow(overflowfreq) TCCR1B = ((TCCR1B & 0xf8) | (overflowfreq))
#define timercounter2_setoverflow(overflowfreq) TCCR2B = ((TCCR2B & 0xf8) | (overflowfreq))
