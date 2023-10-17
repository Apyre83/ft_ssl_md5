#include "ft_ssl.h"

int main() {
    uint64_t key = 0x133457799BBCDFF1;  // Juste un exemple de clé
    uint64_t plaintext = 0x0123456789ABCDEF;  // Juste un exemple de texte en clair

    uint64_t cipher = des(plaintext, key, 'e');
    uint64_t decrypted = des(cipher, key, 'd');

    printf("Plaintext: %016lX\n", plaintext);
    printf("Cipher (DES): %016lX\n", cipher);
    printf("Decrypted (DES): %016lX\n", decrypted);

    return 0;
}

