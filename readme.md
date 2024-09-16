# Sloccy

Sloccy is a source-lines of code CLI tool.
Given a path, it'll read all the files in that directory and its subdirectories
and figure out how many non-whitespace characters and lines
are in each, and then calculates a "score" based on
the expected average characters-per-line and number of characters.

![image](https://github.com/user-attachments/assets/8b3c5b06-5d74-4b6c-bab8-3dc4e4993e84)

## Basic Usage

- `-h` flag will print a help message
- `-v` will print the current version
- `-s` will exclude subdirectories
- `-n` will print without color (see `./build`)
- `-l` will count only `\n` as linebreaks
- `-r` will reset the configuration file
- `-c` will print the configuration

## Configuration

The configuration file is a basic text file that contains
a list of Language-Families, and then the extensions
that belong to that family. Each Language-Family is separated
by a `;` character, and each extension or name is separated
with whitespace.

## Bugs / Missing Features
- completely ignores comments and empty lines
- the last line in the config, if there isn't a space after the last entry,
will interpret it as having one less entry than it should
- the `strncmp` function being used incorrectly returns `true` for strings of mismatched length
such as `.readme` and `.r` since the first parts do match. It also completely ignores the
`len` argument. Tried a couple fixes and had no luck so far, so coming back to it later

## Sloccy's Score

### ghloc score

![Endpoint Badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fghloc.vercel.app%2Fapi%2FJohnAlexCO%2Fsloccy%2Fbadge%3Ffilter%3D.c%24&label=C&labelColor=yellow&color=yellow)
![Endpoint Badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fghloc.vercel.app%2Fapi%2FJohnAlexCO%2Fsloccy%2Fbadge%3Ffilter%3D.md%24%2C.txt%24%2C.readme%24%2C.sml%24&label=Text&labelColor=blue&color=blue)
![Endpoint Badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fghloc.vercel.app%2Fapi%2FJohnAlexCO%2Fsloccy%2Fbadge&label=Total&labelColor=black&color=black)

### Self-Given score
               C    263 pts  9 files, 679 linebreaks, 12k chars
               R    37 pts  1 files, 47 linebreaks, 1k chars
            Text    52 pts  3 files, 117 linebreaks, 2k chars
           Total    352 pts  13 files, 843 linebreaks, 17k chars
