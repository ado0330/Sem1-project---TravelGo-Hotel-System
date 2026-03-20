# TravelGo Hotel Review & Membership System

**Course:** CCA101 - Report-Based Programming Assessment (Individual)  
**Name:** KHAW ZHI XIN  
**Matric Number:** 24303631  

---

## 1. Problem Statement

**Scenario:**
TravelGo is a global booking platform that requires a system to manage user profiles and hotel reviews. Currently, customer service officers lack a unified tool to view user activities, analyze hotel ratings, and update membership tiers automatically based on accumulated points.

**Goal:**
Design a modular C++ program using **Functions** and **Parallel Arrays** that allows officers to:
1. Load user and review data from files (Read Once).
2. Display reviews filtered by user or hotel.
3. Calculate and update membership status (Basic, Silver, Gold, Platinum).
4. Add new reviews and award bonus points for detailed feedback.
5. Save updated data back to files (Write Once).

---

## 2. Project Specification

The global hospitality industry relies heavily on customer feedback, where authentic hotel reviews play a pivotal role in shaping traveler decisions and maintaining service standards. As booking platforms expand, customer service officers face increasing challenges in manually tracking user activity, analyzing hotel performance trends, and managing loyalty rewards. In response to these operational demands, the **TravelGo Hotel Review & Membership System** has been developed to provide a centralized and efficient data management tool for platform administrators.

The TravelGo System is a comprehensive console-based application designed to streamline the management of user profiles and hotel review histories. This system offers a suite of administrative features, including the ability to filter reviews by specific criteria (such as positive ratings or keywords), calculate automatic membership upgrades **(Basic, Silver, Gold, Platinum)** based on accumulated points, and generate real-time statistics on hotel popularity. By automating these tasks, the system ensures that user engagement is accurately rewarded and hotel quality is easily monitored.

In this documentation, we will discuss the technical implementation of the TravelGo System, specifically focusing on the use of **Modular Programming** and **Parallel Arrays** to handle data efficiently without dynamic memory overhead. We will explain the algorithms behind key features such as the leaderboard sorting, keyword search, and the bonus point calculation logic. We will also examine the specific constraints, such as file handling protocols and static memory limits. Ultimately, this report aims to provide a working C++ solution that demonstrates how the TravelGo System enhances operational efficiency and data accessibility for the platform's management team.

---

## 3. Problem Analysis

### Input, Process and Output (IPO)

**Input:**
* Name of the input files (`users.txt` and `reviews.txt`)
* Choice of user from the menu (1-13)
* Specific User ID that the user wants to view reviews for
* Specific Hotel Name that the user wants to view reviews for
* New Review Data:
  * User ID
  * Hotel Name
  * Rating (1-5)
  * Review Statement (Comment)

**Process:**
* **Load Data:** Read `users.txt` and `reviews.txt` into parallel arrays once at startup.
* **Menu Logic:** Perform appropriate actions based on user menu choice (Switch-Case).
* **Search & Filter:** Find specific reviews in the arrays based on target User ID or Hotel Name.
* **Calculation:** Calculate new total points (Base + Bonus for >50 words) and update Membership Category (Basic/Silver/Gold/Platinum).
* **Sort:** Arrange users to identify the Top 3 reviewers for the leaderboard.
* **Save Data:** Write updated array data back to the text files upon exit.

**Output:**
* List of reviews filtered by specific User or Hotel
* Detailed User Profile information (Name, Country, Membership, Points)
* System Summary (Total users, Total reviews, Total points awarded)
* Top 3 Reviewers Leaderboard
* Membership Upgrade Notifications (e.g., "Upgraded to Gold")
* Updated content saved back to `users.txt` and `reviews.txt`
* Appropriate prompts and error messages for the user

### Constraints
* **Fixed Data Structures**: The program strictly uses Parallel Arrays to manage data. The use of struct, class, vector, or pointer is strictly prohibited.
* **Restricted File Handling**: Input files (`users.txt` and `reviews.txt`) must be opened exactly once for reading at the start and exactly once for writing at the end. Re-opening files inside loops or writing to files during processing is forbidden to ensure efficiency.
* **Modular Design**: The solution must be implemented using modular programming, with separate functions handling specific tasks (loading, displaying, adding, saving) rather than a monolithic main function.
* **Static Memory Allocation**: Since dynamic memory is not allowed, the system assumes a maximum limit for the number of users (e.g., 100) and reviews (e.g., 500) that can be stored in the arrays.

### Assumptions
* **Fixed Data Limits**: Since dynamic memory is not allowed, the program assumes the number of users will never exceed 100 and reviews will never exceed 500.
* **Correct File Format**: It is assumed that `users.txt` and `reviews.txt` are formatted correctly with tabs separating the data, and that these files exist in the same folder as the program.
* **Valid User Input**: While basic type validation is implemented (preventing crashes on non-numeric input), it is assumed that users will generally follow instructions (e.g., not entering a rating of 100).
* **Case-Sensitive Search**: The keyword search functionality is designed to be case-sensitive. It is assumed that the user will input the keyword matching the exact case used in the reviews.

---

## 4. Programming Design & Solution

### Flowchart
Please refer to the attached file named `Flowchart_KHAWZHIXIN.png` to view the complete logic and structure of the system. 
*Alternatively, view it via this [Google Drive link](https://drive.google.com/file/d/1ewygtiaEHAgzS2haSnEiigF_L-JwFA6v/view?usp=sharing).*

### Pseudocode
```text
Write function prototype at the top of program

Function Main
    Declare Constants MAX_USERS, MAX_REVIEWS
    Declare Parallel Arrays for Users and Reviews
    Initialize userCount = 0, reviewCount = 0

    Call loadData()

    Do
        Display Menu Options (1-13)
        Get user choice

        Switch choice
            Case 1: Call displayAllUsers()
            Case 2: Input UserID -> Call displayUserReviews()
            Case 3: Input HotelName -> Call displayHotelReviews()
            Case 4: Input HotelName -> Call displayPositiveReviews()
            Case 5: Call displaySummary()
            Case 6: Call displayUsersByCategory()
            Case 7: Call displayHotelRatingSummary()
            Case 8: Call displayTopReviewers()
            Case 9: Call addNewReview()
            Case 10: Input Keyword -> Call searchReviewsByKeyword()
            Case 11: Call displayTopUsersByPoints()
            Case 12: Call displayHotelsByPopularity()
            Case 13: Call saveData()
            Default: Display Error Message
        End Switch
    While choice is not 13
End Main

Function loadData
    Open "users.txt" for Reading
    While not End of File
        Read data into User Arrays
        Increment userCount
    End While
    Close "users.txt"

    Open "reviews.txt" for Reading
    While not End of File
        Read data into Review Arrays
        Increment reviewCount
    End While
    Close "reviews.txt"
End Function

Function saveData
    Open "users.txt" for Writing
    For each user
        Write User Array data to file
    End For
    Close "users.txt"

    Open "reviews.txt" for Writing
    For each review
        Write Review Array data to file
    End For
    Close "reviews.txt"
End Function

Function determineCategory(points)
    If points >= 10000 Return "Platinum"
    Else If points >= 5000 Return "Gold"
    Else If points >= 1000 Return "Silver"
    Else Return "Basic"
End Function

Function countWords(text)
    Count number of words in text based on spaces
    Return wordCount
End Function

// ... (View and Action Functions omitted for brevity in README, refer to source code) ...
