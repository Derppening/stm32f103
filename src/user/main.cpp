#include "main.h"

int main()
{
	COM1.init(9600);
	while (1)
	{
		COM1.tx("Hello!\n\r");
	}
}
