#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_lib.h"

void create_author_entry(struct an_author* authors_list, char* author_name) //adaugarea unui autor in baza de date. nu se introduc aici informatiile despre carti
{
	struct an_author* new_author;

	new_author = malloc(sizeof(struct an_author));

	strcpy(new_author->name, author_name);
	new_author->no_books_authored = 0;
	new_author->no_books_coauthored = 0;
	new_author->books_authored_list = malloc(new_author->no_books_authored * sizeof(struct a_book*));
	new_author->books_coauthored_list = malloc(new_author->no_books_coauthored * sizeof(struct a_book*));

	new_author->next_auhtor = authors_list->next_auhtor;
	authors_list->next_auhtor = new_author;
}

struct an_author* check_author_entry(struct an_author* authors_list, char* author_name) //cautarea unui autor in lista de autori
{
	for (struct an_author* author_iterator = authors_list; author_iterator->next_auhtor != NULL; author_iterator = author_iterator->next_auhtor)
	{
		if (!strcmp(author_iterator->next_auhtor->name, author_name))
		{
			return author_iterator->next_auhtor; //daca se gaseste, se returneaza pointer catre el. iteratorul este cu o intrare in urma, se returneaza deci urmatorul autor
		}
	}

	return NULL;//in caz ca nu a fost gasit se returneaza NULL

}

void link_author(struct a_book* book, struct an_author** authors_list, char* author_name)//aici se link-eaza un autor cu o carte, autorul este autor
{

	struct an_author* check_author;
	check_author = check_author_entry(authors_list['z' - author_name[0]], author_name);//mai intai se cauta in lista

	//link area efectiva
	if (check_author)
	{
		check_author->no_books_authored++;
		check_author->books_authored_list = realloc(check_author->books_authored_list, check_author->no_books_authored * sizeof(struct a_book*));
		check_author->books_authored_list[check_author->no_books_authored - 1] = book;
		book->author = check_author;
	}
	else
	{
		create_author_entry(authors_list['z' - author_name[0]], author_name);//daca nu se gaseste, se creeaza o intrare
		authors_list['z' - author_name[0]]->next_auhtor->no_books_authored++;
		authors_list['z' - author_name[0]]->next_auhtor->books_authored_list = realloc(authors_list['z' - author_name[0]]->next_auhtor->books_authored_list, authors_list['z' - author_name[0]]->next_auhtor->no_books_authored * sizeof(struct a_book*));
		authors_list['z' - author_name[0]]->next_auhtor->books_authored_list[authors_list['z' - author_name[0]]->next_auhtor->no_books_authored - 1] = book;
		book->author = authors_list['z' - author_name[0]]->next_auhtor;
	}
}

void link_coauthor(struct a_book* book, struct an_author** authors_list, char* author_name, int nr_crt)//aici se link-eaza un autor si o carte, autorul este coautor
{
	struct an_author* check_author;
	check_author = check_author_entry(authors_list['z' - author_name[0]], author_name);//mai inatai se cauta iin lista

	//link area efectiva
	if (check_author)
	{
		check_author->no_books_coauthored++;
		check_author->books_coauthored_list = realloc(check_author->books_coauthored_list, check_author->no_books_coauthored * sizeof(struct a_book*));
		check_author->books_coauthored_list[check_author->no_books_coauthored - 1] = book;
		book->coauthors_list[nr_crt] = check_author;
	}
	else
	{
		create_author_entry(authors_list['z' - author_name[0]], author_name);//daca nu se gaseste, se creeaza o intrare
		authors_list['z' - author_name[0]]->next_auhtor->no_books_coauthored++;
		authors_list['z' - author_name[0]]->next_auhtor->books_coauthored_list = realloc(authors_list['z' - author_name[0]]->next_auhtor->books_coauthored_list, authors_list['z' - author_name[0]]->next_auhtor->no_books_coauthored * sizeof(struct a_book*));
		authors_list['z' - author_name[0]]->next_auhtor->books_coauthored_list[authors_list['z' - author_name[0]]->next_auhtor->no_books_coauthored - 1] = book;
		book->coauthors_list[nr_crt] = authors_list['z' - author_name[0]]->next_auhtor;
	}

}

void input_book(struct a_book* books_list, char* book_name, int no_coaut) //se adauga o carte, dar doar numele si nr. de coautori
{
	struct a_book* new_book;

	new_book = malloc(sizeof(struct a_book));
	strcpy(new_book->name, book_name);
	new_book->author = malloc(sizeof(struct an_author*));
	new_book->no_coauthors = no_coaut;
	new_book->coauthors_list = malloc(no_coaut * sizeof(struct an_author*));

	new_book->next_book = books_list->next_book;
	books_list->next_book = new_book;

}

struct a_book* check_book_entry(struct a_book* books_list, char* book_name) //cautarea unei carti in biblioteca
{
	for (struct a_book* book_iterator = books_list; book_iterator->next_book != NULL; book_iterator = book_iterator->next_book)
	{
		if (!strcmp(book_iterator->next_book->name, book_name))
		{
			return book_iterator->next_book;
		}
	}

	return NULL;
}
