#include <GL/glut.h>
#include <pthread.h>
#include <stdio.h>
typedef struct{
	float x1, y1;
	float x2, y2;
	float peluru_x, peluru_y;
	int sedangMenembak;
	int nyawa;
}gametank;
pthread_t player[2];
	int pilih;

gametank user;
gametank user2;
void reDraw();
void looping();
void drawString(float x, float y, float z, char *string);
//prosedur untuk menembak
void *tembak1(){//untuk player 1
		if (user.peluru_y > -1.0 && user.sedangMenembak == 1 )
		{
		user.peluru_y = user.peluru_y - 0.001;//Supaya koordinat bertambah saat player menembak
		}else{
			user.sedangMenembak = 0;
		}

}
void *tembak2(){//untuk player 2

		if (user2.peluru_y < 1.0  && user2.sedangMenembak == 1 )
		{
		user2.peluru_y = user2.peluru_y + 0.001;
		}else{
			user2.sedangMenembak = 0;
		}
}

void interaksi(){//nyawa
	if(user.peluru_y < user2.y2 - 0.05 && (user.peluru_x < user2.x1 && user.peluru_x > user2.x2)){
		user2.nyawa = 1;
	}else if (user2.peluru_y > user.y2 - 0.05 && (user2.peluru_x < user.x1 && user2.peluru_x > user.x2)){
		user.nyawa = 1;
	}
}

void menu(){//menampilkan menu
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);//untuk menghapus warna menjadi hitam
glClear (GL_COLOR_BUFFER_BIT);
//membuat kotak atau garis
glPushMatrix ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);//garis
glVertex2f(-0.9,0.9); //kiri atas
glVertex2f(-0.9,-0.9); //kiri atas
glEnd ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);//garis
glVertex2f(0.9,-0.9); //kanan bawah
glVertex2f(-0.9,-0.9); //kanan bawah
glEnd ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);
glVertex2f(0.9,-0.9);//kanan atas
glVertex2f(0.9,0.9); //kanan atas
glEnd ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);
glVertex2f(-0.9,0.9); //kiri atas
glVertex2f(0.9,0.9); //kiri atas
glEnd ();
drawString(-0.1,0.1,0, "Game Tank");
drawString(-0.2,-0.1,0, "Tekan Y untuk bermain");
drawString(-0.2,-0.3, 0, "Tekan C untuk Keluar");

glFlush();
}


void bentuk(void){
	user.x1=0.1;
	user.x2=0.0;

	user.y1=0.8;
	user.y2=0.7;

	user.sedangMenembak = 0;
	user.nyawa = 0;

	user2.x1=0.1;
	user2.x2=0.0;

	user2.y1=-0.8;
	user2.y2=-0.7;

	user2.sedangMenembak = 0;
	user2.nyawa = 0;

	pilih=0;
}

void reDraw(){
	user.x1=user.x1;//tank 1
	user.x2=user.x2;//tank 1

	user.y1=user.y1;//tank 1 
	user.y2=user.y2;//tank 1

	user2.x1=user2.x1;//tank 2
	user2.x2=user2.x2;//tank 2

	user2.y1=user2.y1;//tank 2
	user2.y2=user2.y2;//tank 2

	if (user.sedangMenembak == 0)
	{
		user.peluru_x=user.x1 - 0.05;//agar peluru mengikuti tank 1
		user.peluru_y=user.y1 - 0.05;//agar peluru mengikuti tank 1
	}

	if (user2.sedangMenembak == 0){
		user2.peluru_x=user2.x2 + 0.05;//agar peluru mengikuti tank 2
		user2.peluru_y=user2.y2 - 0.05;//agar peluru mengikuti tank 2
	}
}

//membuat tampilan jika permainan selesai
void gameover(){
glClearColor (0.0f, 0.0f, 0.0f, 0.0f);//untuk menghapus warna menjadi hitam
glClear (GL_COLOR_BUFFER_BIT);
//membuat kotak atau garis
glPushMatrix ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);//garis
glVertex2f(-0.9,0.9); //kiri atas
glVertex2f(-0.9,-0.9); //kiri atas
glEnd ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);//garis
glVertex2f(0.9,-0.9); //kanan bawah
glVertex2f(-0.9,-0.9); //kanan bawah
glEnd ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);
glVertex2f(0.9,-0.9);//kanan atas
glVertex2f(0.9,0.9); //kanan atas
glEnd ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);
glVertex2f(-0.9,0.9); //kiri atas
glVertex2f(0.9,0.9); //kiri atas
glEnd ();
if (user.nyawa == 1)//nyawa yang diberikan 1
{
	drawString(0,0,0, "PLAYER 1 MENANG");
}else if(user2.nyawa == 1){//nyawa yang diberikan 1
	drawString(0,0,0, "PLAYER 2 MENANG");
}
drawString(0,-0.2,0, "Tekan R untuk bermain kembali");
glFlush();
}

//membuat style text
void drawString(float x, float y, float z, char *string) {
  glRasterPos3f(x, y, z);

  for (char* c = string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);//font style yang diberikan
  }
}

void display(void)
{
glClearColor (0.0f, 0.0f, 0.0f, 0.0f);//untuk menghapus warna menjadi hitam
glClear (GL_COLOR_BUFFER_BIT);
//membuat kotak atau garis
glPushMatrix ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);//garis
glVertex2f(-0.9,0.9); //kiri atas
glVertex2f(-0.9,-0.9); //kiri atas
glEnd ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);//garis
glVertex2f(0.9,-0.9); //kanan bawah
glVertex2f(-0.9,-0.9); //kanan bawah
glEnd ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);
glVertex2f(0.9,-0.9);//kanan atas
glVertex2f(0.9,0.9); //kanan atas
glEnd ();

glClearColor(1,1,1,0);
glColor3f(1,1,1); //
glBegin(GL_LINES);
glVertex2f(-0.9,0.9); //kiri atas
glVertex2f(0.9,0.9); //kiri atas
glEnd ();

//membuat batas
glClearColor(1,1,1,0);
glColor3f(0,1,0); //
glBegin(GL_LINES);
glVertex2f(-0.9,0.0); //kanan bawah
glVertex2f(0.9,0.0);
glEnd ();

//membuat tank 1
if (user.nyawa == 0)
{
	/* code */
glClearColor(1,1,1,0);
glColor3f(0.5,0.1,0);//warna merah
glBegin(GL_LINE_LOOP); //membuat bentuk tank 1
glVertex2f(user.x1,user.y1);//kiri
glVertex2f(user.x2,user.y1);//kanan
glVertex2f(user.x2,user.y2);//atas
glVertex2f(user.x1,user.y2);//bawah
glEnd();
glColor3f(1,1,1);
drawString(-0.8,-0.8,0, "player 1");
//membuat peluru user 1

glPointSize(4.0);
glColor3f(1.0, 1.0, 1.0);//warna putih
glBegin(GL_POINTS);//membuat titik
glVertex3f(user.peluru_x, user.peluru_y, 0.0);// posisi titik yang akan digambar
glEnd();
}


//membuat tank 2
if (user2.nyawa == 0)
{
	/* code */
glClearColor(1,1,1,0);
glColor3f(0.5,0,1);//warna ungu
glBegin(GL_LINE_LOOP);
glVertex2f(user2.x1,user2.y1); //kiri
glVertex2f(user2.x2,user2.y1); //kanan
glVertex2f(user2.x2,user2.y2); //atas
glVertex2f(user2.x1,user2.y2); //bawah
glEnd();
//membuat peluru user 2
glPointSize(4.0);
glColor3f(1.0, 1.0, 1.0);//warna putih
glBegin(GL_POINTS);// awal kode untuk menggambar
glVertex3f(user2.peluru_x, user2.peluru_y, 0.0);// posisi titik yang akan digambar
glEnd();
}
drawString(-0.8,0.8,0, "player 2");



glFlush();
}



//menggerakkan
 void keys (unsigned char key, int xmouse, int ymouse)
{	
	switch (key){
		case 'w':
		if (user.y1 < 0.9 && user.y2 < 0.9)//tank tidak akan bisa melebihi garis atas
		{
			user.x1=user.x1;
			user.x2=user.x2;
			user.y1=user.y1 + 0.1;//agar dapat gerak ke atas, maka ditambah 0.1
			user.y2=user.y2 + 0.1;//agar dapat gerak ke atas, maka ditambah 0.1
		}
			break;
		case 'a':
		if(user.x1 > -0.9 && user.x2 > -0.9){//tank tidak akan bisa melebihi garis kiri
			user.x1=user.x1 - 0.1;//agar dapat gerak ke kiri, maka dikurangi 0.1
			user.x2=user.x2 - 0.1;//agar dapat gerak ke kiri, maka dikurangi 0.1
			user.y1=user.y1;
			user.y2=user.y2;
		}	
			break;
		case 's':
		if (user.y1 > -0.0 && user.y2 > -0.0)//batas untuk tank sampai tengah
		{
			user.x1=user.x1;
			user.x2=user.x2;
			user.y1=user.y1 -0.1; //agar dapat gerak ke bawah, maka dikurangi 0.1
			user.y2=user.y2 - 0.1;  //agar dapat gerak ke kiri, maka dikurangi 0.1
		}
			break;
		case 'd':
		if(user.x1 < 0.9 && user.x2 < 0.9){//tank tidak akan bisa melebihi garis kanan
			user.x1=user.x1 + 0.1; //agar dapat gerak ke kanan, maka ditambah 0.1
			user.x2=user.x2 + 0.1; //agar dapat gerak ke kiri, maka ditambah 0.1
			user.y1=user.y1;
			user.y2=user.y2;
		}
			break;

		case 'i':
		if (user2.y1 < 0.0 && user2.y2 < 0.0)//batas untuk tank sampai tengah
		{
			user2.x1=user2.x1;
			user2.x2=user2.x2;
			user2.y1=user2.y1 + 0.1; //agar dapat gerak ke kiri, maka ditambah 0.1
			user2.y2=user2.y2 + 0.1; //agar dapat gerak ke kiri, maka ditambah 0.1
		}
			break;
		case 'j':
		if(user2.x1 > -0.9 && user2.x2 > -0.9){ //tank tidak akan bisa melebihi garis kiri
			user2.x1=user2.x1 - 0.1; //agar dapat gerak ke kiri, maka dikurangi 0.1
			user2.x2=user2.x2 - 0.1; //agar dapat gerak ke kiri, maka dikurangi 0.1
			user2.y1=user2.y1;
			user2.y2=user2.y2;
		}	
			break;
		case 'k':
		if (user2.y1 > -0.9 && user2.y2 > -0.9)//tank tidak akan bisa melebihi garis bawah
		{
			user2.x1=user2.x1;
			user2.x2=user2.x2;
			user2.y1=user2.y1 -0.1;//agar dapat gerak ke kiri, maka dikurangi 0.1
			user2.y2=user2.y2 - 0.1;//agar dapat gerak ke kiri, maka dikurangi 0.1
		}
			break;
		case 'l':
		if(user2.x1 < 0.9 && user2.x2 < 0.9){//tank tidak akan bisa melebihi garis atas
			user2.x1=user2.x1 + 0.1; //agar dapat gerak ke kiri, maka ditambah 0.1
			user2.x2=user2.x2 + 0.1; //agar dapat gerak ke kiri, maka ditambah 0.1
			user2.y1=user2.y1;
			user2.y2=user2.y2;
		}
			break;

		case 'f':
			user.sedangMenembak = 1;
		break;
		case ';':
			user2.sedangMenembak = 1;
		break;
		case 'c': 
				exit(0);//jika menekan c, maka akan keluar 
		break;
		case 'y':
			pilih = 1;//game akan memulai
		break;
		case 'r':
			pilih = 0;//mengembalikan kondisi
			user.nyawa = 0;//mengembalikan kondisi
			user2.nyawa = 0;//mengembalikan kondisi
		break;

		default:
         break;
	}
}


int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutCreateWindow("Game Tank"); //tampilan atas
bentuk();//untuk memanggil prosedur gerak
glutDisplayFunc(display);//untuk menampilkan objek
glutPostRedisplay();//untuk menampilkan ulang objek
glutIdleFunc(looping);
glutMainLoop();//untuk memanggil looping
    return 0;
}

void looping(){//agar proses dapat diulang kembali
if(user.nyawa == 1 || user2.nyawa == 1){//nyawa player di set 1
glutDisplayFunc(gameover);//untuk menampilkan objek
 }else if(pilih == 0){//jika mengulang kembali maka akan di set menjadi default
 glutDisplayFunc(menu);
 }else{
glutDisplayFunc(display);//untuk menampilkan objek 	
 }
glutPostRedisplay();//untuk menampilkan ulang objek
glutKeyboardFunc(keys);//agar dapat bisa digerakkan
reDraw();//untuk menggambar ulang
pthread_create(&player[0], NULL,tembak1, NULL);//thread di masukkan saat player 1 menembak
pthread_create(&player[1], NULL,tembak2, NULL);//thread di masukkan saat player 2 menembak

for (int i = 0; i < 2; ++i)
 {
 	pthread_join(player[i],NULL);
 } 
 interaksi();
}
