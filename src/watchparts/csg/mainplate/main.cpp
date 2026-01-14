#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include <opencsg.h>

#include "displaylistPrimitive.hpp"

#include "../shapes/shape_list.hpp"
#include "mainplate.hpp"

size_t SinCosCache::slices = 64;
std::vector<float> SinCosCache::sin;
std::vector<float> SinCosCache::cos;

//------- アニメーションの再生・停止----------//
static bool isPlaying = false;

//---------- OpenCSG用コンテナ -------------//
std::vector<OpenCSG::Primitive*> primitives;

// 地板 //
using gearx::MainPlate;
MainPlate mainplate;

//-----------各種プロトタイプ------------//
void display();
void reshape(int w, int h);
void timer(int val);
void keyboard(unsigned char key, int x, int y);

//---各種ディスプレイリスト作成---/
void createDisplayList();
void mainplateCreateDisplayList();

// 
void createDisplayList(){
	mainplateCreateDisplayList();
}


void mainplateCreateDisplayList() {
	// 地板の基盤となる板を描画
	GLuint id1 = glGenLists(1);
	glNewList(id1, GL_COMPILE);
	glPushMatrix();
	glScalef(0.01, 0.01, 0.01);
	/* 	
	for (const auto& object : mainplate.plate.objects){
		std::visit([](const auto& obj){
			obj.render();
		}, object);
	} */
	glPopMatrix();
 	
	glEndList();
	
	//　地板に穴をあける
	GLuint id2 = glGenLists(1);
	glNewList(id2, GL_COMPILE);
	glPushMatrix();
	glScalef(0.01, 0.01, 0.01);
	for (const auto& object : mainplate.cutout.objects) {
		std::visit([](const auto& obj) {
			obj.render();
		}, object);
	}
	glPopMatrix();
	glEndList();

	primitives.push_back(new OpenCSG::DisplayListPrimitive(id2, OpenCSG::Intersection, 1));
	primitives.push_back(new OpenCSG::DisplayListPrimitive(id1, OpenCSG::Subtraction, 1));
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
	glutCreateWindow("test [Eta 6497]");
	GLUT_CALL_FUNCs();

	OtherMyInit();
}


//--------- メイン関数 -----------//
int main(int argc, char **argv)
{
	

	GLUT_INITs(&argc,argv);
	gearx::shape_3d::Cylinder::initCache();
	// Primitivesにセット
	createDisplayList();

	
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