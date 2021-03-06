#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <bits/stdc++.h>
#include <Windows.h>

#define oo 1e9
#define filePath "C:\\Users\\Lenovo\\Desktop\\graphics_project_math\\scores.txt"

using namespace std;



int phyWidth = 700;
int phyHeight = 700;
int logWigth = 100;
int logHeight = 100;

int centerX = logWigth/2;
int centerY = logHeight/2;

int mouseX = 0;
int mouseY = 0;

int status = 0;
int alphaY = 0;

bool playFlag = 1;
bool fileFlag = 1;

int numOfEq = 50;
int arrRes[55];
int answer = oo;
int index = 0;

int score = 0;
int Rank = 0;
int arrScores[10000];
int scoreSize = 0;
int scoreWindow = 0;

int durationGame = 60000;
int end_time = 0;

stringstream ss;



class square
{
public:

    int cX;
    int cY;
    int width;
    int hight;
    float red;
    float green;
    float blue;
    int deltaX = 0;
    int deltaY = 0;
    char equation[10];
    bool isAnswer = 0;
    float tRed = 1;
    float tGreen = 1;
    float tBlue = 1;

    square(char *eq, int cx, int cy, int wid, int high, float r, float g, float b)
    {
        strcpy(equation,eq);
        cX = cx;
        cY = cy;
        width = wid;
        hight = high;
        red = r;
        green = g;
        blue = b;
    }

    square(int cx, int cy, int wid, int high, float r, float g, float b)
    {
        cX = cx;
        cY = cy;
        width = wid;
        hight = high;
        red = r;
        green = g;
        blue = b;
    }

private:

    void printSome(string str, int cx, int cy)
    {
        glRasterPos2d(cx,cy);

        int len = str.size();
        for (int i=0;i<len;i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);

        glFlush();
    }

public:

    void color(float r, float g, float b)
    {
        red = r;
        green = g;
        blue = b;
    }

    void textColor(float r, float g, float b)
    {
        tRed = r;
        tGreen = g;
        tBlue = b;
    }

    void drawSquare(string str, float r, float g, float b)
    {
        glColor3f(r,g,b);
        glBegin(GL_POLYGON);
            glVertex2f(cX-(width/2)+1, cY-(hight/2)-1);
            glVertex2f(cX+(width/2)+1, cY-(hight/2)-1);
            glVertex2f(cX+(width/2)+1, cY+(hight/2)-1);
            glVertex2f(cX-(width/2)+1, cY+(hight/2)-1);
        glEnd();

        glColor3f(red,green,blue);
        glBegin(GL_POLYGON);
            glVertex2f(cX-width/2 +deltaX, cY-hight/2 +deltaY);
            glVertex2f(cX+width/2 +deltaX, cY-hight/2 +deltaY);
            glVertex2f(cX+width/2 +deltaX, cY+hight/2 +deltaY);
            glVertex2f(cX-width/2 +deltaX, cY+hight/2 +deltaY);
        glEnd();

        int len = str.size();
        int x = cX-len+1 +deltaX;
        int y = cY-1 +deltaY;

        glColor3f(tRed,tGreen,tBlue);
        printSome(str,x,y);
    }

    void drawSquare(float r, float g, float b, int dY)
    {
        glColor3f(r,g,b);
        glBegin(GL_POLYGON);
            glVertex2f(cX-(width+2)/2, cY-(hight+2)/2 +dY);
            glVertex2f(cX+(width+2)/2, cY-(hight+2)/2 +dY);
            glVertex2f(cX+(width+2)/2, cY+(hight+2)/2 +dY);
            glVertex2f(cX-(width+2)/2, cY+(hight+2)/2 +dY);
        glEnd();

        glColor3f(red,green,blue);
        glBegin(GL_POLYGON);
            glVertex2f(cX-width/2, cY-hight/2 +dY);
            glVertex2f(cX+width/2, cY-hight/2 +dY);
            glVertex2f(cX+width/2, cY+hight/2 +dY);
            glVertex2f(cX-width/2, cY+hight/2 +dY);
        glEnd();

        int len = strlen(equation);
        int x = cX-len+3;
        int y = cY-1+dY;

        glColor3f(tRed,tGreen,tBlue);
        printSome(equation,x,y);
    }

    bool checkRange(int mX, int mY)
    {
        return mX >= cX-width/2 && mX <= cX+width/2 && mY >= cY-hight/2 && mY <= cY+hight/2;
    }
};

class triangle
{
public:

    int cX;
    int cY;
    int hypotenuse;
    float red;
    float green;
    float blue;
    bool click = false;

    triangle(int cx, int cy, int hypot, float r, float g, float b)
    {
        cX = cx;
        cY = cy;
        hypotenuse = hypot;
        red = r;
        green = g;
        blue = b;
    }

    void color(float r, float g, float b)
    {
        red = r;
        green = g;
        blue = b;
    }

    void drawArrowDown()
    {
        glColor3f(red,green,blue);
        glBegin(GL_POLYGON);
            glVertex2f(cX, cY);
            glVertex2f(cX-hypotenuse+click, cY+hypotenuse-click);
            glVertex2f(cX+hypotenuse-click, cY+hypotenuse-click);
        glEnd();
    }

    void drawArrowUp()
    {
        glColor3f(red,green,blue);
        glBegin(GL_POLYGON);
            glVertex2f(cX, cY);
            glVertex2f(cX-hypotenuse+click, cY-hypotenuse+click);
            glVertex2f(cX+hypotenuse-click, cY-hypotenuse+click);
        glEnd();
    }

    bool checkRange(int mX, int mY)
    {
        return mX >= cX-hypotenuse && mX <= cX+hypotenuse && mY >= cY && mY <= cY+hypotenuse;
    }

    bool checkRange(int mX, int mY, int x)
    {
        return mX >= cX-hypotenuse && mX <= cX+hypotenuse && mY <= cY && mY >= cY-hypotenuse;
    }
};


square playBTN = square(centerX,centerY+15,20,10,0.5,0.5,0.5);
square highScoreBTN = square(centerX,centerY,20,10,0.5,0.5,0.5);
square quitBTN = square(centerX,centerY-15,20,10,0.5,0.5,0.5);
square helpBTN = square(centerX+38,centerY-46,10,5,0,0,0);

square background = square(centerX,centerY,100,100,0.5,0.5,0.5);
square centerLine = square(centerX,centerY,2,100,1,1,1);
square highScoresBG = square(centerX,centerY,80,45,0.5,0.5,0.5);

vector <square> eqArr;

triangle arrowDown = triangle(centerX,centerY-28,2,1,1,1);
triangle arrowUp = triangle(centerX,centerY+28,2,1,1,1);


void init2D(float r, float g, float b)
{
    glClearColor(r,g,b,0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, logWigth, 0.0, logHeight);
}

void Timer(int value)
{
    glutTimerFunc(100,Timer,value);
    glutPostRedisplay();
}

void printSome24(char *str,int x,int y)
{
    glRasterPos2d(x,y);

    int len = strlen(str);
    for (int i=0;i<len;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);

    glFlush();
}

void mouseClick(int btn, int state, int x, int y)
{
    mouseX = x;
    mouseX = 0.5+1.0*mouseX*logWigth/phyWidth;
    mouseY = phyHeight- y;
    mouseY = 0.5+1.0*mouseY*logHeight/phyHeight;

    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(arrowUp.checkRange(mouseX,mouseY,1) && status == 4)
        {
            arrowUp.click = true;
            arrowUp.color(0.5,0.5,0.5);
        }
        else if(arrowDown.checkRange(mouseX,mouseY) && status == 4)
        {
            arrowDown.click = true;
            arrowDown.color(0.5,0.5,0.5);
        }
        else
        {
            arrowUp.click = false;
            arrowUp.color(1,1,1);

            arrowDown.click = false;
            arrowDown.color(1,1,1);
        }
    }
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if(playBTN.checkRange(mouseX,mouseY) && status == 1)
            status = 2;
        else if(highScoreBTN.checkRange(mouseX,mouseY) && status == 1)
            status = 4;
        else if(helpBTN.checkRange(mouseX,mouseY) && status == 1)
            status = 5;
        else if(quitBTN.checkRange(mouseX,mouseY) && status == 1)
            status = 6;

        if(arrowUp.checkRange(mouseX,mouseY,1) && status == 4)
        {
            arrowUp.click = false;
            arrowUp.color(1,1,1);
            scoreWindow -= (scoreWindow > 0);
        }
        else if(arrowDown.checkRange(mouseX,mouseY) && status == 4)
        {
            arrowDown.click = false;
            arrowDown.color(1,1,1);
            scoreWindow += (scoreWindow < scoreSize-1);
        }
    }
}

void passiveMouse(int x, int y)
{
    mouseX = x;
    mouseX = 0.5+1.0*mouseX*logWigth/phyWidth;
    mouseY = phyHeight- y;
    mouseY = 0.5+1.0*mouseY*logHeight/phyHeight;

    if(status == 1)
    {
        if(playBTN.checkRange(mouseX,mouseY))
        {
            playBTN.color(0,0.8,0);
            playBTN.deltaX = 1;
            playBTN.deltaY = -1;
        }
        else if(highScoreBTN.checkRange(mouseX,mouseY))
        {
            highScoreBTN.color(0,0,1);
            highScoreBTN.deltaX = 1;
            highScoreBTN.deltaY = -1;
        }
        else if(quitBTN.checkRange(mouseX,mouseY))
        {
            quitBTN.color(1,0,0);
            quitBTN.deltaX = 1;
            quitBTN.deltaY = -1;
        }
        else if(helpBTN.checkRange(mouseX,mouseY))
        {
            helpBTN.color(0.8,0.8,0.8);
            helpBTN.textColor(0,0,0);
        }
        else
        {
            playBTN.color(0.5,0.5,0.5);
            playBTN.deltaX = 0;
            playBTN.deltaY = 0;

            highScoreBTN.color(0.5,0.5,0.5);
            highScoreBTN.deltaX = 0;
            highScoreBTN.deltaY = 0;

            quitBTN.color(0.5,0.5,0.5);
            quitBTN.deltaX = 0;
            quitBTN.deltaY = 0;

            helpBTN.color(0,0,0);
            helpBTN.textColor(1,1,1);
        }
    }
}

void Keyboard(unsigned char key, int x, int y)
{
    ss<<key;

    if(key == (char)13)
    {
        ss>>answer;
        ss.clear();
    }
}

void specialKeyboard(int key, int x, int y)
{
    if(key==GLUT_KEY_F1)
    {
        status = 2;
        playFlag = 1;
    }
    else if(key== GLUT_KEY_F2)
    {
        status = 1;

        mouseX = 0;
        mouseY = 0;

        playBTN.color(0.5,0.5,0.5);
        playBTN.deltaX = 0;
        playBTN.deltaY = 0;

        highScoreBTN.color(0.5,0.5,0.5);
        highScoreBTN.deltaX = 0;
        highScoreBTN.deltaY = 0;

        quitBTN.color(0.5,0.5,0.5);
        quitBTN.deltaX = 0;
        quitBTN.deltaY = 0;
    }
}

void setup()
{
    eqArr.clear();

    int y = 15;
    char operators[] = {'+','-','x'};
    char str[10];

    sprintf(str,"START  ");
    square sq = square(str,centerX,y,20,10,0.5,0,0.5);
    eqArr.push_back(sq);
    y -= 35;

    arrRes[0] = -oo;

    for(int i=1; i<numOfEq; i++)
    {
        int num1 = rand()%100; //rand()%4;
        int num2 = rand()%100; //rand()%4;
        char op = operators[rand()%3];

        sprintf(str,"%d %c %d",num1,op,num2);
        sq = square(str,centerX,y,20,10,0.5,0,0.5);
        eqArr.push_back(sq);
        y -= 35;

        switch(op)
        {
            case '+': arrRes[i] = num1+num2;break;
            case '-': arrRes[i] = num1-num2;break;
            case 'x': arrRes[i] = num1*num2;break;
        }
    }
}

void menu()
{
    playFlag = 1;

    glColor3f(1,0,0);
    char str[] = "Ma+h Her0";
    printSome24(str,centerX-9,95);

    playBTN.drawSquare("PLAY",0.7,0.7,0.7);
    highScoreBTN.drawSquare("HIGH SCORE",0.7,0.7,0.7);
    quitBTN.drawSquare("QUIT",0.7,0.7,0.7);
    helpBTN.drawSquare("HELP",0,0,0);
}

void checkAns()
{
    if(arrRes[index] == answer && !eqArr[index].isAnswer && eqArr[index].cY+alphaY > 1)
    {
        score++;
        eqArr[index].color(0,0.8,0);
        eqArr[index].isAnswer = 1;
    }
    else if(arrRes[index+1] == answer && !eqArr[index+1].isAnswer && eqArr[index+1].cY+alphaY > 1)
    {
        score++;
        eqArr[index+1].color(0,0.8,0);
        eqArr[index+1].isAnswer = 1;
    }
    else if(arrRes[index+2] == answer && !eqArr[index+2].isAnswer && eqArr[index+2].cY+alphaY > 1)
    {
        score++;
        eqArr[index+2].color(0,0.8,0);
        eqArr[index+2].isAnswer = 1;
    }

    answer = oo;
}

void play()
{
    if(playFlag)
    {
        score = 0;
        index = 0;
        alphaY = 0;
        setup();
        end_time = clock()+durationGame;
        playFlag = 0;
    }

    background.drawSquare(0.5,0.5,0.5,0);
    centerLine.drawSquare(0.5,0.5,0.5,0);

    char str[15];
    sprintf(str,"Score: %d",score);
    glColor3f(1,1,1);
    printSome24(str,2,95);

    for(int i=0; i<numOfEq; i++)
    {
        eqArr[i].drawSquare(1,1,1,alphaY);
    }
    alphaY++;

    checkAns();

    if(eqArr[index].cY+alphaY > 101)
    {
        index++;
    }

    if(clock() >= end_time)
    {
        status = 3;
        fileFlag = 1;

        FILE *fscores = fopen(filePath,"a");
        fprintf(fscores,"%d\n",score);
        fclose(fscores);

        int i = 0;

        fscores = fopen(filePath,"r");
        while(~fscanf(fscores,"%d",arrScores+i++));
        fclose(fscores);

        scoreSize = i-1;

        sort(arrScores, arrScores+scoreSize);

        Rank = upper_bound(arrScores, arrScores+scoreSize, score) - arrScores;
        Rank = scoreSize - Rank + 1;
    }
}

void result()
{
    char str[15];

    sprintf(str,"Your Score is %d",score);
    glColor3f(1,1,1);
    printSome24(str,centerX-16,centerY+4);

    if(Rank%10 == 1)
        sprintf(str,"Your Rank is %dst",Rank);
    else if(Rank%10 == 2)
        sprintf(str,"Your Rank is %dnd",Rank);
    else
        sprintf(str,"Your Rank is %dth",Rank);

    glColor3f(1,1,1);
    printSome24(str,centerX-16,centerY-4);
}

void highScores()
{
    char str[15] = "HIGH SCORES";
    glColor3f(0,0,1);
    printSome24(str,centerX-11,95);

    arrowUp.drawArrowUp();
    highScoresBG.drawSquare(1,1,1,0);
    arrowDown.drawArrowDown();

    if(fileFlag)
    {
        int i = 0;

        FILE *fscores = fopen(filePath,"r");
        while(~fscanf(fscores,"%d",arrScores+i++));
        fclose(fscores);

        scoreSize = i-1;

        sort(arrScores, arrScores+scoreSize, greater<int>());

        fileFlag = 0;
    }

    for(int i=scoreWindow; i<5+scoreWindow && i<scoreSize; i++)
    {
        sprintf(str,"%d. %d",i+1,arrScores[i]);
        glColor3f(1,1,1);
        printSome24(str,13,65-i*8+scoreWindow*8);
    }
}

void help()
{
    char str[15];
    glColor3f(1,1,1);

    sprintf(str,"PLAY -> F1");
    printSome24(str,centerX-10,centerY+4);

    sprintf(str,"MENU -> F2");
    printSome24(str,centerX-10,centerY-4);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    switch(status)
    {
        case 0: setup();status=1;break;
        case 1: menu();break;
        case 2: play();break;
        case 3: result();break;
        case 4: highScores();break;
        case 5: help();break;
        case 6: exit(0);
    }

    glutSwapBuffers();

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowPosition (logWigth, logHeight);
    glutInitWindowSize (phyWidth , phyHeight);
    glutCreateWindow ("MATH HERO");
    init2D(0.0,0.0,0.0);
    glutDisplayFunc(display);

    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(passiveMouse);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(specialKeyboard);

    Timer(0);
    glutMainLoop();

    return EXIT_SUCCESS;
}
