// movieList.cpp : Defines the entry point for the console application.
/*This program will allow the user to create a movie list with ratings. 
It gives the user multiple options for editing the list. It also gives the user
the total count and the average rating. The purpose of this program is to practice with
functions, vectors, writing to files, and input validation*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

void menuOptions();     //Function prototype for the menu options
void createList();      //Function prototype for option 1: Create a movie list
void viewList();        //Functon prototype for option 2: view movie list
void addToList();       //Function prototype for option 3: add to movie list
void editList();       //Function prototype for option 4: edit a movie list
void deleteList();     //Function prototype for option 5: delete a movie list item

vector<string> movieTitles(1);    //global vector variable to hold the movie titles. Initialized to 1 so user will add exact amount
vector<float> movieRatings(1);      //global vector varaible to hold the movie ratings. Initialized to 1 so user will add exact amount


int main()
{//Tells the user what the program is for and sends to the menu function.
	cout << setw(50) << "THE MOVIE LIST PROGRAM!\n";
	cout << "This program will allow you to create and edit your own movie list!\n"
		<< "A movie list allows you to document which movies you have seen and what you rated them.\n"
		<< "If this is your first time, you will want to start by creating a movie list.\n"
		<< "Please select one of the options below by typing the appropriate number and press ENTER.\n" << endl << endl << endl;
	menuOptions();




	system("pause");
	return 0;
}


/*FUNCTION DEFINITION
This function displays the menu option and captures the choice made by the user.
It then returns that value to the main function.*/
void menuOptions()
{
	char choice = 0;                           //Define and initialize the variable for the user choice 
	cout << "1. Create a Movie List\n"
		<< "2. View your current Movie List\n"
		<< "3. Add a movie to your Movie List\n"
		<< "4. Edit a movie title or rating\n"
		<< "5. Delete a movie title or rating\n"
		<< "6. Exit\n";
	cin >> choice;                           //Takes the choice from the user

	//This will send the user to the appropriate function based upon the choice selected
	switch (choice)
	{
	case '1': createList();
		break;
	case '2': viewList();
		break;
	case '3': addToList();
		break;
	case '4': editList();
		break;
	case '5': deleteList();
		break;
	case '6': cout << "Thank you! Have a nice day!\n";
		return;
	}

}

/*FUNCTION DEFINITION
This function allows the user to create a movie list
and send it to a file*/
void createList()
{
	//Explains to the user what they are about to do
	cout << "You chose to create a new Movie List!\n"
		<< "Here you will add the titles of movies that you have seen and a rating for that movie.\n"
		<< "Start by entering your movie title, then entering a rating of 1-10.\n"
		<< "1 being the worst movie you have ever seen, and 10 being the best.\n"
		<< "You can also input half rating such as 5.5.\n"
		<< "Please input your first movie title and rating.\n";

	char option = 'n';   ///To initialize the option to continue the input or exit

	do  //Vector loop to get inputs for the movie title and the movie rating 
	{
		string title = " ";              //To create a variable for inputting the movie title 
		float rating = 0;                  //To create a variable for inputting the movie rating

		cout << "Movie Title: ";
		cin.get();                         //To remove the new line character. Without this, the getline cuts off the first word of the movie title.
		getline(cin, title);               //Captures the movie title as a string
		movieTitles.push_back(title);      //Uses the pushback member function to input the user entry into the vector movieTitles
		cout << endl;
		cout << "Movie Rating: ";
		cin >> rating;                      //has the user input the movie rating
		movieRatings.push_back(rating);     //uses the pushback member function to add the user entry to the vector movieRatings
		cout << endl;
		cout << "Would you like to input another movie? y/n\n";       //Asks the user if they would like to input another title
		cin >> option;                                                //Holds the option. This is defined outside of the loop
	} while (option == 'y');                 //If user selects y, the loop will continue.


	//To display the input list and the ratings to the user 
	for (int count = 1; count < movieTitles.size(); count++)
	{
		cout << movieTitles[count] << "   " << movieRatings[count] << endl;
	}


	//To calculate the total movies input in the list
	int totalTitles = movieTitles.size() - 1;           /*variable to hold the total amount of elements in MovieTitles.
													Which should match the amount of titles in the vector. Its off by one, so I subtracted 1*/
	cout << "You watched a total of " << totalTitles << " movies.";



	//To get the average rating of the movies watched
	double totalRatings = 0.0;               //To define and initialize total ratings so it can be used outside of for statement
	for (int index = 1; index < movieRatings.size(); index++)
	{
		totalRatings += movieRatings[index];       //To accumulate the total movie ratings
	}

	cout << "Your average movie rating for all movies watched is " << totalRatings / totalTitles << ".\n"
		<< "You have created your movie list. You will now be taken back to the main menu.\n";


	//To open the file and write the movie list and movie rating to the file
	ofstream writeMovieList;
	writeMovieList.open("movieList.txt");
	writeMovieList << "MOVIE TITLE" << setw(95) << "MOVIE RATING" << endl;

	
	for (int index1 = 1; index1 < movieRatings.size(); index1++)
	{
		writeMovieList << left << movieTitles[index1];           //**work on output formatting**//
		writeMovieList << left << movieRatings[index1] << endl;
	}
	
	writeMovieList << "You watched a total of " << totalTitles << " movies.\n";
	writeMovieList << "Your average movie rating is " << setprecision(2) << totalRatings / totalTitles << ".\n";


	//To Close the File
	writeMovieList.close();

	//To send back to the main menu
	menuOptions();
}


/*FUNCTION DEFINITION
This function allows the user to view the current movie list
no edits are allowed*/
void viewList()
{
	//Opens the file
	string title;
	cout << "Below is your current movie list.\n";
		ifstream viewFile;
	viewFile.open("movielist.txt");
	
	//To skip the first line in the file
	string dummy;   
	getline(viewFile, dummy);

	
	//To read in the remainder of the file
	int counter = 1;
	while (getline(viewFile, title))
		{
			cout << counter << ". " << title << endl;
			counter++;
		}
		//*****NEED TO FIGURE OUT HOW TO SEPARATE THE MOVIE TITLE AND MOVIE RATING********//
	
	

	
	//To Close the file
	viewFile.close();

	cout << endl << endl << endl;  //To put some space between the last file line and the main menu
	//To send back to the main menu
	menuOptions();
}


/*FUNCTION DEFINITION
This function allows the user to add an item to the 
movie list*/
void addToList()
{
	char choice = 'n';
	do
	{
		//To add the movie title to the end of the list
		string addTitle;
		cout << "Ok, you would like to add a movie to your list\n"
			<< "Please input the name of the movie: ";
		cin.get();
		getline(cin, addTitle);               //Captures the movie title as a string
		movieTitles.push_back(addTitle);      //Uses the pushback member function to input the user entry into the vector movieTitles

		//To add the movie rating to the end of the list
		int addRating;
		cout << "Now input the rating for that title: ";
		cin >> addRating;
		movieRatings.push_back(addRating);

		cout << "Would you like to add another title? y/n\n";
		cin >> choice;

	} while (choice == 'y');

	
	//After adding titles and ratings, we must recreate the file and recalculate the statistics.
	//To calculate the total movies input in the list
	int totalTitles = movieTitles.size() - 1;           /*variable to hold the total amount of elements in MovieTitles.
														Which should match the amount of titles in the vector. Its off by one, so I subtracted 1*/




	/*BELOW THIS LINE IS A FUNCTION THAT IS SUPPOSED TO WRITE THE LIST OF MOVIES TO THE FILE
	UNFORTUNATELY IT IS ONLY WRITING THE CURRENTLY WRITTEN MOVIE IN THE LIST AND DELETING THE 
	OTHER TEXT. I COPIED THIS PART FROM MENU OPTION 1. NEED TO TWEAK IT SO THAT IT DOES NOT DELETE
	THE PRE-EXISTING VECTOR FUNCTIONS*/
														
														
														
														
														//To get the average rating of the movies watched
	double totalRatings = 0.0;               //To define and initialize total ratings so it can be used outside of for statement
	for (int index = 1; index < movieRatings.size(); index++)
	{
		totalRatings += movieRatings[index];       //To accumulate the total movie ratings
	}


	//To open the file and write the movie list and movie rating to the file
	ofstream writeMovieList;
	writeMovieList.open("movieList.txt");
	writeMovieList << "MOVIE TITLE" << setw(95) << "MOVIE RATING" << endl;


	for (int index1 = 1; index1 < movieRatings.size(); index1++)
	{
		writeMovieList << left << movieTitles[index1];           //**work on output formatting**//
		writeMovieList << left << movieRatings[index1] << endl;
	}

	writeMovieList << "You watched a total of " << totalTitles << " movies.\n";
	writeMovieList << "Your average movie rating is " << setprecision(2) << totalRatings / totalTitles << ".\n";


	//To Close the File
	writeMovieList.close();


	//****THIS IS THE END OF THE STUFF THAT NEEDS TO BE FIXED******/

	//To ask the user what they want to do next. They can either view their movie list or go back to the main menu.
	char option2;
	cout << "Would you like to view your list with changes? y/n\n";
	cin >> option2;
	
	switch (option2)
	{
	case 'n': menuOptions();
		break;
	case 'y': viewList();
		break;
	}

}

/*FUNCTION DEFINITION
This function allows the user to edit a movie
title or a movie rating*/
void editList()
{
	cout << "You are in the function edit list\n";
}


/*FUNCTION DEFINITION
This function allows the user to delete an item
from the movie list*/
void deleteList()
{
	cout << "You are in the function delete list\n";
}