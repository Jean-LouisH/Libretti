#include "include/Strings.h"
#include <stdlib.h>

lb_String newString(int capacity)
{
	lb_String string;
	string.data = calloc(capacity, sizeof(char));
	string.length = 0;
	string.capacity = capacity;
	return string;
}

void append(lb_String* string, char symbol)
{
	if (string->length >= string->capacity)
	{
		int newCapacity = string->capacity * 2;
		string->data = realloc(string->data, newCapacity * sizeof(char));
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