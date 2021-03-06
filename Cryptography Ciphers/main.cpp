#include<bits/stdc++.h>

using namespace std;

class Cesar {
public:
    string cesar(string text, int key, int choice) {
        for (int i = 0; i < text.length(); i++) {
            if (!(isalpha(text[i]))) { // string includes ( _ / * / white space / % / .... );
                continue;
            }
            char type = isupper(text[i]) ? 'A' : 'a'; // determine the type of string UPPER or LOWER;
            if (choice == 1) // encrypt
                text[i] = (text[i] + key - type) % 26 + type;
            else if (choice == 2) // decrypt
                text[i] = ((text[i] - key - type) + 26) % 26 + type;  // +26 for negative values
        }
        return text;
    }
};

class Affine {
public:
    string AffineEncrypt(string text, int key, int m) {
        for (int i = 0; i < text.length(); i++) {
            if (!(isalpha(text[i]))) { // string includes ( _ / * / white space / % / .... );
                continue;
            }
            char type = isupper(text[i]) ? 'A' : 'a'; // determine the type of string UPPER or LOWER;
            text[i] = (((text[i] - type) * m + key) % 26) + type;
        }
        return text;
    }

    string AffineDecrypt(string text, int key, int m) {
        int f = 0, m_inv = 0;
        for (int i = 0; i < 26; i++) { // To determine m';
            f = (m * i) % 26;
            if (f == 1)
                m_inv = i;
        }

        for (int i = 0; i < text.length(); i++) {
            if (!(isalpha(text[i]))) { // string includes ( _ / * / white space / % / .... );
                continue;
            }
            char type = isupper(text[i]) ? 'A' : 'a'; // determine the type of string UPPER or LOWER;
            text[i] = (m_inv * (text[i] - type - key + 26)) % 26 + type;
        }
        return text;
    }
};

class SimpleShift_Vignere {
public:
    void generateKey_Simple(vector<int> &key, string text) {
        cout << "Enter number of elements:\n";
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) { // read the whole key ex: 5 13 2 7;
            int x;
            cin >> x;
            key.push_back(x);
        }

        int i = 0;
        //int length = key.size();    // 3
        while (key.size() != text.size()) { //generete the key;
            //if (i == length)
            //i = 0;
            key.push_back(key[i]);
            i++;
        }
    }

    string SimpleVigenere(string text, vector<int> &key, int choice) {
        for (int i = 0, j = 0; i < text.length(); i++, j++) {
            if (!(isalpha(text[i]))) { // string includes ( _ / * / white space / % / .... );
                j--;    // when a space appears j moves to the next key while the current key is not used;
                continue;
            }
            char type = isupper(text[i]) ? 'A' : 'a';  // determine the type of string UPPER or LOWER;
            if (choice == 1)    //encrypt;
                text[i] = (text[i] + key[j] - type) % 26 + type;
            else if (choice == 2)   //decrypt;
                text[i] = (text[i] - key[j] - type + 26) % 26 + type;    // +26 to avoid the negative values;
        }
        return text;
    }
};

class FallVigenere {
public:
    void generateKey_Fall(string &key, string text) {
        int i = 0;
        while (key.size() != text.size()) {
            if (i == text.size())
                i = 0;
            key.push_back(key[i]);
            i++;
        }
    }

    string Fall_Vigenere(string text, string key, int choice) {
        for (int i = 0, j = 0; i < text.length(); ++i, j++) {
            if (!(isalpha(text[i]))) { // string includes ( _ / * / white space / % / .... );
                j--;
                continue;
            }
            text[i] = toupper(text[i]); //transform string to uppercase;
            if (choice == 1)    //encrypt;
                text[i] = (text[i] + key[j] - 2 * 'A') % 26 + 'A';
            else if (choice == 2)   //decrypt;
                text[i] = (text[i] - key[j] + 26) % 26 + 'A';
        }
        return text;
    }
};

class ROT13 {
public:
    void create_map(map<char, int> &alpha1, map<int, char> &alpha2) {
        for (int i = 0; i < 26; i++)
            alpha1[char('A' + i)] = i + 1;

        alpha2[0] = 'Z';
        for (int i = 0; i < 26; i++) {
            alpha2[i + 1] = char('A' + i);
        }
    }

    string rot13(string text, int choice, map<char, int> &alpha1, map<int, char> &alpha2) {
        int key = 13;
        for (int i = 0; i < text.length(); i++) {
            if (!(isalpha(text[i]))) { // string includes ( _ / * / white space / % / .... );
                continue;
            }

            if (choice == 1) {
                int idx = (alpha1[text[i]] + key) % 26; //shifting the index;
                text[i] = alpha2[idx];  //add the shfited index from the other map;
            } else if (choice == 2) {
                int idx = (alpha1[text[i]] - key + 26) % 26; //shifting the index;
                text[i] = alpha2[idx];  //add the shfited index from the other map;
            }
        }

        return text;
    }
};

class S_Box {
public:
    string To_binary(int asci) {
        string binary = "";
        int n = 8; //store 8 bits;
        while (n--) {
            binary += (asci % 2) + '0';
            asci /= 2;
        }
        reverse(binary.begin(), binary.end());  //reverse the string;
        return binary;
    }

    string Solve(string text, map<string, string> &mp, string key) {
        string T, U, E;
        T += (text[2] - '0' ^ key[0] - '0') + '0';
        T += (text[3] - '0' ^ key[1] - '0') + '0';
        T += (text[2] - '0' ^ key[2] - '0') + '0';

        T = mp[T]; //look up at the map to the corresponding string;

        U += (text[0] - '0' ^ T[0] - '0') + '0';
        U += (text[1] - '0' ^ T[1] - '0') + '0';

        E.push_back(text[2]), E.push_back(text[3]);
        E.push_back(U[0]), E.push_back(U[1]);

        return E;
    }

    int To_decimal(string decimal) {    //convert binary to decimal;
        int num = 0;
        for (int i = 0; i < decimal.length(); i++) {
            num += (decimal[i] - '0') * pow(2, i);
        }
        return num;
    }

    void s_box(string text, string key, ofstream &result) {
        map<string, string> mp; //generate s-box table;
        mp["000"] = "11", mp["001"] = "01", mp["010"] = "00", mp["011"] = "10";
        mp["100"] = "01", mp["101"] = "00", mp["110"] = "11", mp["111"] = "10";

        for (int i = 0; i < text.length(); i++) {
            string binary = To_binary(text[i]);
            string decimal = Solve(binary.substr(0, 4), mp, key) +
                             Solve(binary.substr(4, 4), mp, key); //solve equation of each half;
            reverse(decimal.begin(), decimal.end());    //reverse again to convert binary to decimal;
            result << text[i] << ": " << To_decimal(decimal) << '\n';
        }
    }
};

class PlayFair {
public:
    string PlayFair_Encrypt(string text, vector<vector<char>> &alphaTable, map<char, int> &mp) {
        int n = 5;
        string finalText = "";
        for (int i = 0; i < text.size(); i++) { //remove spaces;
            if (text[i] != ' ')
                finalText += text[i];
        }

        for (int i = 0; i < finalText.size() - 1; i++) {    //add an 'x' between 2 continuous characters;
            if (finalText[i] == finalText[i + 1])
                finalText.insert(i + 1, 1, 'x');
        }

        if (finalText.size() % 2 == 1)  // if odd size add an 'x' to the string;
            finalText += 'x';

        map<char, pair<int, int> > mp2;
        for (int i = 0; i < n; i++) {   //add indicies to the coresponding characters;
            for (int j = 0; j < n; j++) {
                mp2[alphaTable[i][j]] = make_pair(i, j); // 'L' ==> (0,1);
            }
        }

        string ans = "";
        for (int i = 0; i < finalText.size() - 1; i += 2) {
            int row1 = mp2[finalText[i]].first; //get row;
            int col1 = mp2[finalText[i]].second; //get col;
            int row2 = mp2[finalText[i + 1]].first;
            int col2 = mp2[finalText[i + 1]].second;
            if (row1 == row2) { //move right;
                ans += alphaTable[row1][(col1 + 1) % 5];
                ans += alphaTable[row1][(col2 + 1) % 5];
            } else if (col1 == col2) {  //move down;
                ans += alphaTable[(row1 + 1) % 5][col1];
                ans += alphaTable[(row2 + 1) % 5][col2];
            } else {
                ans += alphaTable[row1][col2];
                ans += alphaTable[row2][col1];
            }
        }
        return ans;
    }


    string PlayFair_Decrypt(string text, vector<vector<char>> &alphaTable, map<char, int> &mp) {
        string ans;
        int n = 5;
        map<char, pair<int, int> > mp2;
        for (int i = 0; i < n; i++) {   //add indicies to the coresponding characters;
            for (int j = 0; j < n; j++) {
                mp2[alphaTable[i][j]] = make_pair(i, j); // 'L' ==> (0,1);
            }
        }

        for (int i = 0; i < text.size() - 1; i += 2) {
            int row1 = mp2[text[i]].first;  //get row;
            int col1 = mp2[text[i]].second; //get col;
            int row2 = mp2[text[i + 1]].first;
            int col2 = mp2[text[i + 1]].second;
            if (row1 == row2) { // move left;
                ans += alphaTable[row1][(col1 - 1 + 5) % 5];    //avoid negative indices;
                ans += alphaTable[row1][(col2 - 1 + 5) % 5];
            } else if (col1 == col2) {  //move up;
                ans += alphaTable[(row1 - 1 + 5) % 5][col1];
                ans += alphaTable[(row2 - 1 + 5) % 5][col2];
            } else {
                ans += alphaTable[row1][col2];
                ans += alphaTable[row2][col1];
            }
        }

        string final_ans = "";
        for (auto &c : ans) { // remove 'x' from final string;
            if (c != 'x')
                final_ans += c;
        }

        return final_ans;
    }

    string Playfair(string text, string key, int choice) {
        int i = 0, j = 0, n = 5, k = 0;
        vector<vector<char>> alphaTable(5, vector<char>(5, ' ')); //2d array (table);
        map<char, int> mp;
        for (i = 0; i < n; i++) {   //generate the table;
            for (j = 0; j < n; j++) {
                while (mp[key[k]] > 0 && k < key.size()) {
                    k++;
                }
                if (k < key.size()) {   //if the corresponding char appears in key we add it to the table;
                    alphaTable[i][j] = key[k];
                    mp[key[k]]++;   //remove the corresponding character from the table;
                }
                if (k == key.size())    //break when all of the key is insreted to the table;
                    break;
            }
            if (k == key.size())
                break;
        }

        k = 0;
        for (; i < n; i++) {    //add the rest of alphabet to the table in lexicographically (a--> z) order;
            for (; j < n; j++) {
                while (mp[char(k + 'a')] > 0 && k < 26) {
                    k++;
                }
                if (char(k + 'a') == 'j') { // add i/j in the same cell;
                    j--;
                    k++;
                    continue;
                }
                if (k < 26) {   //replace character at the coresponding position in the table;
                    alphaTable[i][j] = char(k + 'a');
                    mp[char(k + 'a')]++;
                }
            }
            j = 0;
        }

        if (choice == 1) return PlayFair_Encrypt(text, alphaTable, mp);
        else return PlayFair_Decrypt(text, alphaTable, mp);
    }
};

int main() {
    string plainText;
    ifstream File("input.txt");  //read input from file;
    getline(File, plainText);
    File.close();

    ofstream result("result.txt");

    cout << "1) Cesar cipher \n2) Affine cipher \n3) Simple shift Vigenere cipher\n"
         << "4) Full Vigenere cipher \n5) ROT13 \n6) S-box \n7) Playfair cipher \n";
    int type;
    cin >> type;

    int key, choice;
    switch (type) {
        case 1: {
            cout << "1) Encrypt \n2) Decrypt\n";
            cin >> choice;
            cout << "Enter the key (digit): " << '\n';
            cin >> key;
            Cesar ob1;
            result << ob1.cesar(plainText, key, choice);
            break;
        }

        case 2: {
            int m;
            cout << "1) Encrypt \n2) Decrypt\n";
            cin >> choice;
            cout << "Enter the key and 'm': " << '\n';
            cin >> key >> m;
            Affine ob1;
            if (choice == 1) result << ob1.AffineEncrypt(plainText, key, m);
            else result << ob1.AffineDecrypt(plainText, key, m);
            break;
        }

        case 3: {
            cout << "Enter the key (digits): \n";
            vector<int> key;
            SimpleShift_Vignere ob1;
            ob1.generateKey_Simple(key, plainText);
            cout << "1) Encrypt \n2) Decrypt\n";
            cin >> choice;
            result << ob1.SimpleVigenere(plainText, key, choice) << endl;
            break;
        }
        case 4: {
            string key;
            cout << "Enter the key (string): \n";
            cin >> key;
            cout << "1) Encrypt \n2) Decrypt\n";
            cin >> choice;
            FallVigenere ob1;
            ob1.generateKey_Fall(key, plainText);
            result << ob1.Fall_Vigenere(plainText, key, choice) << endl;
            break;
        }
        case 5: {
            cout << "1) Encrypt \n2) Decrypt\n";
            cin >> choice;
            map<char, int> alpha1;
            map<int, char> alpha2;
            ROT13 ob1;
            ob1.create_map(alpha1, alpha2);
            result << ob1.rot13(plainText, choice, alpha1, alpha2);
            break;
        }
        case 6: {
            string key;
            cout << "Enter the key (digits):\n";
            cin >> key;     //011
            S_Box ob1;
            ob1.s_box(plainText, key, result);
            break;
        }
        case 7: {
            string key;
            cout << "Enter the key (string): \n";
            cin >> key;
            cout << "1) Encrypt \n2) Decrypt\n";
            cin >> choice;
            PlayFair ob1;
            if (choice == 1) result << ob1.Playfair(plainText, key, choice);
            else result << ob1.Playfair(plainText, key, choice);
            break;
        }
        default:
            cout << "Wrong Choice\n";
    }
    result.close();
    return 0;
}