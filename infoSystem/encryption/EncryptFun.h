#ifndef EncryptFun_h
#define EncryptFun_h
bool filecmp(const char  *fileName1,const char  *fileName2);
bool encryptFile(const char  *srcfile,const char  *destfile);
bool decryptFile(const char  *srcfile,const char  *destfile);
bool decryptFile(const char  *srcfile,const char  *destfile,const char *key,int keysize);
bool encryptFile(const char  *srcfile,const char  *destfile,const char *key,int keysize);
bool setTag(const char *fileName,const char *tagStr,int tagsize);
bool testTag(const char *fileName,const char *tagStr,int tagsize);
bool removeTag(const char *fileName,const char *tagStr,int tagsize);
//

//
#endif