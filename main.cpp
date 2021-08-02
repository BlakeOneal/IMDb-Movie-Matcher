#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct movie {
    // Info for movie object, stored in csv file
    string imdbTitle, title, country, director, firstGenre;
    set<string> genre;
    set<string> countries;
    int year, duration;
    float avgVote;
    movie(string imdbTitle, string title, string director, string firstGenre, set<string> genre, set<string> countries, string currCountry, int year, int duration, float avgVote);
};

// Constructor for movie object
movie::movie(string _imdbTitle, string _title, string _director, string _firstGenre, set<string> _genre, set<string> _countries, string _currCountry, int _year, int _duration, float _avgVote) {
    imdbTitle = _imdbTitle;
    title = _title;
    director = _director;
    firstGenre = _firstGenre;
    genre = _genre;
    countries = _countries;
    country = _currCountry;
    year = _year;
    duration = _duration;
    avgVote = _avgVote;
}

// Reads info from the .csv file and creates movie objects, format specified in file
vector<movie> loadFile() {
    // loadFile code taken from Lab 7 done by myself in COP3503, adapted code to fit this project
    vector<movie> movies;
    ifstream input = ifstream("IMDb movies.csv");
    string ignore;
    getline(input, ignore);
    string data;
    while(getline(input, data)) {
        istringstream token(data);
        string tempInt, imdbTitle, title, countryList, currCountry, director, currGenre, genreList;
        int year, duration;
        float avgVote;
        set<string> genres;
        set<string> country;
        getline(token, imdbTitle, ',');

        getline(token, title, ',');

        getline(token, tempInt, ',');
        year = stoi(tempInt);

        getline(token, genreList, ',');
        if(genreList.find('|') != string::npos) {
            while(genreList.find('|') != string::npos) {
                int endIndex = 0;
                endIndex = genreList.find('|');
                currGenre = genreList.substr(0, endIndex);
                genres.insert(currGenre);
                genreList.erase(0, endIndex + 1);
            }
        }
        else {
            genres.insert(genreList);
        }

        getline(token, tempInt, ',');
        duration = stoi(tempInt);

        getline(token, countryList, ',');
        if(countryList.find('|') != string::npos) {
            while(countryList.find('|') != string::npos) {
                int endIndex = 0;
                endIndex = countryList.find('|');
                currCountry = countryList.substr(0, endIndex);
                country.insert(currCountry);
                countryList.erase(0, endIndex + 1);
            }
        }
        else {
            country.insert(countryList);
        }

        getline(token, director, ',');

        getline(token, tempInt, ',');
        avgVote = float(stof(tempInt));
        currGenre = *genres.begin();
        currCountry = *country.begin();

        // Pushes movie objects into movies vector
        movie movieToAdd = movie(imdbTitle, title, director, currGenre, genres, country, currCountry, year, duration, avgVote);
        movies.push_back(movieToAdd);
    }
    return movies;
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
int partitionYear(vector<movie>&notSorted, int low, int high){
    int pivot = notSorted[low].year;
    int up = low;
    int down = high;
    while(up < down) {
        for(int i = up; i < high; i++) {
            if(notSorted[up].year > pivot) {
                break;
            }
            up++;
        }
        for(int i = high; i > low; i--) {
            if(notSorted[down].year < pivot) {
                break;
            }
            down--;
        }
        if(up < down) {
            movie temp = notSorted[up];
            movie temp2 = notSorted[down];
            notSorted[up] = temp2;
            notSorted[down] = temp;
        }
    }
    movie temp = notSorted[low];
    movie temp2 = notSorted[down];
    notSorted[low] = temp2;
    notSorted[down] = temp;
    return down;
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
// Driver for quickSort, sorts movies by Release Year
void quickSortYear(vector<movie>&notSorted, int low, int high) {
    if(low < high) {
        int pivot = partitionYear(notSorted, low, high);
        quickSortYear(notSorted, low, pivot - 1);
        quickSortYear(notSorted, pivot + 1, high);

    }
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
int partitionDuration(vector<movie>&notSorted, int low, int high) {
    int pivot = notSorted[low].duration;
    int up = low;
    int down = high;
    while(up < down) {
        for(int i = up; i < high; i++) {
            if(notSorted[up].duration > pivot) {
                break;
            }
            up++;
        }
        for(int i = high; i > low; i--) {
            if(notSorted[down].duration < pivot) {
                break;
            }
            down--;
        }
        if(up < down) {
            movie temp = notSorted[up];
            movie temp2 = notSorted[down];
            notSorted[up] = temp2;
            notSorted[down] = temp;
        }
    }
    movie temp = notSorted[low];
    movie temp2 = notSorted[down];
    notSorted[low] = temp2;
    notSorted[down] = temp;
    return down;
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
// Driver for quickSort, sorts movies by Duration
void quickSortDuration(vector<movie>&notSorted, int low, int high){
    if(low < high) {
        int pivot = partitionDuration(notSorted, low, high);
        quickSortDuration(notSorted, low, pivot - 1);
        quickSortDuration(notSorted, pivot + 1, high);
    }
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
int partitionVote(vector<movie>&notSorted, int low, int high) {
    float pivot = notSorted[low].avgVote;
    int up = low;
    int down = high;
    while(up < down) {
        for(int i = up; i < high; i++) {
            if(notSorted[up].avgVote > pivot) {
                break;
            }
            up++;
        }
        for(int i = high; i > low; i--) {
            if(notSorted[down].avgVote < pivot) {
                break;
            }
            down--;
        }
        if(up < down) {
            movie temp = notSorted[up];
            movie temp2 = notSorted[down];
            notSorted[up] = temp2;
            notSorted[down] = temp;
        }
    }
    movie temp = notSorted[low];
    movie temp2 = notSorted[down];
    notSorted[low] = temp2;
    notSorted[down] = temp;
    return down;
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
// Driver for quickSort, sorts movies by Average User Vote
void quickSortVote(vector<movie>&notSorted, int low, int high){
    if(low < high) {
        int pivot = partitionVote(notSorted, low, high);
        quickSortVote(notSorted, low, pivot - 1);
        quickSortVote(notSorted, pivot + 1, high);
    }
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
int partitionIMDbTitle(vector<movie>&notSorted, int low, int high) {
    string pivot = notSorted[low].imdbTitle;
    int up = low;
    int down = high;
    while(up < down) {
        for(int i = up; i < high; i++) {
            if(notSorted[up].imdbTitle > pivot) {
                break;
            }
            up++;
        }
        for(int i = high; i > low; i--) {
            if(notSorted[down].imdbTitle < pivot) {
                break;
            }
            down--;
        }
        if(up < down) {
            movie temp = notSorted[up];
            movie temp2 = notSorted[down];
            notSorted[up] = temp2;
            notSorted[down] = temp;
        }
    }
    movie temp = notSorted[low];
    movie temp2 = notSorted[down];
    notSorted[low] = temp2;
    notSorted[down] = temp;
    return down;
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
// Driver for quickSort, sorts movies by IMDb ID
void quickSortIMDbTitle(vector<movie>&notSorted, int low, int high){
    if(low < high) {
        int pivot = partitionIMDbTitle(notSorted, low, high);
        quickSortIMDbTitle(notSorted, low, pivot - 1);
        quickSortIMDbTitle(notSorted, pivot + 1, high);
    }
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
int partitionTitle(vector<movie>&notSorted, int low, int high) {
    string pivot = notSorted[low].title;
    int up = low;
    int down = high;
    while(up < down) {
        for(int i = up; i < high; i++) {
            if(notSorted[up].title > pivot) {
                break;
            }
            up++;
        }
        for(int i = high; i > low; i--) {
            if(notSorted[down].title < pivot) {
                break;
            }
            down--;
        }
        if(up < down) {
            movie temp = notSorted[up];
            movie temp2 = notSorted[down];
            notSorted[up] = temp2;
            notSorted[down] = temp;
        }
    }
    movie temp = notSorted[low];
    movie temp2 = notSorted[down];
    notSorted[low] = temp2;
    notSorted[down] = temp;
    return down;
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
// Driver for quickSort, sorts movies by Title
void quickSortTitle(vector<movie>&notSorted, int low, int high){
    if(low < high) {
        int pivot = partitionTitle(notSorted, low, high);
        quickSortTitle(notSorted, low, pivot - 1);
        quickSortTitle(notSorted, pivot + 1, high);
    }
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
int partitionGenre(vector<movie>&notSorted, int low, int high) {
    string pivot = notSorted[low].firstGenre;
    int up = low;
    int down = high;
    while(up < down) {
        for(int i = up; i < high; i++) {
            if(notSorted[up].firstGenre > pivot) {
                break;
            }
            up++;
        }
        for(int i = high; i > low; i--) {
            if(notSorted[down].firstGenre < pivot) {
                break;
            }
            down--;
        }
        if(up < down) {
            movie temp = notSorted[up];
            movie temp2 = notSorted[down];
            notSorted[up] = temp2;
            notSorted[down] = temp;
        }
    }
    movie temp = notSorted[low];
    movie temp2 = notSorted[down];
    notSorted[low] = temp2;
    notSorted[down] = temp;
    return down;
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
// Driver for quickSort, sorts movies by genre, note, genre is a set, sorts by first element in the movie's set
void quickSortGenre(vector<movie>&notSorted, int low, int high){
    if(low < high) {
        int pivot = partitionGenre(notSorted, low, high);
        quickSortGenre(notSorted, low, pivot - 1);
        quickSortGenre(notSorted, pivot + 1, high);
    }
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
int partitionCountry(vector<movie>&notSorted, int low, int high) {
    string pivot = notSorted[low].country;
    int up = low;
    int down = high;
    while(up < down) {
        for(int i = up; i < high; i++) {
            if(notSorted[up].country > pivot) {
                break;
            }
            up++;
        }
        for(int i = high; i > low; i--) {
            if(notSorted[down].country < pivot) {
                break;
            }
            down--;
        }
        if(up < down) {
            movie temp = notSorted[up];
            movie temp2 = notSorted[down];
            notSorted[up] = temp2;
            notSorted[down] = temp;
        }
    }
    movie temp = notSorted[low];
    movie temp2 = notSorted[down];
    notSorted[low] = temp2;
    notSorted[down] = temp;
    return down;
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
// Driver for quickSort, sorts movies by country, note, country is a set, sorts based on first country in movie's set
void quickSortCountry(vector<movie>&notSorted, int low, int high){
    if(low < high) {
        int pivot = partitionCountry(notSorted, low, high);
        quickSortCountry(notSorted, low, pivot - 1);
        quickSortCountry(notSorted, pivot + 1, high);
    }
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
int partitionDirector(vector<movie>&notSorted, int low, int high) {
    string pivot = notSorted[low].director;
    int up = low;
    int down = high;
    while(up < down) {
        for(int i = up; i < high; i++) {
            if(notSorted[up].director > pivot) {
                break;
            }
            up++;
        }
        for(int i = high; i > low; i--) {
            if(notSorted[down].director < pivot) {
                break;
            }
            down--;
        }
        if(up < down) {
            movie temp = notSorted[up];
            movie temp2 = notSorted[down];
            notSorted[up] = temp2;
            notSorted[down] = temp;
        }
    }
    movie temp = notSorted[low];
    movie temp2 = notSorted[down];
    notSorted[low] = temp2;
    notSorted[down] = temp;
    return down;
}
// Code taken from slides given by Amanpreet Kapoor on Quicksort Algorithm Code
// Driver for quickSort, sorts movies by director
void quickSortDirector(vector<movie>&notSorted, int low, int high){
    if(low < high) {
        int pivot = partitionDirector(notSorted, low, high);
        quickSortDirector(notSorted, low, pivot - 1);
        quickSortDirector(notSorted, pivot + 1, high);
    }
}
// Sorts movies by Year using cocktail sort
void cocktailSortYear(vector<movie>&notSorted) {
    // General code for bubble sort adapted from Amanpreet Kapoor's slides on bubble sort
    bool swapDone = true;
    while(swapDone) {
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = 0; i < notSorted.size() - 1; i++) {
            if(notSorted[i].year > notSorted[i + 1].year) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
        // Idea for a bool value taken from Amanpreet Kapoor's slides, makes code more efficient
        if(!swapDone) {
            break;
        }
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = notSorted.size() - 2; i >= 0; i--) {
            if(notSorted[i + 1].year < notSorted[i].year) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
    }
}
// Sorts movies by Duration using cocktail sort
void cocktailSortDuration(vector<movie>&notSorted) {
    // General code for bubble sort adapted from Amanpreet Kapoor's slides on bubble sort
    bool swapDone = true;
    while(swapDone) {
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = 0; i < notSorted.size() - 1; i++) {
            if(notSorted[i].duration > notSorted[i + 1].duration) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
        // Idea for a bool value taken from Amanpreet Kapoor's slides, makes code more efficient
        if(!swapDone) {
            break;
        }
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = notSorted.size() - 2; i >= 0; i--) {
            if(notSorted[i + 1].duration < notSorted[i].duration) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
    }
}
// Sorts movies by Avg. User Vote using cocktail sort
void cocktailSortVote(vector<movie>&notSorted) {
    // General code for bubble sort adapted from Amanpreet Kapoor's slides on bubble sort
    bool swapDone = true;
    while(swapDone) {
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = 0; i < notSorted.size() - 1; i++) {
            if(notSorted[i].avgVote > notSorted[i + 1].avgVote) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
        // Idea for a bool value taken from Amanpreet Kapoor's slides, makes code more efficient
        if(!swapDone) {
            break;
        }
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = notSorted.size() - 2; i >= 0; i--) {
            if(notSorted[i + 1].avgVote < notSorted[i].avgVote) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
    }
}
// Sorts movies by IMDb ID using cocktail sort
void cocktailSortIMDbTitle(vector<movie>&notSorted) {
    // General code for bubble sort adapted from Amanpreet Kapoor's slides on bubble sort
    bool swapDone = true;
    while(swapDone) {
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = 0; i < notSorted.size() - 1; i++) {
            if(notSorted[i].imdbTitle > notSorted[i + 1].imdbTitle) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
        // Idea for a bool value taken from Amanpreet Kapoor's slides, makes code more efficient
        if(!swapDone) {
            break;
        }
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = notSorted.size() - 2; i >= 0; i--) {
            if(notSorted[i + 1].imdbTitle < notSorted[i].imdbTitle) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
    }
}
// Sorts movies by Title using cocktail sort
void cocktailSortTitle(vector<movie>&notSorted) {
    // General code for bubble sort adapted from Amanpreet Kapoor's slides on bubble sort
    bool swapDone = true;
    while(swapDone) {
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = 0; i < notSorted.size() - 1; i++) {
            if(notSorted[i].title > notSorted[i + 1].title) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
        // Idea for a bool value taken from Amanpreet Kapoor's slides, makes code more efficient
        if(!swapDone) {
            break;
        }
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = notSorted.size() - 2; i >= 0; i--) {
            if(notSorted[i + 1].title < notSorted[i].title) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
    }
}
// Sorts movies by Genre using cocktail sort, same note applies here from quickSortGenre
void cocktailSortGenre(vector<movie>&notSorted) {
    // General code for bubble sort adapted from Amanpreet Kapoor's slides on bubble sort
    bool swapDone = true;
    while(swapDone) {
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = 0; i < notSorted.size() - 1; i++) {
            if(notSorted[i].firstGenre > notSorted[i + 1].firstGenre) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
        // Idea for a bool value taken from Amanpreet Kapoor's slides, makes code more efficient
        if(!swapDone) {
            break;
        }
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = notSorted.size() - 2; i >= 0; i--) {
            if(notSorted[i + 1].firstGenre < notSorted[i].firstGenre) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
    }
}
// Sorts movies by Country using cocktail sort, same note applies here from quickSortCountry
void cocktailSortCountry(vector<movie>&notSorted) {
    // General code for bubble sort adapted from Amanpreet Kapoor's slides on bubble sort
    bool swapDone = true;
    while(swapDone) {
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = 0; i < notSorted.size() - 1; i++) {
            if(notSorted[i].country > notSorted[i + 1].country) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
        // Idea for a bool value taken from Amanpreet Kapoor's slides, makes code more efficient
        if(!swapDone) {
            break;
        }
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = notSorted.size() - 2; i >= 0; i--) {
            if(notSorted[i + 1].country < notSorted[i].country) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
    }
}
// Sorts movies by Director using cocktail sort
void cocktailSortDirector(vector<movie>&notSorted) {
    // General code for bubble sort adapted from Amanpreet Kapoor's slides on bubble sort
    bool swapDone = true;
    while(swapDone) {
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = 0; i < notSorted.size() - 1; i++) {
            if(notSorted[i].director > notSorted[i + 1].director) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
        // Idea for a bool value taken from Amanpreet Kapoor's slides, makes code more efficient
        if(!swapDone) {
            break;
        }
        // Set swapDone to false to see if there were any forward-phase swaps done, if not, vector is sorted
        swapDone = false;
        for(int i = notSorted.size() - 2; i >= 0; i--) {
            if(notSorted[i + 1].director < notSorted[i].director) {
                movie temp1 = notSorted[i];
                movie temp2 = notSorted[i + 1];
                notSorted[i] = temp2;
                notSorted[i + 1] = temp1;
                swapDone = true;
            }
        }
    }
}

int main() {
    // Welcome message
    cout << "Welcome to the IMDb Database!" << endl;
    cout << "=============================" << endl;
    cout << "Loading files...";
    vector<movie> movieObjects = loadFile();
    vector<movie> sortOne, sortTwo;
    cout << "\n" << "\n" << "Files loaded! " << movieObjects.size() << " Movies Within Our Repository!" << endl;
    cout << "\n" << "If you would like to View the Details on a Specific Movie, please type 'Y'" << endl;
    int desiredLength, desiredYear;
    float desiredScore;
    string desiredGenre, desiredTitle, desiredDirector, desiredCountry;
    char option;
    cin >> option;
    cin.ignore();
    // Search algorithm for the movie specified
    while(option == 'Y') {
        cout << "What is the Name of the Movie you would like to View Details about? **Note: Names are Case Sensitive**" << endl;
        getline(cin, desiredTitle);
        bool found = false;
        for (int i = 0; i < movieObjects.size(); i++) {
            string stringToCompare = movieObjects[i].title;
            if (stringToCompare.compare(desiredTitle) == 0) {
                found = true;
                cout << "IMDb ID: " << movieObjects[i].imdbTitle << "\n" << "Title: " << movieObjects[i].title
                     << "\n" << "Year: " << movieObjects[i].year << "\n" << "Genre: ";
                for (auto iter = movieObjects[i].genre.begin(); iter != movieObjects[i].genre.end(); iter++) {
                    cout << *iter << " ";
                }
                cout << "\n" << "Duration (Minutes): " << movieObjects[i].duration << "\n" << "Premiere Countries: ";
                for (auto iter = movieObjects[i].countries.begin();
                     iter != movieObjects[i].countries.end(); iter++) {
                    cout << *iter << " ";
                }
                cout << "\n" << "Director: " << movieObjects[i].director << "\n" << "IMDb Rating: "
                     << movieObjects[i].avgVote << "\n" << endl;
            }
        }
        // Movie not present
        if(!found) {
            cout << "We couldn't Find a Movie with that Name... Please try again." << endl;
        }
        cout << "Would you like to Search for Another Movie? If so, please type 'Y'" << endl;
        cin >> option;
        cin.ignore();
    }
    // Driver for IMDb movie matcher
    char option2;
    cout << "If you would like to use the IMDb Movie Matcher, please type 'Y'" << endl;
    cin >> option2;
    cin.ignore();
    // IMDb movie matcher code
    while(option2 == 'Y') {
        cout << "Welcome to the IMDb Movie Matcher! Please Follow the Instructions so we can Match you with the best Movie Possible!" << endl;
        cout << "What is the Maximum Length, in Minutes, of a Movie that you would Watch?" << endl;
        cin >> desiredLength;
        // Subsets of movie objects based on specified criteria given by User Input
        vector<movie> possibleMatchesDuration, possibleMatchesGenre, possibleMatchesYear, possibleMatchesCountry, possibleMatchesRating, perfectMatches;
        for (int i = 0; i < movieObjects.size(); i++) {
            if (movieObjects[i].duration <= desiredLength) {
                possibleMatchesDuration.push_back(movieObjects[i]);
            }
        }
        cout << "Next, what Genre Would you Like? *Please capitalize the First Letter to Ensure that our Algorithm Works Properly.*" << endl;
        cin >> desiredGenre;
        for (int i = 0; i < possibleMatchesDuration.size(); i++) {
            set<string> genres = possibleMatchesDuration[i].genre;
            if (genres.find(desiredGenre) != genres.end()) {
                possibleMatchesGenre.push_back(possibleMatchesDuration[i]);
            }
        }
        cout << "Alright, we Have Some Data... but we Need More!" << "\n"
             << "What is the Lowest Possible Critic Rating of a Movie that you would Watch?" << endl;
        cin >> desiredScore;
        for (int i = 0; i < possibleMatchesGenre.size(); i++) {
            if (possibleMatchesGenre[i].avgVote >= desiredScore) {
                possibleMatchesRating.push_back(possibleMatchesGenre[i]);
            }
        }

        cout << "What about the Oldest Release Year you would Watch?" << endl;
        cin >> desiredYear;
        for (int i = 0; i < possibleMatchesRating.size(); i++) {
            if (possibleMatchesRating[i].year >= desiredYear) {
                possibleMatchesYear.push_back(possibleMatchesRating[i]);
            }
        }

        cout << "What Country would you like your Movie to have Premiered in?" << endl;
        cin >> desiredCountry;
        for (int i = 0; i < possibleMatchesYear.size(); i++) {
            set<string> countries = possibleMatchesYear[i].countries;
            if (countries.find(desiredCountry) != countries.end()) {
                perfectMatches.push_back(possibleMatchesYear[i]);
            }
        }
        // Displays movies if there are perfect matches
        int matchesShown = 0;
        if(perfectMatches.empty()) {
            // No perfect matches present, users encouraged to try again
            cout << "We were Unfortunately Unable to Find any Matching Movies... Please Retry!" << endl;
        }
        else {
            cout << "We were able to find " << perfectMatches.size() << " Matching Movies for you!" << endl;
            if(matchesShown == 0 && perfectMatches.size() >= 10) {
                cout << "Displaying first 10 Matches... " << endl;
            }
            else if(matchesShown == 0) {
                cout << "Displaying all " << perfectMatches.size() << " Matching Movies for you!" << endl;
            }
            int count = 0;
            for (int i = matchesShown; i < perfectMatches.size(); i++) {
                if(count != 10) {
                    cout << "IMDb ID: " << perfectMatches[i].imdbTitle << "\n" << "Title: " << perfectMatches[i].title
                         << "\n" << "Year: " << perfectMatches[i].year << "\n" << "Genre: ";
                    for (auto iter = perfectMatches[i].genre.begin(); iter != perfectMatches[i].genre.end(); iter++) {
                        cout << *iter << " ";
                    }
                    cout << "\n" << "Duration (Minutes): " << perfectMatches[i].duration << "\n" << "Premiere Countries: ";
                    for (auto iter = perfectMatches[i].countries.begin();
                         iter != perfectMatches[i].countries.end(); iter++) {
                        cout << *iter << " ";
                    }
                    cout << "\n" << "Director: " << perfectMatches[i].director << "\n" << "IMDb Rating: "
                         << perfectMatches[i].avgVote << "\n" << endl;
                    matchesShown++;
                    count++;
                }
            }
            char option3 = 'Y';
            while(option3 == 'Y' && matchesShown != perfectMatches.size()) {
                cout << "If you would like to see the next 10 matches, please type 'Y'" << endl;
                cin >> option3;
                if(option3 != 'Y') {
                    break;
                }
                cout << "\n" << "Showing next 10 matches..." << endl;
                count = 0;
                for (int i = matchesShown; i < perfectMatches.size(); i++) {
                    if(count != 10) {
                        cout << "IMDb ID: " << perfectMatches[i].imdbTitle << "\n" << "Title: " << perfectMatches[i].title
                             << "\n" << "Year: " << perfectMatches[i].year << "\n" << "Genre: ";
                        for (auto iter = perfectMatches[i].genre.begin(); iter != perfectMatches[i].genre.end(); iter++) {
                            cout << *iter << " ";
                        }
                        cout << "\n" << "Duration (Minutes): " << perfectMatches[i].duration << "\n" << "Premiere Countries: ";
                        for (auto iter = perfectMatches[i].countries.begin();
                             iter != perfectMatches[i].countries.end(); iter++) {
                            cout << *iter << " ";
                        }
                        cout << "\n" << "Director: " << perfectMatches[i].director << "\n" << "IMDb Rating: "
                             << perfectMatches[i].avgVote << "\n" << endl;
                        matchesShown++;
                        count++;
                    }
                }
            }
        }
        sortOne = perfectMatches;
        sortTwo = perfectMatches;
        cout << "If the List was too Long, we Encourage you to Refine your Answers and Retry!" << endl;
        cout << "Would you like to use the IMDb Movie Matcher again? Enter 'Y' if you would like to" << endl;
        cin >> option2;
        cin.ignore();
    }
    // Sorting algorithm portion
    cout << "Next, we will demonstrate the difference between Quick Sort and Cocktail Sort using the Perfect Matches generated by the IMDb Movie Matcher." << endl;
    cout << "\n" << "What Would You Like to Sort the Movies by?" << endl;
    cout << "\n 1. IMDb ID \n 2. Title \n 3. Genre \n 4. Country \n 5. Director \n 6. Year Released \n 7. Duration \n 8. Average User Score \n 0. Exit \n";
    int userOption;
    cin >> userOption;
    if(sortOne.empty()) {
        sortOne = movieObjects;
        sortTwo = movieObjects;
    }
    time_point<steady_clock> startTime1, startTime2, endTime1, endTime2;
    nanoseconds timeForQuickSort, timeForCocktailSort;
    string option3 = "Temp";
    while(userOption != 0) {
    switch (userOption) {
        // Sorts by IMDb ID
        case 1:
            cout << "Sorting by IMDb ID..." << endl;
            // Timing the code was adapted from https://www.cplusplus.com/reference/chrono/
            startTime1 = high_resolution_clock::now();
            quickSortDuration(sortOne, 0, sortOne.size() - 1);
            quickSortIMDbTitle(sortOne, 0, sortOne.size() - 1);
            endTime1 = high_resolution_clock::now();
            timeForQuickSort = duration_cast<nanoseconds>(endTime1 - startTime1);
            cout << "Time for Quick Sort: " << timeForQuickSort.count() << " nanoseconds" << endl;
            startTime2 = high_resolution_clock::now();
            cocktailSortIMDbTitle(sortTwo);
            endTime2 = high_resolution_clock::now();
            timeForCocktailSort = duration_cast<nanoseconds>(endTime2 - startTime2);
            cout << "Time for Cocktail Sort: " << timeForCocktailSort.count() << " nanoseconds" << endl;
            cout << "\n" << "Would you like to display the sorted IMDb IDs? If you would, Please Type 'Y'" << endl;
            cin.ignore();
            getline(cin, option3);
            cout << option3 << endl;
            if(option3 == "Y") {
                cout << "\n" << "Displaying sorted IMDb IDs..." << endl;
                cout << "\n" << "Sorted IMDb IDs by Quick Sort: " << "\n" << "================================" << endl;
                for(int i = 0; i < sortOne.size(); i++) {
                    cout << sortOne[i].imdbTitle << " ";
                }
                cout << "\n" << "Sorted IMDb IDs by Cocktail Sort: " << "\n" << "================================" << endl;
                for(int j = 0; j < sortTwo.size(); j++) {
                    cout << sortTwo[j].imdbTitle << " ";
                }
            }
            break;
            // Sorts by Title
        case 2:
            cout << "Sorting by Movie Title..." << endl;
            startTime1 = high_resolution_clock::now();
            quickSortTitle(sortOne, 0, sortOne.size() - 1);
            endTime1 = high_resolution_clock::now();
            timeForQuickSort = duration_cast<nanoseconds>(endTime1 - startTime1);
            cout << "Time for Quick Sort: " << timeForQuickSort.count() << " nanoseconds" << endl;
            startTime2 = high_resolution_clock::now();
            cocktailSortTitle(sortTwo);
            endTime2 = high_resolution_clock::now();
            timeForCocktailSort = duration_cast<nanoseconds>(endTime2 - startTime2);
            cout << "Time for Cocktail Sort: " << timeForCocktailSort.count() << " nanoseconds" << endl;
            cout << "\n" << "Would you like to display the sorted Movie Titles? If you would, Please Type 'Y'" << endl;
            cin.ignore();
            getline(cin, option3);
            cout << option3 << endl;
            if(option3 == "Y") {
                cout << "\n" << "Displaying sorted Movie Titles..." << endl;
                cout << "\n" << "Sorted Movie Titles by Quick Sort: " << "\n" << "================================" << endl;
                for(int i = 0; i < sortOne.size(); i++) {
                    cout << sortOne[i].title << " ";
                }
                cout << "\n" << "Sorted Movie Titles by Cocktail Sort: " << "\n" << "================================" << endl;
                for(int j = 0; j < sortTwo.size(); j++) {
                    cout << sortTwo[j].title << " ";
                }
            }
            break;
            // Sorts by Genre
        case 3:
            cout << "Sorting by Genre..." << endl;
            startTime1 = high_resolution_clock::now();
            quickSortGenre(sortOne, 0, sortOne.size() - 1);
            endTime1 = high_resolution_clock::now();
            timeForQuickSort = duration_cast<nanoseconds>(endTime1 - startTime1);
            cout << "Time for Quick Sort: " << timeForQuickSort.count() << " nanoseconds" << endl;
            startTime2 = high_resolution_clock::now();
            cocktailSortGenre(sortTwo);
            endTime2 = high_resolution_clock::now();
            timeForCocktailSort = duration_cast<nanoseconds>(endTime2 - startTime2);
            cout << "Time for Cocktail Sort: " << timeForCocktailSort.count() << " nanoseconds" << endl;
            cout << "\n" << "Would you like to display the sorted Genres? If you would, Please Type 'Y'" << endl;
            cin.ignore();
            getline(cin, option3);
            cout << option3 << endl;
            if(option3 == "Y") {
                cout << "\n" << "Displaying sorted Genres..." << endl;
                cout << "\n" << "Sorted Genres by Quick Sort: " << "\n" << "================================" << endl;
                for(int i = 0; i < sortOne.size(); i++) {
                    set<string> genreList = sortOne[i].genre;
                    if(genreList.size() > 1) {
                        for(auto iter = genreList.begin(); iter != genreList.end(); iter++) {
                            cout << *iter << ", ";
                        }
                    }
                    else {
                        cout << sortOne[i].firstGenre;
                    }
                    cout << "| ";
                }
                cout << "\n" << "Sorted Genres by Cocktail Sort: " << "\n" << "================================" << endl;
                for(int j = 0; j < sortTwo.size(); j++) {
                    set<string> genreList = sortTwo[j].genre;
                    if(genreList.size() > 1) {
                        for(auto iter = genreList.begin(); iter != genreList.end(); iter++) {
                            cout << *iter << ", ";
                        }
                    }
                    else {
                        cout << sortTwo[j].firstGenre;
                    }
                    cout << "| ";
                }
            }
            break;
        case 4:
            // Sorts by Country
            cout << "Sorting by Country..." << endl;
            startTime1 = high_resolution_clock::now();
            quickSortCountry(sortOne, 0, sortOne.size() - 1);
            endTime1 = high_resolution_clock::now();
            timeForQuickSort = duration_cast<nanoseconds>(endTime1 - startTime1);
            cout << "Time for Quick Sort: " << timeForQuickSort.count() << " nanoseconds" << endl;
            startTime2 = high_resolution_clock::now();
            cocktailSortCountry(sortTwo);
            endTime2 = high_resolution_clock::now();
            timeForCocktailSort = duration_cast<nanoseconds>(endTime2 - startTime2);
            cout << "Time for Cocktail Sort: " << timeForCocktailSort.count() << " nanoseconds" << endl;
            cout << "\n" << "Would you like to display the sorted Countries? If you would, Please Type 'Y'" << endl;
            cin.ignore();
            getline(cin, option3);
            cout << option3 << endl;
            if(option3 == "Y") {
                cout << "\n" << "Displaying sorted Countries..." << endl;
                cout << "\n" << "Sorted Countries by Quick Sort: " << "\n" << "================================" << endl;
                for(int i = 0; i < sortOne.size(); i++) {
                    set<string> countryList = sortOne[i].countries;
                    if(countryList.size() > 1) {
                        for(auto iter = countryList.begin(); iter != countryList.end(); iter++) {
                            cout << *iter << ", ";
                        }
                    }
                    else {
                        cout << sortOne[i].country;
                    }
                    cout << "| ";
                }
                cout << "\n" << "Sorted Countries by Cocktail Sort: " << "\n" << "================================" << endl;
                for(int j = 0; j < sortTwo.size(); j++) {
                    set<string> countryList = sortTwo[j].countries;
                    if(countryList.size() > 1) {
                        for(auto iter = countryList.begin(); iter != countryList.end(); iter++) {
                            cout << *iter << ", ";
                        }
                    }
                    else {
                        cout << sortTwo[j].country;
                    }
                    cout << "| ";
                }
            }
            break;
        case 5:
            // Sorts by Director
            cout << "Sorting by Director..." << endl;
            startTime1 = high_resolution_clock::now();
            quickSortDirector(sortOne, 0, sortOne.size() - 1);
            endTime1 = high_resolution_clock::now();
            timeForQuickSort = duration_cast<nanoseconds>(endTime1 - startTime1);
            cout << "Time for Quick Sort: " << timeForQuickSort.count() << " nanoseconds" << endl;
            startTime2 = high_resolution_clock::now();
            cocktailSortDirector(sortTwo);
            endTime2 = high_resolution_clock::now();
            timeForCocktailSort = duration_cast<nanoseconds>(endTime2 - startTime2);
            cout << "Time for Cocktail Sort: " << timeForCocktailSort.count() << " nanoseconds" << endl;
            cout << "\n" << "Would you like to display the sorted Directors? If you would, Please Type 'Y'" << endl;
            cin.ignore();
            getline(cin, option3);
            cout << option3 << endl;
            if(option3 == "Y") {
                cout << "\n" << "Displaying sorted Directors..." << endl;
                cout << "\n" << "Sorted Directors by Quick Sort: " << "\n" << "================================" << endl;
                for(int i = 0; i < sortOne.size(); i++) {
                    cout << sortOne[i].director << " ";
                }
                cout << "\n" << "Sorted Directors by Cocktail Sort: " << "\n" << "================================" << endl;
                for(int j = 0; j < sortTwo.size(); j++) {
                    cout << sortTwo[j].director << " ";
                }
            }
            break;
        case 6:
            // Sorts by Year Released
            cout << "Sorting by Year Released..." << endl;
            startTime1 = high_resolution_clock::now();
            quickSortYear(sortOne, 0, sortOne.size() - 1);
            endTime1 = high_resolution_clock::now();
            timeForQuickSort = duration_cast<nanoseconds>(endTime1 - startTime1);
            cout << "Time for Quick Sort: " << timeForQuickSort.count() << " nanoseconds" << endl;
            startTime2 = high_resolution_clock::now();
            cocktailSortYear(sortTwo);
            endTime2 = high_resolution_clock::now();
            timeForCocktailSort = duration_cast<nanoseconds>(endTime2 - startTime2);
            cout << "Time for Cocktail Sort: " << timeForCocktailSort.count() << " nanoseconds" << endl;
            cout << "\n" << "Would you like to display the sorted Release Years? If you would, Please Type 'Y'" << endl;
            cin.ignore();
            getline(cin, option3);
            cout << option3 << endl;
            if(option3 == "Y") {
                cout << "\n" << "Displaying sorted Release Years..." << endl;
                cout << "\n" << "Sorted Release Years by Quick Sort: " << "\n" << "================================" << endl;
                for(int i = 0; i < sortOne.size(); i++) {
                    cout << sortOne[i].year << " ";
                }
                cout << "\n" << "Sorted Release Years by Cocktail Sort: " << "\n" << "================================" << endl;
                for(int j = 0; j < sortTwo.size(); j++) {
                    cout << sortTwo[j].year << " ";
                }
            }
            break;
        case 7:
            // Sorts by Duration
            cout << "Sorting by Duration (Minutes)..." << endl;
            startTime1 = high_resolution_clock::now();
            quickSortDuration(sortOne, 0, sortOne.size() - 1);
            endTime1 = high_resolution_clock::now();
            timeForQuickSort = duration_cast<nanoseconds>(endTime1 - startTime1);
            cout << "Time for Quick Sort: " << timeForQuickSort.count() << " nanoseconds" << endl;
            startTime2 = high_resolution_clock::now();
            cocktailSortDuration(sortTwo);
            endTime2 = high_resolution_clock::now();
            timeForCocktailSort = duration_cast<nanoseconds>(endTime2 - startTime2);
            cout << "Time for Cocktail Sort: " << timeForCocktailSort.count() << " nanoseconds" << endl;
            cout << "\n" << "Would you like to display the sorted Movie Durations? If you would, Please Type 'Y'" << endl;
            cin.ignore();
            getline(cin, option3);
            cout << option3 << endl;
            if(option3 == "Y") {
                cout << "\n" << "Displaying sorted Movie Durations..." << endl;
                cout << "\n" << "Sorted Movie Durations by Quick Sort: " << "\n" << "================================" << endl;
                for(int i = 0; i < sortOne.size(); i++) {
                    cout << sortOne[i].duration << " ";
                }
                cout << "\n" << "Sorted Movie Durations by Cocktail Sort: " << "\n" << "================================" << endl;
                for(int j = 0; j < sortTwo.size(); j++) {
                    cout << sortTwo[j].duration << " ";
                }
            }
            break;
        case 8:
            // Sorts by Average User Vote from IMDb
            cout << "Sorting by Average User Vote..." << endl;
            startTime1 = high_resolution_clock::now();
            quickSortVote(sortOne, 0, sortOne.size() - 1);
            endTime1 = high_resolution_clock::now();
            timeForQuickSort = duration_cast<nanoseconds>(endTime1 - startTime1);
            cout << "Time for Quick Sort: " << timeForQuickSort.count() << " nanoseconds" << endl;
            startTime2 = high_resolution_clock::now();
            cocktailSortVote(sortTwo);
            endTime2 = high_resolution_clock::now();
            timeForCocktailSort = duration_cast<nanoseconds>(endTime2 - startTime2);
            cout << "Time for Cocktail Sort: " << timeForCocktailSort.count() << " nanoseconds" << endl;
            cout << "\n" << "Would you like to display the sorted User Ratings? If you would, Please Type 'Y'" << endl;
            cin.ignore();
            getline(cin, option3);
            cout << option3 << endl;
            if(option3 == "Y") {
                cout << "\n" << "Displaying sorted Movie User Ratings..." << endl;
                cout << "\n" << "Sorted Movie User Ratings by Quick Sort: " << "\n" << "================================" << endl;
                for(int i = 0; i < sortOne.size(); i++) {
                    cout << sortOne[i].avgVote << " ";
                }
                cout << "\n" << "Sorted Movie User Ratings by Cocktail Sort: " << "\n" << "================================" << endl;
                for(int j = 0; j < sortTwo.size(); j++) {
                    cout << sortTwo[j].avgVote << " ";
                }
            }
            break;
            // Exit Sequence
        case 0:
            break;
        default:
            // Default option for invalid input
            cout << "That is not a valid option! Please enter a valid value!" << endl;
    }
    // Loop menu while !exit
        cout << "\n" << "\n" << "What Would You Like to Sort the Movies by?" << endl;
        cout << "\n 1. IMDb ID \n 2. Title \n 3. Genre \n 4. Country \n 5. Director \n 6. Year Released \n 7. Duration \n 8. Average User Score \n 0. Exit \n";
        cin >> userOption;
    }
// Exit message
    cout << "\n" << "Thank you for using the IMDb Movie Database. Have a Great Day! :)";
        return 0;
}
