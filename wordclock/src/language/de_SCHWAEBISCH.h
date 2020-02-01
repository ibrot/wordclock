#ifndef WORDCLOCK_GRID_LANG_DE_SCHWAEBISCH_H
#define WORDCLOCK_GRID_LANG_DE_SCHWAEBISCH_H

class Grid_de_SCHWAEBISCH {
	public:
	static int time_it_is[6];
	static int time_minutes[12][18];
	static int time_hours[12][7];

	static void setTime(int hour, int minute);
};

typedef class Grid_de_SCHWAEBISCH Grid;

#endif
