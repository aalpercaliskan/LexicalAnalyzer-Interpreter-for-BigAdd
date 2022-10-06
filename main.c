#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 50 // struct array capacity  
#define MAX_ARR 50 //array capacity for loop rule

int loop_number_arr[MAX_ARR]; //LNA (for loop rule)
int top_LNA = -1;

// for loop rule
void pushLNA(int item)
{
	top_LNA += 1;
	loop_number_arr[top_LNA] = item;
}

// for loop rule
int popLNA()
{
	int item = loop_number_arr[top_LNA];
	loop_number_arr[top_LNA] = 0; 
	top_LNA -= 1;
	return item;
}

// for loop rule
int lenLNA()
{
	return top_LNA +1;
}

int loop_location_arr[MAX_ARR]; //LLA (to find open block index for loop rule)
int top_LLA = -1;

// for loop rule
void pushLLA(int item)
{
	top_LLA += 1;
	loop_location_arr[top_LLA] = item;
}

// for loop rule
void pushToIndexLLA(int item,int index)
{
	loop_location_arr[index] = item;
	if(index > top_LLA)
	{
		top_LLA = index;
	}
}

// for loop rule
int popLLA()
{
	int item = loop_location_arr[top_LLA];
	loop_location_arr[top_LLA] = 0; 
	top_LLA -= 1;
	return item;
}

// for loop rule
int lenLLA()
{
	return top_LLA+1;
}

// for loop rule
int peekLLA()
{
	return loop_location_arr[top_LLA];	
}

int keyword_location_arr[MAX_ARR]; //KLA (to find 'add', 'sub', 'out','move' and 'int' keywords indexes)
int top_KLA = -1;

// for loop rule
void pushKLA(int item)
{
	top_KLA += 1;
	keyword_location_arr[top_KLA] = item;
}

// for loop rule
int popKLA()
{
	int item = keyword_location_arr[top_KLA];
	keyword_location_arr[top_KLA] = 0; //sil sonra
	top_KLA -= 1;
	return item;
}

// for loop rule
int lenKLA()
{
	return top_KLA + 1;
}

// for loop rule
int index_at_KLA(int item)
{
	int i;
	for(i = 0; i <= top_KLA; i++)
	{
		if(keyword_location_arr[i] == item || keyword_location_arr[i] > item) 
		{
			return i;
		}
	}
}

// for loop rule
void resetKLA() 
{
	while(top_KLA != -1)
	{
		popKLA();
	}
}

int variable_index_arr[MAX_ARR]; //VIA (hold variables indexes at struct)
int top_VIA = -1;

// for loop rule
void pushVIA(int item)
{
	top_VIA += 1;
	variable_index_arr[top_VIA] = item;
}

// for loop rule
int popVIA()
{
	int item = variable_index_arr[top_VIA];
	variable_index_arr[top_VIA] = 0;
	top_VIA -=1;
	return item;
}

/* holds variables and their corresponding integer values*/
struct variable
{
    char variable_name[200];
    int variable_value;
};

/*reads letters until there is a space and forms a word.*/
void scan(char *str, FILE *fp,FILE *wp, int *current_line, int *is_end_of_line, int *is_separator, int *eol_without_dut, long *number_of_char)
{
	char c;
	int len = strlen(str);
	if(*eol_without_dut == 1) //if line is not finised with '.' and lenght of word longer 0 than current_line value is changed after scan function called again
	{						  //and eol_without_dut set 0					
		*current_line += 1;   
		*eol_without_dut = 0; 
	}
	*str = 0; // str is reset
	*is_end_of_line = 0;
	*is_separator = 0;
	
	while(true)
	{
		//times can not be adjacent to ']'  
		if(strcmp(str,"times")==0)
		{
			break;
		}
		
		c = fgetc(fp);
		*number_of_char += 1;
		
		if (c == EOF)
		{
			// space string is created when file reading is finished.
			// So exit 'checkKeyword' function.
			if(strlen(str) == 0)
			{
				strncat(str, " ", 1);
			}	
			break;
		}
		
		else if(c == ',') 
		{
			*is_separator = 1;	
			strncat(str, &c, 1);			
			break;
		}
		
		else if(c == '.')
		{
			*is_end_of_line = 1;		
			strncat(str, &c, 1);	
			break;
		}
		
		else if( c == '"')
		{
			
			strncat(str, &c, 1);
			c = fgetc(fp);
			*number_of_char += 1;
			while(c != '"')
			{
				if(c == EOF)
				{
					printf("\n(Line %d) Error: Expected (\") not found\n",*current_line);
					printf("\nPress any key to exit...");
					getchar();
					getchar();
					exit(1);		
				}
				if(c == '\n')
				{
					*current_line += 1;
					*number_of_char += 1;
				}
				strncat(str, &c, 1);
				c = fgetc(fp);	
				*number_of_char += 1;		
			}
			strncat(str, &c, 1);
			break;
			
		}
		else if(c == '[' || c == ']')
		{
			strncat(str, &c, 1);
			break;
		}
		
		else if(c  == '{')
		{
			while(c != '}')
			{
				c =fgetc(fp);
				*number_of_char += 1;
				if(c == '\n')
				{
					*current_line += 1;
					*number_of_char += 1;	
				}
				else if(c == EOF)
				{
        			printf("\n(Line %d) Error: Expected '}' not found\n",*current_line);
        			printf("\nPress any key to exit...");
        			getchar();
        			getchar();
					exit(1);
		   	 	}	
			}
			break;			
		}
		
		else if(c == '\n')
		{
			*number_of_char += 1;
			if(strlen(str) == 0)
			{
				*current_line += 1;	
			}
			else //if line is not finised with '.' and lenght of word longer 0 than current_line value is not changed until scan function called again
			{
				*eol_without_dut = 1;
			}		
			break;
		}
		
		else if(c == ' ' || c == '\t')
		{
			break;
		}
		
		else
		{
			strncat(str, &c, 1);
		}		
	}
	if(strlen(str)==0)
	{
		scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	}
	
}


//Checks for valid keyword according to BigAdd language
bool isKeyword(char *str)
{
    if (!strcmp(str, "int") || !strcmp(str, "newline")  || !strcmp(str, "move") || !strcmp(str, "loop") || !strcmp(str, "times") || !strcmp(str, "out") ||!strcmp(str, "sub") || !strcmp(str, "add") || !strcmp(str, "to") || !strcmp(str, "from"))
    {
        return (true);
    }

    return (false);
}

/*if int_value is 0: integer variable
  if int_value is 1: integer constant
  if int_value is -1: invalid integer value */
int getIntValue(char *str,FILE *wp, int *current_line,struct variable *arr_variables, int *index_variable)
{
    
	int len = strlen(str);
	int int_value = -1;
	
    if (len == 0 || len > 100)
    {
    	return (int_value);  
    }

    int i;
    for(i = 0; i < *index_variable+1; i++){
        if(strcmp(arr_variables[i].variable_name,str) ==0)
        {
            int_value=0;
            return (int_value);         
      	}
    }
    
    for (i = 0; i < len; i++)
    {
        if ((str[i] == '-' && i == 0 && len!=1) || str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9')
        {
            continue;
        }
        else
        {
        	return (int_value);           
        }
    }
    int_value=1;

    return (int_value);
}

//check variable rules
bool isValidVariable(char *str)
{
    int len = strlen(str);
    if(len<=20 && isalpha(str[0]))
    {
        int i;
        for(i =1;i<len;i++)
        {
            if(isalnum(str[i]) || str[i]=='_' || str[i] == ' ')
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

//remove '.' and ','
char *remove_last_char(char *str)
{
    int len=strlen(str);  
    str[len-1] = '\0';
    
}

void checkIntRule(char *str,FILE *fp,FILE *wp,  int *current_line,struct variable *arr_variables, int *index_variable, int *is_end_of_line, int *is_separator, int *eol_without_dut,long *number_of_char )
{
//	printf("Keyword %s\n", str);
    fprintf(wp,"Keyword %s\n", str);
    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
    
    if(*is_end_of_line == 1)
	{
		remove_last_char(str);
	}  
	  
    //variable kontrol
    if(!isValidVariable(str))
    {
        printf("\n(Line %d) Error: Invalid variable '%s'\n",*current_line,str);
        printf("\nPress any key to exit...");
		getchar();
		getchar();
		exit(1);    
    }
    else if(isKeyword(str))
    {
        printf("\n(Line %d) Error : Variables can not be keyword '%s'\n",*current_line, str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);  
    }    
    else
    {
        //printf("Identifier %s\n", str);
        fprintf(wp,"Identifier %s\n", str);
    
		/*creat variable first time or if it created previous than set value 0*/
       	int i;
   	 	bool isCreated = false;
       	for(i = 0; i < *index_variable+1; i++)
		{
           	if(strcmp(arr_variables[i].variable_name,str) ==0)
           	{
               	isCreated = true;
               	break;
           	}
       	}
       	if(isCreated)
		{
           	arr_variables[i].variable_value = 0;
   	 	}
       	else
       	{
           	strcpy(arr_variables[*index_variable].variable_name,str);
           	arr_variables[*index_variable].variable_value = 0;
           	*index_variable += 1;
       	}	    		
    }
	
	if(*is_end_of_line == 1)
	{
        fprintf(wp,"EndOfLine\n");
        scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	}
	
		
	else
	{
		int previous_line = *current_line; //to print the number of lines correctly when giving an error  
		scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char); //if there is blank before '.'
		if(strcmp(str,".") == 0)
		{
        	fprintf(wp,"EndOfLine\n");
        	scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
		}
		else
		{
			printf("\n(Line %d) Error: Expected '.' not found\n",previous_line);
			printf("\nPress any key to exit...");
			getchar();
			getchar();
			exit(1);  
		}
	}	 
}

void checkSubRule(char *str,FILE *fp,FILE *wp, int *current_line,struct variable *arr_variables, int *index_variable, int *is_end_of_line, int *is_separator,int *eol_without_dut, long *number_of_char )
{	
    fprintf(wp,"Keyword %s\n", str);
    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
    
    int value; //hold integer to operation
    int int_value = getIntValue(str,wp,current_line,arr_variables, index_variable);
    if (int_value == 1)
    {
        fprintf(wp,"IntConstant %s\n", str);
      	value = atoi(str);	
    }
	else if(int_value == 0)
	{
        fprintf(wp,"Identifier %s\n", str);
       	int i;
       	for(i = 0; i < *index_variable+1; i++)
		{
           	if(strcmp(arr_variables[i].variable_name,str) ==0)
           	{
               	value = arr_variables[i].variable_value; // If the variable is already defined, value take variable_value in struct.
           	}
       	} 	
    }
    else
	{
    	printf("\n(Line %d) Error: Invalid integer value '%s'\n",*current_line,str);
    	printf("\nPress any key to exit...");
		getchar();
		getchar();
		exit(1);      
	}

    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
    
    if(strcmp(str, "from") != 0)
    {
        printf("\n(Line %d) Error: Expect 'from' instead of '%s' \n", *current_line,str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);  
    }
    else
    {
        fprintf(wp, "Keyword %s\n", str);
	}
    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	
	if(*is_end_of_line == 1)
	{
		remove_last_char(str);
	}  
		 
	if(isKeyword(str))
    {
        printf("\n(Line %d) Error :Variables can not be keyword '%s'\n", *current_line,str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);  
    }
        
    else if(!isValidVariable(str))
    {
        printf("\n(Line %d) Error: Invalid variable '%s'\n",*current_line,str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);  
    }
    
	
    else
    {
    	/*if variable created previous than printing that identifier
		  else occurred error */    
      	int i;
		bool is_defined = false;
    	for(i = 0; i < *index_variable+1; i++)
		{
       		if(strcmp(arr_variables[i].variable_name,str) ==0)
       		{
           		fprintf(wp,"Identifier %s\n", str);
           		arr_variables[i].variable_value -= value; //sub value from variable_value
           		is_defined = true;
       		}
   		}	
    	if(!is_defined)
		{
			printf("\n(Line %d) Error : Undefined variable '%s'\n", *current_line,str);
			printf("\nPress any key to exit...");
			getchar();
			getchar();
	        exit(1);  
		} 
		
    }
	
    
	if(*is_end_of_line == 1)
	{
        fprintf(wp,"EndOfLine\n");
        scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	}	
	else
	{
		int previous_line = *current_line; //to print the number of lines correctly when giving an error  
		scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char); //if there is blank before '.'
		if(strcmp(str,".") == 0)
		{
        	fprintf(wp,"EndOfLine\n");
        	scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
		}
		else
		{
			printf("\n(Line %d) Error: Expected '.' not found\n",previous_line);
			printf("\nPress any key to exit...");
			getchar();
			getchar();
			exit(1);  
		}
	}    	    		 
}

void checkAddRule(char *str,FILE *fp,FILE *wp,  int *current_line,struct variable *arr_variables, int *index_variable, int *is_end_of_line, int *is_separator,int *eol_without_dut,long *number_of_char )
{	
    fprintf(wp,"Keyword %s\n", str);
    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
    
    int value; //hold integer to operation
    int int_value = getIntValue(str,wp,current_line,arr_variables, index_variable);
    if (int_value == 1)
    {
        fprintf(wp,"IntConstant %s\n", str);
      	value = atoi(str);	
    }
	else if(int_value == 0)
	{
        fprintf(wp,"Identifier %s\n", str);	
      	int i;
   	 	for(i = 0; i < *index_variable+1; i++)
		{
           	if(strcmp(arr_variables[i].variable_name,str) ==0)
           	{
               	value = arr_variables[i].variable_value; // If the variable is already defined, value take variable_value in struct.     
          	}
       	}
    	
    }
    else
	{
    	printf("\n(Line %d) Error: Invalid integer value '%s'\n",*current_line,str);
    	printf("\nPress any key to exit...");
		getchar();
		getchar();
		exit(1);      
	}

    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
    
    if(strcmp(str, "to") != 0)
    {
        printf("\n(Line %d) Error: Expect 'to' instead of '%s' \n", *current_line,str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);  
    }
    else
    {
        fprintf(wp, "Keyword %s\n", str);
	}
    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	
	if(*is_end_of_line == 1)
	{
		remove_last_char(str);
	}  
		 
	if(isKeyword(str))
    {
        printf("\n(Line %d) Error :Variables can not be keyword '%s'\n", *current_line,str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);  
    }
        
    else if(!isValidVariable(str))
    {
        printf("\n(Line %d) Error: Invalid variable '%s'\n",*current_line,str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);  
    }
    
	
    else
    {
    	/*if variable created previous than printing that identifier
		  else occurred error */    
       	int i;
		bool is_defined = false;
   		for(i = 0; i < *index_variable+1; i++)
		{
       		if(strcmp(arr_variables[i].variable_name,str) ==0)
       		{
           		fprintf(wp,"Identifier %s\n", str);
           		arr_variables[i].variable_value += value; //add value to variable_value
           		is_defined = true;
       		}
    	}
    		
    	if(!is_defined)
		{
			printf("\n(Line %d) Error : Undefined variable '%s'\n", *current_line,str);
			printf("\nPress any key to exit...");
			getchar();
			getchar();
	        exit(1);
		} 	
    }
	
    
	if(*is_end_of_line == 1)
	{
        fprintf(wp,"EndOfLine\n");
        scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	}	
	else
	{
		int previous_line = *current_line; //to print the number of lines correctly when giving an error  
		scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char); //if there is blank before '.'
		if(strcmp(str,".") == 0)
		{
        	fprintf(wp,"EndOfLine\n");
        	scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
		}
		else
		{
			printf("\n(Line %d) Error: Expected '.' not found\n",previous_line);
			printf("\nPress any key to exit...");
			getchar();
			getchar();
			exit(1);  
		}
	}    	    		 
}


void checkMoveRule(char *str,FILE *fp,FILE *wp,  int *current_line,struct variable *arr_variables, int *index_variable, int *is_end_of_line, int *is_separator,int *eol_without_dut,long *number_of_char )
{	
    fprintf(wp,"Keyword %s\n", str);
    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
    
    int value; //hold integer to operation
    int int_value = getIntValue(str,wp,current_line,arr_variables, index_variable);
    if (int_value == 1)
    {
        fprintf(wp,"IntConstant %s\n", str);
      	value = atoi(str);	
    }
	else if(int_value == 0)
	{
        fprintf(wp,"Identifier %s\n", str);
       	int i;
       	for(i = 0; i < *index_variable+1; i++)
		{
           	if(strcmp(arr_variables[i].variable_name,str) ==0)
           	{
               	value = arr_variables[i].variable_value;  // If the variable is already defined, value take variable_value in struct.    
           	}
       	}	
    }
    else
	{
    	printf("\n(Line %d) Error: Invalid integer value '%s'\n",*current_line,str);
    	printf("\nPress any key to exit...");
		getchar();
		getchar();
		exit(1);      
	}

    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
    
    if(strcmp(str, "to") != 0)
    {
        printf("\n(Line %d) Error: Expect 'to' instead of '%s' \n", *current_line,str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);  
    }
    else
    {
        fprintf(wp, "Keyword %s\n", str);
	}
    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	
	if(*is_end_of_line == 1)
	{
		remove_last_char(str);
	}  
		 
	if(isKeyword(str))
    {
        printf("\n(Line %d) Error :Variables can not be keyword '%s'\n", *current_line,str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);  
    }
        
    else if(!isValidVariable(str))
    {
        printf("\n(Line %d) Error: Invalid variable '%s'\n",*current_line,str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);  
    }
    
	
    else
    {
    	/*if variable created previous than printing that identifier
		  else occurred error */    
       	int i;
		bool is_defined = false;
   		for(i = 0; i < *index_variable+1; i++)
		{
       		if(strcmp(arr_variables[i].variable_name,str) ==0)
       		{
           		fprintf(wp,"Identifier %s\n", str);
           		arr_variables[i].variable_value = value; //move value to variable_value
           		is_defined = true;
       		}
   		}
    		
    	if(!is_defined)
		{
			printf("\n(Line %d) Error : Undefined variable '%s'\n", *current_line,str);
			printf("\nPress any key to exit...");
			getchar();
			getchar();
	        exit(1);
		} 
    }
	
    
	if(*is_end_of_line == 1)
	{
        fprintf(wp,"EndOfLine\n");
        scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	}	
	else
	{
		int previous_line = *current_line; //to print the number of lines correctly when giving an error  
		scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char); //if there is blank before '.'
		if(strcmp(str,".") == 0)
		{
        	fprintf(wp,"EndOfLine\n");
        	scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
		}
		else
		{
			printf("\n(Line %d) Error: Expected '.' not found\n",previous_line);
			printf("\nPress any key to exit...");
			getchar();
			getchar();
			exit(1);  
		}
	}    	    		 
}


void checkOutRule(char *str,FILE *fp,FILE *wp,  int *current_line,struct variable *arr_variables, int *index_variable, int *is_end_of_line, int *is_separator,int *eol_without_dut, long *number_of_char )
{
    fprintf(wp,"Keyword %s\n", str);
	scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	
    while(true)
	{
		if(*is_end_of_line == 1 || *is_separator == 1)
		{
			remove_last_char(str);
		}  
		
		int int_value = getIntValue(str,wp,current_line,arr_variables, index_variable);	
		if(int_value == 1)
    	{
            fprintf(wp,"IntConstant %s\n", str);
			printf(str);   
        }
        
		else if(int_value == 0)
		{
            fprintf(wp,"Identifier %s\n", str);
           	int i;
        	for(i = 0; i < *index_variable+1; i++)
			{
           		if(strcmp(arr_variables[i].variable_name,str) ==0)
           		{
               		printf("%d",arr_variables[i].variable_value);      
           		}
       	 	} 	 	
        }
        
		else if(strcmp(str, "newline")==0)
		{
        	fprintf(wp,"Keyword %s\n", str);
			printf("\n");	
		}
		
		else if (str[0] == '"')
    	{
    		int len = strlen(str);
			if(feof(fp) != 0)  //if string not closed with (") error occurred
			{
				printf("\n(Line %d) Error: Expected (\") not found\n",*current_line);
				printf("\nPress any key to exit...");
				getchar();
				getchar();
				exit(1);
			}
    		if(str[len -1] != '"') //if string length cannot be longer than 20 error occurred
			{
				printf("\n(Line %d) Error: The length of the string constant can not exceed 20 '%s...'\n",*current_line,str);
				printf("\nPress any key to exit...");
				getchar();
				getchar();
				exit(1);
			}
			else
			{
        		fprintf(wp,"String Constant %s\n", str);
        		int i;
        		for(i = 1; i <strlen(str)-1;i++)
				{
					printf("%c",str[i]);
				}	
			}
		}
				
        else 
		{
			printf("\n(Line %d) Error: Expect string or integer value or 'newline' instead of '%s'\n",*current_line,str);
			printf("\nPress any key to exit...");
			getchar();
			getchar();
			exit(1);
		}
				
		if(*is_separator == 1)
		{
            fprintf(wp,"Separator\n");
            scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char); 
            if(strcmp(str,".") == 0) //can not be '.' after ','
			{
				printf("\n(Line %d) Error: Expect string or integer value or 'newline' after ','\nEndOfLine\n",*current_line,str);
				printf("\nPress any key to exit...");
				getchar();
				getchar();
				exit(1);
			}
		}
		
		else if(*is_end_of_line == 1)
		{			
            fprintf(wp,"EndOfLine\n");
            scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);; 
           	break;
		}
		
		else //if there is blank before '.'
        { 
		    int previous_line = *current_line; //to print the number of lines correctly when giving an error     	
            scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
            
            if(strcmp(str,",") == 0)
			{
            	fprintf(wp,"Separator\n");
            	scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
            	if(strcmp(str,".") == 0) //can not be '.' after ','
				{
					printf("\n(Line %d) Error: Expect string or integer value or 'newline' after ','\nEndOfLine\n",*current_line,str);
					printf("\nPress any key to exit...");
					getchar();
					getchar();
					exit(1);
				}
			}
			
			else if(strcmp(str,".") == 0)
			{			
           		fprintf(wp,"EndOfLine\n");
            	scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);  
           		break;
			}
			
			else 
			{
				printf("\n(Line %d) Error: Expected '.' not found \n",previous_line);
				printf("\nPress any key to exit...");
				getchar();
				getchar();
				exit(1);
			}        
        }
	}    
}

//for loop rule
void checkRules(char *str,FILE *fp,FILE *wp,  int *current_line,struct variable *arr_variables, int *index_variable, int *is_end_of_line, int *is_separator,int *eol_without_dut, long *number_of_char )
{
	if (strcmp(str,".") == 0)
   	{
       	scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
   	}
   	else if(strcmp(str, "int")==0)
    {
        checkIntRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
   	}
    else if(strcmp(str, "move")==0)
    {		
    	checkMoveRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);		
	}
    else if( strcmp(str, "add")==0)
	{
		checkAddRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	}   
   	else if(strcmp(str, "sub")==0 )
    {
   		checkSubRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
   	}
   	else if(strcmp(str, "out") == 0)
	{
		checkOutRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	}
}

void checkLoopRule(char *str,FILE *fp,FILE *wp, int *current_line,struct variable *arr_variables, int *index_variable, int *is_end_of_line, int *is_separator,int *eol_without_dut, long *number_of_char)
{
    fprintf(wp,"Keyword %s\n", str);
    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
        
    int int_value = getIntValue(str,wp,current_line,arr_variables, index_variable);
    if (int_value == 1)
    {
        fprintf(wp,"IntConstant %s\n", str);
        int loop_value = atoi(str);
        if(loop_value < 1)
		{
			printf("\n(Line %d) Error: Invalid loop value '%s'\n",*current_line,str); 
			printf("\nPress any key to exit...");	
			getchar();
			getchar();
			exit(1);
		}
		pushLNA(loop_value);
		pushVIA(-1); //if int value not variable value push variable_index_arr -1.
		
        
    }
	else if(int_value == 0)
	{
        fprintf(wp,"Identifier %s\n", str);
        int i;
        for(i = 0; i < *index_variable+1; i++)
		{
            if(strcmp(arr_variables[i].variable_name,str) ==0)
            {
            	if(arr_variables[i].variable_value < 1)
				{
					printf("\n(Line %d) Error: Invalid loop value '%s'\n",*current_line,str);  	
					printf("\nPress any key to exit...");
					getchar();
					getchar();
					exit(1);
				}
           		pushLNA(arr_variables[i].variable_value);
           		pushVIA(i); //if int value is variable value push variable_index_arr variable_value's index (i).
            	break;
            }
    	}     
    }
    else
	{
    	printf("\n(Line %d) Error: Invalid integer value '%s'\n",*current_line,str); 
    	printf("\nPress any key to exit...");
		getchar();
		getchar();
		exit(1); 
	}

    scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
    if(strcmp(str, "times") != 0)
    {
        printf("\n(Line %d) Error: Expect 'times' instead of '%s' \n",*current_line, str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);
    }
    else
    {
     
        fprintf(wp,"Keyword %s\n", str);
     
        scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
		
		// if is not code block
		if(strcmp(str,".") == 0 || strcmp(str, "int")==0 || strcmp(str, "move")==0 || strcmp(str, "add")==0 ||strcmp(str, "sub")==0 || strcmp(str, "out") == 0)
		{
			int location_keyword; //hold keyword's index
			fseek(fp,-1,SEEK_CUR);
			if(fgetc(fp) == '\n') // if keyword at end of line
			{
				location_keyword = *number_of_char -strlen(str) -2;
				pushKLA(location_keyword);	
			}
			else
			{
				location_keyword = *number_of_char -strlen(str) -1;
				pushKLA(location_keyword);
			}
			checkRules(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
			
			int previous_number_of_char = *number_of_char; 
			int previous_current_line = *current_line;
				
			int len,iteration_number,i,j,variable_index;
			int starting_index = index_at_KLA(location_keyword);
			
			
			while(lenLLA() != lenLNA())
			{
				iteration_number = popLNA();
				variable_index = popVIA();
				len = lenKLA();
				if(variable_index == -1)
				{
					iteration_number -= 1;
					while(iteration_number > 0)
					{
						for(j = starting_index; j < len; j++)
						{
							pushKLA(location_keyword);
							fseek(fp,location_keyword,SEEK_SET);
							scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
							checkRules(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
						}
						iteration_number -= 1;
					}
				}
				else
				{
					arr_variables[variable_index].variable_value -= 1;
					while(arr_variables[variable_index].variable_value > 0)
					{
						for(j = starting_index; j < len; j++)
						{
							pushKLA(location_keyword);
							fseek(fp,location_keyword,SEEK_SET);
							scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
							checkRules(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
						}
						arr_variables[variable_index].variable_value -= 1;	
					}
				}
			}
			*current_line = previous_current_line;
			*number_of_char = previous_number_of_char;		
		}
		
		//if there is a nested loop	
		else if(strcmp(str,"loop") == 0)
		{
			checkLoopRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);					
		}
		
		// if there is code block
		else if(strcmp(str,"[") == 0)
		{
			int last_index_LNA = lenLNA()-1;
			pushToIndexLLA(*number_of_char,last_index_LNA);
			scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
			while(strcmp(str,"]")!= 0)
			{
				if(strcmp(str,".") == 0 || strcmp(str, "int")==0 || strcmp(str, "move")==0 || strcmp(str, "add")==0 ||strcmp(str, "sub")==0 || strcmp(str, "out") == 0)
				{
					fseek(fp,-1,SEEK_CUR);
					if(fgetc(fp) == '\n')
					{
						pushKLA(*number_of_char -strlen(str) -2);	
					}
					else
					{
						pushKLA(*number_of_char -strlen(str) -1);
					}
					
					checkRules(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
					
				}
				else if(strcmp(str,"loop") == 0)
				{
					checkLoopRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);						
				}
				else if(strcmp(str," ") == 0) //if end of file
				{
					printf("\n(Line %d) Error: Expected ']' not found \n", *current_line);
					printf("\nPress any key to exit...");
					getchar();
					getchar();
					exit(1);
				}
				else
				{
					printf("\n(Line %d) Error: Invalid keyword '%s'\n",*current_line,str);
					printf("\nPress any key to exit...");
					getchar();
					getchar();
					exit(1);
				}	
				
			}
			int previous_number_of_char = *number_of_char;
			int previous_current_line = *current_line;
			
			int len, iteration_number,i,j,variable_index;
			int starting_index = index_at_KLA(peekLLA());
					
			do
			{	
				popLLA();
				iteration_number = popLNA();
				variable_index = popVIA();	
				len = lenKLA();
				if(variable_index == -1)
				{
					iteration_number -= 1;
					while(iteration_number > 0)
					{
						for(j = starting_index; j < len; j++)
						{
							pushKLA(keyword_location_arr[j]);
							fseek(fp,keyword_location_arr[j],SEEK_SET);
							scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
							checkRules(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
						}
						iteration_number -= 1;
					}	
				}
				else
				{
					arr_variables[variable_index].variable_value -= 1;
					while(arr_variables[variable_index].variable_value > 0)
					{
						for(j = starting_index; j < len; j++)
						{
							pushKLA(keyword_location_arr[j]);
							fseek(fp,keyword_location_arr[j],SEEK_SET);
							scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
							checkRules(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
						}
						arr_variables[variable_index].variable_value -= 1;
					}	
				}	
			}
			while(lenLLA() >=1 && peekLLA() == 0);
			
			*current_line = previous_current_line;
			*number_of_char = previous_number_of_char;	
			fseek(fp,*number_of_char,SEEK_SET);	
			scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);		
		}
		else
		{
			printf("\n(Line %d) Error: Invalid keyword '%s'\n",*current_line,str);
			printf("\nPress any key to exit...");
			getchar();
			getchar();
			exit(1);
		}	
		
	
	}
	       
}


/* Checks whether the incoming word is a valid keyword or '.'(End of line) Then the corresponding rule function is called */
void checkKeyword(char *str,FILE *fp,FILE *wp, int *current_line,struct variable *arr_variables, int *index_variable, int *is_end_of_line, int *is_separator,int *eol_without_dut, long *number_of_char )
{
	
	if(strcmp(str," ")==0) //if file reading is finished
	{
		return;
	} 
	   
	else if (strcmp(str,".") == 0)
    {
        fprintf(wp,"EndOfLine\n");
        scan(str,fp,wp,current_line,is_end_of_line,is_separator,eol_without_dut,number_of_char);
    }
    
    else if(strcmp(str, "int")==0)
    {
        checkIntRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
    }
        
    else if(strcmp(str, "move")==0)
    {	
    	checkMoveRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	}
    else if( strcmp(str, "add")==0)
	{
		checkAddRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	}   
    else if(strcmp(str, "sub")==0 )
    {     	
    	checkSubRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
    }
        
    else if(strcmp(str, "out") == 0)
	{
		checkOutRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	}
    
    else if(strcmp(str, "loop") == 0)
    {	
    	checkLoopRule(str,fp,wp, current_line,arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);		
		resetKLA(); 	     
 	}
      
    else
	{
        printf("\n(Line %d) Error: Invalid keyword '%s'\n",*current_line,str);
        printf("\nPress any key to exit...");
        getchar();
        getchar();
		exit(1);     
    }
    
    
	checkKeyword(str, fp, wp, current_line, arr_variables, index_variable,is_end_of_line,is_separator,eol_without_dut,number_of_char);
	
    
}

int main()
{
    FILE *fp;
    FILE *wp;
    
    long number_of_char = 0; //hold char indexes
    int eol_without_dut = 0; //if line is not finised with '.' and lenght of word longer 0 than it set 1 in scan function because of get correct line number (used as flag)
    int current_line = 1; //it holds number of line
    int index_variable = 0; //used for struct array's index
    char str[200]; // hold word
    int is_end_of_line = 0; // check there is '.' (used as flag)
	int is_separator = 0; // check there is ',' (used as flag)

    
    printf("Enter the file extension and file name respectively (Exp: 'ba filename'):\n");
    char input[]="";  
 	while(strcmp(input,"ba")!=0)
	{
		scanf("%s",input);
		if(strcmp(input,"ba")==0)
		{
			scanf("%s",input);
			break;
		}
	}
    
    strcat(input,".ba");
    
    if ((fp = fopen(input, "r")) == NULL)
    {
        printf("Error: Can not open the file\n");
        scanf("%s",input);
        exit(1);
    }

    if ((wp = fopen("myscript.lx", "w")) == NULL)
    {
        printf("Error: Can not write the file\n");
        scanf("%s",input);
        exit(1);
    }


    struct variable arr_variables[MAX];
    
    scan(str,fp,wp,&current_line,&is_end_of_line,&is_separator,&eol_without_dut,&number_of_char);
        
    checkKeyword(str,fp,wp, &current_line, arr_variables, &index_variable,&is_end_of_line,&is_separator,&eol_without_dut, &number_of_char);
        	

	printf("\nPress any key to exit...");
	getchar();
	getchar();
    fclose(fp);
    fclose(wp);
    return (0);
    
}
