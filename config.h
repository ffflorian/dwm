/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
	"monospace:size=10",
	"Source Code Pro:size=10"
};
#define NUMCOLORS         4
static const char colors[NUMCOLORS][MAXCOLORS][8] = {
  // border   foreground background
  { "#444444", "#bbbbbb", "#222222" },  // normal
  { "#008f46", "#eeeeee", "#008f46" },  // selected
  { "#ff0000", "#000000", "#ffff00" },  // urgent/warning  (black on yellow)
  { "#ff0000", "#ffffff", "#ff0000" },  // error (white on red)
  // add more here
};
static const char dmenufont[]       = "Source Code Pro:size=10";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", colors[0][2], "-nf", colors[0][1], "-sb", colors[1][2], "-sf", colors[1][1], NULL };
static const char *termcmd[]     = { "urxvt", NULL };
static const char *lockcmd[]     = { "slock", NULL };
static const char *telegramcmd[] = { "telegram", NULL };
static const char *spotifycmd[]  = { "spotify", NULL };

#include "selfrestart.c"

static Key keys[] = {
	/* modifier                     key                      function        argument */
	{ MODKEY,                       XK_b,                    togglebar,      {0} },
	{ MODKEY,                       XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                    incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                    incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_j,                    setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_p,                    zoom,           {0} },
	{ MODKEY,                       XK_Tab,                  view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                    killclient,     {0} },
	{ MODKEY,                       XK_w,                    killclient,     {0} },
	{ MODKEY,                       XK_t,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                togglefloating, {0} },
	{ MODKEY,                       XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,               focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,               tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Left,                 x_prevtag,      {0} },
	{ MODKEY,                       XK_Right,                x_nexttag,      {0} },
	{ MODKEY|ShiftMask,             XK_r,                    self_restart,   {0} },
	{ MODKEY|ShiftMask,             XK_q,                    quit,           {0} },
	{ MODKEY,                       XK_Return,               spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_r,                    spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_l,                    spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_t,                    spawn,          {.v = telegramcmd } },
	{ MODKEY,                       XK_s,                    spawn,          {.v = spotifycmd } },
	{ MODKEY,                       XK_c,                    spawn,          SHCMD("chromium || chromium-browser") },
	{ 0,                            XK_Print,                spawn,          SHCMD("scrot --multidisp ~/Pictures/screenshot_%Y-%m-%d_%H-%M-%S.png") },
	{ 0|ShiftMask,                  XK_Print,                spawn,          SHCMD("scrot --focused ~/Pictures/screenshot_%Y-%m-%d_%H-%M-%S.png") },
	{ 0|ControlMask|ShiftMask,      XK_Print,                spawn,          SHCMD("scrot --select ~/Pictures/screenshot_%Y-%m-%d_%H-%M-%S.png") },
	{ 0,                            XF86XK_AudioMute,        spawn,          SHCMD("amixer -q set Master toggle || amixer -c 1 -q set Master toggle") },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,          SHCMD("amixer -q set Master 2- unmute || amixer -c 1 -q set Master 2- unmute") },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,          SHCMD("amixer -q set Master 2+ unmute || amixer -c 1 -q set Master 2+ unmute") },
	{ MODKEY,                       XK_Down,                 spawn,          SHCMD("amixer -q set Master 2- unmute || amixer -c 1 -q set Master 2- unmute") },
	{ MODKEY,                       XK_Up,                   spawn,          SHCMD("amixer -q set Master 2+ unmute || amixer -c 1 -q set Master 2+ unmute") },
	TAGKEYS(                        XK_1,                                    0)
	TAGKEYS(                        XK_2,                                    1)
	TAGKEYS(                        XK_3,                                    2)
	TAGKEYS(                        XK_4,                                    3)
	TAGKEYS(                        XK_5,                                    4)
	TAGKEYS(                        XK_6,                                    5)
	TAGKEYS(                        XK_7,                                    6)
	TAGKEYS(                        XK_8,                                    7)
	TAGKEYS(                        XK_9,                                    8)
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
