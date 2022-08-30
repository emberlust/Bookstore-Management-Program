#ifndef _MY_IO_H
#define _MY_IO_H

void read_fk(struct a_book* books_list, struct an_author** authors_list, FILE* stream);
void print_books_array(struct a_book** books_list, unsigned int no_books);
void print_authors_array(struct an_author** authors_list, unsigned int no_authors);

#endif // !_MY_IO_H

