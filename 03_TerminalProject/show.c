#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <sys/stat.h>
#include <string.h>

typedef struct stat Stat;
typedef char* String;
typedef WINDOW Window;

#define new(type) malloc(sizeof(type))
#define newa(type, size) malloc(sizeof(type) * size)

size_t get_size(char* filename) {
	Stat st;
	stat(filename, &st);
	return st.st_size;
}

void init_ncurses() {
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	cbreak();
	refresh();
}

int main(int argc, const char* argv[]) {
	size_t size = get_size(argv[1]);
	FILE* f = fopen(argv[1], "r");

	String whole_file = newa(char, size + 1);
	fread(whole_file, sizeof(char), size, f);
	int str_count = 0;
	whole_file[size++] = '\n';
	for (int i = 0; i < size; ++i) {
		str_count += (whole_file[i] == '\n');
	}

	String* lines = newa(String, str_count);

	int p = 0;
	for (int i = 0; i < size; ++i) {
		int nxt = p;
		while (whole_file[nxt] != '\n') {
			++nxt;
		}

		String s = newa(char, nxt - p);
		memcpy(s, whole_file + p, nxt - p);
		s[nxt - p] = 0;
		lines[i] = s;

		p = nxt = 1;
	}
	
	init_ncurses();

	Window* win = newwin(LINES, COLS, 0, 0);
	int x = 0;

	for (;;) {
		werase(win);
		for (int i = x; i < str_count && i < x + LINES; i++) {
			wprintw(win, "%3d: %.50s\n", i, lines[i]);
		}
			
		box(win, 0, 0);
		wrefresh(win);
		char c;
		switch (c = wgetch(win)) {
		case 27:
			endwin();
			fclose(f);
			for (int i = 0; i < str_count; ++i) {
				free(lines[i]);
			}
			free(lines);
			free(whole_file);
			exit(0);
			break;
		case KEY_UP:
			x -= (x > 0);
			break;
		case KEY_DOWN:
			x += (x + LINES + 1 < str_count);
			break;
		}
	}

}