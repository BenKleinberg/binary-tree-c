//Author: Benjamin Kleinberg

#include "command.h"

Command::Command() {
	initialize();
}

void Command::initialize() {
	num = 0;
	flag = 0;
	for(int index = 0; index < MAX_ARGUMENTS; index++)
		arguments[index] = 0;
}

/**
 * Interprets a command from a given c-string.
 *
 * @param text c-string to interpret.
 *
 * @return boolean result of the attempt, with 0 meaning failure to read.
 * 			On a failed read, num is set to negative showing which argument was invalid.
 */
int Command::readCommand(const char* text) {
	int readSuccess = 1;
	initialize();

	//If the text is a null pointer return a fail flag
	if(text == 0)
		readSuccess = 0;

	else {
		readSuccess = readFlag(text);

		//Read the arguments unless a failure occurs
		while(readSuccess && *text != '\0')
			readSuccess = readArgument(text);
	}

	return readSuccess;
}

/**
 * Reads the single character flag from the given c-string and advances
 * the pointer forward.
 * The flag is stored in flag.
 *
 * @param &text the c-string to read the flag from.
 * @post &text is advanced forward past the flag.
 *
 * @return boolean result of the attempt, with 0 meaning failure to read.
 */
int Command::readFlag(const char* &text) {
	int readSuccess = 1;

	//If the text is a null pointer then fail to read
	if(text == 0)
		readSuccess = 0;

	else {
		text = stripWhiteSpace(text);
		if(!isWhiteSpace(*text)) {
			flag = *text;
			text++;
		}

		//If the flag is too long then fail to read
		if(!isWhiteSpace(*text)) {
			flag = 0;
			readSuccess = 0;
		}
	}

	return readSuccess;
}

/**
 * Reads an integer argument from the given c-string and advances
 * the pointer forward.
 * The argument is stored in the next args slot, if available.
 *
 * @param &text the c-string to read the argument from
 * @post &text is advanced forward past the argument
 *
 * @return boolean result of the attempt, with 0 meaning failure to read.
 */
int Command::readArgument(const char* &text) {
	int readSuccess = 1;

	//If the text is a null pointer then fail
	if(text == 0)
		readSuccess = 0;
	//If the command is already invalid then fail
	else if(num < 0)
		readSuccess = 0;

	text = stripWhiteSpace(text);

	if(readSuccess && *text != '\0') {
		//If the argument list is full then fail
		if(num >= MAX_ARGUMENTS)
			readSuccess = 0;

		else {
			arguments[num] = 0;
			int isNegative = 0;

			//Make the number negative if the leading character is a -
			if(*text == '-') {
				isNegative = 1;
				text++;

				//A single - is not a valid argument
				if(isWhiteSpace(*text))
					readSuccess = 0;
			}

			//Read in the number until whitespace is hit
			while(readSuccess && !isWhiteSpace(*text)) {
				if(*text >= '0' && *text <= '9')
					arguments[num] = arguments[num] * 10 + *text - '0';

				//If the character read is not a number then fail
				else
					readSuccess = 0;
				text++;
			}

			if(isNegative)
				arguments[num] = -arguments[num];
		}

		num = num + 1;
		//If the read failed, set num to negative to show which argument failed
		if(!readSuccess)
			num = -num;
	}

	return readSuccess;
}

/**
 * Finds the first character in a c-string that is not whitespace.
 *
 * @param text c-string that will have the whitespace removed.
 *
 * @return a pointer to the first non whitespace character, or the null character if there are none
 */
const char* stripWhiteSpace(const char* text) {
	//Do not strip null pointers
	if(text == 0)
		return 0;

	while(*text != '\0' && isWhiteSpace(*text))
		text++;

	return text;
}

/**
 * Determines whether a given character is considered whitespace.
 *
 * @param ch the character the check.
 *
 * @return a boolean result where true means it is whitespace.
 */
int isWhiteSpace(char ch) {
	return ch == ' ' || ch == '\t' || ch == '\0';
}
