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


//startx,starty,boxsizex,boxsizex
#define Bry_Cherry 0,0,12,12
#define Bry_Strawberry 16,0,11,12
#define Bry_Peach 32,0,12,12
#define Bry_Apple 48,0,13,13
#define Bry_Lime 65,0,11,12
#define Bry_Spear 80,1,11,11
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

#define GhostRight1 0,0,28,28
#define GhostRight2 32,0,28,28
#define GhostLeft1 64,0,28,28
#define GhostLeft2 96,0,28,28
#define GhostUp1 128,0,28,28
#define GhostUp2 160,0,28,28
#define GhostDown1 192,0,28,28
#define GhostDown2 224,0,28,28




// Note to self use Delta Time for movement don't use set frame limit

//https://www.codesdope.com/blog/article/backtracking-to-solve-a-rat-in-a-maze-c-java-pytho/
//https://www.youtube.com/watch?v=ataGotQ7ir8


const bool DEBUG = false;


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


        /*
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
        */



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
        readFile >> highscore;
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

    //cout<<Berrytimer<<" ";
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

        //   if(GhostScared == true && GhostDead == false)
        // Ghost.setTexture(textureOrig);
    }

    if(powerUpTimer == 480 || powerUpTimer == 540) {

        if(GhostScared == true && GhostDead == false)
            Ghost.setTexture(textureWhite);
    }


    if(powerUpTimer > 600 && GhostDead == false && GhostScared == true) {

        return true;

    }


    return false;
}


void PlaceLives(std::vector<sf::Sprite> &PacLife) {

    int temp;

    for(int i = 0; i<PacLife.size(); i++) {

        temp = 400 + i*50;

        PacLife[i].setOrigin(15,15);
        PacLife[i].setPosition(temp,600);

    }
}




int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(522, 620), "Pac Man", sf::Style::Default,settings);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));

    sf::Font font;
    font.loadFromFile("Assets/Other/Arial.ttf");


    sf::Text GameDone("Loading...", font);
    GameDone.setCharacterSize(30);
    GameDone.setStyle(sf::Text::Bold);
    GameDone.setFillColor(sf::Color::Red);
    GameDone.setPosition(182, 387);

    window.draw(GameDone);
    window.display();



    srand (time(NULL));



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
    int pacTimer = 0;


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
    bool BlueFail = false;



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

    int Track = 1;
    bool InMenu = true;
    bool GamePaused = false;
    bool InSettings = false;
    int PauseTimer = 0;
    int lives = 2;
    int Berrytimer = 0;
    bool GameOver = false;
    int powerUpTimer = 0;
    bool GhostScared = false;
    bool Music = false;
    bool Sound_Ef = false;
    bool Master_Vol = true;
    int TitlePacTimer = 0;
    int Level = 0;
    bool freeLife = true;



    int gameoverTimer = 0;
    int death_ani_Timer = 0;

    // Must be less than 18
    const int DeadSpeed = 4.5;
    const double GhostSpeed = 1.5;



    int place = 0;
    int dotplace = 0;
    int PowerUpplace = 0;
    bool TileChange = false;
    bool MenuOnce = true;


    int RedGhostFeetTimer = 0;
    int BlueGhostFeetTimer = 0;
    int OrangeGhostFeetTimer = 0;
    int PinkGhostFeetTimer = 0;



    string GameState = "Game";


    string Help_Text = "\t\t\t\t\t\t\t\t HELP \n \n \nMove is Arrow keys \nIf you eat all the dots on the board more will spawn. \nIf a ghost hits you and is not Blue, YOU. WILL. DIE! \nTo make a ghost blue you must eat a power pellet,\nthere are 4 accros the map.\nYou Have 3 lives,\nif you beat the High score You get a free life.\n\n\t\tBy. Nicholas Parise";
    string Settings_Text = "Master Audio: \n\n\n Music: \n\n\n Sound Effects: \n\n\n\n Music Track:";
    string scoreShow;
    string HSString;

    string Setting1, Setting2, Setting3, Setting4;




    int FileLine = 0;
    string editstring;
    char escape = '1';
    int interval = 0;

    ifstream readFile;
    readFile.open("Assets/Other/Settings.txt");

    if(readFile.is_open()) {

        while(!readFile.eof()) {

            escape = '1';
            interval = 0;

            readFile >> editstring;

            while(escape != ':') {

                escape = editstring[interval];
                interval++;
            }

            if(FileLine == 0) {

                if(editstring[interval] == 't') {

                    Master_Vol = true;
                } else {

                    Master_Vol = false;
                }
            }

            if(FileLine == 1) {

                if(editstring[interval] == 't') {

                    Music = true;
                } else {

                    Music = false;
                }
            }
            if(FileLine == 2) {

                if(editstring[interval] == 't') {

                    Sound_Ef = true;
                } else {

                    Sound_Ef = false;
                }
            }
            if(FileLine == 3) {

                if(editstring[interval] == '1') {

                    Track = 1;

                } else if(editstring[interval] == '2') {

                    Track = 2;

                } else if(editstring[interval] == '3') {

                    Track = 3;
                }
            }

            if(FileLine == 3) {
                break;
            }


            FileLine++;
        }

    }



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

            Orange_solution[i,j].push_back(0);

            Blue_solution[i,j].push_back(0);

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
    image.loadFromFile("Assets/Sprite/PacMan_background.png");

    sf::Texture MapTexture;
    MapTexture.loadFromImage(image);

    sf::Sprite Background;
    Background.setTexture(MapTexture);
    Background.setPosition(sf::Vector2f(0, 0));


    sf::Texture PacTexture1;
    PacTexture1.loadFromFile("Assets/Sprite/PacMan_open.png");

    sf::Texture PacTexture2;
    PacTexture2.loadFromFile("Assets/Sprite/PacMan_closed.png");

    sf::Texture RedGTexture1;
    RedGTexture1.loadFromFile("Assets/Sprite/RedGhostRight.png");

    sf::Texture OrangeGTexture1;
    OrangeGTexture1.loadFromFile("Assets/Sprite/OrangeGhostRight.png");

    sf::Texture BlueGTexture1;
    BlueGTexture1.loadFromFile("Assets/Sprite/BlueGhostRight.png");

    sf::Texture PinkGTexture1;
    PinkGTexture1.loadFromFile("Assets/Sprite/PinkGhostRight.png");


    sf::Texture ScaredGhostTexture1;
    ScaredGhostTexture1.loadFromFile("Assets/Sprite/ScaredGhost1.png");

    sf::Texture ScaredGhostTexture2;
    ScaredGhostTexture2.loadFromFile("Assets/Sprite/ScaredGhost2.png");


    sf::Texture ScaredGhostWhiteTexture1;
    ScaredGhostWhiteTexture1.loadFromFile("Assets/Sprite/ScaredGhostWhite1.png");

    sf::Texture ScaredGhostWhiteTexture2;
    ScaredGhostWhiteTexture2.loadFromFile("Assets/Sprite/ScaredGhostWhite2.png");



    sf::Texture DeadGhostTexture;
    DeadGhostTexture.loadFromFile("Assets/Sprite/eyes.png");

    sf::Texture PauseTexture;
    PauseTexture.loadFromFile("Assets/Sprite/pause.png");



    sf::Texture texture9;
    texture9.loadFromFile("Assets/Other/PacMan-Start.png");

    sf::Texture texture10;
    texture10.loadFromFile("Assets/Sprite/Berry_Sprite_Sheet.png");




    sf::Image RedSheetimage;
    RedSheetimage.loadFromFile("Assets/Sprite/RedGhostSpriteSheet.png");


    sf::Texture RedGhostDown1;
    RedGhostDown1.loadFromImage(RedSheetimage, sf::IntRect(GhostDown1));

    sf::Texture RedGhostDown2;
    RedGhostDown2.loadFromImage(RedSheetimage, sf::IntRect(GhostDown2));


    sf::Texture RedGhostLeft1;
    RedGhostLeft1.loadFromImage(RedSheetimage, sf::IntRect(GhostLeft1));

    sf::Texture RedGhostLeft2;
    RedGhostLeft2.loadFromImage(RedSheetimage, sf::IntRect(GhostLeft2));

    sf::Texture RedGhostRight1;
    RedGhostRight1.loadFromImage(RedSheetimage, sf::IntRect(GhostRight1));

    sf::Texture RedGhostRight2;
    RedGhostRight2.loadFromImage(RedSheetimage, sf::IntRect(GhostRight2));

    sf::Texture RedGhostUp1;
    RedGhostUp1.loadFromImage(RedSheetimage, sf::IntRect(GhostUp1));

    sf::Texture RedGhostUp2;
    RedGhostUp2.loadFromImage(RedSheetimage, sf::IntRect(GhostUp2));



    // textureRedSheet.loadFromImage(image);
    sf::Texture textureRedSheet;
    textureRedSheet.loadFromFile("Assets/Sprite/RedGhostSpriteSheet.png");

///////

    sf::Image OrangeSheetimage;
    OrangeSheetimage.loadFromFile("Assets/Sprite/OrangeGhostSpriteSheet.png");


    sf::Texture OrangeGhostDown1;
    OrangeGhostDown1.loadFromImage(OrangeSheetimage, sf::IntRect(GhostDown1));

    sf::Texture OrangeGhostDown2;
    OrangeGhostDown2.loadFromImage(OrangeSheetimage, sf::IntRect(GhostDown2));


    sf::Texture OrangeGhostLeft1;
    OrangeGhostLeft1.loadFromImage(OrangeSheetimage, sf::IntRect(GhostLeft1));

    sf::Texture OrangeGhostLeft2;
    OrangeGhostLeft2.loadFromImage(OrangeSheetimage, sf::IntRect(GhostLeft2));

    sf::Texture OrangeGhostRight1;
    OrangeGhostRight1.loadFromImage(OrangeSheetimage, sf::IntRect(GhostRight1));

    sf::Texture OrangeGhostRight2;
    OrangeGhostRight2.loadFromImage(OrangeSheetimage, sf::IntRect(GhostRight2));

    sf::Texture OrangeGhostUp1;
    OrangeGhostUp1.loadFromImage(OrangeSheetimage, sf::IntRect(GhostUp1));

    sf::Texture OrangeGhostUp2;
    OrangeGhostUp2.loadFromImage(OrangeSheetimage, sf::IntRect(GhostUp2));


////////

    sf::Image BlueSheetimage;
    BlueSheetimage.loadFromFile("Assets/Sprite/BlueGhostSpriteSheet.png");


    sf::Texture BlueGhostDown1;
    BlueGhostDown1.loadFromImage(BlueSheetimage, sf::IntRect(GhostDown1));

    sf::Texture BlueGhostDown2;
    BlueGhostDown2.loadFromImage(BlueSheetimage, sf::IntRect(GhostDown2));


    sf::Texture BlueGhostLeft1;
    BlueGhostLeft1.loadFromImage(BlueSheetimage, sf::IntRect(GhostLeft1));

    sf::Texture BlueGhostLeft2;
    BlueGhostLeft2.loadFromImage(BlueSheetimage, sf::IntRect(GhostLeft2));

    sf::Texture BlueGhostRight1;
    BlueGhostRight1.loadFromImage(BlueSheetimage, sf::IntRect(GhostRight1));

    sf::Texture BlueGhostRight2;
    BlueGhostRight2.loadFromImage(BlueSheetimage, sf::IntRect(GhostRight2));

    sf::Texture BlueGhostUp1;
    BlueGhostUp1.loadFromImage(BlueSheetimage, sf::IntRect(GhostUp1));

    sf::Texture BlueGhostUp2;
    BlueGhostUp2.loadFromImage(BlueSheetimage, sf::IntRect(GhostUp2));

    /////
    sf::Image PinkSheetimage;
    PinkSheetimage.loadFromFile("Assets/Sprite/PinkGhostSpriteSheet.png");


    sf::Texture PinkGhostDown1;
    PinkGhostDown1.loadFromImage(PinkSheetimage, sf::IntRect(GhostDown1));

    sf::Texture PinkGhostDown2;
    PinkGhostDown2.loadFromImage(PinkSheetimage, sf::IntRect(GhostDown2));


    sf::Texture PinkGhostLeft1;
    PinkGhostLeft1.loadFromImage(PinkSheetimage, sf::IntRect(GhostLeft1));

    sf::Texture PinkGhostLeft2;
    PinkGhostLeft2.loadFromImage(PinkSheetimage, sf::IntRect(GhostLeft2));

    sf::Texture PinkGhostRight1;
    PinkGhostRight1.loadFromImage(PinkSheetimage, sf::IntRect(GhostRight1));

    sf::Texture PinkGhostRight2;
    PinkGhostRight2.loadFromImage(PinkSheetimage, sf::IntRect(GhostRight2));

    sf::Texture PinkGhostUp1;
    PinkGhostUp1.loadFromImage(PinkSheetimage, sf::IntRect(GhostUp1));

    sf::Texture PinkGhostUp2;
    PinkGhostUp2.loadFromImage(PinkSheetimage, sf::IntRect(GhostUp2));
    //////


    sf::Image EyeSheetimage;
    EyeSheetimage.loadFromFile("Assets/Sprite/EyeSpriteSheet.png");


    sf::Texture EyeDown;
    EyeDown.loadFromImage(EyeSheetimage, sf::IntRect(GhostDown1));

    sf::Texture EyeLeft;
    EyeLeft.loadFromImage(EyeSheetimage, sf::IntRect(GhostLeft1));

    sf::Texture EyeRight;
    EyeRight.loadFromImage(EyeSheetimage, sf::IntRect(GhostRight1));

    sf::Texture EyetUp;
    EyetUp.loadFromImage(EyeSheetimage, sf::IntRect(GhostUp1));


    //////////


    sf::Texture texture11;
    texture11.loadFromFile("Assets/Other/Solid_black.png");

    sf::Texture texture12;
    texture12.loadFromFile("Assets/Sprite/Pac-Death-SpriteSheet.png");

    sf::Texture texture13;
    texture13.loadFromFile("Assets/Sprite/eyes.png");

    sf::Texture texture14;
    texture14.loadFromFile("Assets/Sprite/pause.png");

    sf::Texture texture15;
    texture15.loadFromFile("Assets/Buttons/Settings_1.png");

    sf::Texture texture16;
    texture16.loadFromFile("Assets/Buttons/Settings_2.png");

    sf::Texture texture17;
    texture17.loadFromFile("Assets/Buttons/Return_1.png");

    sf::Texture texture18;
    texture18.loadFromFile("Assets/Buttons/Return_2.png");

    sf::Texture texture19;
    texture19.loadFromFile("Assets/Buttons/Help_1.png");

    sf::Texture texture20;
    texture20.loadFromFile("Assets/Buttons/Help_2.png");

    sf::Texture texture21;
    texture21.loadFromFile("Assets/Buttons/Yes_1.png");

    sf::Texture texture22;
    texture22.loadFromFile("Assets/Buttons/Yes_2.png");

    sf::Texture texture23;
    texture23.loadFromFile("Assets/Buttons/No_1.png");

    sf::Texture texture24;
    texture24.loadFromFile("Assets/Buttons/No_2.png");

    sf::Texture texture25;
    texture25.loadFromFile("Assets/Buttons/1_1.png");

    sf::Texture texture26;
    texture26.loadFromFile("Assets/Buttons/1_2.png");

    sf::Texture texture27;
    texture27.loadFromFile("Assets/Buttons/2_1.png");

    sf::Texture texture28;
    texture28.loadFromFile("Assets/Buttons/2_2.png");

    sf::Texture texture29;
    texture29.loadFromFile("Assets/Buttons/3_1.png");

    sf::Texture texture30;
    texture30.loadFromFile("Assets/Buttons/3_2.png");


    sf::SoundBuffer sound1;
    sound1.loadFromFile("Assets/Audio/Music/Pizza_Theme.wav");

    sf::SoundBuffer sound2;
    sound2.loadFromFile("Assets/Audio/Music/Wii_Menu2.wav");

    sf::SoundBuffer sound13;
    sound13.loadFromFile("Assets/Audio/Music/SubwooferLullaby.ogg");

    sf::SoundBuffer sound14;
    sound14.loadFromFile("Assets/Audio/Music/Sweden.ogg");



    sf::SoundBuffer sound3;
    sound3.loadFromFile("Assets/Audio/Effect/Mac_Startup.wav");

    sf::SoundBuffer sound4;
    sound4.loadFromFile("Assets/Audio/Effect/XP_Dots.wav");

    sf::SoundBuffer sound5;
    sound5.loadFromFile("Assets/Audio/Effect/XP_Start.wav");

    sf::SoundBuffer sound6;
    sound6.loadFromFile("Assets/Audio/Effect/XP_Teleport.wav");

    sf::SoundBuffer sound7;
    sound7.loadFromFile("Assets/Audio/Effect/XP_End.wav");

    sf::SoundBuffer sound8;
    sound8.loadFromFile("Assets/Audio/Effect/Click_Button.wav");

    sf::SoundBuffer sound9;
    sound9.loadFromFile("Assets/Audio/Effect/Select_Button.wav");

    sf::SoundBuffer sound10;
    sound10.loadFromFile("Assets/Audio/Effect/Death.wav");

    sf::SoundBuffer sound11;
    sound11.loadFromFile("Assets/Audio/Effect/PowerUp.wav");

    sf::SoundBuffer sound12;
    sound12.loadFromFile("Assets/Audio/Effect/XP_Yay.wav");

    sf::SoundBuffer sound15;
    sound15.loadFromFile("Assets/Audio/Effect/Fortnite_Clap.wav");

/////

//music
    sf::Sound BackG_Pizza;
    BackG_Pizza.setBuffer(sound1);

    sf::Sound BackG_Subwooder;
    BackG_Subwooder.setBuffer(sound13);

    sf::Sound BackG_Sweden;
    BackG_Sweden.setBuffer(sound14);

//sfx
    sf::Sound BackG_Wii;
    BackG_Wii.setBuffer(sound2);

    sf::Sound Mac_start;
    Mac_start.setBuffer(sound3);

    sf::Sound XP_Tele;
    XP_Tele.setBuffer(sound4);

    sf::Sound XP_start;
    XP_start.setBuffer(sound5);

    sf::Sound Dot_Chomp;
    Dot_Chomp.setBuffer(sound6);

    sf::Sound XP_End;
    XP_End.setBuffer(sound7);

    sf::Sound Button_click;
    Button_click.setBuffer(sound8);

    sf::Sound Button_select;
    Button_select.setBuffer(sound9);

    sf::Sound Dead;
    Dead.setBuffer(sound10);

    sf::Sound PowerSound;
    PowerSound.setBuffer(sound11);

    sf::Sound Yay;
    Yay.setBuffer(sound12);

    sf::Sound Fortnite_Clap;
    Fortnite_Clap.setBuffer(sound15);

    if(Music == true) {
        BackG_Wii.play();
    }

    BackG_Wii.setLoop(true);
    BackG_Pizza.setLoop(true);
    BackG_Subwooder.setLoop(true);
    BackG_Sweden.setLoop(true);

    BackG_Wii.setVolume(60.f);
    XP_Tele.setVolume(50.f);
    Mac_start.setVolume(50.f);
    BackG_Pizza.setVolume(10.f);
    PowerSound.setVolume(30.f);


////
    sf::Sprite PacMan;
    PacMan.setTexture(PacTexture2);
    PacMan.setOrigin(15,15);
    PacMan.setPosition(sf::Vector2f(253.607, 325));


    sf::Sprite RedGhost;
    RedGhost.setTexture(RedGhostUp1);
    RedGhost.setOrigin(15,15);
    RedGhost.setPosition(sf::Vector2f(18.78571429*RedRow+(18.78571429/2), 18.61290323*RedCol+(18.61290323/2)));

    sf::Sprite BlueGhost;
    BlueGhost.setTexture(BlueGhostUp1);
    BlueGhost.setOrigin(15,15);
    BlueGhost.setPosition(sf::Vector2f(18.78571429*BlueRow+(18.78571429/2), 18.61290323*BlueCol+(18.61290323/2)));

    sf::Sprite OrangeGhost;
    OrangeGhost.setTexture(OrangeGhostUp1);
    OrangeGhost.setOrigin(15,15);
    OrangeGhost.setPosition(sf::Vector2f(18.78571429*OrangeRow+(18.78571429/2), 18.61290323*OrangeCol+(18.61290323/2)));

    sf::Sprite PinkGhost;
    PinkGhost.setTexture(PinkGhostUp1);
    PinkGhost.setOrigin(15,15);
    PinkGhost.setPosition(sf::Vector2f(18.78571429*PinkRow+(18.78571429/2), 18.61290323*PinkCol+(18.61290323/2)));


    sf::Sprite Paused;
    Paused.setTexture(PauseTexture);
    Paused.setPosition(sf::Vector2f(0, 0));
    Paused.setOrigin(25,31);
    Paused.setScale(1.f,1.f);
    Paused.setPosition(1000,1000);



    sf::IntRect rectSourceSprite(Bry_Apple);
    sf::Sprite Berry(texture10,rectSourceSprite);
    Berry.setScale(2.f, 2.f);
    Berry.setPosition(1000,1000);


    sf::IntRect rectSourceSprite2(Pac_wack11);
    sf::Sprite PacDeath(texture12,rectSourceSprite2);
    PacDeath.setScale(2.5f, 2.5f);
    PacDeath.setPosition(1000,1000);


    sf::Sprite TitlePacMan;
    TitlePacMan.setTexture(PacTexture1);
    TitlePacMan.setOrigin(15,15);
    TitlePacMan.setRotation(-90);



    sf::Sprite StartImage;
    StartImage.setTexture(texture9);
    StartImage.setPosition(sf::Vector2f(266, 150));
    StartImage.setOrigin(225,51);

    sf::Sprite Menu;
    Menu.setTexture(texture11);
    Menu.setPosition(sf::Vector2f(0, 0));
    Menu.setOrigin(0,0);
    Menu.setScale(10.f, 10.f);

    sf::Sprite Setting;
    Setting.setTexture(texture15);
    Setting.setOrigin(312,47);
    Setting.setPosition(sf::Vector2f(522/2.f,388.f));
    Setting.setScale(.7f,.7f);

    sf::Sprite Return;
    Return.setTexture(texture17);
    Return.setOrigin(136,47);
    Return.setPosition(sf::Vector2f(1000,1000));
    Return.setScale(.6f,.6f);

    sf::Sprite Help;
    Help.setTexture(texture19);
    Help.setOrigin(111,47);
    Help.setPosition(sf::Vector2f(522/2.f,488.f));
    Help.setScale(.6f,.6f);

    sf::Sprite Track1;

    if(Track == 1) {
        Track1.setTexture(texture26);
    } else {
        Track1.setTexture(texture25);
    }
    Track1.setOrigin(65,47);
    Track1.setPosition(sf::Vector2f(1000,1000));
    Track1.setScale(.6f,.6f);

    sf::Sprite Track2;

    if(Track == 2) {
        Track2.setTexture(texture28);
    } else {
        Track2.setTexture(texture27);
    }
    Track2.setOrigin(65,47);
    Track2.setPosition(sf::Vector2f(1000,1000));
    Track2.setScale(.6f,.6f);

    sf::Sprite Track3;

    if(Track == 3) {
        Track3.setTexture(texture30);
    } else {
        Track3.setTexture(texture29);
    }
    Track3.setOrigin(65,47);
    Track3.setPosition(sf::Vector2f(1000,1000));
    Track3.setScale(.6f,.6f);

//----------------Sprite Vectors----------------

    std::vector<sf::Sprite> YorN(3, sf::Sprite(texture21));

    for(int i = 0; i<3; i++) {

        YorN[i].setScale(.7f,.7f);
        YorN[i].setPosition(1000,1000);
    }


    std::vector<sf::Sprite> PacLife(3, sf::Sprite(PacTexture1));
    PlaceLives(PacLife);



    //----------------Text----------------

    sf::Text NewHS("NEW HIGHSCORE!!", font);
    NewHS.setCharacterSize(30);
    NewHS.setStyle(sf::Text::Bold);
    NewHS.setFillColor(sf::Color::Red);
    NewHS.setOrigin(150,15);
    NewHS.setPosition(1000, 1000);


    sf::Text scoreDis("0", font);
    scoreDis.setCharacterSize(30);
    scoreDis.setStyle(sf::Text::Bold);
    scoreDis.setFillColor(sf::Color::White);
    scoreDis.setOrigin(15,15);
    scoreDis.setPosition(30,590);



    SaveHS(highscore,score,HSString,NewHS);


    sf::Text HsDis(HSString, font);
    HsDis.setCharacterSize(30);
    HsDis.setStyle(sf::Text::Bold);
    HsDis.setFillColor(sf::Color::White);
    HsDis.setOrigin(15,15);
    HsDis.setPosition(250, 590);



    sf::Text PreStart("Push Space To Start", font);
    PreStart.setCharacterSize(30);
    PreStart.setStyle(sf::Text::Bold);
    PreStart.setFillColor(sf::Color::White);
    PreStart.setOrigin(142,15);
    PreStart.setPosition(522/2, 620/2);


    GameDone.setOrigin(95,15);
    GameDone.setPosition(522/2, 322);
    GameDone.setString("GAME OVER");



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

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

                SaveHS(highscore,score,HSString,NewHS);
                window.close();

                return 69;
            }

            if (event.type == sf::Event::Resized) {
                view = getLetterboxView( view, event.size.width, event.size.height );
            }

            pixelPos = sf::Mouse::getPosition(window);
            worldPos = window.mapPixelToCoords(pixelPos);

            if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {
              //  cout<<worldPos.x<<" "<<worldPos.y<<endl;
                TempRowCol = ClossestTile(worldPos.x,worldPos.y, Tiles);
                //  cout<<endl;
                //  cout<<TempRowCol[0]<<" "<<TempRowCol[1]<<endl;
                //  return 0;
            }


            TitlePacMan.setPosition(worldPos.x,worldPos.y);



            ///////

            if(isSpriteHover(Setting.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) == true) {

                Setting.setTexture(texture16);

                if(Sound_Ef == true) {
                    Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {

                    InSettings = true;

                    if(Sound_Ef == true) {
                        Button_click.play();
                    }

                    Help.setPosition(1000, 1000);
                    Setting.setPosition(1000, 1000);
                    StartImage.setPosition(1000, 1000);
                    PreStart.setPosition(1000,1000);

                    Settings_text_sprite.setPosition(100, 10);
                    Track1.setPosition(sf::Vector2f(150.f,450.f));
                    Track2.setPosition(sf::Vector2f(250.f,450.f));
                    Track3.setPosition(sf::Vector2f(350.f,450.f));
                    Return.setPosition(sf::Vector2f(522/2.f,550.f));

                    for(int i = 0; i<3; i++) {
                        YorN[i].setPosition(400,i*90+10);
                    }
                }
            } else {

                Setting.setTexture(texture15);
            }


            if(isSpriteHover(Return.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) == true) {

                Return.setTexture(texture18);

                if(Sound_Ef == true) {
                    Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {

                    InSettings = false;

                    Return.setPosition(1000, 1000);
                    Help.setPosition(sf::Vector2f(522/2.f,488.f));
                    StartImage.setPosition(sf::Vector2f(266, 150));
                    PreStart.setPosition(522/2, 620/2);
                    Setting.setPosition(sf::Vector2f(522/2.f,388.f));
                    Help_text_sprite.setPosition(1000, 1000);
                    Settings_text_sprite.setPosition(1000, 1000);
                    Track1.setPosition(sf::Vector2f(1000,1000));
                    Track2.setPosition(sf::Vector2f(1000,1000));
                    Track3.setPosition(sf::Vector2f(1000,1000));

                    if(Sound_Ef == true) {
                        Button_click.play();
                    }

                    for(int i = 0; i<3; i++) {
                        YorN[i].setPosition(1000,1000);
                    }

                    ofstream writeFile("Assets/Other/Settings.txt");

                    if(Master_Vol == false) {
                        Setting1 = "Master:f\n";
                    }
                    if(Master_Vol == true) {
                        Setting1 =  "Master:t\n";
                    }

                    if(Music == false) {
                        Setting2 =  "Music:f\n";
                    }
                    if(Music == true) {
                        Setting2 =  "Music:t\n";
                    }

                    if(Sound_Ef == false) {
                        Setting3 =  "SoundEf:f\n";
                    }
                    if(Sound_Ef == true) {
                        Setting3 =  "SoundEf:t\n";
                    }

                    if(Track == 1) {
                        Setting4 =  "Track:1";
                    }
                    if(Track == 2) {
                        Setting4 =  "Track:2";
                    }
                    if(Track == 3) {
                        Setting4 =  "Track:3";
                    }

                    writeFile<<Setting1;
                    writeFile<<Setting2;
                    writeFile<<Setting3;
                    writeFile<<Setting4;
                    writeFile.close();


                }
            } else {

                Return.setTexture(texture17);
            }


            if(isSpriteHover(Help.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) == true) {

                Help.setTexture(texture20);
                if(Sound_Ef == true) {
                    Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {

                    InSettings = true;

                    if(Sound_Ef == true) {
                        Button_click.play();
                    }

                    Return.setPosition(sf::Vector2f(522/2.f,550.f));
                    Help.setPosition(1000, 1000);
                    Setting.setPosition(1000, 1000);
                    StartImage.setPosition(1000, 1000);
                    PreStart.setPosition(1000,1000);
                    Help_text_sprite.setPosition(0, 100);

                }
            } else {
                Help.setTexture(texture19);
            }

            if(isSpriteHover(YorN[0].getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) == true) {


                if(Master_Vol == false) {
                    YorN[0].setTexture(texture24);
                } else {
                    YorN[0].setTexture(texture22);
                }

                if(Sound_Ef == true) {
                    Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {

                    if(Sound_Ef == true) {
                        Button_click.play();
                    }

                    if(Master_Vol == true) {

                        Master_Vol = false;
                        Music = false;
                        Sound_Ef = false;

                        BackG_Wii.stop();
                        YorN[0].setTexture(texture23);
                        YorN[1].setTexture(texture23);
                        YorN[2].setTexture(texture23);

                    } else {
                        Master_Vol = true;
                        YorN[0].setTexture(texture21);
                    }
                }
            } else {

                if(Master_Vol == false) {
                    YorN[0].setTexture(texture23);
                } else {
                    YorN[0].setTexture(texture21);
                }
            }

            if(isSpriteHover(YorN[1].getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) == true) {

                if(Music == false) {
                    YorN[1].setTexture(texture24);
                } else {
                    YorN[1].setTexture(texture22);
                }
                if(Sound_Ef == true) {
                    Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {

                    if(Sound_Ef == true) {
                        Button_click.play();
                    }
                    if(Master_Vol == true && Music == false) {

                        YorN[1].setTexture(texture21);
                        Music = true;
                        BackG_Wii.play();

                    } else if(Master_Vol == true && Music == true) {

                        Music = false;
                        BackG_Wii.stop();
                        YorN[1].setTexture(texture23);
                    }
                }
            } else {

                if(Music == false) {
                    YorN[1].setTexture(texture23);
                } else {
                    YorN[1].setTexture(texture21);
                }
            }

            if(isSpriteHover(YorN[2].getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) == true) {
                if(Sound_Ef == true) {
                    Button_select.play();
                }

                if(Sound_Ef == false) {
                    YorN[2].setTexture(texture24);
                } else {
                    YorN[2].setTexture(texture22);
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {

                    if(Master_Vol == true) {
                        Button_click.play();
                    }
                    if(Master_Vol == true && Sound_Ef == false) {

                        YorN[2].setTexture(texture21);
                        Sound_Ef = true;

                    } else if(Master_Vol == true && Sound_Ef == true) {

                        Sound_Ef = false;
                        YorN[2].setTexture(texture23);
                    }
                }
            } else {
                if(Sound_Ef == false) {
                    YorN[2].setTexture(texture23);
                } else {
                    YorN[2].setTexture(texture21);
                }
            }

            if(isSpriteHover(Track1.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) == true) {

                Track1.setTexture(texture26);

                if(Sound_Ef == true) {
                    Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {

                    Track = 1;
                    Track2.setTexture(texture27);
                    Track3.setTexture(texture29);
                    if(Sound_Ef == true) {
                        Button_click.play();
                    }
                }
            } else {
                if(Track != 1) {
                    Track1.setTexture(texture25);
                }
            }

            if(isSpriteHover(Track2.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) == true) {

                Track2.setTexture(texture28);

                if(Sound_Ef == true) {
                    Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {

                    Track = 2;

                    Track1.setTexture(texture25);
                    Track3.setTexture(texture29);
                    if(Sound_Ef == true) {
                        Button_click.play();
                    }
                }
            } else {

                if(Track != 2) {
                    Track2.setTexture(texture27);
                }
            }


            if(isSpriteHover(Track3.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) == true) {

                Track3.setTexture(texture30);

                if(Sound_Ef == true) {
                    Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {

                    Track = 3;

                    Track1.setTexture(texture25);
                    Track2.setTexture(texture27);
                    if(Sound_Ef == true) {
                        Button_click.play();
                    }
                }
            } else {

                if(Track != 3) {
                    Track3.setTexture(texture29);
                }
            }
        }



        //////Path Finding


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

                               // shape.setPosition(sf::Vector2f(18.78571429*solutionRow+(PacBlueDistanceX*PacBlueDistanceX)+(18.78571429/2), 18.61290323*solutionCol+(PacBlueDistanceY*PacBlueDistanceY)+(18.61290323/2)));
                            } else {
                                if(!solvemaze(BlueCol,BlueRow,solutionRow-PacBlueDistanceX,solutionCol+PacBlueDistanceY, CurrentBlueDir, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix)) {
                                    BlueFail = true;
                                }

                             //   shape.setPosition(sf::Vector2f(18.78571429*solutionRow-(PacBlueDistanceX*PacBlueDistanceX)+(18.78571429/2), 18.61290323*solutionCol-(PacBlueDistanceY*PacBlueDistanceY)+(18.61290323/2)));
                            }

                        } else {

                            if(RedCol >PacCol) {

                                if(!solvemaze(BlueCol,BlueRow,solutionRow+PacBlueDistanceX,solutionCol-PacBlueDistanceY, CurrentBlueDir, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix)) {
                                    BlueFail = true;
                                }

                               // shape.setPosition(sf::Vector2f(18.78571429*solutionRow+(PacBlueDistanceX*PacBlueDistanceX)+(18.78571429/2), 18.61290323*solutionCol-(PacBlueDistanceY*PacBlueDistanceY)+(18.61290323/2)));

                            } else {
                                if(!solvemaze(BlueCol,BlueRow,solutionRow-PacBlueDistanceX,solutionCol-PacBlueDistanceY, CurrentBlueDir, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix)) {
                                    BlueFail = true;
                                }
                            //    shape.setPosition(sf::Vector2f(18.78571429*solutionRow-(PacBlueDistanceX*PacBlueDistanceX)+(18.78571429/2), 18.61290323*solutionCol-(PacBlueDistanceY*PacBlueDistanceY)+(18.61290323/2)));
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

            if(DEBUG == true) {

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


        }
        //////////////



        PacManAvallibleDir = WallTest(GameMatrix, PacRow, PacCol, CurrentPacDir,stopPacMan);

        //  PacCloseToCenter = CenterOfTile(PacRow, PacCol, CurrentPacDir, PacMan,stopPacMan);







        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

            if(GamePaused == false && InMenu == false && PauseTimer >10) {

                GamePaused = true;
                Paused.setPosition(261,288);
                BackG_Pizza.pause();
                BackG_Subwooder.pause();
                BackG_Sweden.pause();
            }

            else if(GamePaused == true && InMenu == false && PauseTimer > 50) {

                PauseTimer = 0;
                GamePaused = false;
                Paused.setPosition(1000,1000);

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


            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& InMenu == true && InSettings == false) {

            cout<<"adsa"<<endl;


            if(Sound_Ef == true) {
                Mac_start.play();
            }


            MenuOnce = true;

            GameOver = false;
            InMenu = false;
            gameoverTimer = 0;

            freeLife = true;
            PacLives = 3;
            Level = 0;

            Berrytimer = 0;

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

            //RedGhost.setTexture(RedGTexture1);

            RedGhost.setTexture(RedGhostUp1);
            OrangeGhost.setTexture(OrangeGhostUp1);
            BlueGhost.setTexture(BlueGhostLeft1);
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


            PlaceLives(PacLife);



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



        if(PacMan.getPosition().x<10) {

            PacMan.setPosition(522,269.887096835);
            if(Sound_Ef == true) {
                XP_Tele.play();
            }
        }

        if(PacMan.getPosition().x>522) {

            PacMan.setPosition(10,269.887096835);
            if(Sound_Ef == true) {
                XP_Tele.play();
            }
        }


        if(RedGhost.getPosition().x<20 && CurrentRedDir == "Left") {

            RedGhost.setPosition(522,269.887096835);
            if(Sound_Ef == true) {
                XP_Tele.play();
            }
        }

        if(RedGhost.getPosition().x>512 && CurrentRedDir == "Right") {

            RedGhost.setPosition(10,269.887096835);
            if(Sound_Ef == true) {
                XP_Tele.play();
            }
        }


        if(OrangeGhost.getPosition().x<20 && CurrentOrangeDir == "Left") {

            OrangeGhost.setPosition(522,269.887096835);
            if(Sound_Ef == true) {
                XP_Tele.play();
            }
        }

        if(OrangeGhost.getPosition().x>512 && CurrentOrangeDir == "Right") {

            OrangeGhost.setPosition(10,269.887096835);
            if(Sound_Ef == true) {
                XP_Tele.play();
            }
        }


        if(BlueGhost.getPosition().x<20 && CurrentBlueDir == "Left") {

            BlueGhost.setPosition(522,269.887096835);
            if(Sound_Ef == true) {
                XP_Tele.play();
            }
        }

        if(BlueGhost.getPosition().x>512 && CurrentBlueDir == "Right") {

            BlueGhost.setPosition(10,269.887096835);
            if(Sound_Ef == true) {
                XP_Tele.play();
            }
        }


        if(PinkGhost.getPosition().x<20 && CurrentPinkDir == "Left") {

            PinkGhost.setPosition(522,269.887096835);
            if(Sound_Ef == true) {
                XP_Tele.play();
            }
        }

        if(PinkGhost.getPosition().x>512 && CurrentPinkDir == "Right") {

            PinkGhost.setPosition(10,269.887096835);
            if(Sound_Ef == true) {
                XP_Tele.play();
            }
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
            // RedGhost.setTexture(RedGTexture1);

            RedGhost.setTexture(RedGhostUp1);
        }

        if(OutOfTheCloset(OrangeRow, OrangeCol, CurrentOrangeDir, Orange_PathCol, Orange_PathRow, GhostHomeRow, GhostHomeCol, OrangeDead)) {

            OrangeScared = false;
            OrangeDead = false;
            OrangeGhost.setTexture(OrangeGhostUp1);
        }

        if(OutOfTheCloset(BlueRow, BlueCol, CurrentBlueDir, Blue_PathCol, Blue_PathRow, GhostHomeRow, GhostHomeCol, BlueDead)) {

            BlueScared = false;
            BlueDead = false;
            BlueGhost.setTexture(BlueGhostUp1);
        }

        if(OutOfTheCloset(PinkRow, PinkCol, CurrentPinkDir, Pink_PathCol, Pink_PathRow, GhostHomeRow, GhostHomeCol, PinkDead)) {

            PinkScared = false;
            PinkDead = false;
            PinkGhost.setTexture(PinkGhostUp1);
        }






//Red
        if((RedRow+1) == Red_PathCol[1] && RedCol == Red_PathRow[1] && CurrentRedDir != "Left") {

            if(RedDead == false) {
                RedX = GhostSpeed;

            } else {
                RedX = DeadSpeed;
            }

            RedY = 0;
            CurrentRedDir = "Right";

            //cout<<"Right"<<endl;
            //  RedGhost.setPosition((18.78571429*(RedRow+1))+(18.78571429/2),RedGhost.getPosition().y);

        } else  if((RedRow-1) == Red_PathCol[1] && RedCol == Red_PathRow[1] && CurrentRedDir != "Right") {

            if(RedDead == false) {
                RedX = GhostSpeed*-1;

            } else {
                RedX = DeadSpeed*-1;
            }


            RedY = 0;
            CurrentRedDir = "Left";
            //cout<<"Left"<<endl;
            //  RedGhost.setPosition((18.78571429*(RedRow-1))+(18.78571429/2),RedGhost.getPosition().y);

        } else if((RedCol-1) == Red_PathRow[1] && RedRow == Red_PathCol[1] && CurrentRedDir != "Down") {

            RedX = 0;

            if(RedDead == false) {

                RedY = GhostSpeed*-1;
            } else {
                RedY = DeadSpeed*-1;
            }

            CurrentRedDir = "Up";
            //cout<<"Up"<<endl;
            //   RedGhost.setPosition(RedGhost.getPosition().x,(18.61290323*(RedCol-1))+(18.61290323/2));

        } else if((RedCol+1) == Red_PathRow[1] && RedRow == Red_PathCol[1] && CurrentRedDir != "Up") {

            RedX = 0;
            if(RedDead == false) {

                RedY = GhostSpeed;

            } else {
                RedY = DeadSpeed;
            }

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

            if(OrangeDead == false) {
                OrangeX = GhostSpeed;


                if(OrangeScared == false) {
                    OrangeGhost.setTexture(OrangeGhostRight1);
                }

            } else {
                OrangeX = DeadSpeed;
            }


            OrangeY = 0;
            CurrentOrangeDir = "Right";
            //cout<<"Right"<<endl;

            //  OrangeGhost.setPosition((18.78571429*(OrangeRow+1))+(18.78571429/2),OrangeGhost.getPosition().y);

        } else  if((OrangeRow-1) == Orange_PathCol[1] && OrangeCol == Orange_PathRow[1] && CurrentOrangeDir != "Right") {

            if(OrangeDead == false) {
                OrangeX = GhostSpeed*-1;

                if(OrangeScared == false) {
                    OrangeGhost.setTexture(OrangeGhostLeft1);
                }


            } else {
                OrangeX = DeadSpeed*-1;
            }

            OrangeY = 0;
            CurrentOrangeDir = "Left";
            //cout<<"Left"<<endl;
            //  OrangeGhost.setPosition((18.78571429*(OrangeRow-1))+(18.78571429/2),OrangeGhost.getPosition().y);

        } else if((OrangeCol-1) == Orange_PathRow[1] && OrangeRow == Orange_PathCol[1] && CurrentOrangeDir != "Down") {

            OrangeX = 0;

            if(OrangeDead == false) {
                OrangeY = GhostSpeed*-1;


                if(OrangeScared == false) {
                    OrangeGhost.setTexture(OrangeGhostUp1);
                }


            } else {
                OrangeY = DeadSpeed*-1;
            }


            CurrentOrangeDir = "Up";
            //cout<<"Up"<<endl;
            //   OrangeGhost.setPosition(OrangeGhost.getPosition().x,(18.61290323*(OrangeCol-1))+(18.61290323/2));

        } else if((OrangeCol+1) == Orange_PathRow[1] && OrangeRow == Orange_PathCol[1] && CurrentOrangeDir != "Up") {

            OrangeX = 0;

            if(OrangeDead == false) {
                OrangeY = GhostSpeed;

                if(OrangeScared == false) {
                    OrangeGhost.setTexture(OrangeGhostDown1);
                }


            } else {
                OrangeY = DeadSpeed;
            }

            CurrentOrangeDir = "Down";
            //cout<<"Down"<<endl;
            //  OrangeGhost.setPosition(OrangeGhost.getPosition().x,(18.61290323*(OrangeCol+1))+(18.61290323/2));
        }


//Blue
        if((BlueRow+1) == Blue_PathCol[1] && BlueCol == Blue_PathRow[1] && CurrentBlueDir != "Left") {

            if(BlueDead == false) {
                BlueX = GhostSpeed;

                if(BlueScared == false) {
                    BlueGhost.setTexture(BlueGhostRight1);
                }


            } else {
                BlueX = DeadSpeed;
            }

            BlueY = 0;
            CurrentBlueDir = "Right";
            //cout<<"Right"<<endl;

            //  BlueGhost.setPosition((18.78571429*(BlueRow+1))+(18.78571429/2),BlueGhost.getPosition().y);

        } else  if((BlueRow-1) == Blue_PathCol[1] && BlueCol == Blue_PathRow[1] && CurrentBlueDir != "Right") {

            if(BlueDead == false) {
                BlueX = GhostSpeed*-1;

                if(BlueScared == false) {
                    BlueGhost.setTexture(BlueGhostLeft1);
                }


            } else {
                BlueX = DeadSpeed*-1;
            }

            BlueY = 0;
            CurrentBlueDir = "Left";
            //cout<<"Left"<<endl;
            //  BlueGhost.setPosition((18.78571429*(BlueRow-1))+(18.78571429/2),BlueGhost.getPosition().y);

        } else if((BlueCol-1) == Blue_PathRow[1] && BlueRow == Blue_PathCol[1] && CurrentBlueDir != "Down") {

            BlueX = 0;
            if(BlueDead == false) {
                BlueY = GhostSpeed*-1;

                if(BlueScared == false) {
                    BlueGhost.setTexture(BlueGhostUp1);
                }


            } else {
                BlueY = DeadSpeed*-1;
            }

            CurrentBlueDir = "Up";
            //cout<<"Up"<<endl;
            //   BlueGhost.setPosition(BlueGhost.getPosition().x,(18.61290323*(BlueCol-1))+(18.61290323/2));

        } else if((BlueCol+1) == Blue_PathRow[1] && BlueRow == Blue_PathCol[1] && CurrentBlueDir != "Up") {

            BlueX = 0;

            if(BlueDead == false) {
                BlueY = GhostSpeed;

                if(BlueScared == false) {
                    BlueGhost.setTexture(BlueGhostDown1);
                }


            } else {
                BlueY = DeadSpeed;
            }

            CurrentBlueDir = "Down";
            //cout<<"Down"<<endl;
            //  BlueGhost.setPosition(BlueGhost.getPosition().x,(18.61290323*(BlueCol+1))+(18.61290323/2));
        }


//Pink
        if((PinkRow+1) == Pink_PathCol[Pink_PathPlace] && PinkCol == Pink_PathRow[Pink_PathPlace] && CurrentPinkDir != "Left") {

            if(PinkDead == false) {
                PinkX = GhostSpeed;

                if(PinkScared == false) {
                    PinkGhost.setTexture(PinkGhostRight1);
                }

            } else {
                PinkX = DeadSpeed;
            }

            PinkY = 0;
            CurrentPinkDir = "Right";
            //cout<<"Right"<<endl;

            //  PinkGhost.setPosition((18.78571429*(PinkRow+1))+(18.78571429/2),PinkGhost.getPosition().y);

        } else  if((PinkRow-1) == Pink_PathCol[Pink_PathPlace] && PinkCol == Pink_PathRow[Pink_PathPlace] && CurrentPinkDir != "Right") {

            if(PinkDead == false) {
                PinkX = GhostSpeed*-1;

                if(PinkScared == false) {
                    PinkGhost.setTexture(PinkGhostLeft1);
                }

            } else {
                PinkX = DeadSpeed*-1;
            }


            PinkY = 0;
            CurrentPinkDir = "Left";
            //cout<<"Left"<<endl;
            //  PinkGhost.setPosition((18.78571429*(PinkRow-1))+(18.78571429/2),PinkGhost.getPosition().y);

        } else if((PinkCol-1) == Pink_PathRow[Pink_PathPlace] && PinkRow == Pink_PathCol[Pink_PathPlace] && CurrentPinkDir != "Down") {

            PinkX = 0;
            if(PinkDead == false) {
                PinkY = GhostSpeed*-1;

                if(PinkScared == false) {
                    PinkGhost.setTexture(PinkGhostUp1);
                }

            } else {
                PinkY = DeadSpeed*-1;
            }

            CurrentPinkDir = "Up";
            //cout<<"Up"<<endl;
            //   PinkGhost.setPosition(PinkGhost.getPosition().x,(18.61290323*(PinkCol-1))+(18.61290323/2));

        } else if((PinkCol+1) == Pink_PathRow[Pink_PathPlace] && PinkRow == Pink_PathCol[Pink_PathPlace] && CurrentPinkDir != "Up") {

            PinkX = 0;

            if(PinkDead == false) {
                PinkY = GhostSpeed;

                if(PinkScared == false) {
                    PinkGhost.setTexture(PinkGhostDown1);
                }


            } else {
                PinkY = DeadSpeed;
            }

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

                if(Sound_Ef == true) {
                    Dot_Chomp.play();
                }
            }
        }


        for (int i = 0; i < PowerUp.size(); i++) {
            if(PacMan.getGlobalBounds().intersects(PowerUp[i].getGlobalBounds())) {
                PowerUp[i].setPosition(PowerUp[i].getPosition().x+1000,PowerUp[i].getPosition().y);


                if(Sound_Ef == true) {
                    PowerSound.play();
                }

                powerUpTimer = 0;

                GhostScared = true;

                PowerUpEaten ++;
                score +=25;

                GameState = "Chase";

                if(RedDead == false) {
                    RedScared = true;
                    RedGhost.setTexture(ScaredGhostTexture1);
                    ScareStart = true;
                    ScaredTimer = 0;
                    CurrentRedDir = "a";
                }

                if(OrangeDead == false) {
                    OrangeScared = true;
                    OrangeGhost.setTexture(ScaredGhostTexture1);
                    ScareStart = true;
                    ScaredTimer = 0;
                    CurrentOrangeDir = "a";
                }

                if(PinkDead == false) {
                    PinkScared = true;
                    PinkGhost.setTexture(ScaredGhostTexture1);
                    ScareStart = true;
                    ScaredTimer = 0;
                    CurrentPinkDir = "a";
                }

                if(BlueDead == false) {
                    BlueScared = true;
                    BlueGhost.setTexture(ScaredGhostTexture1);
                    ScareStart = true;
                    ScaredTimer = 0;
                    CurrentBlueDir = "a";
                }
            }
        }



        if(ScaredTimer > (60*8) && ScareStart == true) {

            ScareStart = false;

        } else {
            ScaredTimer++;
        }





        if(PowerStop(powerUpTimer, RedGhost, ScaredGhostTexture1, ScaredGhostWhiteTexture1, RedScared, RedDead) == true) {

            //RedGhost.setTexture(RedGTexture1);
            // RedGhost.setTexture(RedGhostUp1);
            RedScared = false;
            GhostScared = false;
        }
        if(PowerStop(powerUpTimer, OrangeGhost, ScaredGhostTexture1, ScaredGhostWhiteTexture1, OrangeScared, OrangeDead) == true) {

            // OrangeGhost.setTexture(OrangeGhostUp1);
            OrangeScared = false;
            GhostScared = false;
        }
        if(PowerStop(powerUpTimer, BlueGhost, ScaredGhostTexture1, ScaredGhostWhiteTexture1, BlueScared, BlueDead) == true) {

            //  BlueGhost.setTexture(BlueGhostUp1);
            BlueScared = false;
            GhostScared = false;
        }
        if(PowerStop(powerUpTimer, PinkGhost, ScaredGhostTexture1, ScaredGhostWhiteTexture1, PinkScared, PinkDead) == true) {

            //  PinkGhost.setTexture(PinkGhostUp1);
            PinkScared = false;
            GhostScared = false;
        }



        if(PacDead == false && DEBUG == false) {
            if(PacMan.getGlobalBounds().intersects(RedGhost.getGlobalBounds())) {

                if(RedDead == false) {
                    if(RedScared == true) {
                        score +=10;

                        if(Sound_Ef == true) {
                            Yay.play();
                        }

                        RedDead = true;
                        RedGhost.setTexture(DeadGhostTexture);
                    } else {

                        BackG_Pizza.pause();
                        BackG_Subwooder.pause();
                        BackG_Sweden.pause();

                        if(Sound_Ef == true) {
                            Dead.play();
                        }

                        PacDead = true;
                    }
                }
            }

            if(PacMan.getGlobalBounds().intersects(OrangeGhost.getGlobalBounds())) {

                if(OrangeDead == false) {
                    if(OrangeScared == true) {
                        score +=10;

                        if(Sound_Ef == true) {
                            Yay.play();
                        }

                        OrangeDead = true;
                        OrangeGhost.setTexture(DeadGhostTexture);
                    } else {

                        BackG_Pizza.pause();
                        BackG_Subwooder.pause();
                        BackG_Sweden.pause();

                        if(Sound_Ef == true) {
                            Dead.play();
                        }

                        PacDead = true;
                    }
                }
            }

            if(PacMan.getGlobalBounds().intersects(BlueGhost.getGlobalBounds())) {

                if(BlueDead == false) {
                    if(BlueScared == true) {
                        score +=10;

                        if(Sound_Ef == true) {
                            Yay.play();
                        }

                        BlueDead = true;
                        BlueGhost.setTexture(DeadGhostTexture);
                    } else {

                        BackG_Pizza.pause();
                        BackG_Subwooder.pause();
                        BackG_Sweden.pause();



                        if(Sound_Ef == true) {
                            Dead.play();
                        }

                        PacDead = true;
                    }
                }
            }

            if(PacMan.getGlobalBounds().intersects(PinkGhost.getGlobalBounds())) {

                if(PinkDead == false) {
                    if(PinkScared == true) {
                        score +=10;

                        if(Sound_Ef == true) {
                            Yay.play();
                        }

                        PinkDead = true;
                        PinkGhost.setTexture(DeadGhostTexture);
                    } else {
                        BackG_Pizza.pause();
                        BackG_Subwooder.pause();
                        BackG_Sweden.pause();

                        if(Sound_Ef == true) {
                            Dead.play();
                        }

                        PacDead = true;
                    }
                }
            }
        }

        if(PacMan.getGlobalBounds().intersects(Berry.getGlobalBounds())) {

            Berry.setPosition(1000,1000);
            score +=10;


            if(Sound_Ef == true) {
                Fortnite_Clap.play();
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








        if(freeLife == true && score>highscore) {

            freeLife = false;
            cout<<"aaaaaaaaaaaaaaaa"<<endl;
            PacLives++;

        }







        if(dotsEaten == 244 && PowerUpEaten==4) {

            cout<<"Next Level"<<endl;

            if(Sound_Ef == true) {
                Mac_start.play();
            }



            Level++;

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

            Berrytimer = 0;
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

            RedGhost.setTexture(RedGhostUp1);
            OrangeGhost.setTexture(OrangeGhostUp1);
            BlueGhost.setTexture(BlueGhostUp1);
            PinkGhost.setTexture(PinkGhostUp1);


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


        if(PacDeathAni(PacDeath, PacMan, death_ani_Timer)&& DEBUG == false) {

            PacDead = false;



            cout<<"reset"<<endl;

            PacDeath.setPosition(1000,1000);

            death_ani_Timer = 0;

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
            PacLife[PacLives].setPosition(1000,1000);

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

            RedGhost.setTexture(RedGhostUp1);
            OrangeGhost.setTexture(OrangeGhostUp1);
            BlueGhost.setTexture(BlueGhostUp1);
            PinkGhost.setTexture(PinkGhostUp1);


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


        }





        if(PacLives == 0 && DEBUG == false && MenuOnce == true) {
            //Game Over
            MenuOnce = false;

            BackG_Pizza.stop();

            BackG_Subwooder.stop();

            BackG_Sweden.stop();


            if(Sound_Ef == true) {
                XP_End.play();
            }


            SaveHS(highscore,score,HSString,NewHS);


            BackG_Pizza.stop();
            BackG_Subwooder.stop();
            BackG_Sweden.stop();


            InMenu = true;
            GameOver = true;
            InSettings = false;
        }



        scoreUpdate(HsDis, scoreDis, score, highscore, scoreShow, HSString);
        PowerPelletAni(PowerUp, Pwr_ani_frame, glowTimer);




        if(TitlePacTimer == 10) {

            TitlePacMan.setTexture(PacTexture2);

        } else if(TitlePacTimer == 20) {

            TitlePacMan.setTexture(PacTexture1);
            TitlePacTimer = 0;
        }


        if(pacTimer == 10) {

            PacMan.setTexture(PacTexture2);

        } else if(pacTimer == 20) {

            PacMan.setTexture(PacTexture1);
            pacTimer = 0;
        }


        BerryPlace(Berry, Berrytimer);



        if(GameOver == true) {

            if(gameoverTimer < 80) {
                gameoverTimer++;
            } else {
                GameOver = false;


                if(Music == true) {
                    BackG_Wii.play();
                }

            }
        }




        RedGhostFeetTimer+=2;
        BlueGhostFeetTimer+=2;
        OrangeGhostFeetTimer+=2;
        PinkGhostFeetTimer+=2;


        if(RedGhostFeetTimer==20) {
            RedGhostFeetTimer = 0;
        }
        if(OrangeGhostFeetTimer==20) {
            OrangeGhostFeetTimer = 0;
        }
        if(BlueGhostFeetTimer==20) {
            BlueGhostFeetTimer = 0;
        }
        if(PinkGhostFeetTimer==20) {
            PinkGhostFeetTimer = 0;
        }


        //////////////////


        if(RedScared == false) {

            if(RedX>0) {
                if(OrangeGhostFeetTimer<10) {
                    RedGhost.setTexture(RedGhostRight1);
                } else if(OrangeGhostFeetTimer>10) {
                    RedGhost.setTexture(RedGhostRight2);
                }
            } else if(RedX<0) {
                if(OrangeGhostFeetTimer<10) {
                    RedGhost.setTexture(RedGhostLeft1);
                } else if(OrangeGhostFeetTimer>10) {
                    RedGhost.setTexture(RedGhostLeft2);
                }
            } else {
                if(RedY>0) {
                    if(OrangeGhostFeetTimer<10) {
                        RedGhost.setTexture(RedGhostDown1);
                    } else if(OrangeGhostFeetTimer>10) {
                        RedGhost.setTexture(RedGhostDown2);
                    }
                } else if(RedY<0) {
                    if(OrangeGhostFeetTimer<10) {
                        RedGhost.setTexture(RedGhostUp1);
                    } else if(OrangeGhostFeetTimer>10) {
                        RedGhost.setTexture(RedGhostUp2);
                    }
                }
            }
        } else {

            if(RedDead == false) {

                if(powerUpTimer <480 || (powerUpTimer > 510 && powerUpTimer < 540) || powerUpTimer >570) {

                    if(OrangeGhostFeetTimer<10) {
                        RedGhost.setTexture(ScaredGhostTexture1);
                    } else if(OrangeGhostFeetTimer>10) {
                        RedGhost.setTexture(ScaredGhostTexture2);
                    }
                } else if((powerUpTimer > 480 && powerUpTimer < 510) || (powerUpTimer > 540&& powerUpTimer < 570)) {

                    if(OrangeGhostFeetTimer<10) {
                        RedGhost.setTexture(ScaredGhostWhiteTexture1);
                    } else if(OrangeGhostFeetTimer>10) {
                        RedGhost.setTexture(ScaredGhostWhiteTexture2);
                    }
                }
            } else {

                if(RedX>0) {
                    RedGhost.setTexture(EyeRight);
                } else if(RedX<0) {
                    RedGhost.setTexture(EyeLeft);
                } else if(RedY>0) {
                    RedGhost.setTexture(EyeDown);
                } else if(RedY<0) {
                    RedGhost.setTexture(EyetUp);
                }
            }
        }

        ////
        if(OrangeScared == false) {

            if(OrangeX>0) {
                if(OrangeGhostFeetTimer<10) {
                    OrangeGhost.setTexture(OrangeGhostRight1);
                } else if(OrangeGhostFeetTimer>10) {
                    OrangeGhost.setTexture(OrangeGhostRight2);
                }
            } else if(OrangeX<0) {
                if(OrangeGhostFeetTimer<10) {
                    OrangeGhost.setTexture(OrangeGhostLeft1);
                } else if(OrangeGhostFeetTimer>10) {
                    OrangeGhost.setTexture(OrangeGhostLeft2);
                }
            } else {
                if(OrangeY>0) {
                    if(OrangeGhostFeetTimer<10) {
                        OrangeGhost.setTexture(OrangeGhostDown1);
                    } else if(OrangeGhostFeetTimer>10) {
                        OrangeGhost.setTexture(OrangeGhostDown2);
                    }
                } else if(OrangeY<0) {
                    if(OrangeGhostFeetTimer<10) {
                        OrangeGhost.setTexture(OrangeGhostUp1);
                    } else if(OrangeGhostFeetTimer>10) {
                        OrangeGhost.setTexture(OrangeGhostUp2);
                    }
                }
            }
        } else {

            if(OrangeDead == false) {

                if(powerUpTimer <480 || (powerUpTimer > 510 && powerUpTimer < 540) || powerUpTimer >570) {

                    if(OrangeGhostFeetTimer<10) {
                        OrangeGhost.setTexture(ScaredGhostTexture1);
                    } else if(OrangeGhostFeetTimer>10) {
                        OrangeGhost.setTexture(ScaredGhostTexture2);
                    }
                } else if((powerUpTimer > 480 && powerUpTimer < 510) || (powerUpTimer > 540&& powerUpTimer < 570)) {

                    if(OrangeGhostFeetTimer<10) {
                        OrangeGhost.setTexture(ScaredGhostWhiteTexture1);
                    } else if(OrangeGhostFeetTimer>10) {
                        OrangeGhost.setTexture(ScaredGhostWhiteTexture2);
                    }
                }

            } else {
                if(OrangeX>0) {
                    OrangeGhost.setTexture(EyeRight);
                } else if(OrangeX<0) {
                    OrangeGhost.setTexture(EyeLeft);
                } else if(OrangeY>0) {
                    OrangeGhost.setTexture(EyeDown);
                } else if(OrangeY<0) {
                    OrangeGhost.setTexture(EyetUp);
                }
            }

        }

        ///////////
        if(PinkScared == false) {

            if(PinkX>0) {
                if(PinkGhostFeetTimer<10) {
                    PinkGhost.setTexture(PinkGhostRight1);
                } else if(PinkGhostFeetTimer>10) {
                    PinkGhost.setTexture(PinkGhostRight2);
                }
            } else if(PinkX<0) {
                if(PinkGhostFeetTimer<10) {
                    PinkGhost.setTexture(PinkGhostLeft1);
                } else if(PinkGhostFeetTimer>10) {
                    PinkGhost.setTexture(PinkGhostLeft2);
                }
            } else {
                if(PinkY>0) {
                    if(PinkGhostFeetTimer<10) {
                        PinkGhost.setTexture(PinkGhostDown1);
                    } else if(PinkGhostFeetTimer>10) {
                        PinkGhost.setTexture(PinkGhostDown2);
                    }
                } else if(PinkY<0) {
                    if(PinkGhostFeetTimer<10) {
                        PinkGhost.setTexture(PinkGhostUp1);
                    } else if(PinkGhostFeetTimer>10) {
                        PinkGhost.setTexture(PinkGhostUp2);
                    }
                }
            }
        } else {
            if(PinkDead == false) {
                if(powerUpTimer <480 || (powerUpTimer > 510 && powerUpTimer < 540) || powerUpTimer >570) {

                    if(OrangeGhostFeetTimer<10) {
                        PinkGhost.setTexture(ScaredGhostTexture1);
                    } else if(OrangeGhostFeetTimer>10) {
                        PinkGhost.setTexture(ScaredGhostTexture2);
                    }
                } else if((powerUpTimer > 480 && powerUpTimer < 510) || (powerUpTimer > 540&& powerUpTimer < 570)) {

                    if(OrangeGhostFeetTimer<10) {
                        PinkGhost.setTexture(ScaredGhostWhiteTexture1);
                    } else if(OrangeGhostFeetTimer>10) {
                        PinkGhost.setTexture(ScaredGhostWhiteTexture2);
                    }
                }
            } else {
                if(PinkX>0) {
                    PinkGhost.setTexture(EyeRight);
                } else if(PinkX<0) {
                    PinkGhost.setTexture(EyeLeft);
                } else if(PinkY>0) {
                    PinkGhost.setTexture(EyeDown);
                } else if(PinkY<0) {
                    PinkGhost.setTexture(EyetUp);
                }
            }
        }

        //////

        if(BlueScared == false) {

            if(BlueX>0) {
                if(PinkGhostFeetTimer<10) {
                    BlueGhost.setTexture(BlueGhostRight1);
                } else if(PinkGhostFeetTimer>10) {
                    BlueGhost.setTexture(BlueGhostRight2);
                }
            } else if(BlueX<0) {
                if(PinkGhostFeetTimer<10) {
                    BlueGhost.setTexture(BlueGhostLeft1);
                } else if(PinkGhostFeetTimer>10) {
                    BlueGhost.setTexture(BlueGhostLeft2);
                }
            } else {
                if(BlueY>0) {
                    if(PinkGhostFeetTimer<10) {
                        BlueGhost.setTexture(BlueGhostDown1);
                    } else if(PinkGhostFeetTimer>10) {
                        BlueGhost.setTexture(BlueGhostDown2);
                    }
                } else if(BlueY<0) {
                    if(PinkGhostFeetTimer<10) {
                        BlueGhost.setTexture(BlueGhostUp1);
                    } else if(PinkGhostFeetTimer>10) {
                        BlueGhost.setTexture(BlueGhostUp2);
                    }
                }
            }
        } else {
            if(BlueDead == false) {
                if(powerUpTimer <480 || (powerUpTimer > 510 && powerUpTimer < 540) || powerUpTimer >570) {

                    if(OrangeGhostFeetTimer<10) {
                        BlueGhost.setTexture(ScaredGhostTexture1);
                    } else if(OrangeGhostFeetTimer>10) {
                        BlueGhost.setTexture(ScaredGhostTexture2);
                    }
                } else if((powerUpTimer > 480 && powerUpTimer < 510) || (powerUpTimer > 540&& powerUpTimer < 570)) {

                    if(OrangeGhostFeetTimer<10) {
                        BlueGhost.setTexture(ScaredGhostWhiteTexture1);
                    } else if(OrangeGhostFeetTimer>10) {
                        BlueGhost.setTexture(ScaredGhostWhiteTexture2);
                    }
                }
            } else {
                if(BlueX>0) {
                    BlueGhost.setTexture(EyeRight);
                } else if(BlueX<0) {
                    BlueGhost.setTexture(EyeLeft);
                } else if(BlueY>0) {
                    BlueGhost.setTexture(EyeDown);
                } else if(BlueY<0) {
                    BlueGhost.setTexture(EyetUp);
                }
            }

        }





        PauseTimer++;

        if(InMenu == true) {
            TitlePacTimer++;
        }

        if(GamePaused == false && InMenu  == false) {

            glowTimer++;
            powerUpTimer++;
            Berrytimer++;





            if(PacDead == true) {
                death_ani_Timer++;
            }


            if(PacManX !=0 || PacManY !=0) {
                pacTimer++;
            }


            if(GhostScared == false) {
                GameStateTimer++;
            }

            if(PacDead == false) {
                PacMan.move(PacManX,PacManY);
                RedGhost.move(RedX, RedY);
                OrangeGhost.move(OrangeX, OrangeY);
                BlueGhost.move(BlueX, BlueY);
                PinkGhost.move(PinkX, PinkY);
            }
        }


        window.clear();
        window.setView(view);


        if(GameOver == false) {
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


                if(PacDead == false)
                    window.draw(PacMan);


            //    window.draw(shape);
                window.draw(scoreDis);

                window.draw(Berry);

                window.draw(PacDeath);

                window.draw(Paused);

                for(int i = 0; i<PacLife.size(); i++) {

                    window.draw(PacLife[i]);
                }


            } else {

                window.draw(Menu);




                for(int i = 0; i<3; i++) {
                    window.draw(YorN[i]);
                }

                window.draw(Setting);
                window.draw(Return);
                window.draw(Help);
                window.draw(Help_text_sprite);
                window.draw(Settings_text_sprite);

                window.draw(Track1);
                window.draw(Track2);
                window.draw(Track3);

                window.draw(StartImage);
                window.draw(PreStart);

                window.draw(TitlePacMan);

            }
        } else {
            window.draw(NewHS);
            window.draw(GameDone);
        }

        // window.draw(TestGhost);

        sf::View view = window.getView();
        window.display();
    }

    return 0;
}
