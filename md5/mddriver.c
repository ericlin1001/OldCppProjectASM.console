/* MDDRIVER.C - test driver for MD2, MD4 and MD5
*/

/* Copyright (C) 1990-2, RSA Data Security, Inc. Created 1990. All
rights reserved.

  RSA Data Security, Inc. makes no representations concerning either
  the merchantability of this software or the suitability of this
  software for any particular purpose. It is provided "as is"
  without express or implied warranty of any kind.
  
	These notices must be retained in any copies of any part of this
	documentation and/or software.
*/

/* The following makes MD default to MD5 if it has not already been
defined with C compiler flags.
*/
#ifndef MD
#define MD 5
#endif

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "global.h"
#if MD == 2
#include "md2.h"
#endif
#if MD == 4



#include "md4.h"
#endif
#if MD == 5
#include "md5.h"
#endif


/* Length of test block, number of test blocks.
*/
#define TEST_BLOCK_LEN 1000
#define TEST_BLOCK_COUNT 1000

static void MDString PROTO_LIST ((char *));
static void MDTimeTrial PROTO_LIST ((void));
static void MDTestSuite PROTO_LIST ((void));
static void MDFile PROTO_LIST ((char *));
static void MDFilter PROTO_LIST ((void));
static void MDPrint PROTO_LIST ((unsigned char [16]));

#if MD == 2
#define MD_CTX MD2_CTX
#define MDInit MD2Init
#define MDUpdate MD2Update
#define MDFinal MD2Final
#endif
#if MD == 4
#define MD_CTX MD4_CTX
#define MDInit MD4Init
#define MDUpdate MD4Update
#define MDFinal MD4Final
#endif
#if MD == 5
#define MD_CTX MD5_CTX
#define MDInit MD5Init
#define MDUpdate MD5Update
#define MDFinal MD5Final
#endif

/* Main driver.

  Arguments (may be any combination):
  -sstring - digests string
  -t       - runs time trial
  -x       - runs test script
  filename - digests file
  (none)   - digests standard input
*/

/* Digests a string and prints the result.
*/
static void MDString (char *string)
{
	MD_CTX context;
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
	MD_CTX context;
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
	MD_CTX context;
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
	MD_CTX context;
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
}/*
int main (int argc, char *argv[])
{
	if(mynewcmp("ad","adfasdfasdfad")){
	}
	char digest[10];char buffer[100];char temp[100];
	getHex("c4ca4238a0b923820dcc",digest);
	MDPrint(digest);
	MDString("1");
	while(1){	scanf("%s",buffer);
	MDStr20(buffer,temp);
	printf("MD5:%s\n",temp);
	}
	
	return (0);
}*/
