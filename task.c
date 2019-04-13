#include "stdio.h"
#include "stdlib.h"
#include "sys/stat.h"
#include "unistd.h"
#include "sys/types.h"
#include "string.h"
//Check command user want call what function
enum check_command{
	Create_File,
	Add_Data,
	Remove_Data,
	Find_Max,
	Find_Min,
	Total
};
enum check_command State = Create_File;
char *command[6] = {"-create","-add","-remove","-max","-min","-total"};
//Pointer of file
FILE *pfile;
struct stat buffer;
char string_send_file[20];
char string_store_file[20];
//Struct to store data 
struct Data{
	int NumberID;
	int Math;
	int Physics;
	int English;
};
struct Data SV[1000];
int Number_of_struct=0;

//Delare function
void Store_data_to_struct(char argument_1[]);
void Check_line_of_file(char argument_1[]);
int Check_Argument_Main(char argument[], int num);
int Check_file_exist(char argument_1[]);
int Processing_function_create(char argument_1[]);
int Processing_function_add(char argument_1[], char argument_2[], char argument_3[], char argument_4[]);
int Processing_function_remove(char argument_1[], char argument_2[]);
int Processing_function_max(char argument_1[]);
int Processing_function_min(char argument_1[]);
int Processing_function_total(char argument_1[]);


int main(int argc, char *argv[]){
	//Check Argument of main function
	if(Check_Argument_Main(argv[1], argc)!=0)
		return -1;

	//Check command then select function process
	switch(State){
		case Create_File:	if(Processing_function_create(argv[2])!=0)
									return -1;
							break;
		case Add_Data:		if(Processing_function_add(argv[2], argv[3], argv[4], argv[5])!=0)
									return -1;
							break;
		case Remove_Data:	if(Processing_function_remove(argv[2], argv[3])!=0)	
									return -1;
							break;
		case Find_Max:		if(Processing_function_max(argv[2])!=0)		
									return -1;
							break;
		case Find_Min:		if(Processing_function_min(argv[2])!=0)		
									return -1;
							break;
		case Total:			if(Processing_function_total(argv[2])!=0)	
									return -1;
							break;
		default:			break;
	}
	//Exit main function success
	return 0;
}

/**
*		Name function: 	Read_data_to_struct
*		Description: 	Function to read number data of file
*		Argument: 		Name of file
*		Return value: 	None
**/
void Check_line_of_file(char argument_1[]){
	while(fgets(string_store_file, sizeof(string_store_file), pfile) != NULL){
		Number_of_struct++;
	}
}

/**
*		Name function: 	Read_data_to_struct
*		Description: 	Function to store data from file to struct
*		Argument: 		Name of file
*		Return value: 	None
**/
void Store_data_to_struct(char argument_1[]){
	int temp=0, num=0;
	int data_store[4];
	char *token;
	//Read data and store to struct
	while(fgets(string_store_file, sizeof(string_store_file), pfile) != NULL){
		num = 0;
		token = strtok(string_store_file, " ");
		while(token!=NULL){
			temp = atoi(token);
			data_store[num] = temp;
			token = strtok(NULL, " ");
			num++;
		}

		SV[Number_of_struct].NumberID = data_store[0];
		SV[Number_of_struct].Math = data_store[1];
		SV[Number_of_struct].Physics = data_store[2];
		SV[Number_of_struct].English = data_store[3];

		Number_of_struct++;
	}
	return;
}

/**
*		Name function: 	Check_Argument_Main
*		Description: 	Function to check argument of main function
*		Argument: 		Name of command, number of argument
*		Return value: 	Errno or success
**/
int Check_Argument_Main(char argument[], int num){
	/*Check argument for main function enough 3 element
	*	program -create filename
	*/
	if(!strcmp(argument, command[Create_File])&&num==3){
		//Call function process
		State = Create_File;
		return 0;				//Return success
	}
	/*Check argument for main function enough 6 element
	*	program -add filename x y z
	*/
	else if(!strcmp(argument, command[Add_Data])&&num==6){
		//Call function process
		State = Add_Data;
		return 0;				//Return success
	}
	/*Check argument for main function enough 4 element
	*	program -remove filename N
	*/
	else if(!strcmp(argument, command[Remove_Data])&&num==4){
		//Call function process
		State = Remove_Data;
		return 0;				//Return success
	}
	/*Check argument for main function enough 3 element
	*	program -max filename
	*/
	else if(!strcmp(argument, command[Find_Max])&&num==3){
		//Call function process
		State = Find_Max;
		return 0;				//Return success
	}
	/*Check argument for main function enough 3 element
	*	program -min filename
	*/
	else if(!strcmp(argument, command[Find_Min])&&num==3){
		//Call function process
		State = Find_Min;
		return 0;				//Return success
	}
	/*Check argument for main function enough 3 element
	*	program -total filename
	*/
	else if(!strcmp(argument, command[Total])&&num==3){
		//Call function process
		State = Total;
		return 0;				//Return success
	}
	//If check argument user type not correct
	printf("Command not correct !\n");
	return -1;
}

/**
*		Name function: 	Check_file_exist
*		Description: 	Check file exist or not
*		Argument: 		Name of filename
*		Return value: 	1(exist), 0(not).
**/
int Check_file_exist(char argument_1[]){
    int exist = stat(argument_1,&buffer);
    if(exist == 0)
        return 1;
    else // -1
        return 0;
}

/**
*		Name function: 	Processing_function_create
*		Description: 	Function to process create file
*		Argument: 		Name of filename
*		Return value: 	Errno or success
**/
int Processing_function_create(char argument_1[]){
	if(Check_file_exist(argument_1)){
		printf("File is exist !\n");
		return -1;
	}
	else{
		pfile = fopen(argument_1, "w");	//Create new file
		if(pfile==NULL)		return -1;
		fclose(pfile);
		return 0;
	}

}

/**
*		Name function: 	Processing_function_add
*		Description: 	Function to process add data to file
*		Argument: 		Name of file, math score, physics score, english score
*		Return value: 	Errno or success
**/
int Processing_function_add(char argument_1[], char argument_2[], char argument_3[], char argument_4[]){
	if(Check_file_exist(argument_1)){
		pfile = fopen(argument_1, "a+");	//Create new file
		if(pfile==NULL)		return -1;
		//First data send file
		if(buffer.st_size==0){
			sprintf(string_send_file, "1 %s %s %s\r\n", argument_2, argument_3, argument_4);
			fputs(string_send_file, pfile);
			Number_of_struct++;
		}
		else{
			//Read data and store to struct
			Check_line_of_file(argument_1);
			sprintf(string_send_file, "%d %s %s %s\r\n", Number_of_struct+1, argument_2, argument_3, argument_4);
			fputs(string_send_file, pfile);
		}
		fclose(pfile);
		return 0;
	}
	else{
		printf("File is not exist ! Plaeve type correct filename or create new file\n");
		return -1;
	}
}

/**
*		Name function: 	Processing_function_remove
*		Description: 	Function to remove data in file
*		Argument: 		Name of file, line need remove
*		Return value: 	Errno or success
**/
int Processing_function_remove(char argument_1[], char argument_2[]){
	if(Check_file_exist(argument_1)){
		int del_line=0;
		pfile = fopen(argument_1, "a+");	//Create new file
		if(pfile==NULL)		return -1;
		//First data send file
		if(buffer.st_size==0){
			printf("No data in file ! Need add data program -add math physics english\n");
		}
		else{
			//Read data and store to struct
			Store_data_to_struct(argument_1);
			del_line = atoi(argument_2);
			fclose(pfile);
			pfile = fopen(argument_1, "w");	//Create new file
			for(int i=0;i<Number_of_struct-del_line;i++)
				SV[del_line-1+i] = SV[del_line+i];
			Number_of_struct--;
			for(int i=0;i<Number_of_struct;i++){
				sprintf(string_send_file, "%d %d %d %d\n", i+1, SV[i].Math, SV[i].Physics, SV[i].English);
				fputs(string_send_file, pfile);
			}
		}
		fclose(pfile);
		return 0;
	}
	else{
		printf("File is not exist ! Plaeve type correct filename or create new file\n");
		return -1;
	}
}

/**
*		Name function: 	Check_Argument_Main
*		Description: 	Function to check argument of main function
*		Argument: 		Name of file
*		Return value: 	Errno or success
**/
int Processing_function_max(char argument_1[]){
	if(Check_file_exist(argument_1)){
		int del_line=0;
		pfile = fopen(argument_1, "r");	//Create new file
		if(pfile==NULL)		return -1;
		//First data send file
		if(buffer.st_size==0){
			printf("No data in file ! Need add data program -add math physics english\n");
		}
		else{
			struct Data max;
			int Flag_to_check_next_max=0;
			Store_data_to_struct(argument_1);
			max = SV[0];
			for(int i=1;i<Number_of_struct;i++){
				if(((float)(SV[i].Math+SV[i].Physics+SV[i].English)/3)>((float)(max.Math+max.Physics+max.English)/3)){
					max = SV[i];
					Flag_to_check_next_max=1;
				}
			}
			while(Flag_to_check_next_max){
				printf("Max avg score with NumberID: %d, Score avg: %2f\n", max.NumberID, ((float)(max.Math+max.Physics+max.English)/3));
				Flag_to_check_next_max=0;
				for(int i=max.NumberID+1;i<Number_of_struct;i++){
					if((SV[i].Math==max.Math)&&(SV[i].Physics==max.Physics)&&(SV[i].English==max.English)){
						max = SV[i];
						Flag_to_check_next_max=1;
					}
				}
			}
		}
		fclose(pfile);
		return 0;
	}
	else{
		printf("File is not exist ! Plaeve type correct filename or create new file\n");
		return -1;
	}
}

/**
*		Name function: 	Check_Argument_Main
*		Description: 	Function to check argument of main function
*		Argument: 		Name of file
*		Return value: 	Errno or success
**/
int Processing_function_min(char argument_1[]){
	if(Check_file_exist(argument_1)){
		int del_line=0;
		pfile = fopen(argument_1, "r");	//Create new file
		if(pfile==NULL)		return -1;
		//First data send file
		if(buffer.st_size==0){
			printf("No data in file ! Need add data program -add math physics english\n");
		}
		else{
			struct Data min;
			int Flag_to_check_next_min=0;
			Store_data_to_struct(argument_1);
			min = SV[0];
			for(int i=0;i<Number_of_struct;i++){
				if(((float)(SV[i].Math+SV[i].Physics+SV[i].English)/3)<((float)(min.Math+min.Physics+min.English)/3)){
					min = SV[i];
					Flag_to_check_next_min=1;
				}
			}
			while(Flag_to_check_next_min){
				printf("Min avg score with NumberID: %d, Score avg: %2f\n", min.NumberID, ((float)(min.Math+min.Physics+min.English)/3));
				Flag_to_check_next_min=0;
				for(int i=min.NumberID+1;i<Number_of_struct;i++){
					if((SV[i].Math==min.Math)&&(SV[i].Physics==min.Physics)&&(SV[i].English==min.English)){
						min = SV[i];
						Flag_to_check_next_min=1;
					}
				}
			}
		}
		fclose(pfile);
		return 0;
	}
	else{
		printf("File is not exist ! Plaeve type correct filename or create new file\n");
		return -1;
	}
}

/**
*		Name function: 	Check_Argument_Main
*		Description: 	Function to check argument of main function
*		Argument: 		Name of file
*		Return value: 	Errno or success
**/
int Processing_function_total(char argument_1[]){

}