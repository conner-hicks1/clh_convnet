#pragma once
#include <stdint.h>

class Dataset
{
public:
	uint32_t image_width;
	uint32_t image_height;
	uint32_t image_pixel_size;
	uint8_t ncolor_channels;
	uint32_t image_byte_size;
	uint32_t channel_size;
	const char* file_path;
};

Dataset* create_dataset(const char* file_name, uint32_t image_width, uint32_t image_height, uint8_t ncolor_channels);

void get_dataset_image_size(Dataset* dataset, uint32_t* image_width, uint32_t* image_height, uint32_t* image_size);

// Exclusive
uint8_t* read_dataset_bytes(Dataset* dataset, uint32_t start, uint32_t end);

uint8_t* get_dataset_texture_array(Dataset* dataset, uint32_t index);

void destroy_dataset(Dataset* dataset);