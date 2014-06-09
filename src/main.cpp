
#define STRICT
#define WIN32_Lean_AND_MEAN
#define pi 3.141592
#define PI 3.141592
#include "enviroment/AgentsEnviroment.h"
#include <windows.h>
#include <GL/glui.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#define PlayAndStop 1
#define Evolution 2
#define Initialization 3
#define MAX_SPEED 4
#define ADD 5






using namespace std;
int WinWidth=1200;
int WinHeight=1000;
AgentsEnviroment env;
AgentsEnviroment env_copy;








float xy_aspect;
int   last_x, last_y;
GLUI_RadioGroup  *radio;
GLUI_Button *ok;
GLUI_Button *init_ok;
GLUI_Button *play_stop;
GLUI *glui;
int   main_window;
GLUI_Panel      *obj_panel;
GLfloat rx=0;
GLfloat ry=0;
GLfloat tx=0;
GLfloat ty=0;
GLfloat tz=-9;
GLint tt=0;
GLboolean bTimer=0;
bool timeroff=true;
const string tstr[2]= {"Translate XY","TranslateXZ"};
int mx,my;
double angle;
bool ldown=false;
bool rdown=false;
double x=0,y=0,z=0;
bool evolution=false;
bool file=false;
int predator_count=7;
int herbivore_count=15;
int plant_count=20;
int env_size=40;
int ev_count=10;
bool ev_flag=false;
int population_num=0;
int add_x=20;
int add_y=20;
int radioint=2;



DWORD WINAPI SecondThread(PVOID pvParam)
{
    // for(int i=0;i<10000;i++)
//cout<<"Potok!"<<* ((int *) pvParam)<<endl;
    for(int i=0; i<* ((int *) pvParam); i++)
    {
        env_copy.NewPopulation();
        population_num+=1;
            glui->sync_live();
    }
    ev_flag=true;
    return(0);
}
void Mouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON)
    {
        switch(state)
        {
        case GLUT_DOWN:
        {
            ldown=true;
            mx=x;
            my=y;
            break;
        }

        case GLUT_UP:
            ldown=false;
            break;
        }
    }
    if(button==GLUT_RIGHT_BUTTON)
    {
        switch(state)
        {
        case GLUT_DOWN:
            rdown=true;
            mx=x;
            my=y;
            break;
        case GLUT_UP:
            rdown=false;
            break;
        }
    }

}
void MouseMotion(int x,int y)
{
    if(ldown)
    {
        rx+=0.5*(y-my);
        ry+=0.5*(x-mx);
        mx=x;
        my=y;
        glutPostRedisplay();
    }
    if(rdown)
    {
        tx+=0.01*(x-mx);
        if(tt)
            tz+=0.01*(y-my);
        else
            ty+=0.01*(my-y);
        mx=x;
        my=y;
        glutPostRedisplay();
    }

}
void Init()
{
    glEnable(GL_DEPTH_TEST);

    float ambient[4] = {0.6, 0.6, 0.6, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glClearColor(0,0,0,1);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}
double x1=0,z1=0,rotx=0;
void Timer(int value)
{
    if(bTimer)
    {

        env.AgentsObserver();
        env.NewStep();
        env.AgentsMove(40);
        if(evolution)
        {
            evolution=!evolution;
            //for(int k=0; k<100; k++)
            //{
            //    env.NewPopulation();
            //}
            env_copy=env;
            DWORD dwThreadID;
            HANDLE hThread = CreateThread(NULL, 0, SecondThread, (PVOID) &ev_count, 0, &dwThreadID);

        }
        if(ev_flag)
        {

            ev_flag=false;
            for(int i=0; i<env.herbivorious.size(); i++)
            {
                env.herbivorious[i].brain=env_copy.herbivorious[i%(env_copy.herbivorious.size())].brain;
            }
            for(int i=0; i<env.predators.size(); i++)
            {
                env.predators[i].brain=env_copy.predators[i%(env_copy.predators.size())].brain;
            }
            cout<<"Copy data"<<endl<<"Population:"<<population_num<<endl;
            ok->enable();
        }
        glutPostRedisplay();
        glutTimerFunc(80,Timer,1);

    }
}
void myGlutReshape( int x, int y )
{
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    glViewport( tx, ty, tw, th );

    xy_aspect = (float)tw / (float)th;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,WinWidth/WinHeight,10,200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}
void Display()
{

    GLfloat light_position[]= {-1.0,1.0,-1.0,0.0};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0,0,-60);
    glTranslatef(5*tx,5*ty,tz);
    glRotatef(30,1,0,0);
    //glRotatef(90,0,1,0);
    glRotatef(rx,1,0,0);
    glRotatef(ry,0,1,0);
    glTranslatef(-20,0,-20);
    glBegin(GL_QUADS);
    glColor3f(0.3,0.4,0);  //цвет пола
    glVertex3d(0,0,0);
    glVertex3d(0,0,40);
    glVertex3d(40,0,40);
    glVertex3d(40,0,0);
    glEnd();
    glTranslatef(0,0.5,0);
    glColor3f(1.0, 0.0, 0.0); //красный
    int pred_cycle_count=env.predators.size();
    for(unsigned int i=0; i<pred_cycle_count; i++)
    {

        glPushMatrix();
        glTranslatef(env.predators[i].x,0,env.predators[i].y);
        glRotatef((env.predators[i].angle*180/pi),0,1,0);
        glutSolidSphere(env.predators[i].energy/600.0,10,10);
        glPopMatrix();

    }
    glColor3f(0.0, 0.0, 1.0);
    int herb_cycle_count=env.herbivorious.size();
    for(unsigned int i=0; i<herb_cycle_count; i++)
    {

        glPushMatrix();
        glTranslatef(env.herbivorious[i].x,0,env.herbivorious[i].y);
        //glutSolidCube(0.5);
        glRotatef((env.herbivorious[i].angle*180/pi),0,1,0);
        glutSolidSphere(env.herbivorious[i].energy/600.0,10,10);
        glPopMatrix();

    }
    glColor3f(0.0, 1.0, 0.0); //зеленый
    int plant_cycle_count=env.plants.size();
    for(unsigned int i=0; i<plant_cycle_count; i++)
    {

        glPushMatrix();
        glTranslatef(env.plants[i].x,0,env.plants[i].y);
        glutSolidCube(0.5);
        glPopMatrix();

    }
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();


}
void Keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
    case VK_ESCAPE:
        exit(0);
        break;
    }
}

void KeyboardSpecial(int key,int x,int y)
{

}
void Reshape(int Width,int Height)
{
    WinWidth=Width;
    WinHeight=Height;
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    glViewport( tx, ty, tw, th );

    xy_aspect = (float)tw / (float)th;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,WinWidth/WinHeight,10,200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}
void control_cb( int control )
{

    if(control==PlayAndStop)
    {
        bTimer=!bTimer;
        if(bTimer==false)
        {
            timeroff=true;
        }
    }
    if (bTimer&&timeroff)
    {
        timeroff=false;
        glutTimerFunc(80,Timer,1);
    }
    if(control==Evolution)
    {
        evolution=!evolution;
        ok->disable();
    }
    if(control==ADD)
    {
        if(radioint==0)
        {
         Predator pred(add_x,add_y,rand()%400,(static_cast<double>(rand()) / RAND_MAX)/4);
         pred.brain=mutate(env.predators[0].brain);
        env.predators.push_back(pred);
        }
        if(radioint==1)
        {
         Herbivore herb(add_x,add_y,rand()%400,(static_cast<double>(rand()) / RAND_MAX)/4);
        herb.brain=mutate(env.herbivorious[0].brain);
        env.herbivorious.push_back(herb);
        }
        if(radioint==2)
        {
         Plant plant(add_x,add_y);
        env.plants.push_back(plant);
        }
    }


    if(control==Initialization)
    {
        init_ok->disable();
        play_stop->enable();
        env.predators.clear();
        env.plants.clear();
        env.herbivorious.clear();
        srand(time(NULL));
        for(int i=0; i<predator_count; i++)
        {
            Predator pred(rand()%40,rand()%40,rand()%400,(static_cast<double>(rand()) / RAND_MAX)/4);
            //cout<<"x:"<<pred.x<<"y:"<<pred.y<<endl;
            env.predators.push_back(pred);

        }

        for(int i=0; i<herbivore_count; i++)
        {
            Herbivore herb(rand()%40,rand()%40,rand()%400,(static_cast<double>(rand()) / RAND_MAX)/4);
            //cout<<"x:"<<herb.x<<"y:"<<herb.y<<endl;
            env.herbivorious.push_back(herb);
        }
        for(int i=0; i<plant_count; i++)
        {
            Plant plantf(rand()%40,rand()%40);
            env.plants.push_back(plantf);
        }
    }
}
void myGlutMouse(int button, int button_state, int x, int y )
{
}
void myGlutIdle( void )
{
    /* According to the GLUT specification, the current window is
       undefined during an idle callback.  So we need to explicitly change
       it if necessary */
    if ( glutGetWindow() != main_window )
        glutSetWindow(main_window);

    /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                         application  */

    glutPostRedisplay();
}
void myGlutMotion(int x, int y )
{
    glutPostRedisplay();
}
int main(int argc,char*argv[])
{
    env.width=40;
    env.bestherbfitness=1;
    env.bestpredfitness=1;
    srand(time(NULL));
    for(int i=0; i<predator_count; i++)
    {
        Predator pred(rand()%40,rand()%40,rand()%400,(static_cast<double>(rand()) / RAND_MAX)/4);
        //cout<<"x:"<<pred.x<<"y:"<<pred.y<<endl;
        env.predators.push_back(pred);

    }

    for(int i=0; i<herbivore_count; i++)
    {
        Herbivore herb(rand()%40,rand()%40,rand()%400,(static_cast<double>(rand()) / RAND_MAX)/4);
        //cout<<"x:"<<herb.x<<"y:"<<herb.y<<endl;
        env.herbivorious.push_back(herb);
    }
    for(int i=0; i<plant_count; i++)
    {
        Plant plantf(rand()%40,rand()%40);
        env.plants.push_back(plantf);
    }
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WinWidth,WinHeight);
    glutInitWindowPosition(20,20);
    main_window=glutCreateWindow("Artifical life");
    Init();
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(KeyboardSpecial);
    //glutReshapeFunc(Reshape);
    glutMouseFunc(Mouse);
    glutMotionFunc(MouseMotion);
    GLUI_Master.set_glutReshapeFunc( myGlutReshape );
    GLUI_Master.set_glutIdleFunc( myGlutIdle );
    glui = GLUI_Master.create_glui_subwindow( main_window,GLUI_SUBWINDOW_RIGHT);
    obj_panel = new GLUI_Rollout(glui, "Initial parameters",true);
    GLUI_Spinner *predator_spinner =
        new GLUI_Spinner( obj_panel, "Predators:", &predator_count);
    predator_spinner->set_int_limits( 3, 20 );
    predator_spinner->set_alignment( GLUI_ALIGN_RIGHT );
    GLUI_Spinner *herbivore_spinner =
        new GLUI_Spinner( obj_panel, "Herbivorious:", &herbivore_count);
    herbivore_spinner->set_int_limits( 3, 20 );
    herbivore_spinner->set_alignment( GLUI_ALIGN_RIGHT );
    GLUI_Spinner *plant_spinner =
        new GLUI_Spinner( obj_panel, "Plants:", &plant_count);
    plant_spinner->set_int_limits( 5, 100 );
    plant_spinner->set_alignment( GLUI_ALIGN_RIGHT );
    init_ok=new GLUI_Button( obj_panel, "OK", Initialization, control_cb );











    GLUI_Panel *option= new GLUI_Rollout( glui, "Option" ,false);
    GLUI_Panel *act_panel = new GLUI_Panel( option, "Action" );

    radio = new GLUI_RadioGroup(act_panel,&radioint,8,control_cb);
    new GLUI_RadioButton( radio, "Add predator" );
    new GLUI_RadioButton( radio, "Add herbivore" );
    new GLUI_RadioButton( radio, "Add plant" );
    GLUI_Spinner *x_spinner =new GLUI_Spinner( option, "Agent's x:", &add_x);
    x_spinner->set_int_limits( 0, 40 );
    x_spinner->set_alignment( GLUI_ALIGN_LEFT);
    GLUI_Spinner *y_spinner =new GLUI_Spinner( option, "Agent's y:", &add_y);
    y_spinner->set_int_limits( 0, 40 );
    y_spinner->set_alignment( GLUI_ALIGN_LEFT );
    new GLUI_Button( option, "Add", ADD, control_cb );
    new GLUI_Checkbox( option, "Energy", &energy_flag );
    GLUI_Panel *evolution= new GLUI_Rollout( glui, "Evolution",false );
    GLUI_EditText *counter_edittext = new GLUI_EditText( evolution, "Population:", &population_num );
    counter_edittext->disable();
    GLUI_Spinner *evolution_spinner =
        new GLUI_Spinner( evolution, "GA iterations:", &ev_count);

    evolution_spinner->set_int_limits( 1, 100 );
    evolution_spinner->set_alignment( GLUI_ALIGN_RIGHT );
    ok=new GLUI_Button( evolution, "OK", Evolution, control_cb );

    play_stop=new GLUI_Button( glui, "Play/Stop", PlayAndStop, control_cb );
    play_stop->disable();
    glutMainLoop();
    return 0;
}
