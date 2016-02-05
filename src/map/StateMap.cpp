#include "StateMap.h"
#include "Graphics.h"
#include "render/Text.h"
#include "piaf/Archive.h"


#define STATEMAP WalrusRPG::States::StateMap

using namespace WalrusRPG;
using namespace WalrusRPG::Graphics;
using WalrusRPG::Utils::Rect;
using WalrusRPG::PIAF::Archive;
using WalrusRPG::PIAF::File;
using WalrusRPG::Graphics::Texture;

namespace
{

    // x, y, width, height, xoffset, yoffset
    const int16_t haeccity[][6] = {
        ///*32*/{0, 0, 0, 0},
/*33*/{0, 0, 1, 6, 0, 3},
/*34*/{1, 0, 3, 2, 0, 3},
/*35*/{4, 0, 5, 5, 0, 3},
/*36*/{9, 0, 5, 7, 0, 3},
/*37*/{0, 6, 8, 6, 0, 3},
/*38*/{14, 0, 5, 6, 0, 3},
/*39*/{1, 2, 1, 2, 0, 3},
/*40*/{19, 0, 2, 8, 0, 2},
/*41*/{8, 7, 2, 8, 0, 2},
/*42*/{0, 12, 5, 5, 0, 2},
/*43*/{5, 12, 3, 3, 0, 5},
/*44*/{1, 4, 2, 2, 0, 8},
/*45*/{2, 2, 2, 2, 0, 5},
/*46*/{8, 5, 1, 1, 0, 8},
/*47*/{10, 7, 3, 7, 0, 3},
/*48*/{13, 7, 4, 6, 0, 3},
/*49*/{17, 6, 2, 6, 0, 3},
/*50*/{21, 0, 4, 6, 0, 3},
/*51*/{25, 0, 3, 6, 0, 3},
/*52*/{28, 0, 5, 6, 0, 3},
/*53*/{33, 0, 3, 6, 0, 3},
/*54*/{36, 0, 4, 6, 0, 3},
/*55*/{40, 0, 3, 6, 0, 3},
/*56*/{43, 0, 4, 6, 0, 3},
/*57*/{47, 0, 4, 6, 0, 3},
/*58*/{51, 0, 1, 5, 0, 4},
/*59*/{52, 0, 2, 6, 0, 4},
/*60*/{54, 0, 3, 5, 0, 4},
/*61*/{57, 0, 3, 3, 0, 5},
/*62*/{60, 0, 3, 5, 0, 4},
/*63*/{57, 3, 3, 6, 0, 3},
/*64*/{19, 8, 5, 6, 0, 3},
/*65*/{13, 13, 4, 6, 0, 3},
/*66*/{0, 17, 4, 6, 0, 3},
/*67*/{4, 17, 4, 6, 0, 3},
/*68*/{8, 15, 4, 6, 0, 3},
/*69*/{24, 6, 3, 6, 0, 3},
/*70*/{27, 6, 3, 6, 0, 3},
/*71*/{30, 6, 4, 6, 0, 3},
/*72*/{34, 6, 4, 6, 0, 3},
/*73*/{12, 14, 1, 6, 0, 3},
/*74*/{38, 6, 3, 7, 0, 3},
/*75*/{24, 12, 4, 6, 0, 3},
/*76*/{17, 14, 3, 6, 0, 3},
/*77*/{28, 12, 5, 6, 0, 3},
/*78*/{13, 19, 4, 6, 0, 3},
/*79*/{0, 23, 4, 6, 0, 3},
/*80*/{4, 23, 4, 6, 0, 3},
/*81*/{8, 21, 5, 7, 0, 3},
/*82*/{20, 14, 4, 6, 0, 3},
/*83*/{33, 12, 4, 6, 0, 3},
/*84*/{41, 6, 3, 6, 0, 3},
/*85*/{44, 6, 4, 6, 0, 3},
/*86*/{48, 6, 5, 6, 0, 3},
/*87*/{63, 0, 5, 6, 0, 3},
/*88*/{68, 0, 5, 6, 0, 3},
/*89*/{73, 0, 5, 6, 0, 3},
/*90*/{53, 6, 4, 6, 0, 3},
/*91*/{60, 5, 2, 8, 0, 2},
/*92*/{41, 12, 3, 7, 0, 3},
/*93*/{24, 18, 2, 8, 0, 2},
/*94*/{13, 25, 5, 3, 0, 2},
/*95*/{3, 5, 4, 1, 0, 10},
/*96*/{17, 12, 2, 2, 1, 1},
/*97*/{17, 20, 4, 5, 0, 4},
/*98*/{18, 25, 4, 7, 0, 2},
/*99*/{21, 20, 3, 5, 0, 4},
/*100*/{0, 29, 4, 7, 0, 2},
/*101*/{4, 29, 4, 5, 0, 4},
/*102*/{8, 28, 4, 8, 0, 2},
/*103*/{4, 34, 4, 6, 0, 4},
/*104*/{0, 36, 4, 7, 0, 2},
/*105*/{12, 28, 1, 7, 0, 2},
/*106*/{13, 28, 2, 8, 0, 2},
/*107*/{26, 18, 4, 7, 0, 2},
/*108*/{15, 28, 2, 7, 0, 2},
/*109*/{30, 18, 5, 5, 0, 4},
/*110*/{35, 18, 4, 5, 0, 4},
/*111*/{37, 13, 4, 5, 0, 4},
/*112*/{44, 12, 4, 6, 0, 4},
/*113*/{48, 12, 4, 6, 0, 4},
/*114*/{52, 12, 3, 5, 0, 4},
/*115*/{55, 12, 4, 5, 0, 4},
/*116*/{78, 0, 3, 6, 0, 3},
/*117*/{81, 0, 4, 5, 0, 4},
/*118*/{85, 0, 3, 5, 0, 4},
/*119*/{88, 0, 5, 5, 0, 4},
/*120*/{93, 0, 3, 5, 0, 4},
/*121*/{96, 0, 4, 6, 0, 4},
/*122*/{81, 5, 3, 5, 0, 4},
/*123*/{62, 6, 3, 8, 0, 2},
/*124*/{12, 35, 1, 7, 0, 3},
/*125*/{4, 40, 3, 8, 0, 2},
/*126*/{7, 40, 5, 2, 0, 5},
/*127*/{65, 6, 5, 5, 0, 4},
        /*uncovered by littera for now*/
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
/*338*/{22, 26, 6, 6, 0, 3},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
/*339*/{32, 25, 6, 5, 0, 4},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {7, 42, 5, 8, 0, 1},
        {0, 0, 0, 0, 0, 0},
/*161*/{0, 48, 1, 6, 0, 4},
/*162*/{1, 48, 4, 7, 0, 3},
/*163*/{32, 30, 4, 6, 0, 3},
/*164*/{21, 35, 6, 4, 0, 3},
/*165*/{27, 34, 5, 6, 0, 3},
/*166*/{0, 54, 1, 7, 0, 3},
/*167*/{21, 39, 3, 7, 0, 3},
/*168*/{14, 6, 3, 1, 1, 2},
/*169*/{36, 30, 6, 7, 0, 2},
/*170*/{38, 25, 4, 5, 0, 2},
/*171*/{16, 42, 5, 3, 0, 5},
/*172*/{35, 23, 4, 2, 0, 5},
/*173*/{15, 35, 2, 2, 0, 5},
/*174*/{84, 5, 7, 8, 0, 2},
/*175*/{54, 5, 3, 1, 0, 2},
/*176*/{16, 45, 3, 3, 0, 2},
/*177*/{12, 47, 3, 5, 0, 4},
/*178*/{5, 50, 2, 4, 0, 3},
/*179*/{7, 50, 2, 4, 0, 3},
/*180*/{15, 37, 2, 2, 1, 1},
/*181*/{75, 10, 5, 6, 0, 4},
/*182*/{32, 36, 4, 7, 0, 3},
/*183*/{8, 6, 1, 1, 0, 6},
/*184*/{5, 48, 2, 2, 1, 9},
/*185*/{75, 6, 2, 4, 0, 3},
/*186*/{24, 40, 4, 5, 0, 2},
/*187*/{70, 13, 5, 3, 0, 5},
/*188*/{100, 0, 7, 6, 0, 3},
/*189*/{107, 0, 6, 6, 0, 3},
/*190*/{113, 0, 7, 6, 0, 3},
/*191*/{9, 50, 3, 6, 0, 4},
/*192*/{1, 55, 4, 9, 0, 0},
/*193*/{5, 54, 4, 9, 0, 0},
/*194*/{28, 40, 4, 9, 0, 0},
/*195*/{15, 48, 4, 9, 0, 0},
/*196*/{9, 56, 4, 8, 0, 1},
/*197*/{5, 63, 4, 9, 0, 0},
/*198*/{19, 46, 6, 6, 0, 3},
/*199*/{0, 64, 4, 8, 0, 3},
/*200*/{25, 45, 3, 9, 0, 0},
/*201*/{19, 52, 3, 9, 0, 0},
/*202*/{13, 57, 3, 9, 0, 0},
/*203*/{9, 64, 3, 8, 0, 1},
/*204*/{16, 57, 2, 9, 0, 0},
/*205*/{22, 52, 2, 9, 0, 0},
/*206*/{46, 23, 3, 9, -1, 0},
/*207*/{61, 18, 3, 8, -1, 1},
/*208*/{49, 24, 5, 6, 0, 3},
/*209*/{54, 24, 4, 9, 0, 0},
/*210*/{42, 32, 4, 9, 0, 0},
/*211*/{36, 37, 4, 9, 0, 0},
/*212*/{32, 43, 4, 9, 0, 0},
/*213*/{28, 49, 4, 9, 0, 0},
/*214*/{24, 54, 4, 8, 0, 1},
/*215*/{12, 52, 3, 3, 0, 5},
/*216*/{18, 61, 4, 6, 0, 3},
/*217*/{12, 66, 4, 9, 0, 0},
/*218*/{0, 72, 4, 9, 0, 0},
/*219*/{4, 72, 4, 9, 0, 0},
/*220*/{8, 72, 4, 8, 0, 1},
/*221*/{46, 32, 5, 9, 0, 0},
/*222*/{80, 10, 4, 6, 0, 3},
/*223*/{91, 5, 4, 6, 0, 3},
/*224*/{120, 0, 4, 8, 0, 1},
/*225*/{95, 6, 4, 8, 0, 1},
/*226*/{84, 13, 4, 8, 0, 1},
/*227*/{64, 19, 4, 8, 0, 1},
/*228*/{58, 26, 4, 7, 0, 2},
/*229*/{68, 19, 4, 8, 0, 1},
/*230*/{72, 16, 5, 5, 0, 4},
/*231*/{77, 16, 4, 7, 0, 4},
/*232*/{72, 21, 4, 8, 0, 1},
/*233*/{62, 27, 4, 8, 0, 1},
/*234*/{51, 33, 4, 8, 0, 1},
/*235*/{55, 33, 4, 7, 0, 2},
/*236*/{16, 66, 2, 8, 0, 1},
/*237*/{22, 61, 2, 8, 0, 1},
/*238*/{18, 67, 3, 8, -1, 1},
/*239*/{59, 33, 3, 7, -1, 2},
/*240*/{66, 27, 4, 7, 0, 2},
/*241*/{88, 13, 4, 8, 0, 1},
/*242*/{99, 6, 4, 8, 0, 1},
/*243*/{103, 6, 4, 8, 0, 1},
/*244*/{107, 6, 4, 8, 0, 1},
/*245*/{111, 6, 4, 8, 0, 1},
/*246*/{115, 6, 4, 7, 0, 2},
/*247*/{81, 16, 3, 5, 0, 4},
/*248*/{124, 0, 4, 5, 0, 4},
/*249*/{128, 0, 4, 8, 0, 1},
/*250*/{124, 5, 4, 8, 0, 1},
/*251*/{119, 8, 4, 8, 0, 1},
/*252*/{92, 14, 4, 7, 0, 2},
/*253*/{96, 14, 4, 9, 0, 1},
/*254*/{81, 21, 3, 8, 0, 2},
/*255*/{76, 23, 4, 8, 0, 2}
    };

    const int8_t haeccity_kernings[][3] = {
        {66, 74, -1},
        {67, 74, -1},
        {68, 74, -1},
        {70, 44, -2},
        {70, 46, -1},
        {70, 59, -1},
        {70, 74, -2},
        {71, 74, -1},
        {76, 34, -1},
        {76, 39, -1},
        {76, 84, -1},
        {76, 86, -1},
        {76, 87, -1},
        {76, 89, -1},
        {76, 121, -1},
        {79, 74, -1},
        {80, 44, -2},
        {80, 46, -1},
        {80, 59, -1},
        {80, 74, -1},
        {80, 88, -1},
        {80, 97, -1},
        {84, 44, -1},
        {84, 46, -1},
        {84, 59, -1},
        {84, 74, -1},
        {84, 97, -1},
        {86, 44, -2},
        {86, 46, -1},
        {86, 59, -1},
        {86, 74, -1},
        {86, 97, -1},
        {87, 59, -1},
        {87, 74, -1},
        {89, 44, -2},
        {89, 46, -1},
        {89, 59, -1},
        {89, 74, -1},
        {98, 44, -1},
        {98, 106, -1},
        {101, 44, -1},
        {101, 97, -1},
        {101, 106, -1},
        {102, 34, 1},
        {102, 39, 1},
        {102, 44, -1},
        {102, 97, -1},
        {107, 97, -1},
        {107, 102, -1},
        {107, 103, -1},
        {107, 115, -1},
        {107, 116, -1},
        {107, 118, -1},
        {107, 121, -1},
        {108, 97, -1},
        {108, 102, -1},
        {108, 103, -1},
        {108, 115, -1},
        {108, 116, -1},
        {108, 121, -1},
        {111, 44, -1},
        {111, 106, -1},
        {112, 44, -1},
        {112, 106, -1},
        {114, 44, -2},
        {114, 46, -1},
        {114, 97, -1},
        {114, 100, -1},
        {114, 106, -1},
        {115, 44, -1},
        {115, 102, -1},
        {115, 106, -1},
        {115, 116, -1},
        {118, 44, -1},
        {118, 106, -1},
        {119, 44, -1},
        {119, 106, -1},
    };

    void print_debug_camera_data(const Camera &camera)
    {
        Text::print_format(0, 8, "CAM : X : %d Y: %d", camera.get_x(), camera.get_y());
    }

    void print_debug_map_data(const Map &map)
    {
        Text::print_format(0, 16, "MAP : W: %d, H:%d", map.get_width(), map.get_height());
    }

}

void STATEMAP::putchar_haeccity(unsigned char c, unsigned x, unsigned y)
{
        if(c <= 32) return;
        c -= 33;
        Rect letter{haeccity[c][0], haeccity[c][1], haeccity[c][2], haeccity[c][3]};
        put_sprite(tex_haeccity, x + haeccity[c][4], y + haeccity[c][5], letter);        
}

void STATEMAP::putchar_haeccity_tint(unsigned char c, unsigned x, unsigned y, const Pixel& col)
{
        if(c <= 32) return;
        c -= 33;
        Rect letter{haeccity[c][0], haeccity[c][1], haeccity[c][2], haeccity[c][3]};
        put_sprite_tint(tex_haeccity, x + haeccity[c][4], y + haeccity[c][5], letter, col);  
}


void STATEMAP::print_haeccity(const char *str, unsigned x, unsigned y, const Pixel& col = White)
{
    const bool must_tint = (col != White);
    for(unsigned i = 0; str[i] && x < 320; i++)
    {
        unsigned char c = str[i];
        if(c < 32) continue;
        if(c == 32) {x+=2; continue;}
        // printf("%c = %d\n", c, c);
        if(must_tint)
            putchar_haeccity_tint(c, x, y, col);
        else
            putchar_haeccity(c, x, y);
        x += haeccity[c-33][2] +1;
    }
}

STATEMAP::StateMap(int x, int y, Map &map) : camera(x, y), map(map), arc_haeccity("data/haeccity.wrf"), tex_haeccity(arc_haeccity.get("haeccity"))
{
}

void STATEMAP::update(unsigned dt)
{
    camera.update(dt);
}

void STATEMAP::render(unsigned dt)
{
    // fill(Black);
    map.render(camera, dt);

    // print_debug_camera_data(camera);
    // print_debug_map_data(map);
    print_haeccity("Hello world! :D", 0, 0);
    print_haeccity("This isn't actually a utility nor built-ins functions.", 0, 9);
    print_haeccity("This is a quick prototype to see if variable-wdith fonts works.", 0, 18);
    print_haeccity("Builting it myself allows me to make it work on calc too.", 0, 27, Yellow);
    print_haeccity("( I wonder if a conditionnal to tint the text slows down a lot the process. )", 0, 36, Gray);
    print_haeccity("Oh well, I hope I'll get to do a pretty textbox like in games !", 0, 45);

    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            putchar_haeccity_tint(16*j + i+32, 6*i, 9*j + 54, Pixel(i*16, j*16, 255));
        }
    }
    
}
