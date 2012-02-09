/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-12-*-*-*-*-*-iso8859-15";
static const char normbordercolor[] = "#222222";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#CCCCCC";
static const char selbordercolor[]  = "#444444";
static const char selbgcolor[]      = "#222222";
static const char selfgcolor[]      = "#CC3333";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const Bool showbar           = False;    /* False means no bar */
static const Bool topbar            = False;    /* False means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */

/* tagging */
static const char *tags[] = { "net", "med", "cmd", "dev", "var" };

static const Rule rules[] = {
    /* class                    instance        title           tagmask     isfloating      monitor */
    { "feh",                    NULL,           NULL,           0,          True,           0 },
    { "Firefox",                NULL,           NULL,           1,          False,          0 },
    { "Firefox",                NULL,           "Descargas",    1,          True,           0 },
    { "MPlayer",                NULL,           NULL,           2,          True,           0 },
    { "Pcmanfm",                NULL,           NULL,           4,          False,          0 },
    { "Eclipse",                NULL,           NULL,           8,          False,          0 },
    { NULL,                     NULL,           "OpenOffice",   16,         True,           0 },
    { NULL,                     NULL,           "LibreOffice",  16,         False,          0 },
    { "Evince",                 NULL,           NULL,           16,         False,          0 },
    { "MuPDF",                  NULL,           NULL,           16,         False,          0 },
    { "Gimp",                   NULL,           NULL,           16,         True,           0 },
};

/* layout(s) */
static const float mfact        = 0.50;     /* factor of master area size [0.05..0.95] */
static const Bool resizehints   = False;    /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
    /* symbol   arrange function */
    { "[]=",    tile },     /* first entry is default */
    { "TTT",    bstack },
    { "###",    gaplessgrid },
    { "><>",    NULL },     /* no layout function means floating behavior */
    { "[M]",    monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                           KEY,    view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,               KEY,    toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,                 KEY,    tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask,     KEY,    toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *menucmd[] = {
    "dmenu_run", "-i", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor,
    "-sb", selbgcolor, "-sf", selfgcolor, "-p", "dmenu", "-b", NULL
};

static const char *termcmd[] = { "urxvtc", NULL };
static const char *navgcmd[] = { "firefox", NULL };
static const char *filecmd[] = { "pcmanfm", NULL };
static const char *mailcmd[] = { "urxvtc", "-e", "mutt", NULL };
static const char *editcmd[] = { "urxvtc", "-e", "vim", NULL };
static const char *shotcmd[] = { "scrot", "-mq10", NULL };
static const char *wshtcmd[] = { "scrot", "-sq10", NULL };
static const char *lockcmd[] = { "slock", NULL };
static const char *musicmd[] = { "urxvtc", "-e", "ncmpcpp", NULL };
static const char *mtogcmd[] = { "ncmpcpp", "toggle", NULL };
static const char *mprecmd[] = { "ncmpcpp", "prev", NULL };
static const char *mnexcmd[] = { "ncmpcpp", "next", NULL };
static const char *voltcmd[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };

#include "movestack.c"
static Key keys[] = {
    /* modifier             key                 function            argument */
    { MODKEY,               XK_space,           spawn,              {.v = menucmd } },
    { MODKEY,               XK_Return,          spawn,              {.v = termcmd } },
    { MODKEY,               XK_w,               spawn,              {.v = navgcmd } },
    { MODKEY,               XK_e,               spawn,              {.v = mailcmd } },
    { MODKEY,               XK_a,               spawn,              {.v = editcmd } },
    { MODKEY,               XK_s,               spawn,              {.v = lockcmd } },
    { MODKEY,               XK_d,               spawn,              {.v = filecmd } },
    { 0,                    0xff61,             spawn,              {.v = shotcmd } },
    { MODKEY,               0xff61,             spawn,              {.v = wshtcmd } },
    { 0,                    0x1008ff81,         spawn,              {.v = musicmd } },
    { 0,                    0x1008ff16,         spawn,              {.v = mprecmd } },
    { 0,                    0x1008ff14,         spawn,              {.v = mtogcmd } },
    { 0,                    0x1008ff17,         spawn,              {.v = mnexcmd } },
    { 0,                    0x1008ff12,         spawn,              {.v = voltcmd } },
    { MODKEY,               XK_m,               togglebar,          {0} },
    { MODKEY,               XK_j,               focusstack,         {.i = +1 } },
    { MODKEY,               XK_k,               focusstack,         {.i = -1 } },
    { MODKEY|ShiftMask,     XK_j,               movestack,          {.i = +1 } },
    { MODKEY|ShiftMask,     XK_k,               movestack,          {.i = -1 } },
    { MODKEY,               XK_h,               setmfact,           {.f = -0.05} },
    { MODKEY,               XK_l,               setmfact,           {.f = +0.05} },
    { MODKEY|ShiftMask,     XK_Return,          zoom,               {0} },
    { MODKEY,               XK_Tab,             view,               {0} },
    { MODKEY,               XK_q,               killclient,         {0} },
    { MODKEY,               XK_1,               setlayout,          {.v = &layouts[0]} },
    { MODKEY,               XK_2,               setlayout,          {.v = &layouts[1]} },
    { MODKEY,               XK_3,               setlayout,          {.v = &layouts[2]} },
    { MODKEY,               XK_4,               setlayout,          {.v = &layouts[3]} },
    { MODKEY,               XK_5,               setlayout,          {.v = &layouts[4]} },
    { MODKEY|ShiftMask,     XK_f,               togglefloating,     {0} },
    { MODKEY,               XK_p,               view,               {.ui = ~0 } },
    { MODKEY|ShiftMask,     XK_p,               tag,                {.ui = ~0 } },
    { MODKEY,               XK_comma,           focusmon,           {.i = -1 } },
    { MODKEY,               XK_period,          focusmon,           {.i = +1 } },
    { MODKEY|ShiftMask,     XK_comma,           tagmon,             {.i = -1 } },
    { MODKEY|ShiftMask,     XK_period,          tagmon,             {.i = +1 } },
    { MODKEY|ShiftMask,     XK_q,               quit,               {0} },
    TAGKEYS(                XK_z,               0)
    TAGKEYS(                XK_x,               1)
    TAGKEYS(                XK_c,               2)
    TAGKEYS(                XK_v,               3)
    TAGKEYS(                XK_b,               4)
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click            event mask  button      function        argument */
    { ClkLtSymbol,      0,          Button1,    setlayout,      {0} },
    { ClkLtSymbol,      0,          Button3,    setlayout,      {.v = &layouts[2]} },
    { ClkClientWin,     MODKEY,     Button1,    movemouse,      {0} },
    { ClkClientWin,     MODKEY,     Button3,    resizemouse,    {0} },
    { ClkTagBar,        0,          Button1,    view,           {0} },
    { ClkTagBar,        0,          Button3,    toggleview,     {0} },
    { ClkTagBar,        MODKEY,     Button1,    tag,            {0} },
    { ClkTagBar,        MODKEY,     Button3,    toggletag,      {0} },
};

/* vim: set expandtab sw=4 ts=4: */
