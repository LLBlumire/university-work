#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

/* Insert your functions from last week here */

/// Converts a percentage into a grade.
char GradeFromPercentage(float percentage) {
    if (percentage >= 90.0) {
        return 'A';
    } else if (percentage >= 70) {
        return 'B';
    } else if (percentage >= 50) {
        return 'C';
    } else if (percentage >= 30) {
        return 'D';
    } else {
        return 'F';
    }
}

/// Converts mars into a grade.
char GradeFromRawMarks(float marksAwarded, float marksAvailable) {
    return GradeFromPercentage( (marksAwarded / marksAvailable) * 100.0 );
}

/// Converts a set of mars into a grade
char GradeFromTotalRawMarks(float marksAwarded[], float marksAvailable[], size_t maxAssignments) {
    float awarded = 0;
    float available = 0;
    for (size_t i = 0; i < maxAssignments; i++) {
        awarded = awarded + marksAwarded[i];
        available = available + marksAvailable[i];
    }
    return GradeFromRawMarks(awarded, available);
}


/// Checks if a char is uppercase 
bool IsUppercase(char a) {
    if (a >= 65 && a <= 90) {
        return true;
    } else {
        return false;
    }
}

/// Checks if a char is lowercase
bool IsLowercase(char a) {
    if (a >= 97 && a <= 122) {
        return true;
    } else {
        return false;
    }
}

/// Checks if two chars are alphabetical and the same (ignoring case)
bool CheckCase(char a, char b) {
    if (IsUppercase(a)) {
        a = a + 32;
    }
    if (IsUppercase(b)) {
        b = b + 32;
    }

    if (IsLowercase(a) && IsLowercase(b)) { // True for all alphabetical values now
        if (a == b) {
            return true;
        }
    }
    return false;
}

/// Output all Marks 
void DisplayAllRawMarks(float marksAwarded[], float marksAvailable[], int maxAssignments) {
    for (size_t i = 0; i < maxAssignments; i++) {
        printf("%zu:\t%.1f/%.1f\t-> %c\n", i, marksAwarded[i], marksAvailable[i],
                GradeFromRawMarks(marksAwarded[i], marksAvailable[i]));
    }
    printf("====================\n");
    printf("Final Grade: %c", GradeFromTotalRawMarks(marksAwarded, marksAvailable, maxAssignments));
}

/// Change the value in an assignment
void EditAssignment(float marksAwarded[], float marksAvailable[], int position) {
    fputs("Enter New Marks Awarded: ", stdout);
    fscanf(stdin, "%f", &marksAwarded[position]);
    fputs("Enter New Marks Available: ", stdout);
    fscanf(stdin, "%f", &marksAvailable[position]);
}

/// Add an Assignment
void AddAssignment(float marksAwarded[], float marksAvailable[], int *max) {
    *max = *max + 1;
    EditAssignment(marksAwarded, marksAvailable, *max - 1);
}

/// Remove an Assignment
void RemoveAssignment(float marksAwarded[], float marksAvailable[], int *max, int position) {
    *max = *max - 1;
    for (; position < *max; position++) {
        marksAwarded[position] = marksAwarded[position + 1];       
        marksAvailable[position] = marksAvailable[position + 1];       
    }
}

int main() {
	char userInput = '?'; // some place to store input from the user
	int max = 0;          // the maximum assignment count (i.e. how many assignements we have
	float marksAwarded[100];     // place to store the marks
	float marksAvailable[100]; // place to store the available marks

	// Since we've not got any code to add new assignments yet,
	// here's some test assignments manually assigned.
	
	/* Testing code: default assignment scores */
	{
		marksAwarded[0] = 10; marksAvailable[0] = 10;
		marksAwarded[1] = 7;  marksAvailable[1] = 11;
		marksAwarded[2] = 5;  marksAvailable[2] = 11;
		marksAwarded[3] = 3;  marksAvailable[3] = 11;
		marksAwarded[4] = 0;  marksAvailable[4] = 100;
		max = 5; // update how many items we have
	}
	/* End of testing code */
	
	while(1) // forever
	{
		// Print the main menu
		printf("\nA) Display Marks\nB) Edit Assignment\nC) Add Assignment\nD)Remove Assignment\n\nQ) Quit\n\n>");
		
		// Grab the option from the user
		scanf(" %c", &userInput);
				
		if(CheckCase(userInput, 'A')) 
		{
			// Display all the marks we have
			DisplayAllRawMarks(marksAwarded, marksAvailable, max);
		}

        if(CheckCase(userInput, 'B'))
        {
            // Get a position and edit it
            int position;
            fputs("Enter a position of an assignment to edit: ", stdout);
            fscanf(stdin, "%d", &position);
            EditAssignment(marksAwarded, marksAvailable, position);
        }

        if(CheckCase(userInput, 'C'))
        {
            // Create a new assignment
            AddAssignment(marksAwarded, marksAvailable, &max);
        }

        if(CheckCase(userInput, 'D'))
        {
            // Get a position and remove it
            int position;
            fputs("Enter a position of an assignment to remove: ", stdout);
            fscanf(stdin, "%d", &position);
            RemoveAssignment(marksAwarded, marksAvailable, &max, position);
        }
		
		
		if(CheckCase(userInput, 'Q')) 
		{
			// If 'Q' or 'q' entered, break out of the while loop
			break;
		}
		
		// Keep going around the while loop if the user didn't quit
	}
	
	return 0;
}
