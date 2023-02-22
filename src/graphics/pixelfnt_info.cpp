#include "pixelfnt.h"

const CharInfo pixelfnt_chars[] = {
  {.id=32, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=4 },
  {.id=33, .x=80, .y=38, .width=4, .height=11, .xoffset=-1, .yoffset=3, .xadvance=4 },
  {.id=34, .x=90, .y=61, .width=5, .height=4, .xoffset=-1, .yoffset=3, .xadvance=5 },
  {.id=35, .x=98, .y=38, .width=7, .height=11, .xoffset=-1, .yoffset=3, .xadvance=7 },
  {.id=36, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=37, .x=0, .y=50, .width=10, .height=10, .xoffset=-1, .yoffset=4, .xadvance=10 },
  {.id=38, .x=118, .y=26, .width=10, .height=11, .xoffset=-1, .yoffset=3, .xadvance=10 },
  {.id=39, .x=96, .y=61, .width=3, .height=4, .xoffset=-1, .yoffset=3, .xadvance=3 },
  {.id=40, .x=119, .y=38, .width=4, .height=10, .xoffset=-1, .yoffset=4, .xadvance=4 },
  {.id=41, .x=124, .y=38, .width=4, .height=10, .xoffset=-1, .yoffset=4, .xadvance=4 },
  {.id=42, .x=62, .y=61, .width=5, .height=5, .xoffset=-1, .yoffset=5, .xadvance=5 },
  {.id=43, .x=9, .y=61, .width=9, .height=9, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=44, .x=57, .y=61, .width=4, .height=6, .xoffset=-1, .yoffset=10, .xadvance=4 },
  {.id=45, .x=107, .y=61, .width=6, .height=3, .xoffset=-1, .yoffset=9, .xadvance=6 },
  {.id=46, .x=85, .y=61, .width=4, .height=4, .xoffset=-1, .yoffset=10, .xadvance=4 },
  {.id=47, .x=59, .y=0, .width=7, .height=12, .xoffset=-1, .yoffset=3, .xadvance=7 },
  {.id=48, .x=79, .y=0, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=49, .x=88, .y=0, .width=6, .height=11, .xoffset=-1, .yoffset=3, .xadvance=7 },
  {.id=50, .x=95, .y=0, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=51, .x=104, .y=0, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=8 },
  {.id=52, .x=113, .y=0, .width=9, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=53, .x=0, .y=14, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=54, .x=9, .y=14, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=55, .x=18, .y=14, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=56, .x=27, .y=14, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=57, .x=36, .y=14, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=58, .x=124, .y=50, .width=4, .height=9, .xoffset=-1, .yoffset=5, .xadvance=4 },
  {.id=59, .x=85, .y=38, .width=4, .height=11, .xoffset=-1, .yoffset=5, .xadvance=4 },
  {.id=60, .x=19, .y=61, .width=6, .height=9, .xoffset=-1, .yoffset=5, .xadvance=6 },
  {.id=61, .x=68, .y=61, .width=8, .height=5, .xoffset=-1, .yoffset=7, .xadvance=8 },
  {.id=62, .x=26, .y=61, .width=6, .height=9, .xoffset=-1, .yoffset=5, .xadvance=6 },
  {.id=63, .x=90, .y=38, .width=7, .height=11, .xoffset=-1, .yoffset=3, .xadvance=8 },
  {.id=64, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=65, .x=0, .y=26, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=66, .x=9, .y=26, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=67, .x=18, .y=26, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=8 },
  {.id=68, .x=27, .y=26, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=69, .x=36, .y=26, .width=7, .height=11, .xoffset=-1, .yoffset=3, .xadvance=8 },
  {.id=70, .x=44, .y=26, .width=7, .height=11, .xoffset=-1, .yoffset=3, .xadvance=8 },
  {.id=71, .x=52, .y=26, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=72, .x=61, .y=26, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=73, .x=70, .y=26, .width=6, .height=11, .xoffset=-1, .yoffset=3, .xadvance=7 },
  {.id=74, .x=8, .y=0, .width=8, .height=13, .xoffset=-2, .yoffset=3, .xadvance=8 },
  {.id=75, .x=119, .y=14, .width=9, .height=11, .xoffset=-1, .yoffset=3, .xadvance=10 },
  {.id=76, .x=77, .y=26, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=7 },
  {.id=77, .x=86, .y=26, .width=12, .height=11, .xoffset=-1, .yoffset=3, .xadvance=13 },
  {.id=78, .x=99, .y=26, .width=9, .height=11, .xoffset=-1, .yoffset=3, .xadvance=10 },
  {.id=79, .x=109, .y=26, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=80, .x=0, .y=38, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=81, .x=17, .y=0, .width=8, .height=13, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=82, .x=9, .y=38, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=83, .x=18, .y=38, .width=7, .height=11, .xoffset=-1, .yoffset=3, .xadvance=8 },
  {.id=84, .x=26, .y=38, .width=8, .height=11, .xoffset=-2, .yoffset=3, .xadvance=7 },
  {.id=85, .x=35, .y=38, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=86, .x=44, .y=38, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=87, .x=106, .y=38, .width=12, .height=10, .xoffset=-1, .yoffset=3, .xadvance=13 },
  {.id=88, .x=53, .y=38, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=89, .x=62, .y=38, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=90, .x=71, .y=38, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=91, .x=31, .y=0, .width=4, .height=13, .xoffset=-1, .yoffset=3, .xadvance=4 },
  {.id=36, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=92, .x=36, .y=0, .width=4, .height=13, .xoffset=-1, .yoffset=3, .xadvance=4 },
  {.id=94, .x=77, .y=61, .width=7, .height=5, .xoffset=-1, .yoffset=4, .xadvance=7 },
  {.id=95, .x=100, .y=61, .width=6, .height=3, .xoffset=-1, .yoffset=13, .xadvance=5 },
  {.id=96, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=97, .x=11, .y=50, .width=8, .height=9, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=98, .x=45, .y=14, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=99, .x=20, .y=50, .width=7, .height=9, .xoffset=-1, .yoffset=5, .xadvance=7 },
  {.id=100, .x=54, .y=14, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=101, .x=28, .y=50, .width=8, .height=9, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=102, .x=63, .y=14, .width=7, .height=11, .xoffset=-1, .yoffset=3, .xadvance=7 },
  {.id=103, .x=41, .y=0, .width=8, .height=12, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=104, .x=71, .y=14, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=9 },
  {.id=105, .x=123, .y=0, .width=4, .height=11, .xoffset=-1, .yoffset=3, .xadvance=5 },
  {.id=106, .x=0, .y=0, .width=7, .height=13, .xoffset=-2, .yoffset=3, .xadvance=7 },
  {.id=107, .x=80, .y=14, .width=8, .height=11, .xoffset=-1, .yoffset=3, .xadvance=8 },
  {.id=108, .x=89, .y=14, .width=4, .height=11, .xoffset=-1, .yoffset=3, .xadvance=5 },
  {.id=109, .x=37, .y=50, .width=12, .height=9, .xoffset=-1, .yoffset=5, .xadvance=13 },
  {.id=110, .x=50, .y=50, .width=8, .height=9, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=111, .x=59, .y=50, .width=8, .height=9, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=112, .x=94, .y=14, .width=8, .height=11, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=113, .x=103, .y=14, .width=8, .height=11, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=114, .x=68, .y=50, .width=7, .height=9, .xoffset=-1, .yoffset=5, .xadvance=7 },
  {.id=115, .x=76, .y=50, .width=7, .height=9, .xoffset=-1, .yoffset=5, .xadvance=8 },
  {.id=116, .x=112, .y=14, .width=6, .height=11, .xoffset=-1, .yoffset=3, .xadvance=7 },
  {.id=117, .x=84, .y=50, .width=8, .height=9, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=118, .x=93, .y=50, .width=8, .height=9, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=119, .x=102, .y=50, .width=12, .height=9, .xoffset=-1, .yoffset=5, .xadvance=13 },
  {.id=120, .x=115, .y=50, .width=8, .height=9, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=121, .x=50, .y=0, .width=8, .height=12, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=122, .x=0, .y=61, .width=8, .height=9, .xoffset=-1, .yoffset=5, .xadvance=9 },
  {.id=123, .x=67, .y=0, .width=5, .height=12, .xoffset=-1, .yoffset=3, .xadvance=5 },
  {.id=124, .x=26, .y=0, .width=4, .height=13, .xoffset=-1, .yoffset=3, .xadvance=3 },
  {.id=125, .x=73, .y=0, .width=5, .height=12, .xoffset=-1, .yoffset=3, .xadvance=5 },
  {.id=126, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=127, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=128, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=129, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=130, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=131, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=132, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=133, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=134, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=135, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=136, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=137, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=138, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=139, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=140, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=141, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=142, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=143, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=144, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=145, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=146, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=147, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=148, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=149, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=150, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=151, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=152, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=153, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=154, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=155, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=156, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=157, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=158, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=159, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=160, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=161, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=162, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=163, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=164, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=165, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=166, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=167, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=168, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=169, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=170, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=171, .x=33, .y=61, .width=11, .height=9, .xoffset=-1, .yoffset=5, .xadvance=11 },
  {.id=172, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=173, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=174, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=175, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=176, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=177, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=178, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=179, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=180, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=181, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=182, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=183, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=184, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=185, .x=0, .y=0, .width=0, .height=0, .xoffset=0, .yoffset=0, .xadvance=0 },
  {.id=186, .x=114, .y=59, .width=11, .height=9, .xoffset=-1, .yoffset=5, .xadvance=11 }, // special for empty black space
  {.id=187, .x=45, .y=61, .width=11, .height=9, .xoffset=-1, .yoffset=5, .xadvance=11 }
};