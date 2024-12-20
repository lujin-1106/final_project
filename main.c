//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    
    // Tocode: to read the list of the exercises and diets
    loadExercises("exercises.txt");	//Me : Run the loadExercises function with the "exercises.txt" file as a parameter
    loadDiets("diets.txt");	//Me : Run the loadDiets function with the "diets.txt" file as a parameter
    
    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
    	int remain_calories = health_data.total_calories_intake - 1300 - health_data.total_calories_burned;	//Me : Calculation of remaining calories
    	
    	if (remain_calories == 0){	//Me : When the remaining calories are zero
            printf("You have consumed all your calories for today! \n");	
            choice = 4;	//Me : Save the choice value to 4 -> enable termination
		} 
		else{
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        }
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	inputExercise(&health_data); //Me : inputExercise function is executed
                break;
                
            case 2:
            	inputDiet(&health_data); //Me : inputDiet function is executed
                break;
                
            case 3:
            	printHealthData(&health_data); //Me : 
                break;
                
            case 4:
            	
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (choice != 4);	//Me : Repeat over and over again when the choice value is not 4 = If the choice value is 4, it ends

    return 0;
}

