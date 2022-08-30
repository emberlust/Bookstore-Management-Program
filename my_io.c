#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "my_lib.h"
#include "my_io.h"

void read_fk(struct a_book* books_list, struct an_author** authors_list, FILE* stream)
{
	char book_name[MAX_NAME];
	char author_name[MAX_NAME];
	int no_coaut;
	char coauthor_name_buffer[MAX_NAME];

	if (stream == stdin)//se afiseaza mesajul doar daca se citeste de la tastatura, pentru a nu aglomera meniul
		printf("    Numele cartii: \n    ");
	fscanf(stream, "%[^\n]%*c", book_name);//se pot citi datele atat de la tastatura(stdin) cat si din fisier(file stream)

	if (stream == stdin)
		printf("    Numele autorului: \n    ");
	fscanf(stream, "%[^\n]%*c", author_name);


	if (stream == stdin)
		printf("    Numar coautori: \n    ");
	fscanf(stream, "%d%*c", &no_coaut);

	input_book(books_list, book_name, no_coaut);
	link_author(books_list->next_book, authors_list, author_name);

	if (stream == stdin && no_coaut != 0)
		printf("    Numele coautorilor: \n    ");

	for (unsigned int coaut_itr = 0; coaut_itr < no_coaut; coaut_itr++)
	{
		fscanf(stream, "%[^\n]%*c", coauthor_name_buffer);
		link_coauthor(books_list->next_book, authors_list, coauthor_name_buffer, coaut_itr);
	}

}

void print_books_array(struct a_book** books_list, unsigned int no_books)
{
	for (unsigned int bk_itr = 0; bk_itr < no_books; bk_itr++)
	{
		printf("%s, ", books_list[bk_itr]->name);

	}
	printf("\b\b \n");
}

void print_authors_array(struct an_author** authors_list, unsigned int no_authors)
{
	for (unsigned int at_itr = 0; at_itr < no_authors; at_itr++)
	{
		printf("%s, ", authors_list[at_itr]->name);
	}
	printf("\b\b \n");
}
