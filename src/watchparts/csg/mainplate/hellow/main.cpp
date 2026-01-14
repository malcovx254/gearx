#include <GL/glew.h>
#include <GL/glut.h>
#include <opencsg.h>
#include "../displaylistPrimitive.hpp"
#include <iostream>


//---------- OpenCSG用コンテナ -------------//
std::vector<OpenCSG::Primitive*> primitives;


//-----------各種プロトタイプ------------//
void display();
void reshape(int w, int h);
void timer(int val);

//---------- GLUTの初期設定 -------------//
void GLUT_CALL_FUNCs()
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,17);
}


void OtherMyInit()
{
	glClearColor(1,1,1,1);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, 1 );//両面に光源があたる
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

}

void GLUT_INITs(int *argcp,char **argv)
{
	glutInit(argcp, argv);
	glutInitWindowSize(640,480);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH|GLUT_STENCIL);
	glutCreateWindow("Hello OpenCSG");
	GLUT_CALL_FUNCs();

	OtherMyInit();
}

//ディスプレイリスト作成
void CreateDisplayList()
{
	GLuint id1 = glGenLists(1);
	glNewList(id1, GL_COMPILE);
	glutSolidSphere(1.2, 60, 60);
	glEndList();

	GLuint id2 = glGenLists(1);
	glNewList(id2, GL_COMPILE);
	glPushMatrix();
	glTranslatef(0.0,1.0,1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glEndList();

	primitives.push_back(new OpenCSG::DisplayListPrimitive(id1, OpenCSG::Intersection, 1));
	primitives.push_back(new OpenCSG::DisplayListPrimitive(id2, OpenCSG::Subtraction, 1));

}

//--------- メイン関数 -----------//
int main(int argc, char **argv)
{
	
	GLUT_INITs(&argc,argv);

	CreateDisplayList();

	
	GLenum err;
	err = glewInit();
	if (err != GLEW_OK){
		std::cerr << glewGetErrorString(err) << '\n'; //エラーを出力
		return -1;
	}

	
	//オフスクリーンの種類は自動で
	OpenCSG::setOption(OpenCSG::OffscreenSetting, OpenCSG::AutomaticOffscreenType);
	OpenCSG::setOption(OpenCSG::DepthComplexitySetting, OpenCSG::NoDepthComplexitySampling);
	glutMainLoop();


	return 0;
}

//--------- ここから各種コールバック ---------//
void display()
{
	static int rot = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(-3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	static float Light0Pos[]={1,1,1,0}; //光源の位置
	glLightfv(GL_LIGHT0, GL_POSITION, Light0Pos);

	glPushMatrix();
	glRotatef(static_cast<float>(rot),0,1,0);
	glColor3f(0,1,0);

	//ここからOpenCSGによる描画
	OpenCSG::render(primitives);
	glDepthFunc(GL_EQUAL);
	for (std::vector<OpenCSG::Primitive*>::const_iterator Iter = primitives.begin(); Iter != primitives.end(); ++Iter) {
		(*Iter)->render();
	}
	glDepthFunc(GL_LESS);


	glPopMatrix();

	glutSwapBuffers();

	if(++rot >= 360 ) rot = 0; 
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, w / static_cast<double>(h), 0.1, 200.0);
	glMatrixMode(GL_MODELVIEW);

}

void timer(int val)
{
	glutTimerFunc(17,timer,17);
	glutPostRedisplay();
}