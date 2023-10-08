## Author Details

Braedan Chappel
University of Guelph
September 23rd 2023


## What are "hapax legomena"

My tool will tally how many occurrences of each word there is in each
data file presented on the command line, but our underlying objective
is to list the *hapax legomena*.  Each *hapax legomenon* (the singular
form of this term) is a word that occurs **only once** in an entire
document.

From a processing point of view, however, I don't know
whether any given word is going to occur again until my code has processed
every word in the entire document. Therefore I had to:

* keep track of all of the words, and
* for each word, keep track of a counter indicating how many times it has occurred.

## Intended program function / Command Line

This program is compiled using make and uses the -g -Wall flags for debugging.

The removal of '.o' files can removed by using 'make clean' command.


My program will take information from the command line in order to
determine how it operates. The usage key for our program is this:

	Usage:
	    ./hapax [<options>] <datafile> [ <datafile> ...]

	Options:
	-d     : print out all data loaded before printing hapax legomena.
	-h     : this help.  You are looking at it.
	-l <N> : only print hapax legomena of length <N>.
	       : If no -l option is given, all hapax legomena are printed.


(Note that in program usage statements, the use of `[` `]` brackets indicates
an optional item, and items in `<` `>` brackets indicate a value.
This means that the above is saying that all of the options are, well, optional;
the "`<datafile>`" arguments can optionally be in a list with many filenames; and
the "`-l`" argument takes a number following the argument as a value indicating the length.)


Running the program will print out the hapax legomenon from one or more
data files (of only the desired length if indicated).

Let us say the file "`smalldata.txt`" has this content:

	hello where, hello there
	this is a test
	line three

If we run our "`hapax`" program on this file, this is the output we should see:

	$ ./hapax smalldata.txt 
	Total word count 10
	Tally loaded
	Hapax legomena from file 'smalldata.txt':
		a
		is
		line
		test
		this
		three
		there
		where
	$ ./hapax -l 3 smalldata.txt 
	Total word count 10
	Tally loaded
	Hapax legomena from file 'smalldata.txt':
	$ ./hapax -l 4 smalldata.txt 
	Total word count 10
	Tally loaded
	Hapax legomena from file 'smalldata.txt':
		line
		test
		this