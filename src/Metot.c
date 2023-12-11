#include "Metot.h"

Metot MetotOlustur()
{
	Metot this;
	
	this = (Metot)malloc(sizeof(struct METOT));
	
	this->substring=&Substring;
	this->indexOf=&Indexof;
	this->length=&Length;
	this->removespaces=&Removespaces;
	this->toDouble=&ToDouble;
	this->metotYoket=&MetotYoket;
	return this;
}


char* Substring(const Metot this,char *src, int m, int n)
{
    int len = n - m;
 
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
    *dest = '\0';
 
    return dest - len;
}



int Indexof(const Metot this,char *str, char c)
    {
        int i;
        for (i = 0; i < strlen(str); i++)
        {
            if (str[i] == c)
                return i;
        }

        return -1;
    }
	
	
int Length(const Metot this,char s[]) {
   int c = 0;
   while (s[c] != '\0')
      c++;

   return c;
}

void Removespaces(const Metot this,char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}


double ToDouble(const Metot this,char s[])
{
    double val, power;
    int i, sign;
	for (i = 0; isspace(s[i]); i++) 
    ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    return sign * val / power;
}

void MetotYoket(Metot this)
{
	if(this==NULL) return;
	free(this);
}
