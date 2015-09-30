#include "../git-compat-util.h"

/* Adapted from libiberty's basename.c.  */
char *gitbasename (char *path)
{
	const char *base;
	/* Skip over the disk name in MSDOS pathnames. */
	if (has_dos_drive_prefix(path))
		path += 2;
	for (base = path; *path; path++) {
		if (is_dir_sep(*path))
			base = path + 1;
	}
	return (char *)base;
}

char *gitdirname(char *path)
{
	char *p = path, *slash, c;

	/* Skip over the disk name in MSDOS pathnames. */
	if (has_dos_drive_prefix(p))
		p += 2;
	/* POSIX.1-2001 says dirname("/") should return "/" */
	slash = is_dir_sep(*p) ? ++p : NULL;
	while ((c = *(p++)))
		if (is_dir_sep(c)) {
			char *tentative = p - 1;

			/* POSIX.1-2001 says to ignore trailing slashes */
			while (is_dir_sep(*p))
				p++;
			if (*p)
				slash = tentative;
		}

	if (!slash)
		return ".";
	*slash = '\0';
	return path;
}
