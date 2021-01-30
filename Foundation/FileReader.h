#ifndef FileReader_h
#define FileReader_h

#include <stdio.h>
#include <stdlib.h>
#include <simd/simd.h>

typedef struct FileReader
{
	FILE* file;
	char* line;
	size_t lineSize;
}
FileReader;

FileReader* openReader(const char* filePath);

void closeReader(FileReader* reader);

simd_quatf readQuaternion(FileReader* reader);

simd_float3 readVector3(FileReader* reader);

simd_float2 readVector2(FileReader* reader);

int readInt(FileReader* reader);

unsigned int readUInt(FileReader* reader);

float readFloat(FileReader* reader);

char* readLine(FileReader* reader);

void skipLine(FileReader* reader);

#endif /* FileReader_h */
