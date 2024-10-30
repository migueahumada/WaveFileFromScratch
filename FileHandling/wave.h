//
//  wave.h
//  FileHandling
//
//  Created by Miguel Angel Ahumada Gaona on 30/10/24.
//

#ifndef wave_h
#define wave_h

#define HEADER_IDS_ARRAY_SIZE 4 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <math.h>


static char RIFF_ID[HEADER_IDS_ARRAY_SIZE] = {'R','I','F','F'};
static char WAVE_ID[HEADER_IDS_ARRAY_SIZE] = {'W','A','V','E'};
static char FMT_ID[HEADER_IDS_ARRAY_SIZE] = {'f','m','t',' '};
static char DATA_ID[HEADER_IDS_ARRAY_SIZE] = {'d','a','t','a'};

typedef struct WaveHeader
{
    //RIFF CHUNK
    char chunkID[HEADER_IDS_ARRAY_SIZE]; //"RIFF"
    int chunkSize; //File size - 8 bytes
    char format[HEADER_IDS_ARRAY_SIZE]; //"WAVE"
    
    //FMT SUBCHUNK
    char subchunkID[HEADER_IDS_ARRAY_SIZE]; // "fmt "
    int subchunkSize; // chunk length
    short audioFormat; // 1 -> for PCM
    short numChannels; // number of channels
    int sampleRate; //sampleing frecuency
    int byteRate; // nBlockAlign * rate
    short blockAlign; // numChannels * size / 8
    short bitsPerSample; //Size of each sample
    
    //DATA SUBCHUNK
    char subchunkID2[HEADER_IDS_ARRAY_SIZE]; //"data"
    int datasize; //sound data size in bytes
    
}WaveHeader;

//This funcions reads binary data and count the samples in an audio file
int readBinaryData(const char* path);

void updateHeader(WaveHeader* waveHeader, int sampleRate, int numChannels, int precision, int databytes);

int outputWaveFile(const char* path);

#endif /* wave_h */
