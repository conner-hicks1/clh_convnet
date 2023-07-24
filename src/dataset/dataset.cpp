#include "dataset.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

Dataset* create_dataset(const char* file_name, uint32_t image_width, uint32_t image_height, uint8_t ncolor_channels)
{
	Dataset* dataset = (Dataset*)calloc(1, sizeof(Dataset));
	
	dataset->image_width = image_width;
	dataset->image_height = image_height;
	dataset->image_pixel_size = image_width * image_height;
	dataset->ncolor_channels = ncolor_channels;
	dataset->image_byte_size = image_width * image_height * ncolor_channels;
	dataset->channel_size = image_width / ncolor_channels;
	dataset->file_path = file_name;
	
	return dataset;
}

void get_dataset_image_size(Dataset* dataset, uint32_t* image_width, uint32_t* image_height, uint32_t* image_size)
{
	*image_width = dataset->image_width;
	*image_height = dataset->image_height;
	*image_size = dataset->image_size;
}

uint8_t* read_dataset_bytes(Dataset* dataset, uint32_t start, uint32_t end)
{
	uint8_t* dataset_byte_array = (uint8_t*)calloc((end - start + 1), sizeof(uint8_t));
	
	FILE* file = fopen(dataset->file_path, "rb");
	
	if (!file)
	{
		std::cout << "Cannot open file!" << std::endl;
	}
	
	fseek(file, start * sizeof(uint8_t), SEEK_SET);
	fread(dataset_byte_array, (end - start + 1) * sizeof(uint8_t), 1, file);
	
	return dataset_byte_array;
}

uint8_t* get_dataset_texture_array(Dataset* dataset, uint32_t index)
{
	uint32_t start = 2 * (index + 1) + 3072 * index;
	uint32_t end = 2 * (index + 1) + 3072 * (index + 1);
	
	assert(end >= start);
	
	uint8_t* dataset_byte_array = read_dataset_bytes(dataset, start, end);
	uint8_t* dataset_texture_array = (uint8_t*)calloc((end - start), sizeof(uint8_t));
	
	for (uint32_t i = 0; i < dataset->image_byte_size; i++)
	{
		uint32_t j = (dataset->ncolor_channels * (i % dataset->channel_size) + floor(i / dataset->channel_size));
		
		dataset_texture_array[i] = dataset_byte_array[j];
	}
	
	return dataset_texture_array;
}

void destroy_dataset(Dataset* dataset)
{
	free(dataset);
}