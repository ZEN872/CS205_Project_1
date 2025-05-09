//CS_205_HW
#include <iostream>
#include <vector>
#include <queue>
#include <map>

#define spaure_size 3 // defines the size of grid. // can be chnaged if you want to increase or lower the size of the grid. 
#define NODE_CAP 75000 // limits the amount of nodes that can be made. 
using namespace std; 

static int MAX_QUEUE =0, NODES_EXPAND =0, DEPTH_SOLUTION =0; // Basic inputs to keep track of Max Queue, Total nodes Expanded, and the depth of the solution 
bool SEARCH_SUCC = false; // A trigger to check if a solution is found. 

////////////////////////////////////////////
map<vector<vector<int>>,int > all_puzzle; // this hash map keeps track of created states 
bool map_check(vector<vector<int>>); // Checks if the grid is already in the has map
void print_grid(vector<vector<int>> ); // function to print grids 
int Unform_search(vector<vector<int>> ); // the main search function that will be used. 
///////////////////////////////////////////

class Puzzle {
    public:
    Puzzle(){} // default constructor 

    Puzzle(vector<vector<int>> Grid, int depth){ // 
        this->Grid = Grid; // get the defined grid 
        this->depth = depth; // get the current depth of this puzzle 
        dim = Grid.size(); 
        Num_correct_in_grid(); // runs a function to define the number of correct tiles and the Zero position on this grid 
        all_puzzle.insert({Grid,1}); // adds the puzzle to the map table. 
    }

    vector<vector<int>> cur_grid()const {return Grid;}

    void Num_correct_in_grid(){
        Num_correct = 0; // defines the amount of correct tiles. 
        int current = 1; 
        for( int i = 0; i < dim;i++){
            for(int j =0; j < dim; j++){
                if(current >= dim * dim && Grid[i][j] == 0  ) // checks if last vale is ZERO
                    {Num_correct++; }
                else if(Grid[i][j] == current) // Check if a tile is in the correct position. 
                    {Num_correct++; }
                current++; 

                if(Grid[i][j] == 0) {
                    Zero_position = {i,j}; // saves the ZERO position to be used later 
                }
            }
        } 
    }

    int dim_()const{return dim;} // returns the length of the grid 
    int depth_()const{return depth;} // returns the current depth of this puzzle 
    int num_correct_() const { return Num_correct; } // returns number of correct tiles. 

    bool goalstate_met() const{ // checks if the grid ahs met the goal state
        if(Num_correct == dim*dim){return true; } // if the Number of correct tiles equla the size of the grid then the puzzle is solved  
        else{return false;} 
    }
    vector<int> Zero_Coord(){return Zero_position; } // returns the vector containing the zero position. 

    private:
    vector<int> Zero_position; // holds the Zero position {y,x}
    int dim; // Size of grid 
    int Num_correct;  // amount of correct elements 
    vector<vector<int>> Grid; // A 2d vector that makes a grid that houses the Current puzzle state. 
    int depth;  // the depth at which this puzzle is at
};

struct Heuristic { // function to determine the values in the priority queue
    bool operator()(const Puzzle& a, const Puzzle& b) const {
        // The Puzzle with the less misplace tiles has higher priority
        return a.num_correct_() < b.num_correct_();
    }
};


///////////////////////////////////////////
int  main(int argc, char *argv[]){
    vector<vector<int>> grid; 
    int num; 
    int i =1; 

    if(argc < spaure_size*spaure_size + 1){
        printf("Invaild input\n");
        return -1; 
    }
    else {

        for(int j =0; j < spaure_size; j++){
            grid.push_back({});
            for(int t =0; t < spaure_size; t++){
                grid[j].push_back(atoi(argv[i])); //COls
                i++;
            }
        }
    
        print_grid(grid);
        Unform_search(grid); 
        printf("Number of Nodes expand: %d \n", NODES_EXPAND);
        printf("Max Queue: %d \n", MAX_QUEUE);
        printf("Solution found at Depth: %d\n",DEPTH_SOLUTION);

    }
    
    return 0; 
}
///////////////////////////////////////////////////////
 
priority_queue<Puzzle, vector<Puzzle>, Heuristic>  add_node(  priority_queue<Puzzle, vector<Puzzle>, Heuristic> inserted_node, Puzzle puzzle_, int x, int y,int x1, int y1){
        if(!inserted_node.size() == 0 ){ // check if the queue is empty 
            Puzzle NewNode; 
            vector<vector<int>> placeholder = puzzle_.cur_grid(); // Holding the grid to modify 
        
            if(map_check(placeholder)){return inserted_node; } // a case in which the node is a new has not be added to the has map 

            bool x_check = (x1 < puzzle_.dim_() && x1 > -1); 
            bool y_check = (y1 < puzzle_.dim_() && y1 > -1); 

            if(x_check && y_check){ // checks if the move is able to done 
                swap(placeholder[x][y], placeholder[x1][y1]); 
                if(map_check(placeholder)){

                    NewNode = Puzzle(placeholder,puzzle_.depth_()+1); // Creates a new puzzle 
                    inserted_node.push(NewNode);// Adds the puzzle to the Queue 
                    NODES_EXPAND++; // Increase Number of Nodes Expanded 

                    if(MAX_QUEUE < inserted_node.size()){ // check id there is new Max Queue size 
                        MAX_QUEUE = inserted_node.size();
                    }

                        if (NewNode.goalstate_met()){ // Checks if the Goal State was met 
                        SEARCH_SUCC = true; // Soltuion was found 
                        DEPTH_SOLUTION = NewNode.depth_(); // Define Depth of Solution 
                        return {}; } // returns an empty queue to end the search 
                }
            }
        }
            return inserted_node; 
    } 

    priority_queue<Puzzle, vector<Puzzle>, Heuristic>  expand_nodes(priority_queue<Puzzle, vector<Puzzle>, Heuristic>  inserted_node){
        if(inserted_node.size() == 0 ){return inserted_node;} // If size is zero, no nodes can be expanded 
        
        Puzzle puzzle_ =  inserted_node.top();
        int oldsize = inserted_node.size();  
        
        /* gets the zero position of the grid
         this will be used to find all possible move 
         that can be made in this state  */
        
         int x = puzzle_.Zero_Coord()[0];
        int y = puzzle_.Zero_Coord()[1];
        
        /*For this sliding puzzle there are 4 to 2 possible moves 
        In this section we check which moves are possible and if 
        the create a new state they are added to the queue*/

            inserted_node = add_node(inserted_node, puzzle_,x,y, x+1,y); 
            inserted_node = add_node(inserted_node, puzzle_,x,y, x-1,y); 
            inserted_node = add_node(inserted_node, puzzle_,x,y, x,y-1);
            inserted_node = add_node(inserted_node, puzzle_,x,y, x,y+1);

        if(oldsize == inserted_node.size()){ // check if new nodes were added 
            inserted_node.pop(); // If no new nodes were add we dequeue this node. 
        } 
        return inserted_node; 
    }




int Unform_search(vector<vector<int>> Siding_puzzle){
    Puzzle inital_puzzle = Puzzle(Siding_puzzle,0); // defines out inital puzzle 
        
    priority_queue<Puzzle, vector<Puzzle>, Heuristic> Search_queue; // defines our inital queue 
        
    Search_queue.push(inital_puzzle);// adds to the queue 
        if(Search_queue.top().goalstate_met()){ // check if we start in the goal state
            return 1;  
        }

        while(Search_queue.size() > 0 ){
            Search_queue = expand_nodes(Search_queue); // expandes nodes 
           
            if(Search_queue.size() > 0 ){
                if (NODES_EXPAND > NODE_CAP ){ // check if node cap was hit // NODE CAP == 75000
                    printf ("Nodes Expand exceeded %d\n Search FAILED\n",NODE_CAP ); 
                    return -1; // Search Failed
                } 
            }
        }
        if(SEARCH_SUCC){ // checks if a goal state was met 
            printf ("goal state met \n");  
            return 0; 
        }else 
            {printf("Failed in finding a solution \n");} 
             
    return -1; // Search failed 
}


/////////////////////////////////////////////////////////////////////
void print_grid(vector<vector<int>>  dis_grid){ // Prints the 2D Vector 
    for( int i = 0; i < spaure_size;i++){
        cout << "[ "; 
        for(int j =0; j < spaure_size; j++){
            cout << dis_grid[i][j]<< " "; 
        }
        cout << "]\n";
    }
}

bool map_check(vector<vector<int>> Grid){ // Checks if the new 2D vector is in the hash map. 
    if(all_puzzle.find(Grid) == all_puzzle.end()){
        all_puzzle.insert({Grid,1});// If not in the map it is then added. 
        return true; 
    }
    else 
    return false;

}
/////////////////////////////////////////////////////////////////////