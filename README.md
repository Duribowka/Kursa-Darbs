HOW TO USE!!!

1. --item and --author flags change whether program works with items in "database.txt" or authors in "authors.txt". It is set to --item by default.

2. Here will be a list of all flags that assign value to struct's variables which than can be printed in databases:
    For items: -name -type -date -weight -price -width -height -author -stock
    For authors: -name -street -mail -site -phone -country -date
    Value should be entered after flag like this: -name <some> or -name <"some text"> if it includes spaces.
    *Value to date should be assigned like this: -date <day> <month> <year>

3. To append data to database flag "--add" should be entered, for example:
    ./main.o -name programming -type education --add | this will append data to the file

4. In order to see data, flag "--show" exists. By using it a block of data will be printed to terminal. Example of usage: ./main.o --show <name>

5. It is possible to edit data via "--edit" flag. Name and category have to be provided, example: ./main.o --edit <name> <category> <new text>
         ./main.o --edit programming Genre drama | from - Genre: education
                                                   to  -  Genre: drama

6. Block of data can be completely removed with "--rm" flag like this: ./main.o --rm <name>

7. The data inside file can be sorted and printed with "--sort" command. Sorting options: alphabet, stock, price, date

8. To filter a file and print it use command "--filter". Example: ./main.o --filter Education

9. To filter AND sort output of the whole file use "--filter+sort" command. Example: ./main.o --filter+sort Education price

10. And lastly program can be compiled with "make main" command and "make clean" removes all object files.

I hope this program is great to work with :)