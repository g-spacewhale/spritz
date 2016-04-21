#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define TRUE 1

void spritz(char* org_word);
void print_word(int orp, char* word);

//reading speed sets the words per minute. standard is 250, you can input more through argv
int _reading_speed=250;
//what type of sentence you are reading.
int _sentence_setting= -1;

int main(int argc, char * argv[])
{	
	char buff[10000];
	double input_speed;
	int len, i=0;
	int sentence_pos=0;
	//sets reading speed, if reading speed was inputted, could be done 
	//without input_speed, but why bother
	if(argv[1])
	input_speed=atoi(argv[1]);
	else
	input_speed=250;
	//reading speed stuff
	_reading_speed=(int)(((60.0/input_speed))*1000000);
	printf("reading speed set to %.0f\n", input_speed);
	sleep(1);
	//check if stdin is empty, not working yet, get to work
	while(TRUE)
	{
		fgets(buff,600,stdin);
		if (buff[0]==EOF)
			{	
				printf("EOF");
				return 0;
			}
		//printf("%s",buff);
		//sleep(10);
		int buff_len=(int)strlen(buff);
		char * pch;
		pch = strtok(buff," ,.-\n\r\t");
		while (pch != NULL)
		{
			len = strlen(pch);
			
			//following while checks what the setting of the current sentence is by searching end of sentence indocator.
			
			while(_sentence_setting==-1)
			{
				if((sentence_pos+i)>buff_len)
				{	
					_sentence_setting=1;
				}
				if(buff[sentence_pos+i]=='!')
				_sentence_setting=2;
				else if(buff[sentence_pos+i]=='?')
				_sentence_setting=3;
				else if(buff[sentence_pos+i]=='.')
				_sentence_setting=1;
				i++;
			}
			
			spritz(pch);
			//if after spritz so that current words sentence endings are still printend in setting
			if(pch[len-1]=='?' || pch[len-1]=='!'||pch[len-1]=='.')
			{
				//printf("Sentence finished, should change settings now!\n");
				//sleep(1);
				_sentence_setting =-1;
			}
			sentence_pos+=i;	
			i=0;

			pch = strtok (NULL, " ,.-");
		}

	}
	return 0;
}

void spritz(char* org_word)
{
	int orp;
	//get length of word

	int i=1;
	char tmpchar[11]={0};
	
	i=strlen(org_word);

	//find ORP of word
	switch(i)
	{
	case 1:
		orp = 1;
		break;
	case 2:
	case 3:
	case 4:
	case 5:
		orp = 2;
		break;
	case 6:
	case 7:
	case 8:
	case 9:
		orp = 3;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
		orp = 4;
		break;
	default:
		//if string longer that 10, split up, print first one, check second one
		strncpy(tmpchar, org_word, strlen(org_word)>10?10:strlen(org_word));
		print_word(4,tmpchar);
		spritz(&org_word[10]);
		return;
	}
	//printf("%d,%s\n",orp,org_word);
	print_word(orp,org_word);
}
void print_word(int orp, char* word)
{
	usleep(_reading_speed);
	char words[32]={0};
	char first_part[16]={0};
	//char last_part[16]={0};
	int i=0;
	//10 is basic offset of word, the farther away the offset the less offset has to be used
	system("clear");
	while(i<10-orp)
	{
		strcat(words," ");
		i++;
	}
	strcat(words, word);
	strcat(words,"\n");
	strncpy(first_part,words,9);
	//strncpy(last_part,&words[9],10);
	switch(_sentence_setting)
	{
		case-1:
		printf("%s"ANSI_COLOR_CYAN"%c" ANSI_COLOR_RESET"%s\n",first_part,words[9],&words[10]);
		break;
	case 1:
		printf("%s"ANSI_COLOR_CYAN"%c" ANSI_COLOR_RESET"%s\n",first_part,words[9],&words[10]);
		break;
	case 2:
		printf("%s"ANSI_COLOR_RED"%c" ANSI_COLOR_RESET"%s\n",first_part,words[9],&words[10]);
		break;
	case 3:
		printf("%s"ANSI_COLOR_GREEN"%c" ANSI_COLOR_RESET"%s\n",first_part,words[9],&words[10]);
		break;
	default:
		printf("%s"ANSI_COLOR_CYAN"%c" ANSI_COLOR_RESET"%s\n",first_part,words[9],&words[10]);
		break;
		
	}

	return;
}