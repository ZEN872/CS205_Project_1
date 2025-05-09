NAME = Uniform_search

make: 
	g++ -o $(NAME) $(NAME).cpp

clean: 
	rm $(NAME)

test1: 
	g++ -o $(NAME) $(NAME).cpp
#depth 0
	./$(NAME) 1 2 3 4 5 6 7 8 0
#depth 1
	./$(NAME) 1 2 3 4 5 0 7 8 6
#depth 2
	./$(NAME) 1 2 3 4 0 5 7 8 6
#depth 3
	./$(NAME) 1 0 3 4 2 5 7 8 6
#depth 4
	./$(NAME) 0 1 3 4 2 5 7 8 6
#depth 5
	./$(NAME) 4 1 3 0 2 5 7 8 6

test2: 
	g++ -o $(NAME) $(NAME).cpp
#depth 6
	./$(NAME) 4 1 3 2 0 5 7 8 6
#depth 7
	./$(NAME) 4 0 3 2 1 5 7 8 6
#depth 8
	./$(NAME) 0 4 3 2 1 5 7 8 6

test3:
	g++ -o $(NAME) $(NAME).cpp
#depth 14
	./$(NAME) 1 2 3 4 0 5 6 7 8 
#depth 15
	./$(NAME) 1 2 3 0 4 5 6 7 8 
#deoth 16
	./$(NAME) 0 3 8 1 2 5 6 4 7

test4:
	g++ -o $(NAME) $(NAME).cpp
#depth 20
	./$(NAME) 4 1 2 7 8 6 0 5 3
#depth 32
	./$(NAME) 0 1 2 8 6 4 7 5 3 
