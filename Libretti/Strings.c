#include "include/Strings.h"
#include <string.h>
#include <stdlib.h>

lb_String lb_newString(const char* initialString)
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

void lb_appendString(lb_String* string, char symbol)
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
		string->data[string->length + 1] = NULL;
		string->length++;
	}
}

void lb_clearString(lb_String* string)
{
	string->data[0] = NULL;
	string->length = 0;
}

void lb_freeString(lb_String* string)
{
	lb_clearString(string);
	free(string->data);
	string->capacity = 0;
}