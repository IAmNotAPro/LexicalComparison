# Project Four 
Author: Grant Carmichael

This project is for CSCE 20104 at the University of Arkansas
## Purpose
The purpose of this project is to determine the lexical similarity between two books. This is done through two files, one handling the reading/writing of the frequency of words in a book file, while the other compares two files.

## Functionality

### Reading Data
The file given to the program is first stripped of all of the non-alphabetical values:

    while (file >> word)
    {
        string cleaned = "";

        // examine each character in the word, cleans         
        non-letter aspects of each word
        for (char c : word)
        {
            if (isalpha(c))
                cleaned += c;
        }

        // only store non-empty words
        if (!cleaned.empty())
            cleanedWords.push_back(cleaned);
    }

After being cleaned, all of the words are converted to lowercase:
```
for(const string word: cleanedWords)
    {
        string lowercase = "";
        
        // Converts all words to lowercase
        for(char c: word){
            lowercase += tolower(c);
        }

        if(!lowercase.empty())
            words.push_back(lowercase);
    }
```

### Handling Frequency
After reading the data and cleaning it, the values are pushed into a vector which is then passed to another function that handles calculating the frequency of each word.

```
vector<string> WordFrequency(const vector<string>& words)
{
    vector<string> frequency;
    int count = 0;
    cout << words.size() << endl;

    string freqWord;
    vector<string> frequentWords;
    ifstream file("FrequentWords.txt");

    while(file >> freqWord){
        frequentWords.push_back(freqWord);
    }
    
    sort(frequentWords.begin(), frequentWords.end()); // Sorts list alphabetically

    for(int i = 0; i < words.size(); i++){
        string word = words[i];
        int search = binarySearch(word, frequentWords, 0, 99);
        if(search){ // If search is true, go to next index, else keep going
            continue;
        }
        
        if(word == words[i+1]){
            //cout << "Same word: ";
            //cout << word << endl;
            count++;
        } else {
            if(count > 1){
                //cout << "Pushed back" << endl;
                frequency.push_back(word + ":" + to_string(count));
                word = words[i+1];
                count = 0;
            }
        }
    }
    return frequency;
}
```
This function uses a binary search algorithm that performs the removal of the 100 most common words in the english dictionary from the words in the file.

### Comparison

For the final portion of the project, the googoo file processes the frequency information given from goo, and uses that information to compare two chosen books. 

First, the program must ensure it has the correct information to compare the two books, which is done through a function known as readBooks. Because in the frequency files for each book the data is stored as "Word: frequency", the program must read the data up to the colon before it knows that it's now no longer looking at the actual word and instead the frequency.

```
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
```

After processing that data, the program moves onto the actual comparison itself. This comparison uses a linear search algorithm which searches word by word using the information obtained from the readBooks function. The calculation itself is found by taking the shared amount of words between the two books and dividing by the average number of words in the two books, multiplying by 100 to get a percentage. 

```
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
```

## Test Cases
Using the goo file initally to write all of the book frequencies to their respective text files, the user can then use the googoo file to compare the similarities of two of the books.

Upon running the goo file, the following text will be shown:

![Goo Output](Images/frequency-calculation.PNG)

After the user has been shown this screen, moving to the googoo file will allow for lexical comparison to be performed:

![GooGoo 1](Images/user-choice-1.PNG)

![GooGoo 2](Images/user-choice-2.PNG)

## Conclusion
This was one of the most beneficial projects I completed during my data structures and algorithms class. I learned useful information for using linear and binary search algorithms in software, and the process for implementing those. 

I would like to eventually revist this program to allow the user to search any two books on the web and compare those two rather then only having a set number.


