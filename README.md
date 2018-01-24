# RC4-Encryption-System
This program implements RC4 encryption system in C++

## Instructions
1. The program includes a Makefile. To compile the program, run "make" in the terminal.
2. After compiling, run “./c2 —generate” to generate a key. Also, you can set the key by yourself. Note that the length of the key is less or equal to 256 bits.
3. To encrypt, run “./c2 —encrypt “plaintext” —key “key””.
4. To decrypt, run “./c2 —decrypt “ciphertext” —key “key””.

## Tips
1. If you have “!” in your input, remember to write it as “\!”. Otherwise, the program can not be run.
2. The plaintext and ciphertext should be less or equal to 1024 bits.
3. The key should be less or equal to 256 bits.
4. Any other types of input except the three mentioned in Instruction 1, 2, 3, will be treated as wrong input.
