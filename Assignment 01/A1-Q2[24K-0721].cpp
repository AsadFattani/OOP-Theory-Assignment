#include <iostream>
using namespace std;

class Robot {
    private:
        string robotName;
        int totalHits;
    public:
        Robot(string name) : robotName(name), totalHits(0) {}
        void hitBall(int &ballX, int &ballY,  string &direction){
            if(direction == "up"){
                ballY++;
            }else if(direction == "down"){
                ballY--;
            }else if(direction == "left"){
                ballX--;
            }else if(direction == "right"){
                ballX++;
            }
            totalHits++;
        }
        int getTotalHits()  {
            return totalHits;
        }
};

class Ball {
    private:
        int ballX;
        int ballY;
    public:
        Ball(int x, int y) : ballX(x), ballY(y) {}
        int getBallX()  {
            return ballX;
        }
        int getBallY()  {
            return ballY;
        }
        void moveBall(int dx, int dy){
            ballX = dx;
            ballY = dy;
        }
        void getBallPosition()  {
            cout << "Ball Position: (" << ballX << ", " << ballY << ")" << endl;
        }
};

class Goal {
    private:
        int goalX;
        int goalY;
    public:
        Goal(int x, int y) : goalX(x), goalY(y) {}
        bool isGoalReached(int ballX, int ballY)  {
            return ballX == goalX && ballY == goalY;
        }
};

class Team {
    private:
        string teamName;
        Robot *robot;
    public:
        Team(string name, Robot *r) : teamName(name), robot(r) {}
        Robot* getRobot()  {
            return robot;
        }
        string getTeamName()  {
            return teamName;
        }
};

class Game {
    private:
        Team *teamOne;
        Team *teamTwo;
        Ball *ball;
        Goal *goal;
    public:
        Game(Team *t1, Team *t2, Ball *b, Goal *g) : teamOne(t1), teamTwo(t2), ball(b), goal(g) {}
        void startGame() {
            while (!goal->isGoalReached(ball->getBallX(), ball->getBallY())) {
                play(teamOne);
                if (goal->isGoalReached(ball->getBallX(), ball->getBallY())) break;
                play(teamTwo);
            }
            declareWinner();
        }
        void play(Team *team) {
            string direction;
            while (true) {
                cout << team->getTeamName() << ", enter direction (up, down, left, right): ";
                cin >> direction;
                if (direction == "up" || direction == "down" || direction == "left" || direction == "right") {
                    break;
                } else {
                    cout << "Invalid direction. Please enter a valid direction (up, down, left, right)." << endl;
                }
            }
            int ballX = ball->getBallX();
            int ballY = ball->getBallY();
            team->getRobot()->hitBall(ballX, ballY, direction);
            ball->moveBall(ballX, ballY);
            ball->getBallPosition();
        }
        void declareWinner() {
            int hitsTeamOne = teamOne->getRobot()->getTotalHits();
            int hitsTeamTwo = teamTwo->getRobot()->getTotalHits();
            if (hitsTeamOne < hitsTeamTwo) {
                cout << teamOne->getTeamName() << " wins with " << hitsTeamOne << " hits!" << endl;
            } else if (hitsTeamTwo < hitsTeamOne) {
                cout << teamTwo->getTeamName() << " wins with " << hitsTeamTwo << " hits!" << endl;
            } else {
                cout << "It's a tie!" << endl;
            }
        }
};

int main() {
    Robot robot1("Robot1");
    Robot robot2("Robot2");
    Ball ball(0, 0);
    Goal goal(2, 3); // 5 steps | must be odd 
    Team teamOne("Team One", &robot1);
    Team teamTwo("Team Two", &robot2);
    Game game(&teamOne, &teamTwo, &ball, &goal);
    game.startGame();
    return 0;
}


