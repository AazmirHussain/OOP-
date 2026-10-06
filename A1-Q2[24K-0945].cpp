#include<iostream>
using namespace std;

class Robot{
    string name;
    int hits, robotx, roboty, ballx, bally;

    public:
        Robot(string name) : name(name), hits(0), robotx(0), roboty(0), ballx(0), bally(0) {};

        void setPosition(int x, int y){
            robotx = x;
            roboty = y;
        }
    
        int getX(){ 
	        return robotx; 
	    }
        int getY(){ 
	        return roboty; 
	    }
        int getHits() const{ 
	        return hits; 
	    }

        void hitBall(int &ballX, int &ballY, const string &direction){
            if (direction == "up"){
		        ballY++;
	        }
            else if (direction == "down"){
            	ballY--;
	    	}
            else if (direction == "left"){
	    	    ballX--;
		    }
            else if (direction == "right"){
            	ballX++;
		    }
            hits++;
        }

        void move(int dx, int dy){
            robotx += dx;
            roboty += dy;
        }
       
        ~Robot(){
            cout << name << " deleted" << endl;
        }
};

class Team{
    string teamName;
    Robot *robot;

    public:
        Team(string name, string robotName) : teamName(name){
            robot = new Robot(robotName);
        }

        Robot* getRobot(){ 
		    return robot; 
		}

        ~Team(){
            delete robot;
            cout << teamName << " deleted" << endl;
        }
};

class Game{
    Team *teamOne;
    Team *teamTwo;
    int ballX, ballY;
    const int goalX = 3, goalY = 3;

    public:
        Game() : ballX(0), ballY(0){
            teamOne = new Team("Team A", "Robot A");
            teamTwo = new Team("Team B", "Robot B");
        }
    
    ~Game(){
        delete teamOne;
        delete teamTwo;
        cout << "Game deleted" << endl;
    }
    
    bool isGoalReached(int x, int y){ // Validation
        return x == goalX && y == goalY;
    }
    
    void play(Team *team){
        Robot *robot = team->getRobot();
        
        while (!isGoalReached(ballX, ballY)){
            cout << "Move (up, down, left, right): ";
            string direction; // User input
            cin >> direction;
            
            robot->hitBall(ballX, ballY, direction);
            cout << "Ball at (" << ballX << ", " << ballY << ")" << endl; // Co-ordinates output
        }
    }
    
    void start() {
        cout << "Starting game..." << endl;
        play(teamOne);
        int hitsOne = teamOne->getRobot()->getHits();
        ballX = 0;
        ballY = 0;
        
        play(teamTwo);
        int hitsTwo = teamTwo->getRobot()->getHits();
        
        Winner(hitsOne, hitsTwo);
    }

    void Winner(int hitsOne, int hitsTwo){
        cout << endl << "Game over!" << endl;
        if (hitsOne < hitsTwo){
		    cout << "Team A wins with " << hitsOne << " hits!" << endl;
		    cout << "As compared to " << hitsTwo << " hits of Team B" << endl;
		}
        else if (hitsTwo < hitsOne) {
		    cout << "Team B wins with " << hitsTwo << " hits!" << endl;
		    cout << "As compared to " << hitsOne << " hits of Team A" << endl;
		}
        else {
		    cout << "It's a tie! Both teams took " << hitsOne << " hits." << endl;
		}
		cout << endl;
    }
};

int main() {
    Game game;
    game.start(); 
    
    return 0;
}