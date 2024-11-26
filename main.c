#include "ft_ssl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Define BLOCK_SIZE
#define BLOCK_SIZE 8 // DES block size in bytes

// Define the t_args structure and g_args


args g_args;

// Function prototypes
int parse_des(int argc, char **argv);
void derive_key_from_password();
unsigned char *read_input_data(size_t *data_len);
void write_output_data(unsigned char *data, size_t data_len);
void apply_padding(unsigned char **data, size_t *data_len);
void remove_padding(unsigned char *data, size_t *data_len);
void process_data(unsigned char *data, size_t data_len);
uint8_t *base64_encode(const char *input, uint32_t *len);
uint8_t *base64_decode(const char *input, uint32_t *len);

// The DES function (you should have this implemented)
uint64_t des(uint64_t input, uint64_t key, char mode);

int main(int argc, char **argv) {
    // Initialize g_args to zero
    memset(&g_args, 0, sizeof(args));

    // Parse command-line arguments
    if (parse_des(argc, argv) != 0) {
        return EXIT_FAILURE;
    }

    // Key derivation or validation
    if (!g_args.flag_k) {
        if (g_args.flag_p && g_args.flag_s) {
            derive_key_from_password();
        } else {
            fprintf(stderr, "Error: Key must be provided using -k flag or password and salt must be provided\n");
            return EXIT_FAILURE;
        }
    }

    // Read input data
    size_t data_len;
    unsigned char *data = read_input_data(&data_len);

    // Base64 decoding before decryption
    if (g_args.flag_d && g_args.flag_a) {
        uint32_t decoded_len = (uint32_t)data_len;
        uint8_t *decoded_data = base64_decode((const char *)data, &decoded_len);

        free(data);
        data = decoded_data;
        data_len = decoded_len;
    }

    // For encryption, apply padding
    if (g_args.flag_e) {
        apply_padding(&data, &data_len);
    } else {
        // For decryption, data_len should be a multiple of BLOCK_SIZE
        if (data_len % BLOCK_SIZE != 0) {
            fprintf(stderr, "Error: Data length is not a multiple of block size\n");
            return EXIT_FAILURE;
        }
    }

    // Process data
    process_data(data, data_len);

    // For decryption, remove padding
    if (g_args.flag_d) {
        remove_padding(data, &data_len);
    }

    // Base64 encoding after encryption
    if (g_args.flag_e && g_args.flag_a) {
        uint32_t encoded_len = (uint32_t)data_len;
        uint8_t *encoded_data = base64_encode((const char *)data, &encoded_len);

        free(data);
        data = encoded_data;
        data_len = encoded_len;
    }

    // Write output data
    write_output_data(data, data_len);

    // Clean up
    free(data);

    return EXIT_SUCCESS;
}

// Implement the missing functions below

#include <ctype.h> // For isprint in padding functions

// Parsing function
int parse_des(int argc, char **argv) {
    int i = 1;
    g_args.flag_e = 1;

    while (++i < argc) {
        if (argv[i][0] != '-') {
            printf("ft_ssl: Error: '%s', you must provide a file to indicate a non-flag parameter.\n", argv[i]);
            return (1);
        }

        if (strcmp(argv[i], "-a") == 0) {
            g_args.flag_a = 1;
        }
        else if (strcmp(argv[i], "-d") == 0) {
            g_args.flag_d = 1; g_args.flag_e = 0;
        }
        else if (strcmp(argv[i], "-e") == 0) {
            g_args.flag_e = 1; g_args.flag_d = 0;
        }
        else if (strcmp(argv[i], "-i") == 0) {
            g_args.flag_i = 1;
            if (i + 1 >= argc) {
                printf("ft_ssl: Error: -i flag requires an argument.\n");
                return (1);
            }
            if (g_args.nb_files > 1023) {
                printf("ft_ssl: Error: too many files.\n");
                return (1);
            }
            g_args.files[g_args.nb_files] = argv[i + 1];
            g_args.nb_files++;
            i++;
        }
        else if (strcmp(argv[i], "-k") == 0) {
            g_args.flag_k = 1;
            if (i + 1 >= argc) {
                printf("ft_ssl: Error: -k flag requires an argument.\n");
                return (1);
            }
            g_args.key = strtoull(argv[i + 1], NULL, 16);
            i++;
        }
        else if (strcmp(argv[i], "-o") == 0) {
            g_args.flag_o = 1;
            if (i + 1 >= argc) {
                printf("ft_ssl: Error: -o flag requires an argument.\n");
                return (1);
            }
            g_args.file_o = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-p") == 0) {
            g_args.flag_p = 1;
            if (i + 1 >= argc) {
                printf("ft_ssl: Error: -p flag requires an argument.\n");
                return (1);
            }
            g_args.password = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-s") == 0) {
            g_args.flag_s = 1;
            if (i + 1 >= argc) {
                printf("ft_ssl: Error: -s flag requires an argument.\n");
                return (1);
            }
            g_args.salt = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-v") == 0) {
            g_args.flag_v = 1;
            if (i + 1 >= argc) {
                printf("ft_ssl: Error: -v flag requires an argument.\n");
                return (1);
            }
            g_args.iv = strtoull(argv[i + 1], NULL, 16);
            i++;
        }
        else {
            printf("ft_ssl: Error: '%s', invalid option.\n", argv[i]);
            return (1);
        }
    }

    return (0);
}

// Key derivation function (simple example)
void derive_key_from_password() {
    // Simple key derivation: concatenate password and salt, hash, take first 8 bytes
    // For illustration purposes only. Use a proper KDF in production code.

    unsigned char combined[256];
    size_t combined_len = strlen(g_args.password) + strlen(g_args.salt);

    if (combined_len > 255) {
        fprintf(stderr, "Error: Password and salt too long\n");
        exit(EXIT_FAILURE);
    }

    strcpy((char *)combined, g_args.password);
    strcat((char *)combined, g_args.salt);

    // Simple hash: sum of bytes modulo 256
    uint8_t hash = 0;
    for (size_t i = 0; i < combined_len; i++) {
        hash = (hash + combined[i]) % 256;
    }

    // Use hash to generate key
    g_args.key = 0;
    for (int i = 0; i < 8; i++) {
        g_args.key = (g_args.key << 8) | hash;
    }
}

// Read input data
unsigned char *read_input_data(size_t *data_len) {
    FILE *input_file = stdin;
    if (g_args.flag_i) {
        input_file = fopen(g_args.files[0], "rb");
        if (!input_file) {
            fprintf(stderr, "Error: Unable to open input file %s\n", g_args.files[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Read the file into memory
    unsigned char *data = NULL;
    size_t buffer_size = 1024;
    size_t total_read = 0;

    data = malloc(buffer_size);
    if (!data) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    size_t bytes_read;
    while ((bytes_read = fread(data + total_read, 1, buffer_size - total_read, input_file)) > 0) {
        total_read += bytes_read;
        if (total_read == buffer_size) {
            buffer_size *= 2;
            unsigned char *new_data = realloc(data, buffer_size);
            if (!new_data) {
                fprintf(stderr, "Error: Memory allocation failed\n");
                free(data);
                exit(EXIT_FAILURE);
            }
            data = new_data;
        }
    }

    if (ferror(input_file)) {
        fprintf(stderr, "Error: Reading input failed\n");
        free(data);
        exit(EXIT_FAILURE);
    }

    if (g_args.flag_i) {
        fclose(input_file);
    }

    *data_len = total_read;
    return data;
}

// Write output data
void write_output_data(unsigned char *data, size_t data_len) {
    FILE *output_file = stdout;
    if (g_args.flag_o) {
        output_file = fopen(g_args.file_o, "wb");
        if (!output_file) {
            fprintf(stderr, "Error: Unable to open output file %s\n", g_args.file_o);
            exit(EXIT_FAILURE);
        }
    }

    size_t bytes_written = fwrite(data, 1, data_len, output_file);
    if (bytes_written != data_len) {
        fprintf(stderr, "Error: Writing output failed\n");
        exit(EXIT_FAILURE);
    }

    if (g_args.flag_o) {
        fclose(output_file);
    }
}

// Apply PKCS#7 padding
void apply_padding(unsigned char **data, size_t *data_len) {
    size_t padding_len = BLOCK_SIZE - (*data_len % BLOCK_SIZE);
    unsigned char padding_byte = (unsigned char)padding_len;

    // Allocate more space
    unsigned char *new_data = realloc(*data, *data_len + padding_len);
    if (!new_data) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    *data = new_data;

    // Append padding bytes
    for (size_t i = 0; i < padding_len; i++) {
        (*data)[*data_len + i] = padding_byte;
    }

    *data_len += padding_len;
}

// Remove PKCS#7 padding
void remove_padding(unsigned char *data, size_t *data_len) {
    if (*data_len == 0) {
        fprintf(stderr, "Error: Data length is zero\n");
        exit(EXIT_FAILURE);
    }

    unsigned char padding_len = data[*data_len - 1];
    if (padding_len > BLOCK_SIZE || padding_len == 0) {
        fprintf(stderr, "Error: Invalid padding\n");
        exit(EXIT_FAILURE);
    }

    // Verify padding
    for (size_t i = 0; i < padding_len; i++) {
        if (data[*data_len - 1 - i] != padding_len) {
            fprintf(stderr, "Error: Invalid padding\n");
            exit(EXIT_FAILURE);
        }
    }

    *data_len -= padding_len;
}

// Process data block by block
void process_data(unsigned char *data, size_t data_len) {
    uint64_t key = g_args.key;
    char mode = g_args.flag_d ? 'd' : 'e';

    // For each block
    for (size_t i = 0; i < data_len; i += BLOCK_SIZE) {
        // Read 8 bytes into a 64-bit block
        uint64_t block = 0;
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block <<= 8;
            block |= data[i + j];
        }

        // Encrypt/Decrypt
        uint64_t processed_block = des(block, key, mode);

        // Write back to data
        for (int j = BLOCK_SIZE - 1; j >= 0; j--) {
            data[i + j] = (unsigned char)(processed_block & 0xFF);
            processed_block >>= 8;
        }
    }
}

// Base64 encoding and decoding functions (simplified examples)

// Base64 encode
uint8_t *base64_encode(const char *input, uint32_t *len) {
    // Implement your Base64 encoding here or use your existing implementation
    // Placeholder for demonstration
    fprintf(stderr, "Base64 encoding not implemented.\n");
    exit(EXIT_FAILURE);
}

// Base64 decode
uint8_t *base64_decode(const char *input, uint32_t *len) {
    // Implement your Base64 decoding here or use your existing implementation
    // Placeholder for demonstration
    fprintf(stderr, "Base64 decoding not implemented.\n");
    exit(EXIT_FAILURE);
}

