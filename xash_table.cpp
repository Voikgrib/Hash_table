
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<locale>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#define DEBUG( debug_info )		if(1 == 0) printf(debug_info);


#define WRITE_NODE														\
			while(cur_node->next != NULL)								\
			{															\
				if(strcmp(cur_node->buffer, &my_buff[cur_pos]) == 0)		\
				{														\
					cur_node->counter++;								\
					need_create = false;								\
				}														\
				cur_node = cur_node->next;								\
			}															\
																		\
			if(need_create == true)										\
				cur_node = node_creator(my_buff, cur_pos, cur_node);	\
			while(my_buff[cur_pos] != '\0')								\
				cur_pos++;												\


#define WORDS_TYPE		33
#define GRAPH_TYPE		66


#define IN_ONE			10
#define IN_ALPHABET		20
#define IN_LEN			30
#define IN_ASCII_SYM	40
#define IN_GNU			50
#define IN_MAGIC		60

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

const int Max_massive_size = 1000;
const int Max_word_size = 100;
const int Poizon = -13;

//-----------------------------------------------
//! This class realize struct with buffer
//-----------------------------------------------
class c_buffer
{
	public:

	char* buffer;
	long int size;
};


//-----------------------------------------------
//! This class realize one node of xash tables
//-----------------------------------------------
class xash_node
{
	public:

	int counter;
	char* buffer;
	class xash_node* next;

	  //=============//
	 // Constructor //
	//=============//
	xash_node()
	{
		counter = 0;
		buffer = new char [Max_word_size];
		next = NULL;
	}

	  //===============//
	 // Deconstructor //
	//===============//
	~xash_node()
	{
		counter = Poizon;
		delete [] buffer;
	}
};

class c_buffer *buffer_get(void);

class xash_node* node_creator(char *my_buff, int buf_pos, class xash_node* cur_node);
class xash_node* xash_gen(char *my_buff, long int buffer_size, int xash_type);

long int get_file_size(FILE *text);
long int file_read(FILE *text, long int size_of_text, char* my_buff);

void n_sub(char *my_buff, long int size_of_text);
void hash_printer(char *name_of_file, class xash_node* cur_node, int print_type);
void exel_printer(char *name_of_file, class xash_node* cur_node);

//=====================================================================
//!
//!		This programm create hash tables of word in text
//!
//!		   Author: Gribanov Vladimir
//!
//=====================================================================
int main()
{
	class c_buffer *main_buffer = NULL;

	main_buffer = buffer_get();

	// Hash generate here

	class xash_node* first_hash = xash_gen(main_buffer->buffer, main_buffer->size, IN_ONE);
	DEBUG("xash 1 generated \n")
	hash_printer("HASH_1.txt", first_hash, WORDS_TYPE);
	DEBUG("xash 1 printed \n")

	class xash_node* second_xash = xash_gen(main_buffer->buffer, main_buffer->size, IN_ALPHABET);
	DEBUG("xash 2 generated \n")
	hash_printer("HASH_2.txt", second_xash, WORDS_TYPE);
	DEBUG("xash 2 printed \n")

	class xash_node* thrid_xash = xash_gen(main_buffer->buffer, main_buffer->size, IN_LEN);
	DEBUG("xash 3 generated \n")
	hash_printer("HASH_3.txt", thrid_xash, WORDS_TYPE);
	DEBUG("xash 3 printed \n")

	class xash_node* fourth_xash = xash_gen(main_buffer->buffer, main_buffer->size, IN_ASCII_SYM);
	DEBUG("xash 4 generated \n")
	exel_printer("HASH_4_exel.csv", fourth_xash);
	hash_printer("HASH_4.txt", fourth_xash, WORDS_TYPE);
	DEBUG("xash 4 printed \n")

	class xash_node* fiveth_xash = xash_gen(main_buffer->buffer, main_buffer->size, IN_GNU);
	DEBUG("xash 5 generated \n")
	exel_printer("HASH_5_exel.csv", fiveth_xash);
	hash_printer("HASH_5.txt", fiveth_xash, WORDS_TYPE);
	DEBUG("xash 5 printed \n")

	class xash_node* sixth_xash = xash_gen(main_buffer->buffer, main_buffer->size, IN_GNU);
	DEBUG("xash 6 generated \n")
	exel_printer("HASH_6_exel.csv", sixth_xash);
	hash_printer("HASH_6.txt", sixth_xash, WORDS_TYPE);
	DEBUG("xash 6 printed \n")

	
	delete [] main_buffer->buffer;
	delete main_buffer;
	delete [] first_hash;
	delete [] second_xash;
	delete [] thrid_xash;
	delete [] fourth_xash;
	delete [] fiveth_xash;
	delete [] sixth_xash;
	return 0;
}


//---------------------------------------------------------------------
//!
//! This function print xash in csv format
//!
//---------------------------------------------------------------------
void exel_printer(char *name_of_file, class xash_node* cur_node)
{
	long int cur_pointer = 0;
	int counter = 0;
	
	class xash_node* working_node = NULL;

	FILE* cur_file = fopen(name_of_file, "w");

	fprintf(cur_file, "Num; xash;\n");

	while(cur_pointer != Max_massive_size)
	{
		counter = 0;

		working_node = &cur_node[cur_pointer];
		while(working_node->next != NULL)
		{
			working_node = working_node->next;
			counter++;
		}

		fprintf(cur_file, "%d; %d;\n", cur_pointer, counter);
	
		cur_pointer++;
	}

	fclose(cur_file);
}


//---------------------------------------------------------------------
//!
//! This function print xash in readable file
//!
//! @param[in] char *name_of_file - name of new txt file
//! @param[in] class xash_node* cur_node - pointer on massive
//! @param[in] int print_type - type of printf
//!
//---------------------------------------------------------------------
void hash_printer(char *name_of_file, class xash_node* cur_node, int print_type)
{
	long int cur_pointer = 0;
	
	FILE* cur_file = fopen(name_of_file, "w");
	DEBUG("xash print->start \n")
	class xash_node* working_node = NULL;
	
	while(cur_pointer != Max_massive_size)
	{
		fprintf(cur_file, "buffer[%ld]", cur_pointer);

		if(cur_node[cur_pointer].next != NULL)
		{
			working_node = &cur_node[cur_pointer];
	
			while(working_node->next != NULL)
			{
				if(print_type == WORDS_TYPE)
					fprintf(cur_file, " -> %s", working_node->buffer);
				else if(print_type == GRAPH_TYPE)
					fprintf(cur_file, "#");

				working_node = working_node->next;
			}
		}
	
		fprintf(cur_file, "\n");
		cur_pointer++;
	}
	
	fclose(cur_file);
}


//---------------------------------------------------------------------
//!
//! Hash number 1
//!
//! @param[in] char *my_buff - указатель на буфер
//! @param[in] long int buffer_size - длина буфера
//!
//---------------------------------------------------------------------
class xash_node* xash_gen(char *my_buff, long int buffer_size, int xash_type)
{
	long int cur_pos = 0;
	long int len_pos = 0;
	unsigned long int gnu_const = 5381;
	unsigned int roll_xash = 0;
	unsigned int bit_saver = 0;
	int ascii_sym = 0;

	bool need_create = true;

	class xash_node* xash_massive = new class xash_node[Max_massive_size];
	class xash_node* cur_node = NULL;

	while(cur_pos != buffer_size)
	{
		need_create = true;
	
		if(my_buff[cur_pos] != '\0' && xash_type == IN_ONE)
		{
			cur_node = &xash_massive[Max_massive_size / 2];

			WRITE_NODE
		}
		else if(my_buff[cur_pos] != '\0' && xash_type == IN_ALPHABET)
		{
			DEBUG("2 hash test\n");
			cur_node = &xash_massive[my_buff[cur_pos]];

			WRITE_NODE
		}
		else if(my_buff[cur_pos] != '\0' && xash_type == IN_LEN)
		{
			DEBUG("3 hash test\n");
			len_pos = cur_pos;

			while(my_buff[len_pos] != '\0')
				len_pos++;

			cur_node = &xash_massive[len_pos - cur_pos];

			WRITE_NODE
		}
		else if(my_buff[cur_pos] != '\0' && xash_type == IN_ASCII_SYM)
		{
			DEBUG("4 hash test\n");
			len_pos = cur_pos;
			ascii_sym = 0;

			while(my_buff[len_pos] != '\0')
			{
				ascii_sym = ascii_sym + my_buff[len_pos];
				len_pos++;
			}

			ascii_sym = ascii_sym - ascii_sym / Max_massive_size * Max_massive_size;

			cur_node = &xash_massive[ascii_sym];

			WRITE_NODE
		}
		else if(my_buff[cur_pos] != '\0' && xash_type == IN_GNU)
		{
			DEBUG("5 hash test\n");

			gnu_const = ((gnu_const << 5) + gnu_const) + my_buff[cur_pos];
			gnu_const = gnu_const - gnu_const / Max_massive_size * Max_massive_size;
			
			cur_node = &xash_massive[gnu_const];

			WRITE_NODE
		}
		else if(my_buff[cur_pos] != '\0' && xash_type == IN_GNU)
		{
			DEBUG("6 hash test\n");
			bit_saver = 1;

			bit_saver = (roll_xash << 1) & bit_saver;
			roll_xash = (roll_xash | bit_saver) ^ my_buff[cur_pos];
			
			roll_xash = roll_xash - roll_xash / Max_massive_size * Max_massive_size;

			cur_node = &xash_massive[roll_xash];

			WRITE_NODE
		}

		cur_pos++;
	}

	return xash_massive;
}


//-----------------------------------------------------------------
//!
//! This function generate new buffer node
//!
//-----------------------------------------------------------------
class xash_node* node_creator(char *my_buff, int buf_pos, class xash_node* cur_node)
{
	int cur_pos = 0;

	cur_node->next = new class xash_node;

	while(my_buff[buf_pos] != '\0')
	{
		cur_node->buffer[cur_pos] = my_buff[buf_pos];
		cur_pos++;
		buf_pos++;
	}

	cur_pos++;
	cur_node->buffer[cur_pos] = '\0';

	return cur_node->next;
}


//-----------------------------------------------------------------
//!
//! Считывает файл в буфер, удаляя пробелы, табы и энтеры
//!
//! @param[out] char* - указатель на полученный массив
//!
//-----------------------------------------------------------------
class c_buffer *buffer_get(void)
{
	class c_buffer *main_buffer = NULL;
	main_buffer = new class c_buffer;
	main_buffer->buffer = new char [Max_word_size];
	FILE* text = fopen("cur_text.txt","r");

	main_buffer->size = get_file_size(text);
	main_buffer->buffer = new char [main_buffer->size];
	
	file_read(text, main_buffer->size, main_buffer->buffer);

	fclose(text);

	return main_buffer;
}


//-----------------------------------------------------------------
//!
//! Считывает размер файла для записи в буфер
//!
//! @param[in] FILE *text - файл, размер которого надо узнать
//!
//! @param[out] size_of_text - Размер текста
//!
//-----------------------------------------------------------------
long int get_file_size(FILE *text)
{
    long int size_of_text = 0;

    const int zero = 0;

    fseek(text, zero, SEEK_END);
    size_of_text = ftell(text);

    return size_of_text;
}


//-----------------------------------------------------------------
//!
//! Функция находит '\n', ' ', '\t'  в буфере и заменяет их на '\0'
//!
//! @param[in] char *my_buff - указатель на буфер
//! @param[in] long int size_of_text - длина буфера
//!
//-----------------------------------------------------------------
void n_sub(char *my_buff, long int size_of_text)
{
    int cur_poz = 0;

    while(cur_poz != size_of_text)
    {
        if(my_buff[cur_poz] == '\n' || my_buff[cur_poz] == ' ' || my_buff[cur_poz] == '\t' || ispunct(my_buff[cur_poz]))
            my_buff[cur_poz] = '\0';

		if('A' <= my_buff[cur_poz] && my_buff[cur_poz] <= 'Z')
			my_buff[cur_poz] = (char)tolower(my_buff[cur_poz]);

        cur_poz++;
    }
}


//------------------------------------------------------------------
//!
//! Считывает файл и записывает в буфер + возвращает количество строк
//!
//! @param[in] FILE *text - файл
//! @param[in] long int size_of_text - размер файла
//! @param[in] char* my_buff - буфер
//!
//! @param[out] num_of_str - количество строк
//!
//------------------------------------------------------------------
long int file_read(FILE *text, long int size_of_text, char* my_buff)
{
    long int num_of_str = 0;

    const int zero = 0;

    fseek(text, zero, SEEK_SET);
    fread(my_buff, sizeof(char), size_of_text, text);
    n_sub(my_buff, size_of_text);

    return num_of_str;
}


