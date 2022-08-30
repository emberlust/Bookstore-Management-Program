#ifndef _MY_LIB_H
#define _MY_LIN_H

#define MAX_NAME 51 //dimensiunea maxima a unui camp pentru nume

struct an_author
{
	char name[MAX_NAME];                   //nume autor
	unsigned int no_books_authored;        //numarul de carti autorate
	struct a_book** books_authored_list;   //lista cartilor autorate, array de pointer
	unsigned int no_books_coauthored;      // numarul de carti coautorate
	struct a_book** books_coauthored_list; // lista cartilor coautorate, array de pointer
	struct an_author* next_auhtor;         // pointer catre urmatorul autor
};

struct a_book
{
	char name[MAX_NAME];                  //titlu carte
	struct an_author* author;             //pointer catre autor
	unsigned int no_coauthors;            //numar coautori
	struct an_author** coauthors_list;    //lista de coautori, array de pointeri
	struct a_book* next_book;
};

void input_book(struct a_book* books_list, char* book_name, int no_coaut);
void link_coauthor(struct a_book* book, struct an_author** authors_list, char* author_name, int nr_crt);
void link_author(struct a_book* book, struct an_author** authors_list, char* author_name);
struct an_author* check_author_entry(struct an_author* authors_list, char* author_name);
void create_author_entry(struct an_author* authors_list, char* author_name);
struct a_book* check_book_entry(struct a_book* books_list, char* book_name);


#endif // !_MY_LIB_H

