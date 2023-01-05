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
static char normbgcolor[]		= "#1d2021";
static char normbordercolor[]		= "#1d2021";
static char normfgcolor[]		= "#ebdbb2";
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

static const char *const autostart[] = {
	"dwmblocks", NULL,
	"picom", NULL,
	"unclutter", NULL,
	NULL /* terminate */
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
	{ "floating",NULL,     NULL,           0,         1,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layouts */
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


/* keybinds */
#include <X11/XF86keysym.h>
#define XF86XK_PrtScr 0x0000ff61
static const Key keys[] = {
	{ 0,			XF86XK_AudioMute, 	spawn, 	   	SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0,		XF86XK_AudioLowerVolume, 	spawn, 	   	SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
	{ 0,		XF86XK_AudioRaiseVolume, 	spawn, 	   	SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
	{ 0,		XF86XK_MonBrightnessUp,		spawn,		SHCMD("brightnessctl set 5%+; kill -45 $(pidof dwmblocks)") },
	{ 0,		XF86XK_MonBrightnessDown,	spawn,		SHCMD("brightnessctl set 5%-; kill -45 $(pidof dwmblocks)") },
	{ 0, 				XF86XK_PrtScr,	spawn,		SHCMD("scrot -F \"$HOME/pics/screenshots/%Y-%m-%d-%H-%M-%S.png\" ") },
	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY,			XK_w,		spawn,		{.v = (const char *[]){ "dmenu-wifi", NULL } } },
	{ MODKEY,			XK_i,		spawn,		{.v = (const char *[]){ "firefox", NULL } } },
	{ MODKEY,			XK_o,		spawn,		{.v = (const char*[]){ "st", "-e", "lf",  NULL } } },
	{ MODKEY,			XK_p,		spawn,		{.v = (const char*[]){ "dmenu-passmenu", NULL } } },
	{ MODKEY,			XK_a,		incnmaster,	{.i = +1 } },
	{ MODKEY,			XK_s,		incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_d,		spawn,		{.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	{ MODKEY,			XK_h,		focusmon,	{.i = -1 } },
	{ MODKEY,			XK_j,		focusstack,	{.i = +1 } },
	{ MODKEY,			XK_k,		focusstack,	{.i = -1 } },
	{ MODKEY,			XK_l,		focusmon,	{.i = +1 } },
	{ MODKEY,			XK_Return,	spawn,		{.v = (const char *[]){ "st", NULL } } },
	{ MODKEY,			XK_z,		spawn,		{.v = (const char *[]){ "dwm-keylay", NULL } } },
	{ MODKEY,			XK_v,		spawn,		SHCMD("st -c floating -e pulsemixer && kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			XK_b,		spawn,		{.v = (const char *[]){ "dmenu-bluetooth", NULL } } },
	{ MODKEY,			XK_m,		spawn,		{.v = (const char *[]){ "thunderbird" , NULL } } },
	{ MODKEY,			XK_n,		spawn,		{.v = (const char*[]){ "st", "-e", "nvim", NULL } } },
	{ MODKEY|ShiftMask,             XK_q,      	spawn,		{.v = (const char *[]){ "dwm-quitmenu", NULL } } },
	{ MODKEY|ShiftMask,		XK_y,		moveresize,	{.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,		XK_u,		moveresize,	{.v = "0x 25y 0w 0h" } },
	{ MODKEY|ShiftMask,		XK_i,		moveresize,	{.v = "0x -25y 0w 0h" } },
	{ MODKEY|ShiftMask,		XK_o,		moveresize,	{.v = "25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,		XK_h,		tagmon,		{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_j,		movestack,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_k,		movestack,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_l,		tagmon,		{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Return,	zoom,		{0} },
	{ MODKEY|ShiftMask,		XK_m,		spawn,		{.v = (const char *[]){ "dwm-monmenu", NULL } } },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },
	{ MODKEY|ControlMask,		XK_y,		moveresize,	{.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,		XK_u,		moveresize,	{.v = "0x 0y 0w 25h" } },
	{ MODKEY|ControlMask,		XK_i,		moveresize,	{.v = "0x 0y 0w -25h" } },
	{ MODKEY|ControlMask,		XK_o,		moveresize,	{.v = "0x 0y 25w 0h" } },
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
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "lineheight",		INTEGER, &user_bh },
		{ "font",		STRING,  &font },
		{ "selbackground",	STRING,  &selbgcolor },
		{ "selbordercolor",	STRING,  &selbordercolor },
		{ "selforeground",	STRING,  &selfgcolor },
		//{ "baralpha",		INTEGER, &baralpha },
		{ "background",		STRING,  &normbgcolor },
		{ "bordercolor",	STRING,  &normbordercolor },
		{ "foreground",		STRING,  &normfgcolor },
		{ "gap",		INTEGER,  &gappx },
		{ "borderpx",		INTEGER, &borderpx },
		{ "mfact",		FLOAT,   &mfact },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "snap",		INTEGER, &snap },
};
