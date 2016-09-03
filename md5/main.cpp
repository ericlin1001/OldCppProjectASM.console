#include<stdio.h>
#include<cstring>
#include "global.h"

#include "md5.h"
#define MD_CTX MD5_CTX
#define MDInit MD5Init
#define MDUpdate MD5Update
#define MDFinal MD5Final

static void MDString (char *string)
{
	MD5_CTX context;
	unsigned char digest[16];
	unsigned int len = strlen (string);
	
	MDInit (&context);
	MDUpdate (&context, string, len);
	MDFinal (digest, &context);
	
	printf ("MD%d (\"%s\") = ", MD, string);
	MDPrint (digest);
	printf ("\n");
	
}
static char* MDStr (char *string,char *str){
	MD5_CTX context;
	unsigned char digest[16];
	unsigned short i;
	 char temp[10];
	unsigned int len = strlen (string);
	
	MDInit (&context);
	MDUpdate (&context, string, len);
	MDFinal (digest, &context);;
	
	str[0]=0;
	for (i = 0; i < 16; i++){
		sprintf (temp,"%02x", digest[i]);
		strcat(str,temp);
	}/**/
return str;
}
static char* MDStr20 (char *string,char *str){
	MD5_CTX context;
	unsigned char digest[16];
	unsigned short i;
	 char temp[10];
	unsigned int len = strlen (string);
	
	MDInit (&context);
	MDUpdate (&context, string, len);
	MDFinal (digest, &context);;
	
	str[0]=0;
	for (i = 0; i < 10; i++){
		sprintf (temp,"%02x", digest[i]);
		strcat(str,temp);
	}/**/
return str;
}
/* Prints a message digest in hexadecimal.
*/
static void MDPrint (digest)
unsigned char digest[16];
{
	unsigned int i;
	
	for (i = 0; i < 16; i++)
		printf ("%02x", digest[i]);
}

bool mynewcmp(char *string,char *tdigest){
	MD5_CTX context;
	unsigned char digest[16];
	MDInit (&context);
	MDUpdate (&context, string, strlen (string));
	MDFinal (digest, &context);;
	return (strncmp(tdigest,digest,10)==0);
}
void getHex(char *orign,char *hex){
	unsigned int i;
	for (i = 0; i < 10; i++)
	sscanf(orign+i*2,"%02x",&hex[i]);
}
/**/int main(){

	return 0;
}