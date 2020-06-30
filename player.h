/*
 * gbsplay is a Gameboy sound player
 * This file contains the player code common to both CLI and X11 frontends.
 *
 * 2003-2005,2008,2018,2020 (C) by Tobias Diedrich <ranma+gbsplay@tdiedrich.de>
 *                                 Christian Garbs <mitch@cgarbs.de>
 * Licensed under GNU GPL v1 or, at your option, any later version.
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "common.h"

#include "gbs.h"
#include "plugout.h"
#include "cfgparser.h"

#define LN2 .69314718055994530941
#define MAGIC 5.78135971352465960412
#define FREQ(x) (262144 / x)
/* #define NOTE(x) ((log(FREQ(x))/LN2 - log(55)/LN2)*12 + .2) */
#define NOTE(x) ((long)((log(FREQ(x))/LN2 - MAGIC)*12 + .2))

#define MAXOCTAVE 9

/* player modes */
#define PLAYMODE_LINEAR  1
#define PLAYMODE_RANDOM  2
#define PLAYMODE_SHUFFLE 3

/* global variables */
extern char *myname;
extern char *filename;
extern long quit;
extern long pause_mode;

extern unsigned long random_seed;

extern long refresh_delay;

/* default values */
extern long playmode;
extern long loopmode;
extern enum plugout_endian endian;
extern long verbosity;
extern long rate;
extern long silence_timeout;
extern long fadeout;
extern long subsong_gap;
extern long subsong_start;
extern long subsong_stop;
extern long subsong_timeout;

extern const char cfgfile[];

extern char *sound_name;
extern char *filter_type;
extern char *sound_description;
extern plugout_open_fn  sound_open;
extern plugout_skip_fn  sound_skip;
extern plugout_pause_fn sound_pause;
extern plugout_io_fn    sound_io;
extern plugout_step_fn  sound_step;
extern plugout_write_fn sound_write;
extern plugout_close_fn sound_close;

extern struct gbhw_buffer buf;

extern const struct cfg_option options[];

struct displaytime {
	long played_min, played_sec, total_min, total_sec;
};

regparm long get_next_subsong(struct gbs *gbs);
regparm int get_prev_subsong(struct gbs *gbs);
regparm long nextsubsong_cb(struct gbs *gbs, void *priv);
regparm void update_displaytime(struct displaytime *time, struct gbs *gbs);
regparm struct gbs *common_init(int argc, char **argv);

#endif