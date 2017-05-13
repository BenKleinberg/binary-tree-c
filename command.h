//Author: Benjamin Kleinberg

#ifndef COMMAND_H_
#define COMMAND_H_

/**
 * A simple class to interpret commands from c-strings.
 * Has a one character flag to identify the command read, and an
 * array of integer arguments.
 */
class Command {
public:
	static const int MAX_ARGUMENTS = 2;

	char flag;
	int num;
	int arguments[MAX_ARGUMENTS];

	Command();

	void initialize();
	int readCommand(const char* text);

private:
	int readFlag(const char* &text);
	int readArgument(const char* &text);
};

const char* stripWhiteSpace(const char* text);
int isWhiteSpace(char ch);


#endif
