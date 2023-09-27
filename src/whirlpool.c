#include "ft_ssl.h"


#define BLOCK_SIZE 64
#define KEY_SIZE 32
#define NUM_ROUNDS 10

typedef struct {
    uint8_t data[BLOCK_SIZE];
} Block;

uint8_t state[8][8];
uint8_t subkeys[NUM_ROUNDS][KEY_SIZE];

void initialize(uint8_t *key, size_t key_size) {
    ft_memset(state, 0, sizeof(state));
    for (int i = 0; i < NUM_ROUNDS; i++) {
        ft_memcpy(subkeys[i], key, key_size);
    }
}

void nonlinear_permutation(uint8_t state[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            state[i][j] = (state[i][j] << 4) | (state[i][j] >> 4);
        }
    }
}

void diffusion_transform(uint8_t state[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            state[i][j] = (state[i][j] + 1) % 256;
        }
    }
}

void apply_subkey(uint8_t state[8][8], uint8_t subkey[KEY_SIZE]) {
    int subkey_index = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            state[i][j] ^= subkey[subkey_index % KEY_SIZE];
            subkey_index++;
        }
    }
}

void process_block(uint8_t *block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        state[i / 8][i % 8] ^= block[i];
    }
    for (int i = 0; i < NUM_ROUNDS; i++) {
        nonlinear_permutation(state);
        diffusion_transform(state);
        apply_subkey(state, subkeys[i]);
    }
}


void preprocess(uint8_t *message, size_t length, Block **blocks, size_t *num_blocks) {
    *num_blocks = (length + BLOCK_SIZE - 1) / BLOCK_SIZE;
    *blocks = malloc(*num_blocks * sizeof(Block));
    for (size_t i = 0; i < *num_blocks; i++) {
        ft_memcpy((*blocks)[i].data, message + i * BLOCK_SIZE, BLOCK_SIZE);
    }
    size_t last_block_size = length % BLOCK_SIZE;
    if (last_block_size != 0) {
        ft_memset((*blocks)[*num_blocks - 1].data + last_block_size, 0, BLOCK_SIZE - last_block_size);
    }
}

uint8_t	*convert_state_to_array(uint8_t state[8][8], uint8_t *array) {
    if (array == NULL) {
        // Gérer l'erreur d'allocation
        exit(1);
    }

    int index = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            array[index++] = state[i][j];
        }
    }
	return array;
}

void	whirlpool(uint8_t *message, uint8_t *array, uint32_t message_length) {

	uint8_t key[KEY_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                             0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                             0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                             0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};

    initialize(key, sizeof(key));

	Block *blocks;
    size_t num_blocks;
    preprocess(message, message_length, &blocks, &num_blocks);

    num_blocks = (message_length + BLOCK_SIZE - 1) / BLOCK_SIZE;
    for (size_t i = 0; i < num_blocks; i++) {
        process_block(message + i * BLOCK_SIZE);
    }

	free(blocks);	
	convert_state_to_array(state, array);
}
