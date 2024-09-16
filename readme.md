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
- `-r` will reset the configuration file
- `-c` will print the configuration

## Configuration

The configuration file is a basic text file that contains
a list of Language-Families, and then the extensions
that belong to that family. Each Language-Family is separated
by a `;` character, and each extension or name is separated
with whitespace.