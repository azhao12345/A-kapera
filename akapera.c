#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//typedef struct sample
//{
//    char low;
//    char high;
//} sample;

typedef struct stereo_sample
{
    int16_t left;
    int16_t right;
} stereo_sample;


unsigned int alignmentValue(stereo_sample *first, stereo_sample *second, unsigned int length);
unsigned int difference(int16_t first, int16_t second);


int main()
{
    FILE *vocal = fopen("./vocal.raw", "r");
    FILE *inst = fopen("./inst.raw", "r");
    
    //use a 100 MB buffer for now
    size_t buffer_size = 100 * 1000000;
    stereo_sample *buffer = (stereo_sample *)malloc(buffer_size);
    //read the data into the buffer, then copy it into a properly sized array for the data
    size_t vocal_size = fread(buffer, sizeof(stereo_sample), buffer_size, vocal);
    stereo_sample *vocal_data = (stereo_sample *)malloc(vocal_size);
    memcpy(vocal_data, buffer, vocal_size);

    size_t inst_size = fread(buffer, sizeof(stereo_sample), buffer_size, inst);
    stereo_sample *inst_data = (stereo_sample *)malloc(inst_size);
    memcpy(inst_data, buffer, inst_size);

    //free the buffer since we don't need it anymore
    //free(buffer);
    printf("%d\n", (int)vocal_size);
    printf("%d\n", (int)inst_size);
//    printf("%d\n", alignmentValue(vocal_data, inst_data, 2000000));
//    printf("%d\n", alignmentValue(vocal_data, inst_data, 1000000));
    //now we will do the alignment
    printf("limit: %d\n",  vocal_size / 500);
    unsigned int alignmentIndex;
    unsigned int minAlignment = alignmentValue(vocal_data, inst_data, vocal_size / 100);
    for(unsigned int i = 0; i < vocal_size / 500; i++)
    {
        //printf("%d\n", alignmentValue(vocal_data + i, inst_data, vocal_size / 10));
        if(i%1000==0)
        {
            printf("%d\n", i);
            printf("%d\n", alignmentValue(vocal_data+i, inst_data, vocal_size / 100));
        }
        unsigned int val = alignmentValue(vocal_data + i, inst_data, vocal_size / 100);
        if(val < minAlignment)
        {
            minAlignment = val;
            alignmentIndex = i;
            printf("current val: %d\n", val);
        }
    }

    int numSamples;
    if(vocal_size - alignmentIndex < inst_size)
    {
        numSamples = vocal_size - alignmentIndex;
    }
    else
    {
        numSamples = inst_size;
    }
    printf("%d\n", numSamples);


    for(unsigned int i = 0; i < numSamples; i++)
    {
        buffer[i].left = vocal_data[i + alignmentIndex].left - inst_data[i].left;
        buffer[i].right = vocal_data[i + alignmentIndex].right - inst_data[i].right;
    }
    
    FILE *out = fopen("./out.raw", "w");
    fwrite(buffer, sizeof(stereo_sample), numSamples, out);

    printf("finished\n");
    return 0;
}

unsigned int alignmentValue(stereo_sample *first, stereo_sample *second, unsigned int length)
{
    unsigned int diffsum = 0;
    for(unsigned int i = 0; i < length; i++)
    {
        diffsum += difference(first[i].left, second[i].left);
        diffsum += difference(first[i].right, second[i].right);
    }
    return diffsum;
}

//returns the absolute value of the difference of the samples with a bit shift
unsigned int difference(int16_t first, int16_t second)
{
    return ((unsigned int)abs(first - second)) >> 5;
}


