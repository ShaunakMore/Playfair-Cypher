# Playfair Cipher (C++ Implementation)

This is a simple implementation of the **Playfair Cipher** in C++.  
It allows you to encrypt and decrypt text using a given key by constructing a 5x5 Playfair matrix.

---

## Features
- Converts input text into digraphs (pairs of letters).
- Handles edge cases like:
  - Same consecutive letters (inserts `x`).
  - Odd length text (adds `z`).
  - Treats `i` and `j` as the same character.
- Generates a 5x5 encryption matrix from the key.
- Encrypts the text using Playfair rules:
  - Same row → shift right
  - Same column → shift down
  - Rectangle rule → swap columns
- Decrypts back to the original text.

---

## Usage
1. Compile the program:
   ```bash
   g++ playfair.cpp -o playfair

2. Run the program:

   ```bash
   ./playfair
   ```
3. Input:

   * Enter the text to encrypt.
   * Enter the key.

Example:

```
Enter the text to be encrypted:
hello

Enter the key to encrypt the text:
keyword
```

Output:

```
The Encryption Matrix formed is:
k  e  y  w  o  
r  d  a  b  c  
f  g  h  i  l  
m  n  p  q  s  
t  u  v  x  z  

The Encrypted string is:
gatcpl

The Decrypted string is:
helloz
```

---

## Notes

* This program is intended for **educational purposes**.
* Currently only supports lowercase alphabetic text.
* `j` is treated as `i` for matrix consistency.
