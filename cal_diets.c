//
//  cal_diets.c
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

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    
    int n = 500;	//Me : Defining for fgets()
	char str[n];	//Me : Defining for fgets()
	
	while (fgets(str, n, file) != NULL) {	//Me : Read line by line until there is no more reading to read
    	
    	char *food_name = strtok(str, " ");	//Me : the beginning of a sentence divided by a space - using strtok for dividing a sentence
    	char *calories_intake = strtok(NULL, "\n");	//Me : dividing the remaining parts of a sentence by /n - using strtok 
		
		strcpy(diet_list[diet_list_size].food_name, food_name);	//Me : save diet_list as food_name in diet_list_size
		diet_list[diet_list_size].calories_intake = atoi(calories_intake);	//Me : save as diet_list of diet_list_size's calories_intake- Use atoi to replace string with integer
    	
    	diet_list_size++;	//Me : Increase the number of saved diet_lists -> to see if there are more than 100
    	
        if (diet_list_size >= MAX_DIETS){
        	break;
		}
    }
    fclose(file);
    
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");	
    
    for (i=0; i < diet_list_size; i++)	//Me : Repeat as many values as stored in diet_list
    	printf("%d. %s (%d kcal)\n", i+1, diet_list[i].food_name, diet_list[i].calories_intake);	//Me : Output the appropriate numbers and food menus and calories
    printf("%d. Exit\n", diet_list_size+1);	//Me : Output Exit Menu to Last Number
    
	// ToCode: to enter the diet to be chosen with exit option
    printf("Choose (1-%d): ", diet_list_size+1);	//Me : Output Choose
    scanf("%d", &choice);	//Me : Scan the menu selected by the user and save it to choice

    // ToCode: to enter the selected diet in the health data
	if((choice >= 1) && (choice <= diet_list_size)){	//Me : When choice is a food menu
		health_data->diet[health_data->diet_count] = diet_list[choice-1];	//Me : Save the selected diet_list at the diet_count of the diet array in health_data
		health_data->diet_count++;	//Me: Increase Diet_count
	
	// ToCode: to enter the total calories intake in the health data
		health_data->total_calories_intake += diet_list[choice-1].calories_intake;	//Me : Add calories from the food you choose to the total_calories_intake of health_data
	}
	else if (choice == diet_list_size+1){	//Me : When choice is a Quit menu
		printf("Go back to Main menu\n");	//Me : print "Go back to Main menu"
	}
	else {	//Me : When choice is unvalid
		printf("You choose wrong menu!\n");	//Me : print "You choose wrong menu!"
	}
	
}

