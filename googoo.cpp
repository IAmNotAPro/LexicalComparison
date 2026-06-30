// Author: Grant Carmichael

// Libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
int numCount = 0;

/* 
    Find number of words in each book, add them together and divide by two to find the average. Then
    find how many words are actually shared in the two books. Then, divide that number by the average 
    amount of words to find the lexical similarity, multiplying by 100 to find the percentage.
*/

float lexicalComparison(const vector<string>& bookOneWords, const vector<string>& bookTwoWords){
    float averageWords = (bookOneWords.size() + bookTwoWords.size()) / 2.0;
    float sharedWords = 0.0;
    bool bookOneLarger = false;

    if(bookOneWords.size() > bookTwoWords.size()){
        bookOneLarger = true;
    } else {
        bookOneLarger = false;
    }

    if(!bookOneLarger){
        for (int i = 0; i < bookTwoWords.size(); i++){
            bool isFound = false;
            int temp = 0;
            while(temp < bookOneWords.size()){
                if (bookTwoWords[i] == bookOneWords[temp]){
                    sharedWords++;
                    isFound = true;
                    break;
                }
                temp++;
            }
        }
    }
    else{
        for (int i = 0; i < bookOneWords.size(); i++){
            bool isFound = false;
            int temp = 0;
            while(temp < bookTwoWords.size()){
                if (bookOneWords[i] == bookTwoWords[temp]){
                    sharedWords++;
                    isFound = true;
                    break;
                }
                temp++;
            }
        }
    }

    float lexicalSimilarity = sharedWords / averageWords;
    cout << "Lexical similarity is: " << (lexicalSimilarity * 100.0) << "%" << endl;

    return lexicalSimilarity;

}

vector<string> readBooks(string book){

    numCount = 0;
    
    ifstream file("Books/Frequency/" + book + "Frequency.txt");

    /* 
        Need to read word by word, checking for ":", and once that character is found
        then store the word in its own vector, and add the frequency to a "count"
    */

    vector<string> words;
    vector<string> frequencies;
    string word;
    int uniqueWords = 0;

    while (file >> word)
    {
        string cleanword = "";
        string frequency = "";
        bool foundColon = false;

        for (char c: word){
            if (c == ':'){
                foundColon = true;
                uniqueWords++;
                continue;
            }
            
            if (!foundColon){
                cleanword += c;
            }
            else {  
                frequency += c;
            }
        }
        
        numCount = numCount + stoi(frequency);
        
        frequencies.push_back(frequency);
        words.push_back(cleanword);
    }

    cout << endl << book << endl;
    cout << "Total words in Book: " << ": " << numCount << endl;
    cout << "Number of Unique Words: " << uniqueWords << endl;

    return words;
}

int main(){
    
    string book1;
    string book2;
    int averageWords = 0;
    cout << "Please choose two books from the following list: " << endl
        << "1. Beowulf" << endl << "2. CityOfGod" << endl << "3. BrothersKaramazov" << endl
        << "4. Frankenstein" << endl << "5. GreatGatsby" << endl << "6. MobyDick" << endl
        << "7. PrideAndPrejudice" << endl << "8. RomeoAndJuliet" << endl << "9. SherlockHolmes" 
        << endl << "10. TomSawyer" << endl;
    cout << "Input first book name (no spaces): ";
    cin >> book1;
    cout << "Input second book name (no spaces): ";
    cin >> book2;
    vector<string> bookOneWords = readBooks(book1);
    vector<string> bookTwoWords = readBooks(book2);

    lexicalComparison(bookOneWords, bookTwoWords);

}