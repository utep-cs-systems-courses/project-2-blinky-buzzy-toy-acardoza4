#ifndef buzzer_included
#define buzzer_included

#define B5 1012
#define C6 954
#define G5 1274
#define D5 1702
#define E5 1516
#define A5 1136
#define F5 1430
#define Bb5 1073
#define D6 850
#define G6 1244

extern char play_song;
extern int notes[14];
extern int note_duration[14];
extern int delay_time[14];

void buzzer_init();
void buzzer_set_period(short cycles);

#endif // included
