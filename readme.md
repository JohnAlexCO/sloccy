# Sloccy

Sloccy is a source-lines of code CLI tool.
Given a path, it'll read all the files in that directory and its subdirectories
and figure out how many non-whitespace characters and lines
are in each, and then calculates a "score" based on
the expected average characters-per-line and number of characters.

## Basic Usage

- `-h` flag will print a help message
- `-v` will print the current version
- `-s` will exclude subdirectories
- `-n` will print without color (see `./build`)
- `-r` will reset the configuration file
- `-c` will print the configuration

## Configuration

The configuration file is a basic text file that contains
a list of Language-Families, and then the extensions
that belong to that family. Each Language-Family is separated
by a `;` character, and each extension or name is separated
with whitespace.

## Bugs
- the last line in the config, if there isn't a space after the last entry,
will interpret it as having one less entry than it should
- the `strncmp` function being used incorrectly returns `true` for strings of mismatched length
such as `.readme` and `.r` since the first parts do match. It also completely ignores the
`len` argument. Tried a couple fixes and had no luck so far, so coming back to it later

## Sloccy's Score
               C    261 pts  9 files, 672 lines, 12696 chars
               R    20 pts  1 files, 34 lines, 1005 chars
            Text    28 pts  3 files, 97 lines, 1392 chars
           Total    309 pts  13 files, 803 lines, 15093 chars
