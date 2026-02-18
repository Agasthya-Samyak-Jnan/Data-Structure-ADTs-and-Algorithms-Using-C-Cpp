#include<bits/stdc++.h>

using namespace std;

// SHIFT CIPHER - 'K' Shifted
class ShiftCipher {
private:
    int key;

public:
    ShiftCipher (int k) { key = k; }

    string encrypt (string plaintext) {

        string ciphertext;

        for (auto letter : plaintext) {
            ciphertext += (((letter-'a') + key) % 26 + 'a');
        }

        return ciphertext;
    }

    string decrypt (string ciphertext) {

        string plaintext;

        for (auto letter : ciphertext) {
            plaintext += (((letter-'a') - key + 26) % 26 + 'a');
        }

        return plaintext;
    }

};

// PLAYFAIR CIPHER - 5x5 , DIGRAM
class PlayfairCipher {
private:
    vector<vector<char>> key;
    unordered_map<char,vector<int>> pos;

public:
    PlayfairCipher (string k) {
        
        unordered_map<char,int> found;
        key = vector<vector<char>>(5,vector<char>(5));
        int i = 0;

        for (auto letter : k) { 
            if (!found[letter]) {
                found[letter] = 1; 
                key[i/5][i%5] = letter; 
                pos[letter] = {i/5,i%5};
                i++; 
            }
        }

        for (char c='a';c<='z';c++) {
            if (found[c] || c == 'j') { continue; }
            key[i/5][i%5] = c;
            pos[c] = {i/5,i%5};
            i++;
        }
    }

    string encrypt (string pt) {

        // Seperate Same Consecutive Characters in Digrams
        for (int i=0;i<pt.length();i+=2) {  if (pt[i] == pt[i+1]) { pt.insert(i+1,"x"); } }
        if (pt.length() % 2 == 1) { pt.push_back('x'); }
        int n = pt.length();

        // Ciphertext String
        string ct(n,' ');

        for (int i=0;i<n;i+=2) {
            
            // Same Row
            if (pos[pt[i]][0] == pos[pt[i+1]][0]) {
                ct[i] = key[pos[pt[i]][0]][(pos[pt[i]][1]+1)%5];
                ct[i+1] = key[pos[pt[i+1]][0]][(pos[pt[i+1]][1]+1)%5];
            }

            // Same Column
            else if (pos[pt[i]][1] == pos[pt[i+1]][1]) {
                ct[i] = key[(pos[pt[i]][0]+1)%5][pos[pt[i]][1]];
                ct[i+1] = key[(pos[pt[i+1]][0]+1)%5][pos[pt[i+1]][1]];
            }

            // Rectangle Mode
            else {
                ct[i] = key[pos[pt[i]][0]][pos[pt[i+1]][1]];
                ct[i+1] = key[pos[pt[i+1]][0]][pos[pt[i]][1]];
            }

        }

        return ct;
    }

    string decrypt (string ct) {

        int n = ct.length();
        string pt(n,' ');

        for (int i=0;i<n;i+=2) {
            
            // Same Row
            if (pos[ct[i]][0] == pos[ct[i+1]][0]) {
                pt[i] = key[pos[ct[i]][0]][(pos[ct[i]][1]-1)%5];
                pt[i+1] = key[pos[ct[i+1]][0]][(pos[ct[i+1]][1]-1)%5];
            }

            // Same Column
            else if (pos[ct[i]][1] == pos[ct[i+1]][1]) {
                pt[i] = key[(pos[ct[i]][0]-1)%5][pos[ct[i]][1]];
                pt[i+1] = key[(pos[ct[i+1]][0]-1)%5][pos[ct[i+1]][1]];
            }

            // Rectangle Mode
            else {
                pt[i] = key[pos[ct[i]][0]][pos[ct[i+1]][1]];
                pt[i+1] = key[pos[ct[i+1]][0]][pos[ct[i]][1]];
            }

        }

        return pt;
    }

};

// HILL CIPHER - NxN , N-gram
class HillCipher {
private:
    vector<vector<int>> key, key_inv;
    int n;

public:
    HillCipher (vector<vector<int>> k, vector<vector<int>> ki, int size) {
        key = k;
        n = size;
        key_inv = ki;
    }

    string encrypt (string plaintext) {

        string ciphertext;
        vector<int> ciphervals(n,0);
        int l = plaintext.length();

        for (int pos=0;pos<l;pos+=n) {
            for (int row=0;row<n;row++) {
                for (int col=0;col<n;col++) {
                    ciphervals[row] += key[row][col]*(plaintext[pos+col]-'a');
                }
                ciphertext += ((ciphervals[row] % 26) + 'a');
                ciphervals[row] = 0;
            }
        }

        return ciphertext;
    }

    string decrypt (string ciphertext) {

        string plaintext;
        vector<int> plainvals(n,0);
        int l = ciphertext.length();

        for (int pos=0;pos<l;pos+=n) {
            for (int row=0;row<n;row++) {
                for (int col=0;col<n;col++) {
                    plainvals[row] += key_inv[row][col]*(ciphertext[pos+col]-'a');
                }
                plaintext += ((((plainvals[row] % 26) + 26) % 26) + 'a');
                plainvals[row] = 0;
            }
        }

        return plaintext;
    }

};

// VIGENERE CIPHER
class VigenereCipher {
private:
    string key;

public:
    VigenereCipher (string k) { key = k; }

    string encrypt (string plaintext) {

        string ciphertext;
        int n = plaintext.length(), k = key.length();

        for (int i=0;i<n;i++) {
            ciphertext += (((plaintext[i]-'a')+(key[i%k]-'a')) % 26) + 'a';
        }

        return ciphertext;
    }

    string decrypt (string ciphertext) {
        
        string plaintext;
        int n = ciphertext.length(), k = key.length();

        for (int i=0;i<n;i++) {
            plaintext += (((ciphertext[i]-'a')-(key[i%k]-'a') + 26) % 26) + 'a';
        }

        return plaintext;
    }
};

// VERNAM CIPHER
class VernamCipher {
private:
    string key;

public:
    VernamCipher (string k) { key = k; }

    string encrypt (string plaintext) {

        string ciphertext;
        int n = plaintext.length(), k = key.length();

        for (int i=0;i<n;i++) {
            ciphertext += ((plaintext[i]-'a')^(key[i%k]-'a')) + 'a';
        }

        return ciphertext;
    }

    string decrypt (string ciphertext) {
        
        string plaintext;
        int n = ciphertext.length(), k = key.length();

        for (int i=0;i<n;i++) {
            plaintext += ((ciphertext[i]-'a')^(key[i%k]-'a')) + 'a';
        }

        return plaintext;
    }
};

// RAIL FENCE CIPHER - 'K' Rows
class RailFenceCipher {
    private:
        int key;

    public:
    RailFenceCipher (int k) { key = k; }

    string encrypt (string plaintext) {

        if (key == 1) { return plaintext; }

        int n = plaintext.length(), i = 0, j = 0;
        vector<vector<char>> a = vector<vector<char>>(key,vector<char>(n,'\0'));
        vector<int> dx = {1,1};
        string ciphertext;

        for (auto letter : plaintext) {
            a[i][j] = letter;
            if (i == 0) { dx = {1,1}; }
            if (i == key-1) { dx = {-1,1}; }
            i += dx[0]; j += dx[1];
        }

        for (auto row : a) {
            for (auto letter : row) {
                ciphertext += letter;
            }
        }

        return ciphertext;
    }

    string decrypt (string ciphertext) {

        if (key == 1) { return ciphertext; }

    }

};

// ROW COLUMN TRANSPOSITION CIPHER
class RowColumnCipher {
private:
    vector<int> key;
    int n;

public:
    RowColumnCipher (vector<int> k) { key = k; n = k.size(); }

    string encrypt (string plaintext) {

        string ciphertext;
        int p = plaintext.length(), i = 0;
        vector<vector<char>> mat((p+n-1)/n,vector<char>(n));

        for (char letter : plaintext) { mat[i/n][i%n] = letter; i++; }
        while (i<mat.size()*n) { mat[i/n][i%n] = (rand() % 26) + 'a'; i++; }

        for (auto col : key) {
            for (int i=0;i<mat.size();i++) {
                ciphertext += mat[i][col-1];
            } 
        }

        return ciphertext;
    }

    string decrypt (string ciphertext) {
        
        string plaintext;
        int c = ciphertext.length(), i = 0, j = 0;
        vector<vector<char>> mat(c/n,vector<char>(n));

        for (auto col : key) {
            for (int i=0;i<c/n;i++) {
                mat[i][col-1] = ciphertext[j++];
            }
        }

        for (auto row : mat) {
            for (auto letter : row) {
                plaintext += letter;
            }
        }

        return plaintext;
    }

};


// DRIVER CODE
int main () {

    string plaintext = "killcoronavirusattwelveamtomorrow";
    srand(time(0));

    RowColumnCipher V({4,3,1,2,5,6,7});


    cout<<"ENCRYPTED PLAINTEXT : "<<V.encrypt(plaintext)<<"\n";

    cout<<"DECRYPTED CIPHERTEXT : "<<V.decrypt(V.encrypt(plaintext))<<"\n";

}