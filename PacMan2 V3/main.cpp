#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>


using namespace std;

#define SIZEX 28
#define SIZEY 31

#define Bry_Cherry 0,0,13,13
#define Bry_Strawberry 16,0,13,13
#define Bry_Peach 32,0,13,13
#define Bry_Apple 48,0,13,13
#define Bry_Lime 65,0,13,13
#define Bry_Spear 80,0,11,13
#define Bry_Bell 96,0,12,13
#define Bry_Key 114,0,7,13

#define Pac_wack1 0,2,13,9
#define Pac_wack2 15,3,15,8
#define Pac_wack3 31,5,15,6
#define Pac_wack4 47,6,15,5
#define Pac_wack5 63,7,15,5
#define Pac_wack6 79,7,15,6
#define Pac_wack7 96,8,13,6
#define Pac_wack8 114,7,9,7
#define Pac_wack9 132,7,5,7
#define Pac_wack10 150,7,1,5
#define Pac_wack11 161,5,11,11


//https://www.codesdope.com/blog/article/backtracking-to-solve-a-rat-in-a-maze-c-java-pytho/
//https://www.youtube.com/watch?v=ataGotQ7ir8


//matrix to store the solution

bool DEBUG = true;


void printsolution(int solutionRow,int solutionCol,int StartRow,int StartCol,vector<vector<int>> &solution,vector<vector<int>> maze) {
//function to print the solution matrix
    cout<<endl;
    int i,j;
    for(i=0; i<SIZEY; i++) {
        for(j=0; j<SIZEX; j++) {

            if(solutionCol == i && solutionRow == j) {

                cout<<"@ ";

            } else if(StartCol == i && StartRow == j) {

                cout<<"$ ";
            } else if(maze[i][j]== 1) {

                cout<<"||";

            } else {
                cout<<" "<<solution[i][j];
            }

        }
        cout<<endl;
    }
}

//int solution[SIZEY][SIZEX];

int SmallestDistance(int Start, int Solution) {

    int Number;

    if(Start>Solution) {

        Number = Start - Solution;

    } else {

        Number = Solution - Start;
    }

    return Number;
}



int solvemaze(int r, int c, int solutionCol,int solutionRow, string CurrentDirection,vector<vector<int>> &solution,vector<int> &PathCol, vector<int> &PathRow,vector<vector<int>> maze) {

    //if destination is reached, maze is solved
    //destination is the last cell(maze[SIZE-1][SIZE-1])
    if((r==solutionRow) && (c==solutionCol)) {
        solution[r][c] = 1;
        PathCol.push_back(c);
        PathRow.push_back(r);
        return 1;
    }
    //checking if we can visit in this cell or not
    //the indices of the cell must be in (0,SIZE-1)
    //and solution[r][c] == 0 is making sure that the cell is not already visited
    //maze[r][c] == 0 is making sure that the cell is not blocked
    if(r>=0 && c>=0 && r<SIZEY && c<SIZEX && solution[r][c] == 0 && maze[r][c] != 1) {
        //  if(r>=0 && c>=0 && r<SIZEY && c<SIZEX) {

        //if safe to visit then visit the cell
        solution[r][c] = 1;

        PathCol.push_back(c);
        PathRow.push_back(r);

        //cout<<endl;
        // cout<<"---------------"<<endl;

        int BaseRow = SmallestDistance(r, solutionRow);
        int BaseCol = SmallestDistance(c, solutionCol);
        int BaseScore = (BaseRow*BaseRow)+(BaseCol*BaseCol);


        int RigthRow = SmallestDistance(r, solutionRow);
        int RigthCol = SmallestDistance(c+1, solutionCol);
        int RigthScore = (RigthRow*RigthRow)+(RigthCol*RigthCol);

        int LeftRow = SmallestDistance(r, solutionRow);
        int LeftCol = SmallestDistance(c-1, solutionCol);
        int LeftScore = (LeftRow*LeftRow)+(LeftCol*LeftCol);

        int UpRow = SmallestDistance(r-1, solutionRow);
        int UpCol = SmallestDistance(c, solutionCol);
        int UpScore = (UpRow*UpRow)+(UpCol*UpCol);

        int DownRow = SmallestDistance(r+1, solutionRow);
        int DownCol = SmallestDistance(c, solutionCol);
        int DownScore = (DownRow*DownRow)+(DownCol*DownCol);


        vector<int> AllScores = {UpScore,LeftScore,DownScore,RigthScore};

        vector<int> AllScoresTemp = AllScores;

        std::sort(AllScoresTemp.begin(), AllScoresTemp.end());

        int lowest = AllScoresTemp[0];
        int SecondLowest = AllScoresTemp[1];
        int ThridLowest = AllScoresTemp[2];
        int Highest = AllScoresTemp[3];

        bool CanGoDown = false;
        bool CanGoUp = false;
        bool CanGoLeft = false;
        bool CanGoRight = false;

        for(int i = 0; i<4; i++) {

            if(AllScores[i] == lowest) {
                lowest = i;
                break;
            }
        }

        for(int i = 0; i<4; i++) {

            if(AllScores[i] == SecondLowest ) {

                if(i!= lowest) {
                    SecondLowest = i;
                    break;
                }
            }
        }

        for(int i = 0; i<4; i++) {

            if(AllScores[i] == ThridLowest) {
                if(i !=SecondLowest) {
                    ThridLowest = i;
                    break;
                }
            }
        }

        for(int i = 0; i<4; i++) {

            if(AllScores[i] == Highest) {
                if( i !=ThridLowest) {
                    Highest = i;
                    break;
                }
            }
        }



        if(lowest == 0) {

            //cout<<"Right, ";
        } else  if(lowest == 1) {

            //cout<<"Left, ";
        } else  if(lowest == 2) {

            //cout<<"Up, ";
        } else  if(lowest == 3) {

            //cout<<"Down, ";
        }


        if(SecondLowest == 0) {

            //cout<<"Right, ";
        } else  if(SecondLowest == 1) {

            //cout<<"Left, ";
        } else  if(SecondLowest == 2) {

            //cout<<"Up, ";
        } else  if(SecondLowest == 3) {

            //cout<<"Down, ";
        }



        if(ThridLowest == 0) {

            //cout<<"Right, ";
        } else  if(ThridLowest == 1) {

            //cout<<"Left, ";
        } else  if(ThridLowest == 2) {

            //cout<<"Up, ";
        } else  if(ThridLowest == 3) {

            //cout<<"Down, ";
        }

        if(Highest == 0) {

            //cout<<"Right, "<<endl;
        } else  if(Highest == 1) {

            //cout<<"Left, "<<endl;
        } else  if(Highest == 2) {

            //cout<<"Up, "<<endl;
        } else  if(Highest == 3) {

            //cout<<"Down, "<<endl;
        }




//cout<<"Can Go: ";
        if(solution[r-1][c] == 0 && maze[r-1][c] != 1&& CurrentDirection !="Down") {
            CanGoUp = true;
//cout<<"Up ";
        }

        if(solution[r][c-1] == 0 && maze[r][c-1] != 1&& CurrentDirection !="Right") {
            CanGoLeft = true;
//cout<<"Left ";
        }

        if(solution[r+1][c] == 0 && maze[r+1][c] != 1 && CurrentDirection !="Up") {
            CanGoDown = true;
//cout<<"Down ";
        }

        if(solution[r][c+1] == 0 && maze[r][c+1] != 1 && CurrentDirection !="Left") {
            CanGoRight = true;
//cout<<"Right ";
        }

//cout<<endl;







//cout<<"Did Go: ";
//        if(CanGoUp == true && lowest == 2) {

        if(CanGoUp == true && lowest == 0) {
//cout<<"Up ";
            if(solvemaze((r-1), c, solutionCol, solutionRow,"Up",solution,PathCol,PathRow,maze))
                return 1;

        } else if(CanGoLeft == true && lowest == 1) {
//cout<<"Left ";
            if(solvemaze(r, (c-1), solutionCol, solutionRow,"Left",solution,PathCol,PathRow,maze))
                return 1;

//        } else if(CanGoDown == true && lowest == 3) {
        } else if(CanGoDown == true && lowest == 2) {

//cout<<"Down ";
            if(solvemaze((r+1), c, solutionCol, solutionRow,"Down",solution,PathCol,PathRow,maze))
                return 1;

            //  } else if(CanGoRight == true && lowest == 0) {
        } else if(CanGoRight == true && lowest == 3) {
//cout<<"Right ";
            if(solvemaze(r, (c+1), solutionCol, solutionRow,"Right",solution,PathCol,PathRow,maze))
                return 1;

        } else {



            //  if(CanGoUp == true && SecondLowest == 2) {
            if(CanGoUp == true && SecondLowest == 0) {
//cout<<"Up ";
                if(solvemaze((r-1), c, solutionCol, solutionRow,"Up",solution,PathCol,PathRow,maze))
                    return 1;

            } else if(CanGoLeft == true && SecondLowest == 1) {

//cout<<"Left "<<c-1;
                if(solvemaze(r, (c-1), solutionCol, solutionRow,"Left",solution,PathCol,PathRow,maze))
                    return 1;

                //} else if(CanGoDown == true && SecondLowest == 3) {

            } else if(CanGoDown == true && SecondLowest == 2) {
//cout<<"Down ";
                if(solvemaze((r+1), c, solutionCol, solutionRow,"Down",solution,PathCol,PathRow,maze))
                    return 1;

                // } else if(CanGoRight == true && SecondLowest == 0) {

            } else if(CanGoRight == true && SecondLowest == 3) {

//cout<<"Right "<<c+1;
                if(solvemaze(r, (c+1), solutionCol, solutionRow,"Right",solution,PathCol,PathRow,maze))
                    return 1;

            } else {




//                if(CanGoUp == true && ThridLowest == 2) {

                if(CanGoUp == true && ThridLowest == 0) {

//cout<<"Up ";
                    if(solvemaze((r-1), c, solutionCol, solutionRow,"Up",solution,PathCol,PathRow,maze))
                        return 1;

                } else if(CanGoLeft == true && ThridLowest == 1) {
//cout<<"Left "<<c-1;
                    if(solvemaze(r, (c-1), solutionCol, solutionRow,"Left",solution,PathCol,PathRow,maze))
                        return 1;

                    //  } else if(CanGoDown == true && ThridLowest == 3) {

                } else if(CanGoDown == true && ThridLowest == 2) {

//cout<<"Down ";
                    if(solvemaze((r+1), c, solutionCol, solutionRow,"Down",solution,PathCol,PathRow,maze))
                        return 1;

//               } else if(CanGoRight == true && ThridLowest == 0) {

                } else if(CanGoRight == true && ThridLowest == 3) {
//cout<<"Right "<<c+1;
                    if(solvemaze(r, (c+1), solutionCol, solutionRow,"Right",solution,PathCol,PathRow,maze))
                        return 1;
                } else {



                    //if(CanGoUp == true && Highest == 2) {
                    if(CanGoUp == true && Highest == 0) {
//cout<<"Up ";
                        if(solvemaze((r-1), c, solutionCol, solutionRow,"Up",solution,PathCol,PathRow,maze))
                            return 1;

                    } else if(CanGoLeft == true && Highest == 1) {
//cout<<"Left ";
                        if(solvemaze(r, (c-1), solutionCol, solutionRow,"Left",solution,PathCol,PathRow,maze))
                            return 1;

                        // } else if(CanGoDown == true && Highest == 3) {
                    } else if(CanGoDown == true && Highest == 2) {

//cout<<"Down ";
                        if(solvemaze((r+1), c, solutionCol, solutionRow,"Down",solution,PathCol,PathRow,maze))
                            return 1;

                        //  } else if(CanGoRight == true && Highest == 0) {

                    } else if(CanGoRight == true && Highest == 3) {
//cout<<"Right ";
                        if(solvemaze(r, (c+1), solutionCol, solutionRow,"Right",solution,PathCol,PathRow,maze))
                            return 1;

                    } else {



                        if(CanGoDown == false && CanGoUp == false && CanGoLeft == false && CanGoRight == true) {

                            //cout<<"Right ";
                            if(solvemaze(r, c+1, solutionCol, solutionRow,"Right",solution,PathCol,PathRow,maze))
                                return 1;
                        }

                        if(CanGoDown == false && CanGoUp == false && CanGoLeft == true && CanGoRight == false) {

                            //cout<<"Left ";
                            if(solvemaze(r, c-1, solutionCol, solutionRow,"Left",solution,PathCol,PathRow,maze))
                                return 1;
                        }

                        if(CanGoDown == false && CanGoUp == true && CanGoLeft == false && CanGoRight == false) {

                            //cout<<"Up ";
                            if(solvemaze(r-1, c, solutionCol, solutionRow,"Up",solution,PathCol,PathRow,maze))
                                return 1;
                        }

                        if(CanGoDown == true && CanGoUp == false && CanGoLeft == false && CanGoRight == false) {

                            //cout<<"Down ";
                            if(solvemaze(r+1, c, solutionCol, solutionRow,"Down",solution,PathCol,PathRow,maze))
                                return 1;
                        }
                    }
                }
            }
        }

        //cout<<"It fucked up!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;


        return 1;

        // This is a last resort if the algorithm seriously messes up this may help to solve the maze


        //going up
        if(solution[r-1][c] == 0 && maze[r-1][c] != 1&& CurrentDirection !="Down") {
            //cout<<"Up ";
            if(solvemaze(r-1, c, solutionCol, solutionRow,"Up",solution,PathCol,PathRow,maze))
                return 1;
        }
        //going left
        if(solution[r][c-1] == 0 && maze[r][c-1] != 1&& CurrentDirection !="Right") {
            //cout<<"Left ";
            if(solvemaze(r, c-1, solutionCol, solutionRow,"Left",solution,PathCol,PathRow,maze))
                return 1;
        }

        //going down
        if(solution[r+1][c] == 0 && maze[r+1][c] != 1 && CurrentDirection !="Up") {
            //cout<<"Down ";
            if(solvemaze(r+1, c, solutionCol, solutionRow,"Down",solution,PathCol,PathRow,maze))
                return 1;
        }

        //going right
        if(solution[r][c+1] == 0 && maze[r][c+1] != 1 && CurrentDirection !="Left") {
            //cout<<"Right ";
            if(solvemaze(r, c+1, solutionCol, solutionRow,"Right",solution,PathCol,PathRow,maze))
                return 1;
        }




        //backtracking
        //  solution[r][c] = 0;
        return 0;
    }
    return 0;

}




int ScaredSolver(int r, int c, string CurrentDirection,vector<vector<int>> &solution,vector<int> &PathCol, vector<int> &PathRow,vector<vector<int>> maze) {

    solution[r][c] = 1;
    PathCol.push_back(c);
    PathRow.push_back(r);


    bool CanGoDown = false;
    bool CanGoUp = false;
    bool CanGoLeft = false;
    bool CanGoRight = false;

    int BoolTrue = 0;
    int RandNumber = 0;


    if(solution[r-1][c] == 0 && maze[r-1][c] != 1&& CurrentDirection !="Down") {
        CanGoUp = true;
    }

    if(solution[r][c-1] == 0 && maze[r][c-1] != 1&& CurrentDirection !="Right") {
        CanGoLeft = true;
    }

    if(solution[r+1][c] == 0 && maze[r+1][c] != 1 && CurrentDirection !="Up") {
        CanGoDown = true;
    }

    if(solution[r][c+1] == 0 && maze[r][c+1] != 1 && CurrentDirection !="Left") {
        CanGoRight = true;
    }


    vector <bool> AllCans = {CanGoUp,CanGoLeft,CanGoDown,CanGoRight};
    vector <int> AvaliableNum;


    for(int i = 0; i<4; i++) {
        if(AllCans[i]== true) {

            BoolTrue++;
            AvaliableNum.push_back(i);
        }
    }


    if(BoolTrue>0) {
        RandNumber = rand()%BoolTrue;

        if(AvaliableNum[RandNumber] == 0) {

            solution[r-1][c] = 1;
            PathCol.push_back(c);
            PathRow.push_back(r-1);

        } else if(AvaliableNum[RandNumber] == 1) {

            solution[r][c-1] = 1;
            PathCol.push_back(c-1);
            PathRow.push_back(r);

        } else if(AvaliableNum[RandNumber] == 2) {

            solution[r+1][c] = 1;
            PathCol.push_back(c);
            PathRow.push_back(r+1);

        } else if(AvaliableNum[RandNumber] == 3) {

            solution[r][c+1] = 1;
            PathCol.push_back(c+1);
            PathRow.push_back(r);
        }
    }


    return 1;

}




sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );

    return view;
}


bool isSpriteHover(sf::FloatRect Button, sf::Vector2f mp) {

    if (Button.contains(mp)) {
        return true;
    }

    return false;
}


vector<int> ClossestTile(float PositionX, float PositionY, std::vector<sf::RectangleShape> Tiles) {

    int place = 0;
    int FinalPlace = 0;
    int row = 0;
    int col = 0;

    for(int i = 0; i<28*31; i++) {

        if ((Tiles[i].getGlobalBounds()).contains(sf::Vector2f(PositionX, PositionY))) {

            FinalPlace = i;
            break;
        }
    }
    col = FinalPlace/28;
    row = FinalPlace%28;

    vector<int> RowColArray = {row,col};

    return RowColArray;
}


vector<string> WallTest(vector<vector<int>> GameMatrix, int Row, int Col, string currentDur, bool &Stop) {


    std::vector<string> AvallibleDir;

    //1 is a wall

    // so it doesn't fuck it'self up
    if(Col >0) {
        //Above
        if(GameMatrix[Col-1][Row] == 1) {

            if(currentDur == "Up") {
                Stop = true;
            }
        } else {
            AvallibleDir.push_back("Up");
        }
    }

    //below
    if(GameMatrix[Col+1][Row] == 1) {

        if(currentDur == "Down") {
            Stop = true;
        }
    } else {
        AvallibleDir.push_back("Down");
    }


    //Left
    if(GameMatrix[Col][Row-1] == 1) {

        if(currentDur == "Left") {
            Stop = true;
        }
    } else {
        AvallibleDir.push_back("Left");
    }


    //Right
    if(GameMatrix[Col][Row+1] == 1) {

        if(currentDur == "Right") {
            Stop = true;
        }
    } else {
        AvallibleDir.push_back("Right");
    }


    //cout<<"Available dir: "<<AvallibleDir.size()<<endl;

    return AvallibleDir;

}


bool CenterOfTile(int Row, int Col, string currentDur, sf::Sprite GameSprite, bool Stop) {

    bool inCenter = false;

    bool HorizCenter = false;
    bool VertCenter = false;

    float SpriteX = GameSprite.getPosition().x;
    float SpriteY = GameSprite.getPosition().y;

    float TileX = 18.78571429*Row;
    float TileY = 18.61290323*Col;
    float TileXCenter = (18.78571429*Row)+(18.78571429/2);
    float TileYCenter =(18.61290323*Col)+(18.61290323/2);


    if((SpriteX > (TileXCenter-5)) && (SpriteX < (TileXCenter+5))) {

        HorizCenter = true;

        // cout<<"a"<<endl;
    }

//Note to self change -10 // +10 to something smaller than 8

    if((SpriteY > (TileYCenter-5)) && (SpriteY < (TileYCenter+5))) {

        VertCenter = true;
        //    cout<<"b"<<endl;
    }


    if((currentDur == "Left" || currentDur == "Right") && VertCenter == true) {
        inCenter = true;
    }



    if((currentDur == "Up" || currentDur == "Down") && HorizCenter == true) {
        inCenter = true;
    }


    if(VertCenter && HorizCenter == true) {
        inCenter = true;
    }


    return inCenter;
}


bool isNode(std::vector<string> AvallibleDir) {

    bool isANode = false;

    if(AvallibleDir.size() > 2) {

        isANode = true;
    } else {


        if(AvallibleDir[0]== "Up") {

            if(AvallibleDir[1]== "Left") {

                isANode = true;

            } else if(AvallibleDir[1]== "Right") {

                isANode = true;
            }

        } else if(AvallibleDir[0]== "Down") {

            if(AvallibleDir[1]== "Left") {

                isANode = true;

            } else if(AvallibleDir[1]== "Right") {

                isANode = true;
            }
        }
    }


    return isANode;
}



bool OutOfTheCloset(int GhostRow, int GhostCol, string &CurrentDir, vector<int> &PathCol, vector<int> &PathRow, int HouseRow, int HouseCol, bool GhostDead) {

    //Makes it go down
    if(GhostCol == HouseCol && GhostRow == HouseRow && GhostDead == true) {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol+1;
        CurrentDir = "A";

    }


    if(GhostCol == HouseCol+1 && GhostRow == HouseRow && GhostDead == true) {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol+2;
        CurrentDir = "A";

    }


    if(GhostCol == HouseCol+2 && GhostRow == HouseRow && GhostDead == true) {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol+3;
        CurrentDir = "A";

    }

    //Makes it go Up
    if(GhostCol == HouseCol+3 && GhostRow == HouseRow) {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol+2;
        CurrentDir = "A";


        return true;
    }


    if(GhostCol == HouseCol+2 && GhostRow == HouseRow && GhostDead == false) {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol+1;
        CurrentDir = "A";

    }

    if(GhostCol == HouseCol+1 && GhostRow == HouseRow && GhostDead == false) {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol;
        CurrentDir = "A";

    }


    return false;
}


void scoreUpdate(sf::Text &HsDis, sf::Text &scoreDis, int score, int highscore, string &scoreShow, string &HSString) {
    stringstream ss;
    ss<<score;
    ss>>scoreShow;

    scoreDis.setString("Score: "+scoreShow);

    stringstream ss2;
    ss2<<highscore;
    ss2>>HSString;

    HsDis.setString("HS: "+HSString);
}


void SaveHS(int &highscore, int &score,string &HSString,sf::Text &NewHS) {

    ifstream readFile;
    readFile.open("Assets/Other/High_Score.txt");

    if(readFile.is_open()) {

        while(!readFile.eof()) {

            readFile >> highscore;
        }

    }
    readFile.close();

    ofstream writeFile("Assets/Other/High_Score.txt");
    if(writeFile.is_open()) {

        stringstream ss3;
        ss3<<highscore;
        ss3>>HSString;

        if(score>highscore) {

            highscore = score;

            NewHS.setPosition(522/2, 400);
        }

        writeFile<< highscore;

    }
    writeFile.close();
}


void PowerPelletAni(std::vector<sf::CircleShape> &PowerUp,int &Pwr_ani_frame, int &glowTimer) {

    if(glowTimer == 2*Pwr_ani_frame) {

        for(int i = 0; i<PowerUp.size(); i++) {
            PowerUp[i].setOutlineThickness(-11+Pwr_ani_frame);
        }

        Pwr_ani_frame ++;
    }

    if (glowTimer > 24) {

        Pwr_ani_frame = 1;
        glowTimer = 0;
    }
}

void PacAni(sf::Sprite &PacMan, sf::Texture &texture2, sf::Texture &texture3, int &timer) {

    if(timer == 10)
        PacMan.setTexture(texture3);


    if(timer == 20) {

        PacMan.setTexture(texture2);
        timer = 0;
    }
}

bool PacDeathAni(sf::Sprite &PacDeath, sf::Sprite PacMan, int death_ani_Timer) {

    if(death_ani_Timer==5) {

        PacDeath.setTextureRect(sf::IntRect(Pac_wack1));
        PacDeath.setOrigin(7.5,4);
    }


    if(death_ani_Timer==10) {

        PacDeath.setTextureRect(sf::IntRect(Pac_wack2));
        PacDeath.setOrigin(7.5,3);
        PacDeath.setPosition(PacMan.getPosition().x, PacMan.getPosition().y);
    }
    if(death_ani_Timer==15) {

        PacDeath.setTextureRect(sf::IntRect(Pac_wack3));
        PacDeath.setOrigin(7.5,2.5);
        PacDeath.setPosition(PacMan.getPosition().x, PacMan.getPosition().y);
    }
    if(death_ani_Timer==20) {

        PacDeath.setTextureRect(sf::IntRect(Pac_wack4));
        PacDeath.setOrigin(7.5,2.5);
        PacDeath.setPosition(PacMan.getPosition().x, PacMan.getPosition().y);
    }
    if(death_ani_Timer==25) {

        PacDeath.setTextureRect(sf::IntRect(Pac_wack5));
        PacDeath.setOrigin(7.5,2.5);
        PacDeath.setPosition(PacMan.getPosition().x, PacMan.getPosition().y);
    }
    if(death_ani_Timer==30) {

        PacDeath.setTextureRect(sf::IntRect(Pac_wack6));
        PacDeath.setOrigin(7.5,3);
        PacDeath.setPosition(PacMan.getPosition().x, PacMan.getPosition().y);
    }
    if(death_ani_Timer==35) {

        PacDeath.setTextureRect(sf::IntRect(Pac_wack7));
        PacDeath.setOrigin(6.5,3);
        PacDeath.setPosition(PacMan.getPosition().x, PacMan.getPosition().y);
    }
    if(death_ani_Timer==40) {

        PacDeath.setTextureRect(sf::IntRect(Pac_wack8));
        PacDeath.setOrigin(4.5,3.5);
        PacDeath.setPosition(PacMan.getPosition().x, PacMan.getPosition().y);
    }
    if(death_ani_Timer==45) {

        PacDeath.setTextureRect(sf::IntRect(Pac_wack9));
        PacDeath.setOrigin(2.5,3.5);
        PacDeath.setPosition(PacMan.getPosition().x, PacMan.getPosition().y);
    }
    if(death_ani_Timer==50) {

        PacDeath.setTextureRect(sf::IntRect(Pac_wack10));
        PacDeath.setOrigin(1,1);
        PacDeath.setPosition(PacMan.getPosition().x, PacMan.getPosition().y);
    }
    if(death_ani_Timer==60) {

        PacDeath.setTextureRect(sf::IntRect(Pac_wack11));
        PacDeath.setOrigin(5.5,5.5);
        PacDeath.setPosition(PacMan.getPosition().x, PacMan.getPosition().y);
    }

    if(death_ani_Timer==75) {
        return true;
    } else {
        return false;
    }

}


void BerryPlace(sf::Sprite &Berry, int Berrytimer) {


    if(Berrytimer == 1200) {

        int randtemp = rand()%7;

        if(randtemp == 0)
            Berry.setTextureRect(sf::IntRect(Bry_Cherry));

        if(randtemp == 1)
            Berry.setTextureRect(sf::IntRect(Bry_Strawberry));

        if(randtemp == 2)
            Berry.setTextureRect(sf::IntRect(Bry_Peach));

        if(randtemp == 3)
            Berry.setTextureRect(sf::IntRect(Bry_Apple));

        if(randtemp == 4)
            Berry.setTextureRect(sf::IntRect(Bry_Lime));

        if(randtemp == 5)
            Berry.setTextureRect(sf::IntRect(Bry_Spear));

        if(randtemp == 6)
            Berry.setTextureRect(sf::IntRect(Bry_Bell));

        if(randtemp == 7)
            Berry.setTextureRect(sf::IntRect(Bry_Key));

        Berry.setScale(2.f, 2.f);
        Berry.setPosition(522/2,620/2);
    }

}


bool PowerStop(int powerUpTimer, sf::Sprite &Ghost, sf::Texture &textureOrig, sf::Texture &textureWhite, bool GhostScared, bool GhostDead) {


    if(powerUpTimer <480 || powerUpTimer == 510 || powerUpTimer == 570) {

        if(GhostScared == true && GhostDead == false)
            Ghost.setTexture(textureOrig);
    }

    if(powerUpTimer == 480 || powerUpTimer == 540) {

        if(GhostScared == true && GhostDead == false)
            Ghost.setTexture(textureWhite);
    }


    if(powerUpTimer ==600) {

        return true;
    }


    return false;
}





int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(522, 620), "Pac Man", sf::Style::Default,settings);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));

    srand (time(NULL));

    int place = 0;
    int dotplace = 0;
    int PowerUpplace = 0;
    bool TileChange = false;

    string GameState = "Game";

    //GameState = "Menu";
    //GameState = "Game";
    //GameState = "Scatter";
    //GameState = "Chase";
    //GameState = "Frightened";


    float PacManX = 0;
    float PacManY = 0;
    int PacRow = 14;
    int PacCol = 17;
    int oldPacRow = -1;
    int oldPacCol = -1;
    bool stopPacMan;
    bool PacCloseToCenter = false;
    string CurrentPacDir = "Left";
    bool PacDead = false;


    float RedX = 0;
    float RedY = 0;
    int RedRow = 13;
    int RedCol = 15;
    int Red_OldRow = -1;
    int Red_OldCol = -1;
    int Red_PathPlace = 1;
    int RedPlace = 0;
    const int ScatterRedRow = 23;
    const int ScatterRedCol = 1;
    string CurrentRedDir = "a";
    vector<vector<int>> Red_solution(870);
    vector<int> Red_PathCol;
    vector<int> Red_PathRow;
    bool RedScatter = true;
    bool RedDead = false;
    bool RedScared = false;
    string RedState = "Chase";


    float OrangeX = 0;
    float OrangeY = 0;
    int OrangeRow = 13;
    int OrangeCol = 15;
    int Orange_OldRow = -1;
    int Orange_OldCol = -1;
    int Orange_PathPlace = 1;
    int OrangePlace = 0;
    const int ScatterOrangeRow = 3;
    const int ScatterOrangeCol = 29;
    string CurrentOrangeDir = "a";
    vector<vector<int>> Orange_solution(870);
    vector<int> Orange_PathCol;
    vector<int> Orange_PathRow;
    bool OrangeScatter = false;
    int PacOrangeDistanceX = 0;
    int PacOrangeDistanceY = 0;
    int OrangePacDistance = 0;
    bool OrangeDead = false;
    bool OrangeScared = true;
    string OrangeState = "Chase";


    float BlueX = 0;
    float BlueY = 0;
    int BlueRow = 13;
    int BlueCol = 14;
    int Blue_OldRow = -1;
    int Blue_OldCol = -1;
    int Blue_PathPlace = 1;
    int BluePlace = 0;
    const int ScatterBlueRow = 29;
    const int ScatterBlueCol = 24;
    int PacBlueDistanceX = 0;
    int PacBlueDistanceY = 0;
    string CurrentBlueDir = "a";
    vector<vector<int>> Blue_solution(870);
    vector<int> Blue_PathCol;
    vector<int> Blue_PathRow;
    bool BlueScatter = true;
    bool BlueDead = false;
    bool BlueScared = false;
    string BlueState = "Chase";


    float PinkX = 0;
    float PinkY = 0;
    int PinkRow = 13;
    int PinkCol = 15;
    int Pink_OldRow = -1;
    int Pink_OldCol = -1;
    int Pink_PathPlace = 1;
    int PinkPlace = 0;
    const int ScatterPinkRow = 2;
    const int ScatterPinkCol = 1;
    string CurrentPinkDir = "a";
    vector<vector<int>> Pink_solution(870);
    vector<int> Pink_PathCol;
    vector<int> Pink_PathRow;
    bool PinkScatter = true;
    bool PinkDead = false;
    bool PinkScared = false;
    string PinkState = "Chase";


    int solutionRow = 14;
    int PacLives = 3;
    int solutionCol = 17;
    int StartRow = 13;
    int StartCol = 11;
    int dotsEaten = 0;
    int PowerUpEaten = 0;
    int score = 0;
    int ScaredTimer = 0;
    const int GhostHomeRow = 13;
    const int GhostHomeCol = 11;
    bool ScareStart = false;
    int GameStateTimer = 0;
    int highscore = 0;
    string CurrentDirection = "A";

    int Pwr_ani_frame = 0;
    int glowTimer = 0;

    bool InMenu = true;
    bool GamePaused = false;
    bool InSettings = false;
    int PauseTimer = 0;
    int lives = 2;
    int Berrytimer = 0;
    bool GameOver = false;
    int powerUpTimer = 0;
    bool GhostScared = false;

    string Help_Text = "\t\t\t\t\t\t\t\t HELP \n \n \nMove is Arrow keys \nIf you eat all the dots on the board more will spawn. \nIf a ghost hits you and is not Blue, YOU. WILL. DIE! \nTo make a ghost blue you must eat a power pellet,\nthere are 4 accros the map.\nYou Have 3 lives,\nif you beat the High score You get a free life.\n\n\t\tBy. Nicholas Parise";
    string Settings_Text = "Master Audio: \n\n\n Music: \n\n\n Sound Effects: \n\n\n\n Music Track:";
    string scoreShow;
    string HSString;






    vector <int> TempRowCol;


    std::vector<string> PacManAvallibleDir = {"Left","Right"};


    const vector<vector<int>> GameMatrix = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 8, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 8, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 6, 1, 1, 6, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 6, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 1, 6, 6, 6, 6, 6, 6, 1, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 6, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 8, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 8, 1},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

        //GameMatrix[31 Y][28 X];

        // 0 is a dot
        //1 is a wall
        //6 is a blank spaces
        // 8 is a big dot
    };


    for(int i = 0; i<SIZEX; i++) {
        for(int j = 0; j<SIZEY; j++) {

            Red_solution[i,j].push_back(0);
        }
    }
    for(int i = 0; i<SIZEX; i++) {
        for(int j = 0; j<SIZEY; j++) {

            Orange_solution[i,j].push_back(0);
        }
    }
    for(int i = 0; i<SIZEX; i++) {
        for(int j = 0; j<SIZEY; j++) {

            Blue_solution[i,j].push_back(0);
        }
    }
    for(int i = 0; i<SIZEX; i++) {
        for(int j = 0; j<SIZEY; j++) {

            Pink_solution[i,j].push_back(0);
        }
    }


    std::vector<sf::RectangleShape> Dot(245);

    for (int i = 0; i < Dot.size(); i++) {

        Dot[i].setFillColor(sf::Color::White);
        Dot[i].setSize(sf::Vector2f(5, 5));
        Dot[i].setOrigin(2.5,2.5);
    }


    std::vector<sf::CircleShape> PowerUp(4);

    for (int i = 0; i < PowerUp.size(); i++) {

        PowerUp[i].setFillColor(sf::Color::White);
        PowerUp[i].setRadius(10);
        PowerUp[i].setOrigin(10,10);
        PowerUp[i].setOutlineColor(sf::Color(250, 150, 100));
    }



    std::vector<sf::RectangleShape> Tiles(868);

    for(int i = 0; i<31; i++) {
        for(int j = 0; j<28; j++) {

            Tiles[place].setOrigin(0,0);
            Tiles[place].setSize(sf::Vector2f(18.78571429, 18.61290323));
            Tiles[place].setPosition(sf::Vector2f(18.78571429*j,18.61290323*i));

            if(GameMatrix[i][j] == 0) {
                //  Dot[dotplace].setPosition(sf::Vector2f(17.7857142857*j+j+(17.7857142857/2), 17.6129032258*i+i+(17.6129032258/2)));
                Dot[dotplace].setPosition(sf::Vector2f(18.78571429*j+(18.78571429/2), 18.61290323*i+(18.61290323/2)));
                dotplace++;
                Tiles[place].setFillColor(sf::Color(0,255,255,128));
                Tiles[place].setFillColor(sf::Color(0,255,255,0));
            }

            if(GameMatrix[i][j] == 8) {
//                PowerUp[PowerUpplace].setPosition(sf::Vector2f(17.7857142857*j+j+(17.7857142857/2), 17.6129032258*i+i+(17.6129032258/2)));

                PowerUp[PowerUpplace].setPosition(sf::Vector2f(18.78571429*j+(18.78571429/2), 18.61290323*i+(18.61290323/2)));
                PowerUpplace++;
                Tiles[place].setFillColor(sf::Color(0,255,255,128));
                Tiles[place].setFillColor(sf::Color(0,255,255,0));
            }


            if(GameMatrix[i][j] == 1) {
                Tiles[place].setFillColor(sf::Color(255,0,255,128));
                Tiles[place].setFillColor(sf::Color(255,0,255,0));
            }

            if(GameMatrix[i][j] == 6) {
                //  Tiles[place].setFillColor(sf::Color(255,255,0,128));
                Tiles[place].setFillColor(sf::Color(255,255,0,0));
            }

            place++;
        }
    }



    sf::Image image;
    image.loadFromFile("PacMan_background.png");

    sf::Texture MapTexture;
    MapTexture.loadFromImage(image);

    sf::Sprite Background;
    Background.setTexture(MapTexture);
    Background.setPosition(sf::Vector2f(0, 0));


    sf::Texture PacTexture1;
    PacTexture1.loadFromFile("PacMan_open.png");

    sf::Texture PacTexture2;
    PacTexture2.loadFromFile("PacMan_closed.png");

    sf::Texture RedGTexture1;
    RedGTexture1.loadFromFile("RedGhostRight.png");

    sf::Texture OrangeGTexture1;
    OrangeGTexture1.loadFromFile("OrangeGhostRight.png");

    sf::Texture BlueGTexture1;
    BlueGTexture1.loadFromFile("BlueGhostRight.png");

    sf::Texture PinkGTexture1;
    PinkGTexture1.loadFromFile("PinkGhostRight.png");

    sf::Texture ScaredGhostTexture;
    ScaredGhostTexture.loadFromFile("ScaredGhost.png");

    sf::Texture ScaredGhostTexture2;
    ScaredGhostTexture2.loadFromFile("Assets/Sprite/WhiteDeadGhost.png");


    sf::Texture DeadGhostTexture;
    DeadGhostTexture.loadFromFile("eyes.png");

    sf::Font font;
    font.loadFromFile("Assets/Other/Arial.ttf");

    sf::Texture PauseTexture;
    PauseTexture.loadFromFile("Assets/Sprite/pause.png");


    sf::Sprite PacMan;
    PacMan.setTexture(PacTexture1);
    PacMan.setOrigin(15,15);
    PacMan.setPosition(sf::Vector2f(253.607, 325));


    sf::Sprite RedGhost;
    RedGhost.setTexture(RedGTexture1);
    RedGhost.setOrigin(15,15);
    RedGhost.setPosition(sf::Vector2f(18.78571429*RedRow+(18.78571429/2), 18.61290323*RedCol+(18.61290323/2)));

    sf::Sprite BlueGhost;
    BlueGhost.setTexture(BlueGTexture1);
    BlueGhost.setOrigin(15,15);
    BlueGhost.setPosition(sf::Vector2f(18.78571429*BlueRow+(18.78571429/2), 18.61290323*BlueCol+(18.61290323/2)));

    sf::Sprite OrangeGhost;
    OrangeGhost.setTexture(OrangeGTexture1);
    OrangeGhost.setOrigin(15,15);
    OrangeGhost.setPosition(sf::Vector2f(18.78571429*OrangeRow+(18.78571429/2), 18.61290323*OrangeCol+(18.61290323/2)));

    sf::Sprite PinkGhost;
    PinkGhost.setTexture(PinkGTexture1);
    PinkGhost.setOrigin(15,15);
    PinkGhost.setPosition(sf::Vector2f(18.78571429*PinkRow+(18.78571429/2), 18.61290323*PinkCol+(18.61290323/2)));


    sf::Sprite Paused;
    Paused.setTexture(PauseTexture);
    Paused.setPosition(sf::Vector2f(0, 0));
    Paused.setOrigin(25,31);
    Paused.setScale(1.f,1.f);
    Paused.setPosition(1000,1000);


    //----------------Text----------------

    sf::Text scoreDis("", font);
    scoreDis.setCharacterSize(30);
    scoreDis.setStyle(sf::Text::Bold);
    scoreDis.setFillColor(sf::Color::White);
    scoreDis.setOrigin(15,15);
    scoreDis.setPosition(30,590);


    sf::Text HsDis("", font);
    HsDis.setCharacterSize(30);
    HsDis.setStyle(sf::Text::Bold);
    HsDis.setFillColor(sf::Color::White);
    HsDis.setOrigin(15,15);
    HsDis.setPosition(250, 590);

    sf::Text NewHS("NEW HIGHSCORE!!", font);
    NewHS.setCharacterSize(30);
    NewHS.setStyle(sf::Text::Bold);
    NewHS.setFillColor(sf::Color::Red);
    NewHS.setOrigin(150,15);
    NewHS.setPosition(1000, 1000);

    sf::Text PreStart("Push Space To Start", font);
    PreStart.setCharacterSize(30);
    PreStart.setStyle(sf::Text::Bold);
    PreStart.setFillColor(sf::Color::White);
    PreStart.setOrigin(142,15);
    PreStart.setPosition(522/2, 620/2);

    sf::Text GameDone("GAME OVER", font);
    GameDone.setCharacterSize(30);
    GameDone.setStyle(sf::Text::Bold);
    GameDone.setFillColor(sf::Color::Red);
    GameDone.setOrigin(95,15);
    GameDone.setPosition(1000, 1000);


    sf::Text Help_text_sprite(Help_Text, font);
    Help_text_sprite.setCharacterSize(20);
    Help_text_sprite.setStyle(sf::Text::Bold);
    Help_text_sprite.setFillColor(sf::Color::White);
    Help_text_sprite.setPosition(1000, 1000);


    sf::Text Settings_text_sprite(Settings_Text, font);
    Settings_text_sprite.setCharacterSize(30);
    Settings_text_sprite.setStyle(sf::Text::Bold);
    Settings_text_sprite.setFillColor(sf::Color::White);
    Settings_text_sprite.setPosition(1000, 1000);







    sf::Vector2i pixelPos;
    sf::Vector2f worldPos;


    bool BlueFail = false;

    sf::RectangleShape shape(sf::Vector2f(20, 20));
    shape.setOrigin(10,10);
    shape.setFillColor(sf::Color(50, 50, 250));


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 69;
            }

            if (event.type == sf::Event::Resized) {
                view = getLetterboxView( view, event.size.width, event.size.height );
            }

            pixelPos = sf::Mouse::getPosition(window);
            worldPos = window.mapPixelToCoords(pixelPos);

            if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {
                // cout<<worldPos.x<<" "<<worldPos.y<<endl;
                TempRowCol = ClossestTile(worldPos.x,worldPos.y, Tiles);
                cout<<endl;
                cout<<TempRowCol[0]<<" "<<TempRowCol[1]<<endl;
                //  return 0;
            }
        }



        TempRowCol = ClossestTile(PacMan.getPosition().x,PacMan.getPosition().y, Tiles);
        PacRow = TempRowCol[0];
        PacCol = TempRowCol[1];

        TempRowCol = ClossestTile(RedGhost.getPosition().x,RedGhost.getPosition().y, Tiles);
        RedRow = TempRowCol[0];
        RedCol = TempRowCol[1];

        TempRowCol = ClossestTile(OrangeGhost.getPosition().x,OrangeGhost.getPosition().y, Tiles);
        OrangeRow = TempRowCol[0];
        OrangeCol = TempRowCol[1];

        TempRowCol = ClossestTile(BlueGhost.getPosition().x,BlueGhost.getPosition().y, Tiles);
        BlueRow = TempRowCol[0];
        BlueCol = TempRowCol[1];

        TempRowCol = ClossestTile(PinkGhost.getPosition().x,PinkGhost.getPosition().y, Tiles);
        PinkRow = TempRowCol[0];
        PinkCol = TempRowCol[1];



        if(PacRow != oldPacRow || PacCol != oldPacCol || Orange_OldCol != OrangeCol || Orange_OldRow != OrangeRow || Pink_OldCol != PinkCol || Pink_OldRow != PinkRow||Red_OldCol != RedCol || Red_OldRow != RedRow||Blue_OldCol != BlueCol || Blue_OldRow != BlueRow) {


            oldPacCol = PacCol;
            oldPacRow = PacRow;
            solutionRow =  PacRow;
            solutionCol = PacCol;



            place = 0;
            for(int i = 0; i<31; i++) {
                for(int j = 0; j<28; j++) {

                    if(GameMatrix[i][j] == 0) {
                        Tiles[place].setFillColor(sf::Color(0,255,255,0));
                    }
                    if(GameMatrix[i][j] == 8) {
                        Tiles[place].setFillColor(sf::Color(0,255,255,0));
                    }
                    if(GameMatrix[i][j] == 6) {
                        Tiles[place].setFillColor(sf::Color(255,255,0,0));
                    }
                    place++;
                }
            }


            //Red
            if(PacRow != oldPacRow || PacCol != oldPacCol || Red_OldCol != RedCol || Red_OldRow != RedRow) {

                Red_OldRow = RedRow;
                Red_OldCol = RedCol;
                Red_PathCol.clear();
                Red_PathRow.clear();


                for(int x = 0; x<SIZEX; x++) {
                    for(int y = 0; y<SIZEY; y++) {

                        Red_solution[y][x] = 0;

                    }
                }


                if(RedDead == true) {

                    solvemaze(RedCol,RedRow,GhostHomeRow,GhostHomeCol, CurrentRedDir, Red_solution,Red_PathCol,Red_PathRow,GameMatrix);

                } else {

                    if(RedScared == true) {

                        ScaredSolver(RedCol, RedRow, CurrentRedDir, Red_solution, Red_PathCol, Red_PathRow, GameMatrix);

                    } else if(RedScatter == false) {
                        solvemaze(RedCol,RedRow,solutionRow,solutionCol, CurrentRedDir, Red_solution,Red_PathCol,Red_PathRow,GameMatrix);
                        //  printsolution(solutionRow,solutionCol,StartRow,StartCol,Red_solution,GameMatrix);
                    } else if(RedScatter == true) {
                        solvemaze(RedCol,RedRow,ScatterRedRow,ScatterRedCol, CurrentRedDir, Red_solution,Red_PathCol,Red_PathRow,GameMatrix);
                        //  printsolution(solutionRow,solutionCol,StartRow,StartCol,Red_solution,GameMatrix);
                    }
                }
            }


            //Blue
            if(PacRow != oldPacRow || PacCol != oldPacCol || Blue_OldCol != BlueCol || Blue_OldRow != BlueRow) {


                Blue_OldRow = BlueRow;
                Blue_OldCol = BlueCol;
                Blue_PathCol.clear();
                Blue_PathRow.clear();

                for(int x = 0; x<SIZEX; x++) {
                    for(int y = 0; y<SIZEY; y++) {
                        Blue_solution[y][x] = 0;
                    }
                }


                if(BlueDead == true) {

                    solvemaze(BlueCol,BlueRow,GhostHomeRow,GhostHomeCol, CurrentBlueDir, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix);
                    //  printsolution(solutionRow,solutionCol,StartRow,StartCol,Blue_solution,GameMatrix);
                } else {

                    if(BlueScared == true) {

                        ScaredSolver(BlueCol, BlueRow, CurrentBlueDir, Blue_solution, Blue_PathCol, Blue_PathRow, GameMatrix);

                    } else if(BlueScatter == false) {


                        PacBlueDistanceY = PacCol-RedCol;

                        PacBlueDistanceX = PacRow-RedRow;

                        BlueFail = false;

                        if(RedRow > PacRow) {

                            if(RedCol >PacCol) {

                                if(!solvemaze(BlueCol,BlueRow,solutionRow-PacBlueDistanceX,solutionCol+PacBlueDistanceY, CurrentBlueDir, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix)) {
                                    BlueFail = true;
                                }

                                shape.setPosition(sf::Vector2f(18.78571429*solutionRow+(PacBlueDistanceX*PacBlueDistanceX)+(18.78571429/2), 18.61290323*solutionCol+(PacBlueDistanceY*PacBlueDistanceY)+(18.61290323/2)));
                            } else {
                                if(!solvemaze(BlueCol,BlueRow,solutionRow-PacBlueDistanceX,solutionCol+PacBlueDistanceY, CurrentBlueDir, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix)) {
                                    BlueFail = true;
                                }

                                shape.setPosition(sf::Vector2f(18.78571429*solutionRow-(PacBlueDistanceX*PacBlueDistanceX)+(18.78571429/2), 18.61290323*solutionCol-(PacBlueDistanceY*PacBlueDistanceY)+(18.61290323/2)));
                            }

                        } else {

                            if(RedCol >PacCol) {

                                if(!solvemaze(BlueCol,BlueRow,solutionRow+PacBlueDistanceX,solutionCol-PacBlueDistanceY, CurrentBlueDir, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix)) {
                                    BlueFail = true;
                                }

                                shape.setPosition(sf::Vector2f(18.78571429*solutionRow+(PacBlueDistanceX*PacBlueDistanceX)+(18.78571429/2), 18.61290323*solutionCol-(PacBlueDistanceY*PacBlueDistanceY)+(18.61290323/2)));

                            } else {
                                if(!solvemaze(BlueCol,BlueRow,solutionRow-PacBlueDistanceX,solutionCol-PacBlueDistanceY, CurrentBlueDir, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix)) {
                                    BlueFail = true;
                                }
                                shape.setPosition(sf::Vector2f(18.78571429*solutionRow-(PacBlueDistanceX*PacBlueDistanceX)+(18.78571429/2), 18.61290323*solutionCol-(PacBlueDistanceY*PacBlueDistanceY)+(18.61290323/2)));
                            }
                        }

                        if(BlueFail == true) {
                            solvemaze(BlueCol,BlueRow,solutionRow,solutionCol, CurrentBlueDir, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix);
                            cout<<"Unless..."<<endl;
                        }

                        //  solvemaze(BlueCol,BlueRow,solutionRow,solutionCol, CurrentBlueDir, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix);
                        //  printsolution(solutionRow,solutionCol,StartRow,StartCol,Blue_solution,GameMatrix);
                    } else if(BlueScatter == true) {

                        solvemaze(BlueCol,BlueRow,ScatterBlueRow,ScatterBlueCol, CurrentBlueDir, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix);
                        //  printsolution(solutionRow,solutionCol,StartRow,StartCol,Blue_solution,GameMatrix);
                    }
                }
            }

            solutionRow =  PacRow;
            solutionCol = PacCol;


            //Orange
            if(PacRow != oldPacRow || PacCol != oldPacCol || Orange_OldCol != OrangeCol || Orange_OldRow != OrangeRow) {

                Orange_OldRow = OrangeRow;
                Orange_OldCol = OrangeCol;
                Orange_PathCol.clear();
                Orange_PathRow.clear();

                PacOrangeDistanceX = SmallestDistance(PacRow, OrangeRow);
                PacOrangeDistanceY = SmallestDistance(PacCol, OrangeCol);
                OrangePacDistance = (PacOrangeDistanceX*PacOrangeDistanceX)+(PacOrangeDistanceY*PacOrangeDistanceY);

                if(OrangePacDistance<80) {

                    OrangeScatter = true;
                } else {

                    if(GameState !="Scatter") {
                        OrangeScatter = false;
                    }
                }

                for(int x = 0; x<SIZEX; x++) {
                    for(int y = 0; y<SIZEY; y++) {

                        Orange_solution[y][x] = 0;
                    }
                }


                if(OrangeDead == true) {

                    solvemaze(OrangeCol,OrangeRow,GhostHomeRow,GhostHomeCol, CurrentOrangeDir, Orange_solution,Orange_PathCol,Orange_PathRow,GameMatrix);

                } else {

                    if(OrangeScared == true) {

                        ScaredSolver(OrangeCol, OrangeRow, CurrentOrangeDir, Orange_solution, Orange_PathCol, Orange_PathRow, GameMatrix);

                    } else if(OrangeScatter == false) {

                        solvemaze(OrangeCol,OrangeRow,solutionRow,solutionCol, CurrentOrangeDir, Orange_solution,Orange_PathCol,Orange_PathRow,GameMatrix);
                        //  printsolution(solutionRow,solutionCol,StartRow,StartCol,Blue_solution,GameMatrix);
                    } else {
                        solvemaze(OrangeCol,OrangeRow,ScatterOrangeRow,ScatterOrangeCol, CurrentOrangeDir, Orange_solution,Orange_PathCol,Orange_PathRow,GameMatrix);
                        //  printsolution(solutionRow,solutionCol,StartRow,StartCol,Blue_solution,GameMatrix);
                    }
                }
            }

            solutionRow =  PacRow;
            solutionCol = PacCol;


            //Pink
            if(PacRow != oldPacRow || PacCol != oldPacCol || Pink_OldCol != PinkCol || Pink_OldRow != PinkRow) {

                Pink_OldRow = PinkRow;
                Pink_OldCol = PinkCol;
                Pink_PathCol.clear();
                Pink_PathRow.clear();

                for(int x = 0; x<SIZEX; x++) {
                    for(int y = 0; y<SIZEY; y++) {
                        Pink_solution[y][x] = 0;
                    }
                }



                if(PinkDead == true) {

                    solvemaze(PinkCol,PinkRow,GhostHomeRow,GhostHomeCol, CurrentPinkDir, Pink_solution,Pink_PathCol,Pink_PathRow,GameMatrix);

                } else {


                    if(PinkScared == true) {

                        ScaredSolver(PinkCol, PinkRow, CurrentPinkDir, Pink_solution, Pink_PathCol, Pink_PathRow, GameMatrix);

                    } else if(PinkScatter == false) {

                        if(CurrentPacDir == "Up") {
                            solutionCol-=4;
                        }
                        if(CurrentPacDir == "Down") {
                            solutionCol+=4;
                        }
                        if(CurrentPacDir == "Left") {
                            solutionRow-=4;
                        }
                        if(CurrentPacDir == "Right") {
                            solutionRow+=4;
                        }


                        solvemaze(PinkCol,PinkRow,solutionRow,solutionCol, CurrentPinkDir, Pink_solution,Pink_PathCol,Pink_PathRow,GameMatrix);
                        //  printsolution(solutionRow,solutionCol,StartRow,StartCol,Blue_solution,GameMatrix);

                    } else {
                        solvemaze(PinkCol,PinkRow,ScatterPinkRow,ScatterPinkCol, CurrentPinkDir, Pink_solution,Pink_PathCol,Pink_PathRow,GameMatrix);
                        //  printsolution(solutionRow,solutionCol,StartRow,StartCol,Blue_solution,GameMatrix);
                    }
                }


            }


            for(int i = 0; i<Pink_PathCol.size(); i++) {

                RedPlace = 0;
                RedPlace +=Pink_PathRow[i]*28;
                RedPlace +=Pink_PathCol[i];
                Tiles[RedPlace].setFillColor(sf::Color(255,105,180,128));
            }

            for(int i = 0; i<Orange_PathCol.size(); i++) {

                RedPlace = 0;
                RedPlace +=Orange_PathRow[i]*28;
                RedPlace +=Orange_PathCol[i];
                Tiles[RedPlace].setFillColor(sf::Color(255,140,0,128));
            }

            for(int i = 0; i<Blue_PathCol.size(); i++) {

                RedPlace = 0;
                RedPlace +=Blue_PathRow[i]*28;
                RedPlace +=Blue_PathCol[i];
                Tiles[RedPlace].setFillColor(sf::Color(0,0,255,128));
            }

            for(int i = 0; i<Red_PathCol.size(); i++) {

                RedPlace = 0;
                RedPlace +=Red_PathRow[i]*28;
                RedPlace +=Red_PathCol[i];
                Tiles[RedPlace].setFillColor(sf::Color(255,0,0,128));
            }


        }
        //////////////



        PacManAvallibleDir = WallTest(GameMatrix, PacRow, PacCol, CurrentPacDir,stopPacMan);

        //  PacCloseToCenter = CenterOfTile(PacRow, PacCol, CurrentPacDir, PacMan,stopPacMan);







        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

            if(GamePaused == false && InMenu == false && PauseTimer >10) {

                GamePaused = true;
                Paused.setPosition(261,288);
                // BackG_Pizza.pause();
                // BackG_Subwooder.pause();
                // BackG_Sweden.pause();
            }

            else if(GamePaused == true && InMenu == false && PauseTimer > 50) {

                PauseTimer = 0;
                GamePaused = false;
                Paused.setPosition(1000,1000);
                /*
                                if(Music == true) {

                                    if(Track == 1) {

                                        BackG_Pizza.play();
                                    }
                                    if(Track == 2) {

                                        BackG_Subwooder.play();
                                    }

                                    if(Track == 3) {

                                        BackG_Sweden.play();
                                    }
                                }
                */

            }
        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& InMenu == true && InSettings == false) {

            cout<<"adsa"<<endl;

            GameOver = false;

            InMenu = false;

            dotsEaten = 0;
            PowerUpEaten = 0;

            Berrytimer = 0;
            lives = 2;
            GhostScared = false;

            dotplace = 0;
            PowerUpplace = 0;
            for(int i = 0; i<31; i++) {
                for(int j = 0; j<28; j++) {

                    if(GameMatrix[i][j] == 0) {
                        Dot[dotplace].setPosition(sf::Vector2f(18.78571429*j+(18.78571429/2), 18.61290323*i+(18.61290323/2)));
                        dotplace++;
                    }
                    if(GameMatrix[i][j] == 8) {
                        PowerUp[PowerUpplace].setPosition(sf::Vector2f(18.78571429*j+(18.78571429/2), 18.61290323*i+(18.61290323/2)));
                        PowerUpplace++;
                    }
                }
            }


            powerUpTimer = 601;
            score = 0;
            PowerUpEaten = 0;
            dotsEaten = 0;
            PacManX = 0;
            PacManY = 0;
            RedX = 0;
            RedY = 0;
            OrangeX = 0;
            OrangeY = 0;
            BlueX = 0;
            BlueY = 0;
            PinkX = 0;
            PinkY = 0;

            PinkDead = false;
            PinkScared = false;
            PinkScatter = true;

            OrangeDead = false;
            OrangeScared = false;
            OrangeScatter = true;

            BlueDead = false;
            BlueScared = false;
            BlueScatter = true;

            RedScared = false;
            RedDead = false;
            RedScatter = true;

            GameState = "Scatter";

            RedGhost.setTexture(RedGTexture1);
            OrangeGhost.setTexture(OrangeGTexture1);
            BlueGhost.setTexture(BlueGTexture1);
            PinkGhost.setTexture(PinkGTexture1);


            PacMan.setPosition(sf::Vector2f(253.607, 325));

            RedGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            BlueGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            OrangeGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            PinkGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            CurrentRedDir = "a";
            CurrentBlueDir = "a";
            CurrentPinkDir = "a";
            CurrentOrangeDir = "a";

            GameStateTimer = -1;




            /*

            BackG_Wii.stop();

            if(Sound_Ef == true) {
                Button_click.play();
                Mac_start.play();
            }

            if(Music == true) {

                if(Track == 1) {
                    BackG_Pizza.play();
                }
                if(Track == 2) {
                    BackG_Subwooder.play();
                }
                if(Track == 3) {
                    BackG_Sweden.play();
                }
            }
            */


            // Setting.setPosition(1000, 1000);
            //  Help.setPosition(1000, 1000);
            // StartImage.setPosition(1000, 1000);
            //  PreStart.setPosition(1000,1000);

        }





        for(int i = 0; i<PacManAvallibleDir.size(); i++) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && PacManAvallibleDir[i] == "Left") {

                PacMan.setRotation(-180);
                //  PacManX = -2.7857142857;
                PacManX = -2;
                PacManY = 0;
                CurrentPacDir = "Left";

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& PacManAvallibleDir[i] == "Right") {

                PacMan.setRotation(0);
                //PacManX = 2.7857142857;
                PacManX = 2;
                PacManY = 0;
                CurrentPacDir = "Right";

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& PacManAvallibleDir[i] == "Up") {

                PacMan.setRotation(-90);
                //   PacManY = -2.6129032258;
                PacManY = -2;
                PacManX = 0;
                CurrentPacDir = "Up";

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& PacManAvallibleDir[i] == "Down") {

                PacMan.setRotation(90);
                //  PacManY = 2.6129032258;
                PacManY = 2;
                PacManX = 0;
                CurrentPacDir = "Down";

            }
        }

        if(PacMan.getPosition().y<0) {

            PacMan.setPosition(PacMan.getPosition().x,620);
        }

        if(PacMan.getPosition().y>620) {

            PacMan.setPosition(PacMan.getPosition().x,0);
        }

        if(PacMan.getPosition().x<10) {

            PacMan.setPosition(522,269.887096835);
        }

        if(PacMan.getPosition().x>522) {

            PacMan.setPosition(10,269.887096835);
        }


        if(RedGhost.getPosition().x<20 && CurrentRedDir == "Left") {

            RedGhost.setPosition(522,269.887096835);
        }

        if(RedGhost.getPosition().x>512 && CurrentRedDir == "Right") {

            RedGhost.setPosition(10,269.887096835);
        }


        if(OrangeGhost.getPosition().x<20 && CurrentOrangeDir == "Left") {

            OrangeGhost.setPosition(522,269.887096835);
        }

        if(OrangeGhost.getPosition().x>512 && CurrentOrangeDir == "Right") {

            OrangeGhost.setPosition(10,269.887096835);
        }


        if(BlueGhost.getPosition().x<20 && CurrentBlueDir == "Left") {

            BlueGhost.setPosition(522,269.887096835);
        }

        if(BlueGhost.getPosition().x>512 && CurrentBlueDir == "Right") {

            BlueGhost.setPosition(10,269.887096835);
        }


        if(PinkGhost.getPosition().x<20 && CurrentPinkDir == "Left") {

            PinkGhost.setPosition(522,269.887096835);
        }

        if(PinkGhost.getPosition().x>512 && CurrentPinkDir == "Right") {

            PinkGhost.setPosition(10,269.887096835);
        }


        if(stopPacMan == true ) {
            //&& PacCloseToCenter == true
            stopPacMan = false;
            PacManX = 0;
            PacManY = 0;
        }





        if(OutOfTheCloset(RedRow, RedCol, CurrentRedDir, Red_PathCol, Red_PathRow, GhostHomeRow, GhostHomeCol, RedDead)) {

            RedScared = false;
            RedDead = false;
            RedGhost.setTexture(RedGTexture1);
        }

        if(OutOfTheCloset(OrangeRow, OrangeCol, CurrentOrangeDir, Orange_PathCol, Orange_PathRow, GhostHomeRow, GhostHomeCol, OrangeDead)) {

            OrangeScared = false;
            OrangeDead = false;
            OrangeGhost.setTexture(OrangeGTexture1);
        }

        if(OutOfTheCloset(BlueRow, BlueCol, CurrentBlueDir, Blue_PathCol, Blue_PathRow, GhostHomeRow, GhostHomeCol, BlueDead)) {

            BlueScared = false;
            BlueDead = false;
            BlueGhost.setTexture(BlueGTexture1);
        }

        if(OutOfTheCloset(PinkRow, PinkCol, CurrentPinkDir, Pink_PathCol, Pink_PathRow, GhostHomeRow, GhostHomeCol, PinkDead)) {

            PinkScared = false;
            PinkDead = false;
            PinkGhost.setTexture(PinkGTexture1);
        }






//Red
        if((RedRow+1) == Red_PathCol[1] && RedCol == Red_PathRow[1] && CurrentRedDir != "Left") {

            RedX = 1.5;
            RedY = 0;
            CurrentRedDir = "Right";
            //cout<<"Right"<<endl;

            //  RedGhost.setPosition((18.78571429*(RedRow+1))+(18.78571429/2),RedGhost.getPosition().y);

        } else  if((RedRow-1) == Red_PathCol[1] && RedCol == Red_PathRow[1] && CurrentRedDir != "Right") {

            RedX = -1.5;
            RedY = 0;
            CurrentRedDir = "Left";
            //cout<<"Left"<<endl;
            //  RedGhost.setPosition((18.78571429*(RedRow-1))+(18.78571429/2),RedGhost.getPosition().y);

        } else if((RedCol-1) == Red_PathRow[1] && RedRow == Red_PathCol[1] && CurrentRedDir != "Down") {

            RedX = 0;
            RedY = -1.5;
            CurrentRedDir = "Up";
            //cout<<"Up"<<endl;
            //   RedGhost.setPosition(RedGhost.getPosition().x,(18.61290323*(RedCol-1))+(18.61290323/2));

        } else if((RedCol+1) == Red_PathRow[1] && RedRow == Red_PathCol[1] && CurrentRedDir != "Up") {

            RedX = 0;
            RedY = 1.5;
            CurrentRedDir = "Down";
            //cout<<"Down"<<endl;
            //  RedGhost.setPosition(RedGhost.getPosition().x,(18.61290323*(RedCol+1))+(18.61290323/2));
        } else {
            //   RedX = 0;
            //    RedY = 0;
        }
        // RedGhost.setPosition(((18.61290323*Red_PathCol[1])+(18.61290323/2)),((18.61290323*Red_PathRow[1])+(18.61290323/2)));


//Orange
        if((OrangeRow+1) == Orange_PathCol[1] && OrangeCol == Orange_PathRow[1] && CurrentOrangeDir != "Left") {

            OrangeX = 1.5;
            OrangeY = 0;
            CurrentOrangeDir = "Right";
            //cout<<"Right"<<endl;

            //  OrangeGhost.setPosition((18.78571429*(OrangeRow+1))+(18.78571429/2),OrangeGhost.getPosition().y);

        } else  if((OrangeRow-1) == Orange_PathCol[1] && OrangeCol == Orange_PathRow[1] && CurrentOrangeDir != "Right") {

            OrangeX = -1.5;
            OrangeY = 0;
            CurrentOrangeDir = "Left";
            //cout<<"Left"<<endl;
            //  OrangeGhost.setPosition((18.78571429*(OrangeRow-1))+(18.78571429/2),OrangeGhost.getPosition().y);

        } else if((OrangeCol-1) == Orange_PathRow[1] && OrangeRow == Orange_PathCol[1] && CurrentOrangeDir != "Down") {

            OrangeX = 0;
            OrangeY = -1.5;
            CurrentOrangeDir = "Up";
            //cout<<"Up"<<endl;
            //   OrangeGhost.setPosition(OrangeGhost.getPosition().x,(18.61290323*(OrangeCol-1))+(18.61290323/2));

        } else if((OrangeCol+1) == Orange_PathRow[1] && OrangeRow == Orange_PathCol[1] && CurrentOrangeDir != "Up") {

            OrangeX = 0;
            OrangeY = 1.5;
            CurrentOrangeDir = "Down";
            //cout<<"Down"<<endl;
            //  OrangeGhost.setPosition(OrangeGhost.getPosition().x,(18.61290323*(OrangeCol+1))+(18.61290323/2));
        }


//Blue
        if((BlueRow+1) == Blue_PathCol[1] && BlueCol == Blue_PathRow[1] && CurrentBlueDir != "Left") {

            BlueX = 1.5;
            BlueY = 0;
            CurrentBlueDir = "Right";
            //cout<<"Right"<<endl;

            //  BlueGhost.setPosition((18.78571429*(BlueRow+1))+(18.78571429/2),BlueGhost.getPosition().y);

        } else  if((BlueRow-1) == Blue_PathCol[1] && BlueCol == Blue_PathRow[1] && CurrentBlueDir != "Right") {

            BlueX = -1.5;
            BlueY = 0;
            CurrentBlueDir = "Left";
            //cout<<"Left"<<endl;
            //  BlueGhost.setPosition((18.78571429*(BlueRow-1))+(18.78571429/2),BlueGhost.getPosition().y);

        } else if((BlueCol-1) == Blue_PathRow[1] && BlueRow == Blue_PathCol[1] && CurrentBlueDir != "Down") {

            BlueX = 0;
            BlueY = -1.5;
            CurrentBlueDir = "Up";
            //cout<<"Up"<<endl;
            //   BlueGhost.setPosition(BlueGhost.getPosition().x,(18.61290323*(BlueCol-1))+(18.61290323/2));

        } else if((BlueCol+1) == Blue_PathRow[1] && BlueRow == Blue_PathCol[1] && CurrentBlueDir != "Up") {

            BlueX = 0;
            BlueY = 1.5;
            CurrentBlueDir = "Down";
            //cout<<"Down"<<endl;
            //  BlueGhost.setPosition(BlueGhost.getPosition().x,(18.61290323*(BlueCol+1))+(18.61290323/2));
        }


//Pink
        if((PinkRow+1) == Pink_PathCol[Pink_PathPlace] && PinkCol == Pink_PathRow[Pink_PathPlace] && CurrentPinkDir != "Left") {

            PinkX = 1.5;
            PinkY = 0;
            CurrentPinkDir = "Right";
            //cout<<"Right"<<endl;

            //  PinkGhost.setPosition((18.78571429*(PinkRow+1))+(18.78571429/2),PinkGhost.getPosition().y);

        } else  if((PinkRow-1) == Pink_PathCol[Pink_PathPlace] && PinkCol == Pink_PathRow[Pink_PathPlace] && CurrentPinkDir != "Right") {

            PinkX = -1.5;
            PinkY = 0;
            CurrentPinkDir = "Left";
            //cout<<"Left"<<endl;
            //  PinkGhost.setPosition((18.78571429*(PinkRow-1))+(18.78571429/2),PinkGhost.getPosition().y);

        } else if((PinkCol-1) == Pink_PathRow[Pink_PathPlace] && PinkRow == Pink_PathCol[Pink_PathPlace] && CurrentPinkDir != "Down") {

            PinkX = 0;
            PinkY = -1.5;
            CurrentPinkDir = "Up";
            //cout<<"Up"<<endl;
            //   PinkGhost.setPosition(PinkGhost.getPosition().x,(18.61290323*(PinkCol-1))+(18.61290323/2));

        } else if((PinkCol+1) == Pink_PathRow[Pink_PathPlace] && PinkRow == Pink_PathCol[Pink_PathPlace] && CurrentPinkDir != "Up") {

            PinkX = 0;
            PinkY = 1.5;
            CurrentPinkDir = "Down";
            //cout<<"Down"<<endl;
            //  PinkGhost.setPosition(PinkGhost.getPosition().x,(18.61290323*(PinkCol+1))+(18.61290323/2));
        }

        if(PinkCol == Pink_PathRow[Pink_PathPlace] && PinkRow == Pink_PathCol[Pink_PathPlace]) {

            //   Pink_PathPlace++;
        }






        // --Dot Hittest--

        for (int i = 0; i < Dot.size(); i++) {
            if(PacMan.getGlobalBounds().intersects(Dot[i].getGlobalBounds())) {
                Dot[i].setPosition(Dot[i].getPosition().x+1000,Dot[i].getPosition().y);

                dotsEaten ++;
                score +=5;
            }
        }


        for (int i = 0; i < PowerUp.size(); i++) {
            if(PacMan.getGlobalBounds().intersects(PowerUp[i].getGlobalBounds())) {
                PowerUp[i].setPosition(PowerUp[i].getPosition().x+1000,PowerUp[i].getPosition().y);

                powerUpTimer = 0;

                GhostScared = true;

                PowerUpEaten ++;
                score +=25;

                GameState = "Chase";

                if(RedDead == false) {
                    RedScared = true;
                    RedGhost.setTexture(ScaredGhostTexture);
                    ScareStart = true;
                    ScaredTimer = 0;
                    CurrentRedDir = "a";
                }

                if(OrangeDead == false) {
                    OrangeScared = true;
                    OrangeGhost.setTexture(ScaredGhostTexture);
                    ScareStart = true;
                    ScaredTimer = 0;
                    CurrentOrangeDir = "a";
                }

                if(PinkDead == false) {
                    PinkScared = true;
                    PinkGhost.setTexture(ScaredGhostTexture);
                    ScareStart = true;
                    ScaredTimer = 0;
                    CurrentPinkDir = "a";
                }

                if(BlueDead == false) {
                    BlueScared = true;
                    BlueGhost.setTexture(ScaredGhostTexture);
                    ScareStart = true;
                    ScaredTimer = 0;
                    CurrentBlueDir = "a";
                }
            }
        }



        if(ScaredTimer > (60*8) && ScareStart == true) {

            ScareStart = false;

            if(RedScared == true && RedDead == false) {
                //     RedScared = false;
                //   RedGhost.setTexture(RedGTexture1);
            }

            if(OrangeScared == true && OrangeDead == false) {
              //  OrangeScared = false;
          //    //  OrangeGhost.setTexture(OrangeGTexture1);
            }

            if(BlueScared == true && BlueDead == false) {
           //     BlueScared = false;
           //     BlueGhost.setTexture(BlueGTexture1);
            }

            if(PinkScared == true && PinkDead == false) {
             //   PinkScared = false;
             //   PinkGhost.setTexture(PinkGTexture1);
            }


        } else {
            ScaredTimer++;
        }





        if(PowerStop(powerUpTimer, RedGhost, ScaredGhostTexture, ScaredGhostTexture2, RedScared, RedDead) == true) {

            RedGhost.setTexture(RedGTexture1);
            RedScared = false;
            GhostScared = false;
        }
        if(PowerStop(powerUpTimer, OrangeGhost, ScaredGhostTexture, ScaredGhostTexture2, OrangeScared, OrangeDead) == true) {

            OrangeGhost.setTexture(OrangeGTexture1);
            OrangeScared = false;
            GhostScared = false;
        }
        if(PowerStop(powerUpTimer, BlueGhost, ScaredGhostTexture, ScaredGhostTexture2, BlueScared, BlueDead) == true) {

            BlueGhost.setTexture(BlueGTexture1);
            BlueScared = false;
            GhostScared = false;
        }
        if(PowerStop(powerUpTimer, PinkGhost, ScaredGhostTexture, ScaredGhostTexture2, PinkScared, PinkDead) == true) {

            PinkGhost.setTexture(PinkGTexture1);
            PinkScared = false;
            GhostScared = false;
        }





        if(PacMan.getGlobalBounds().intersects(RedGhost.getGlobalBounds())) {

            if(RedScared == true && RedDead == false) {
                score +=10;
                RedDead = true;
                RedGhost.setTexture(DeadGhostTexture);
            } else {
                PacDead = true;
            }

        }

        if(PacMan.getGlobalBounds().intersects(OrangeGhost.getGlobalBounds())) {

            if(OrangeScared == true && OrangeDead == false) {
                score +=10;
                OrangeDead = true;
                OrangeGhost.setTexture(DeadGhostTexture);
            } else {
                PacDead = true;
            }
        }

        if(PacMan.getGlobalBounds().intersects(BlueGhost.getGlobalBounds())) {
            if(BlueScared == true && BlueDead == false) {
                score +=10;
                BlueDead = true;
                BlueGhost.setTexture(DeadGhostTexture);
            } else {
                PacDead = true;
            }

        }

        if(PacMan.getGlobalBounds().intersects(PinkGhost.getGlobalBounds())) {

            if(PinkScared == true && PinkDead == false) {
                score +=10;
                PinkDead = true;
                PinkGhost.setTexture(DeadGhostTexture);
            } else {
                PacDead = true;
            }

        }



        //GameState Timer
        //5 seconds Scatter
        //20 seconds Chase
        //5 Seconds Scatter
        //20 Seconds Chase
        //5 seconds Scatter
        //20 seconds chase
        //5 seconds scatter
        //rest of time Chase

        if(GameStateTimer  == 60*5 || GameStateTimer  == 60*30|| GameStateTimer  == 60*55|| GameStateTimer  == 60*80) {

            GameState = "Chase";
            cout<<"Chase"<<endl;
            PinkScatter = false;
            OrangeScatter = false;
            RedScatter = false;
            BlueScatter = false;

        } else if(GameStateTimer == 60*25|| GameStateTimer  == 60*50|| GameStateTimer  == 60*75) {

            GameState = "Scatter";
            cout<<"Scatter"<<endl;
            PinkScatter = true;
            OrangeScatter = true;
            RedScatter = true;
            BlueScatter = true;
        }
        cout<<GameStateTimer<<endl;



        if(dotsEaten == 244 && PowerUpEaten==4) {

            cout<<"Next Level"<<endl;

            dotplace = 0;
            PowerUpplace = 0;
            for(int i = 0; i<31; i++) {
                for(int j = 0; j<28; j++) {

                    if(GameMatrix[i][j] == 0) {
                        Dot[dotplace].setPosition(sf::Vector2f(18.78571429*j+(18.78571429/2), 18.61290323*i+(18.61290323/2)));
                        dotplace++;
                    }
                    if(GameMatrix[i][j] == 8) {
                        PowerUp[PowerUpplace].setPosition(sf::Vector2f(18.78571429*j+(18.78571429/2), 18.61290323*i+(18.61290323/2)));
                        PowerUpplace++;
                    }
                }
            }


            PowerUpEaten = 0;
            dotsEaten = 0;
            PacManX = 0;
            PacManY = 0;
            RedX = 0;
            RedY = 0;
            OrangeX = 0;
            OrangeY = 0;
            BlueX = 0;
            BlueY = 0;
            PinkX = 0;
            PinkY = 0;

            PinkDead = false;
            PinkScared = false;
            PinkScatter = true;

            OrangeDead = false;
            OrangeScared = false;
            OrangeScatter = true;

            BlueDead = false;
            BlueScared = false;
            BlueScatter = true;

            RedScared = false;
            RedDead = false;
            RedScatter = true;

            GameState = "Scatter";

            RedGhost.setTexture(RedGTexture1);
            OrangeGhost.setTexture(OrangeGTexture1);
            BlueGhost.setTexture(BlueGTexture1);
            PinkGhost.setTexture(PinkGTexture1);


            PacMan.setPosition(sf::Vector2f(253.607, 325));

            RedGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            BlueGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            OrangeGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            PinkGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            CurrentRedDir = "a";
            CurrentBlueDir = "a";
            CurrentPinkDir = "a";
            CurrentOrangeDir = "a";

            GameStateTimer = -1;

        }



        //if(PacDead == true){
        if(false) {

            cout<<"reset"<<endl;

            PowerUpEaten = 0;
            dotsEaten = 0;
            PacManX = 0;
            PacManY = 0;
            RedX = 0;
            RedY = 0;
            OrangeX = 0;
            OrangeY = 0;
            BlueX = 0;
            BlueY = 0;
            PinkX = 0;
            PinkY = 0;
            PacLives --;

            PinkDead = false;
            PinkScared = false;
            PinkScatter = true;

            OrangeDead = false;
            OrangeScared = false;
            OrangeScatter = true;

            BlueDead = false;
            BlueScared = false;
            BlueScatter = true;

            RedScared = false;
            RedDead = false;
            RedScatter = true;

            GameState = "Scatter";

            RedGhost.setTexture(RedGTexture1);
            OrangeGhost.setTexture(OrangeGTexture1);
            BlueGhost.setTexture(BlueGTexture1);
            PinkGhost.setTexture(PinkGTexture1);


            PacMan.setPosition(sf::Vector2f(253.607, 325));

            RedGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            BlueGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            OrangeGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            PinkGhost.setPosition(sf::Vector2f((18.78571429*13)+(18.78571429/2), (18.61290323*15)+(18.61290323/2)));

            CurrentRedDir = "a";
            CurrentBlueDir = "a";
            CurrentPinkDir = "a";
            CurrentOrangeDir = "a";

            GameStateTimer = -1;

            /*
                dotplace = 0;
                for(int i = 0; i<31; i++) {
            for(int j = 0; j<28; j++) {

            if(GameMatrix[i][j] == 0) {
                Dot[dotplace].setPosition(sf::Vector2f(18.78571429*j+(18.78571429/2), 18.61290323*i+(18.61290323/2)));
                dotplace++;
            }
            }}
            */


        }


        if(PacLives == 0) {



        }



        scoreUpdate(HsDis, scoreDis, score, highscore, scoreShow, HSString);
        PowerPelletAni(PowerUp, Pwr_ani_frame, glowTimer);









        PauseTimer++;


        if(GamePaused == false && InMenu  == false) {

            glowTimer++;
            powerUpTimer++;

            if(GhostScared == false) {
                GameStateTimer++;
            }

            PacMan.move(PacManX,PacManY);
            RedGhost.move(RedX, RedY);
            OrangeGhost.move(OrangeX, OrangeY);
            BlueGhost.move(BlueX, BlueY);
            PinkGhost.move(PinkX, PinkY);
        }


        window.clear();
        window.setView(view);


        if(InMenu == false) {

            window.draw(Background);

            if(DEBUG == true) {
                int temp = 0;
                for(int i = 0; i<31; i++) {
                    for(int j = 0; j<28; j++) {
                        if(GameMatrix[i][j] != 1) {
                            window.draw(Tiles[temp]);
                        }
                        temp++;
                    }
                }
            }

            for(int i = 0; i<Dot.size(); i++) {

                window.draw(Dot[i]);
            }


            for(int i = 0; i<4; i++) {

                window.draw(PowerUp[i]);
            }


            window.draw(RedGhost);
            window.draw(OrangeGhost);
            window.draw(BlueGhost);
            window.draw(PinkGhost);


            window.draw(PacMan);


            window.draw(shape);
            window.draw(scoreDis);

            window.draw(Paused);

        }


        sf::View view = window.getView();
        window.display();
    }

    return 0;
}
