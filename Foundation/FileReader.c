#include "FileReader.h"

FileReader* openReader(const char* filePath)
{
	FILE* file = fopen(filePath, "r");
	if (!file)
	{
		return NULL;
	}
	
	FileReader* reader = malloc(sizeof(FileReader));
	reader->file = file;
	reader->lineSize = 2048;
	reader->line = malloc(sizeof(char) * reader->lineSize);
	
	return reader;
}

void closeReader(FileReader* reader)
{
	if (!reader)
	{
		return;
	}
	
	if (reader->line)
	{
		free(reader->line);
	}
	
	if (reader->file)
	{
		fclose(reader->file);
	}
	
	free(reader);
}

simd_quatf readQuaternion(FileReader* reader)
{
	getline(&reader->line, &reader->lineSize, reader->file);
	const float x = strtof(reader->line, NULL);
	
	getline(&reader->line, &reader->lineSize, reader->file);
	const float y = strtof(reader->line, NULL);
	
	getline(&reader->line, &reader->lineSize, reader->file);
	const float z = strtof(reader->line, NULL);
	
	getline(&reader->line, &reader->lineSize, reader->file);
	const float w = strtof(reader->line, NULL);
	
	return simd_quaternion(x, y, z, w);
}

simd_float3 readVector3(FileReader* reader)
{
	getline(&reader->line, &reader->lineSize, reader->file);
	const float x = strtof(reader->line, NULL);
	
	getline(&reader->line, &reader->lineSize, reader->file);
	const float y = strtof(reader->line, NULL);
	
	getline(&reader->line, &reader->lineSize, reader->file);
	const float z = strtof(reader->line, NULL);
	
	return simd_make_float3(x, y, z);
}

simd_float2 readVector2(FileReader* reader)
{
	getline(&reader->line, &reader->lineSize, reader->file);
	const float x = strtof(reader->line, NULL);
	
	getline(&reader->line, &reader->lineSize, reader->file);
	const float y = strtof(reader->line, NULL);
	
	return simd_make_float2(x, y);
}

int readInt(FileReader* reader)
{
	getline(&reader->line, &reader->lineSize, reader->file);
	return (int)strtol(reader->line, NULL, 10);
}

unsigned int readUInt(FileReader* reader)
{
	getline(&reader->line, &reader->lineSize, reader->file);
	return (unsigned int)strtol(reader->line, NULL, 10);
}

float readFloat(FileReader* reader)
{
	getline(&reader->line, &reader->lineSize, reader->file);
	return strtof(reader->line, NULL);
}

char* readLine(FileReader* reader)
{
	size_t lineSize = 0;
	char* line = NULL;
	getline(&line, &lineSize, reader->file);
	return line;
}

void skipLine(FileReader* reader)
{
	getline(&reader->line, &reader->lineSize, reader->file);
}
