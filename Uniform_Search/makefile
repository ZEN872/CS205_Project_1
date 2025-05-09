NAME = Uniform_Search

make: 
	g++ -o $(NAME) $(NAME).cpp

clean: 
	rm $(NAME)

test: 
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
	./$(NAME) 1 2 3 0 4 5 6 7 8 



