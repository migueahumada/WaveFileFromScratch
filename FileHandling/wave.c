//
//  wave.c
//  FileHandling
//
//  Created by Miguel Angel Ahumada Gaona on 30/10/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include "wave.h"

#define TWO_PI (2 * M_PI)
#define ERROR_RESULT 0

//This funcions reads binary data and count the samples in an audio file
int readBinaryData(const char* path)
{
    FILE* file;
    short* audioblock;
    int blockSize = 1024;
    int samples = 0;
    
    //Read a file
    file = fopen(path, "rb");
    if (file == NULL) {
        fclose(file);
        return ERROR_RESULT;
    }
    
    //Allocate some memory for the buffer called audioblock.
    audioblock = (short*)malloc(sizeof(short)*blockSize);
    if (audioblock == NULL) {
        puts("No memory to allocate\n");
        free(audioblock);
        fclose(file);
        return ERROR_RESULT;
    }
    
    //Main loop where samples are added each loop iteration.
    //The audio block is being filled over and over
    while (!feof(file)) {
        samples += fread(audioblock, sizeof(short), blockSize, file);
        //printf("Samples read in the audio file -> %d\n",samples);
    }
    
    printf("Samples read in the audio file -> %d\n",samples);
    
    free(audioblock);
    fclose(file);
    
    return 1;
}

void updateHeader(WaveHeader* waveHeader, int sampleRate, int numChannels, int precision, int databytes)
{
    /*RIFF CHUNK*/
    memcpy(waveHeader->chunkID, RIFF_ID, sizeof(RIFF_ID));
    waveHeader->chunkSize = databytes + sizeof(WaveHeader) - 8; // Correct total size
    memcpy(waveHeader->format, WAVE_ID, sizeof(WAVE_ID));
    
    /*FMT SUBCHUNK*/
    memcpy(waveHeader->subchunkID, FMT_ID, sizeof(FMT_ID));
    waveHeader->subchunkSize = 16; // PCM format size
    waveHeader->audioFormat = 1;    // PCM format
    waveHeader->numChannels = (short)numChannels; // Mono/Stereo
    waveHeader->sampleRate = sampleRate; // Sample rate
    waveHeader->byteRate = sampleRate * numChannels * (precision / 8); // Byte rate
    waveHeader->blockAlign = (short)(numChannels * (precision / 8)); // Block align
    waveHeader->bitsPerSample = (short)precision; // Bits per sample
    
    /*DATA SUBCHUNK*/
    memcpy(waveHeader->subchunkID2, DATA_ID, sizeof(DATA_ID));
    waveHeader->datasize = databytes; // Size of the data
}

int outputWaveFile(const char* path)
{
    FILE* file;
    short* audioblock;
    int numSamples, i, j;
    int sampleRate = 48000;
    int blockframes = 256;
    int databytes;
    unsigned int index = 0;
    float duration = 1.0f;
    float frequency = 700.0f;
    WaveHeader* waveHeader;
    numSamples = (int)(duration*sampleRate);
    
    //Creates a write binary file
    file = fopen(path, "wb");
    if (file == NULL) {
        fclose(file);
        return ERROR_RESULT;
    }
    
    //Allocates memory for the audioblock that will be changing during the program
    audioblock = (short *) malloc(sizeof(short)*blockframes);
    if (audioblock == NULL) {
        free(audioblock);
        fclose(file);
        return ERROR_RESULT;
    }
    
    waveHeader = (WaveHeader *) malloc(sizeof(WaveHeader));
    if (waveHeader == NULL) {
        free(audioblock);
        free(waveHeader);
        fclose(file);
        return ERROR_RESULT;
    }
    
    databytes = numSamples * sizeof(short);
    
    updateHeader(waveHeader, sampleRate, 1, 16, databytes);
    fwrite(waveHeader, 1, sizeof(WaveHeader), file);
    
    for(i=0; i < numSamples; i+=blockframes){
        for(j=0; j < blockframes; j++, index++){
           audioblock[j] = 16000*sin(index*TWO_PI*frequency/sampleRate);
        }
        fwrite(audioblock,sizeof(short), blockframes, file);
    }
    
    free(audioblock);
    free(waveHeader);
    fclose(file);
    
    return 1;
}


