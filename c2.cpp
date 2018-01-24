#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

int chrtoint(char a){
  int asc = (int)a;
  int i;
  string symbol = ",.;?!()";
  if (asc>=97 && asc<=122) i = asc - 97;
  else if (asc>=65 && asc<=90) i = asc - 39;
  else if (asc>=48 && asc<=57) i = asc + 4;
  else{
    for (int k=0; k<7; k++){
      if (a == symbol[k]){
        i = k + 62;
        break;
      }
    }
  }
  return i;
}

char inttochr(int i){
  char chr;
  string symbol = ",.;?!()";
  if (i>=0 && i<=25) chr = (char)(i + 97);
  else if (i>=26 && i<=51) chr = (char)(i + 39);
  else if (i>=52 && i<=61) chr = (char)(i - 4);
  else{
    chr = symbol[i-62];
  }
  return chr;
}

int generate (unsigned int key[]) {
	srand(time(NULL));
	int keylen = rand()%256 + 1;
	for (int i = 0; i < keylen; i++) {
		key[i] = rand() % 69;
	}
	return keylen;
}

void rc4_key (unsigned int keystream[], unsigned int key[], int keylen, int datalen) {
	unsigned int s[256];
	for (int i = 0; i < 256; i++) {
		s[i] = i;
	}
	int j = 0;
	for (int i = 0; i < 256; i++) {
		j = (j + s[i] + key[i%keylen]) % 256;
		int temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
	int m = 0;
	int n = 0;
	for (int i = 0; i < datalen; i++) {
		m = (m+1) % 256;
		n = (n + s[m]) % 256;
		int temp = s[m];
		s[m] = s[n];
		s[n] = temp;
		keystream[i] = (s[(s[m] + s[n]) % 256]) % 64;
	}
}

void encrypt (unsigned int message[], unsigned int keystream[], unsigned int cipher[], int datalen) {
	for (int i = 0; i < datalen; i++) {
		cipher[i] = message[i] ^ keystream[i];
	}
}

void decrypt (unsigned int message[], unsigned int keystream[], unsigned int cipher[], int datalen) {
	for (int i = 0; i < datalen; i++) {
		message[i] = cipher[i] ^ keystream[i];
	}
}

int main (int argc, char* argv[]) {
	int keylen;
	unsigned int keystream[1024];
	int datalen;
	unsigned int message[1024];
	unsigned int cipher[1024];
	unsigned int key[256]; 

	if (argc == 2 && strcmp(argv[1], "--generate") == 0){
		keylen = generate(key);
		cout << "The key is: ";
		for (int i = 0; i < keylen; i++) {
			cout << inttochr(key[i]);
		}
		cout << endl;
	}
  	else if (argc == 5){
    	if (strcmp(argv[1], "--encrypt") == 0 && strcmp(argv[3], "--key") == 0){
    		for (int i = 0; i < strlen(argv[4]); i++) {
    			key[i] = chrtoint (argv[4][i]);
    		}
    		keylen = strlen(argv[4]);
	      	for (int i = 0; i < strlen(argv[2]); i++) {
    			message[i] = chrtoint(argv[2][i]);
    		}
	      	datalen = strlen(argv[2]);
	      	rc4_key (keystream, key, keylen, datalen);
	      	encrypt (message, keystream, cipher, datalen);
	      	cout << "Ciphertext is: ";
	      	for (int i = 0; i < datalen; i++) {
				cout << inttochr(cipher[i]);
			}
			cout << endl;
    	}
    	else if (strcmp(argv[1], "--decrypt") == 0 && strcmp(argv[3], "--key") == 0){
      		for (int i = 0; i < strlen(argv[4]); i++) {
    			key[i] = chrtoint (argv[4][i]);
    		}
    		keylen = strlen(argv[4]);
	      	for (int i = 0; i < strlen(argv[2]); i++) {
    			cipher[i] = chrtoint (argv[2][i]);
    		}
	      	datalen = strlen(argv[2]);
	      	rc4_key (keystream, key, keylen, datalen);
	      	decrypt (message, keystream, cipher, datalen);
	      	cout << "Plaintext is: ";
	      	for (int i = 0; i < datalen; i++) {
				cout << inttochr(message[i]);
			}
			cout << endl;
    	}
    	else{
      		cout << "Wrong input!" << endl;
    	}
  	}
  	else{
    	cout << "Wrong input!" << endl;
  	}
  	return 0;
}