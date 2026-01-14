#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>

#include "./3d/shape3D.hpp"

using namespace gearx::shape_3d;

//------- アニメーションの再生・停止----------//
static bool isPlaying = false;
// 円柱 // 
size_t SinCosCache::slices = 10;	//min 10 max 2048*40
std::vector<float> SinCosCache::sin;
std::vector<float> SinCosCache::cos;

Cylinder c1(0.8, 1.0);
TruncatedCone t1(0.5, 1.0, 1.0);
ObroundCylinder ob1(1.0, 1.5, 1.0, SemiCircle::BOTH);
// ObroundCylinder ob1(Vec2(0.0, 0.0), Vec2(1.0, 0.0), 0.5, 1.0);

//-----------各種プロトタイプ------------//
void display();
void reshape(int w, int h);
void timer(int val);
void keyboard(unsigned char key, int x, int y);

void dosomething_init() {
	SinCosCache::init();
	float offset = 1.9f;
	c1.setHoleRadius(0.5).setPosition(0.0, 0.0, 0.0).setHeightRel(0.0, -1.0).setPosition(offset, 0.0, 0.0);
	t1.setHoleRadius(0.4).setPosition(c1.position()).setHeightRel(c1.top(), +0.5).setPosition(0.0, 0.0, 0.0);
	ob1.setRotation(+150.0).setPosition(-offset, 0.0, 0.0 );
	
	setNormal(Normal::OUTSIDE);
}

void dosomething() {
	//disk(sinCache, cosCache, 0.1);
	//hollowDisk(sinCache, cosCache, 0.3, 1.0);	

	glColor3f(0.2, 1.0, 0.2);
	glPushMatrix();
	c1.translate();
	c1.render();
	glPopMatrix();

	glPushMatrix();
	t1.translate();
	t1.render();
	glPopMatrix();

	glPushMatrix();
	ob1.translate();
	ob1.render();
	glPopMatrix();
}


void GLUT_CALL_FUNCs()
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,17);
	glutKeyboardFunc(keyboard);
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

	dosomething_init();
}


//--------- メイン関数 -----------//
int main(int argc, char **argv)
{
	

	GLUT_INITs(&argc,argv);

	
	GLenum err;
	err = glewInit();
	if (err != GLEW_OK){
		std::cerr << glewGetErrorString(err) << '\n'; //エラーを出力
		return -1;
	}
	
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

	glDepthFunc(GL_LESS);


	dosomething();

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
	// アニメーションの再生
	if (isPlaying) glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  	case '\033':  /* '\033' は ESC の ASCII コード */
    	exit(0);
	case ' ':	
		// スペースキーを押すと、再生⇋停止を切り替える
		isPlaying = !isPlaying;
		break;
  	default:
    	break;
  }
}