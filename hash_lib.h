

class xash_node* stupid_hash(char *my_buff, unsigned long int first_val, class xash_node* xash_massive)
{
	DEBUG("1 hash test\n");
	return &xash_massive[Max_massive_size / 2];
}


class xash_node* alphabet_hash(char *my_buff, unsigned long int first_val, class xash_node* xash_massive)
{
	DEBUG("2 hash test\n");
	return &xash_massive[my_buff[first_val]];
}


class xash_node* lengh_hash(char *my_buff, unsigned long int first_val, class xash_node* xash_massive)
{
	DEBUG("3 hash test\n");
	unsigned long int len_pos = first_val;

	while(my_buff[len_pos] != '\0')
		len_pos++;

	return &xash_massive[len_pos - first_val];
}

class xash_node* ascii_hash(char *my_buff, unsigned long int first_val, class xash_node* xash_massive)
{
	DEBUG("4 hash test\n");
	int len_pos = first_val;
	int ascii_sym = 0;

	while(my_buff[len_pos] != '\0')
	{
		ascii_sym = ascii_sym + my_buff[len_pos];
		len_pos++;
	}

	ascii_sym = ascii_sym % Max_massive_size;

	return &xash_massive[ascii_sym];
}


class xash_node* gnu_hash(char *my_buff, unsigned long int first_val, class xash_node* xash_massive)
{
	DEBUG("5 hash test\n");

	static unsigned long int gnu_const = 5381;

	gnu_const = ((gnu_const << 5) + gnu_const) + my_buff[first_val];
	gnu_const = gnu_const % Max_massive_size;
			
	return &xash_massive[gnu_const];
}


class xash_node* roll_hash(char *my_buff, unsigned long int first_val, class xash_node* xash_massive)
{
	DEBUG("6 hash test\n");
	unsigned short int bit_saver = 1;
	static unsigned short roll_xash = 0;

			//bit_saver = (roll_xash >> 1) & bit_saver;		// LEFT! || по три для каждого символа || указателем на ф-цию
	bit_saver = roll_xash & bit_saver;
	roll_xash = ((roll_xash >> 1) | (roll_xash << 15)) ^ my_buff[first_val];
			
	roll_xash = roll_xash % Max_massive_size;

	return &xash_massive[roll_xash];
}






