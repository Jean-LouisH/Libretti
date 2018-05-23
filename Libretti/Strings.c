#include "include/Strings.h"
#include <string.h>
#include <stdlib.h>

lb_String newString(const char* initialString)
{
	lb_String string;
	string.length = strlen(initialString);
	if (string.length < 1)
		string.capacity = 1;
	else
		string.capacity = string.length;
	string.data = calloc(string.capacity, sizeof(char));
	strcpy(string.data, initialString);
	return string;
}

void append(lb_String* string, char symbol)
{
	if (string->length >= string->capacity)
	{
		int newCapacity = string->capacity + 8;
		string->data = realloc(string->data, newCapacity * sizeof(char));
		if (string->data != NULL)
			string->capacity = newCapacity;
	}

	/*in case allocation fails, check again.*/
	if (string->length < string->capacity)
	{
		string->data[string->length] = symbol;
		string->data[string->length + 1] = 0;
		string->length++;
	}
}

void clear(lb_String* string)
{
	string->data[0] = 0;
	string->length = 0;
}

void freeString(lb_String* string)
{
	clear(string);
	free(string->data);
}