/*
 * Program: TravelGo Hotel Review & Membership System
 * Assignment: CCA101 Report-Based Assessment
 * Description: Manages user profiles and reviews using Parallel Arrays.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// --- CONSTANTS ---
// Defines the maximum capacity for the arrays to avoid dynamic memory
const int MAX_USERS = 100;
const int MAX_REVIEWS = 500;

// --- FUNCTION PROTOTYPES ---
void loadData(string uID[], string uName[], string uCountry[], string uState[], string uEmail[], string uCat[], int uPoints[], int &uCount,
              string rUID[], int rRating[], string rStmt[], string rHotel[], int &rCount);
void saveData(const string uID[], const string uName[], const string uCountry[], const string uState[], const string uEmail[], const string uCat[], const int uPoints[], int uCount,
              const string rUID[], const int rRating[], const string rStmt[], const string rHotel[], int rCount);
string determineCategory(int points);
int countWords(string text);

// View Functions
void displayUserReviews(string targetUID, const string rUID[], const string rStmt[], const string rHotel[], const int rRating[], int rCount);
void displayHotelReviews(string targetHotel, const string rHotel[], const int rRating[], const string rStmt[], int rCount);
void displayAllUsers(const string uID[], const string uName[], const string uCountry[], const string uState[], const string uEmail[], const string uCat[], const int uPoints[], int uCount);
void displaySummary(int uCount, int rCount, const int uPoints[]);
void displayPositiveReviews(string targetHotel, const string rHotel[], const int rRating[], const string rStmt[], int rCount);
void displayUsersByCategory(const string uID[], const string uName[], const string uCat[], int uCount);
void displayHotelRatingSummary(const string rHotel[], const int rRating[], int rCount);

// Action Functions
void displayTopReviewers(const string uID[], const string uName[], const string rUID[], int uCount, int rCount);
void addNewReview(string rUID[], int rRating[], string rStmt[], string rHotel[], int &rCount,
                  string uID[], int uPoints[], string uCat[], int uCount);

// Additional features Functions
void searchReviewsByKeyword(string keyword, const string rStmt[], const string rHotel[], const int rRating[], int rCount);
void displayTopUsersByPoints(const string uID[], const string uName[], const int uPoints[], const string uCat[], int uCount);
void displayHotelsByPopularity(const string rHotel[], int rCount);

// --- MAIN FUNCTION ---
int main() {
    // 1. Parallel Arrays for Users
    string uIDs[MAX_USERS], uNames[MAX_USERS], uCountries[MAX_USERS], uStates[MAX_USERS], uEmails[MAX_USERS], uCategories[MAX_USERS];
    int uPoints[MAX_USERS];
    int userCount = 0; // Tracks actual number of users loaded

    // 2. Parallel Arrays for Reviews
    string rUserIDs[MAX_REVIEWS], rStatements[MAX_REVIEWS], rHotels[MAX_REVIEWS];
    int rRatings[MAX_REVIEWS];
    int reviewCount = 0; // Tracks actual number of reviews loaded

    // 3. Load Data ONCE at startup
    loadData(uIDs, uNames, uCountries, uStates, uEmails, uCategories, uPoints, userCount,
             rUserIDs, rRatings, rStatements, rHotels, reviewCount);

    int choice;
    do {
        // Display Menu Interface
        cout << "\n";
        cout << "\t ............................................\n";
        cout << "\t :                TRAVELGO                  :\n";
        cout << "\t :     Hotel Review & Membership System     :\n";
        cout << "\t :..........................................:\n";
        cout << "\t :                                          :\n";
        cout << "\t :   [ VIEW DATA ]                          :\n";
        cout << "\t :   1. Display All Users                   :\n";
        cout << "\t :   2. Search Reviews by User ID           :\n";
        cout << "\t :   3. Search Reviews by Hotel Name        :\n";
        cout << "\t :   4. Filter: Positive Reviews (4-5*)     :\n";
        cout << "\t :                                          :\n";
        cout << "\t :   [ STATISTICS ]                         :\n";
        cout << "\t :   5. System Summary (Stats)              :\n";
        cout << "\t :   6. Users by Membership Tier            :\n";
        cout << "\t :   7. Hotel Rating Summary                :\n";
        cout << "\t :   8. Top 3 Reviewers (By Count)          :\n";
        cout << "\t :                                          :\n";
        cout << "\t :   [ ACTION ]                             :\n";
        cout << "\t :   9. Add New Review                      :\n";
        cout << "\t :                                          :\n";
        cout << "\t :   [ ADDITIONAL FEATURES ]                :\n";
        cout << "\t :   10. Keyword Search (Review Text)       :\n";
        cout << "\t :   11. Leaderboard (By Points)            :\n";
        cout << "\t :   12. Most Popular Hotels                :\n";
        cout << "\t :   13. Save & Exit                        :\n";
        cout << "\t :..........................................:\n";
        cout << "\n";
        cout << "\t >> Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }  else {
            cin.ignore(10000, '\n');
        }

        string inputID, inputHotel, inputKeyword;

        switch(choice) {
            case 1:
                displayAllUsers(uIDs, uNames, uCountries, uStates, uEmails, uCategories, uPoints, userCount);
                break;
            case 2:
                cout << "Enter User ID to search (e.g., U001): ";
                getline(cin, inputID);
                displayUserReviews(inputID, rUserIDs, rStatements, rHotels, rRatings, reviewCount);
                break;
            case 3:
                cout << "Enter Hotel Name to search (e.g., GreenLeaf Hotel): ";
                getline(cin, inputHotel);
                displayHotelReviews(inputHotel, rHotels, rRatings, rStatements, reviewCount);
                break;
            case 4:
                cout << "Enter Hotel Name for Positive Reviews: ";
                getline(cin, inputHotel);
                displayPositiveReviews(inputHotel, rHotels, rRatings, rStatements, reviewCount);
                break;
            case 5:
                displaySummary(userCount, reviewCount, uPoints);
                break;
            case 6:
                displayUsersByCategory(uIDs, uNames, uCategories, userCount);
                break;
            case 7:
                displayHotelRatingSummary(rHotels, rRatings, reviewCount);
                break;
            case 8:
                displayTopReviewers(uIDs, uNames, rUserIDs, userCount, reviewCount);
                break;
            case 9:
                addNewReview(rUserIDs, rRatings, rStatements, rHotels, reviewCount,
                             uIDs, uPoints, uCategories, userCount);
                break;
            case 10:
                cout << "Enter keyword to search in reviews (e.g., clean, bad, wifi): ";
                getline(cin, inputKeyword);
                searchReviewsByKeyword(inputKeyword, rStatements, rHotels, rRatings, reviewCount);
                break;
            case 11:
                displayTopUsersByPoints(uIDs, uNames, uPoints, uCategories, userCount);
                break;
            case 12:
                displayHotelsByPopularity(rHotels, reviewCount);
                break;

            case 13:
                cout << "Saving data to files...\n";
                saveData(uIDs, uNames, uCountries, uStates, uEmails, uCategories, uPoints, userCount,
                         rUserIDs, rRatings, rStatements, rHotels, reviewCount);
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 13);

    return 0;
}

// --- FUNCTION DEFINITIONS ---

// Function: loadData
// Reads data from "users.txt" and "reviews.txt" into parallel arrays.
// Ensures data is loaded into memory at the start of the program.
void loadData(string uID[], string uName[], string uCountry[], string uState[], string uEmail[], string uCat[], int uPoints[], int &uCount,
              string rUID[], int rRating[], string rStmt[], string rHotel[], int &rCount) {

    // 1. Read Users File
    ifstream inFile("users.txt");
    if (!inFile) {
        cout << "Error: Cannot open users.txt." << endl;
    } else {
        // Read tab-separated values until end of file or array full
        while (uCount < MAX_USERS && getline(inFile, uID[uCount], '\t')) {
            getline(inFile, uName[uCount], '\t');
            getline(inFile, uCountry[uCount], '\t');
            getline(inFile, uState[uCount], '\t');
            getline(inFile, uEmail[uCount], '\t');
            getline(inFile, uCat[uCount], '\t');
            inFile >> uPoints[uCount];
            inFile.ignore(); // Consume the newline character after the number
            uCount++;
        }
        inFile.close();
    }

    // 2. Read Reviews File
    ifstream rFile("reviews.txt");
    if (!rFile) {
        cout << "Error: Cannot open reviews.txt." << endl;
    } else {
        while (rCount < MAX_REVIEWS && getline(rFile, rUID[rCount], '\t')) {
            rFile >> rRating[rCount];
            rFile.ignore(); // Consume the tab after the number
            getline(rFile, rStmt[rCount], '\t');
            getline(rFile, rHotel[rCount]); // Read until end of line
            rCount++;
        }
        rFile.close();
    }
    cout << "Data loaded successfully! Users: " << uCount << ", Reviews: " << rCount << endl;
}

// Function: saveData
// Writes the current state of parallel arrays back to the text files.
// This preserves any new reviews or updated points added during runtime.
void saveData(const string uID[], const string uName[], const string uCountry[], const string uState[], const string uEmail[], const string uCat[], const int uPoints[], int uCount,
              const string rUID[], const int rRating[], const string rStmt[], const string rHotel[], int rCount) {

    ofstream uFile("users.txt");
    for (int i = 0; i < uCount; i++) {
        uFile << uID[i] << "\t" << uName[i] << "\t" << uCountry[i] << "\t"
              << uState[i] << "\t" << uEmail[i] << "\t" << uCat[i] << "\t"
              << uPoints[i] << endl;
    }
    uFile.close();

    ofstream rFile("reviews.txt");
    for (int i = 0; i < rCount; i++) {
        rFile << rUID[i] << "\t" << rRating[i] << "\t" << rStmt[i] << "\t" << rHotel[i] << endl;
    }
    rFile.close();
}

// Function: determineCategory
// Helper function to return membership status based on points.
string determineCategory(int points) {
    if (points >= 10000) return "Platinum";
    else if (points >= 5000) return "Gold";
    else if (points >= 1000) return "Silver";
    else return "Basic";
}

// Function: countWords
// Helper function to count words in a review for bonus point calculation.
int countWords(string text) {
    if (text.empty()) return 0;
    int words = 0;
    bool inWord = false;
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            inWord = false;
        } else if (!inWord) {
            inWord = true;
            words++;
        }
    }
    return words;
}

// Function: displayAllUsers
// Iterates through parallel arrays to print a formatted list of all users.
void displayAllUsers(const string uID[], const string uName[], const string uCountry[], const string uState[], const string uEmail[], const string uCat[], const int uPoints[], int uCount) {
    cout << left << setw(8) << "ID" << setw(20) << "Name" << setw(15) << "Country" << setw(20) << "State" << setw(25) << "Email" << setw(10) << "Category" << setw(10) << "Points" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < uCount; i++) {
        cout << left << setw(8) << uID[i] << setw(20) << uName[i] << setw(15) << uCountry[i] << setw(20) << uState[i] << setw(25) << uEmail[i] << setw(10) << uCat[i] << setw(10) << uPoints[i] << endl;
    }
}

// Function: displayUserReviews
// Filters reviews by User ID and displays matches.
void displayUserReviews(string targetUID, const string rUID[], const string rStmt[], const string rHotel[], const int rRating[], int rCount) {
    bool found = false;
    cout << "\n--- Reviews by User: " << targetUID << " ---\n";
    for (int i = 0; i < rCount; i++) {
        if (rUID[i] == targetUID) {
            cout << "Hotel: " << rHotel[i] << " | Rating: " << rRating[i] << "/5" << endl;
            cout << "Comment: " << rStmt[i] << endl;
            cout << "------------------------\n";
            found = true;
        }
    }
    if (!found) cout << "No reviews found for this user.\n";
}

// Function: displayHotelReviews
// Filters reviews by Hotel Name and displays matches.
void displayHotelReviews(string targetHotel, const string rHotel[], const int rRating[], const string rStmt[], int rCount) {
    bool found = false;
    cout << "\n--- Reviews for Hotel: " << targetHotel << " ---\n";
    for (int i = 0; i < rCount; i++) {
        if (rHotel[i] == targetHotel) {
            cout << "Rating: " << rRating[i] << "/5 | Comment: " << rStmt[i] << endl;
            found = true;
        }
    }
    if (!found) cout << "No reviews found for this hotel.\n";
}

// Function: displayPositiveReviews
// Filters for reviews matching a specific hotel AND having a rating >= 4.
void displayPositiveReviews(string targetHotel, const string rHotel[], const int rRating[], const string rStmt[], int rCount) {
    bool found = false;
    cout << "\n--- Positive Reviews (4-5 Stars) for: " << targetHotel << " ---\n";
    for (int i = 0; i < rCount; i++) {
        if (rHotel[i] == targetHotel && rRating[i] >= 4) {
            cout << "Rating: " << rRating[i] << "/5 | Comment: " << rStmt[i] << endl;
            found = true;
        }
    }
    if (!found) cout << "No positive reviews found for this hotel.\n";
}

// Function: displaySummary
// Calculates and displays system-wide statistics (Total Users, Reviews, Points).
void displaySummary(int uCount, int rCount, const int uPoints[]) {
    long long totalPoints = 0;
    for(int i=0; i<uCount; i++) totalPoints += uPoints[i];

    cout << "\n--- System Activity Summary ---\n";
    cout << "A. Total Users: " << uCount << endl;
    cout << "B. Total Reviews: " << rCount << endl;
    cout << "C. Total Points Awarded: " << totalPoints << endl;
}

// Function: displayUsersByCategory
// Groups users by their membership tier (Platinum, Gold, Silver, Basic).
void displayUsersByCategory(const string uID[], const string uName[], const string uCat[], int uCount) {
    cout << "\n--- Users by Membership Category ---\n";
    string categories[] = {"Platinum", "Gold", "Silver", "Basic"};

    for(int c=0; c<4; c++) {
        cout << "\nCategory: " << categories[c] << endl;
        bool found = false;
        for(int i=0; i<uCount; i++) {
            if(uCat[i] == categories[c]) {
                cout << " - " << uName[i] << " (" << uID[i] << ")" << endl;
                found = true;
            }
        }
        if(!found) cout << " (No users)" << endl;
    }
}

// Function: displayHotelRatingSummary
// Aggregates reviews for each hotel to calculate and display average ratings.
void displayHotelRatingSummary(const string rHotel[], const int rRating[], int rCount) {
    string uniqueHotels[MAX_REVIEWS];
    int hotelCounts[MAX_REVIEWS] = {0};
    int hotelTotalScore[MAX_REVIEWS] = {0};
    int uniqueCount = 0;

    // Aggregate data manually without complex structures
    for (int i = 0; i < rCount; i++) {
        bool exists = false;
        int index = -1;
        // Check if hotel is already in unique list
        for (int j = 0; j < uniqueCount; j++) {
            if (uniqueHotels[j] == rHotel[i]) {
                exists = true;
                index = j;
                break;
            }
        }

        if (exists) {
            hotelCounts[index]++;
            hotelTotalScore[index] += rRating[i];
        } else {
            uniqueHotels[uniqueCount] = rHotel[i];
            hotelCounts[uniqueCount] = 1;
            hotelTotalScore[uniqueCount] = rRating[i];
            uniqueCount++;
        }
    }

    cout << "\n--- Hotel Rating Summary ---\n";
    cout << left << setw(25) << "Hotel Name" << setw(15) << "Reviews" << setw(10) << "Avg Rating" << endl;
    for (int i = 0; i < uniqueCount; i++) {
        double avg = (double)hotelTotalScore[i] / hotelCounts[i];
        cout << left << setw(25) << uniqueHotels[i] << setw(15) << hotelCounts[i] << setw(10) << fixed << setprecision(1) << avg << endl;
    }
}

// Function: displayTopReviewers
// Sorts users by review count (using bubble sort) and displays the top 3.
void displayTopReviewers(const string uID[], const string uName[], const string rUID[], int uCount, int rCount) {
    int reviewCounts[MAX_USERS] = {0};
    string tempIDs[MAX_USERS];

    // 1. Count reviews per user
    for(int i=0; i<uCount; i++) {
        tempIDs[i] = uID[i];
        for(int j=0; j<rCount; j++) {
            if(rUID[j] == uID[i]) {
                reviewCounts[i]++;
            }
        }
    }

    // 2. Sort (Bubble sort descending) using parallel temporary arrays
    for(int i=0; i<uCount-1; i++) {
        for(int j=0; j<uCount-i-1; j++) {
            if(reviewCounts[j] < reviewCounts[j+1]) {
                // Swap counts
                int tempCount = reviewCounts[j];
                reviewCounts[j] = reviewCounts[j+1];
                reviewCounts[j+1] = tempCount;

                // Swap IDs to keep alignment
                string tempID = tempIDs[j];
                tempIDs[j] = tempIDs[j+1];
                tempIDs[j+1] = tempID;
            }
        }
    }

    cout << "\n--- Top 3 Reviewers ---\n";
    for(int i=0; i<3 && i<uCount; i++) {
        string name = "Unknown";
        // Find name for the ID (since we sorted a temp array of IDs)
        for(int k=0; k<uCount; k++) {
            if(uID[k] == tempIDs[i]) name = uName[k];
        }
        cout << (i+1) << ". " << name << " (ID: " << tempIDs[i] << ") - " << reviewCounts[i] << " reviews\n";
    }
}

// Function: addNewReview
// Allows user to input a new review at runtime.
// Calculates points, updates membership tier, and appends to arrays.
void addNewReview(string rUID[], int rRating[], string rStmt[], string rHotel[], int &rCount,
                  string uID[], int uPoints[], string uCat[], int uCount) {
    if (rCount >= MAX_REVIEWS) {
        cout << "Database full. Cannot add more reviews.\n";
        return;
    }

    string userID;
    cout << "Enter User ID: ";
    getline(cin, userID);

    // Verify user exists
    int userIndex = -1;
    for(int i=0; i<uCount; i++) {
        if(uID[i] == userID) {
            userIndex = i;
            break;
        }
    }

    if(userIndex == -1) {
        cout << "User ID not found! Please register first.\n";
        return;
    }

    // Input Review Data
    rUID[rCount] = userID;
    cout << "Enter Hotel Name: ";
    getline(cin, rHotel[rCount]);

    cout << "Enter Rating (1-5): ";
    // Loop until input is a number AND is between 1-5
    while (!(cin >> rRating[rCount]) || rRating[rCount] < 1 || rRating[rCount] > 5) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid rating. Enter 1-5: ";
    }
    cin.ignore(10000, '\n'); // Clear buffer after valid input

    cout << "Enter Review (Comment): ";
    getline(cin, rStmt[rCount]);

    // Calculate Points: Base 100 + Bonus 10 for >50 words
    int pointsEarned = 100;
    if (countWords(rStmt[rCount]) > 50) {
        pointsEarned += 10;
        cout << " [Bonus] Review > 50 words! +10 extra points.\n";
    }

    // Update User Points
    uPoints[userIndex] += pointsEarned;

    // Update Membership automatically if threshold reached
    string newCat = determineCategory(uPoints[userIndex]);
    if(newCat != uCat[userIndex]) {
        cout << " *** STATUS UPDATE ***\n";
        cout << " User " << uID[userIndex] << " upgraded from " << uCat[userIndex] << " to " << newCat << "!\n";
        uCat[userIndex] = newCat;
    }

    rCount++; // Increment total reviews
    cout << "Review added successfully! Total points earned: " << pointsEarned << endl;
}

// Function: searchReviewsByKeyword
// Allows user to search for a specific word inside review comments.
void searchReviewsByKeyword(string keyword, const string rStmt[], const string rHotel[], const int rRating[], int rCount) {
    bool found = false;
    cout << "\n--- Search Results for '" << keyword << "' ---\n";
    for (int i = 0; i < rCount; i++) {
        if (rStmt[i].find(keyword) != string::npos) { // Checks if keyword exists in statement
             cout << "Hotel: " << rHotel[i] << " (" << rRating[i] << "/5) - \"" << rStmt[i] << "\"\n";
             found = true;
        }
    }
    if (!found) cout << "No reviews found containing '" << keyword << "'.\n";
}

// Function: displayTopUsersByPoints
// Displays a leaderboard of users ranked by their membership points.
void displayTopUsersByPoints(const string uID[], const string uName[], const int uPoints[], const string uCat[], int uCount) {
    // Create temporary arrays to preserve original data order
    string tID[MAX_USERS], tName[MAX_USERS], tCat[MAX_USERS];
    int tPoints[MAX_USERS];

    for(int i=0; i<uCount; i++) {
        tID[i] = uID[i]; tName[i] = uName[i];
        tPoints[i] = uPoints[i]; tCat[i] = uCat[i];
    }

    // Bubble Sort: Descending order by Points
    for(int i=0; i<uCount-1; i++) {
        for(int j=0; j<uCount-i-1; j++) {
            if(tPoints[j] < tPoints[j+1]) {
                // Swap points
                int tempP = tPoints[j];
                tPoints[j] = tPoints[j+1];
                tPoints[j+1] = tempP;

                // Swap associated metadata (ID, Name, Category)
                string tempS;
                tempS = tID[j]; tID[j] = tID[j+1]; tID[j+1] = tempS;
                tempS = tName[j]; tName[j] = tName[j+1]; tName[j+1] = tempS;
                tempS = tCat[j]; tCat[j] = tCat[j+1]; tCat[j+1] = tempS;
            }
        }
    }

    cout << "\n--- Leaderboard by Points ---\n";
    cout << left << setw(5) << "Rank" << setw(20) << "Name" << setw(15) << "Category" << setw(10) << "Points" << endl;
    for(int i=0; i<uCount; i++) {
        cout << left << setw(5) << (i+1) << setw(20) << tName[i] << setw(15) << tCat[i] << setw(10) << tPoints[i] << endl;
    }
}

// Function: displayHotelsByPopularity
// Ranks and displays hotels based on the volume of reviews received.
void displayHotelsByPopularity(const string rHotel[], int rCount) {
    string uniqueHotels[MAX_REVIEWS];
    int hotelCounts[MAX_REVIEWS] = {0};
    int uniqueCount = 0;

    // Aggregate counts for unique hotels
    for(int i=0; i<rCount; i++) {
        int idx = -1;
        // Search if hotel already exists in unique list
        for(int j=0; j<uniqueCount; j++) {
            if(uniqueHotels[j] == rHotel[i]) { idx = j; break; }
        }

        if(idx != -1) {
            hotelCounts[idx]++;
        } else {
            uniqueHotels[uniqueCount] = rHotel[i];
            hotelCounts[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    // Bubble Sort by Review Counts (Descending)
    for(int i=0; i<uniqueCount-1; i++) {
        for(int j=0; j<uniqueCount-i-1; j++) {
            if(hotelCounts[j] < hotelCounts[j+1]) {
                // Swap Counts
                int tempC = hotelCounts[j];
                hotelCounts[j] = hotelCounts[j+1];
                hotelCounts[j+1] = tempC;

                // Swap Names
                string tempH = uniqueHotels[j];
                uniqueHotels[j] = uniqueHotels[j+1];
                uniqueHotels[j+1] = tempH;
            }
        }
    }

    cout << "\n--- Most Popular Hotels (By Review Count) ---\n";
    for(int i=0; i<uniqueCount; i++) {
        cout << (i+1) << ". " << uniqueHotels[i] << " - " << hotelCounts[i] << " reviews\n";
    }
}