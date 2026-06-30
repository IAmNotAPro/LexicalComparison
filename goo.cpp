// Author: Grant Carmichael

// Libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// Function read words from a file and store them as a vector of words
vector<string> ReadWords(const string filename)
{
    vector<string> cleanedWords;
    vector<string> words;        // final container
    ifstream file(filename);     // open file

    if (!file)
    {
        cout << "Error opening file.\n";
        return words;
    }

    string word;

    // read one word at a time
    while (file >> word)
    {
        string cleaned = "";

        // examine each character in the word, cleans non-letter aspects of each word
        for (char c : word)
        {
            if (isalpha(c))
                cleaned += c;
        }

        // only store non-empty words
        if (!cleaned.empty())
            cleanedWords.push_back(cleaned);
    }

    // Converts all characters to lowercase and stores them in the final vector
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

    file.close();
    return words;
}

// Function to write the frequency of words to a file, from the WordFrequency function
vector<string> WriteFrequency(const vector<string>& frequency, string input)
{
    ofstream file("Books/Frequency/" + input);

    if (!file)
    {
        cout << "Error opening file for writing.\n";
        return frequency;
    }

    for (const string& word : frequency)
    {
        file << word << endl;
    }

    file.close();
    return frequency;
}

bool binarySearch(string desired, const vector<string>& words, int min, int max)
{
    int mid = (min+max)/2;

    if(max < min)
        return false;
    else if (words[mid] == desired)
    {
        return true;
    }
    else if (words[mid] < desired){
        return(binarySearch(desired, words, mid+1, max));
    }
    else if (words[mid] > desired){
        return(binarySearch(desired, words, min, mid-1));
    }

    return false;
}

// Function to find the frequency of words in a vector
vector<string> WordFrequency(const vector<string>& words)
{
    vector<string> frequency;
    int count = 0;

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

int main(){

    /*
        HARDCODED, CALCULATES FREQUENCY OF ALL 10 FILES
        ONLY NEEDS TO BE RAN ONCE TO BE USED IN GOO GOO 
        FUNCTION.

        Currently, all books are being read out of a folder titled "Books",
        if the reading is not working for you, either change the file paths
        in the code, or create a folder titled "Books" and place the .txt files
        in there.

    */

    // Read and write Beowulf frequency
    cout << "Calculating frequency for Beowulf..." << endl;
    vector<string> Beowulf = ReadWords("Books/Beowulf.txt");
    sort(Beowulf.begin(), Beowulf.end());
    vector<string> BeowulfFrequency = WordFrequency(Beowulf);
    WriteFrequency(BeowulfFrequency, "BeowulfFrequency.txt");

    // ------------------------------------------------------------

    // Read and write City of God frequency
    cout << "Calculating frequency for City of God..." << endl;
    vector<string> CityOfGod = ReadWords("Books/CityOfGod.txt");
    sort(CityOfGod.begin(), CityOfGod.end());
    vector<string> CityOfGodFrequency = WordFrequency(CityOfGod);
    WriteFrequency(CityOfGodFrequency, "CityOfGodFrequency.txt");

    // ------------------------------------------------------------

    // Read and write Frankenstein frequency
    cout << "Calculating frequency for Frankenstein..." << endl;
    vector<string> Frankenstein = ReadWords("Books/Frankenstein.txt");
    sort(Frankenstein.begin(), Frankenstein.end());
    vector<string> FrankensteinFrequency = WordFrequency(Frankenstein);
    WriteFrequency(FrankensteinFrequency, "FrankensteinFrequency.txt");

    // ------------------------------------------------------------

    // Read and write Moby Dick frequency
    cout << "Calculating frequency for Moby Dick..." << endl;
    vector<string> MobyDick = ReadWords("Books/MobyDick.txt");
    sort(MobyDick.begin(), MobyDick.end());
    vector<string> MobyDickFrequency = WordFrequency(MobyDick);
    WriteFrequency(MobyDickFrequency, "MobyDickFrequency.txt");

    // ------------------------------------------------------------

    // Read and write Pride and Prejudice frequency
    cout << "Calculating frequency for Pride and Prejudice..." << endl;
    vector<string> PrideAndPrejudice = ReadWords("Books/PrideAndPrejudice.txt");
    sort(PrideAndPrejudice.begin(), PrideAndPrejudice.end());
    vector<string> PrideAndPrejudiceFrequency = WordFrequency(PrideAndPrejudice);
    WriteFrequency(PrideAndPrejudiceFrequency, "PrideAndPrejudiceFrequency.txt");

    // ------------------------------------------------------------

    // Read and write Romeo and Juliet frequency
    cout << "Calculating frequency for Romeo and Juliet..." << endl;
    vector<string> RomeoAndJuliet = ReadWords("Books/RomeoAndJuliet.txt");
    sort(RomeoAndJuliet.begin(), RomeoAndJuliet.end());
    vector<string> RomeoAndJulietFrequency = WordFrequency(RomeoAndJuliet);
    WriteFrequency(RomeoAndJulietFrequency, "RomeoAndJulietFrequency.txt");

    // ------------------------------------------------------------

    // Read and write The Adventures of Sherlock Holmes frequency
    cout << "Calculating frequency for Sherlock Holmes..." << endl;
    vector<string> SherlockHolmes = ReadWords("Books/SherlockHolmes.txt");
    sort(SherlockHolmes.begin(), SherlockHolmes.end());
    vector<string> SherlockHolmesFrequency = WordFrequency(SherlockHolmes);
    WriteFrequency(SherlockHolmesFrequency, "SherlockHolmesFrequency.txt");

    // ------------------------------------------------------------

    // Read and Write The Adventures of Tom Sawyer frequency
    cout << "Calculating frequency for Tom Sawyer..." << endl;
    vector<string> TomSawyer = ReadWords("Books/TomSawyer.txt");
    sort(TomSawyer.begin(), TomSawyer.end());
    vector<string> TomSawyerFrequency = WordFrequency(TomSawyer);
    WriteFrequency(TomSawyerFrequency, "TomSawyerFrequency.txt");

    // ------------------------------------------------------------

    // Read and write The Brothers Karamazov frequency
    cout << "Calculating frequency for The Brothers Karamazov..." << endl;
    vector<string> BrothersKaramazov = ReadWords("Books/BrothersKaramazov.txt");
    sort(BrothersKaramazov.begin(), BrothersKaramazov.end());
    vector<string> BrothersKaramazovFrequency = WordFrequency(BrothersKaramazov);
    WriteFrequency(BrothersKaramazovFrequency, "BrothersKaramazovFrequency.txt");   

    // ------------------------------------------------------------    

    // Read and write The Great Gatsby frequency
    cout << "Calculating frequency for The Great Gatsby..." << endl;
    vector<string> GreatGatsby = ReadWords("Books/GreatGatsby.txt");
    sort(GreatGatsby.begin(), GreatGatsby.end());
    vector<string> GreatGatsbyFrequency = WordFrequency(GreatGatsby);
    WriteFrequency(GreatGatsbyFrequency, "GreatGatsbyFrequency.txt");

    return 0;
}