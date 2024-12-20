//
//  cal_healthdata.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    for (i = 0; i < health_data->exercise_count; i++)	//Me : Repeat by execise_count
  		fprintf(file, "Exercise: %s, Calories burned : %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);	//Me : Type an Exercise-Calleries burned statement in file
    
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n");
	for (i = 0; i < health_data->diet_count; i++)	//Me : Repeat by diet_count
		fprintf(file, "Food: %s, Calories intake : %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);	//Me : Type a Food-Calories intake statement in file


    // ToCode: to save the total remaining calrories
    int remain_calories = health_data->total_calories_intake - 1300 - health_data->total_calories_burned;	//Me : Calculation of remaining calories
    fprintf(file, "\n[Total] \n");
    fprintf(file, "Basal Metabolic Rate: 1300 kcal\n");	//Me : Type a Basal Metabolic Rate statement in file
 	fprintf(file, "Total calories burned: %d kcal\n", health_data->total_calories_burned);	//Me : Type a total calories burned statement in file
 	fprintf(file, "Total calories intake: %d kcal\n", health_data->total_calories_intake);	//Me : Type a total calories intake statement in file
 	fprintf(file, "The remaining calories: %d kcal\n", remain_calories); 	//Me : Type a Remaining calories in file
    
    fclose(file);	//Me : close a file
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void printHealthData(const HealthData* health_data) {
	int i;
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
  
  	for (i = 0; i < health_data->exercise_count; i++)	//Me : Repeat by execise_count
  		printf("Exercise: %s, Calories burned : %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);	//Me : Output Exercise-Calories burned statement
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");

	for (i = 0; i < health_data->diet_count; i++)	//Me : Repeat by diet_count
		printf("Food: %s, Calories intake : %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);	//Me : Output Food-Calories intake statement

    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	int remain_calories = health_data->total_calories_intake - 1300 - health_data->total_calories_burned;	//Me : Calculation of remaining calories
	
	printf("============================== Total Calories =========================\n");
 
 	printf("Basal Metabolic Rate: 1300 kcal\n");	//Me : Output Basal Metabolic Rate statement
 	printf("Total calories burned: %d kcal\n", health_data->total_calories_burned);	//Me : Output total calories burned statement
 	printf("Total calories intake: %d kcal\n", health_data->total_calories_intake);	//Me : Output total calories intake statement
 	printf("The remaining calories: %d kcal\n", remain_calories); 	//Me : Output the remaining calories statement
 	
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    
    if (remain_calories < 0) {	//Me : when the remaining calories are less than zero
    	printf("[Warning] Too few calories!\n");	//Me : print out a sentence
    	if(health_data->total_calories_intake == 2000)	//Me : When the calorie intake is equal to the recommended daily calories (2000)
    		printf("¡°Your total calorie intake for today has reached your goal!\n");	//Me : print out a sentence
    	else if(health_data->total_calories_intake < 2000)	//Me : When the calorie intake is higher than the recommended daily calorie (2000)
    		printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");	//Me : print out a sentence
    	else if(health_data->total_calories_intake > 2000)	//Me : When the number of calories consumed is less than the recommended daily calorie (2000)
    		printf("You have eaten more calories than planned today, but you have exercised too much!\n");	//Me : print out a sentence
	}
	
	else if (remain_calories > 0) {	//Me : when the remaining calories are more than zero
		printf("Please exercise for your health!\n");	//Me : print out a sentence
		if(health_data->total_calories_intake >= 2000)	//Me : When the calorie intake is equal to or higher than the recommended daily calorie (2000)
			printf("Your total calorie intake for today has reached your goal!\n");	//Me : print out a sentence
		else if(health_data->total_calories_intake < 2000)	//Me : When the number of calories consumed is less than the recommended daily calorie (2000)
			printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");	//Me : print out a sentence
	}
    
	 printf("=======================================================================\n");
}
