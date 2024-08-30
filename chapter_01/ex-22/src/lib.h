#include <stdbool.h>

int read_line(char buffer[], int size);
int string_length(char buffer[]);

bool space(char c);
bool tab(char c);
bool blank(char c);
bool blank_sequence(char prev, char cur);

void fold(char from[], char to[], int max_line_length);

void debug(char buffer[]);
