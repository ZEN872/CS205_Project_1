NAME = tile_misplace

make: 
	g++ -o $(NAME) $(NAME).cpp

clean: 
	rm $(NAME)

test1: 
	g++ -o $(NAME) $(NAME).cpp
	./$(NAME) 1 2 3 4 5 6 7 8 0
	./$(NAME) 1 2 3 4 5 6 7 0 8 


test2:
	g++ -o $(NAME) $(NAME).cpp
	./$(NAME) 1 2 3 0 4 5 6 7 8 

test_long: 
	./$(NAME) 8 4 7 3 0 1 2 6 5 



