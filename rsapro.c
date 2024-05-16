#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int inverse_mod(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return x1;
}

void generate_keys(int p, int q, int e, int *public_key, int *private_key) {
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    while (gcd(e, phi) != 1) {
        e = rand() % phi;
    }
    *public_key = e;
    *private_key = inverse_mod(e, phi);
}

int encrypt(int message, int public_key, int n) {
    return (int)((long long)pow(message, public_key) % n);
}

int decrypt(int ciphertext, int private_key, int n) {
    return (int)((long long)pow(ciphertext, private_key) % n);
}

int main() {
    int p = 3;
    int q = 7;
    int e = 11;
    int public_key, private_key;

    generate_keys(p, q, e, &public_key, &private_key);
    printf("Public key (e, n): (%d, %d)\n", public_key, p * q);
    printf("Private key (d, n): (%d, %d)\n", private_key, p * q);

    int message = 42;
    int encrypted_message = encrypt(message, public_key, p * q);
    printf("Encrypted message: %d\n", encrypted_message);
    int decrypted_message = decrypt(encrypted_message, private_key, p * q);
    printf("Decrypted message: %d\n", decrypted_message);

    return 0;
}
