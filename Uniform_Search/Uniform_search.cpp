//CS_205_HW
#include <iostream>
#include <vector>
#include <queue>
#include <map>

#define spaure_size 3
#define NODE_CAP 75000
using namespace std; 

static int MAX_QUEUE =0, NODES_EXPAND =0, DEPTH_SOLUTION =0; 
bool SEARCH_SUCC = false; 

////////////////////////////////////////////
map<vector<vector<int>>,int > all_puzzle; 
bool map_check(vector<vector<int>>);
void print_grid(vector<vector<int>> );
int Unform_search(vector<vector<int>> );
///////////////////////////////////////////

class Puzzle {
    public:
    Puzzle(){}

    Puzzle(vector<vector<int>> Grid, int depth){
        this->Grid = Grid;
        this->depth = depth;
        dim = Grid.size(); 
        Num_correct_in_grid(); 
        all_puzzle.insert({Grid,1});
    }

    vector<vector<int>> cur_grid(){return Grid;}

    void Num_correct_in_grid(){
        Num_correct = 0; 
        int current = 1; 
        for( int i = 0; i < dim;i++){
            for(int j =0; j < dim; j++){
                if(current >= dim * dim )
                    {Num_correct++; }
                else if(Grid[i][j] == current)
                    {Num_correct++; }
                    current++; 

                if(Grid[i][j] == 0) {
                    Zero_position = {i,j};
                }
            }
        } 
    }

    int dim_(){return dim;}
    int depth_(){return depth;}

    bool goalstate_met(){
        if(Num_correct == dim*dim){return true; }
        else{return false;} 
    }
    vector<int> Zero_Coord(){return Zero_position; }

    private:
    vector<int> Zero_position; 
    int dim; 
    int Num_correct; 
    vector<vector<int>> Grid;
    int depth;  
};

queue<Puzzle> expand_nodes(queue<Puzzle>);

///////////////////////////////////////////
int  main(int argc, char *argv[]){
    vector<vector<int>> grid; 
    int num; 
    int i =1; 

    if(argc < 10){
        printf("Invaild input\n");
        /*Need to add user alt input*/
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
    queue<Puzzle> add_node(queue<Puzzle> inserted_node, int x, int y,int x1, int y1){
        if(!inserted_node.size() == 0){
            Puzzle NewNode; 
            vector<vector<int>> placeholder = inserted_node.front().cur_grid(); 
        
            if(map_check(placeholder)){return inserted_node; }

            bool x_check = (x1 < inserted_node.front().dim_() && x1 > -1); 
            bool y_check = (y1 < inserted_node.front().dim_() && y1 > -1); 

            if(x_check && y_check){
                swap(placeholder[x][y], placeholder[x1][y1]); 
                if(map_check(placeholder)){

                    NewNode = Puzzle(placeholder,inserted_node.front().depth_()+1);
                    inserted_node.push(NewNode);
                    NODES_EXPAND++; 
                    if(MAX_QUEUE < inserted_node.size()){
                        MAX_QUEUE = inserted_node.size();
                    }

                    if (NewNode.goalstate_met()){
                        SEARCH_SUCC = true; 
                        DEPTH_SOLUTION = NewNode.depth_();
                        return {}; }
                    
                }
            }
        }
            return inserted_node; 
    } 

    queue<Puzzle> expand_nodes(queue<Puzzle> inserted_node){
        if(inserted_node.size() == 0 ){return inserted_node;}

        int x = inserted_node.front().Zero_Coord()[0];
        int y = inserted_node.front().Zero_Coord()[1];

            inserted_node = add_node(inserted_node, x,y, x+1,y); 
            inserted_node = add_node(inserted_node, x,y, x-1,y); 
            inserted_node = add_node(inserted_node, x,y, x,y-1);
            inserted_node = add_node(inserted_node, x,y, x,y+1);
        
        return inserted_node; 
    }


    int Unform_search(vector<vector<int>> Siding_puzzle){
        Puzzle inital_puzzle = Puzzle(Siding_puzzle,0); 
        
        queue<Puzzle> Search_queue;

        
        Search_queue.push(inital_puzzle);
        if(Search_queue.front().goalstate_met()){
            return 1;  
        }

         while(Search_queue.size() > 0 ){
            Search_queue = expand_nodes(Search_queue); 
           
            if(Search_queue.size() > 0 ){ 
                if (NODES_EXPAND > NODE_CAP ){
                    printf ("Nodes Expand exceeded %d\n Search FAILED\n",NODE_CAP ); 
                    return -1; 
                } 
                Search_queue.pop();
            }
        
            }

            if(SEARCH_SUCC){
            printf ("goal state met \n");  
             return 0; 
            }
             else 
             printf("Failed in finding a solution \n"); 
             return -1; 
    }


/////////////////////////////////////////////////////////////////////
void print_grid(vector<vector<int>>  dis_grid){
    for( int i = 0; i < spaure_size;i++){
        cout << "[ "; 
        for(int j =0; j < spaure_size; j++){
            cout << dis_grid[i][j]<< " "; 
        }
        cout << "]\n";
    }
}

bool map_check(vector<vector<int>> Grid){
    if(all_puzzle.find(Grid) == all_puzzle.end()){
        all_puzzle.insert({Grid,1});
        return true; 
    }
    else 
    return false;

}
/////////////////////////////////////////////////////////////////////