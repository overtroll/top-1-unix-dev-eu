#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

int main(void) {
	setlocale(LC_ALL, "");
	bindtextdomain("guess", LOCALE_PATH);
	textdomain("guess");

	int l = 0;
	int r = 100;
	char ans[228];

	while (l < r) {
		int m = (l + r) / 2;
		const int mid = (l + r) / 2;
		printf(_("> %d: "), mid);


		scanf("%s", ans);

		if (ans[0] == 'y') {
			l = mid;
		} else {
			r = mid;
		}
	}
	printf(_("Answer %d\n"), r);
	return 0;
}