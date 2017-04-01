/* See LICENSE file for copyright and license details. */

#define NUMCOLORS 13

/* appearance */
static const char font[ ] = "-*-xbmicons-medium-r-*-*-12-*-*-*-*-*-*-*" ","
                            "-*-terminus-medium-r-*-*-12-*-*-*-*-*-*-*";
static const char colors[NUMCOLORS][ColLast][9] = {
// border foreground background
  { "#282a2e", "#5b626c", "#1d1f21" }, // 1 = normal (grey on black)
  { "#f0c674", "#c5c8c6", "#1d1f21" }, // 2 = selected (white on black)
  { "#dc322f", "#1d1f21", "#f0c674" }, // 3 = urgent (black on yellow)
  { "#282a2e", "#282a2e", "#1d1f21" }, // 4 = darkgrey on black (triangle)
  { "#282a2e", "#1d1f21", "#282a2e" }, // 5 = black on darkgrey (triangle)
  { "#282a2e", "#b294bb", "#282a2e" }, // 6 = magenta on darkgrey
  { "#282a2e", "#cc6666", "#1d1f21" }, // 7 = red on black
  { "#282a2e", "#b5bd68", "#1d1f21" }, // 8 = green on black
  { "#282a2e", "#81a2be", "#282a2e" }, // 9 = blue on darkgrey
  { "#282a2e", "#f0c674", "#1d1f21" }, // A = yellow on black
  { "#282a2e", "#f0c674", "#282a2e" }, // B = yellow on darkgrey
  { "#282a2e", "#de935f", "#1d1f21" }, // C = orange on black
  { "#282a2e", "#8abeb7", "#282a2e" }, // D = cyan on darkgrey
};
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gap pixel between windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */

/* tagging */
static const char *tags[ ] = { "\uE000", "\uE001", "\uE008", "\uE002", "\uE006", "\uE007" };

static const Rule rules[] = {
    /* class                        instance    title           tagmask     isfloating  monitor */
    { "feh",                        NULL,       NULL,           0,          True,       0 },
    { "Firefox",                    NULL,       NULL,           1,          False,      0 },
    { "Pale moon",                  NULL,       NULL,           1,          False,      0 },
    { "mpv",                        NULL,       NULL,           4,          True,       0 },
    { "Spotify",                    NULL,       NULL,           4,          False,      0 },
    { "Pcmanfm",                    NULL,       NULL,           8,          False,      0 },
    { "VirtualBox",                 NULL,       NULL,           8,          True,       0 },
    { "Java",                       "java",     "Eclipse",      16,         True,       0 },
    { "Eclipse",                    NULL,       NULL,           16,         False,      0 },
    { NULL,                         NULL,       "LibreOffice",  32,         False,      0 },
    { "libreoffice-calc",           NULL,       NULL,           32,         False,      0 },
    { "libreoffice-impress",        NULL,       NULL,           32,         False,      0 },
    { "libreoffice-startcenter",    NULL,       NULL,           32,         False,      0 },
    { "libreoffice-writer",         NULL,       NULL,           32,         False,      0 },
    { "Zathura",                    NULL,       NULL,           32,         False,      0 },
    { "Gimp",                       NULL,       NULL,           32,         False,      0 }
};


/* layout(s) */
static const float mfact      = 0.50;   /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;      /* number of clients in master area */
static const Bool resizehints = False;  /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
  /* symbol     arrange function */
  { "\uE019 \uE009 \uE019",    tile },    /* first entry is default */
  { "\uE019 \uE00C \uE019",    bstack },
  { "\uE019 \uE00D \uE019",    gaplessgrid },
  { "\uE019 \uE00B \uE019",    monocle },
  { "\uE019 \uE00A \uE019",    NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char *[ ]) { "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[ ]      = { "dmenu_run", "-fn", "Terminus-9", "-nb", colors[0][ColBG], "-nf", colors[1][ColFG], "-sb", colors[2][ColBG], "-sf", colors[2][ColFG], NULL };
static const char *termcmd[ ]       = { "urxvtc", NULL };
static const char scratchpadname[ ] = "scratchpad";
static const char *scratchpadcmd[ ] = { "urxvtc", "-name", scratchpadname, "-geometry", "100x25", NULL };
static const char *navgcmd[ ]       = { "palemoon", NULL };
static const char *filecmd[ ]       = { "pcmanfm", NULL };
static const char *mailcmd[ ]       = { "urxvtc", "-e", "mutt", NULL };
static const char *shotcmd[ ]       = { "scrot", "-mq10", NULL };
static const char *lockcmd[ ]       = { "slock", NULL };

#include "push.c"
static Key keys[] = {
    /* modifier             key                 function            argument */
    { MODKEY,               XK_space,           spawn,              {.v = dmenucmd      } },
    { MODKEY,               XK_Return,          spawn,              {.v = termcmd       } },
    { MODKEY,               XK_s,               togglescratch,      {.v = scratchpadcmd } },
    { MODKEY,               XK_w,               spawn,              {.v = navgcmd       } },
    { MODKEY,               XK_e,               spawn,              {.v = mailcmd       } },
    { MODKEY|ShiftMask,     XK_l,               spawn,              {.v = lockcmd       } },
    { MODKEY,               XK_d,               spawn,              {.v = filecmd       } },
    { 0,                    0xff61,             spawn,              {.v = shotcmd       } },
    { MODKEY,               XK_m,               togglebar,          {0} },
    { MODKEY,               XK_j,               focusstack,         {.i = +1 } },
    { MODKEY,               XK_k,               focusstack,         {.i = -1 } },
    { MODKEY|ShiftMask,     XK_j,               pushdown,           {.i = +1 } },
    { MODKEY|ShiftMask,     XK_k,               pushup,             {.i = -1 } },
    { MODKEY,               XK_i,               incnmaster,         {.i = +1 } },
    { MODKEY,               XK_o,               incnmaster,         {.i = -1 } },
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
    { MODKEY,               XK_0,               setlayout,          {0} },
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
    TAGKEYS(                XK_n,               5)
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click            event mask  button      function        argument */
    { ClkLtSymbol,      0,          Button1,    setlayout,      {0} },
    { ClkLtSymbol,      0,          Button3,    setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,      0,          Button2,    zoom,           {0} },
    { ClkStatusText,    0,          Button2,    spawn,          {.v = termcmd } },
    { ClkClientWin,     MODKEY,     Button1,    movemouse,      {0} },
    { ClkClientWin,     MODKEY,     Button2,    togglefloating, {0} },
    { ClkClientWin,     MODKEY,     Button3,    resizemouse,    {0} },
    { ClkTagBar,        0,          Button1,    view,           {0} },
    { ClkTagBar,        0,          Button3,    toggleview,     {0} },
    { ClkTagBar,        MODKEY,     Button1,    tag,            {0} },
    { ClkTagBar,        MODKEY,     Button3,    toggletag,      {0} },
};

/* vim: set expandtab sw=4 ts=4: */
