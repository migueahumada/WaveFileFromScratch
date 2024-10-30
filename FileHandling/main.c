//
//  main.c
//  FileHandling
//
//  d by Miguel Angel Ahumada Gaona on 25/10/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include "wave.h"

#define MAX_ARRAY_SIZE 50
#define ERROR_RESULT 0

int main(int argc, const char * argv[])
{
    const char* inputPath ="/Volumes/LaCie/Coding/FileHandling/Assets/Audio_Test.wav";
    
    if (readBinaryData(inputPath) != ERROR_RESULT)
        printf("Binary data successfully read!\n");
    
    if (outputWaveFile("/Volumes/LaCie/Coding/FileHandling/Assets/ResultWaveFile.wav")!= ERROR_RESULT) {
        puts("Output wave file generated successfully!\n");
    }
    
    return 0;
}




