#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "my_lib.h"
#include "random_data.h"
#include "my_io.h"



int main()
{
	struct an_author** authors_list = malloc(26 * sizeof(struct an_author*));

	for (int init = 0; init < 26; init++) // spargerea listei de autori in subliste
	{
		authors_list[init] = malloc(sizeof(struct an_author));
		authors_list[init]->next_auhtor = NULL;
	}

	struct a_book* books_list;

	books_list = malloc(sizeof(struct a_book));
	books_list->next_book = NULL;




	printf("!A se folosi numai minuscule pentru nume!\n");
	char case_sel = 'x';
	while (case_sel != '5') // meniul programului
	{
		printf("1. Generare lista aleatoare si testare date.\n");
		printf("2. Adaugati o carte.\n");
		printf("3. Determinarea listei cartilor care au coautor un autor dat.\n");
		printf("4. Determinarea listei autorilor care sunt coautori pentru o anumita carte.\n");
		printf("5. Iesire.\n");

		scanf("%c%*c", &case_sel);

		switch (case_sel)
		{
		case '1':
		    test_f(books_list,authors_list);
			break;
		case '2':
			read_fk(books_list, authors_list, stdin);
		break;
		case '3':
		{
		    //secventa pentru cautarea listei de carti care au co-autor un autor dat
			char author_name[MAX_NAME];
			struct an_author* author;
			unsigned int no_books;
			struct a_book** list;
			printf("    Numele autorului este: \n    ");
			scanf("%[^\n]%*c", author_name);
			//se cauta autorul, deoarece lista de carti este inclusa in structura autorului
			author = check_author_entry(authors_list['z' - author_name[0]], author_name);
			if (author)
			{
				no_books = author->no_books_coauthored;
				list = author->books_coauthored_list;
				print_books_array(list, no_books);
			}
			else
			{
				printf("    Lista nu a fost gasita!\n");
			}
		}
		break;
		case '4':
		{
		    //secventa pentru cautarea liste de co autori pentru o anumita carte
			char book_name[MAX_NAME];
			struct a_book* book;
			unsigned int no_authors;
			struct an_author** list;
			printf("    Numele cartii este: \n    ");
			scanf("%[^\n]%*c", book_name);
			//se cauta cartea, deoarece lista de coautori este inclusa in strucura cartii
			book = check_book_entry(books_list, book_name);
			if (book)
			{
				no_authors = book->no_coauthors;
				list = book->coauthors_list;
				print_authors_array(list, no_authors);
			}
			else
			{
				printf("    Lista nu a fost gasita!\n");
			}
		}
		break;
		case '5':
			printf("    Iesire...\n");
			break;
		default:
			printf("    Selectati 1, 2, 3, 4 sau 5!!\n");
			break;
		}
	}



	return 0;
}

//i hate my life
