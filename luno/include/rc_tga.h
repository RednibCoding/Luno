/*
 * TGA File Handling Library
 * by Michael Binder (RednibCoding)
 *
 * This library provides functionality to load and save TGA (Targa) image files, including support for uncompressed
 * and RLE-compressed true-color (32-bit RGBA) images. The library is simple and self-contained, designed for
 * easy integration into projects requiring TGA image manipulation.
 *
 * Key Features:
 * - TGA Loading from Memory and Files:
 *   - rc_load_tga_mem: Loads a TGA image directly from a memory buffer.
 *   - rc_load_tga: Loads a TGA image from a file on disk.
 *
 * - TGA Writing to Memory and Files:
 *   - rc_write_tga_mem: Converts raw pixel data to a TGA format and stores it in a memory buffer.
 *   - rc_write_tga: Saves raw pixel data as a TGA file to disk.
 *
 *
 * Usage:
 * This library can be used in projects that need to handle TGA files for image loading or manipulation,
 * particularly in contexts such as game development or graphics tools.
 *
 * Define RC_TGA_IMPL before including rc_tga.h in *one* c-file to create the implementations. All other files can just include rc_tga.h.
 *
 * LICENSE: public domain ⁠— no warranty implied; use at your own risk.
 */

#ifndef _RC_TGA_H_
#define _RC_TGA_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    unsigned char *rc_load_tga_mem(unsigned char *data, size_t size, int *width, int *height);
    unsigned char *rc_load_tga(const char *filename, int *width, int *height);
    int rc_write_tga_mem(const unsigned char *pixels, int width, int height, unsigned char **out_data, size_t *out_size);
    int rc_write_tga(const char *filename, const unsigned char *pixels, int width, int height);
    bool rc_write_tga_as_c_array(const char *filename, const char *output_filename, const char *array_name);

#ifdef __cplusplus
}
#endif

#endif // _RC_TGA_H_

#ifdef RC_TGA_IMPL

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* Function to convert a string to uppercase and return a new heap-allocated string */
    static unsigned char *to_uppercase(const char *str)
    {
        size_t length = strlen(str);
        unsigned char *uppercase_str = malloc(length + 1);
        if (!uppercase_str)
        {
            fprintf(stderr, "Memory allocation failed for uppercase string\n");
            return NULL;
        }

        for (size_t i = 0; i < length; i++)
        {
            uppercase_str[i] = toupper((unsigned char)str[i]);
        }
        uppercase_str[length] = '\0';

        return uppercase_str;
    }

    unsigned char *rc_load_tga_mem(unsigned char *data, size_t size, int *width, int *height)
    {
        if (size < 18)
        {
            fprintf(stderr, "Invalid TGA data: insufficient size\n");
            return NULL;
        }

        // Read the TGA header
        unsigned char *header = data;

        // Verify image type (uncompressed or RLE compressed true-color)
        if (header[2] != 2 && header[2] != 10)
        {
            fprintf(stderr, "Unsupported TGA image type (only uncompressed or RLE true-color supported)\n");
            return NULL;
        }

        // Extract image dimensions and pixel depth
        *width = header[12] | (header[13] << 8);
        *height = header[14] | (header[15] << 8);
        int pixel_depth = header[16];

        if (pixel_depth != 32)
        {
            fprintf(stderr, "Unsupported TGA pixel depth (only 32-bit supported)\n");
            return NULL;
        }

        const unsigned char *pixel_data = data + 18;
        size_t data_size = size - 18;

        unsigned char *pixels = malloc((*width) * (*height) * 4);
        if (!pixels)
        {
            fprintf(stderr, "Memory allocation failed for pixel data\n");
            return NULL;
        }

        if (header[2] == 2)
        {
            // Uncompressed TGA
            if (data_size < (*width) * (*height) * 4)
            {
                fprintf(stderr, "Insufficient pixel data for uncompressed TGA\n");
                free(pixels);
                return NULL;
            }
            memcpy(pixels, pixel_data, (*width) * (*height) * 4);
        }
        else if (header[2] == 10)
        {
            // RLE-compressed TGA
            const unsigned char *ptr = pixel_data;
            unsigned char *out_ptr = pixels;
            int pixel_count = (*width) * (*height);

            while (pixel_count > 0 && ptr < data + size)
            {
                unsigned char packet_header = *ptr++;
                int packet_size = (packet_header & 0x7F) + 1;

                if (packet_header & 0x80)
                {
                    // RLE packet
                    if (ptr + 4 > data + size)
                    {
                        fprintf(stderr, "Insufficient RLE pixel data\n");
                        free(pixels);
                        return NULL;
                    }
                    for (int i = 0; i < packet_size; i++)
                    {
                        if (pixel_count <= 0)
                            break;
                        memcpy(out_ptr, ptr, 4);
                        out_ptr += 4;
                        pixel_count--;
                    }
                    ptr += 4;
                }
                else
                {
                    // Raw packet
                    int raw_size = packet_size * 4;
                    if (ptr + raw_size > data + size)
                    {
                        fprintf(stderr, "Insufficient raw pixel data\n");
                        free(pixels);
                        return NULL;
                    }
                    memcpy(out_ptr, ptr, raw_size);
                    out_ptr += raw_size;
                    ptr += raw_size;
                    pixel_count -= packet_size;
                }
            }

            if (pixel_count > 0)
            {
                fprintf(stderr, "Not enough pixel data for RLE-compressed TGA\n");
                free(pixels);
                return NULL;
            }
        }

        return pixels;
    }

    unsigned char *rc_load_tga(const char *filename, int *width, int *height)
    {
        FILE *file = fopen(filename, "rb");
        if (!file)
        {
            perror("Failed to open TGA file");
            return NULL;
        }

        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        if (file_size <= 0)
        {
            fprintf(stderr, "Invalid TGA file size\n");
            fclose(file);
            return NULL;
        }

        unsigned char *data = malloc(file_size);
        if (!data)
        {
            fprintf(stderr, "Memory allocation failed for file data\n");
            fclose(file);
            return NULL;
        }

        if (fread(data, 1, file_size, file) != (size_t)file_size)
        {
            fprintf(stderr, "Failed to read TGA file\n");
            free(data);
            fclose(file);
            return NULL;
        }

        fclose(file);

        unsigned char *pixels = rc_load_tga_mem(data, file_size, width, height);
        free(data);
        return pixels;
    }

    int rc_write_tga_mem(const unsigned char *pixels, int width, int height, unsigned char **out_data, size_t *out_size)
    {
        size_t header_size = 18;
        size_t pixel_data_size = width * height * 4;
        *out_size = header_size + pixel_data_size;

        unsigned char *data = malloc(*out_size);
        if (!data)
        {
            fprintf(stderr, "Memory allocation failed for TGA output buffer\n");
            return -1;
        }

        memset(data, 0, header_size);
        data[2] = 2; // Uncompressed true-color image
        data[12] = width & 0xFF;
        data[13] = (width >> 8) & 0xFF;
        data[14] = height & 0xFF;
        data[15] = (height >> 8) & 0xFF;
        data[16] = 32; // 32 bits per pixel

        memcpy(data + header_size, pixels, pixel_data_size);

        *out_data = data;
        return 0;
    }

    int rc_write_tga(const char *filename, const unsigned char *pixels, int width, int height)
    {
        unsigned char *out_data;
        size_t out_size;

        if (rc_write_tga_mem(pixels, width, height, &out_data, &out_size) != 0)
        {
            return -1;
        }

        FILE *file = fopen(filename, "wb");
        if (!file)
        {
            perror("Failed to open file for writing");
            free(out_data);
            return -1;
        }

        if (fwrite(out_data, 1, out_size, file) != out_size)
        {
            fprintf(stderr, "Failed to write TGA data to file\n");
            fclose(file);
            free(out_data);
            return -1;
        }

        fclose(file);
        free(out_data);
        return 0;
    }

    bool rc_write_tga_as_c_array(const char *filename, const char *output_filename, const char *array_name)
    {
        FILE *input_file = fopen(filename, "rb");
        if (!input_file)
        {
            perror("Failed to open input TGA file");
            return false;
        }

        fseek(input_file, 0, SEEK_END);
        long file_size = ftell(input_file);
        fseek(input_file, 0, SEEK_SET);

        if (file_size <= 0)
        {
            fprintf(stderr, "Invalid TGA file size\n");
            fclose(input_file);
            return false;
        }

        unsigned char *data = malloc(file_size);
        if (!data)
        {
            fprintf(stderr, "Memory allocation failed for input TGA data\n");
            fclose(input_file);
            return false;
        }

        if (fread(data, 1, file_size, input_file) != (size_t)file_size)
        {
            fprintf(stderr, "Failed to read TGA file\n");
            free(data);
            fclose(input_file);
            return false;
        }

        fclose(input_file);

        FILE *output_file = fopen(output_filename, "w");
        if (!output_file)
        {
            perror("Failed to open output header file");
            free(data);
            return false;
        }

        unsigned char *array_name_upper = to_uppercase(array_name);

        fprintf(output_file, "#ifndef _EMBEDDED_%s_H\n", array_name_upper);
        fprintf(output_file, "#define _EMBEDDED_%s_H\n", array_name_upper);
        fprintf(output_file, "//////////////////////////////////////////////////////////////////////////////\n");
        fprintf(output_file, "// Embedded %s\n", filename);
        fprintf(output_file, "//////////////////////////////////////////////////////////////////////////////\n\n");

        fprintf(output_file, "unsigned char %s[] = {\n", array_name);
        for (long i = 0; i < file_size; i++)
        {
            fprintf(output_file, "0x%02X%s", data[i], (i < file_size - 1) ? ", " : "");
            if ((i + 1) % 12 == 0)
            {
                fprintf(output_file, "\n");
            }
        }
        fprintf(output_file, "\n};\n\n");
        fprintf(output_file, "int %sSize = sizeof(%s);\n\n", array_name, array_name);

        fprintf(output_file, "#endif // _EMBEDDED_%s_H_\n", array_name_upper);

        fclose(output_file);
        free(data);
        free(array_name_upper);

        return true;
    }

#ifdef __cplusplus
}
#endif

#endif // RC_TGA_IMPL