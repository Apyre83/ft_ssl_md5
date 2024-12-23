
#include "ft_ssl.h"

#define LB32_MASK 0x00000001
#define LB64_MASK 0x0000000000000001
#define L64_MASK 0x00000000ffffffff
#define H64_MASK 0xffffffff00000000




const uint64_t	IP[] = {
	58,	50,	42,	34,	26,	18,	10,	2,
	60,	52,	44,	36,	28,	20,	12,	4,
	62,	54,	46,	38,	30,	22,	14,	6,
	64,	56,	48,	40,	32,	24,	16,	8,
	57,	49,	41,	33,	25,	17,	9,	1,
	59,	51,	43,	35,	27,	19,	11,	3,
	61,	53,	45,	37,	29,	21,	13,	5,
	63,	55,	47,	39,	31,	23,	15,	7
};

const uint64_t E[] = {
	32, 1, 2, 3, 4, 5,
	4,	5,	6,	7,	8,	9,
	8,	9,	10,	11,	12,	13,
	12,	13,	14,	15,	16,	17,
	16,	17,	18,	19,	20,	21,
	20,	21,	22,	23,	24,	25,
	24,	25,	26,	27,	28,	29,
	28,	29,	30,	31,	32,	1,
};

const uint64_t PC1[] = {
	57,	49,	41,	33,	25,	17,	9,
	1,	58,	50,	42,	34,	26,	18,
	10,	2,	59,	51,	43,	35,	27,
	19,	11,	3,	60,	52,	44,	36,
	63,	55,	47,	39,	31,	23,	15,
	7,	62,	54,	46,	38,	30,	22,
	14,	6,	61,	53,	45,	37,	29,
	21,	13,	5,	28,	20,	12,	4
};

const uint64_t PC2[] = {
	14,	17, 11, 24, 1, 5,
	3,	28,	15,	6,	21,	10,
	23,	19,	12,	4,	26,	8,
	16,	7,	27,	20,	13,	2,
	41,	52,	31,	37,	47,	55,
	30,	40,	51,	45,	33,	48,
	44,	49,	39,	56,	34,	53,
	46,	42,	50,	36,	29,	32
};

const uint64_t P[] = {
	16,	7,	20,	21,
	29,	12,	28,	17,
	1,	15,	23,	26,
	5,	18,	31,	10,
	2,	8,	24,	14,
	32,	27,	3,	9,
	19,	13,	30,	6,
	22,	11,	4,	25
};

const uint64_t PI[] = {
	40,	8,	48,	16,	56,	24,	64,	32,
	39,	7,	47,	15,	55,	23,	63,	31,
	38,	6,	46,	14,	54,	22,	62,	30,
	37,	5,	45,	13,	53,	21,	61,	29,
	36,	4,	44,	12,	52,	20,	60,	28,
	35,	3,	43,	11,	51,	19,	59,	27,
	34,	2,	42,	10,	50,	18,	58,	26,
	33,	1,	41,	9,	49,	17,	57,	25
};


const int S[8][64] = {
    {
        14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
    },
    {
        15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
        3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
        0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
        13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
    },
    {
        10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
        13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
        13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
        1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
    },
    {
        7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
        13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
        10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
        3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
    },
    {
        2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
        14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
        4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
        11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
    },
    {
        12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
        10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
        9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
        4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
    },
    {
        4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
        13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
        1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
        6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
    },
    {
        13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
        1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
        7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
        2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
    }
};

const int iteration_shift[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };


/*
https://github.com/kongfy/DES
*/



uint64_t performInitialPermutation(uint64_t input) {
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        result <<= 1;
        result |= (input >> (64 - IP[i])) & LB64_MASK;
    }
    return result;
}

uint64_t generateKeyFromPermutations(uint64_t key, int round) {
    uint64_t pc1Result = 0;
    for (int i = 0; i < 56; i++) {
        pc1Result <<= 1;
        pc1Result |= (key >> (64 - PC1[i])) & LB64_MASK;  // Corrected here
    }

    uint32_t C = (uint32_t) ((pc1Result >> 28) & 0x000000000fffffff);
    uint32_t D = (uint32_t) (pc1Result & 0x000000000fffffff);

    // Left shifts
    for (int j = 0; j < iteration_shift[round]; j++) {
        C = (0x0fffffff & (C << 1)) | (0x00000001 & (C >> 27));
        D = (0x0fffffff & (D << 1)) | (0x00000001 & (D >> 27));
    }

    // PC-2 permutation
    uint64_t combined = (((uint64_t) C) << 28) | (uint64_t) D;
    uint64_t subKey = 0;
    for (int i = 0; i < 48; i++) {
        subKey <<= 1;
        subKey |= (combined >> (56 - PC2[i])) & LB64_MASK;
    }

    return subKey;  // Return the generated subKey
}



uint32_t functionF(uint32_t halfData, uint64_t subkey) {
    uint64_t expandedData = 0;

    // Step 1: Expansion
    for (int i = 0; i < 48; i++) {
        expandedData <<= 1;
        expandedData |= (halfData >> (32 - E[i])) & LB32_MASK;
    }

    // Step 2: XOR with subkey
    expandedData ^= subkey;

    // Step 3: S-Box substitution
    uint32_t substituted = 0;
    for (int i = 0; i < 8; i++) {
        char row = (char) ((expandedData & (0x0000840000000000 >> (6 * i))) >> (42 - 6 * i));
        row = (row >> 4) | (row & 0x01);
        char column = (char) ((expandedData & (0x0000780000000000 >> (6 * i))) >> (43 - 6 * i));
        substituted <<= 4;
        substituted |= S[i][16 * row + column] & 0x0f;
    }

    // Step 4: Permutation
    uint32_t output = 0;
    for (int i = 0; i < 32; i++) {
        output <<= 1;
        output |= (substituted >> (32 - P[i])) & LB32_MASK;
    }

    return output;
}


uint64_t finalPermutation(uint64_t preOutput) {
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        result <<= 1;
        result |= (preOutput >> (64 - PI[i])) & LB64_MASK;
    }
    return result;
}

void validate_des() {
    uint64_t result = 0x9474B8E8C73BCA7D;
    for (int i = 0; i < 16; i++) {
        result = des(result, result, i%2 == 0 ? 'e' : 'd');
    }
    printf("%016lX\n", result);
}


uint64_t des(uint64_t input, uint64_t key, char mode) {
    uint32_t leftHalf, rightHalf, temp;
    uint64_t initialPermutedBlock, combinedHalfBlocks, roundKey;

    // Étape 1: Permutation initiale
    initialPermutedBlock = performInitialPermutation(input);

    // Divisez le bloc en deux moitiés
    leftHalf = (uint32_t)(initialPermutedBlock >> 32) & L64_MASK;
    rightHalf = (uint32_t)initialPermutedBlock & L64_MASK;

    // Étape 2: Boucle des 16 tours
    for (int i = 0; i < 16; i++) {
        roundKey = generateKeyFromPermutations(key, mode == 'd' ? 15 - i : i);
        temp = rightHalf;
        rightHalf = leftHalf ^ functionF(rightHalf, roundKey);
        leftHalf = temp;
    }

    combinedHalfBlocks = ((uint64_t)rightHalf << 32) | leftHalf;

    return finalPermutation(combinedHalfBlocks);
}

