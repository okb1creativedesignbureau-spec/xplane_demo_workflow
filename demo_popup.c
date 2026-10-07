#include "XPLMPlugin.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include <stdio.h>
#include <string.h>

#ifndef IBM
#define IBM 1
#endif
#ifndef XPLM200
#define XPLM200 1
#endif

static XPLMWindowID g_window = NULL;

void draw_demo_popup(XPLMWindowID in_window_id, void * in_refcon) {
    int l, t, r, b;
    XPLMGetWindowGeometry(in_window_id, &l, &t, &r, &b);
    
    XPLMDrawTranslucentDarkBox(l, t, r, b);
    
    float white[]  = {1.0f, 1.0f, 1.0f};
    float yellow[] = {1.0f, 0.85f, 0.2f};
    float red[]    = {1.0f, 0.3f, 0.3f};

    XPLMDrawString(white,  l + 20, t - 30,  "OKB-1 CreativeDesignBureau - Scenery Demo", NULL, xplmFont_Proportional);
    XPLMDrawString(red,    l + 20, t - 55,  "DEMO VERSION NOTICE:", NULL, xplmFont_Basic);
    XPLMDrawString(white,  l + 20, t - 75,  "Thank you for trying out this demo airport area!", NULL, xplmFont_Basic);
    XPLMDrawString(white,  l + 20, t - 95,  "Please note that scenery coverage is restricted in this build.", NULL, xplmFont_Basic);
    
    XPLMDrawString(yellow, l + 20, t - 125, "Full expanded version available at our Ko-fi Shop:", NULL, xplmFont_Basic);
    XPLMDrawString(yellow, l + 20, t - 140, "https://ko-fi.com/okb1creativedesignbureau/shop", NULL, xplmFont_Basic);
    
    XPLMDrawTranslucentDarkBox(l + 130, b + 45, r - 130, b + 15);
    XPLMDrawString(white,  l + 165, b + 25, "[ Click Here to Dismiss ]", NULL, xplmFont_Basic);
}

int handle_click(XPLMWindowID in_window_id, int x, int y, XPLMMouseStatus in_mouse, void * in_refcon) {
    if (in_mouse == xplm_MouseDown) {
        if (g_window != NULL) {
            XPLMDestroyWindow(g_window);
            g_window = NULL;
        }
    }
    return 1;
}

void handle_key(XPLMWindowID in_window_id, char in_key, XPLMKeyFlags in_flags, char in_vkey, void * in_refcon, int losing_focus) {}

PLUGIN_API int XPluginStart(char * outName, char * outSig, char * outDesc) {
    strcpy(outName, "OKB-1 Demo Notification");
    strcpy(outSig, "okb1.scenery.demo.popup");
    strcpy(outDesc, "Shows a demo notice pop-up on scenery load");
    return 1;
}

PLUGIN_API void XPluginStop(void) {}

PLUGIN_API void XPluginEnable(void) {
    g_window = XPLMCreateWindow(300, 700, 800, 480, 1, draw_demo_popup, handle_key, handle_click, NULL);
}

PLUGIN_API void XPluginDisable(void) {
    if (g_window != NULL) {
        XPLMDestroyWindow(g_window);
        g_window = NULL;
    }
}

PLUGIN_API void XPluginReceiveMessage(int inFrom, int inMsg, void * inParam) {}