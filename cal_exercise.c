//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    
	int n = 500;	//Me : Defining for fgets()
	char str[n];	//Me : Defining for fgets()
	
	while (fgets(str, n, file) != NULL) {	//Me : Read line by line until there is no more reading to read
    	
    	char *exercise_name = strtok(str, " ");	//Me : the beginning of a sentence divided by a space - using strtok for dividing a sentence
    	char *calories_burned_per_minute = strtok(NULL, "\n");	//Me : dividing the remaining parts of a sentence by /n - using strtok 
		
		strcpy(exercise_list[exercise_list_size].exercise_name, exercise_name);	//Me : save exercise_list as exercise_name in exercise_list_size
		exercise_list[exercise_list_size].calories_burned_per_minute = atoi(calories_burned_per_minute);	//Me : save as exercise_list of exercise_list_size's calories_burned_per_minute- Use atoi to replace string with integer
    	
    	exercise_list_size++;	//Me : Increase the number of saved exercise_lists -> to see if there are more than 100
        
		if (exercise_list_size >= MAX_EXERCISES){
        	break;
		}
    }

    fclose(file);
    
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");
    
    for (i=0; i < exercise_list_size; i++)	//Me : Repeat as many values as stored in exercise_list
    	printf("%d. %s (%d kcal burned per min.)\n", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);	//Me : Output the appropriate numbers and exercise menus and calories burne per min
    printf("%d. Exit\n", exercise_list_size+1);	//Me : Output Exit Menu to Last Number


    // ToCode: to enter the exercise to be chosen with exit option

 	printf("Choose (1-%d): ", exercise_list_size+1);	//Me : Outputting words to choice
    scanf("%d", &choice);	//Me : Scan the menu selected by the user and save it to choice
    
    // To enter the duration of the exercise
    if((choice >= 1) && (choice <= exercise_list_size)){	//Me : When choice is a exercise menu
		printf("Enter the duration of the exercise (in min.): ");	//Me : Outputting words to receive duration
    	scanf("%d", &duration);

    // ToCode: to enter the selected exercise and total calcories burned in the health data
		health_data->exercises[health_data->exercise_count] = exercise_list[choice-1];	//Me : Store the selected execise_list at the execise_count of the execise array in health_data
		health_data->exercises[health_data->exercise_count].calories_burned_per_minute *= duration;	//change the value of the stored execise_list's callories_burned_per_minute to the value multiplied by the duration
		health_data->total_calories_burned += health_data->exercises[health_data->exercise_count].calories_burned_per_minute;	//Me : Add calories from the exercise you choose to the total_calories_burned of health_data
		health_data->exercise_count++;	//Me: Increase exercise_count
	}
	else if (choice == exercise_list_size+1){	//Me : When choice is a Quit menu
		printf("Go back to Main menu\n");	//Me : print "Go back to Main menu"
	}
	else {	//Me : When choice is unvalid
		printf("You choose wrong menu!\n");	//Me : print "You choose wrong menu!"
	}
    
}
