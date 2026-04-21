#include "stdafx.h"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/pem.h>
#include <openssl/err.h>

int pad(unsigned char *data, int length, int block_size) {
	int padding = block_size - (length % block_size);
	for (int i = 0; i < padding; i++) {
		data[length + i] = padding;
	}
	return padding;
}

int unpad(unsigned char *data, int length) {
	int padding = data[length - 1];
	if (padding > AES_BLOCK_SIZE || padding <= 0) {
		fprintf(stderr, "Invalid padding\n");
		return -1;
	}
	for (int i = 0; i < padding; i++) {
		if (data[length - i - 1] != padding) {
			fprintf(stderr, "Invalid padding\n");
			return -1;
		}
	}
	return length - padding;
}

void encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
	unsigned char *ciphertext) {
	AES_KEY enc_key;

	// Use the full 32 bytes of the key for AES-256
	if (AES_set_encrypt_key(key, 256, &enc_key) < 0) {
		fprintf(stderr, "Unable to set encryption key.\n");
		exit(1);
	}

	AES_ecb_encrypt(plaintext, ciphertext, &enc_key, AES_ENCRYPT);
}

void decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
	unsigned char *plaintext) {
	AES_KEY dec_key;

	// Use the full 32 bytes of the key for AES-256
	if (AES_set_decrypt_key(key, 256, &dec_key) < 0) {
		fprintf(stderr, "Unable to set decryption key.\n");
		exit(1);
	}

	AES_ecb_encrypt(ciphertext, plaintext, &dec_key, AES_DECRYPT);
}

// Function to convert a byte array to a hex string
void bytes_to_hex(const unsigned char *bytes, size_t len, char *hexstr) {
	for (size_t i = 0; i < len; i++) {
		sprintf(hexstr + (i * 2), "%02X", bytes[i]);
	}
	hexstr[len * 2] = '\0';
}

int main(int argc, char *argv[]) {
	// Set up the key and iv. Do I need to say to not hard code these in a real application?
	const char *key_str = "!@#$&*PrinterGeniusExpert*&$#@!!";
	unsigned char *key = (unsigned char *)key_str;

	// Ensure the key is exactly 32 bytes long
	unsigned char actual_key[32];
	memcpy(actual_key, key, 32);

	unsigned char *plaintext = (unsigned char *)"printer!@#";

	// Buffer for padded plaintext
	int plaintext_len = strlen((char *)plaintext);
	int block_size = AES_BLOCK_SIZE;
	int padded_plaintext_len = ((plaintext_len + block_size) / block_size) * block_size;
	unsigned char *padded_plaintext = (unsigned char *)malloc(padded_plaintext_len);

	if (!padded_plaintext) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	// Copy plaintext into padded plaintext buffer and add padding
	memcpy(padded_plaintext, plaintext, plaintext_len);
	pad(padded_plaintext, plaintext_len, block_size);

	// Buffer for ciphertext
	unsigned char *ciphertext = (unsigned char *)malloc(block_size);

	if (!ciphertext) {
		fprintf(stderr, "Memory allocation failed\n");
		free(padded_plaintext);
		exit(1);
	}

	// Buffer for decrypted text
	unsigned char *decryptedtext = (unsigned char *)malloc(padded_plaintext_len);

	if (!decryptedtext) {
		fprintf(stderr, "Memory allocation failed\n");
		free(padded_plaintext);
		free(ciphertext);
		exit(1);
	}

	// Encrypt the plaintext
	encrypt(padded_plaintext, padded_plaintext_len, actual_key, ciphertext);

	// Print ciphertext in hex format
	char ciphertext_hex[AES_BLOCK_SIZE * 2 + 1];
	bytes_to_hex(ciphertext, block_size, ciphertext_hex);
	printf("Ciphertext (hex): %s\n", ciphertext_hex);

	// Decrypt the ciphertext
	decrypt(ciphertext, block_size, actual_key, decryptedtext);

	// Remove padding from decrypted text
	int decryptedtext_len = unpad(decryptedtext, padded_plaintext_len);

	// Add a NULL terminator. We are expecting printable text
	decryptedtext[decryptedtext_len] = '\0';

	// Show the decrypted text
	printf("Decrypted text is:\n");
	printf("%s\n", decryptedtext);

	// Free allocated memory
	free(padded_plaintext);
	free(ciphertext);
	free(decryptedtext);

	return 0;
}



