#include "dataset.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <errno.h>

Dataset* create_dataset(const char* file_name, uint32_t image_width, uint32_t image_height, uint8_t ncolor_channels)
{
	Dataset* dataset = (Dataset*)calloc(1, sizeof(Dataset));
	
	dataset->image_width = image_width;
	dataset->image_height = image_height;
	dataset->image_pixel_size = image_width * image_height;
	dataset->ncolor_channels = ncolor_channels;
	dataset->image_byte_size = image_width * image_height * ncolor_channels;
	dataset->channel_size = image_width * image_height;
	dataset->file_path = file_name;
	
	return dataset;
}

void get_dataset_image_size(Dataset* dataset, uint32_t* image_width, uint32_t* image_height, uint32_t* image_pixel_size)
{
	*image_width = dataset->image_width;
	*image_height = dataset->image_height;
	*image_pixel_size = dataset->image_pixel_size;
}

uint8_t* read_dataset_bytes(Dataset* dataset, uint32_t start, uint32_t end)
{
	uint8_t* dataset_byte_array = (uint8_t*)calloc((end - start), sizeof(uint8_t));
	
	FILE* file = fopen(dataset->file_path, "rb");
	
	if (!file)
	{
		std::cout << "Cannot open file!" << std::endl;
		std::cout << "Error: " << errno << std::endl;
	}
	
	fseek(file, start * sizeof(uint8_t), SEEK_SET);
	fread(dataset_byte_array, (end - start) * sizeof(uint8_t), 1, file);
	
	fclose(file);
	
	return dataset_byte_array;
}

uint8_t* get_dataset_texture_array(Dataset* dataset, uint32_t index)
{
	uint32_t start = 2 * (index + 1) + dataset->image_byte_size * index;
	
	assert(dataset->image_byte_size != 0);
	
	uint8_t* dataset_byte_array = read_dataset_bytes(dataset, start, start + dataset->image_byte_size);
	uint8_t* dataset_texture_array = (uint8_t*)calloc((dataset->image_byte_size), sizeof(uint8_t));
	
	for (uint32_t red_byte_pointer = 0; red_byte_pointer < dataset->channel_size; red_byte_pointer++)
	{
		dataset_texture_array[red_byte_pointer * 3] = dataset_byte_array[red_byte_pointer];
	}
	
	for (uint32_t green_byte_pointer = 0; green_byte_pointer < dataset->channel_size; green_byte_pointer++)
	{
		dataset_texture_array[green_byte_pointer * 3 + 1] = dataset_byte_array[green_byte_pointer + dataset->channel_size];
	}
	
	for (uint32_t blue_byte_pointer = 0; blue_byte_pointer < dataset->channel_size; blue_byte_pointer++)
	{
		dataset_texture_array[blue_byte_pointer * 3 + 2] = dataset_byte_array[blue_byte_pointer + dataset->channel_size * 2];
	}
	
	return dataset_texture_array;
}

void destroy_dataset(Dataset* dataset)
{
	free(dataset);
}