#include<iostream>
#include<bits/stdc++.h>
using namespace std;

vector<int> createAlphabetArray()  // Create an array to store alphabets from a to z
{
    return vector<int>(26,1);      // Initialize a vector of size 26 with default value 1
} 

vector<pair<int,int>> processText(string &text)
{
    vector<pair<int,int>> digraph;  // Create a digraph with all the pairs from the plain text

    int len = text.size();

    if(len%2 !=0)       // If the text size is odd then add the alphabet 'z' to the end of plain text
    {
        text+= 'z';
        len++;
    }

    for(int i=0; i<len;i++)
    {
        if(text[i]=='j') text[i]='i';
    }

    int i=0, j=1;

    while(j<len)
    {
        pair<int,int>temp;

        if(text[i]==text[j])        // If two similar characters in a pair then add an 'x' to the first
        {
            temp= make_pair((text[i]-'a'),('x'-'a'));
            i++;
            j++;
        }
        else
        {
            temp = make_pair((text[i]-'a'),(text[j]-'a'));
            i+=2;
            j+=2;
        }

        digraph.push_back(temp);
    }
    return digraph;
}
pair<string,string> acceptKey()
{
    string key,text;
    cout<<"Enter the text to be encrypted:\n";
    cin>>text;
    cout<<"\n\nEnter the key to encrypt the text:\n";
    cin>>key;
    return make_pair(text,key);
}

vector<vector<int>> createEncriptionMatrix(string &key,vector<int> &alphabetArray)
{
    vector<vector<int>> encryptionArray(5, vector<int>(5, 0));

    int i =0,j=0;

    int len  = key.size();

    for(int k=0;k<len;k++)
    {
        int temp = key[k]-'a';
        if(alphabetArray[temp]==1)  // No duplicate letters from the key to be added to the matrix
        {
            encryptionArray[i][j]= temp;
            alphabetArray[temp] = 0;
            j++;
        }
        if(j==5)
        {
            j=0;
            i++;
        }
    }

    for(int l=0;l<26; l++)      // Add the remaining letters to the encryption matrix
    {
        if(alphabetArray[l]==1)
        {
            if(j == 5)
            {
                j=0;
                i++;
            }
            encryptionArray[i][j]=l; 
            j++;
        }
    }

    cout<<"\nThe Encryption Matrix formed is:\n";
    for(int m=0; m<5; m++)
    {
        for(int n=0; n<5; n++)
        {
            char ch = 'a' + encryptionArray[m][n];
            cout<<ch<<"  ";
        }
        cout<<"\n";
    }
    return encryptionArray;
}

string findTextPairAndEncrypt(int letterOne, int letterTwo,vector<vector<int>> &encryptionArray)
{
    pair<int,int> indexLetterOne,indexLetterTwo;    // Store the indices locations of the pair to be encrypted

    string encrypt="";

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(encryptionArray[i][j]==letterOne)
            {
                indexLetterOne = make_pair(i,j);
                break;
            }
        }
    }

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(encryptionArray[i][j]==letterTwo)
            {
                indexLetterTwo = make_pair(i,j);
                break;
            }
        }
    }

    if(indexLetterOne.first == indexLetterTwo.first)    // If the two letters are in one row
    {
        int i=indexLetterOne.second;
        i++;
        int j=indexLetterTwo.second;
        j++;

        if(i==5) i=0;

        if(j==5) j=0;

        char charI = encryptionArray[indexLetterOne.first][i] +'a';
        char charJ = encryptionArray[indexLetterTwo.first][j] +'a';
        encrypt+=charI;
        encrypt+=charJ;

        return encrypt;
    }

    else if(indexLetterOne.second == indexLetterTwo.second)     //If the two letters are in the same column
    {
        int i=indexLetterOne.first;
        i++;
        int j=indexLetterTwo.first;
        j++;

        if(i==5) i=0;

        if(j==5) j=0;

        char charI = encryptionArray[i][indexLetterOne.second] +'a';
        char charJ = encryptionArray[j][indexLetterTwo.second] +'a';
        encrypt+=charI;
        encrypt+=charJ;

        return encrypt;
    }

    else if((indexLetterOne.first != indexLetterTwo.first) && (indexLetterOne.second != indexLetterTwo.second))     // If the two letters are in a diagonal
    {
        if(indexLetterTwo.second > indexLetterOne.second || indexLetterTwo.second < indexLetterOne.second)
        {
            int i=indexLetterOne.second;
            int j=indexLetterTwo.second;

            char charI = encryptionArray[indexLetterOne.first][j] +'a';
            char charJ = encryptionArray[indexLetterTwo.first][i] +'a';
            encrypt+=charI;
            encrypt+=charJ;

            return encrypt;
        }

    }
}

string decryptingString(string &encryptedString,vector<vector<int>> &encryptionMatrix)
{
    vector<pair<int,int>> digraph;

    int len = encryptedString.size();

    int i=0, j=1;

    while(j<len)
    {
        pair<int,int>temp;
        temp = make_pair((encryptedString[i]-'a'),(encryptedString[j]-'a'));
        i+=2;
        j+=2;
        digraph.push_back(temp);
    }

    string decrypt="";

    for(int i=0;i<digraph.size();i++)
    {
        int letterOne= digraph[i].first;
        int letterTwo= digraph[i].second;
        pair<int,int> indexLetterOne,indexLetterTwo;

        for(int i=0; i<5; i++)
        {
            for(int j=0; j<5; j++)
            {
                if(encryptionMatrix[i][j]==letterOne)
                {
                    indexLetterOne = make_pair(i,j);
                    break;
                }
            }
        }

        for(int i=0; i<5; i++)
        {
            for(int j=0; j<5; j++)
            {
                if(encryptionMatrix[i][j]==letterTwo){
                    indexLetterTwo = make_pair(i,j);
                    break;
                }
            }
        }

        if(indexLetterOne.first == indexLetterTwo.first)
        {
            int i=indexLetterOne.second;
            i--;
            int j=indexLetterTwo.second;
            j--;

            if(i==-1) i=4;

            if(j==-1) j=4;

            char charI = encryptionMatrix[indexLetterOne.first][i] +'a';
            char charJ = encryptionMatrix[indexLetterTwo.first][j] +'a';
            decrypt+=charI;
            decrypt+=charJ;
        }

        else if(indexLetterOne.second == indexLetterTwo.second)
        {
            int i=indexLetterOne.first;
            i--;
            int j=indexLetterTwo.first;
            j--;

            if(i==-1) i=4;

            if(j==-1) j=4;

            char charI = encryptionMatrix[i][indexLetterOne.second] +'a';
            char charJ = encryptionMatrix[j][indexLetterTwo.second] +'a';
            decrypt+=charI;
            decrypt+=charJ;
        }

        else if((indexLetterOne.first != indexLetterTwo.first) && (indexLetterOne.second != indexLetterTwo.second))
        {
            if(indexLetterTwo.second > indexLetterOne.second || indexLetterTwo.second < indexLetterOne.second)
            {
                int i=indexLetterOne.second;
                int j=indexLetterTwo.second;

                char charI = encryptionMatrix[indexLetterOne.first][j] +'a';
                char charJ = encryptionMatrix[indexLetterTwo.first][i] +'a';
                decrypt+=charI;
                decrypt+=charJ;
            }

        }

    }
    return decrypt;
}

pair<string,string> encryptingAndDecryptingText(string &text, string &key)
{
    vector<int> alphabetArray= createAlphabetArray();

    alphabetArray[9]=0;

    vector<vector<int>> encryptionMatrix= createEncriptionMatrix(key,alphabetArray);

    vector<pair<int,int>> digraphs= processText(text);

    string encryptedText="";

    for(int i=0;i<digraphs.size();i++)
    {
        encryptedText+= findTextPairAndEncrypt(digraphs[i].first,digraphs[i].second,encryptionMatrix); // Encrypt each pair in the digraph
    }

    string decryptedString = decryptingString(encryptedText,encryptionMatrix);

    return make_pair(encryptedText,decryptedString);
}

int main()
{
    pair<string,string> input= acceptKey();

    string text = input.first;

    string key = input.second;

    pair<string,string> strPair = encryptingAndDecryptingText(text,key);

    string encryptedString = strPair.first;

    string decrytedString = strPair.second;

    cout<<"\nThe Encryted string is:\n"<<encryptedString;

    cout<<"\n\nThe Decrypted string is:\n"<<decrytedString;

    return 0;
}