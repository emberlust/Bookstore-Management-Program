#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "my_lib.h"
#include "my_io.h"
#include "random_data.h"

void random_string(int length, char* new_string)//generare string aleator
{
	char string_c[] = "abcdefghijklmnopqestuvwxyz ";
	new_string[length - 2] = 'a';
	for (int i = 0; i < length - 1; i++)
	{
		new_string[i] = string_c[rand() % strlen(string_c)];//se alege aleator un caracter predefinit
		if (new_string[0] == ' ' || new_string[length - 2] == ' ')//coditie ca primul si ultimul caracte sa nu fie whitespace
		{
			i--;
		}
	}
	new_string[length - 1] = '\0';//marcarea sfarsitului stringului
}

void random_books(int no_books)
{
	FILE* data;
	data = fopen("data.in", "w");

	srand(time(NULL));


	for (int iterator_books = 0; iterator_books < no_books; iterator_books++)//secventa pentru generarea a n carti
	{
	    //memoria este alocata dinamic si apoi golita
		char* book_name;
		int book_len = rand() % 10 + 3;
		book_name = malloc(book_len * sizeof(char));

		int nr_coaut = rand() % 10;
		random_string(book_len, book_name);
		fprintf(data, "%s\n", book_name);
		free(book_name);

		char* aut_name;
		int aut_len = rand() % 10 + 3;
		aut_name = malloc(aut_len * sizeof(char));
		random_string(aut_len, aut_name);
		fprintf(data, "%s\n", aut_name);
		free(aut_name);
		fprintf(data, "%d\n", nr_coaut);

		for (int coauthors_iterator = 0; coauthors_iterator < nr_coaut; coauthors_iterator++)
		{
			char* coaut_name;
			int aut_len = rand() % 10 + 3;
			coaut_name = malloc(aut_len * sizeof(char));
			random_string(aut_len, coaut_name);
			fprintf(data, "%s\n", coaut_name);
			free(coaut_name);
		}

	}
	fclose(data);
}

void test_f(struct a_book* books_list, struct an_author** authors_list)//algoritm de testare a datelor
{
    	FILE* book_data;
    srand(time(NULL));
    	    unsigned int no_books = 0;
			printf("    Introduceti numarul cartilor generate: \n    ");
			scanf("%d%*c", &no_books);

			clock_t begin = clock();

			// se initializeaza biblioteca cu un un numar predefinit de carti generate aleator
			random_books(no_books);
			book_data = fopen("data.in", "r");
			for (; no_books; no_books--)
			{
				read_fk(books_list, authors_list, book_data);
			}
			fclose(book_data);
			clock_t end = clock();

			double time_spent_generate_add = (double)(end - begin) / CLOCKS_PER_SEC;

			printf("timp generare si adaugare: %lf\n", time_spent_generate_add);

			unsigned int no_tests;

			printf("    Introduceti numarul de teste pentru determinarea listei de carti care au co-autor un autor dat: \n    ");
			scanf("%d%*c", &no_tests);

			for(;no_tests;no_tests--)//teste aleatoare de cautare a listei de carti
			{
			    begin = clock();
                char random_author_name[MAX_NAME];
                random_string(rand() % 10 + 2,random_author_name);

                struct an_author* random_author = check_author_entry(authors_list['z'-random_author_name[0]],random_author_name);
                struct a_book** list;
                if (random_author)
                {
                    no_books = random_author->no_books_coauthored;
                    list = random_author->books_coauthored_list;
                }
                end = clock();

                double time_spent_find_books = (double)(end - begin) / CLOCKS_PER_SEC;
                printf("timp cautare test %d: %lf\n",no_tests, time_spent_find_books);
			}

			unsigned int no_authors = 0;

			printf("    Introduceti numarul de teste pentru determinarea listei de co-autori pentru o carte: \n    ");
			scanf("%d%*c", &no_tests);

			for(;no_tests;no_tests--)//teste aleatoare de cautare a listei de coautori
			{
			    begin = clock();
                char random_book_name[MAX_NAME];
                random_string(rand() % 10 + 2,random_book_name);

                struct a_book* random_book = check_book_entry(books_list,random_book_name);
                struct an_author** list;
                if (random_book)
                {
                    no_authors = random_book->no_coauthors;
                    list = random_book->coauthors_list;
                }
                end = clock();

                double time_spent_find_authors = (double)(end - begin) / CLOCKS_PER_SEC;
                printf("timp cautare test %d: %lf\n",no_tests, time_spent_find_authors);
			}

}
