#include <Windows.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")
#define EKV Event.KeyEvent.wVirtualKeyCode 
typedef int i; typedef unsigned int ui; typedef INPUT_RECORD IR; typedef HANDLE H;
struct V { i x; i y; V():x(0), y(0) {} V(i x, i y):x(x), y(y) {} };
int main() { timeBeginPeriod(0); srand((ui)time(0));
H o = (H)::GetStdHandle(-11), input = (H)::GetStdHandle(-10);
SMALL_RECT ws = {0,0,70-1,35-1}, r = {0,0,70-1,35-1}; COORD bs={70,35}, bc={0, 0};
CHAR_INFO ob[70 * 35]; i gd=0; V ap=V(10, 10), s[100], sd(-1, 0);
DWORD noe, noer; IR* eb; ui ct=timeGetTime(), pt=ct, et=0, msm=100, mt=0, sl=1;
for(ui ii=0; ii<sl; ++ii) {s[ii]=V(70/2,35/2);}
::SetConsoleWindowInfo(o, 1, &ws); ::SetConsoleScreenBufferSize(o, bs);
while (!gd) {pt=ct; ct=timeGetTime(); et=ct-pt;
for (i ii=0; ii<70*35; ++ii) {ob[ii].Char.AsciiChar=32; ob[ii].Attributes=0;}
::GetNumberOfConsoleInputEvents(input, &noe);
if(noe){eb=(IR*)malloc(sizeof(IR)*noe); ReadConsoleInput(input, eb, noe, &noer);}
for(ui ii = 0; ii < noer; ++ii){if (eb[ii].EventType == 1){
if(eb[ii].EKV==37) if(!(sd.x==1 && sd.y==0)){sd.x=-1; sd.y=0;} if(eb[ii].EKV==39) if(!(sd.x==-1 && sd.y==0)){sd.x=1; sd.y=0;}
if(eb[ii].EKV==38) if(!(sd.x==0 && sd.y==1)){sd.x=0; sd.y=-1;}if(eb[ii].EKV==40) if(!(sd.x==0 && sd.y==-1)){sd.x=0; sd.y=1;}}}
if(noe>0){free(eb);}if((mt+=et) > msm){for(i ii=sl-1; ii>0; --ii)
{s[ii].x=s[ii - 1].x; s[ii].y=s[ii-1].y;} s[0].x+=sd.x; s[0].y+=sd.y; mt=0;}
for (ui ii = 1; ii < sl - 1; ++ii) { if (s[0].x == s[ii].x && s[0].y == s[ii].y) {gd=1;}}
if (s[0].x<0 || s[0].x>70-1 || s[0].y<0 || s[0].y>35-1) {break;}
if (s[0].x == ap.x && s[0].y == ap.y){                
while (true) { i fgs=1; ap.x = rand() % 70; ap.y = rand() % 35;
for (ui ii = 0; ii < sl; ++ii) { if (s[ii].x == ap.x && s[ii].y == ap.y) {fgs=0;}}
if (fgs) { break; }} s[sl++] = V(s[sl - 1].x, s[sl - 1].y);
msm -= (msm < 50) ? 0 : 10;} ob[ap.y * 70 + ap.x].Char.AsciiChar = 64;
ob[ap.y * 70 + ap.x].Attributes = 4; for (ui ii = 0; ii < sl; ++ii) {
ob[s[ii].y * 70 + s[ii].x].Char.AsciiChar = 35; ob[s[ii].y * 70 + s[ii].x].Attributes = 2;}                
::WriteConsoleOutputA(o, ob, bs, bc, &r);} timeEndPeriod(0);return 0;}