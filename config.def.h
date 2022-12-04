/* options */
static const int swallowfloating    	= 0;		/* 1 means swallow floating windows by default */
static int showbar            		= 1;		/* 0 means no bar */
static int topbar             		= 1;		/* 0 means bottom bar */
static int user_bh            		= 0;		/* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static char font[]            		= "Hack Nerd Font:size=12";
static const char *fonts[]          	= { font };
static char selbgcolor[]		= "#458588";
static char selbordercolor[]		= "#458588";
static char selfgcolor[]		= "#ebdbb2";
static const unsigned int baralpha 	= 230;
static const unsigned int borderalpha 	= OPAQUE;
static char normbgcolor[]		= "#282828";
static char normbordercolor[]		= "#282828";
static char normfgcolor[]		= "#ebdbb2";
static char dmenufont[]       		= "Hack Nerd Font:size=12";
static unsigned int gappx 		= 5;		/* gaps between windows */
static unsigned int borderpx  		= 1;		/* border pixel of windows */
static float mfact     			= 0.5; 		/* factor of master area size [0.05..0.95] */
static int nmaster     			= 1;		/* number of clients in master area */
static int resizehints 			= 1;		/* 1 means respect size hints in tiled resizals */
static unsigned int snap      		= 32;		/* snap pixel */
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },

};
static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "firefox", NULL,     NULL,           0,    	  0,          0,           1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layouts */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTMOD Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
  	{ MODKEY|Mod1Mask,		KEY,      swaptags,       {.ui = 1 << TAG} },
#define STATUSBAR "dwmblocks"

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "st", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *passcmd[]  = { "passmenu", NULL };
static const char *quitmenu[] = { "dwm-quitmenu", NULL };
static const char *tdualmon[] = { "dwm-tdualmon", NULL };
static const char *keylay[] = { "dwm-keylay", NULL };

/* keybinds */
#include <X11/XF86keysym.h>
static const Key keys[] = {
	{ 0,		XF86XK_AudioLowerVolume, 	spawn, 	   	SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof STATUSBAR)") },
	{ 0,			XF86XK_AudioMute, 	spawn, 	   	SHCMD("pamixer -t; kill -44 $(pidof STATUSBAR)") },
	{ 0,		XF86XK_AudioRaiseVolume, 	spawn, 	   	SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof STATUSBAR)") },
	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY,			XK_p,		spawn,		{.v = passcmd } },
	{ MODKEY,			XK_a,		incnmaster,	{.i = +1 } },
	{ MODKEY,			XK_s,		incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_d,		spawn,		{.v = dmenucmd } },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	{ MODKEY,			XK_h,		focusmon,	{.i = -1 } },
	{ MODKEY,			XK_j,		focusstack,	{.i = +1 } },
	{ MODKEY,			XK_k,		focusstack,	{.i = -1 } },
	{ MODKEY,			XK_l,		focusmon,	{.i = +1 } },
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY,			XK_z,		spawn,		{.v = keylay } },
	{ MODKEY,			XK_m,		spawn,		{.v = tdualmon } },
	{ MODKEY|ShiftMask,             XK_q,      	spawn,		{.v = quitmenu } },
	{ MODKEY|ShiftMask,		XK_u,		moveresize,	{.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,		XK_i,		moveresize,	{.v = "0x 25y 0w 0h" } },
	{ MODKEY|ShiftMask,		XK_o,		moveresize,	{.v = "0x -25y 0w 0h" } },
	{ MODKEY|ShiftMask,		XK_p,		moveresize,	{.v = "25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,		XK_h,		tagmon,		{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_j,		movestack,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_k,		movestack,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_l,		tagmon,		{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Return,	zoom,		{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },
	{ MODKEY|ControlMask,		XK_u,		moveresize,	{.v = "0x 0y 0w 25h" } },
	{ MODKEY|ControlMask,		XK_i,		moveresize,	{.v = "0x 0y 0w -25h" } },
	{ MODKEY|ControlMask,		XK_o,		moveresize,	{.v = "0x 0y 25w 0h" } },
	{ MODKEY|ControlMask,		XK_p,		moveresize,	{.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,		XK_h,		setmfact,	{.f = -0.05} },
	{ MODKEY|ControlMask,		XK_l,		setmfact,	{.f = +0.05} },
	{ MODKEY|ControlMask,		XK_j,		inplacerotate,	{.i = +2} },
	{ MODKEY|ControlMask,		XK_k,		inplacerotate,	{.i = -2} },
	// alltags
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },
	// tagkeys
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* Xresources preferences */
ResourcePref resources[] = {
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "barheight",		INTEGER, &user_bh },
		{ "font",               STRING,  &font },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		//{ "baralpha",		INTEGER, &baralpha },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "gap",              	INTEGER,  &gappx },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "mfact",      	FLOAT,   &mfact },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "snap",          	INTEGER, &snap },
};
